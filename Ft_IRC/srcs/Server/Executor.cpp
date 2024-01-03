/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Executor.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:34:45 by schuah            #+#    #+#             */
/*   Updated: 2024/01/03 20:26:47 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server/Executor.hpp"

Executor::Executor() {}

TOKEN	Executor::_getToken(std::string token) {
	const std::pair<std::string, TOKEN> tokenPairs[] = {
		std::pair<std::string, TOKEN>("PASS", PASS),
		std::pair<std::string, TOKEN>("NICK", NICK),
		std::pair<std::string, TOKEN>("USER", USER),
		std::pair<std::string, TOKEN>("PRIVMSG", PRIVMSG),
		std::pair<std::string, TOKEN>("JOIN", JOIN),
		std::pair<std::string, TOKEN>("KICK", KICK),
		std::pair<std::string, TOKEN>("TOPIC", TOPIC)
	};

	for (int i = 0; i < 7; i++) {
		if (tokenPairs[i].first == token)
			return (tokenPairs[i].second);
	}
	return (UNKNOWN);
}

tokensVector Executor::_getNextTokens(tokensVector& tokens) {
    tokensVector::iterator	it = std::find(tokens.begin(), tokens.end(), "\r\n");
    size_t									tokensToCopy = std::distance(tokens.begin(), it);
    tokensVector						result(tokens.begin(), tokens.begin() + tokensToCopy);

    tokens.erase(tokens.begin(), it + 1);
    return result;
}

void	Executor::execute(t_irc& irc, Client& client, tokensVector& tokens) {
	const std::pair<TOKEN, ATokenParser *>	verifyTokensPairs[] = {
		std::pair<TOKEN, ATokenParser *>(PASS, &this->_Pass),
		std::pair<TOKEN, ATokenParser *>(NICK, &this->_Nick),
		std::pair<TOKEN, ATokenParser *>(USER, &this->_User),
		std::pair<TOKEN, ATokenParser *>(PRIVMSG, &this->_Privmsg),
		std::pair<TOKEN, ATokenParser *>(JOIN, &this->_Join),
		std::pair<TOKEN, ATokenParser *>(KICK, &this->_Kick)
	};

	while (tokens.size() > 0) {
		tokensVector	currentTokens = this->_getNextTokens(tokens);
		TOKEN	token = this->_getToken(currentTokens[0]);
		if (token == UNKNOWN) {
			this->_SendMsg.error421(irc, client, currentTokens[0]);
			continue;
		}
		// if (irc.password.length() != 0 && token != PASS && client.verified == false) {
		// 	this->_SendMsg.error451(client);
		// 	continue;
		// }
		verifyTokensPairs[token].second->verifyTokens(irc, client, currentTokens);
	}
}

void	Executor::disconnect(t_irc& irc, int i) {
	std::vector<struct pollfd>&	fds = irc.fds;
	std::map<int, Client>&			clients = irc.clients;
	int													pollfd = fds[i].fd;
	
	std::map<std::string, Channel>	&channels = irc.channels;
	tokensVector										channelsJoined = clients[pollfd].channels;
	for (size_t j = 0; j < channelsJoined.size(); j++)
		channels[channelsJoined[j]].users.erase(clients[pollfd].nickname);
	
	std::cout << RED << "Client " << clients[pollfd].nickname << " Disconnected" << RESET << std::endl;
	
	close(pollfd);
	fds.erase(fds.begin() + i);
	clients.erase(pollfd);
}
