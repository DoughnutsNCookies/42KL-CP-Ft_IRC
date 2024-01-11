/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 20:46:39 by schuah            #+#    #+#             */
/*   Updated: 2024/01/11 21:34:48 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands/Invite.hpp"

Invite::Invite() {}

void	Invite::verifyTokens(t_irc& irc, Client& client, tokensVector& tokens) {
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

	if (channel.opName != client.nickname) {
		this->_SendMsg.error482(irc, client, this->_channelName);
		return ;
	}

	if (channel.users.find(this->_nickname) != channel.users.end()) {
		this->_SendMsg.error443(irc, client, this->_nickname, this->_channelName);
		return ;
	}

	this->_executeCommand(irc, client);
}

void	Invite::_parseTokens(tokensVector& tokens) {
	this->_nickname = this->_Utils.extractFromToken(tokens[1]);
	this->_channelName = this->_Utils.extractFromToken(tokens[2]);
	if (this->_channelName[0] != '#')
		this->_channelName = "#" + this->_channelName;
}

void	Invite::_executeCommand(t_irc& irc, Client& client) {
	this->_SendMsg.rpl341(irc, client, this->_nickname, this->_channelName);

	try {
		Client&		invitee = this->_Utils.getClientByNickname(irc, this->_nickname);
		std::string	message = ":" + client.nickname + " INVITE " + this->_nickname + " " + this->_channelName + "\r\n";
		this->_SendMsg.customMsg(irc, invitee, message);
	} catch (Utils::NoClientFoundException& e) {
		return ;
	}
}
