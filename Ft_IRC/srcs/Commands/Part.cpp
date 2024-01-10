/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:13:48 by schuah            #+#    #+#             */
/*   Updated: 2024/01/10 17:47:53 by schuah           ###   ########.fr       */
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

void	Part::_parseTokens(tokensVector& tokens) {
	tokensVector	parsedChannelNames = this->_Parser.parse(tokens[1], ",");
	if (parsedChannelNames.size() == 0)
		return;
	for (size_t i = 0; i < parsedChannelNames.size(); i++) {
		if (parsedChannelNames[i][0] != '#')
			parsedChannelNames[i] = "#" + parsedChannelNames[i];
	}
	parsedChannelNames.erase(parsedChannelNames.end() - 1);
	this->_channelNames = std::set<std::string>(parsedChannelNames.begin(), parsedChannelNames.end());

	if (tokens.size() > 2)
		this->_reason = this->_Utils.extractFromToken(tokens[2]);
	for (size_t i = 3; i < tokens.size(); i++)
		this->_reason += " " + tokens[i];
}

void	Part::_executeCommand(t_irc& irc, Client& client) {
	for (std::set<std::string>::iterator it = this->_channelNames.begin(); it != this->_channelNames.end(); it++) {
		std::string	channelName = *it;
		try {
			Channel&	channel = this->_Utils.getChannelByName(irc, channelName);
			if (channel.users.find(client.nickname) == channel.users.end()) {
				this->_SendMsg.error442(irc, client, channelName);
				continue;
			}
			this->_leaveChannel(irc, client, channel);
		} catch (Utils::NoChannelFoundException& e) {
			this->_SendMsg.error403(irc, client, channelName);
			continue;
		}
	}
}

void	Part::_leaveChannel(t_irc& irc, Client& client, Channel& channel) {
	std::string	message = ":" + client.nickname + " PART " + channel.name + " :" + this->_reason + "\r\n";
	this->_SendMsg.sendToAllUsersInChannel(irc, client, channel, message, true);

	channel.users.erase(client.nickname);
	std::remove(client.channels.begin(), client.channels.end(), channel.name);
	if (channel.users.size() == 0)
		irc.channels.erase(channel.name);
}
