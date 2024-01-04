/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 16:44:42 by plau              #+#    #+#             */
/*   Updated: 2024/01/04 21:04:07 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOPIC_HPP
#define TOPIC_HPP

#include "Commands/ATokenParser.hpp"
#include "Commands/Privmsg.hpp"
#include "Utils/irc.hpp"
#include "Utils/SendMsg.hpp"
#include "Utils/Utils.hpp"

class Topic : public ATokenParser {
	public:
		Topic();
		void		verifyTokens(t_irc& irc, Client& client, tokensVector& tokens);

	private:
		std::string	_topic;
		std::string	_channelName;
		bool		_setTopic;

		Privmsg		_Privmsg;
		SendMsg		_SendMsg;
		Utils		_Utils;

		void		_parseTokens(tokensVector& tokens);
		void		_executeCommand(t_irc& irc, Client& client);
		void		_setNewTopic(t_irc& irc, Client& client, Channel& channel);
		void		_getTopic(t_irc& irc, Client& client, Channel& channel);
};

#endif
