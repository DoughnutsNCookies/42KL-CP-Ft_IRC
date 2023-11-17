/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Executor.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:34:05 by schuah            #+#    #+#             */
/*   Updated: 2023/11/17 18:04:27 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_HPP
#define EXECUTOR_HPP

#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>

enum TOKEN {
	UNKNOWN = -1,
	PASS = 0,
	NICK = 1,
	USER = 2,
	JOIN = 3,
	PRIVMSG = 4,
	KICK = 5,
	TOPIC = 6
};

class Executor {
	public:
		Executor();
		void		execute(std::vector<std::string> &tokens);
	private:
		TOKEN		_getToken(std::string token);
};

#endif
