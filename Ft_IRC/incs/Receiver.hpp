/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Receiver.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:22:58 by schuah            #+#    #+#             */
/*   Updated: 2023/11/17 16:23:04 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef Receiver_HPP
#define Receiver_HPP

#include <vector>
#include <poll.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include <map>

#include "color.hpp"
#include "Client.hpp"

class Receiver
{
public:
	Receiver();
	void new_connection(int server_fd, std::vector<struct pollfd> &fds, std::map<int, Client> &clients);
	void receive(std::map<int, Client> &clients, std::vector<struct pollfd> &fds, int i);

private:
	void perror_exit(const char *error);
};

#endif
