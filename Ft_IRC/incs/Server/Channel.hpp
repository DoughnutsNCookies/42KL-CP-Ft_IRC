/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 20:23:51 by schuah            #+#    #+#             */
/*   Updated: 2023/11/30 20:54:54 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <map>
#include <string>

#include "Server/Client.hpp"

class Channel {
	public:
		Channel();
		Channel(std::string channelName, std::string opName);

		std::string										name;
		std::string										topic;
		std::string										opName;
		std::map<std::string, Client>	users;
};

#endif
