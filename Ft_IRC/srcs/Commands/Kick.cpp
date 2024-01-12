/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 16:43:26 by schuah            #+#    #+#             */
/*   Updated: 2024/01/12 19:28:23 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands/Kick.hpp"

Kick::Kick() {}

void	Kick::verifyTokens(t_irc& irc, Client& client, tokensVector& tokens) {
	if (tokens.size() < 3 || tokens[1].size() == 0 || tokens[2].size() == 0) {
		this->_SendMsg.error461(irc, client, tokens[0]);
		return;
	}
	
	this->_parseTokens(tokens);
	if (this->_nicknames.size() == 0) {
		this->_SendMsg.error461(irc, client, tokens[0]);
		return;
	}

	Channel	channel;
	try {
		channel = this->_Utils.getChannelByName(irc, this->_channelName);
	} catch (Utils::NoChannelFoundException& e) {
		this->_SendMsg.error403(irc, client, this->_channelName);
		return;
	}

	if (channel.users.find(client.nickname) == channel.users.end()) {
		this->_SendMsg.error442(irc, client, this->_channelName);
		return;
	}

	if (channel.opName != client.nickname) {
		this->_SendMsg.error482(irc, client, this->_channelName);
		return;
	}

	for (size_t i = 0; i < this->_nicknames.size(); i++) {
		if (channel.users.find(this->_nicknames[i]) == channel.users.end()) {
			this->_SendMsg.error441(irc, client, this->_nicknames[i], this->_channelName);
			return;
		}
	}

	this->_executeCommand(irc, client);
}

void	Kick::_parseTokens(tokensVector& tokens) {
	this->_channelName = this->_Utils.extractFromToken(tokens[1]);
	if (this->_channelName[0] != '#')
		this->_channelName = "#" + this->_channelName;
	
	std::string	nicknames = this->_Utils.extractFromToken(tokens[2]);
	this->_nicknames = this->_Parser.parse(nicknames, ",", false);
	if (this->_nicknames.size() == 0)
		return;
	for (size_t i = 0; i < this->_nicknames.size(); i++) {
		if (this->_nicknames[i][0] != '#')
			this->_nicknames[i] = "#" + this->_nicknames[i];
	}

	this->_comment = "No commment given";
	if (tokens.size() > 3)
		this->_comment = this->_Utils.extractFromToken(tokens[3]);
	for (size_t i = 4; i < tokens.size(); i++)
		this->_comment += " " + tokens[i];
}

void	Kick::_executeCommand(t_irc& irc, Client& client) {
	(void)client;
	Channel&	channel = irc.channels[this->_channelName];

	for (size_t i = 0; i < this->_nicknames.size(); i++) {
		if (channel.users.find(this->_nicknames[i]) == channel.users.end())
			continue;
		channel.users.erase(this->_nicknames[i]);
		Client& user = this->_Utils.getClientByNickname(irc, this->_nicknames[i]);
		user.channels.erase(std::find(user.channels.begin(), user.channels.end(), this->_channelName));
		
		std::string	message = ":" + client.nickname + " KICK " + this->_channelName + " " + this->_nicknames[i] + " :" + this->_comment + "\r\n";
		this->_SendMsg.sendToAllUsersInChannel(irc, client, channel, message, true);
	}
}
