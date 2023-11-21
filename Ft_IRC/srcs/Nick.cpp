/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:49:16 by plau              #+#    #+#             */
/*   Updated: 2023/11/21 21:27:23 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Nick.hpp"

Nick::Nick() {}

void	Nick::verifyTokens(t_irc& irc, Client& client, tokensVector &tokens) {
	if (tokens.size() == 1 || tokens[1].size() == 0) {
		this->_SendError.error431(client);
		return;
	}
	if (tokens.size() > 2) {
		this->_SendError.error432(client);
		return;
	}
	this->_parseTokens(tokens);
	if (this->_checkValidNickName(this->_nick_name) == false) {
		this->_SendError.error432(client);
		return;
	}
	for (std::map<int, Client>::iterator it = irc._clients.begin(); it != irc._clients.end(); ++it) {
		if (it->second._nickname != this->_nick_name)
			continue;
		this->_SendError.error433(client);
		return;
	}
	this->_executeCommand(irc, client);
}

bool	Nick::_checkValidNickName(std::string nickName) {
	std::string	invalid = "#: ";

	return (!(invalid.find(nickName[0]) != std::string::npos
		|| (nickName[0] == '&' && nickName[1] == '#')));
}

void	Nick::_parseTokens(tokensVector &tokens) {
	this->_nick_name = tokens[1];
	if (this->_nick_name[0] == ':')
		this->_nick_name.erase(0, 1);
}

void	Nick::_executeCommand(t_irc& irc, Client& client) {
	(void)irc;
	client._nickname = this->_nick_name;
}
