/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:43:08 by schuah            #+#    #+#             */
/*   Updated: 2023/11/17 21:01:31 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(const char *port, const char *password) {
	this->_irc._port = atoi(port);
	this->_irc._password = password;
	
	this->create_socket();
	this->bind_socket();
	this->listen_socket();
}

void	Server::run() {
	std::vector<struct pollfd>&	fds = this->_irc._fds;
	std::map<int, Client>				clients = this->_irc._clients;
	int&												server_fd = this->_irc._server_fd;
	int&												port = this->_irc._port;

	while (true) {
		std::cout << YELLOW << "(" << port << ") Waiting for connection..." << RESET << std::endl;
		struct pollfd*	array_ptr = fds.data();

		int pollResult = poll(array_ptr, fds.size(), 60000);
		if (pollResult < 0)
			this->perror_exit("Poll failed");

		if (pollResult == 0)
			continue;

		for (unsigned long i = 0; i < fds.size(); i++) {
			if (fds[i].revents & POLLIN) {
				if (fds[i].fd == server_fd)
					this->_Receiver.new_connection(server_fd, fds, clients);
				else if (this->_Receiver.receive(clients, fds, i)) {
					std::vector<std::string> tokens = this->_Parser.parse(clients[fds[i].fd]._buffer);
					this->_Executor.execute(clients[fds[i].fd], tokens);
					fds[i].events = POLLIN;
				}
			}

			if (fds[i].revents & POLLOUT)
				this->_Responder.respond(clients[fds[i].fd], fds[i]);
		}
	}
}

void	Server::perror_exit(const char *error) {
	perror(error);
	exit(EXIT_FAILURE);
}

void	Server::create_socket() {
	int&	server_fd = this->_irc._server_fd;

	server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd < 0)
		this->perror_exit("Cannot create socket");

	int optval = 1;
	if (setsockopt(server_fd, SOL_SOCKET, SO_NOSIGPIPE, &optval, sizeof(optval)) == -1)
		this->perror_exit("Setsockopt failed");
}

void	Server::bind_socket() {
	addrinfo	hints, *res;
	int&			port = this->_irc._port;
	int&			server_fd = this->_irc._server_fd;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	if (getaddrinfo("localhost", std::to_string(port).c_str(), &hints, &res) != 0)
		this->perror_exit("Getaddrinfo failed");

	sockaddr_in serverAddress;
	memcpy(&serverAddress, res->ai_addr, res->ai_addrlen);
	serverAddress.sin_port = htons(port);

	if (bind(server_fd, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
		this->perror_exit("Bind failed");
}

void	Server::listen_socket() {
	int&												server_fd = this->_irc._server_fd;
	std::vector<struct pollfd>&	fds = this->_irc._fds;
	
	if (listen(server_fd, SOMAXCONN) < 0)
		this->perror_exit("Listen failed");

	struct pollfd new_fd;
	new_fd.fd = server_fd;
	new_fd.events = POLLIN;
	fds.push_back(new_fd);
}
