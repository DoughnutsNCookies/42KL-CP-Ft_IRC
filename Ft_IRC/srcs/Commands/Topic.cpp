/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 16:53:57 by plau              #+#    #+#             */
/*   Updated: 2024/01/10 17:13:57 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands/Topic.hpp"

Topic::Topic() {}

void	Topic::verifyTokens(t_irc& irc, Client& client, tokensVector& tokens) {
	if (tokens.size() < 2 || tokens[1].size() == 0) {
		this->_SendMsg.error461(irc, client, tokens[0]);
		return ;
	}

	this->_parseTokens(tokens);
	Channel	channel;
	try {
		channel = this->_Utils.getChannelByName(irc, this->_channelName);
	} catch (Utils::NoChannelFoundException& e) {
		this->_SendMsg.error403(irc, client, this->_channelName);
		return ;
	}

	if (channel.users.find(client.nickname) == channel.users.end()) {
		this->_SendMsg.error442(irc, client, this->_channelName);
		return ;
	}

	this->_executeCommand(irc, client);
}

void	Topic::_parseTokens(tokensVector& tokens) {
	this->_channelName = this->_Utils.extractFromToken(tokens[1]);

	if (tokens.size() > 2)
		this->_topic = this->_Utils.extractFromToken(tokens[2]);
	for (size_t i = 3; i < tokens.size(); i++)
		this->_topic += " " + tokens[i];

	this->_setTopic = tokens.size() > 2;
}

void	Topic::_executeCommand(t_irc& irc, Client& client) {
	Channel&	channel = irc.channels[this->_channelName];
	if (this->_setTopic == false)
		this->_setNewTopic(irc, client, channel);
	else
		this->_getTopic(irc, client, channel);
}

void	Topic::_setNewTopic(t_irc& irc, Client& client, Channel& channel) {
	if (channel.topic.empty()) {
		this->_SendMsg.rpl331(irc, client, this->_channelName);
	} else {
		this->_SendMsg.rpl332(irc, client, this->_channelName, channel.topic);
		this->_SendMsg.rpl333(irc, client, this->_channelName);
	}
}

void	Topic::_getTopic(t_irc& irc, Client& client, Channel& channel) {
	channel.topic = this->_topic;
	std::string message = ":" + client.nickname + " TOPIC " + this->_channelName + " :" + this->_topic + "\r\n";
	this->_SendMsg.sendToAllUsersInChannel(irc, client, channel, message, true);
}
