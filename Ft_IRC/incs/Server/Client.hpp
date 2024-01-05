/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:46:47 by schuah            #+#    #+#             */
/*   Updated: 2024/01/05 17:18:12 by plau             ###   ########.fr       */
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
		Client(int fd, std::string hostname);

		int 			fd;
		bool			verified;
		std::string		response;
		std::string		buffer;
		std::string		nickname;
		std::string		username;
		std::string		realname;
		std::string 	hostname;
		tokensVector	channels;
};

#endif
