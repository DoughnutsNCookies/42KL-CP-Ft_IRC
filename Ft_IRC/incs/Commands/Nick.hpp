/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:49:15 by plau              #+#    #+#             */
/*   Updated: 2023/11/30 21:52:24 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NICK_HPP
#define NICK_HPP

#include "Commands/ATokenParser.hpp"
#include "Commands/Privmsg.hpp"
#include "Utils/irc.hpp"
#include "Utils/SendMsg.hpp"
#include "Utils/Utils.hpp"

class Nick : public ATokenParser {
	public:
		Nick();
		void				verifyTokens(t_irc& irc, Client& client, tokensVector& tokens);
	
	private:
		std::string _nickname;
		
		Privmsg			_Privmsg;
		SendMsg			_SendMsg;

		void				_parseTokens(tokensVector& tokens);
		void				_executeCommand(t_irc& irc, Client& client);
		bool				_checkValidNickName(std::string nickname);
};

#endif
