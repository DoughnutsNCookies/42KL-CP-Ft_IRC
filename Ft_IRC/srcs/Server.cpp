/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:43:08 by schuah            #+#    #+#             */
/*   Updated: 2023/11/21 22:17:00 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(const char *port, const char *password) {
	this->_irc._port = atoi(port);
	this->_irc._password = password;
	
	this->createSocket();
	this->bindSocket();
	this->listenSocket();
}

void	Server::run() {
	std::vector<struct pollfd>&	fds = this->_irc._fds;
	std::map<int, Client>&			clients = this->_irc._clients;
	int&												server_fd = this->_irc._serverFd;
	int&												port = this->_irc._port;

	while (true) {
		std::cout << YELLOW << "(" << port << ") Waiting for connection..." << RESET << std::endl;
		struct pollfd*	array_ptr = fds.data();

		int pollResult = poll(array_ptr, fds.size(), 60000);
		if (pollResult < 0)
			this->perrorExit("Poll failed");

		if (pollResult == 0)
			continue;

		for (unsigned long i = 0; i < fds.size(); i++) {
			if (fds[i].revents & POLLIN) {
				if (fds[i].fd == server_fd)
					this->_Receiver.new_connection(this->_irc);
				else {
					int	recvResult = this->_Receiver.receive(this->_irc, i);
					if (recvResult > 0) {
						std::vector<std::string> tokens = this->_Parser.parse(clients[fds[i].fd]._buffer);
						this->_Executor.execute(this->_irc, clients[fds[i].fd], tokens);
						fds[i].events = POLLOUT;
					} else if (recvResult < 0) {
						this->_Executor.disconnect(this->_irc, i);
						continue;
					}
				}
			}

			if (fds[i].revents & POLLOUT) {
				this->_Responder.respond(this->_irc, clients[fds[i].fd]);
				fds[i].events = POLLIN;
			}
		}
	}
}

void	Server::perrorExit(const char *error) {
	perror(error);
	exit(EXIT_FAILURE);
}

void	Server::createSocket() {
	int&	server_fd = this->_irc._serverFd;

	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd < 0)
		this->perrorExit("Cannot create socket");

	int optval = 1;
	if (setsockopt(server_fd, SOL_SOCKET, SO_NOSIGPIPE, &optval, sizeof(optval)) == -1)
		this->perrorExit("Setsockopt failed");
}

void	Server::bindSocket() {
	addrinfo	hints, *res;
	int&			port = this->_irc._port;
	int&			server_fd = this->_irc._serverFd;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	if (getaddrinfo("localhost", std::to_string(port).c_str(), &hints, &res) != 0)
		this->perrorExit("Getaddrinfo failed");

	sockaddr_in serverAddress;
	memcpy(&serverAddress, res->ai_addr, res->ai_addrlen);
	serverAddress.sin_port = htons(port);

	if (bind(server_fd, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
		this->perrorExit("Bind failed");
}

void	Server::listenSocket() {
	int&												server_fd = this->_irc._serverFd;
	std::vector<struct pollfd>&	fds = this->_irc._fds;
	
	if (listen(server_fd, SOMAXCONN) < 0)
		this->perrorExit("Listen failed");

	struct pollfd new_fd;
	new_fd.fd = server_fd;
	new_fd.events = POLLIN;
	fds.push_back(new_fd);
}
