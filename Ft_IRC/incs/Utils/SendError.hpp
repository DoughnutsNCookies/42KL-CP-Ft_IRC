/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SendError.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:22:31 by plau              #+#    #+#             */
/*   Updated: 2023/11/28 12:26:34 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SENDERROR_HPP
#define SENDERROR_HPP

#include "Server/Client.hpp"

class SendError {
	public:
		SendError();
		
		/* ERR_UNKNOWNCOMMAND */
		void	error421(Client& client, std::string unknownCommand);

		/* ERR_NONICKNAMEGIVEN */
		void	error431(Client& client);

		/* ERR_ERRONEUSNICKNAME */
		void	error432(Client& client);

		/* ERR_NICKNAMEINUSE */
		void	error433(Client& client);

		/* ERR_NOTREGISTERED */
		void	error451(Client& client);

		/* ERR_NEEDMOREPARAMS */
		void	error461(Client& client);

		/* ERR_ALREADYREGISTRED */
		void	error462(Client& client);

		/* ERR_PASSWDMISMATCH */
		void	error464(Client& client);
};

#endif
