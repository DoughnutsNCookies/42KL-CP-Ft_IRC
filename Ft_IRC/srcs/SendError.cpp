/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SendError.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:26:43 by plau              #+#    #+#             */
/*   Updated: 2023/11/21 17:42:53 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SendError.hpp"

SendError::SendError() {}

void	SendError::error461(Client& client) {
	client._response = client._nickname + " PASS :Not enough parameters\r\n";
}

void	SendError::error462(Client& client) {
	client._response = client._nickname + " :You may not reregister\r\n";
}

void	SendError::error464(Client& client) {
	client._response = client._nickname + " :Password incorrect\r\n";
}
