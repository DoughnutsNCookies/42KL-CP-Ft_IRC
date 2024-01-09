/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:42:42 by schuah            #+#    #+#             */
/*   Updated: 2024/01/09 13:51:58 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include <netdb.h>
#include <fcntl.h>
#include <map>
#include <string>
#include <sstream>

#include "Commands/Quit.hpp"
#include "Utils/irc.hpp"
#include "Utils/Utils.hpp"
#include "ft_irc.hpp"
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
		Utils		_Utils;
		Quit		_Quit;

		void		_perrorExit(const char *error);
		void		_createSocket();
		void		_bindSocket();
		void		_listenSocket();
};

#endif
