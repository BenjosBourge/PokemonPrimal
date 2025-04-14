/*
** EPITECH PROJECT, 2023
** B-OOP-400-LYN-4-1-rtype-erwann.laplante
** File description:
** gnehehe
*/

#pragma once
#include <exception>
#include <string>

/*
 * This class is used to raise an exception
 *
 * Returns a pointer to a C-style string that contains the error message
 */
class Error : public std::exception {
public:
    Error(std::string const&) noexcept;
    ~Error() noexcept override = default;

    const char* what(void) const noexcept override
    {
        return (this->_msg.c_str());
    }

private:
    std::string _msg;
};
