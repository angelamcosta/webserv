/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Directive.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:09:44 by anlima            #+#    #+#             */
/*   Updated: 2024/05/09 17:14:10 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIRECTIVE_HPP
#define DIRECTIVE_HPP

#include "macros.hpp"

class Directive {
  private:
    std::string _name;
    std::string _value;
    Directive();

  public:
    ~Directive();
    Directive(const Directive &copy);
    Directive &operator=(const Directive &copy);
    Directive(const std::string &name, const std::string value);

    const std::string &getName(void) const;
    const std::string &getValue(void) const;
};

#endif
