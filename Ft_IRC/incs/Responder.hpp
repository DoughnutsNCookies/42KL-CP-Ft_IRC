/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Responder.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 21:50:09 by schuah            #+#    #+#             */
/*   Updated: 2023/11/17 22:05:16 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONDER_HPP
#define RESPONDER_HPP

#include <sys/socket.h>
#include <poll.h>
#include <string>
#include <iostream>

#include "Client.hpp"
#include "color.hpp"

class Responder {
	public:
		Responder();
		void	respond(Client client);
};

#endif
