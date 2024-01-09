/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 16:33:44 by plau              #+#    #+#             */
/*   Updated: 2024/01/09 16:51:52 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOT_HPP
#define BOT_HPP

#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <fstream>

#include "Server/ASocketServer.hpp"
#include "Server/Responder.hpp"
#include "Utils/Utils.hpp"
#include "Utils/irc.hpp"
#include "Utils/color.hpp"

class Bot : public ASocketServer {
	public:
		Bot(const char* hostname, const char* port, const char* password, const char* targetNickname);
		void		run();
	
	private:
		std::string	_target;

		Responder	_responder;
		Client		_serverClient;

		void		_connectToServer();
		void		_register();
		void		_sendPenguin(std::string filePath);
};

#endif
