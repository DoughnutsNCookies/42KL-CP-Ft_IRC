/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Executor.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:34:05 by schuah            #+#    #+#             */
/*   Updated: 2024/01/10 22:26:33 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_HPP
#define EXECUTOR_HPP

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
#include "Commands/Topic.hpp"
#include "Commands/Pong.hpp"
#include "Commands/Quit.hpp"
#include "Commands/List.hpp"
#include "Commands/Part.hpp"
#include "Commands/Names.hpp"

enum TOKEN {
	UNKNOWN = -1,
	PASS = 0,
	NICK = 1,
	USER = 2,
	PRIVMSG = 3,
	JOIN = 4,
	KICK = 5,
	TOPIC = 6,
	PONG = 7,
	QUIT = 8,
	PART = 9,
	LIST = 10,
	NAMES = 11
};

class Executor {
	public:
		Executor();
		void			execute(t_irc& irc, Client& client, tokensVector& tokens);

	private:
		SendMsg			_SendMsg;
		Pass			_Pass;
		Nick			_Nick;
		User			_User;
		Privmsg			_Privmsg;
		Join			_Join;
		Kick			_Kick;
		Topic			_Topic;
		Pong			_Pong;
		Quit			_Quit;
		List			_List;
		Part			_Part;
		Names			_Names;
		
		TOKEN			_getToken(std::string token);
		tokensVector	_getNextTokens(tokensVector& tokens);
};

#endif
