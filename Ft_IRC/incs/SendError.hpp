/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SendError.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:22:31 by plau              #+#    #+#             */
/*   Updated: 2023/11/21 20:34:35 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SENDERROR_HPP
#define SENDERROR_HPP

#include "Client.hpp"

class SendError {
	public:
		SendError();
		void	error431(Client& client);
		void	error432(Client& client);
		void	error433(Client& client);
		void	error461(Client& client);
		void	error462(Client& client);
		void	error464(Client& client);
};

#endif
