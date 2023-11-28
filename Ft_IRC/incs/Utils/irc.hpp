/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 21:08:33 by schuah            #+#    #+#             */
/*   Updated: 2023/11/28 12:26:29 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_HPP
#define IRC_HPP

#include <string>
#include <map>
#include <vector>

#include "Server/Client.hpp"

typedef struct s_irc {
	int													_port;
	int 												_serverFd;
	std::string									_password;
	std::map<int, Client>				_clients;
	std::vector<struct pollfd>	_fds;
}	t_irc;

#endif
