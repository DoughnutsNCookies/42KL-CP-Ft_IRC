/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Receiver.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:22:58 by schuah            #+#    #+#             */
/*   Updated: 2024/01/04 21:26:19 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef Receiver_HPP
#define Receiver_HPP

#include <poll.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include <netdb.h>

#include "Utils/color.hpp"
#include "Utils/irc.hpp"
#include "Client.hpp"

class Receiver {
	public:
		Receiver();
		void		new_connection(t_irc& irc);
		int			receive(t_irc& irc, int i);
};

#endif
