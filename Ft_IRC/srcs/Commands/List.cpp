/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   List.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:24:13 by plau              #+#    #+#             */
/*   Updated: 2024/01/11 21:51:34 by plau             ###   ########.fr       */
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
	if (this->_listAll) {
		for (std::map<std::string, Channel>::iterator it = irc.channels.begin(); it != irc.channels.end(); it++) {
			this->_SendMsg.rpl322(irc, client, it->second);
		}
		this->_SendMsg.rpl323(irc, client);
		return;
	}

	for (size_t i = 0; i < this->_channelList.size(); i++) {
		Channel&	channel = this->_Utils.getChannelByName(irc, this->_channelList[i]);
		this->_SendMsg.rpl322(irc, client, channel);
	}
	this->_SendMsg.rpl323(irc, client);
}
