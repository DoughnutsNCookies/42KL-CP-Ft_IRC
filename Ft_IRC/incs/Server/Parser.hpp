/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:55:39 by schuah            #+#    #+#             */
/*   Updated: 2023/11/30 14:34:07 by plau             ###   ########.fr       */
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
		tokensVector	parse(std::string str, std::string delim);
};

#endif
