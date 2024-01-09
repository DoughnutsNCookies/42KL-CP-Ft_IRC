/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 18:48:21 by plau              #+#    #+#             */
/*   Updated: 2024/01/09 14:03:49 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_irc.hpp"

int main(int ac, char **av) {
	if (ac != 3) {
		std::cout << "Usage: " << av[0] << " <port> <password>" << std::endl;
		return (1);
	}

	Utils	utils;
	if (utils.checkValidPort(av[1]) == false) {
		std::cout << "Invalid port number" << std::endl;
		return (1);
	}

	Server server = Server(av[1], av[2]);
	server.run();
	return (0);
}
