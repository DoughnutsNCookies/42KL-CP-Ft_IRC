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

void	SendMsg::rpl001(t_irc& irc, Client& client) {
	client.response += this->_header(irc, client, "001") + "Welcome to the Internet Relay Network, " + client.nickname + "!" + client.username + "@" + irc.hostname + "\r\n";
	this->_Utils.setClientToPollOut(irc, client);
}

void	SendMsg::rpl002(t_irc& irc, Client& client) {
	client.response += this->_header(irc, client, "002") + "Your host is " + irc.hostname + ", running version " + irc.version + "\r\n";
	this->_Utils.setClientToPollOut(irc, client);
}

void	SendMsg::rpl003(t_irc& irc, Client& client) {
	client.response += this->_header(irc, client, "003") + "This server was created " + this->_getFormattedTime() + "\r\n";
	this->_Utils.setClientToPollOut(irc, client);
}

void	SendMsg::rpl004(t_irc& irc, Client& client) {
	client.response += this->_header(irc, client, "004") + irc.hostname + " " + irc.version + " " + irc.userModes + " " + irc.channelModes + " " + irc.channelModesWithParam + "\r\n";
	this->_Utils.setClientToPollOut(irc, client);
}

void	SendMsg::rpl005(t_irc& irc, Client& client) {
	client.response += this->_header(irc, client, "005") + irc.supportTokens + " :are supported by this server\r\n";
	this->_Utils.setClientToPollOut(irc, client);
}

void	SendMsg::rpl331(t_irc& irc, Client& client, std::string channelName) {
	client.response += this->_header(irc, client, "331") + channelName + " :No topic is set\r\n";
	this->_Utils.setClientToPollOut(irc, client);
}

void	SendMsg::rpl332(t_irc& irc, Client& client, std::string channelName, std::string channelTopic) {
	client.response += this->_header(irc, client, "332") + channelName + " :" + channelTopic + "\r\n";
	this->_Utils.setClientToPollOut(irc, client);
}

void	SendMsg::rpl333(t_irc& irc, Client& client, std::string channelName) {
	client.response += this->_header(irc, client, "333") + channelName + " " + client.nickname + " " + this->_getEpochTime() + "\r\n";
	this->_Utils.setClientToPollOut(irc, client);
}

void	SendMsg::rpl353(t_irc& irc, Client& client, Channel& channel) {
	std::string userList = "";
	for (std::map<std::string, Client>::iterator it = channel.users.begin(); it != channel.users.end(); it++) {
		if (it->second.nickname == channel.opName)
			userList += "@";
		userList += it->second.nickname + " ";
	}
	client.response += this->_header(irc, client, "353") + "= " + channel.name + " :" + userList + "\r\n";
	this->_Utils.setClientToPollOut(irc, client);
}

void	SendMsg::rpl366(t_irc& irc, Client& client, std::string channelName) {
	client.response += this->_header(irc, client, "366") + channelName + " :End of /NAMES list\r\n";
	this->_Utils.setClientToPollOut(irc, client);
}

void	SendMsg::error401(t_irc& irc, Client& client, std::string nickname) {
	client.response += this->_header(irc, client, "401") + nickname + " :No such nick/channel\r\n";
	this->_Utils.setClientToPollOut(irc, client);
}

void	SendMsg::error403(t_irc& irc, Client& client, std::string channelName) {
	client.response += this->_header(irc, client, "403") + channelName + " :No such channel\r\n";
	this->_Utils.setClientToPollOut(irc, client);
}

void	SendMsg::error411(t_irc& irc, Client& client, std::string command) {
	client.response += this->_header(irc, client, "411") + ":No recipient given (" + command + ")\r\n";
	this->_Utils.setClientToPollOut(irc, client);
}

void	SendMsg::error412(t_irc& irc, Client& client) {
	client.response += this->_header(irc, client, "412") + ":No text to send\r\n";
	this->_Utils.setClientToPollOut(irc, client);
}

void	SendMsg::error421(t_irc& irc, Client& client, std::string unknownCommand) {
	client.response += this->_header(irc, client, "421") + unknownCommand + " :Unknown command\r\n";
	this->_Utils.setClientToPollOut(irc, client);
}

void	SendMsg::error431(t_irc& irc, Client& client) {
	client.response += this->_header(irc, client, "431") + ":No nickname given\r\n";
	this->_Utils.setClientToPollOut(irc, client);
}

void	SendMsg::error432(t_irc& irc, Client& client, std::string nickname) {
	client.response += this->_header(irc, client, "432") + nickname + " :Erroneus nickname\r\n";
	this->_Utils.setClientToPollOut(irc, client);
}

void	SendMsg::error433(t_irc& irc, Client& client, std::string nickname) {
	client.response += this->_header(irc, client, "433") + nickname + " :Nickname is already in use\r\n";
	this->_Utils.setClientToPollOut(irc, client);
}

void	SendMsg::error441(t_irc& irc, Client& client, std::string nickname, std::string channelName) {
	client.response += this->_header(irc, client, "441") + nickname + " " + channelName + " :They aren't on that channel\r\n";
	this->_Utils.setClientToPollOut(irc, client);
}

void	SendMsg::error442(t_irc& irc, Client& client, std::string channelName) {
	client.response += this->_header(irc, client, "442") + channelName + " :You're not on that channel\r\n";
	this->_Utils.setClientToPollOut(irc, client);
}

void	SendMsg::error451(t_irc& irc, Client& client) {
	client.response += this->_header(irc, client, "451") + ":You have not registered\r\n";
	this->_Utils.setClientToPollOut(irc, client);
}

void	SendMsg::error461(t_irc& irc, Client& client, std::string command) {
	client.response += this->_header(irc, client, "461") + command + " :Not enough parameters\r\n";
	this->_Utils.setClientToPollOut(irc, client);
}

void	SendMsg::error462(t_irc& irc, Client& client) {
	client.response += this->_header(irc, client, "462") + ":You may not reregister\r\n";
	this->_Utils.setClientToPollOut(irc, client);
}

void	SendMsg::error464(t_irc& irc, Client& client) {
	client.response += this->_header(irc, client, "464") + ":Password incorrect\r\n";
	this->_Utils.setClientToPollOut(irc, client);
}

void	SendMsg::error482(t_irc& irc, Client& client, std::string channelName) {
	client.response += this->_header(irc, client, "482") + channelName + " :You're not channel operator\r\n";
	this->_Utils.setClientToPollOut(irc, client);
}

void	SendMsg::customMsg(t_irc& irc, Client& client, std::string message) {
	client.response += message;
	this->_Utils.setClientToPollOut(irc, client);
}

void	SendMsg::registeredMsg(t_irc& irc, Client& client) {
	if ((irc.password.size() != 0 && !client.verified) || !client.userSet || !client.nickSet)
		return;
	this->rpl001(irc, client);
	this->rpl002(irc, client);
	this->rpl003(irc, client);
	this->rpl004(irc, client);
	this->rpl005(irc, client);
}

std::string	SendMsg::_header(t_irc& irc, Client& client, std::string code) {
	return (":" + irc.hostname + " " + code + " " + client.nickname + " ");
}

std::string SendMsg::_getEpochTime() {
	struct timeval	time;
	gettimeofday(&time, NULL);
	// return (std::to_string(time.tv_sec));
	return ("1704724095");
}

std::string	SendMsg::_getFormattedTime() {
	time_t currentTime;
    time(&currentTime);
    struct tm *localTime = localtime(&currentTime);

    char formattedTime[50]; // Adjust the size based on your needs
    strftime(formattedTime, sizeof(formattedTime), "%d-%m-%Y %H:%M:%S", localTime);
	return (std::string(formattedTime));
}
