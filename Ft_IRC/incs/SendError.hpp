/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SendError.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:22:31 by plau              #+#    #+#             */
/*   Updated: 2023/11/22 17:51:50 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SENDERROR_HPP
#define SENDERROR_HPP

#include "Client.hpp"

class SendError {
	public:
		SendError();
		
		/* ERR_UNKNOWNCOMMAND */
		void	error421(Client& client, std::string unknownCommand);
		void	error431(Client& client);
		void	error432(Client& client);
		void	error433(Client& client);
		void	error461(Client& client);
		void	error462(Client& client);
		void	error464(Client& client);
};

#endif
