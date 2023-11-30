/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 20:24:15 by schuah            #+#    #+#             */
/*   Updated: 2023/11/30 20:55:30 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server/Channel.hpp"

Channel::Channel() {}

Channel::Channel(std::string channelName, std::string opName): name(channelName), opName(opName) {}
