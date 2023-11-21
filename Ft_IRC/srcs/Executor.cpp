/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Executor.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:34:45 by schuah            #+#    #+#             */
/*   Updated: 2023/11/21 17:56:11 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Executor.hpp"

Executor::Executor() {}

TOKEN	Executor::_getToken(std::string token) {
	static const std::pair<const char*, TOKEN> tokenPairs[] = {
		std::pair<const char*, TOKEN>("PASS", PASS),
		std::pair<const char*, TOKEN>("NICK", NICK),
		std::pair<const char*, TOKEN>("USER", USER),
		std::pair<const char*, TOKEN>("JOIN", JOIN),
		std::pair<const char*, TOKEN>("PRIVMSG", PRIVMSG),
		std::pair<const char*, TOKEN>("KICK", KICK),
		std::pair<const char*, TOKEN>("TOPIC", TOPIC)
	};

	for (int i = 0; i < 7; i++) {
		if (tokenPairs[i].first == token)
			return (tokenPairs[i].second);
	}
	return (UNKNOWN);
}

void	Executor::execute(t_irc& irc, Client& client, tokensVector &tokens) {
	TOKEN	token = this->_getToken(tokens[0]);
	this->_Pass.verify(irc, client, tokens);
	(void)token;
}

void	Executor::disconnect(t_irc& irc, int i) {
	std::vector<struct pollfd>&	fds = irc._fds;
	std::map<int, Client>&			clients = irc._clients;
	int&												pollfd = fds[i].fd;

	std::cout << RED << "Client disconnected" << RESET << std::endl;
	close(pollfd);
	fds.erase(fds.begin() + i);
	clients.erase(pollfd);
}
