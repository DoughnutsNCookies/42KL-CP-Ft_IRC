/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:42:42 by schuah            #+#    #+#             */
/*   Updated: 2023/11/16 23:05:20 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <map>

#include "ft_irc.hpp"
#include "Client.hpp"
#include "Receiver.hpp"
#include "Responder.hpp"

class Server {
	public:
		Server(const char *port);
		void												run();
	
	private:
		int													_port;
		int 												_server_fd;
		std::map<int, Client>				_clients;
		std::vector<struct pollfd>	_fds;

		Receiver										_Receiver;
		Responder										_Responder;

		void												perror_exit(const char *error);
		void												create_socket();
		void												bind_socket();
		void												listen_socket();
};

#endif
