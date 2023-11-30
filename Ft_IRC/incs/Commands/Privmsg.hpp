/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Privmsg.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 13:49:24 by schuah            #+#    #+#             */
/*   Updated: 2023/11/30 21:10:31 by schuah           ###   ########.fr       */
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
		void						verifyTokens(t_irc& irc, Client& client, tokensVector& tokens);
	
	private:
		tokensVector		_destinations;
		std::string			_message;

		Parser					_Parser;
		Utils						_Utils;
		SendMsg					_SendMsg;

		void						_parseTokens(tokensVector& tokens);
		void						_executeCommand(t_irc& irc, Client& client);
		void						_sendToUser(t_irc& irc, Client& client, std::string receiverNickname, std::string destination);
		void						_sendToChannel(t_irc& irc, Client& client, std::string channelName);
};

#endif
