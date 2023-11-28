/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Responder.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 22:08:53 by schuah            #+#    #+#             */
/*   Updated: 2023/11/28 12:27:09 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server/Responder.hpp"

Responder::Responder() {}

void	Responder::respond(t_irc& irc, Client& client) {
	if (client._response.size() != 0)
		client._response = ":localhost:" + std::to_string(irc._port) + " " + client._response;

	send(client._fd, client._response.c_str(), client._response.length(), 0);
	std::cout << GREEN << "Message replied:\n" << client._response << RESET << std::endl;
	client._response.clear();
}
