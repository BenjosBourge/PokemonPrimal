/*
** EPITECH PROJECT, 2023
** B-OOP-400-LYN-4-1-rtype-erwann.laplante
** File description:
** Error
*/

#include <Error/Error.hpp>

/**
 * Construct an Error object with a message.
 */
Error::Error(std::string const& msg) noexcept
    : _msg(msg)
{
}
