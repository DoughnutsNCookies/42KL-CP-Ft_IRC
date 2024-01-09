/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASocketServer.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:12:18 by schuah            #+#    #+#             */
/*   Updated: 2024/01/09 14:56:18 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASOCKETSERVER_HPP
#define ASOCKETSERVER_HPP

#include <iostream>
#include <netdb.h>

#include "Utils/irc.hpp"

class ASocketServer {
	public:
		virtual void	run() = 0;
		
	protected:
		t_irc			_irc;

		void			_perrorExit(const char *error);
		void			_createSocket();
};

#endif