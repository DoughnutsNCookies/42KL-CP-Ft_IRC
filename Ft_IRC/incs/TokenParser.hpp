/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TokenParser.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 16:30:22 by plau              #+#    #+#             */
/*   Updated: 2023/11/21 16:41:18 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENPARSER_HPP
#define TOKENPARSER_HPP

#include <vector>
#include <string>

typedef std::vector<std::string>	tokensVector;

class ATokenParser {
	private:
		virtual void	_parseTokens(tokensVector &tokens) = 0;

};

#endif
