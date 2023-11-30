/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SendMsg.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:26:43 by plau              #+#    #+#             */
/*   Updated: 2023/11/28 20:49:56 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Utils/SendMsg.hpp"

SendMsg::SendMsg() {}

void	SendMsg::rpl332(t_irc& irc, Client& client, Channel channel) {
	client.response += this->_header(irc, client) + " 332 " +  client.nickname + " " + channel.name + " :" + channel.topic + "\r\n";
	this->_Utils.setClientToPollOut(irc, client);
}

void	SendMsg::rpl353(t_irc& irc, Client& client, Channel channel) {
	std::string users = "";
	for (std::map<std::string, Client>::iterator it = channel.users.begin(); it != channel.users.end(); it++) {
		users += it->second.nickname + " ";
	}
	client.response += this->_header(irc, client) + " 353 " +  client.nickname + " = " + channel.name + " :" + users + "\r\n";
	this->_Utils.setClientToPollOut(irc, client);
}

void	SendMsg::rpl366(t_irc& irc, Client& client, Channel channel) {
	client.response += this->_header(irc, client) + " 366 " +  client.nickname + " " + channel.name + " :End of /NAMES list\r\n";
	this->_Utils.setClientToPollOut(irc, client);
}

void	SendMsg::error401(t_irc& irc, Client& client, std::string nickname) {
	client.response += this->_header(irc, client) + " 401 " +  client.nickname + " " + nickname + " :No such nick/channel\r\n";
	this->_Utils.setClientToPollOut(irc, client);
}

void	SendMsg::error411(t_irc& irc, Client& client, std::string command) {
	client.response += this->_header(irc, client) + " 411 " +  client.nickname + " :No recipient given (" + command + ")\r\n";
	this->_Utils.setClientToPollOut(irc, client);
}

void	SendMsg::error412(t_irc& irc, Client& client) {
	client.response += this->_header(irc, client) + " 412 " +  client.nickname + " :No text to send\r\n";
	this->_Utils.setClientToPollOut(irc, client);
}

void	SendMsg::error421(t_irc& irc, Client& client, std::string unknownCommand) {
	client.response += this->_header(irc, client) + " 421 " +  client.nickname + " " + unknownCommand + " :Unknown command\r\n";
	this->_Utils.setClientToPollOut(irc, client);
}

void	SendMsg::error431(t_irc& irc, Client& client) {
	client.response += this->_header(irc, client) + " 431 " +  client.nickname + " :No nickname given\r\n";
	this->_Utils.setClientToPollOut(irc, client);
}

void	SendMsg::error432(t_irc& irc, Client& client, std::string nickname) {
	client.response += this->_header(irc, client) + " 432 " +  client.nickname + " " + nickname + " :Erroneus nickname\r\n";
	this->_Utils.setClientToPollOut(irc, client);
}

void	SendMsg::error433(t_irc& irc, Client& client, std::string nickname) {
	client.response += this->_header(irc, client) + " 433 " +  client.nickname + " " + nickname + " :Nickname is already in use\r\n";
	this->_Utils.setClientToPollOut(irc, client);
}

void	SendMsg::error451(t_irc& irc, Client& client) {
	client.response += this->_header(irc, client) + " 451 " +  client.nickname + " :You have not registered\r\n";
	this->_Utils.setClientToPollOut(irc, client);
}

void	SendMsg::error461(t_irc& irc, Client& client, std::string command) {
	client.response += this->_header(irc, client) + " 461 " +  client.nickname + " " + command + " :Not enough parameters\r\n";
	this->_Utils.setClientToPollOut(irc, client);
}

void	SendMsg::error462(t_irc& irc, Client& client) {
	client.response += this->_header(irc, client) + " 462 " +  client.nickname + " :You may not reregister\r\n";
	this->_Utils.setClientToPollOut(irc, client);
}

void	SendMsg::error464(t_irc& irc, Client& client) {
	client.response += this->_header(irc, client) + " 464 " +  client.nickname + " :Password incorrect\r\n";
	this->_Utils.setClientToPollOut(irc, client);
}

void	SendMsg::customMsg(t_irc& irc, Client& client, std::string message) {
	client.response += message;
	this->_Utils.setClientToPollOut(irc, client);
}

std::string	SendMsg::_header(t_irc& irc, Client& client) {
	return (":" + irc.hostname + ":" + std::to_string(irc.port) + " " + client.nickname);
}
