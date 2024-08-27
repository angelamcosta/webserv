/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedroso <mpedroso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:13:04 by mpedroso          #+#    #+#             */
/*   Updated: 2024/08/27 16:17:59 by mpedroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include "Server.hpp"
# include "Location.hpp"
# include "macros.hpp"
# include <vector>

class Stack
{
private:

    int server;
    std::vector<Location>   locations;

public:
    Stack();
    void    addToStack();
    void    addToStack(Location &location);
    void    remove();
    int     getType();
    Location&   getLocation();
    ~Stack();
};

#endif