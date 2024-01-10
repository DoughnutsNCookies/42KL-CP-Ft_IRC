/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 20:25:40 by schuah            #+#    #+#             */
/*   Updated: 2024/01/10 16:12:13 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOIN_HPP
#define JOIN_HPP

#include "ATokenParser.hpp"
#include "Commands/Privmsg.hpp"
#include "Server/Parser.hpp"
#include "Utils/SendMsg.hpp"

class Join : public ATokenParser {
	public:
		Join();
		void			verifyTokens(t_irc& irc, Client& client, tokensVector &tokens);

	private:
		tokensVector	_channelNames;

		SendMsg			_SendMsg;
		Parser			_Parser;
		Privmsg			_Privmsg;

		void			_parseTokens(tokensVector& tokens);
		void			_executeCommand(t_irc& irc, Client& client);
		void			_createChannel(t_irc& irc, Client& client, std::string name);
		void			_joinChannel(t_irc& irc, Client& client, std::string name);
};

#endif
