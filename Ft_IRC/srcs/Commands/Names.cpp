/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Names.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 22:13:56 by plau              #+#    #+#             */
/*   Updated: 2024/01/11 21:09:38 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands/Names.hpp"

Names::Names() {}

void	Names::verifyTokens(t_irc& irc, Client& client, tokensVector& tokens) {
	if (tokens.size() < 2) {
		this->_displayAll(irc, client);
		return;
	}
	this->_parseTokens(tokens);
	this->_executeCommand(irc, client);
}

void	Names::_displayAll(t_irc& irc, Client& client) {
	if (irc.channels.size() == 0)
		return;
	for (std::map<std::string, Channel>::iterator it = irc.channels.begin(); it != irc.channels.end(); it++) {
		this->_SendMsg.rpl353(irc, client, it->second);
		this->_SendMsg.rpl366(irc, client, it->second.name);
	}
}

void	Names::_parseTokens(tokensVector& tokens) {
	this->_nameList = this->_Parser.parse(tokens[1], ",", false);
	if (this->_nameList.size() == 0)
		return;
	for (size_t i = 0; i < this->_nameList.size(); i++) {
		if (this->_nameList[i][0] != '#')
			this->_nameList[i] = "#" + this->_nameList[i];
	}
}

void	Names::_executeCommand(t_irc& irc, Client& client) {
	for (size_t i = 0; i < this->_nameList.size(); i++) {
		if (irc.channels.find(this->_nameList[i]) != irc.channels.end()) {
			this->_SendMsg.rpl353(irc, client, irc.channels[this->_nameList[i]]);
			this->_SendMsg.rpl366(irc, client, irc.channels[this->_nameList[i]].name);
		} else {
			this->_SendMsg.rpl366(irc, client, this->_nameList[i]);
		}
	}
}
