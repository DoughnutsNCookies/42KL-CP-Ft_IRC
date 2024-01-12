/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 18:38:05 by schuah            #+#    #+#             */
/*   Updated: 2024/01/12 17:41:33 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUIT_HPP
#define QUIT_HPP

#include <iostream>
#include <unistd.h>

#include "ATokenParser.hpp"
#include "Part.hpp"
#include "Server/Responder.hpp"
#include "Utils/color.hpp"
#include "Utils/Utils.hpp"
#include "Utils/SendMsg.hpp"

class Quit : public ATokenParser {
	public:
		Quit();
		void		verifyTokens(t_irc& irc, Client& client, tokensVector& tokens);
		void		disconnectClient(t_irc& irc, int fd);
	
	private:
		std::string	_quitMessage;

		Responder	_Responder;
		Utils		_Utils;
		SendMsg		_SendMsg;
		Part		_Part;

		void		_parseTokens(tokensVector& tokens);
		void		_executeCommand(t_irc& irc, Client& client);
		void		_sendAllClientQuitMessage(t_irc& irc, Client& client);
};

#endif
