/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 13:50:29 by schuah            #+#    #+#             */
/*   Updated: 2023/11/30 20:40:43 by schuah           ###   ########.fr       */
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
		} catch(Utils::NoClientFoundException& e) {
			try {
				this->_Utils.getChannelByName(irc, client, this->_destinations[i]);
			} catch(Utils::NoChannelFoundException& e) {
				this->_SendMsg.error401(irc, client, this->_destinations[i]);
				return;
			}
		}
	}
	this->_executeCommand(irc, client);
}

void	Privmsg::_parseTokens(tokensVector& tokens) {
	std::string nicknames = tokens[1];
	if (nicknames[0] == ':')
		nicknames.erase(0, 1);
	this->_destinations = this->_Parser.parse(nicknames, ",");
	if (this->_destinations.size() == 0)
		return;
	this->_destinations.erase(this->_destinations.end() - 1);

	this->_message = tokens[2];
	size_t	tokensSize = tokens.size();
	for (size_t i = 3; i < tokensSize; i++)
		this->_message += " " + tokens[i];
	if (this->_message[0] == ':')
		this->_message.erase(0, 1);
}

void	Privmsg::_executeCommand(t_irc& irc, Client& client) {
	for (size_t i = 0; i < this->_destinations.size(); i++) {
		if (this->_destinations[i][0] == '#')
			this->_sendToChannel(irc, client, this->_destinations[i]);
		else
			this->_sendToUser(irc, client, this->_destinations[i]);
	}
}

void	Privmsg::_sendToUser(t_irc& irc, Client& client, std::string nickname) {
	Client&	currentClient = this->_Utils.getClientByNickname(irc, nickname);
	currentClient.response += ":" + client.nickname + "!" + client.username + "@" + client.hostname + " PRIVMSG " + nickname + " :" + this->_message + "\r\n";
	this->_Utils.setClientToPollOut(irc, currentClient);
}

void	Privmsg::_sendToChannel(t_irc& irc, Client& client, std::string channelName) {
	Channel& channel = this->_Utils.getChannelByName(irc, client, channelName);
	std::map<std::string, Client>&	users = channel.users;
	for (std::map<std::string, Client>::iterator it = users.begin(); it != users.end(); ++it) {
		if (it->second.nickname == client.nickname)
			continue;
		Client&	currentClient = this->_Utils.getClientByNickname(irc, it->second.nickname);
		currentClient.response += ":" + client.nickname + "!" + client.username + "@" + client.hostname + " PRIVMSG " + channelName + " :" + this->_message + "\r\n";
		this->_Utils.setClientToPollOut(irc, currentClient);
	}
}
