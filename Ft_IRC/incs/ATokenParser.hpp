/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ATokenParser.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 16:30:22 by plau              #+#    #+#             */
/*   Updated: 2023/11/21 18:24:34 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ATOKENPARSER_HPP
#define ATOKENPARSER_HPP

#include <vector>
#include <string>
#include "irc.hpp"
#include "Client.hpp"

typedef std::vector<std::string>	tokensVector;

class ATokenParser {
	public:
		virtual void	verifyTokens(t_irc& irc, Client& client, tokensVector &tokens) = 0;
	private:
		virtual void	_parseTokens(tokensVector &tokens) = 0;
		virtual void	_executeCommand(t_irc& irc, Client& client) = 0;
};

#endif
