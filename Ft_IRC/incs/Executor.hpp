/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Executor.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:34:05 by schuah            #+#    #+#             */
/*   Updated: 2023/11/22 17:50:04 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_HPP
#define EXECUTOR_HPP

#include <unistd.h>
#include <iostream>

#include "irc.hpp"
#include "color.hpp"
#include "Client.hpp"
#include "SendError.hpp"
#include "Pass.hpp"
#include "Nick.hpp"

enum TOKEN {
	UNKNOWN = -1,
	PASS = 0,
	NICK = 1,
	USER = 2,
	JOIN = 3,
	PRIVMSG = 4,
	KICK = 5,
	TOPIC = 6
};

class Executor {
	public:
		Executor();
		void			execute(t_irc& irc, Client& client, tokensVector& tokens);
		void			disconnect(t_irc& irc, int i);

	private:
		SendError	_SendError;
		Pass			_Pass;
		Nick			_Nick;
		
		TOKEN			_getToken(std::string token);
		tokensVector	_getNextTokens(tokensVector& tokens);
};

#endif
