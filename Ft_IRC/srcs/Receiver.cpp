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

#include "Receiver.hpp"

Receiver::Receiver() {}

void Receiver::new_connection(int server_fd, std::vector<struct pollfd> &fds, std::map<int, Client> &clients) {
	int clientSocket = accept(server_fd, NULL, NULL);
	if (clientSocket < 0)
		this->perror_exit("Accept failed");

	struct pollfd new_pollfd;
	new_pollfd.fd = clientSocket;
	new_pollfd.events = POLLIN;
	fds.push_back(new_pollfd);

	clients[clientSocket] = Client(clientSocket);
	std::cout << GREEN << "New connection accepted!" << RESET << std::endl;
}

int	Receiver::receive(std::map<int, Client> &clients, std::vector<struct pollfd> &fds, int i) {
	char buffer[1024];
	bzero(buffer, 1024);

	recv(fds[i].fd, buffer, 1024, 0);
	if (buffer[0] == '\0') {
		std::cout << RED << "Client disconnected" << RESET << std::endl;
		close(fds[i].fd);
		fds.erase(fds.begin() + i);
		clients.erase(fds[i].fd);
		return (0);
	}

	Client&	thisClient = clients[fds[i].fd];
	if (thisClient._buffer.find("\r\n") != std::string::npos)
		thisClient._buffer.clear();

	thisClient._buffer += buffer;
	std::cout << CYAN << "Message received:" << std::endl;
	std::cout << thisClient._buffer << RESET << std::endl;
	std::cout << thisClient._buffer.size() << std::endl;

	return (thisClient._buffer.find("\r\n") != std::string::npos);
}

void Receiver::perror_exit(const char *error) {
	perror(error);
	exit(EXIT_FAILURE);
}
