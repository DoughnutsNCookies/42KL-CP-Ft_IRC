/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:49:16 by plau              #+#    #+#             */
/*   Updated: 2023/11/28 18:13:06 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands/Nick.hpp"

Nick::Nick() {}

void	Nick::verifyTokens(t_irc& irc, Client& client, tokensVector& tokens) {
	if (tokens.size() == 1 || tokens[1].size() == 0) {
		this->_SendError.error431(irc, client);
		return;
	}
	if (tokens.size() > 2) {
		this->_SendError.error432(irc, client, tokens[1]);
		return;
	}
	this->_parseTokens(tokens);
	if (this->_checkValidNickName(this->_nickname) == false) {
		this->_SendError.error432(irc, client, this->_nickname);
		return;
	}
	for (std::map<int, Client>::iterator it = irc.clients.begin(); it != irc.clients.end(); ++it) {
		if (it->second.nickname == this->_nickname) {
			this->_SendError.error433(irc, client, this->_nickname);
			return;
		}
	}
	this->_executeCommand(irc, client);
}

bool	Nick::_checkValidNickName(std::string nickname) {
	std::string	invalid = "#: ";

	return (!(invalid.find(nickname[0]) != std::string::npos
		|| (nickname[0] == '&' && nickname[1] == '#')));
}

void	Nick::_parseTokens(tokensVector& tokens) {
	this->_nickname = tokens[1];
	if (this->_nickname[0] == ':')
		this->_nickname.erase(0, 1);
}

void	Nick::_executeCommand(t_irc& irc, Client& client) {
	(void)irc;
	client.nickname = this->_nickname;
}