/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SendMsg.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:22:31 by plau              #+#    #+#             */
/*   Updated: 2023/11/28 20:50:15 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SendMsg_HPP
#define SendMsg_HPP

#include <sys/time.h>
#include <ctime>

#include "Utils/irc.hpp"
#include "Utils/Utils.hpp"
#include "Server/Client.hpp"
#include "Server/Channel.hpp"


class SendMsg {
	public:
		SendMsg();
		/*	RPL_NOTOPIC	*/
		void				rpl331(t_irc& irc, Client& client, std::string channelName);

		/* RPL_TOPIC */
		void				rpl332(t_irc& irc, Client& client, std::string channelName, std::string channelTopic);

		/* RPL_TOPICWHOTIME	*/
		void				rpl333(t_irc& irc, Client& client, std::string channelName);

		/* RPL_NAMREPLY */
		void				rpl353(t_irc& irc, Client& client, std::map<std::string, Client> users, std::string channelName);

		/* RPL_ENDOFNAMES */
		void				rpl366(t_irc& irc, Client& client, std::string channelName);

		/* ERR_NOSUCHNICK */
		void				error401(t_irc& irc, Client& client, std::string nickname);
		
		/* ERR_NOSUCHCHANNEL */
		void				error403(t_irc& irc, Client& client, std::string channelName);
		
		/* ERR_NORECIPIENT */
		void				error411(t_irc& irc, Client& client, std::string command);

		/* ERR_NOTEXTTOSEND */
		void				error412(t_irc& irc, Client& client);

		/* ERR_UNKNOWNCOMMAND */
		void				error421(t_irc& irc, Client& client, std::string unknownCommand);

		/* ERR_NONICKNAMEGIVEN */
		void				error431(t_irc& irc, Client& client);

		/* ERR_ERRONEUSNICKNAME */
		void				error432(t_irc& irc, Client& client, std::string nickname);

		/* ERR_NICKNAMEINUSE */
		void				error433(t_irc& irc, Client& client, std::string nickname);

		/* ERR_USERNOTINCHANNEL */
		void				error441(t_irc& irc, Client& client, std::string nickname, std::string channelName);

		/* ERR_NOTONCHANNEL */
		void				error442(t_irc& irc, Client& client, std::string channelName);

		/* ERR_NOTREGISTERED */
		void				error451(t_irc& irc, Client& client);

		/* ERR_NEEDMOREPARAMS */
		void				error461(t_irc& irc, Client& client, std::string command);

		/* ERR_ALREADYREGISTRED */
		void				error462(t_irc& irc, Client& client);

		/* ERR_PASSWDMISMATCH */
		void				error464(t_irc& irc, Client& client);

		/* ERR_CHANOPRIVSNEEDED */
		void				error482(t_irc& irc, Client& client, std::string channelName);

		/* Custom message */
		void				customMsg(t_irc& irc, Client& client, std::string message);
	
	private:
		Utils				_Utils;

		std::string			_header(t_irc& irc, Client& client, int code);
		std::string			_getEpochTime();
};

#endif
