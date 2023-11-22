/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:49:15 by plau              #+#    #+#             */
/*   Updated: 2023/11/22 17:24:29 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NICK_HPP
# define NICK_HPP

#include "ATokenParser.hpp"
#include "irc.hpp"
#include "SendError.hpp"

class Nick : public ATokenParser {
	public:
		Nick();
		void				verifyTokens(t_irc& irc, Client& client, tokensVector& tokens);
	
	private:
		std::string _nick_name;
		
		SendError		_SendError;

		void				_parseTokens(tokensVector& tokens);
		void				_executeCommand(t_irc& irc, Client& client);
		bool				_checkValidNickName(std::string nickName);
};

#endif
