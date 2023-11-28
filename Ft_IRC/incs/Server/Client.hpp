/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 13:46:47 by schuah            #+#    #+#             */
/*   Updated: 2023/11/28 18:09:12 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <poll.h>
#include <string>

class Client {
	public:
		Client();
		Client(int fd, std::string hostname);

		int 				fd;
		bool				verified;
		std::string	response;
		std::string	buffer;
		std::string	nickname;
		std::string	username;
		std::string	realname;
		std::string hostname;
};

#endif
