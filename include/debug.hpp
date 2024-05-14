/*
** EPITECH PROJECT, 2024
** bottom-up-parser
** File description:
** debug
*/

#ifndef DEBUG_HPP_
#define DEBUG_HPP_

#include <iostream>

#ifdef DEBUG
#define DEBUG_MSG(str) do { std::cout << str << std::endl; } while( false )
#else
#define DEBUG_MSG(str) do { } while ( false )
#endif


#endif /* !DEBUG_HPP_ */
