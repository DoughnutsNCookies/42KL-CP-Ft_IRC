/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:37:32 by schuah            #+#    #+#             */
/*   Updated: 2024/01/09 16:53:05 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot/Bot.hpp"

Bot::Bot(const char *hostname, const char *port, const char *password, const char *targetNickname) {
	this->_irc.port = atoi(port);
	this->_irc.password = password;
	this->_irc.version = "1.0";
	this->_irc.userModes = "";
	this->_irc.channelModes = "";
	this->_irc.channelModesWithParam = "";
	this->_irc.supportTokens = "";
	this->_irc.hostname = hostname;
	this->_target = targetNickname;

	this->_createSocket();
	this->_serverClient = Client(this->_irc.serverFd, this->_irc.hostname);
	
	this->_connectToServer();
}

void	Bot::run() {
	this->_register();
	while (true) {
		this->_sendPenguin("srcs/Bot/penguin.txt");
		sleep(5);
	}
}

void	Bot::_connectToServer() {
	sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(this->_irc.port);

	if (inet_pton(AF_INET, this->_irc.hostname.c_str(), &serverAddress.sin_addr) <= 0)
		this->_perrorExit("inet_pton failed");
	if (connect(this->_irc.serverFd, (sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
		this->_perrorExit("connect failed");

	std::cout << MAGENTA << "Connected to server on " << this->_irc.hostname << ":" << this->_irc.port << RESET << std::endl;
}

void	Bot::_register() {
	this->_serverClient.response = "PASS " + this->_irc.password + "\r\n";
	this->_serverClient.response += "NICK PengYun\r\n";
	this->_serverClient.response += "USER PengYun 0 * PengYun\r\n";
	this->_responder.respond(this->_irc, this->_serverClient);
}

void	Bot::_sendPenguin(std::string filePath) {
	std::ifstream	penguinFile(filePath);
	if (!penguinFile.is_open()) {
		this->_serverClient.response = "PRIVMSG " + this->_target + " :Cannot open Penguin file :c\r\n";
		this->_responder.respond(this->_irc, this->_serverClient);
		return;
	}

	std::string	line;
	while (std::getline(penguinFile, line)) {
		this->_serverClient.response = "PRIVMSG " + this->_target + " :" + line + "\r\n";
		this->_responder.respond(this->_irc, this->_serverClient);
	}

	penguinFile.close();
}
