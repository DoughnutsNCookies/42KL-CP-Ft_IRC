/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:43:08 by schuah            #+#    #+#             */
/*   Updated: 2024/01/09 13:56:08 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server/Server.hpp"

Server::Server(const char *port, const char *password) {
	this->_irc.port = atoi(port);
	this->_irc.password = password;
	this->_irc.version = "1.0";
	this->_irc.userModes = "io";
	this->_irc.channelModes = "kost";
	this->_irc.channelModesWithParam = "k";
	this->_irc.supportTokens = "";
	
	this->_createSocket();
	this->_bindSocket();
	this->_listenSocket();
}

void	Server::run() {
	std::vector<struct pollfd>&	fds = this->_irc.fds;
	std::map<int, Client>&		clients = this->_irc.clients;
	int&						serverFd = this->_irc.serverFd;
	int&						port = this->_irc.port;

	while (true) {
		std::cout << YELLOW << "(" << port << ") [" << fds.size() - 1 << " Clients Connected] Waiting For Connection..." << RESET << std::endl;
		struct pollfd*	array_ptr = fds.data();

		int pollResult = poll(array_ptr, fds.size(), 60000);
		if (pollResult < 0)
			this->_perrorExit("Poll failed");

		if (pollResult == 0)
			continue;

		for (unsigned long i = 0; i < fds.size(); i++) {
			if (fds[i].revents & POLLIN) {
				if (fds[i].fd == serverFd)
					this->_Receiver.new_connection(this->_irc);
				else {
					int	recvResult = this->_Receiver.receive(this->_irc, i);
					if (recvResult > 0) {
						tokensVector	tokens = this->_Parser.parse(clients[fds[i].fd].buffer, " \r\n");
						this->_Executor.execute(this->_irc, clients[fds[i].fd], tokens);
					} else if (recvResult < 0) {
						this->_Quit.disconnectClient(this->_irc, fds[i].fd);
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

void	Server::_perrorExit(const char *error) {
	perror(error);
	exit(1);
}

void	Server::_createSocket() {
	int&	serverFd = this->_irc.serverFd;

	serverFd = socket(AF_INET, SOCK_STREAM, 0);
	if (serverFd < 0)
		this->_perrorExit("Cannot create socket");

	int optval = 1;
	if (setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1)
		this->_perrorExit("Setsockopt failed");
}

void	Server::_bindSocket() {
	addrinfo	hints, *res;
	int&		port = this->_irc.port;
	int&		serverFd = this->_irc.serverFd;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	std::ostringstream stream;
	stream << port;
	std::string numStr = stream.str();
	if (getaddrinfo("localhost", numStr.c_str(), &hints, &res) != 0)
		this->_perrorExit("Getaddrinfo failed");

	sockaddr_in serverAddress;
	memcpy(&serverAddress, res->ai_addr, res->ai_addrlen);
	serverAddress.sin_port = htons(port);

	if (bind(serverFd, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
		this->_perrorExit("Bind failed");

	struct sockaddr_in clientAddr;
	socklen_t clientAddrSize = sizeof(clientAddr);
	if (getsockname(serverFd, (struct sockaddr *)&clientAddr, &clientAddrSize) < 0)
		this->_perrorExit("getsockname failed");

	struct hostent*	host = gethostbyaddr((const char *)&clientAddr.sin_addr.s_addr, sizeof(clientAddr.sin_addr.s_addr), AF_INET);
	if (host == NULL) {
		close(serverFd);
		this->_perrorExit("gethostbyaddr failed");
	}
	
	this->_irc.hostname = host->h_name;
	std::cout << MAGENTA << "Server started on " << host->h_name << ":" << port << RESET << std::endl;
}

void	Server::_listenSocket() {
	int&						serverFd = this->_irc.serverFd;
	std::vector<struct pollfd>&	fds = this->_irc.fds;
	
	if (listen(serverFd, SOMAXCONN) < 0)
		this->_perrorExit("Listen failed");

	struct pollfd newfd;
	newfd.fd = serverFd;
	newfd.events = POLLIN;
	fds.push_back(newfd);
}
