/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Executor.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:34:45 by schuah            #+#    #+#             */
/*   Updated: 2023/11/21 22:13:12 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Executor.hpp"

Executor::Executor() {}

TOKEN	Executor::_getToken(std::string token) {
	static const std::pair<const char*, TOKEN> tokenPairs[] = {
		std::pair<const char*, TOKEN>("PASS", PASS),
		std::pair<const char*, TOKEN>("NICK", NICK),
		std::pair<const char*, TOKEN>("USER", USER),
		std::pair<const char*, TOKEN>("JOIN", JOIN),
		std::pair<const char*, TOKEN>("PRIVMSG", PRIVMSG),
		std::pair<const char*, TOKEN>("KICK", KICK),
		std::pair<const char*, TOKEN>("TOPIC", TOPIC)
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

void	Executor::execute(t_irc& irc, Client& client, tokensVector &tokens) {
	while (tokens.size() > 0) {
		tokensVector	currentTokens = this->_getNextTokens(tokens);
		TOKEN	token = this->_getToken(currentTokens[0]);

		if (token == 0)
			this->_Pass.verifyTokens(irc, client, currentTokens);
		if (token == 1)
			this->_Nick.verifyTokens(irc, client, currentTokens);
	}
}

void	Executor::disconnect(t_irc& irc, int i) {
	std::vector<struct pollfd>&	fds = irc._fds;
	std::map<int, Client>&			clients = irc._clients;
	int													pollfd = fds[i].fd;

	std::cout << RED << "Client " << clients[pollfd]._nickname << " disconnected" << RESET << std::endl;
	close(pollfd);
	fds.erase(fds.begin() + i);
	clients.erase(pollfd);
}
