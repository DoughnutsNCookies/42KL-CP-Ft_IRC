/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 22:08:10 by schuah            #+#    #+#             */
/*   Updated: 2024/01/08 17:09:58 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server/Client.hpp"

Client::Client() {}

Client::Client(int fd, std::string hostname): fd(fd), verified(false), nickSet(false), userSet(false), nickname("client"), hostname(hostname) {}
