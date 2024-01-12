/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 22:08:10 by schuah            #+#    #+#             */
/*   Updated: 2024/01/12 08:48:26 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server/Client.hpp"

Client::Client() {}

Client::Client(int clientFd, std::string clientHostname): fd(clientFd), verified(false), nickSet(false), userSet(false), hostname(clientHostname) {
    std::ostringstream  stream;
    stream << clientFd;
    this->nickname = "client" + stream.str();
}
