/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Executor.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:34:05 by schuah            #+#    #+#             */
/*   Updated: 2024/01/11 13:31:46 by schuah           ###   ########.fr       */
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

enum TOKEN {
	UNKNOWN,
	PASS,
	NICK,
	USER,
	PRIVMSG,
	JOIN,
	KICK,
	TOPIC,
	PONG,
	QUIT,
	PART,
	LIST,
	NOITCE
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
		
		TOKEN			_getToken(std::string token);
		tokensVector	_getNextTokens(tokensVector& tokens);
};

#endif
