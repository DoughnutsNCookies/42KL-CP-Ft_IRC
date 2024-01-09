/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 16:33:44 by plau              #+#    #+#             */
/*   Updated: 2024/01/09 14:16:49 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOT_HPP
#define BOT_HPP

#include <iostream>

#include "ASocketServer.hpp"
#include "Utils/Utils.hpp"

class Bot : public ASocketServer {
	public:
		Bot();
		~Bot();
		void	sayHello();
		void	drawPenguin();
};

#endif
