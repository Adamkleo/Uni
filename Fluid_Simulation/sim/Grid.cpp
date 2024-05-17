#include "Grid.hpp"
#include "block.hpp"
#include "Constants.hpp"
#include <vector>
#include <iostream>
#include <cmath>
#include "helpers.hpp"
#include <unordered_map>

/**
 * @brief Constructor for the Grid class.
 * @param h_inverse Inverse of the smoothing length used in grid calculations.
 *
 * Initializes the grid with given parameters, sets up the grid blocks based on
 * the size of the grid and the number of blocks.
 */
Grid::Grid()
        : h_not_inverse(0), number_of_particles(0), LINEAR_T(0), particles_mass(0) {
    number_of_blocks = get_n_coefficients();
    inverse_size_of_blocks = get_inverse_s_coefficients();
    size_of_blocks = {0,0,0};
    set_grid_blocks();
}

void Grid::resetGrid(double ppm_other){
    ppm = static_cast<int>(ppm_other);
    h_not_inverse = RADIUS_MULTIPLIER / ppm;
    double const ppm3 = ppm * ppm * ppm;
    particles_mass = FLUID_DENSITY / ppm3;
    number_of_blocks = get_n_coefficients();
    double upper = T_315;//  * particles_mass;
    double const lower = T_64 * PI * pow(h_not_inverse, T_9);
    LINEAR_T = upper / lower;
    LINEAR_T *= particles_mass;
    H_6 = h_not_inverse * h_not_inverse * h_not_inverse * h_not_inverse * h_not_inverse * h_not_inverse;
    double const second_lower = PI * H_6;
    upper =  particles_mass * VISCOSITY;
    double const second_acc_term = (T_45 / second_lower) * upper;
    double const lower_first = PI * H_6;
    double const upper_second = T_3 * particles_mass * STIFFNESS_PRESSURE;
    double const first_acc_term = (T_15 / lower_first) * (upper_second / T_2);
    double const h_squared = h_not_inverse * h_not_inverse;
    density_constants = {H_6, LINEAR_T, h_squared};
    acceleration_constants = {first_acc_term, second_acc_term, h_not_inverse};
    inverse_size_of_blocks = get_inverse_s_coefficients(); // We don't mind the loss of precision here as we only care for a small number of decimal places.
    // In case of a huge amount of block this would be a problem, but that number of blocks would be unfeasible to simulate anyway.
    size_of_blocks = {1/inverse_size_of_blocks.x, 1/inverse_size_of_blocks.y, 1/inverse_size_of_blocks.z}; // Slower constructor faster simulation
    set_grid_blocks();
}

/**
 * @brief Prints detailed information about the grid and its blocks.
 *
 * Iterates through each cell (block) of the grid and prints its details if it contains particles.
 */
[[maybe_unused]] void Grid::print_grid() {
    std::cout << "Printing grid" << '\n';
    for (auto & gridCell : gridCells) {
        if (!gridCell.particles.empty()) {
            print(getBlockIndex(gridCell.id));
            Vector3D const block_position = {(gridCell.id.x * size_of_blocks.x) + B_MIN.x, (gridCell.id.y * size_of_blocks.y) + B_MIN.y, (gridCell.id.z * size_of_blocks.z) + B_MIN.z};
            Vector3D const upper_corner = block_position + size_of_blocks;
            print("Blocks goes from ", block_position, " to ", upper_corner);
            print(gridCell); // Prints the block if it contains particles.
        }
    }
}

/**
 * @brief Adds a particle to the appropriate block in the grid.
 * @param particle The particle to be added.
 */
void Grid::addParticle(Particle particle) {
    Integer3D grid_position = particle.get_grid_position(inverse_size_of_blocks);
    int index = static_cast<int>(grid_position.x + number_of_blocks.x * (grid_position.y + number_of_blocks.y * grid_position.z));

    if ((grid_position < 0).not_zero()){
        /*
        print("Out of bounds, on the bottom");
        print("Previous position: ",particle.position);
        print ("Previous virtual block: ",grid_position);

         */
        grid_position = getClosestBlock(particle);
        index = static_cast<int>(grid_position.x + number_of_blocks.x * (grid_position.y + number_of_blocks.y * grid_position.z));

    }
    if ((grid_position >= number_of_blocks).not_zero()){
        grid_position = getClosestBlock(particle);
        index = static_cast<int>(grid_position.x + number_of_blocks.x * (grid_position.y + number_of_blocks.y * grid_position.z));
        /*
        print("Final position: ",particle.position);
        print("Final block: ",grid_position);
         */
    }
    gridCells[index].addParticle(particle);
    number_of_particles++;
}

/**
 * @brief Retrieves a block from the grid based on its 3D grid position.
 * @param grid_pos The 3D integer position of the block in the grid.
 * @return The Block at the specified grid position.
 */
[[maybe_unused]] Block Grid::getBlock(Integer3D grid_pos) {
    int const blockIndex = static_cast<int>(grid_pos.x + grid_pos.y * number_of_blocks.x + grid_pos.z * number_of_blocks.x * number_of_blocks.y);

    const int size = static_cast<int>(gridCells.size());
    if (blockIndex >= 0 && blockIndex < size) {
        return gridCells[blockIndex];
    }
    std::cerr << "Error: Requested block out of grid bounds!" << '\n';
    return {};  // return an empty block
}


/**
 * @brief Returns a vector of blocks adjacent to a given block.
 * @param block The reference block.
 * @return A vector of adjacent Block objects.
 */
std::vector<int> Grid::getAdjacentBlocks(const Block& block) {
    std::vector<int> adjacentBlocks;
    Integer3D adj_id{};
    for (int i = -1; i <= 1; i++) {
        int const n_x = block.id.x + i;
        if (n_x < 0 || n_x >= number_of_blocks.x) { continue;}
        for (int j = -1; j <= 1; j++) {
            int const n_y = block.id.y + j;
            if (n_y < 0 || n_y >= number_of_blocks.y) { continue;}
            for (int k = -1; k <= 1; k++) {
                int const n_z = block.id.z + k;
                if (n_z < 0 || n_z >= number_of_blocks.z) { continue;}
                adj_id = {n_x, n_y, n_z};
                int const mask = block.id.get_relative_mask(adj_id);
                if ((block.status & mask) == mask || block.id == adj_id) {continue;}
                int const blockIndex = getBlockIndex(adj_id);
                if (gridCells[blockIndex].isNotEmpty()) {
                    adjacentBlocks.push_back(blockIndex);
                }
            }
        }
    }
    return adjacentBlocks;
}




/**
 * @brief Prints a summary of the grid, such as the number of particles and blocks.
 */
void Grid::printGridSummary() {
    std::cout << "\n*******************************+\n";
    std::cout << "Printing grid summary\n";
    std::cout << "Number of blocks: " << number_of_blocks.x << " " << number_of_blocks.y << " " << number_of_blocks.z << "\n";
    std::cout << "Size of blocks: " << size_of_blocks.x << " " << size_of_blocks.y << " " << size_of_blocks.z << "\n";
    std::cout << "Block go from: " << B_MIN.x << " " << B_MIN.y << " " << B_MIN.z << " to " << B_MAX.x << " " << B_MAX.y << " " << B_MAX.z << "\n";
    gridCells[0].printBlock();
    std::cout << "First block old_id: " << gridCells[0].id.x << " " << gridCells[0].id.y << " " << gridCells[0].id.z << "\n";
    std::cout << "Last block old_id: " << gridCells[gridCells.size()-1].id.x << " " << gridCells[gridCells.size() - 1].id.y << " " << gridCells[gridCells.size() - 1].id.z << "\n";
    std::cout << "Number of particles: " << number_of_particles << "\n";
    std::cout << "*******************************+\n";
}

/**
Grid& Grid::operator=(const Grid& other) {
    B_MIN = other.B_MIN;
    B_MAX = other.B_MAX;
    number_of_blocks = other.number_of_blocks;
    inverse_size_of_blocks = other.inverse_size_of_blocks;
    h_inverse = other.h_inverse;
    gridCells = other.gridCells;
    number_of_particles = other.number_of_particles;
    return *this;
}
 **/

// Private member functions

/* Motivation: Because we will need to divide a lot by s
 * we instead retrieve the inverse of s, so we can multiply
 * this reduces the overhead for the division operation
 *
 * Takes the number of blocks and the size of the grid
 * returns a vector with the inverse elements s would have
 *
 * Will only be called from the constructor
 */
Vector3D Grid::get_inverse_s_coefficients() const {
    double const s_x =  number_of_blocks.x /(B_MAX.x - B_MIN.x);
    double const s_y =  number_of_blocks.y /(B_MAX.y - B_MIN.y);
    double const s_z =  number_of_blocks.z /(B_MAX.z - B_MIN.z);
    return {s_x, s_y, s_z};
}

Vector3D Grid::get_n_coefficients() const {
    if (h_not_inverse == 0){
        return {0,0,0};
    }
    double const num_x = std::floor((B_MAX.x - B_MIN.x) / h_not_inverse);
    double const num_y = std::floor((B_MAX.y - B_MIN.y) / h_not_inverse);
    double const num_z = std::floor((B_MAX.z - B_MIN.z) / h_not_inverse);
    return {num_x, num_y, num_z};
}

/**
 * @brief Determines the closest block to a given particle.
 * @param outside_particle The particle for which to find the closest block.
 * @return The Integer3D coordinates of the closest block.
 */
Integer3D Grid::getClosestBlock(Particle& outside_particle) const {
    Integer3D closest_block = outside_particle.get_grid_position(inverse_size_of_blocks);
    // Check and adjust the x component
    if (closest_block.x < 0) {
        closest_block.x = 0;
    } else if (closest_block.x > number_of_blocks.x - 1) {
        closest_block.x = static_cast<int>(number_of_blocks.x) - 1;
    }
    // Check and adjust the y component
    if (closest_block.y < 0) {
        closest_block.y = 0;
    } else if (closest_block.y > number_of_blocks.y - 1) {

        closest_block.y = static_cast<int>(number_of_blocks.y) - 1;
    }
    // Check and adjust the z component
    if (closest_block.z < 0) {
        //outside_particle.position.z = B_MIN.z;
        closest_block.z = 0;
    } else if (closest_block.z > number_of_blocks.z - 1) {
        //outside_particle.position.z = B_MAX.z;
        closest_block.z = static_cast<int>(number_of_blocks.z)- 1;
    }
    return closest_block;
}


/**
 * @brief Initializes and sets up the blocks within the grid.
 */
void Grid::set_grid_blocks() {
    int index = 0;
    for (int i = 0; i < number_of_blocks.x; i++) {
        for (int j = 0; j < number_of_blocks.y; j++) {
            for (int k = 0; k < number_of_blocks.z; k++) {
                Block block;
                block.id = {k, j, i};
                block.index = index;
                gridCells.push_back(block);
                index++;
            }
        }
    }
}


inline int Grid::getBlockIndex(Integer3D grid_pos) const {
    return static_cast<int>(grid_pos.x + grid_pos.y * number_of_blocks.x + grid_pos.z * number_of_blocks.x * number_of_blocks.y);
}

void Grid::updateParticles() {
    std::unordered_map<int, std::vector<std::pair<int, int>>> moveMap;
    std::unordered_map<int, std::vector<Particle>> tempStorageForMoves;

    // Step 1: Identify particles to move and their targets
    for (size_t i = 0; i < gridCells.size(); ++i) {
        Block& block = gridCells[i];
        for (size_t j = 0; j < block.particles.size(); ++j) {
            Particle const& particle = block.particles[j];
            if (particle.changed_block != -1 && particle.changed_block != block.index) {
                moveMap[i].emplace_back(j, particle.changed_block);
            }
        }
    }

    // Step 2: Accumulate particles for batch move
    for (auto& [srcIdx, moves] : moveMap) {
        for (auto& [particleIdx, targetIdx] : moves) {
            Particle const& particle = gridCells[srcIdx].particles[particleIdx];
            tempStorageForMoves[targetIdx].push_back(particle);
        }
    }

    // Apply batch move to target blocks
    for (auto& [targetIdx, particles] : tempStorageForMoves) {
        gridCells[targetIdx].particles.reserve(gridCells[targetIdx].particles.size() + particles.size());
        for (auto& particle : particles) {
            gridCells[targetIdx].particles.push_back(particle);
        }
    }

    // Step 3: Batch remove from source blocks
    for (auto& [srcIdx, moves] : moveMap) {
        Block& block = gridCells[srcIdx];
        std::vector<Particle> remainingParticles;
        remainingParticles.reserve(block.particles.size());
        size_t removeIdx = 0;
        for (size_t i = 0; i < block.particles.size(); ++i) {
            if (removeIdx < moves.size() && static_cast<size_t>(moves[removeIdx].first) == i) {
                ++removeIdx;
            } else {
                remainingParticles.push_back(block.particles[i]);
            }
        }

        block.particles.swap(remainingParticles);
    }
}

std::vector<Particle> Grid::get_ordered_particles() const {
    std::vector<Particle> ordered_particles;
    ordered_particles.resize(number_of_particles);  // Resize to initialize all elements

    for (const auto &gridCell : gridCells) {

        for (const auto &particle : gridCell.particles) {
            if (particle.id > number_of_particles) {
                print("Particle id: ", particle.id);
                throw std::runtime_error("Particle id is bigger than the number of particles");
            }
            ordered_particles[particle.id] = particle;
        }
    }
    print("Number of particles: ", number_of_particles);
    return ordered_particles;

}

struct GridComparison{
    int id_differ = 0;
    int position_differ = 0;
    int velocity_differ = 0;
    int acceleration_differ = 0;
    int density_differ = 0;
    int gradient_differ = 0;
    int bad_blocks = 0;
};

void check_particle(Particle particle_i, Particle particle_j, GridComparison & grid_comparison){
    if (particle_i.id != particle_j.id) {
        print("Error: particles not equal");
        print("Particle i: ", particle_i);
        print("Particle j: ", particle_j);
        grid_comparison.id_differ++;
        return; // NO need to check the rest as the particles are not equal
    }
    if (std::abs(particle_i.density - particle_j.density) > DELTA_DOUBLE) {
        grid_comparison.density_differ++;
    }
    if (particle_i.acceleration != particle_j.acceleration) {
        grid_comparison.acceleration_differ++;
    }
    if (particle_i.position != particle_j.position) {
        grid_comparison.position_differ++;
    }
    if (particle_i.velocity != particle_j.velocity) {
        grid_comparison.velocity_differ++;
    }
    if (particle_i.gradient != particle_j.gradient) {
        grid_comparison.gradient_differ++;
    }

}

void print_comparision(GridComparison comparison){
    print();
    print(comparison.id_differ, " particles have different ids");
    print(comparison.position_differ, " particles have different positions");
    print(comparison.velocity_differ, " particles have different velocities");
    print(comparison.acceleration_differ, " particles have different accelerations");
    print(comparison.density_differ, " particles have different densities");
    print(comparison.gradient_differ, " particles have different gradients");
    print();
    print(comparison.bad_blocks, " blocks are different");
    print();
    print("********************* End of comparison *********************");
}

[[maybe_unused]] void Grid::compare (const Grid &other) const {      // Helper function that prints
        print("********************* Comparing grids *********************");
        std::vector<Particle> const particles_traces = this->get_ordered_particles();
        std::vector<Particle> const particles_grid = other.get_ordered_particles();
        GridComparison comparison;

        for (size_t i = 0; i < particles_traces.size(); i++) {
            check_particle(particles_traces[i], particles_grid[i], comparison);
        }
        for (size_t i = 0; i < gridCells.size(); ++i) {
            if (!(gridCells[i] == other.gridCells[i])) {
                comparison.bad_blocks++;
            }
        }
        print_comparision(comparison);

}


