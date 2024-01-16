/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 16:27:44 by plau              #+#    #+#             */
/*   Updated: 2024/01/16 19:04:41 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot/Bot.hpp"

int	main(int ac, char **av) {
	if (ac != 5) {
		std::cout << "Usage: " << av[0] << " <ipAddress> <port> <password> <targetNickname>" << std::endl;
		return (1);
	}

	Utils	utils;
	if (utils.checkValidPort(av[2]) == false) {
		std::cout << "Invalid port number" << std::endl;
		return (1);
	}
	
	Bot bot = Bot(av[1], av[2], av[3], av[4]);
	bot.run();
	return (0);
}
