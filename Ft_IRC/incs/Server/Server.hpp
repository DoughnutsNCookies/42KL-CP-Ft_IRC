/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:42:42 by schuah            #+#    #+#             */
/*   Updated: 2024/01/05 17:17:57 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <map>
#include <string>

#include "ft_irc.hpp"
#include "Utils/irc.hpp"
#include "Client.hpp"
#include "Receiver.hpp"
#include "Responder.hpp"
#include "Parser.hpp"
#include "Executor.hpp"

class Server {
	public:
		Server(const char *port, const char *password);
		void		run();
	
	private:
		t_irc		_irc;

		Receiver	_Receiver;
		Responder	_Responder;
		Parser		_Parser;
		Executor	_Executor;

		void		perrorExit(const char *error);
		void		createSocket();
		void		bindSocket();
		void		listenSocket();
};

#endif
