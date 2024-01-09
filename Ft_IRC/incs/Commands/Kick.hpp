/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 16:36:15 by schuah            #+#    #+#             */
/*   Updated: 2024/01/09 05:28:28 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KICK_HPP
#define KICK_HPP

#include <algorithm>

#include "Commands/ATokenParser.hpp"
#include "Utils/irc.hpp"
#include "Utils/SendMsg.hpp"
#include "Utils/Utils.hpp"
#include "Server/Parser.hpp"

class Kick : public ATokenParser {
	public:
		Kick();
		void			verifyTokens(t_irc& irc, Client& client, tokensVector& tokens);
	
	private:
		std::string		_channelName;
		std::string		_comment;
		tokensVector	_nicknames;
		Channel			_channel;

		Parser			_Parser;
		Utils			_Utils;
		SendMsg			_SendMsg;
		
		void			_parseTokens(tokensVector& tokens);
		void			_executeCommand(t_irc& irc, Client& client);
};

#endif
