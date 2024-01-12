/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Names.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 22:14:07 by plau              #+#    #+#             */
/*   Updated: 2024/01/11 22:00:17 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NAMES_HPP
#define NAMES_HPP

#include "ATokenParser.hpp"
#include "Server/Parser.hpp"
#include "Utils/Utils.hpp"
#include "Utils/SendMsg.hpp"

class Names : public ATokenParser {
	public:
		Names();
		void	verifyTokens(t_irc& irc, Client& client, tokensVector& tokens);

	private:
		bool			_nameAll;
		tokensVector	_nameList;
		SendMsg			_SendMsg;
		Parser			_Parser;

		void			_parseTokens(tokensVector& tokens);
		void			_executeCommand(t_irc& irc, Client& client);
		void			_displayAllNames(t_irc& irc, Client& client);
		void			_displaySpecifiedNames(t_irc& irc, Client& client);
};

#endif