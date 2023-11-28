/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 21:08:33 by schuah            #+#    #+#             */
/*   Updated: 2023/11/28 18:11:02 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_HPP
#define IRC_HPP

#include <string>
#include <map>
#include <vector>

#include "Server/Client.hpp"

typedef struct s_irc {
	int													port;
	int 												serverFd;
	std::string									password;
	std::string									hostname;
	std::map<int, Client>				clients;
	std::vector<struct pollfd>	fds;
}	t_irc;

#endif
