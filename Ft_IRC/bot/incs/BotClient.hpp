/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BotClient.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 18:21:57 by plau              #+#    #+#             */
/*   Updated: 2024/01/05 18:24:59 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BotClient_HPP
#define BotClient_HPP

#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

class BotClient
{
	public:
		BotClient();
		~BotClient();
		int		createSocket();
		void	connectToServer(int port);
		void	sendClientDetails();
		void	closeSocket();
	private:
		int		clientSocket;
		
};

#endif
