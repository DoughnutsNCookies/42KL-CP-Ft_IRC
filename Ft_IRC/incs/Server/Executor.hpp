/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Executor.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:34:05 by schuah            #+#    #+#             */
/*   Updated: 2024/01/03 20:27:19 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_HPP
#define EXECUTOR_HPP

#include <unistd.h>
#include <iostream>

#include "Utils/irc.hpp"
#include "Utils/color.hpp"
#include "Utils/SendMsg.hpp"
#include "Client.hpp"
#include "Commands/Pass.hpp"
#include "Commands/Nick.hpp"
#include "Commands/User.hpp"
#include "Commands/Privmsg.hpp"
#include "Commands/Join.hpp"
#include "Commands/Kick.hpp"

enum TOKEN {
	UNKNOWN = -1,
	PASS = 0,
	NICK = 1,
	USER = 2,
	PRIVMSG = 3,
	JOIN = 4,
	KICK = 5,
	TOPIC = 6
};

class Executor {
	public:
		Executor();
		void					execute(t_irc& irc, Client& client, tokensVector& tokens);
		void					disconnect(t_irc& irc, int i);

	private:
		SendMsg				_SendMsg;
		Pass					_Pass;
		Nick					_Nick;
		User					_User;
		Privmsg				_Privmsg;
		Join					_Join;
		Kick					_Kick;
		
		TOKEN					_getToken(std::string token);
		tokensVector	_getNextTokens(tokensVector& tokens);
};

#endif
