/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:56:32 by schuah            #+#    #+#             */
/*   Updated: 2023/11/17 18:28:53 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"

Parser::Parser() {}

std::vector<std::string>	Parser::parse(std::string &buffer) {
	std::vector<std::string>	tokens = this->_split(buffer, " \r\n");
	return tokens;
}

std::vector<std::string>	Parser::_split(std::string str, std::string delim) {
	std::vector<std::string>	result;

	while (!str.empty()) {
		size_t pos = str.find_first_not_of(delim);
		if (pos == std::string::npos)
				break;
		size_t nextPos = str.find_first_of(delim, pos);
		result.push_back(str.substr(pos, nextPos - pos));
		if (nextPos == std::string::npos)
			break;
		str.erase(0, nextPos + 1);
	}
	return (result);
}
