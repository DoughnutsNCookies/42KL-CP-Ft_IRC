/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:13:48 by schuah            #+#    #+#             */
/*   Updated: 2024/01/11 14:50:16 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands/Part.hpp"

Part::Part() {}

void	Part::verifyTokens(t_irc& irc, Client& client, tokensVector& tokens) {
	if (tokens.size() < 2)
		this->_SendMsg.error461(irc, client, tokens[0]);
	
	this->_parseTokens(tokens);
	if (this->_channelNames.size() == 0) {
		this->_SendMsg.error461(irc, client, tokens[1]);
		return;
	}
	
	this->_executeCommand(irc, client);
}

void	Part::leaveChannel(t_irc& irc, Client& client, Channel& channel) {
	channel.users.erase(client.nickname);
	if (channel.opName == client.nickname && channel.users.size() > 0)
		channel.opName = channel.users.begin()->second.nickname;

	for (size_t i = 0; i < client.channels.size(); i++) {
		if (client.channels[i] != channel.name)
			continue;
		client.channels.erase(client.channels.begin() + i);
		break;
	}

	if (channel.users.size() == 0)
		irc.channels.erase(channel.name);
}

void	Part::_parseTokens(tokensVector& tokens) {
	this->_channelNames = this->_Parser.parse(tokens[1], ",", false);
	if (this->_channelNames.size() == 0)
		return;

	std::set<std::string>	set(this->_channelNames.begin(), this->_channelNames.end());
	this->_channelNames = tokensVector(set.begin(), set.end());

	for (size_t i = 0; i < this->_channelNames.size(); i++) {
		if (this->_channelNames[i][0] != '#')
			this->_channelNames[i] = "#" + this->_channelNames[i];
	}

	if (tokens.size() > 2)
		this->_reason = this->_Utils.extractFromToken(tokens[2]);
	for (size_t i = 3; i < tokens.size(); i++)
		this->_reason += " " + tokens[i];
}

void	Part::_executeCommand(t_irc& irc, Client& client) {
	for (size_t i = 0; i < this->_channelNames.size(); i++) {
		try {
			Channel&	channel = this->_Utils.getChannelByName(irc, this->_channelNames[i]);
			if (channel.users.find(client.nickname) == channel.users.end()) {
				this->_SendMsg.error442(irc, client, this->_channelNames[i]);
				continue;
			}
			std::string	message = ":" + client.nickname + " PART " + channel.name + " :" + this->_reason + "\r\n";
			this->_SendMsg.sendToAllUsersInChannel(irc, client, channel, message, true);
			this->leaveChannel(irc, client, channel);
		} catch (Utils::NoChannelFoundException& e) {
			this->_SendMsg.error403(irc, client, this->_channelNames[i]);
			continue;
		}
	}
}
