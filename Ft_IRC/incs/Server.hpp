/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:42:42 by schuah            #+#    #+#             */
/*   Updated: 2023/11/16 14:26:40 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

#include "ft_irc.hpp"

class Server {
	public:
		Server(const char *port);
		~Server();
		void												run();
	
	private:
		int													_port;
		int 												_server_fd;
		std::map<int, Client>				_clients;
		std::vector<struct pollfd>	_fds;

		void												perror_exit(const char *error);
		void												create_socket();
		void												bind_socket();
		void												listen_socket();
};

#endif
