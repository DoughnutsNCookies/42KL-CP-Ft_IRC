/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Responder.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 22:08:53 by schuah            #+#    #+#             */
/*   Updated: 2023/11/17 18:07:14 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Responder.hpp"

Responder::Responder() {}

void	Responder::respond(Client client, struct pollfd& pollfd) {
	client._response.clear();
	client._response += ":ft_irc 001 schuah :Welcome to the IRC Network schuah!username@hostname\n";

	send(client._fd, client._response.c_str(), client._response.length(), 0);
	std::cout << GREEN << "Message replied:\n" << client._response << RESET << std::endl;

	pollfd.events = POLLIN;
}
