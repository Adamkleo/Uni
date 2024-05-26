#ifndef FLUIDSIMULATION_GRID_HPP
#define FLUIDSIMULATION_GRID_HPP

#include <vector>
#include <cstdint>
#include <iostream>
#include "Constants.hpp"
#include "particle.hpp"
#include "vector.hpp"
#include "block.hpp"
#include "helpers.hpp"

/**
 * @class Grid
 * @brief Represents the grid structure in a fluid simulation.
 *
 * This class encapsulates the grid used in the fluid simulation,
 * managing the spatial partitioning of particles into blocks,
 * and handling operations like adding particles and retrieving
 * adjacent blocks.
 */
class Grid {
public:
    Vector3D number_of_blocks; ///< Number of blocks in each dimension of the grid.
    std::vector<Block> gridCells; ///< Container for all blocks in the grid.
    int ppm = 0*1;



    Vector3D inverse_size_of_blocks; ///< Size of each block in the grid.
    Vector3D size_of_blocks; ///< Size of each block in the grid.
    //double h_inverse; ///< Coefficient used in calculating grid parameters.
    double h_not_inverse; ///< Coefficient used in calculating grid parameters.

    Vector3D density_constants; ///< Coefficients used in calculating density. .x = H_6, .y = LINEAR_T*m
    Vector3D acceleration_constants; ///< Coefficients used in calculating acceleration. .x = (45*m* STIFFNESS_PREASSURE )/ 2*(PI * H_6), .y = (45*m* STIFFNESS_VISCOSITY )/ (PI * H_6)

    int number_of_particles; ///< Total number of particles in the grid.
    double H_6 = 0*1;
    double LINEAR_T; ///< A coefficient used in particle interactions within the grid.
    double particles_mass; ///< The mass of each particle in the grid.


    Grid(); ///< Constructor initializing the grid with a given inverse smoothing length.

    [[maybe_unused]] void resetGrid(double ppm); ///< Resets the grid with a given inverse smoothing length.

    [[maybe_unused]] void print_grid(); ///< Prints detailed information about the grid and its blocks.

    void addParticle(Particle particle); ///< Adds a particle to the appropriate block in the grid.
    [[maybe_unused]] Block getBlock(Integer3D grid_pos); ///< Retrieves a block from the grid based on its 3D grid position.
    [[nodiscard]] int getBlockIndex(Integer3D grid_pos) const; ///< Retrieves the index of a block in the grid based on its 3D grid position.

    std::vector<int> getAdjacentBlocks(const Block& block); ///< Returns a vector of blocks adjacent to a given block.
    void printGridSummary(); ///< Prints a summary of the grid, such as the number of particles and blocks.

    void updateParticles(); ///< Updates a particle's state based on its position in the grid.

    [[nodiscard]] std::vector<Particle> get_ordered_particles () const;

    void compare(const Grid& other) const;

private:
    [[nodiscard]] Vector3D get_inverse_s_coefficients() const; ///< Calculates and returns inverse coefficients used in grid computations.
    [[nodiscard]] Vector3D get_n_coefficients() const; ///< Calculates and returns coefficients based on the grid's dimensions.
    Integer3D getClosestBlock(Particle& outside_particle) const; ///< Determines the closest block to a given particle.
    void set_grid_blocks(); ///< Initializes and sets up the blocks within the grid.

};

#endif //FLUIDSIMULATION_GRID_HPP
