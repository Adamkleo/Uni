//
// Created by Carlos Barboza on 14/10/23.
//

#ifndef FLUID_FLUID_SIMULATION_HPP
#define FLUID_FLUID_SIMULATION_HPP

#include "Grid.hpp"
#include <iostream>

class FluidSimulation{
public:
    Grid grid;

    FluidSimulation(Grid  grid, int number_of_steps);
    void simulate();

private:
    int number_of_steps;
    int current_step;
    std::vector<int> adjacentBlocks;
    void simulateLogic();
    
    void adjacent_density_updater(Block & current_block);
    void update_inner_densities(Block & current_block) const;
    void update_densities();


    void adjacent_acceleration_updater(Block & current_block);
    void update_inner_accelerations(Block & current_block) const;
    void update_accelerations();




};

#endif //FLUID_FLUID_SIMULATION_HPP
