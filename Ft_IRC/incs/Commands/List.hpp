/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   List.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:25:05 by plau              #+#    #+#             */
/*   Updated: 2024/01/11 22:00:42 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>

#include "ATokenParser.hpp"
#include "Server/Parser.hpp"
#include "Utils/Utils.hpp"
#include "Utils/SendMsg.hpp"

class List : public ATokenParser {
	public:
		List();
		void			verifyTokens(t_irc& irc, Client& client, tokensVector& tokens);
		void			listAllChannels(t_irc&irc, Client& client);

	private:
		bool			_listAll;
		tokensVector	_channelList;

		Utils			_Utils;
		SendMsg			_SendMsg;
		Parser			_Parser;

		void			_parseTokens(tokensVector& tokens);
		void			_executeCommand(t_irc& irc, Client& client);
		void			_displayAllLists(t_irc& irc, Client& client);
		void			_displaySpecifiedLists(t_irc& irc, Client& client);
};

#endif
