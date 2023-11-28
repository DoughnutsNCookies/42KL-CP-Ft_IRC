/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Receiver.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 20:43:48 by schuah            #+#    #+#             */
/*   Updated: 2023/11/16 21:45:14 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server/Receiver.hpp"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>

Receiver::Receiver() {}

void Receiver::new_connection(t_irc& irc) {
	std::vector<struct pollfd>&	fds = irc.fds;
	std::map<int, Client>&			clients = irc.clients;
	int&												serverFd = irc.serverFd;	

	int clientSocket = accept(serverFd, NULL, NULL);
	if (clientSocket < 0) {
		std::cout << "accept failed" << std::endl;
		perror("accept");
	}

	struct pollfd new_pollfd;
	new_pollfd.fd = clientSocket;
	new_pollfd.events = POLLIN;
	fds.push_back(new_pollfd);

	std::cout << GREEN << "New connection accepted!" << RESET << std::endl;

	struct sockaddr_in clientAddr;
	socklen_t clientAddrSize = sizeof(clientAddr);
	if (getsockname(clientSocket, (struct sockaddr *)&clientAddr, &clientAddrSize) < 0) {
		std::cout << "getsockname failed" << std::endl;
		perror("getsockname");
	}

	struct hostent*	host = gethostbyaddr((const char *)&clientAddr.sin_addr.s_addr, sizeof(clientAddr.sin_addr.s_addr), AF_INET);
	clients[clientSocket] = Client(clientSocket, host->h_name);
}

int	Receiver::receive(t_irc& irc, int i) {
	std::vector<struct pollfd>&	fds = irc.fds;
	std::map<int, Client>&			clients = irc.clients;
	int&												pollfd = fds[i].fd;

	char buffer[1024];
	bzero(buffer, 1024);

	recv(pollfd, buffer, 1024, 0);
	if (buffer[0] == '\0')
		return (-1);

	Client&	thisClient = clients[pollfd];
	if (thisClient.buffer.find("\r\n") != std::string::npos)
		thisClient.buffer.clear();

	thisClient.buffer += std::string(buffer);
	std::cout << CYAN << "Message received:" << std::endl;
	std::cout << thisClient.buffer << RESET << std::endl;
	return (thisClient.buffer.find("\r\n") != std::string::npos);
}
