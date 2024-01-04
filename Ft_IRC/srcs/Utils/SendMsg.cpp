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

void	SendMsg::rpl331(t_irc& irc, Client& client, std::string channelName) {
	client.response += this->_header(irc, client) + " 331 " + client.nickname + " " + channelName + " :No topic is set\r\n";
	this->_Utils.setClientToPollOut(irc, client);
}

void	SendMsg::rpl332(t_irc& irc, Client& client, std::string channelName, std::string channelTopic) {
	client.response += this->_header(irc, client) + " 332 " +  client.nickname + " " + channelName + " :" + channelTopic + "\r\n";
	this->_Utils.setClientToPollOut(irc, client);
}

void	SendMsg::rpl333(t_irc& irc, Client& client, std::string channelName) {
	client.response += this->_header(irc, client) + " 333 " +  client.nickname + " " + channelName + " " + client.nickname + " " + this->_getTime() + "\r\n";
	this->_Utils.setClientToPollOut(irc, client);
}

void	SendMsg::rpl353(t_irc& irc, Client& client, std::map<std::string, Client> users, std::string channelName) {
	std::string userList = "";
	for (std::map<std::string, Client>::iterator it = users.begin(); it != users.end(); it++)
		userList += it->second.nickname + " ";
	client.response += this->_header(irc, client) + " 353 " +  client.nickname + " = " + channelName + " :" + userList + "\r\n";
	this->_Utils.setClientToPollOut(irc, client);
}

void	SendMsg::rpl366(t_irc& irc, Client& client, std::string channelName) {
	client.response += this->_header(irc, client) + " 366 " +  client.nickname + " " + channelName + " :End of /NAMES list\r\n";
	this->_Utils.setClientToPollOut(irc, client);
}

void	SendMsg::error401(t_irc& irc, Client& client, std::string nickname) {
	client.response += this->_header(irc, client) + " 401 " +  client.nickname + " " + nickname + " :No such nick/channel\r\n";
	this->_Utils.setClientToPollOut(irc, client);
}

void	SendMsg::error403(t_irc& irc, Client& client, std::string channelName) {
	client.response += this->_header(irc, client) + " 403 " +  client.nickname + " " + channelName + " :No such channel\r\n";
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

void	SendMsg::error441(t_irc& irc, Client& client, std::string nickname, std::string channelName) {
	client.response += this->_header(irc, client) + " 441 " +  client.nickname + " " + nickname + " " + channelName + " :They aren't on that channel\r\n";
	this->_Utils.setClientToPollOut(irc, client);
}

void	SendMsg::error442(t_irc& irc, Client& client, std::string channelName) {
	client.response += this->_header(irc, client) + " 442 " +  client.nickname + " " + channelName + " :You're not on that channel\r\n";
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

void	SendMsg::error482(t_irc& irc, Client& client, std::string channelName) {
	client.response += this->_header(irc, client) + " 482 " +  client.nickname + " " + channelName + " :You're not channel operator\r\n";
	this->_Utils.setClientToPollOut(irc, client);
}

void	SendMsg::customMsg(t_irc& irc, Client& client, std::string message) {
	client.response += message;
	this->_Utils.setClientToPollOut(irc, client);
}

std::string	SendMsg::_header(t_irc& irc, Client& client) {
	return (":" + irc.hostname + ":" + std::to_string(irc.port) + " " + client.nickname);
}

std::string SendMsg::_getTime() {
	std::time_t setAt = std::time(nullptr);
	std::tm* timeInfo = std::gmtime(&setAt);
	char buffer[100];
	std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeInfo);
	return (std::string(buffer));
}
