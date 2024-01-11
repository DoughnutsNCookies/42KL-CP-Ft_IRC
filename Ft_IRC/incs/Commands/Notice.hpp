/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Notice.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:29:41 by schuah            #+#    #+#             */
/*   Updated: 2024/01/11 19:55:35 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NOTICE_HPP
#define NOTICE_HPP

#include "ATokenParser.hpp"
#include "Utils/irc.hpp"
#include "Utils/SendMsg.hpp"
#include "Utils/Utils.hpp"
#include "Server/Parser.hpp"
#include "Server/Channel.hpp"

class Notice : public ATokenParser {
	public:
		Notice();
		void	verifyTokens(t_irc& irc, Client& client, tokensVector& tokens);

	private:
		tokensVector	_destinations;
		std::string		_message;

		Parser			_Parser;
		Utils			_Utils;
		SendMsg			_SendMsg;

		void	_parseTokens(tokensVector& tokens);
		void	_executeCommand(t_irc& irc, Client& client);
		void	_sendToChannel(t_irc& irc, Client& client, std::string channelName);
};

#endif
