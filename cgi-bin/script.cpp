/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   script.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlima <anlima@student.42lisboa.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 18:29:16 by anlima            #+#    #+#             */
/*   Updated: 2024/05/14 18:32:22 by anlima           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Cgi.hpp"

int main(int argc, char **argv) {
    if (argc == 8)
        Cgi cgi(argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7]);
    return (0);
}
