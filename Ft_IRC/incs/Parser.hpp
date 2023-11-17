/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:55:39 by schuah            #+#    #+#             */
/*   Updated: 2023/11/17 17:56:41 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <vector>

class Parser {
	public:
		Parser();
		std::vector<std::string>	parse(std::string &buffer);
	private:
		std::vector<std::string>	_split(std::string str, std::string delim);
};

#endif
