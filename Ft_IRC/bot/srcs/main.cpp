/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 16:27:44 by plau              #+#    #+#             */
/*   Updated: 2024/01/09 14:09:01 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"
#include "BotClient.hpp"

int	main(int ac, char **av) {
	if (ac != 3) {
		std::cout << "Usage: " << av[0] << " <port> <password>" << std::endl;
		return (EXIT_FAILURE);
	}

	Utils	utils;
	if (utils.checkValidPort(av[1]) == false) {
		std::cout << "Invalid port number" << std::endl;
		return (EXIT_FAILURE);
	}
	
	Bot bot = Bot(av[1], av[2]);
	bot.run();
	return (EXIT_SUCCESS);
}
