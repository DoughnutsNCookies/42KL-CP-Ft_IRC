/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 13:50:29 by schuah            #+#    #+#             */
/*   Updated: 2024/01/10 17:58:28 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands/Privmsg.hpp"

Privmsg::Privmsg() {}

void	Privmsg::verifyTokens(t_irc& irc, Client& client, tokensVector& tokens) {
	if (tokens.size() == 1 || tokens[1].size() == 0) {
		this->_SendMsg.error411(irc, client, tokens[0]);
		return;
	}

	if (tokens.size() == 2 || tokens[2].size() == 0) {
		this->_SendMsg.error412(irc, client);
		return;
	}

	this->_parseTokens(tokens);
	if (this->_destinations.size() == 0) {
		this->_SendMsg.error411(irc, client, tokens[0]);
		return;
	}

	for (size_t i = 0; i < this->_destinations.size(); i++) {
		try {
			this->_Utils.getClientByNickname(irc, this->_destinations[i]);
		} catch(Utils::NoClientFoundException& clientError) {
			try {
				Channel& channel = this->_Utils.getChannelByName(irc, this->_destinations[i]);
				if (channel.users.find(client.nickname) == channel.users.end())
					throw Utils::NoChannelFoundException();
			} catch(Utils::NoChannelFoundException& channelError) {
				this->_SendMsg.error401(irc, client, this->_destinations[i]);
				return;
			}
		}
	}

	this->_executeCommand(irc, client);
}

void	Privmsg::_parseTokens(tokensVector& tokens) {
	std::string nicknames = this->_Utils.extractFromToken(tokens[1]);
	
	this->_destinations = this->_Parser.parse(nicknames, ",", false);
	if (this->_destinations.size() == 0)
		return;

	this->_message = this->_Utils.extractFromToken(tokens[2]);
	for (size_t i = 3; i < tokens.size(); i++)
		this->_message += " " + tokens[i];
}

void	Privmsg::_executeCommand(t_irc& irc, Client& client) {
	for (size_t i = 0; i < this->_destinations.size(); i++) {
		if (this->_destinations[i][0] == '#' || this->_destinations[i][0] == '@')
			this->_sendToChannel(irc, client, this->_destinations[i]);
		else {
			std::string	message = ":" + client.nickname + "!" + client.username + "@" + client.hostname + " PRIVMSG " + this->_destinations[i] + " :" + this->_message + "\r\n";
			this->_SendMsg.sendToUser(irc, this->_destinations[i], message);
		}
	}
}

void	Privmsg::_sendToChannel(t_irc& irc, Client& client, std::string channelName) {
	Channel&	channel = this->_Utils.getChannelByName(irc, channelName);
	std::string	message = ":" + client.nickname + "!" + client.username + "@" + client.hostname + " PRIVMSG " + channelName + " :" + this->_message + "\r\n";
	
	if (channelName[0] == '@')
		this->_SendMsg.sendToUser(irc, channel.opName, message);
	else
		this->_SendMsg.sendToAllUsersInChannel(irc, client, channel, message, false);
}
