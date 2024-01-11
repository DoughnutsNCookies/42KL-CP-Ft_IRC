/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:11:17 by schuah            #+#    #+#             */
/*   Updated: 2024/01/11 14:44:53 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PART_HPP
#define PART_HPP

#include <set>

#include "ATokenParser.hpp"
#include "Server/Parser.hpp"
#include "Utils/SendMsg.hpp"
#include "Utils/Utils.hpp"

class Part : public ATokenParser {
	public:
		Part();
		void			verifyTokens(t_irc& irc, Client& client, tokensVector& tokens);
		void			leaveChannel(t_irc& irc, Client& client, Channel& channel);

	private:
		tokensVector	_channelNames;
		std::string		_reason;

		Parser			_Parser;
		Utils			_Utils;
		SendMsg			_SendMsg;

		void			_parseTokens(tokensVector& tokens);
		void			_executeCommand(t_irc& irc, Client& client);
};

#endif
