// Created by Carlos on 10/10/23.

#ifndef FLUIDSIMULATION_PARTICLE_HPP
#define FLUIDSIMULATION_PARTICLE_HPP

#include <iostream>
#include "vector.hpp"
#include <array>
#include "Constants.hpp"

/**
 * @class Particle
 * @brief Represents a particle in a fluid simulation.
 *
 * This class encapsulates the properties and behaviors of a particle
 * within a fluid simulation context. It includes physical attributes
 * like position, velocity, and density, as well as methods for updating
 * these attributes and handling interactions with other particles and boundaries.
 */
class Particle {
public:
    int id; ///< Unique identifier for the particle.
    Vector3D position; ///< Position of the particle in 3D space.
    Vector3D gradient; ///< Gradient (vector field) affecting the particle.
    Vector3D velocity; ///< Velocity of the particle.
    Vector3D acceleration = EXTERNAL_ACCELERATION; ///< Acceleration of the particle.
    double density=0*1; ///< Density of the particle.
    int changed_block = -1; ///< Flag to indicate if the particle has changed blocks.
    bool toBeRemoved = false;

    // Constructors
    //Particle(Vector3D position, int particle_id, Vector3D velocity, Vector3D gradient); ///< Constructs a particle with specified properties.
    explicit Particle(int particle_id); ///< Constructs a particle with a given ID and default properties.
    Particle() : id(-1), density(0.0) {} ///< Default constructor.

    friend std::ostream& operator<<(std::ostream& os, const Particle& p) { // Helper function for development
        os << "Particle ID: " << p.id << "\n"
           << "  Position: " << p.position << "\n"
           << "  Gradient: " << p.gradient << "\n"
           << "  Velocity: " << p.velocity << "\n"
           << "  Acceleration: " << p.acceleration << "\n"
           << "  Density: " << p.density << "\n";
        return os;
    }

    bool operator==(const Particle& other) const {
        return (id == other.id) && (position == other.position) && (velocity == other.velocity) && (acceleration == other.acceleration) && (density == other.density) && (gradient == other.gradient);
    }


    // Helper functions
    [[nodiscard]] Integer3D get_grid_position(Vector3D block_size) const; ///< Computes the particle's position on a grid, given the grid's minimum point and block size.
    [[nodiscard]] Integer3D get_careful_grid_position(Vector3D block_size, Vector3D number_of_blocks) const; ///< Computes the particle's position on a grid, given the grids number of blocks and block size.

    // Updating functions
    void update(Vector3D inverse_size_of_block, Vector3D number_of_blocks); ///< Updates the particle's state.
    void carefulUpdate(Vector3D mask, Vector3D inverse_size_of_bloc, Vector3D number_of_blocks); ///< Carefully updates the particle's state considering boundary conditions.
    //void updateWithFriends(Particle& particle_friend, Vector3D density_constants, Vector3D acceleration_constants);

    /// Forces and acceleration functions
    // Density functions
    void calculateDensityIncrease(Particle& particlej, Vector3D density_constants); ///< Calculates the increase in density due to another particle.
    void linear_transform(double H_6, double LINEAR_T); ///< Applies a linear transformation to the particle's density.

    // Acceleration functions
    void updateAcceleration(Particle& particlej, Vector3D acceleration_constants); ///< Updates acceleration based on interactions with another particle.


    /// Particle collision functions
    // Collision functions
    //void handleMaskedCollision2(Vector3D mask); ///< Handles collisions with boundaries in a generic way.
    void handleXCollisions(Vector3D mask);
    void handleYCollisions(Vector3D mask);
    void handleZCollisions(Vector3D mask);
    void handleColission2(Vector3D mask); ///< Handles collisions with boundaries in a generic way.

    void boundaryInteractor(Vector3D mask);




//private:
    // Private member functions for internal mechanics

    // Additional private methods for collision detection could be added here
};


#endif //FLUIDSIMULATION_PARTICLE_HPP