//
// Created by Carlos Barboza on 14/10/23.
//

#include <iostream>
#include "Fluid_simulation.hpp"
#include "Grid.hpp"
//#include "helpers.hpp"  //Uncomment for print use
#include <utility>



FluidSimulation::FluidSimulation(Grid  grid, int number_of_steps) : grid(std::move(grid)), number_of_steps(number_of_steps), current_step(0){}


void FluidSimulation::simulate() {
    std::cout << "Simulation started" << '\n';
    for (int i = 0; i < number_of_steps; ++i) {
        //std::cout <<"..................................................." <<"Step " << i << "..................................................." << '\n';
        simulateLogic();
        current_step++;
    }
    std::cout << "Simulation finished" << '\n';
}



void FluidSimulation::simulateLogic() {
    // Iterate through the grid to update their densities
    // End time

    grid.updateParticles();
    // Uncoment the following lines to test up to block repositioning (Works for any number of steps)
    /*
    if (current_step == number_of_steps - 1) [[unlikely]]{
        return;
    }
     */

    //print("---------------------------- Density logic ----------------------------");
    update_densities();
    //Uncomment the following lines to test up to density linear transform (Works for any number of steps)
    /*
        if (current_step == number_of_steps - 1){
            return;
        }
     */
    //print("---------------------------- Acceleration logic ----------------------------");
    update_accelerations();
}

void FluidSimulation::update_densities() {
    for (auto & gridCell : grid.gridCells) {
        // Update particles if there are any
        if (!gridCell.particles.empty()) {
            adjacent_density_updater(gridCell);
            update_inner_densities(gridCell);
        }
        gridCell.status = 0;
    }
}

void FluidSimulation::update_accelerations() {
    for (auto & gridCell : grid.gridCells) {
        // Update particles if there are any
        if (!gridCell.particles.empty()) {
            adjacent_acceleration_updater(gridCell);
            update_inner_accelerations(gridCell);
        }
        gridCell.status = 0;
    }
}


void FluidSimulation::adjacent_density_updater(Block & current_block) {
    adjacentBlocks = grid.getAdjacentBlocks(current_block); /// Adjacent blocks return only non updated blocks (in correlation)
    // The same block is not adjacent to itself (for this case)
    // We iterate through the adjacent blocks
    for (auto & adjacent_block : adjacentBlocks) {
        // And for each particle in the adjacent block, we update the current block's particles
        for (auto &adj_particle: grid.gridCells[adjacent_block].particles) {
            for (auto &particle: current_block.particles) {
                particle.calculateDensityIncrease(adj_particle, grid.density_constants);
            }
        }
        grid.gridCells[adjacent_block].status += grid.gridCells[adjacent_block].id.get_relative_mask(
                current_block.id);

    }

}

void FluidSimulation::update_inner_densities(Block &current_block) const {
    // Here all particles inside the block have already been updated with the particles in adjacent blocks
    // We update the particles with the others inside the same block
    for (size_t i = 0; i < current_block.particles.size(); ++i) {
        for (size_t j = i + 1; j < current_block.particles.size(); ++j) {
            current_block.particles[i].calculateDensityIncrease(current_block.particles[j], grid.density_constants);
        }
        current_block.particles[i].linear_transform(grid.H_6, grid.LINEAR_T);
        current_block.particles[i].toBeRemoved = false;
    }

}




void FluidSimulation::adjacent_acceleration_updater(Block &current_block) {
    adjacentBlocks = grid.getAdjacentBlocks(current_block); /// Adjacent blocks return only non updated blocks (in correlation)
    //print("Updating block: ", current_block.id);
    for (auto & adjacent_block : adjacentBlocks) {
        //print("---------Updating with: ", grid.gridCells[adjacent_block].id);
        //print(grid.gridCells[adjacent_block].id);
        // And for each particle in the adjacent block, we update the current block's particles
        for (auto &adj_particle: grid.gridCells[adjacent_block].particles) {
            for (auto &particle: current_block.particles) {
                particle.updateAcceleration(adj_particle, grid.acceleration_constants);
            }
        }
        grid.gridCells[adjacent_block].status += grid.gridCells[adjacent_block].id.get_relative_mask(
                current_block.id);
        //print("Changed status of block: ", grid.gridCells[adjacent_block].id, " to: ",
        //grid.gridCells[adjacent_block].status);
    }


}


void FluidSimulation::update_inner_accelerations(Block & current_block) const{
    if (current_block.blockIsBoundary(grid.number_of_blocks)){
         Vector3D const mask = current_block.maskBoundary(grid.number_of_blocks);
        for (size_t i = 0; i < current_block.particles.size(); ++i) {
            for (size_t j = i + 1 ; j < current_block.particles.size(); ++j) {
                current_block.particles[i].updateAcceleration(current_block.particles[j], grid.acceleration_constants);
            }
            current_block.particles[i].carefulUpdate(mask, grid.inverse_size_of_blocks, grid.number_of_blocks);
            // // Here is where the new block's index is calculated
            if (current_block.particles[i].changed_block != current_block.index){
                current_block.particles[i].toBeRemoved = true;
            }
        }
    }else{
        for (size_t i = 0; i < current_block.particles.size(); ++i) {
            for (size_t j = i + 1; j < current_block.particles.size(); ++j) {
                current_block.particles[i].updateAcceleration(current_block.particles[j], grid.acceleration_constants);
            }
            current_block.particles[i].update(grid.inverse_size_of_blocks, grid.number_of_blocks); // Here is where the new block's index is calculated
            if (current_block.particles[i].changed_block != current_block.index){
                current_block.particles[i].toBeRemoved = true;
            }
        }
    }
}








