/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 20:25:39 by schuah            #+#    #+#             */
/*   Updated: 2023/11/28 21:33:42 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands/Join.hpp"
#include <iostream>

Join::Join() {}

void	Join::verifyTokens(t_irc& irc, Client& client, tokensVector& tokens) {
	if (tokens.size() < 2 || tokens[1].empty()) {
		this->_SendError.error461(irc, client, tokens[0]);
		return;
	}
	this->_parseTokens(tokens);
	if (this->_channelNames.size() == 0) {
		this->_SendError.error461(irc, client, tokens[0]);
		return;
	}
	this->_executeCommand(irc, client);
}

void	Join::_parseTokens(tokensVector& tokens) {
	this->_channelNames = this->_Parser.parse(tokens[1], ",");
	if (this->_channelNames.size() == 0)
		return;
	this->_channelNames.erase(this->_channelNames.end() - 1);
}

void	Join::_executeCommand(t_irc& irc, Client& client) {
	for (size_t i = 0; i < this->_channelNames.size(); i++) {
		std::map<std::string, Channel>::iterator it = irc.channels.find(this->_channelNames[i]);
		if (it == irc.channels.end())
			this->_createChannel(irc, client, this->_channelNames[i]);
		else if (it->second.users.find(client.nickname) == it->second.users.end())
			this->_joinChannel(irc, client, this->_channelNames[i]);
	}
}

void	Join::_createChannel(t_irc& irc, Client& client, std::string channelName) {
	Channel	newChannel = Channel(channelName);
	newChannel.users[client.nickname] = client;
	irc.channels[channelName] = newChannel;
	client.channels.push_back(channelName);
}

void	Join::_joinChannel(t_irc& irc, Client& client, std::string channelName) {
	client.channels.push_back(channelName);	
	Channel&	channel = irc.channels[channelName];
	channel.users[client.nickname] = client;
}
