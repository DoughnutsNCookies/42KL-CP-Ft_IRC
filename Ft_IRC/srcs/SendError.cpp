/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SendError.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:26:43 by plau              #+#    #+#             */
/*   Updated: 2023/11/22 20:02:33 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SendError.hpp"

SendError::SendError() {}

void	SendError::error421(Client& client, std::string unknownCommand) {
	client._response = "421 " +  client._nickname + " " + unknownCommand + " :Unknown command\r\n";
}

void	SendError::error431(Client& client) {
	client._response = "431 " +  client._nickname + " :No nickname given\r\n";
}

void	SendError::error432(Client& client) {
	client._response = "432 " +  client._nickname + " " + client._nickname + " :Erroneus nickname\r\n";
}

void	SendError::error433(Client& client) {
	client._response = "433 " +  client._nickname + " " + client._nickname + " :Nickname is already in use\r\n";
}

void	SendError::error451(Client& client) {
	client._response = "451 " +  client._nickname + " :You have not registered\r\n";
}

void	SendError::error461(Client& client) {
	client._response = "461 " +  client._nickname + " PASS :Not enough parameters\r\n";
}

void	SendError::error462(Client& client) {
	client._response = "462 " +  client._nickname + " :You may not reregister\r\n";
}

void	SendError::error464(Client& client) {
	client._response = "464 " +  client._nickname + " :Password incorrect\r\n";
}
