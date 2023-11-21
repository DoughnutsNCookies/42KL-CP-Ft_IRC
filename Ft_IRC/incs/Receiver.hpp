/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Receiver.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:22:58 by schuah            #+#    #+#             */
/*   Updated: 2023/11/21 20:22:04 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef Receiver_HPP
#define Receiver_HPP

#include <poll.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>

#include "color.hpp"
#include "irc.hpp"
#include "Client.hpp"

class Receiver {
	public:
		Receiver();
		void		new_connection(t_irc& irc);
		int			receive(t_irc& irc, int i);

	private:
		void		perrorExit(const char *error);
};

#endif
