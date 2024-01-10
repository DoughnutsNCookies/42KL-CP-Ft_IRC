/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Executor.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:34:45 by schuah            #+#    #+#             */
/*   Updated: 2024/01/10 18:23:54 by schuah           ###   ########.fr       */
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
		std::pair<std::string, TOKEN>("TOPIC", TOPIC),
		std::pair<std::string, TOKEN>("PONG", PONG),
		std::pair<std::string, TOKEN>("QUIT", QUIT),
		std::pair<std::string, TOKEN>("PART", PART),
		std::pair<std::string, TOKEN>("UNKNOWN", UNKNOWN)
	};

	for (size_t i = 0; tokenPairs[i].second != UNKNOWN; i++) {
		if (tokenPairs[i].first == token)
			return (tokenPairs[i].second);
	}
	return (UNKNOWN);
}
tokensVector Executor::_getNextTokens(tokensVector& tokens) {
    tokensVector::iterator	it = std::find(tokens.begin(), tokens.end(), "\r\n");
    size_t					tokensToCopy = std::distance(tokens.begin(), it);
    tokensVector			result(tokens.begin(), tokens.begin() + tokensToCopy);

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
		std::pair<TOKEN, ATokenParser *>(KICK, &this->_Kick),
		std::pair<TOKEN, ATokenParser *>(TOPIC, &this->_Topic),
		std::pair<TOKEN, ATokenParser *>(PONG, &this->_Pong),
		std::pair<TOKEN, ATokenParser *>(QUIT, &this->_Quit),
		std::pair<TOKEN, ATokenParser *>(PART, &this->_Part)
	};

	while (tokens.size() > 0) {
		tokensVector	currentTokens = this->_getNextTokens(tokens);
		TOKEN	token = this->_getToken(currentTokens[0]);
		if (token == UNKNOWN) {
			this->_SendMsg.error421(irc, client, currentTokens[0]);
			continue;
		}
		verifyTokensPairs[token].second->verifyTokens(irc, client, currentTokens);
	}
}
