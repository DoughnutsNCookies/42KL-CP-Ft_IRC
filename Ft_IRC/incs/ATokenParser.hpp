/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ATokenParser.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 16:30:22 by plau              #+#    #+#             */
/*   Updated: 2023/11/22 17:24:29 by schuah           ###   ########.fr       */
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
		virtual void	verifyTokens(t_irc& irc, Client& client, tokensVector& tokens) = 0;
	private:
		virtual void	_parseTokens(tokensVector& tokens) = 0;
		virtual void	_executeCommand(t_irc& irc, Client& client) = 0;
};

#endif
