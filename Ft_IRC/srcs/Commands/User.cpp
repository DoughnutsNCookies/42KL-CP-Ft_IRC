/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 13:33:41 by plau              #+#    #+#             */
/*   Updated: 2023/11/29 21:09:47 by schuah           ###   ########.fr       */
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
	this->_parseTokens(tokens);
	if (this->_username.size() == 0) {
		this->_SendMsg.error461(irc, client, tokens[0]);
		return;
	}
	this->_executeCommand(irc, client);
}

void	User::_parseTokens(tokensVector &tokens) {
	this->_username = tokens[1];
	if (this->_username[0] == ':')
		this->_username.erase(0, 1);
	if (this->_username.size() > 15)
		this->_username = this->_username.substr(0, 15);
	
	this->_realname = tokens[4];
	size_t	tokensSize = tokens.size();
	if (tokensSize < 5)
		this->_realname = "";
	for (size_t i = 5; i < tokensSize; i++)
		this->_realname += " " + tokens[i];
	if (this->_realname[0] == ':')
		this->_realname.erase(0, 1);
}

void::User::_executeCommand(t_irc& irc, Client& client) {
	(void)irc;
	client.username = this->_username;
	client.realname = this->_realname;
	if (client.realname.empty())
		client.realname = client.nickname;
}
