/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pong.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 18:14:17 by schuah            #+#    #+#             */
/*   Updated: 2024/01/08 18:19:41 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PONG_HPP
#define PONG_HPP

#include "Commands/ATokenParser.hpp"

class Pong : public ATokenParser {
	public:
		Pong();
		void	verifyTokens(t_irc& irc, Client& client, tokensVector& tokens);

	private:
		void	_parseTokens(tokensVector& tokens);
		void	_executeCommand(t_irc& irc, Client& client);
};

#endif
