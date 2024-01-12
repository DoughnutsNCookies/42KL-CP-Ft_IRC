/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 13:33:41 by plau              #+#    #+#             */
/*   Updated: 2024/01/12 17:23:30 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands/User.hpp"

User::User() {}

void	User::verifyTokens(t_irc& irc, Client& client, tokensVector &tokens) {
	if (client.userSet) {
		this->_SendMsg.error462(irc, client);
		return;
	}

	if (tokens.size() < 5) {
		this->_SendMsg.error461(irc, client, tokens[0]);
		return;
	}

	this->_parseTokens(tokens);
	if (this->_username.size() == 0 || this->_realname.size() == 0) {
		this->_SendMsg.error461(irc, client, tokens[0]);
		return;
	}

	this->_executeCommand(irc, client);
}

void	User::_parseTokens(tokensVector &tokens) {
	this->_username = this->_Utils.extractFromToken(tokens[1]);
	this->_realname = this->_Utils.extractFromToken(tokens[4]);
	for (size_t i = 5; i < tokens.size(); i++)
		this->_realname += " " + tokens[i];
}

void::User::_executeCommand(t_irc& irc, Client& client) {
	client.username = this->_username;
	client.realname = this->_realname;
	client.userSet = true;
	this->_SendMsg.registeredMsg(irc, client);
}
