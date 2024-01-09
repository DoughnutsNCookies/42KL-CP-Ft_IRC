/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASocketServer.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schuah <schuah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:12:18 by schuah            #+#    #+#             */
/*   Updated: 2024/01/09 14:15:14 by schuah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASOCKETSERVER_HPP
#define ASOCKETSERVER_HPP

class ASocketServer {
	public:
		virtual void	run() = 0;
	private:
		virtual void	_perrorExit(const char *error) = 0;
		virtual void	_createSocket() = 0;
};

#endif
