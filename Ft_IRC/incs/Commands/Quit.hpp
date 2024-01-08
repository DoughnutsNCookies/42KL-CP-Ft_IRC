/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 18:38:05 by schuah            #+#    #+#             */
/*   Updated: 2024/01/08 21:06:18 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUIT_HPP
#define QUIT_HPP

#include <iostream>
#include <unistd.h>

#include "Utils/color.hpp"
#include "ATokenParser.hpp"
#include "Commands/Privmsg.hpp"
#include "Utils/Utils.hpp"
#include "Utils/SendMsg.hpp"

class Quit : public ATokenParser {
	public:
		Quit();
		void		verifyTokens(t_irc& irc, Client& client, tokensVector& tokens);
		void		disconnectClient(t_irc& irc, int fd);
	
	private:
		std::string	_quitMessage;

		Utils		_Utils;
		SendMsg		_SendMsg;
		Privmsg		_Privmsg;

		void		_parseTokens(tokensVector& tokens);
		void		_executeCommand(t_irc& irc, Client& client);
		void		_sendAllClientQuitMessage(t_irc& irc, Client& client);
};

#endif
