/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 13:33:41 by plau              #+#    #+#             */
/*   Updated: 2024/01/08 17:11:41 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands/User.hpp"

User::User() {}

void	User::verifyTokens(t_irc& irc, Client& client, tokensVector &tokens) {
	if (client.username.size() != 0) {
		this->_SendMsg.error462(irc, client);
		return;
	}

	if (tokens[2] != "0" || tokens[3] != "*") {
		this->_SendMsg.error461(irc, client, tokens[0]);
		return;
	}

	if (tokens.size() < 5) {
		this->_SendMsg.error461(irc, client, tokens[0]);
		return;
	}

	this->_parseTokens(tokens);
	this->_executeCommand(irc, client);
}

void	User::_parseTokens(tokensVector &tokens) {
	this->_username = this->_Utils.extractFromToken(tokens[1]);
	if (this->_username.size() > 15)
		this->_username = this->_username.substr(0, 15);
	
	this->_realname = tokens[4];
	for (size_t i = 5; i < tokens.size(); i++)
		this->_realname += " " + tokens[i];
	this->_realname = this->_Utils.extractFromToken(this->_realname);
}

void::User::_executeCommand(t_irc& irc, Client& client) {
	(void)irc;
	client.username = this->_username;
	client.realname = this->_realname;
	client.userSet = true;
	this->_SendMsg.registeredMsg(irc, client);
}
