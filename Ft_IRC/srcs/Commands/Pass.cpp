/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 18:46:46 by plau              #+#    #+#             */
/*   Updated: 2024/01/16 21:40:26 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands/Pass.hpp"

Pass::Pass() {}

void	Pass::verifyTokens(t_irc& irc, Client& client, tokensVector& tokens) {
	client.bypassCheck = true;
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
	
	this->_parseTokens(tokens);
	if (irc.password != this->_userPassword) {
		this->_SendMsg.error464(irc, client);
		return;
	}
	
	this->_executeCommand(irc, client);
	client.bypassCheck = false;
}

void	Pass::_parseTokens(tokensVector& tokens) {
	this->_userPassword = this->_Utils.extractFromToken(tokens[1]);
}

void	Pass::_executeCommand(t_irc& irc, Client& client) {
	client.verified = true;
	this->_SendMsg.registeredMsg(irc, client);
}
