/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 22:08:10 by schuah            #+#    #+#             */
/*   Updated: 2024/01/09 15:55:52 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server/Client.hpp"

Client::Client() {}

Client::Client(int clientFd, std::string clientHostname): fd(clientFd), verified(false), nickSet(false), userSet(false), nickname("client" + std::to_string(fd)), hostname(clientHostname) {}
