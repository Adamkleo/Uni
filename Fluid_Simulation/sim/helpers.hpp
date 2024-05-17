//
// Created by Carlos Barboza on 17/11/23.
//

#ifndef FLUID_HELPERS_HPP
#define FLUID_HELPERS_HPP
#include <iostream>
#include <iomanip>

template<typename... Args>
void print(Args... args) {
    std::cout << std::setprecision(std::numeric_limits<double>::max_digits10);
    (std::cout << ... << args) << std::endl;
}


#endif //FLUID_HELPERS_HPP
