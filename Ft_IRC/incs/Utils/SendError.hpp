/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SendError.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:22:31 by plau              #+#    #+#             */
/*   Updated: 2023/11/28 18:06:33 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SENDERROR_HPP
#define SENDERROR_HPP

#include "Utils/irc.hpp"
#include "Server/Client.hpp"

class SendError {
	public:
		SendError();

		/* ERR_NOSUCHNICK */
		void				error401(t_irc& irc, Client& client, std::string nickname);
		
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

		/* ERR_NOTREGISTERED */
		void				error451(t_irc& irc, Client& client);

		/* ERR_NEEDMOREPARAMS */
		void				error461(t_irc& irc, Client& client);

		/* ERR_ALREADYREGISTRED */
		void				error462(t_irc& irc, Client& client);

		/* ERR_PASSWDMISMATCH */
		void				error464(t_irc& irc, Client& client);
	
	private:
		std::string	header(t_irc& irc, Client& client);
};

#endif
