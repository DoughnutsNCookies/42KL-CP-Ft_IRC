/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Privmsg.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 13:49:24 by schuah            #+#    #+#             */
/*   Updated: 2023/11/28 21:01:06 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIVMSG_HPP
#define PRIVMSG_HPP

#include "ATokenParser.hpp"
#include "Utils/irc.hpp"
#include "Utils/SendError.hpp"
#include "Server/Parser.hpp"

class Privmsg : public ATokenParser {
	public:
		Privmsg();
		void					verifyTokens(t_irc& irc, Client& client, tokensVector& tokens);
	
	private:
		tokensVector		_nicknames;
		std::string			_message;

		Parser					_Parser;
		SendError				_SendError;

		void						_parseTokens(tokensVector& tokens);
		void						_executeCommand(t_irc& irc, Client& client);
		Client&					_getClientByNickname(t_irc& irc, std::string nickname);
		struct pollfd&	_getPollfdByFd(t_irc& irc, int fd);

		class	NoClientFoundException : public std::exception {
			public:
				virtual const char* what() const throw();
		};

		class	NoPollfdFoundException : public std::exception {
			public:
				virtual const char* what() const throw();
		};
};

#endif
