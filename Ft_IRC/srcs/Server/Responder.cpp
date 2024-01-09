/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Responder.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 22:08:53 by schuah            #+#    #+#             */
/*   Updated: 2024/01/09 16:45:15 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server/Responder.hpp"

Responder::Responder() {}

void	Responder::respond(t_irc& irc, Client& client) {
	(void)irc;
	std::cout << client.response.c_str() << std::endl;
	send(client.fd, client.response.c_str(), client.response.length(), 0);
	std::cout << GREEN << "Message Replied:\n" << client.response << RESET << std::endl;
	client.response.clear();
}
