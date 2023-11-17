/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Executor.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:34:45 by schuah            #+#    #+#             */
/*   Updated: 2023/11/17 18:38:16 by schuah           ###   ########.fr       */
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

void	Executor::execute(std::vector<std::string> &tokens) {
	for (std::vector<std::string>::iterator it = tokens.begin(); it != tokens.end(); ++it) {
		std::cout << "|" << *it << "|" << std::endl;
	}
	TOKEN	token = this->_getToken(tokens[0]);
	std::cout << token << std::endl;
}
