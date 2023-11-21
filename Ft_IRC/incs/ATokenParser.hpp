/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ATokenParser.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 16:30:22 by plau              #+#    #+#             */
/*   Updated: 2023/11/21 20:22:45 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENPARSER_HPP
#define TOKENPARSER_HPP

#include <vector>
#include <string>

typedef std::vector<std::string>	tokensVector;

class ATokenParser {
	private:
		virtual void	_parseTokens(tokensVector &tokens) = 0;
};

#endif
