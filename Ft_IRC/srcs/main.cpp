/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 18:48:21 by plau              #+#    #+#             */
/*   Updated: 2023/11/16 13:54:06 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

typedef struct s_serverData
{
	std::string response;
	std::string message;
	struct pollfd fds[10];
} serverData;

int create_socket()
{
	int server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (server_fd < 0)
	{
		perror("cannot create socket");
		exit(EXIT_FAILURE);
	}

	int optval = 1;
	if (setsockopt(server_fd, SOL_SOCKET, SO_NOSIGPIPE, &optval, sizeof(optval)) == -1)
	{
		perror("Setsockopt");
		exit(EXIT_FAILURE);
	}
	return (server_fd);
}

void bind_socket(int server_fd, char *port)
{
	addrinfo hints, *res;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	if (getaddrinfo("localhost", port, &hints, &res) != 0)
	{
		perror("getaddrinfo failed");
		exit(EXIT_FAILURE);
	}

	sockaddr_in serverAddress;
	memcpy(&serverAddress, res->ai_addr, res->ai_addrlen);
	serverAddress.sin_port = htons(atoi(port));

	if (bind(server_fd, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
}

void listen_socket(int server_fd)
{
	if (listen(server_fd, 3) < 0)
	{
		perror("listen failed");
		exit(EXIT_FAILURE);
	}
}

void accept_connection(serverData &data, int server_fd)
{
	int clientSocket = accept(server_fd, NULL, NULL);
	if (clientSocket < 0)
	{
		perror("Accept failed");
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < 10; i++)
	{
		if (data.fds[i].fd == -1)
		{
			data.fds[i].fd = clientSocket;
			data.fds[i].events = POLLIN;
			break;
		}
	}
	printf("\033[32mConnection accepted\n\033[0m");
}

void receive(serverData &data, int i)
{
	char buffer[1024];
	bzero(buffer, 1024);
	recv(data.fds[i].fd, buffer, 1024, 0);
	if (buffer[0] == '\0')
	{
		printf("Client disconnected\n");
		close(data.fds[i].fd);
		data.fds[i].fd = -1;
		return;
	}

	std::string sbuffer = buffer;

	std::cout << CYAN << "Message received:" << std::endl;
	std::cout << sbuffer << RESET << std::endl;

	data.fds[i].events = POLLOUT;
}

void respond(serverData &data, int i)
{
	data.response.clear();
	data.response += ":ft_irc 001 schuah :Welcome to the IRC Network schuah!username@hostname\n";

	send(data.fds[i].fd, data.response.c_str(), data.response.length(), 0);
	std::cout << GREEN << "Message replied:\n"
			  << data.response << RESET << std::endl;

	data.fds[i].events = POLLIN;
}

int main(int ac, char **av)
{
	int server_fd;
	serverData data;

	Server server = Server(av[1]);
	server.run();
	return 0;

	if (ac != 3)
	{
		printf("Usage: %s <port> <password>\n", av[0]);
		return 1;
	}
	server_fd = create_socket();
	bind_socket(server_fd, av[1]);
	listen_socket(server_fd);

	memset(data.fds, -1, sizeof(data.fds));
	data.fds[0].fd = server_fd;
	data.fds[0].events = POLLIN;
	while (1)
	{
		std::cout << YELLOW << "(" << av[1] << ") Waiting for connection..." << RESET << std::endl;
		int pollResult = poll(data.fds, 10, 10000);
		if (pollResult < 0)
		{
			perror("Poll failed");
			exit(EXIT_FAILURE);
		}

		if (pollResult == 0)
			continue;

		for (int i = 0; i < 10; i++)
		{
			if (data.fds[i].revents & POLLIN)
			{
				if (data.fds[i].fd == server_fd)
					accept_connection(data, server_fd);
				else
					receive(data, i);
			}

			if (data.fds[i].revents & POLLOUT)
				respond(data, i);
		}
	}
}
