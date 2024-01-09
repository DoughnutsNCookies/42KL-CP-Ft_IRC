/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 20:24:15 by schuah            #+#    #+#             */
/*   Updated: 2024/01/09 05:28:33 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server/Channel.hpp"

Channel::Channel() {}

Channel::Channel(std::string channelName, std::string operatorName): name(channelName), opName(operatorName) {}
