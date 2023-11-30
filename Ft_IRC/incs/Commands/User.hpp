/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 13:33:31 by plau              #+#    #+#             */
/*   Updated: 2023/11/30 21:52:24 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
#define USER_HPP

#include "Commands/ATokenParser.hpp"
#include "Utils/SendMsg.hpp"

class User : public ATokenParser {
	public:
		User();
		void				verifyTokens(t_irc& irc, Client& client, tokensVector &tokens);

	private:
		std::string _username;
		std::string _realname;

		SendMsg			_SendMsg;

		void				_parseTokens(tokensVector &tokens);
		void				_executeCommand(t_irc& irc, Client& client);
};

#endif
