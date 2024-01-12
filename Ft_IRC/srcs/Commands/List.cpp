/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   List.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:24:13 by plau              #+#    #+#             */
/*   Updated: 2024/01/12 16:28:43 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands/List.hpp"

List::List() {}

void	List::verifyTokens(t_irc& irc, Client& client, tokensVector& tokens) {
	this->_parseTokens(tokens);
	this->_executeCommand(irc, client);
}

void	List::_parseTokens(tokensVector& tokens) {
	this->_listAll = false;
	if (tokens.size() < 2) {
		this->_listAll = true; 
		return;
	}
	
	this->_channelList = this->_Parser.parse(tokens[1], ",", false);
	for (size_t i = 0; i < this->_channelList.size(); i++) {
		if (this->_channelList[i][0] != '#')
			this->_channelList[i] = "#" + this->_channelList[i];
	}
}

void	List::_executeCommand(t_irc& irc, Client& client) {
	this->_SendMsg.rpl321(irc, client);
	if (this->_listAll)
		this->_displayAllLists(irc, client);
	else
		this->_displaySpecifiedLists(irc, client);
	this->_SendMsg.rpl323(irc, client);
}

void	List::_displayAllLists(t_irc& irc, Client& client) {
	for (std::map<std::string, Channel>::iterator it = irc.channels.begin(); it != irc.channels.end(); it++)
		this->_SendMsg.rpl322(irc, client, it->second);
}

void	List::_displaySpecifiedLists(t_irc& irc, Client& client) {
	for (size_t i = 0; i < this->_channelList.size(); i++) {
		try {
			Channel&	channel = this->_Utils.getChannelByName(irc, this->_channelList[i]);
			this->_SendMsg.rpl322(irc, client, channel);
		} catch (Utils::NoChannelFoundException e) {
			continue;
		}
	}
}
