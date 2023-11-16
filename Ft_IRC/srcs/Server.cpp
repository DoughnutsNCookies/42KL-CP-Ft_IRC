/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:43:08 by schuah            #+#    #+#             */
/*   Updated: 2023/11/16 14:21:08 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(const char *port): _port(atoi(port)) {
	create_socket();
	bind_socket();
}

Server::~Server() {
	
}

void	Server::run() {
	
}

void	Server::perror_exit(const char *error) {
	perror(error);
	exit(EXIT_FAILURE);
}

void	Server::create_socket() {
	this->_server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (this->_server_fd < 0)
		this->perror_exit("Cannot create socket");

	int optval = 1;
	if (setsockopt(this->_server_fd, SOL_SOCKET, SO_NOSIGPIPE, &optval, sizeof(optval)) == -1)
		this->perror_exit("Setsockopt failed");
}

void	Server::bind_socket() {
	addrinfo hints, *res;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	if (getaddrinfo("localhost", std::to_string(this->_port).c_str(), &hints, &res) != 0)
		this->perror_exit("Getaddrinfo failed");

	sockaddr_in serverAddress;
	memcpy(&serverAddress, res->ai_addr, res->ai_addrlen);
	serverAddress.sin_port = htons(this->_port);

	if (bind(this->_server_fd, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
		this->perror_exit("Bind failed");
}

void	Server::listen_socket() {
	if (listen(this->_server_fd, 10) < 0)
		this->perror_exit("Listen failed");

	struct pollfd new_fd;
	new_fd.fd = this->_server_fd;
	new_fd.events = POLLIN;
	this->_fds.push_back(new_fd);
}
