/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 16:27:44 by plau              #+#    #+#             */
/*   Updated: 2024/01/05 20:33:13 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"
#include "BotClient.hpp"

int validport(char *port) {
	for (int i = 0; port[i]; i++) {
		if (!isdigit(port[i]))
			return (EXIT_FAILURE);
	}

	int	numport = atoi(port);
	return (numport < 1024 || numport > 65535);
}

int	main(int ac, char **av) {
	if (ac != 3) {
		std::cout << "Usage: " << av[0] << " <port> <password>" << std::endl;
		return (EXIT_FAILURE);
	}
	if (validport(av[1]) == EXIT_FAILURE) {
		std::cout << "Invalid port number" << std::endl;
		return (EXIT_FAILURE);
	}
	BotClient botClient = BotClient();
	botClient.createSocket();
	botClient.connectToServer(atoi(av[1]));
	botClient.sendClientDetails();
	botClient.closeSocket();
	return (0);
}
