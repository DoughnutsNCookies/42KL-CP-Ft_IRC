/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:49:16 by plau              #+#    #+#             */
/*   Updated: 2024/01/10 17:28:07 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands/Nick.hpp"

Nick::Nick() {}

void	Nick::verifyTokens(t_irc& irc, Client& client, tokensVector& tokens) {
	if (tokens.size() == 1 || tokens[1].size() == 0) {
		this->_SendMsg.error431(irc, client);
		return;
	}

	if (tokens.size() > 2) {
		this->_SendMsg.error432(irc, client, tokens[1]);
		return;
	}

	this->_parseTokens(tokens);
	if (this->_checkValidNickName(this->_nickname) == false) {
		this->_SendMsg.error432(irc, client, this->_nickname);
		return;
	}

	for (std::map<int, Client>::iterator it = irc.clients.begin(); it != irc.clients.end(); ++it) {
		if (it->second.nickname == this->_nickname) {
			this->_SendMsg.error433(irc, client, this->_nickname);
			return;
		}
	}

	this->_executeCommand(irc, client);
}

void	Nick::_parseTokens(tokensVector& tokens) {
	this->_nickname = this->_Utils.extractFromToken(tokens[1]);
}

void	Nick::_executeCommand(t_irc& irc, Client& client) {
	tokensVector&	channelList = client.channels;
	std::string		oldNickname = client.nickname;
	std::string		message = ":" + oldNickname + " NICK " + this->_nickname + "\r\n";
	client.nickname = this->_nickname;

	for (tokensVector::iterator it = channelList.begin(); it != channelList.end(); ++it) {
		Channel&	channel = irc.channels[*it];
		channel.users.erase(oldNickname);
		channel.users.insert(std::pair<std::string, Client>(this->_nickname, client));
		
		if (channel.opName == oldNickname)
			channel.opName = this->_nickname;
		this->_SendMsg.sendToAllUsersInChannel(irc, client, channel, message, false);
	}

	client.nickSet = true;
	this->_SendMsg.customMsg(irc, client, message);
	this->_SendMsg.registeredMsg(irc, client);
}

bool	Nick::_checkValidNickName(std::string nickname) {
	std::string	invalid = "#: ";

	return (!(invalid.find(nickname[0]) != std::string::npos
		|| (nickname[0] == '&' && nickname[1] == '#')));
}
