/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BotClient.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 18:22:10 by plau              #+#    #+#             */
/*   Updated: 2024/01/09 14:28:52 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot/BotClient.hpp"

BotClient::BotClient() {
}

BotClient::~BotClient() {
}

int	BotClient::createSocket() {
	this->clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (this->clientSocket == -1) {
		std::cout << "Error: socket creation failed" << std::endl;
		return (EXIT_FAILURE);
	}
	return (this->clientSocket);
}

void	BotClient::connectToServer(int port) {
	sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(port);

	if (inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr) <= 0) {
		std::cout << "Error: invalid address" << std::endl;
		close(this->clientSocket);
		exit(EXIT_FAILURE);
	}
	if (connect(this->clientSocket, (sockaddr *)&serverAddress, sizeof(serverAddress)) < 0) {
		std::cout << "Error: connection failed" << std::endl;
		close(this->clientSocket);
		exit(EXIT_FAILURE);
	}
	std::cout << "Connected to server" << std::endl;
}

void	BotClient::closeSocket() {
	close(this->clientSocket);
}

void	BotClient::sendClientDetails() {
	const char*	commands[] = {
		"PASS 1234\r\n",
		"NICK Seen\r\n",
		"USER bot 0 * :bott\r\n",
		// "JOIN #test",
		// "PRIVMSG #test :Hello World!",
		// "QUIT :Bye!"
	};

	for (int i = 0; i < 3; i++) {
		ssize_t bytesSent = send(this->clientSocket, commands[i], strlen(commands[i]), 0);
		if (bytesSent == -1) {
			std::cerr << "Error: failed to send command" << std::endl;
		}
		else {
			std::cout << "Command sent to server: " << commands[i] << std::endl;
		}
	}
}
