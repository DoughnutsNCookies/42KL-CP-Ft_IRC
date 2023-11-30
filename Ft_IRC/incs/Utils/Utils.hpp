/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 20:27:10 by schuah            #+#    #+#             */
/*   Updated: 2023/11/30 20:38:15 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP

#include "Server/Client.hpp"
#include "Utils/irc.hpp"

class Utils {
	public:
		Utils();
		void						setClientToPollOut(t_irc& irc, Client& client);
		Client&					getClientByNickname(t_irc& irc, std::string nickname);
		Channel&				getChannelByName(t_irc& irc, Client& client, std::string channelName);
		struct pollfd&	getPollfdByFd(t_irc& irc, int fd);
	
		class	NoClientFoundException : public std::exception {
			public:
				virtual const char* what() const throw();
		};

		class	NoChannelFoundException : public std::exception {
			public:
				virtual const char* what() const throw();
		};
		
		class	NoPollfdFoundException : public std::exception {
			public:
				virtual const char* what() const throw();
		};
};

#endif
