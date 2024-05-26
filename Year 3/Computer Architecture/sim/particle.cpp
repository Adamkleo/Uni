//
// Created by Carlos Barboza on 10/10/23.
//

#include "particle.hpp"
#include "Constants.hpp"


// Constructors

/**
 * @brief Constructs a particle with specified attributes.
 * @param particle_id Unique identifier for the particle.
 * @param position Initial position of the particle.
 * @param velocity Initial velocity of the particle.
 * @param gradient Initial gradient or acceleration affecting the particle.
 */
//Particle::Particle(Vector3D position, int particle_id, Vector3D velocity, Vector3D gradient) :
//id(particle_id), position(position), velocity(velocity),
// gradient(gradient), density(0.0), acceleration(EXTERNAL_ACCELERATION){}

/**
 * @brief Constructs a particle with a given ID and default properties.
 * @param particle_id Unique identifier for the particle.
 */
Particle::Particle(int particle_id) : id(particle_id) {
    this->position = Vector3D(0.0F, 0.0F, 0.0F);
    this->velocity = Vector3D(0.0F, 0.0F, 0.0F);
    this->gradient = Vector3D(0.0F, 0.0F, 0.0F);
}

/**
 * @brief Updates the density of the particle based on its interaction with another particle.
 * @param h Smoothing length in the density calculation.
 * @param particlej The other particle influencing the density.
 * @param LINEAR_T Linear transformation constant.
 */
void Particle::calculateDensityIncrease(Particle& particlej, Vector3D density_constants) {
    // Density constant has to have the following values:
    // .x = H_6 = h^6
    // .y = LINEAR_T*m = 315*m/(64*PI*h^9)
    // .z = hSquared = h^2
    // To avoid calculating h^6 and h^9 every time we calculate density, we precalculate them in the grid class as h is constant throughout the simulation
    // This function is only called if the distance between the particles is less than h
    const Vector3D result = position - particlej.position;

    const double distanceSquared = result.squaredLength();
    if (distanceSquared < density_constants.z) {
        const double diff = (density_constants.z - distanceSquared);
        const double density_inc = diff*diff*diff;
        density += density_inc;
        particlej.density += density_inc;

    }
}


void Particle::linear_transform(double H_6, double LINEAR_T) {
    density = (density + H_6) * LINEAR_T ;
    //print("Density after linear transform: ", density, "of particle: ", id);
    //de
}


/**
 * @brief Calculates the grid position of the particle based on a grid with specified minimum and block size.
 * @param minimum The minimum point of the grid.
 * @param block_size The size of each grid block.
 * @return Integer3D representing the grid position of the particle.
 */
Integer3D Particle::get_grid_position(Vector3D block_size) const {
    const int x_var = std::floor((position.x - B_MIN.x) * block_size.x);
    const int y_var = std::floor((position.y - B_MIN.y) * block_size.y);
    const int z_var = std::floor((position.z - B_MIN.z) * block_size.z);
    return {x_var, y_var, z_var};
}
Integer3D Particle:: get_careful_grid_position(Vector3D block_size, Vector3D number_of_blocks) const {
    int x_var = std::floor((position.x - B_MIN.x) * block_size.x);
    x_var = (x_var >= number_of_blocks.x) ? static_cast<int>(number_of_blocks.x - 1) : x_var;
    x_var = (x_var < 0) ? 0 : x_var;
    int y_var = std::floor((position.y - B_MIN.y) * block_size.y);
    y_var = (y_var >= number_of_blocks.y) ? static_cast<int>(number_of_blocks.y - 1) : y_var;
    y_var = (y_var < 0) ? 0 : y_var;
    int z_var =std::floor((position.z - B_MIN.z) * block_size.z);
    z_var = (z_var >= number_of_blocks.z) ? static_cast<int>(number_of_blocks.z - 1): z_var;
    z_var = (z_var < 0) ? 0 : z_var;
    return {x_var, y_var, z_var};
}



/**
 * @brief Computes the change in acceleration due to the interaction with another particle.
 * @param particlej The other particle.
 * @param h Smoothing length.
 * @param m Mass of the particles.
 * @return Vector3D representing the change in acceleration.
 */


/**
 * @brief Updates the acceleration of this particle and another particle based on their interaction.
 * @param particlej The other particle.
 * @param h Smoothing length.
 * @param m Mass of the particles.
 */
void Particle::updateAcceleration(Particle& particlej, const Vector3D acceleration_constants) {
    // Get the change in acceleration
    const Vector3D pi_minus_pj = this->position - particlej.position;
    double dist_ij = pi_minus_pj.squaredLength();
    const double hSquared = acceleration_constants.z * acceleration_constants.z;
    if (dist_ij < (hSquared)) {
        Vector3D delta_a_ij;
        dist_ij = (dist_ij > DIST_MAX) ? std::sqrt(dist_ij) : SQUARE_DIST;

        const double power = pow((acceleration_constants.z - dist_ij), 2);
        double first_term_multiplicator = (acceleration_constants.x * power) / dist_ij;

        first_term_multiplicator *= ((this->density + particlej.density) - 2 * FLUID_DENSITY);
        const Vector3D first_term = pi_minus_pj * first_term_multiplicator;

        const Vector3D second_term = (particlej.velocity - this->velocity) * acceleration_constants.y;
        delta_a_ij = (first_term + second_term) / (this->density * particlej.density);
        this->acceleration += delta_a_ij;
        particlej.acceleration -= delta_a_ij;
    }
}



/**
 * @brief Handles collisions with the boundary of the simulation.
 * @param mask Mask vector for selective updating.
 */



void Particle::handleColission2(Vector3D mask){
    handleXCollisions(mask);
    handleYCollisions(mask);
    handleZCollisions(mask);
}

void Particle::handleXCollisions(Vector3D mask){
    Vector3D delta_pos;
    if (mask.x != 0) {
        if (mask.x == 1) {
            delta_pos.x = PARTICLE_SIZE - (this->position.x - B_MIN.x);
        } else {
            delta_pos.x = PARTICLE_SIZE - (B_MAX.x - this->position.x);
        }
        if (delta_pos.x > COLLISION_DELTA) {
            if (mask.x == 1) {
                this->acceleration.x = this->acceleration.x + ((STIFFNESS_COLLISIONS * delta_pos.x) - (DAMPING* this->velocity.x));
            } else {
                this->acceleration.x = this->acceleration.x - ((STIFFNESS_COLLISIONS * delta_pos.x) + (DAMPING* this->velocity.x));
            }
        }
    }
}

void Particle::handleYCollisions(Vector3D mask) {
    Vector3D delta_pos;
    // Handle collisions on the y-axis
    if (mask.y != 0) {
        if (mask.y == 1) {
            delta_pos.y = PARTICLE_SIZE - (this->position.y - B_MIN.y);

            // print("delta_pos.y: ", PARTICLE_SIZE ,"- ", this->position.y, " + ", B_MIN.y, " = ", delta_pos.y);
        } else {
            delta_pos.y = PARTICLE_SIZE - (B_MAX.y - this->position.y);
        }
        if (delta_pos.y > COLLISION_DELTA) {
            if (mask.y == 1) {
                this->acceleration.y +=
                        ((STIFFNESS_COLLISIONS * delta_pos.y) - (DAMPING * this->velocity.y));
            } else {
                this->acceleration.y -=
                        ((STIFFNESS_COLLISIONS * delta_pos.y) + (DAMPING * this->velocity.y));
            }
        }
    }
}

void Particle::handleZCollisions(Vector3D mask) {
    Vector3D delta_pos;
    // Handle collisions on the z-axis
    if (mask.z != 0) {
        if (mask.z == 1) {
            delta_pos.z = PARTICLE_SIZE - (this->position.z - B_MIN.z);
        } else {
            delta_pos.z = PARTICLE_SIZE - (B_MAX.z - this->position.z);
        }
        if (delta_pos.z > COLLISION_DELTA) {
            if (mask.z == 1) {
                this->acceleration.z +=
                        ((STIFFNESS_COLLISIONS * delta_pos.z) - (DAMPING * this->velocity.z));
            } else {
                this->acceleration.z -=
                        ((STIFFNESS_COLLISIONS * delta_pos.z) + (DAMPING * this->velocity.z));
            }
        }
    }
}





/**
 * @brief Basic update function for the particle, applying gravity and moving the particle.
 */
void Particle::update(Vector3D inverse_size_of_block, Vector3D number_of_blocks) {

    const double delta_square = DELTA_TIME * DELTA_TIME;

    position = position + (gradient * DELTA_TIME) + (acceleration * (delta_square));
    velocity = gradient + acceleration * ( DELTA_TIME / 2 );
    gradient += acceleration * DELTA_TIME;

    acceleration = EXTERNAL_ACCELERATION;
    density = 0.0;


    const Integer3D block_pos = get_careful_grid_position(inverse_size_of_block, number_of_blocks);
    changed_block = static_cast<int>(block_pos.x + block_pos.y * number_of_blocks.x + block_pos.z * number_of_blocks.x * number_of_blocks.y);
}

/**
 * @brief Updates the particle state with careful consideration of boundary conditions.
 * @param mask Mask vector for selective updating.
 * @param upper Boolean to indicate if the upper boundary is considered.
 */
void Particle::carefulUpdate(Vector3D mask, Vector3D inverse_size_of_bloc, Vector3D number_of_blocks) {
    //Vector3D prev_pos = position;

    position += gradient * DELTA_TIME;
    //Vector3D new_pos = position + gradient * DELTA_TIME;
    // No if statement needed since the mask will be 0 if the particle is not in the boundary
    // And it's assumed this method is only called from boundary blocks
    //Vector3D prev_acceleration = acceleration;
    handleColission2(mask); // Mask indicata the box-boundary data -1 for upper boundary, 1 for lower boundary
//handleMaskedCollision2(mask);

    position = position + (acceleration * (DELTA_TIME_SQ));
    velocity = gradient + acceleration * ( DELTA_TIME / 2 );
    gradient +=  acceleration * DELTA_TIME;

    boundaryInteractor(mask);

    acceleration = EXTERNAL_ACCELERATION;
    density = 0.0;

    const Integer3D block_pos = get_careful_grid_position(inverse_size_of_bloc, number_of_blocks);

    changed_block = static_cast<int>(block_pos.x + block_pos.y * number_of_blocks.x + block_pos.z * number_of_blocks.x * number_of_blocks.y);
}

void Particle::boundaryInteractor(Vector3D mask) {
    const Vector3D d_vector = {
            mask.x != 0 ? (mask.x == 1 ? (position.x - B_MIN.x) : (B_MAX.x - position.x)) : 0,
            mask.y != 0 ? (mask.y == 1 ? (position.y - B_MIN.y) : (B_MAX.y - position.y)) : 0,
            mask.z != 0 ? (mask.z == 1 ? (position.z - B_MIN.z) : (B_MAX.z - position.z)) : 0
    };

    if (d_vector.x == 0 && d_vector.y == 0 && d_vector.z == 0) {
        return;
    }
    position.x = (d_vector.x < 0)? ((mask.x == 1 ? (B_MIN.x - d_vector.x) : (B_MAX.x + d_vector.x) )) : position.x;
    position.y = (d_vector.y < 0)? ((mask.y == 1 ? (B_MIN.y - d_vector.y) : (B_MAX.y + d_vector.y) )) : position.y;
    position.z = (d_vector.z < 0)? ((mask.z == 1 ? (B_MIN.z - d_vector.z) : (B_MAX.z + d_vector.z) )) : position.z;
    const Vector3D update_mask = (d_vector < 0);
    velocity -= velocity * 2 & update_mask;
    gradient -= gradient * 2 & update_mask;
}