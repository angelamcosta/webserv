/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:46:03 by anlima            #+#    #+#             */
/*   Updated: 2024/04/17 15:01:59 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

int main(void)
{
    int server_socket;

	server_socket = create_server_socket();
	if (!start_server(server_socket))
		return (0);
	std::cout << LAVENDER << HEART << CLEAR << MINT << " Welcome to webserv! " << CLEAR << LAVENDER << HEART << CLEAR << std::endl;
	std::cout << LAVENDER << "Go to " << CLEAR << SKYBLUE << "localhost:8080" << CLEAR << LAVENDER " to check it out! " << CLEAR << std::endl;
	while (1)
	{
		int client_socket = accept(server_socket, NULL, NULL);
		create_process(server_socket, client_socket);
	}
	close(server_socket);

	return (0);
}
