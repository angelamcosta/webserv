/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_funcs.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:31:01 by anlima            #+#    #+#             */
/*   Updated: 2024/04/23 14:32:20 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/webserv.hpp"

void    welcome_text(void);

void    welcome_text(void)
{
    std::cout << LAVENDER << HEART << CLEAR << MINT;
    std::cout << " Welcome to webserv! " << CLEAR;
    std::cout << LAVENDER << HEART << CLEAR << std::endl;
	std::cout << LAVENDER << "Go to " << CLEAR;
    std::cout << SKYBLUE << "localhost:8080" << CLEAR;
    std::cout << LAVENDER " to check it out! " << CLEAR << std::endl;
}
