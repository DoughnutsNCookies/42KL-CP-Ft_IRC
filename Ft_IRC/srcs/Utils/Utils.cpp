/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 20:28:05 by schuah            #+#    #+#             */
/*   Updated: 2023/11/30 20:42:28 by schuah           ###   ########.fr       */
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

Channel&	Utils::getChannelByName(t_irc& irc, Client& client, std::string channelName) {
	for (std::map<std::string, Channel>::iterator it = irc.channels.begin(); it != irc.channels.end(); ++it) {
		if (it->second.name == channelName && it->second.users.find(client.nickname) != it->second.users.end())
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

const char*	Utils::NoClientFoundException::what() const throw() {
	return ("No client found with this nickname");
}

const char*	Utils::NoChannelFoundException::what() const throw() {
	return ("No channel found with this name");
}

const char*	Utils::NoPollfdFoundException::what() const throw() {
	return ("No pollfd found with this fd");
}