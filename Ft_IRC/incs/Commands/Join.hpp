/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 20:25:40 by schuah            #+#    #+#             */
/*   Updated: 2024/01/12 19:18:42 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOIN_HPP
#define JOIN_HPP

#include "ATokenParser.hpp"
#include "Server/Parser.hpp"
#include "Utils/Utils.hpp"
#include "Utils/SendMsg.hpp"
#include "Part.hpp"

class Join : public ATokenParser {
	public:
		Join();
		void			verifyTokens(t_irc& irc, Client& client, tokensVector &tokens);

	private:
		tokensVector	_channelNames;
		bool			_leaveAll;

		Utils			_Utils;
		SendMsg			_SendMsg;
		Parser			_Parser;
		Part			_Part;

		void			_parseTokens(tokensVector& tokens);
		void			_executeCommand(t_irc& irc, Client& client);
		void			_createChannel(t_irc& irc, Client& client, std::string name);
		void			_joinChannel(t_irc& irc, Client& client, std::string name);
};

#endif
