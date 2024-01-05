/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 16:33:44 by plau              #+#    #+#             */
/*   Updated: 2024/01/05 17:42:41 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOT_HPP
#define BOT_HPP

#include <iostream>
#include "../../incs/Utils/color.hpp"

class Bot {
	public:
		Bot();
		~Bot();
		void	sayHello();
		void	drawPenguin();
};

#endif
