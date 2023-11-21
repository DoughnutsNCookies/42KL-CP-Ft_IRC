/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 18:46:46 by plau              #+#    #+#             */
/*   Updated: 2023/11/21 17:44:18 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pass.hpp"
#include <iostream>

Pass::Pass() {}

void	Pass::verify(t_irc& irc, Client& client, tokensVector &tokens) {
	if (client._verified) {
		this->_SendError.error462(client);
		return;
	}
	if (irc._password.size() == 0) {
		client._verified = true;
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
	client._verified = true;
	client._response.clear();
}

void	Pass::_parseTokens(tokensVector &tokens) {
	this->_user_password = tokens[1];
	if (this->_user_password[0] == ':')
		this->_user_password.erase(0, 1);
}
