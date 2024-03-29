/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Names.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 22:13:56 by plau              #+#    #+#             */
/*   Updated: 2024/01/12 19:20:47 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands/Names.hpp"

Names::Names() {}

void	Names::verifyTokens(t_irc& irc, Client& client, tokensVector& tokens) {
	this->_parseTokens(tokens);
	this->_executeCommand(irc, client);
}

void	Names::_parseTokens(tokensVector& tokens) {
	this->_nameAll = false;
	if (tokens.size() < 2) {
		this->_nameAll = true; 
		return;
	}

	std::string	nameList = this->_Utils.extractFromToken(tokens[1]);
	this->_nameList = this->_Parser.parse(nameList, ",", false);
	for (size_t i = 0; i < this->_nameList.size(); i++) {
		if (this->_nameList[i][0] != '#')
			this->_nameList[i] = "#" + this->_nameList[i];
	}
}

void	Names::_executeCommand(t_irc& irc, Client& client) {
	if (this->_nameAll)
		this->_displayAllNames(irc, client);
	else
		this->_displaySpecifiedNames(irc, client);
}

void	Names::_displayAllNames(t_irc& irc, Client& client) {
	for (std::map<std::string, Channel>::iterator it = irc.channels.begin(); it != irc.channels.end(); it++) {
		this->_SendMsg.rpl353(irc, client, it->second);
		this->_SendMsg.rpl366(irc, client, it->second.name);
	}
}

void	Names::_displaySpecifiedNames(t_irc& irc, Client& client) {
	for (size_t i = 0; i < this->_nameList.size(); i++) {
		if (irc.channels.find(this->_nameList[i]) != irc.channels.end())
			this->_SendMsg.rpl353(irc, client, irc.channels[this->_nameList[i]]);
		this->_SendMsg.rpl366(irc, client, this->_nameList[i]);
	}
}
