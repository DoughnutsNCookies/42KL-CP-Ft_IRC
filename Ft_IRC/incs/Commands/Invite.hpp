/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 20:46:40 by schuah            #+#    #+#             */
/*   Updated: 2024/01/11 21:15:32 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INVITE_HPP
#define INVITE_HPP

#include "ATokenParser.hpp"
#include "Utils/SendMsg.hpp"
#include "Utils/Utils.hpp"

class Invite : public ATokenParser {
	public:
		Invite();
		void		verifyTokens(t_irc& irc, Client& client, tokensVector& tokens);

	private:
		std::string	_nickname;
		std::string	_channelName;

		Utils		_Utils;
		SendMsg		_SendMsg;

		void		_parseTokens(tokensVector& tokens);
		void		_executeCommand(t_irc& irc, Client& client);
};

#endif
