/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 20:28:05 by schuah            #+#    #+#             */
/*   Updated: 2024/01/12 19:38:58 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Utils/Utils.hpp"

Utils::Utils() {}

void	Utils::setClientToPollOut(t_irc& irc, Client& client) {
	struct pollfd& pollfd = this->getPollfdByFd(irc, client.fd);
	pollfd.events = POLLOUT;
}

Client&	Utils::getClientByNickname(t_irc& irc, std::string nickname) {
	for (std::map<int, Client>::iterator it = irc.clients.begin(); it != irc.clients.end(); ++it) {
		if (it->second.nickname == nickname)
			return (it->second);
	}
	throw Utils::NoClientFoundException();
}

Channel&	Utils::getChannelByName(t_irc& irc, std::string channelName) {
	if (channelName[0] == '@')
		channelName.erase(0, 1);
	for (std::map<std::string, Channel>::iterator it = irc.channels.begin(); it != irc.channels.end(); ++it) {
		if (it->second.name == channelName)
			return (it->second);
	}
	throw Utils::NoChannelFoundException();
}

struct pollfd&	Utils::getPollfdByFd(t_irc& irc, int fd) {
	for (size_t i = 0; i < irc.fds.size(); i++) {
		if (irc.fds[i].fd == fd)
			return (irc.fds[i]);
	}
	throw Utils::NoPollfdFoundException();
}

std::string	Utils::extractFromToken(std::string token) {
	if (token[0] == ':')
		token.erase(0, 1);
	return (token);
}

bool	Utils::checkValidPort(char *port) {
	for (int i = 0; port[i]; i++) {
		if (!isdigit(port[i]))
			return (false);
	}

	int	numport = atoi(port);
	return (numport >= 1024 && numport <= 65535);
}

const char*	Utils::NoClientFoundException::what() const throw() {
	return ("No client found with this nickname");
}

const char*	Utils::NoChannelFoundException::what() const throw() {
	return ("No channel found with this name");
}

const char*	Utils::NoPollfdFoundException::what() const throw() {
	return ("No pollfd found with this fd");
}
