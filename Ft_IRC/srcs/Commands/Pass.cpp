/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 18:46:46 by plau              #+#    #+#             */
/*   Updated: 2023/11/28 12:21:45 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands/Pass.hpp"

Pass::Pass() {}

void	Pass::verifyTokens(t_irc& irc, Client& client, tokensVector& tokens) {
	if (client._verified) {
		this->_SendError.error462(client);
		return;
	}
	if (irc._password.size() == 0) {
		this->_executeCommand(irc, client);
		return;
	}

	if (tokens.size() == 1) {
		this->_SendError.error461(client);
		return;
	}
	if (tokens.size() > 2) {
		this->_SendError.error464(client);
		return;
	}
	
	this->_parseTokens(tokens);
	if (irc._password != this->_user_password) {
		this->_SendError.error464(client);
		return;
	}
	this->_executeCommand(irc, client);
}

void	Pass::_parseTokens(tokensVector& tokens) {
	this->_user_password = tokens[1];
	if (this->_user_password[0] == ':')
		this->_user_password.erase(0, 1);
}

void	Pass::_executeCommand(t_irc& irc, Client& client) {
	(void)irc;
	client._verified = true;
	client._response.clear();
}
