/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 22:08:10 by schuah            #+#    #+#             */
/*   Updated: 2023/11/28 12:26:54 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server/Client.hpp"

Client::Client() {}

Client::Client(int fd): _fd(fd), _verified(false), _nickname("client" + std::to_string(fd)) {}
