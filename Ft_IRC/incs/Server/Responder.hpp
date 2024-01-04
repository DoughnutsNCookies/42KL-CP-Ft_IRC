/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Responder.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 21:50:09 by schuah            #+#    #+#             */
/*   Updated: 2024/01/04 21:26:31 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONDER_HPP
#define RESPONDER_HPP

#include <sys/socket.h>
#include <poll.h>
#include <string>
#include <iostream>

#include "Client.hpp"
#include "Utils/color.hpp"
#include "Utils/irc.hpp"

class Responder {
	public:
		Responder();
		void	respond(t_irc& irc, Client& client);
};

#endif
