/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Directive.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:26:27 by anlima            #+#    #+#             */
/*   Updated: 2024/04/23 16:14:15 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Directive.hpp"

Directive::~Directive() {}
Directive::Directive(const Directive& copy)
{
    _name = copy.getName();
    _value = copy.getValue();
}

Directive &Directive::operator=(const Directive &copy)
{
    if (this != &copy)
    {
        _name = copy.getName();
        _value = copy.getValue();
    }
    return (*this);
}

Directive::Directive(const std::string &name, const std::string value) : _name(name), _value(value) {}

const std::string &Directive::getName(void) const { return (_name); }
const std::string &Directive::getValue(void) const { return (_value); }
