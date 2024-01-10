/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Names.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 22:14:07 by plau              #+#    #+#             */
/*   Updated: 2024/01/10 22:15:45 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NAMES_HPP
#define NAMES_HPP

#include "ATokenParser.hpp"

class Names : public ATokenParser {
	public:
		Names();
		void	verifyTokens(t_irc& irc, Client& client, tokensVector& tokens);

	private:
		void	_parseTokens(tokensVector& tokens);
		void	_executeCommand(t_irc& irc, Client& client);
};

#endif
