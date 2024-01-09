/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 16:27:44 by plau              #+#    #+#             */
/*   Updated: 2024/01/09 16:18:58 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot/Bot.hpp"

int	main(int ac, char **av) {
	if (ac != 5) {
		std::cout << "Usage: " << av[0] << "<ipAddress> <port> <password> <targetNickname>" << std::endl;
		return (EXIT_FAILURE);
	}

	Utils	utils;
	if (utils.checkValidPort(av[2]) == false) {
		std::cout << "Invalid port number" << std::endl;
		return (EXIT_FAILURE);
	}
	
	Bot bot = Bot(av[1], av[2], av[3], av[4]);
	bot.run();
	return (EXIT_SUCCESS);
}
