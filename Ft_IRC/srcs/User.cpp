/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 13:33:41 by plau              #+#    #+#             */
/*   Updated: 2023/11/22 19:51:18 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"
#include <iostream>

User::User() {}

void	User::verifyTokens(t_irc& irc, Client& client, tokensVector &tokens) {
	if (client._username.size() != 0) {
		this->_SendError.error462(client);
		return;
	}
	if (tokens[2] != "0" || tokens[3] != "*") {
		this->_SendError.error461(client);
		return;
	}
	this->_parseTokens(tokens);
	if (this->_username.size() == 0) {
		this->_SendError.error461(client);
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
	client._username = this->_username;
	client._realname = this->_realname;
	if (client._realname.empty())
		client._realname = client._nickname;
}
