/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 18:45:52 by plau              #+#    #+#             */
/*   Updated: 2023/11/21 22:17:05 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PASS_HPP
#define PASS_HPP

#include "ATokenParser.hpp"
#include "Client.hpp"
#include "irc.hpp"
#include "SendError.hpp"

class Pass : public ATokenParser {
	public:
		Pass();
		void				verifyTokens(t_irc& irc, Client& client, tokensVector &tokens);
	
	private:
		std::string	_user_password;
		SendError		_SendError;

		void				_parseTokens(tokensVector &tokens);
		void				_executeCommand(t_irc& irc, Client& client);
};

#endif
