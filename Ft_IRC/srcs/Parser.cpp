/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:56:32 by schuah            #+#    #+#             */
/*   Updated: 2023/11/17 17:22:36 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"

Parser::Parser() {}

std::vector<std::string>	Parser::parse(std::string &buffer) {
	std::vector<std::string>	tokens = this->_split(buffer, " ");
	return tokens;
}

std::vector<std::string>	Parser::_split(std::string str, std::string delim) {
	std::vector<std::string>	result;

	while (str.length() > 0) {
		size_t pos = str.find(delim);
		if (pos == std::string::npos) {
			result.push_back(str);
			break ;
		}
		result.push_back(str.substr(0, pos));
		str.erase(0, pos + delim.length());
	}
	return (result);
}
