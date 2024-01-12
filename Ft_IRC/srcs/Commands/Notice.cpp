/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Notice.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:29:40 by schuah            #+#    #+#             */
/*   Updated: 2024/01/12 19:20:05 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands/Notice.hpp"

Notice::Notice() {}

void	Notice::verifyTokens(t_irc& irc, Client& client, tokensVector& tokens) {
	if (tokens.size() == 1 || tokens[1].size() == 0)
		return;

	if (tokens.size() == 2 || tokens[2].size() == 0)
		return;

	this->_parseTokens(tokens);
	if (this->_destinations.size() == 0)
		return;

	for (size_t i = 0; i < this->_destinations.size(); i++) {
		try {
			this->_Utils.getClientByNickname(irc, this->_destinations[i]);
		} catch(Utils::NoClientFoundException& clientError) {
			try {
				Channel& channel = this->_Utils.getChannelByName(irc, this->_destinations[i]);
				if (channel.users.find(client.nickname) == channel.users.end())
					throw Utils::NoChannelFoundException();
			} catch(Utils::NoChannelFoundException& channelError) {
				return;
			}
		}
	}

	this->_executeCommand(irc, client);
}

void	Notice::_parseTokens(tokensVector& tokens) {
	std::string destinations = this->_Utils.extractFromToken(tokens[1]);
	this->_destinations = this->_Parser.parse(destinations, ",", false);
	if (this->_destinations.size() == 0)
		return;

	this->_message = this->_Utils.extractFromToken(tokens[2]);
	for (size_t i = 3; i < tokens.size(); i++)
		this->_message += " " + tokens[i];
}

void	Notice::_executeCommand(t_irc& irc, Client& client) {
	for (size_t i = 0; i < this->_destinations.size(); i++) {
		if (this->_destinations[i][0] == '#' || this->_destinations[i][0] == '@')
			this->_sendToChannel(irc, client, this->_destinations[i]);
		else {
			std::string	message = ":" + client.nickname + " NOTICE " + this->_destinations[i] + " :" + this->_message + "\r\n";
			this->_SendMsg.sendToUser(irc, this->_destinations[i], message);
		}
	}
}

void	Notice::_sendToChannel(t_irc& irc, Client& client, std::string channelName) {
	Channel&	channel = this->_Utils.getChannelByName(irc, channelName);
	std::string	message = ":" + client.nickname + " NOTICE " + channelName + " :" + this->_message + "\r\n";
	
	if (channelName[0] == '@')
		this->_SendMsg.sendToUser(irc, channel.opName, message);
	else
		this->_SendMsg.sendToAllUsersInChannel(irc, client, channel, message, false);
}
