/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 21:08:33 by schuah            #+#    #+#             */
/*   Updated: 2024/01/08 16:50:15 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_HPP
#define IRC_HPP

#include <string>
#include <map>
#include <vector>

#include "Server/Client.hpp"
#include "Server/Channel.hpp"

typedef struct s_irc {
	int								port;
	int 							serverFd;
	std::string						password;
	std::string						hostname;
	std::string						version;
	std::string						userModes;
	std::string						channelModes;
	std::string						channelModesWithParam;
	std::string						supportTokens;
	std::map<int, Client>			clients;
	std::map<std::string, Channel>	channels;
	std::vector<struct pollfd>		fds;
}	t_irc;

#endif
