/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 21:08:33 by schuah            #+#    #+#             */
/*   Updated: 2024/01/05 17:19:07 by plau             ###   ########.fr       */
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
	std::map<int, Client>			clients;
	std::map<std::string, Channel>	channels;
	std::vector<struct pollfd>		fds;
}	t_irc;

#endif
