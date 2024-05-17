//
// Created by Carlos Barboza on 10/10/23.
//
#ifndef FLUIDSIMULATION_BLOCK_HPP
#define FLUIDSIMULATION_BLOCK_HPP

#include <vector>
#include <iostream>
#include "particle.hpp"
#include "vector.hpp"
#include <algorithm>
#include "helpers.hpp"

/**
 * @class Block
 * @brief Represents a block in the fluid simulation grid.
 *
 * This class is designed to encapsulate a block within the simulation,
 * holding a collection of particles that are present in this specific block.
 */
class Block {
public:
    Integer3D id = {-1, -1, -1}; ///< The identifier of the block, represented as a 3D integer vector.
    std::vector<Particle> particles; ///< A vector containing the particles within this block.
    int status = 0; ///< A mask used to determine which adjacent blocks have been updated
    int index = -1; ///< The index of the block in the grid.

    Block() {
        particles.reserve(1000);
    }

    bool blockIsBoundary(Vector3D number_of_block) const;
    Vector3D maskBoundary(Vector3D number_of_block);

    // Methods
    void addParticle(Particle p); ///< Adds a particle to the block.
    void printBlock(); ///< Outputs information about the block and its particles.
    [[nodiscard]] bool isNotEmpty() const; ///< Checks if the block contains any particles.

    void removeParticle(int particle_id); ///< Removes a particle from the block.

    friend std::ostream& operator<<(std::ostream& os, const Block& block) {
        os << "Block ID: " << block.id << "\n"
           << "Index: " << block.index << "\n"
           << "Status: " << block.status << "\n"
           << "Particles:\n";

        for (const auto& particle : block.particles) {
            //os << particle << "\n";
            os << "  " << particle.id << ": (" << particle.position <<"), acceleration: " << particle.acceleration <<"\n";
        }

        return os;
    }

    [[nodiscard]] std::vector<Particle> get_ordered_particles() const {
        // Adds into vector the particles ordered by id
        std::vector<Particle> ordered_particles = particles;
        std::sort(ordered_particles.begin(), ordered_particles.end(), [](const Particle& lhs, const Particle& rhs) {
            return lhs.id < rhs.id;
        });

        return ordered_particles;
    }

    friend bool operator==(const Block& lhs, const Block& rhs) {
        if (lhs.id != rhs.id){
            return false;
        }
        std::vector <Particle> lhs_particles = lhs.get_ordered_particles();
        std::vector <Particle> rhs_particles = rhs.get_ordered_particles();
        if (lhs_particles.size() != rhs_particles.size()){
            return false;
        }

        for (size_t i = 0; i < lhs_particles.size(); ++i) {
            //print("Comparing particles: ", lhs_particles[i].id, " and ", rhs_particles[i].id);
            if (lhs_particles[i].id != rhs_particles[i].id){
               return false;
            }
        }
        return true;
    }





};



void printBlockFromVector(std::vector<Block> block_vector); ///< Prints information about each block in a vector of blocks.

#endif //FLUIDSIMULATION_BLOCK_HPP
