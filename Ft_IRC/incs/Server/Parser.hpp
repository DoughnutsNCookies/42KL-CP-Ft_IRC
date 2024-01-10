/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:55:39 by schuah            #+#    #+#             */
/*   Updated: 2024/01/10 17:56:41 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <vector>

typedef std::vector<std::string>	tokensVector;

class Parser {
	public:
		Parser();
		tokensVector	parse(std::string str, std::string delim, bool includeEnd);
};

#endif
