/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASocketServer.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:52:20 by schuah            #+#    #+#             */
/*   Updated: 2024/01/09 14:57:48 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server/ASocketServer.hpp"

void	ASocketServer::_perrorExit(const char *error) {
	std::cerr << error << std::endl;
	exit(EXIT_FAILURE);
}

void	ASocketServer::_createSocket() {
	int&	serverFd = this->_irc.serverFd;

	serverFd = socket(AF_INET, SOCK_STREAM, 0);
	if (serverFd < 0)
		this->_perrorExit("Cannot create socket");

	int optval = 1;
	if (setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1)
		this->_perrorExit("Setsockopt failed");
}
