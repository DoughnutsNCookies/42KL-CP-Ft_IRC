/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:56:32 by schuah            #+#    #+#             */
/*   Updated: 2023/11/30 14:27:06 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server/Parser.hpp"

Parser::Parser() {}

tokensVector	Parser::parse(std::string str, std::string delim) {
	tokensVector	result;

	while (!str.empty()) {
		size_t pos = str.find_first_not_of(delim);
		if (pos == std::string::npos)
			break;
		size_t nextPos = str.find_first_of(delim, pos);
		result.push_back(str.substr(pos, nextPos - pos));
		if (nextPos == std::string::npos)
			break;
		if (str[nextPos] == '\r' && str[nextPos + 1] == '\n')
			result.push_back(str.substr(nextPos, 2));
		str.erase(0, nextPos + 1);
	}
	if (result.size() > 0 && result[result.size() - 1] != "\r\n")
		result.push_back("\r\n");
	return (result);
}
