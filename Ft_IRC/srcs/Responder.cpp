/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Responder.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 22:08:53 by schuah            #+#    #+#             */
/*   Updated: 2023/11/21 18:25:22 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Responder.hpp"

Responder::Responder() {}

void	Responder::respond(Client client) {
	send(client._fd, client._response.c_str(), client._response.length(), 0);
	std::cout << GREEN << "Message replied:\n" << client._response << RESET << std::endl;
}
