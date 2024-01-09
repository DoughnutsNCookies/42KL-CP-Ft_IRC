/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:46:47 by schuah            #+#    #+#             */
/*   Updated: 2024/01/09 17:06:45 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <poll.h>
#include <vector>
#include <string>

typedef std::vector<std::string>	tokensVector;

class Client {
	public:
		Client();
		Client(int clientFd, std::string clientHostname);

		int 			fd;
		bool			verified;
		bool			nickSet;
		bool			userSet;
		bool			joined;
		std::string		response;
		std::string		buffer;
		std::string		nickname;
		std::string		username;
		std::string		realname;
		std::string 	hostname;
		tokensVector	channels;
};

#endif
