/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SendError.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:26:43 by plau              #+#    #+#             */
/*   Updated: 2023/11/28 18:10:32 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Utils/SendError.hpp"

SendError::SendError() {}

void	SendError::error401(t_irc& irc, Client& client, std::string nickname) {
	client.response = this->header(irc, client) + " 401 " +  client.nickname + " " + nickname + " :No such nick/channel\r\n";
}

void	SendError::error411(t_irc& irc, Client& client, std::string command) {
	client.response = this->header(irc, client) + " 411 " +  client.nickname + " :No recipient given (" + command + ")\r\n";
}

void	SendError::error412(t_irc& irc, Client& client) {
	client.response = this->header(irc, client) + " 412 " +  client.nickname + " :No text to send\r\n";
}

void	SendError::error421(t_irc& irc, Client& client, std::string unknownCommand) {
	client.response = this->header(irc, client) + " 421 " +  client.nickname + " " + unknownCommand + " :Unknown command\r\n";
}

void	SendError::error431(t_irc& irc, Client& client) {
	client.response = this->header(irc, client) + " 431 " +  client.nickname + " :No nickname given\r\n";
}

void	SendError::error432(t_irc& irc, Client& client, std::string nickname) {
	client.response = this->header(irc, client) + " 432 " +  client.nickname + " " + nickname + " :Erroneus nickname\r\n";
}

void	SendError::error433(t_irc& irc, Client& client, std::string nickname) {
	client.response = this->header(irc, client) + " 433 " +  client.nickname + " " + nickname + " :Nickname is already in use\r\n";
}

void	SendError::error451(t_irc& irc, Client& client) {
	client.response = this->header(irc, client) + " 451 " +  client.nickname + " :You have not registered\r\n";
}

void	SendError::error461(t_irc& irc, Client& client) {
	client.response = this->header(irc, client) + " 461 " +  client.nickname + " PASS :Not enough parameters\r\n";
}

void	SendError::error462(t_irc& irc, Client& client) {
	client.response = this->header(irc, client) + " 462 " +  client.nickname + " :You may not reregister\r\n";
}

void	SendError::error464(t_irc& irc, Client& client) {
	client.response = this->header(irc, client) + " 464 " +  client.nickname + " :Password incorrect\r\n";
}

std::string	SendError::header(t_irc& irc, Client& client) {
	return (":" + irc.hostname + ":" + std::to_string(irc.port) + " " + client.nickname + " ");
}
