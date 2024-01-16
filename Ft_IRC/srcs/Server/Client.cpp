/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 22:08:10 by schuah            #+#    #+#             */
/*   Updated: 2024/01/16 21:33:29 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server/Client.hpp"

Client::Client() {}

Client::Client(int clientFd, std::string clientHostname): fd(clientFd), verified(false), nickSet(false), userSet(false), bypassCheck(false), hostname(clientHostname) {
    std::ostringstream  stream;
    stream << clientFd;
    this->nickname = "client" + stream.str();
}
