/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 18:48:21 by plau              #+#    #+#             */
/*   Updated: 2023/11/17 16:53:17 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

int valid_port(char *port) {
	for (int i = 0; port[i]; i++) {
		if (!isdigit(port[i]))
			return (EXIT_FAILURE);
	}

	int	num_port = atoi(port);
	return (num_port < 1024 || num_port > 65535);
}

int main(int ac, char **av) {
	if (ac != 3) {
		std::cout << "Usage: " << av[0] << " <port> <password>" << std::endl;
		return (EXIT_FAILURE);
	}

	if (valid_port(av[1]) == EXIT_FAILURE) {
		std::cout << "Invalid port number" << std::endl;
		return (EXIT_FAILURE);
	}

	Server server = Server(av[1], av[2]);
	server.run();
	return (EXIT_SUCCESS);
}
