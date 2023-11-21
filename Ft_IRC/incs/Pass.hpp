/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 18:45:52 by plau              #+#    #+#             */
/*   Updated: 2023/11/21 20:20:44 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PASS_HPP
#define PASS_HPP

#include "TokenParser.hpp"
#include "Client.hpp"
#include "irc.hpp"
#include "SendError.hpp"

class Pass : public ATokenParser {
	public:
		Pass();
		void				verify(t_irc& irc, Client& client, tokensVector &tokens);
	
	private:
		std::string	_user_password;
		SendError		_SendError;

		void				_parseTokens(tokensVector &tokens);
};

#endif
