/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 18:46:46 by plau              #+#    #+#             */
/*   Updated: 2023/11/29 21:09:47 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands/Pass.hpp"

Pass::Pass() {}

void	Pass::verifyTokens(t_irc& irc, Client& client, tokensVector& tokens) {
	if (client.verified) {
		this->_SendMsg.error462(irc, client);
		return;
	}
	if (irc.password.size() == 0) {
		this->_executeCommand(irc, client);
		return;
	}

	if (tokens.size() == 1) {
		this->_SendMsg.error461(irc, client, tokens[0]);
		return;
	}
	if (tokens.size() > 2) {
		this->_SendMsg.error464(irc, client);
		return;
	}
	
	this->_parseTokens(tokens);
	if (irc.password != this->_userPassword) {
		this->_SendMsg.error464(irc, client);
		return;
	}
	this->_executeCommand(irc, client);
}

void	Pass::_parseTokens(tokensVector& tokens) {
	this->_userPassword = tokens[1];
	if (this->_userPassword[0] == ':')
		this->_userPassword.erase(0, 1);
}

void	Pass::_executeCommand(t_irc& irc, Client& client) {
	(void)irc;
	client.verified = true;
	client.response.clear();
}
