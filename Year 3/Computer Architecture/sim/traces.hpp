//
// Created by Carlos Barboza on 20/11/23.
//

#ifndef FLUID_TRACES_HPP
#define FLUID_TRACES_HPP
#include <iostream>
#include <fstream>
#include "Grid.hpp"
#include "helpers.hpp"

void check_trace(std::string trz, Grid &grid){

    std::filesystem::path currentPath = std::filesystem::current_path();
    currentPath /= "trz";
    currentPath /=trz;  // append filename to the current directory
    std::ifstream file(trz, std::ios::binary);

    if (!file.is_open()) { //Check error opening
        std::cout<<"Error: Cannot open trace file: " << trz <<" for reading";
        exit (-1);
    }
    int num_blocks = 0;
    file.read(reinterpret_cast<char*>(&num_blocks), sizeof(int));//NOLINT
    long particles_in_block = 0;
    long id_ = 0;
    Particle part;
    //Vector3D const a(0,0,0); //Por qué da error?
    double write_value = 0;
    for (int j = 0; j < num_blocks; j++) {

        file.read(reinterpret_cast<char*>(&particles_in_block), sizeof(long));//NOLINT

        for (int i = 0; i < particles_in_block;i++){

            file.read(reinterpret_cast<char*>(&id_), sizeof(long));//NOLINT
            //Particle part_in_our_grid = find_elem(id_,current_block);
            //std::cout<<"Particle "<<part_in_our_grid.id_<<" in block["<<"] : ";
            part.id = reinterpret_cast<long>(id_); //NOLINT
            file.read(reinterpret_cast<char*>(&write_value), sizeof(double)); //NOLINT
            part.position.x = static_cast<double>(write_value);

            file.read(reinterpret_cast<char*>(&write_value), sizeof(double));//NOLINT
            part.position.y = static_cast<double>(write_value);

            file.read(reinterpret_cast<char*>(&write_value),sizeof(double));//NOLINT
            part.position.z = static_cast<double>(write_value);

            file.read(reinterpret_cast<char*>(&write_value), sizeof(double));//NOLINT
            part.gradient.x = static_cast<double>(write_value);

            file.read(reinterpret_cast<char*>(&write_value), sizeof(double));//NOLINT
            part.gradient.y = static_cast<double>(write_value);

            file.read(reinterpret_cast<char*>(&write_value), sizeof(double));//NOLINT
            part.gradient.z = static_cast<double>(write_value);

            file.read(reinterpret_cast<char*>(&write_value), sizeof(double));//NOLINT
            part.velocity.x = static_cast<double>(write_value);
            file.read(reinterpret_cast<char*>(&write_value), sizeof(double));//NOLINT
            part.velocity.y = static_cast<double>(write_value);
            file.read(reinterpret_cast<char*>(&write_value), sizeof(double));//NOLINT
            part.velocity.z = static_cast<double>(write_value);
            file.read(reinterpret_cast<char*>(&write_value), sizeof(double));//NOLINT
            part.density = write_value;
            file.read(reinterpret_cast<char*>(&write_value), sizeof(double));//NOLINT
            part.acceleration.x = write_value;
            file.read(reinterpret_cast<char*>(&write_value), sizeof(double));//NOLINT
            part.acceleration.y = write_value;
            file.read(reinterpret_cast<char*>(&write_value), sizeof(double));//NOLINT
            part.acceleration.z = write_value;

            grid.addParticle(part);

        }
    }
    std::cout<<"\nTrace is equal to current state of the simulation\n";
    file.close();
}
#endif //FLUID_TRACES_HPP
