/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 18:39:00 by schuah            #+#    #+#             */
/*   Updated: 2024/01/16 18:23:09 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands/Quit.hpp"

Quit::Quit() {}

void	Quit::verifyTokens(t_irc& irc, Client& client, tokensVector& tokens) {
	this->_parseTokens(tokens);
	this->_executeCommand(irc, client);
}

void	Quit::disconnectClient(t_irc& irc, int fd) {
	std::cout << "Died5" << std::endl;
	this->_Responder.respond(irc, irc.clients[fd]);
	std::cout << "Died6" << std::endl;
	this->_sendAllClientQuitMessage(irc, irc.clients[fd]);
	std::vector<struct pollfd>&	fds = irc.fds;
	std::map<int, Client>&		clients = irc.clients;
	
	std::map<std::string, Channel>	&channels = irc.channels;
	tokensVector					channelsJoined = clients[fd].channels;
	for (size_t i = 0; i < channelsJoined.size(); i++)
		this->_Part.leaveChannel(irc, clients[fd], channels[channelsJoined[i]]);
	
	std::cout << RED << "Client " << clients[fd].nickname << " Disconnected" << RESET << std::endl;
	
	close(fd);
	for (size_t i = 0; i < fds.size(); i++) {
		if (fds[i].fd != fd)
			continue;
		fds.erase(fds.begin() + i);
	}
	clients.erase(fd);
}

void	Quit::_parseTokens(tokensVector& tokens) {
	this->_quitMessage = "";
	if (tokens.size() > 1)
		this->_quitMessage = this->_Utils.extractFromToken(tokens[1]);
	for (size_t i = 2; i < tokens.size(); i++)
		this->_quitMessage += " " + tokens[i];
}

void	Quit::_executeCommand(t_irc& irc, Client& client) {
	this->_SendMsg.customMsg(irc, client, "ERROR :Disconnected using QUIT\r\n");
	this->disconnectClient(irc, client.fd);
}

void	Quit::_sendAllClientQuitMessage(t_irc& irc, Client& client) {
	tokensVector&	channels = client.channels;
	for (size_t i = 0; i < channels.size(); i++) {
		Channel&	channel = irc.channels[channels[i]];
		std::string	message = ":" + client.nickname + " QUIT :" + this->_quitMessage + "\r\n";
		this->_SendMsg.sendToAllUsersInChannel(irc, client, channel, message, false);
	}
}
