/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 18:45:52 by plau              #+#    #+#             */
/*   Updated: 2023/11/29 21:19:35 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PASS_HPP
#define PASS_HPP

#include "Commands/ATokenParser.hpp"
#include "Server/Client.hpp"
#include "Utils/irc.hpp"
#include "Utils/SendMsg.hpp"

class Pass : public ATokenParser {
	public:
		Pass();
		void				verifyTokens(t_irc& irc, Client& client, tokensVector& tokens);
	
	private:
		std::string	_userPassword;
		SendMsg			_SendMsg;

		void				_parseTokens(tokensVector& tokens);
		void				_executeCommand(t_irc& irc, Client& client);
};

#endif
