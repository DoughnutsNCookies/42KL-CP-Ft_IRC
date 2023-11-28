/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 18:48:21 by plau              #+#    #+#             */
/*   Updated: 2023/11/28 18:10:32 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

int validport(char *port) {
	for (int i = 0; port[i]; i++) {
		if (!isdigit(port[i]))
			return (EXIT_FAILURE);
	}

	int	numport = atoi(port);
	return (numport < 1024 || numport > 65535);
}

int main(int ac, char **av) {
	if (ac != 3) {
		std::cout << "Usage: " << av[0] << " <port> <password>" << std::endl;
		return (EXIT_FAILURE);
	}

	if (validport(av[1]) == EXIT_FAILURE) {
		std::cout << "Invalid port number" << std::endl;
		return (EXIT_FAILURE);
	}

	Server server = Server(av[1], av[2]);
	server.run();
	return (EXIT_SUCCESS);
}
