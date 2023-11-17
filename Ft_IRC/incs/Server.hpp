/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:42:42 by schuah            #+#    #+#             */
/*   Updated: 2023/11/17 16:54:04 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <map>
#include <string>

#include "ft_irc.hpp"
#include "Client.hpp"
#include "Receiver.hpp"
#include "Responder.hpp"
#include "Parser.hpp"

class Server {
	public:
		Server(const char *port, const char *password);
		void												run();
	
	private:
		int													_port;
		int 												_server_fd;
		std::string									_password;
		std::map<int, Client>				_clients;
		std::vector<struct pollfd>	_fds;

		Receiver										_Receiver;
		Responder										_Responder;
		Parser											_Parser;

		void												perror_exit(const char *error);
		void												create_socket();
		void												bind_socket();
		void												listen_socket();
};

#endif
