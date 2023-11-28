/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 13:50:29 by schuah            #+#    #+#             */
/*   Updated: 2023/11/28 20:41:24 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands/Privmsg.hpp"

Privmsg::Privmsg() {}

void	Privmsg::verifyTokens(t_irc& irc, Client& client, tokensVector& tokens) {
	if (tokens.size() == 1 || tokens[1].size() == 0) {
		this->_SendError.error411(irc, client, tokens[0]);
		return;
	}
	if (tokens.size() == 2 || tokens[2].size() == 0) {
		this->_SendError.error412(irc, client);
		return;
	}

	this->_parseTokens(tokens);
	for (size_t i = 0; i < this->_nicknames.size(); i++) {
		try {
			this->_getClientByNickname(irc, this->_nicknames[i]);
		} catch(NoClientFoundException& e) {
			this->_SendError.error401(irc, client, this->_nicknames[i]);
			return;
		}
	}
	this->_executeCommand(irc, client);
}

void	Privmsg::_parseTokens(tokensVector& tokens) {
	std::string nicknames = tokens[1];
	if (nicknames[0] == ':')
		nicknames.erase(0, 1);
	this->_nicknames = this->_Parser.parse(nicknames, ",");
	this->_nicknames.erase(this->_nicknames.end() - 1);

	this->_message = tokens[2];
	size_t	tokensSize = tokens.size();
	for (size_t i = 3; i < tokensSize; i++)
		this->_message += " " + tokens[i];
	if (this->_message[0] == ':')
		this->_message.erase(0, 1);
}

void	Privmsg::_executeCommand(t_irc& irc, Client& client) {
	for (size_t i = 0; i < this->_nicknames.size(); i++) {
		Client&	currentClient = this->_getClientByNickname(irc, this->_nicknames[i]);
		currentClient.response += ":" + client.nickname + "!" + client.username + "@" + client.hostname + " PRIVMSG " + this->_nicknames[i] + " :" + this->_message + "\r\n";
		struct pollfd&	pollfd = this->_getPollfdByFd(irc, currentClient.fd);
		pollfd.events = POLLOUT;
	}
}

Client&	Privmsg::_getClientByNickname(t_irc& irc, std::string nickname) {
	for (std::map<int, Client>::iterator it = irc.clients.begin(); it != irc.clients.end(); ++it) {
		if (it->second.nickname == nickname)
			return (it->second);
	}
	throw Privmsg::NoClientFoundException();
}

struct pollfd&	Privmsg::_getPollfdByFd(t_irc& irc, int fd) {
	for (size_t i = 0; i < irc.fds.size(); i++) {
		if (irc.fds[i].fd == fd)
			return (irc.fds[i]);
	}
	throw Privmsg::NoPollfdFoundException();
}
