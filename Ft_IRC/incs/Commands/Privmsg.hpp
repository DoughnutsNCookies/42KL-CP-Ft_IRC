/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Privmsg.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 13:49:24 by schuah            #+#    #+#             */
/*   Updated: 2024/01/11 15:07:16 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIVMSG_HPP
#define PRIVMSG_HPP

#include "ATokenParser.hpp"
#include "Utils/irc.hpp"
#include "Utils/SendMsg.hpp"
#include "Utils/Utils.hpp"
#include "Server/Parser.hpp"
#include "Server/Channel.hpp"

class Privmsg : public ATokenParser {
	public:
		Privmsg();
		void			verifyTokens(t_irc& irc, Client& client, tokensVector& tokens);
	
	private:
		tokensVector	_destinations;
		std::string		_message;

		Parser			_Parser;
		Utils			_Utils;
		SendMsg			_SendMsg;

		void			_parseTokens(tokensVector& tokens);
		void			_executeCommand(t_irc& irc, Client& client);
		void			_sendToChannel(t_irc& irc, Client& client, std::string channelName);
};

#endif
