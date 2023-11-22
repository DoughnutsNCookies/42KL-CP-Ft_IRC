/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plau <plau@student.42.kl>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 13:33:31 by plau              #+#    #+#             */
/*   Updated: 2023/11/22 17:36:15 by plau             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef USER_HPP
# define USER_HPP

#include "ATokenParser.hpp"
#include "SendError.hpp"

class User : public ATokenParser {
	public:
		User();
		void				verifyTokens(t_irc& irc, Client& client, tokensVector &tokens);

	private:
		std::string _username;
		std::string _realname;

		SendError		_SendError;

		void				_parseTokens(tokensVector &tokens);
		void				_executeCommand(t_irc& irc, Client& client);
};

#endif
