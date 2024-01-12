/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 20:25:39 by schuah            #+#    #+#             */
/*   Updated: 2024/01/12 19:43:06 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands/Join.hpp"

Join::Join() {}

void	Join::verifyTokens(t_irc& irc, Client& client, tokensVector& tokens) {
	if (tokens.size() < 2 || tokens[1].empty()) {
		this->_SendMsg.error461(irc, client, tokens[0]);
		return;
	}

	this->_parseTokens(tokens);
	if (this->_channelNames.size() == 0) {
		this->_SendMsg.error461(irc, client, tokens[0]);
		return;
	}
	this->_executeCommand(irc, client);
}

void	Join::_parseTokens(tokensVector& tokens) {
	std::string	channelNames = this->_Utils.extractFromToken(tokens[1]);
	this->_channelNames = this->_Parser.parse(channelNames, ",", false);
	if (this->_channelNames.size() == 0)
		return;
	
	this->_leaveAll = false;
	for (size_t i = 0; i < this->_channelNames.size(); i++) {
		if (i == 0 && this->_channelNames[i] == "0") {
			this->_leaveAll = true;
			return;
		}
		if (this->_channelNames[i][0] != '#')
			this->_channelNames[i] = "#" + this->_channelNames[i];
	}
}

void	Join::_executeCommand(t_irc& irc, Client& client) {
	if (this->_leaveAll) {
		tokensVector	tokens(2, "PART");

		for (size_t i = 0; client.channels.size() > 0;) {
			tokens[1] = client.channels[i];
			this->_Part.verifyTokens(irc, client, tokens);
		}
		return ;
	}

	for (size_t i = 0; i < this->_channelNames.size(); i++) {
		std::map<std::string, Channel>::iterator	it = irc.channels.find(this->_channelNames[i]);
		if (it == irc.channels.end())
			this->_createChannel(irc, client, this->_channelNames[i]);
		else if (it->second.users.find(client.nickname) == it->second.users.end())
			this->_joinChannel(irc, client, this->_channelNames[i]);
	}
}

void	Join::_createChannel(t_irc& irc, Client& client, std::string channelName) {
	Channel	newChannel = Channel(channelName, client.nickname);
	newChannel.users[client.nickname] = client;
	irc.channels[channelName] = newChannel;
	client.channels.push_back(channelName);

	this->_SendMsg.customMsg(irc, client, ":" + client.nickname + " JOIN " + channelName + "\r\n");
	this->_SendMsg.rpl353(irc, client, newChannel);
	this->_SendMsg.rpl366(irc, client, channelName);
}

void	Join::_joinChannel(t_irc& irc, Client& client, std::string channelName) {
	client.channels.push_back(channelName);	
	Channel&	channel = irc.channels[channelName];
	channel.users[client.nickname] = client;
	
	std::string	message = ":" + client.nickname + " JOIN " + channelName + "\r\n";
	this->_SendMsg.customMsg(irc, client, message);
	if (channel.topic.empty() == false)
		this->_SendMsg.rpl332(irc, client, channelName, channel.topic);
	this->_SendMsg.rpl353(irc, client, channel);
	this->_SendMsg.rpl366(irc, client, channelName);
	this->_SendMsg.sendToAllUsersInChannel(irc, client, channel, message, false);
}
