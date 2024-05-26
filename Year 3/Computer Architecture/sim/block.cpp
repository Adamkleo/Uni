#include "block.hpp"
#include "helpers.hpp"
/**
 * @brief Adds a particle to the block.
 * @param p The particle to be added to this block.
 */
void Block::addParticle(Particle p) {
    particles.push_back(p); // Adds the particle to the vector of particles in the block.
}

/**
 * @brief Prints information about the block and its contained particles.
 *
 * Outputs the block's ID and details of each particle within the block,
 * including the particle's ID and coordinates.
 */
void Block::printBlock() {
    std::cout << "Printing block" << '\n';
    id.printCoordinates(); // Prints the coordinates of the block.
    std::cout << '\n' << "Block " << id.x << "-" << id.y << "-" << id.z << '\n';
    for (auto & particle : particles) {
        std::cout << "Particle " << particle.id << '\n';
        print(particle); // Prints each particle's ID and coordinates.
    }
}

bool Block::blockIsBoundary(Vector3D number_of_block) const {
    if (id.x == 0 || id.x == number_of_block.x -1){
        return true;
    }
    if (id.y == 0 || id.y == number_of_block.y -1 ){
        return true;
    }
    if (id.z == 0 || id.z == number_of_block.z -1){
        return true;
    }
    return false;
}

Vector3D  Block::maskBoundary(Vector3D number_of_block) {
    Vector3D collisionVector;
    // Check x-axis
    collisionVector.x = (id.x == 0) ? 1 : ((id.x == number_of_block.x - 1) ? -1 : 0);

    // Check y-axis
    collisionVector.y = (id.y == 0) ? 1 : ((id.y == number_of_block.y - 1) ? -1 : 0);

    // Check z-axis
    collisionVector.z = (id.z == 0) ? 1 : ((id.z == number_of_block.z - 1) ? -1 : 0);

    return collisionVector;
}


/**
 * @brief Checks if the block contains any particles.
 * @return True if the block is not empty (contains one or more particles), false otherwise.
 */
bool Block::isNotEmpty() const {
    return !particles.empty(); // Returns true if the particles vector is not empty.
}


/**
 * @brief Prints information about each block in a given vector of blocks.
 * @param block_vector A vector containing blocks to be printed.
 *
 * Iterates through the vector and prints details of each block using printBlock().
 */
void printBlockFromVector(std::vector<Block> block_vector) {
    std::cout << "Printing adjacent blocks" << '\n';
    std::cout << "Size of adjacent blocks: " << block_vector.size() << '\n';
    for (auto & block : block_vector) {
        block.printBlock(); // Calls the printBlock() method on each block in the vector.
    }
}
