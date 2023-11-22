/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SendError.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:22:31 by plau              #+#    #+#             */
/*   Updated: 2023/11/22 16:56:25 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SENDERROR_HPP
#define SENDERROR_HPP

#include "Client.hpp"

class SendError {
	public:
		SendError();

		/* ERR_NONICKNAMEGIVEN */
		void	error431(Client& client);

		/* ERR_ERRONEUSNICKNAME */
		void	error432(Client& client);

		/* ERR_NICKNAMEINUSE */
		void	error433(Client& client);

		/* ERR_NEEDMOREPARAMS */
		void	error461(Client& client);

		/* ERR_ALREADYREGISTRED */
		void	error462(Client& client);

		/* ERR_PASSWDMISMATCH */
		void	error464(Client& client);
};

#endif
