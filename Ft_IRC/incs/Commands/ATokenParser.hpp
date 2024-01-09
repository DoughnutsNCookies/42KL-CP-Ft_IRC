/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ATokenParser.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 16:30:22 by plau              #+#    #+#             */
/*   Updated: 2024/01/09 05:28:25 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ATOKENPARSER_HPP
#define ATOKENPARSER_HPP

#include <vector>
#include <string>

#include "Utils/irc.hpp"
#include "Server/Client.hpp"

typedef std::vector<std::string>	tokensVector;

class ATokenParser {
	public:
		virtual void	verifyTokens(t_irc& irc, Client& client, tokensVector& tokens) = 0;
	private:
		virtual void	_parseTokens(tokensVector& tokens) = 0;
		virtual void	_executeCommand(t_irc& irc, Client& client) = 0;
};

#endif
