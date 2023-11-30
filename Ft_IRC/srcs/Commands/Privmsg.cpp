/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 13:50:29 by schuah            #+#    #+#             */
/*   Updated: 2023/11/30 20:21:31 by schuah           ###   ########.fr       */
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
			this->_getClientByNickname(irc, this->_destinations[i]);
		} catch(NoClientFoundException& e) {
			try {
				this->_getChannelByName(irc, client, this->_destinations[i]);
			} catch(NoChannelFoundException& e) {
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
	Client&	currentClient = this->_getClientByNickname(irc, nickname);
	currentClient.response += ":" + client.nickname + "!" + client.username + "@" + client.hostname + " PRIVMSG " + nickname + " :" + this->_message + "\r\n";
	struct pollfd&	pollfd = this->_getPollfdByFd(irc, currentClient.fd);
	pollfd.events = POLLOUT;
}

void	Privmsg::_sendToChannel(t_irc& irc, Client& client, std::string channelName) {
	Channel& channel = this->_getChannelByName(irc, client, channelName);
	std::map<std::string, Client>&	users = channel.users;
	for (std::map<std::string, Client>::iterator it = users.begin(); it != users.end(); ++it) {
		if (it->second.nickname == client.nickname)
			continue;
		Client&	currentClient = this->_getClientByNickname(irc, it->second.nickname);
		currentClient.response += ":" + client.nickname + "!" + client.username + "@" + client.hostname + " PRIVMSG " + channelName + " :" + this->_message + "\r\n";
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

Channel&	Privmsg::_getChannelByName(t_irc& irc, Client& client, std::string channelName) {
	for (std::map<std::string, Channel>::iterator it = irc.channels.begin(); it != irc.channels.end(); ++it) {
		if (it->second.name == channelName && it->second.users.find(client.nickname) != it->second.users.end())
			return (it->second);
	}
	throw Privmsg::NoChannelFoundException();
}

struct pollfd&	Privmsg::_getPollfdByFd(t_irc& irc, int fd) {
	for (size_t i = 0; i < irc.fds.size(); i++) {
		if (irc.fds[i].fd == fd)
			return (irc.fds[i]);
	}
	throw Privmsg::NoPollfdFoundException();
}

const char*	Privmsg::NoClientFoundException::what() const throw() {
	return ("No client found with this nickname");
}

const char*	Privmsg::NoChannelFoundException::what() const throw() {
	return ("No channel found with this name");
}

const char*	Privmsg::NoPollfdFoundException::what() const throw() {
	return ("No pollfd found with this fd");
}
