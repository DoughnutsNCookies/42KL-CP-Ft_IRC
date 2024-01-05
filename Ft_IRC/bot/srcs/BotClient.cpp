/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BotClient.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 18:22:10 by plau              #+#    #+#             */
/*   Updated: 2024/01/05 18:58:01 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/BotClient.hpp"

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
