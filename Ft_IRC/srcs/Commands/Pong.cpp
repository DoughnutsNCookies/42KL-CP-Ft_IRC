/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pong.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 18:14:16 by schuah            #+#    #+#             */
/*   Updated: 2024/01/08 18:18:48 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands/Pong.hpp"

Pong::Pong() {}

void	Pong::verifyTokens(t_irc& irc, Client& client, tokensVector& tokens) {
	(void)irc;
	(void)client;
	(void)tokens;
}

void	Pong::_parseTokens(tokensVector& tokens) {
	(void)tokens;
}

void	Pong::_executeCommand(t_irc& irc, Client& client) {
	(void)irc;
	(void)client;
}
