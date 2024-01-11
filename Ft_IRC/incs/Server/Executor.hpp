/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Executor.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:34:05 by schuah            #+#    #+#             */
/*   Updated: 2024/01/11 21:46:52 by plau             ###   ########.fr       */
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
#include "Commands/Part.hpp"
#include "Commands/List.hpp"
#include "Commands/Notice.hpp"
#include "Commands/Invite.hpp"
#include "Commands/Part.hpp"
#include "Commands/Names.hpp"

enum TOKEN {
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
	NOTICE,
	INVITE,
	NAMES,
	UNKNOWN
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
		Part			_Part;
		List			_List;
		Notice			_Notice;
		Invite			_Invite;
		Names			_Names;
		
		TOKEN			_getToken(std::string token);
		tokensVector	_getNextTokens(tokensVector& tokens);
};

#endif
