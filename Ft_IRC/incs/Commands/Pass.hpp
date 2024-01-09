/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 18:45:52 by plau              #+#    #+#             */
/*   Updated: 2024/01/04 21:32:49 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PASS_HPP
#define PASS_HPP

#include "Commands/ATokenParser.hpp"
#include "Server/Client.hpp"
#include "Utils/irc.hpp"
#include "Utils/SendMsg.hpp"
#include "Utils/Utils.hpp"

class Pass : public ATokenParser {
	public:
		Pass();
		void		verifyTokens(t_irc& irc, Client& client, tokensVector& tokens);
	
	private:
		std::string	_userPassword;
		
		SendMsg		_SendMsg;
		Utils		_Utils;

		void		_parseTokens(tokensVector& tokens);
		void		_executeCommand(t_irc& irc, Client& client);
};

#endif
