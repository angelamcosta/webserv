/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stack.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedroso <mpedroso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:45:51 by mpedroso          #+#    #+#             */
/*   Updated: 2024/08/27 16:17:51 by mpedroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Stack.hpp"

Stack::Stack() {this->server = 0;}

void    Stack::addToStack() {
	this->server = 1;
}

void    Stack::addToStack(Location &location) {
	this->locations.push_back(location);
}

void	Stack::remove() {
	if (!this->locations.empty())
		this->locations.pop_back();
	this->server = 0;
}

int     Stack::getType() {
	if (!this->locations.empty())
		return 1;
	return 0;
}

Location& Stack::getLocation() {
	return this->locations.back();
}

Stack::~Stack() {}