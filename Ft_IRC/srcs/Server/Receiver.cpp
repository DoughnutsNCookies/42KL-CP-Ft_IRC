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

Receiver::Receiver() {}

void Receiver::new_connection(t_irc& irc) {
	std::vector<struct pollfd>&	fds = irc._fds;
	std::map<int, Client>&			clients = irc._clients;
	int&												server_fd = irc._serverFd;	

	int clientSocket = accept(server_fd, NULL, NULL);
	if (clientSocket < 0)
		this->perrorExit("Accept failed");

	struct pollfd new_pollfd;
	new_pollfd.fd = clientSocket;
	new_pollfd.events = POLLIN;
	fds.push_back(new_pollfd);

	clients[clientSocket] = Client(clientSocket);
	std::cout << GREEN << "New connection accepted!" << RESET << std::endl;
}

int	Receiver::receive(t_irc& irc, int i) {
	std::vector<struct pollfd>&	fds = irc._fds;
	std::map<int, Client>&			clients = irc._clients;
	int&												pollfd = fds[i].fd;

	char buffer[1024];
	bzero(buffer, 1024);

	recv(pollfd, buffer, 1024, 0);
	if (buffer[0] == '\0')
		return (-1);

	Client&	thisClient = clients[pollfd];
	if (thisClient._buffer.find("\r\n") != std::string::npos)
		thisClient._buffer.clear();

	thisClient._buffer += std::string(buffer);
	std::cout << CYAN << "Message received:" << std::endl;
	std::cout << thisClient._buffer << RESET << std::endl;
	return (thisClient._buffer.find("\r\n") != std::string::npos);
}

void Receiver::perrorExit(const char *error) {
	perror(error);
	exit(EXIT_FAILURE);
}
