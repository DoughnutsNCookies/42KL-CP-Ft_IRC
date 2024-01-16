/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Responder.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 22:08:53 by schuah            #+#    #+#             */
/*   Updated: 2024/01/16 21:41:03 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server/Responder.hpp"

Responder::Responder() {}

void	Responder::respond(t_irc& irc, Client& client) {
	(void)irc;
	if (!client.bypassCheck && !client.joined)
		std::cout << RED << "Client not registered yet" << RESET << std::endl;
	else {
		send(client.fd, client.response.c_str(), client.response.length(), 0);
		std::cout << GREEN << "Message Replied:\n" << client.response << RESET << std::endl;
	}
	client.bypassCheck = false;
	client.response.clear();
}
