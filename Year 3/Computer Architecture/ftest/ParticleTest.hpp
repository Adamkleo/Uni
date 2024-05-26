//
// Created by Carlos Barboza on 16/11/23.
//
/*
#ifndef FLUID_PARTICLETEST_HPP
#define FLUID_PARTICLETEST_HPP
#include <gtest/gtest.h>
#include <vector>
#include <chrono>
#include "sim/particle.hpp"

class ParticleTest : public ::testing::Test {
protected:
    std::vector<Particle> particles; // A vector to hold particles for testing

    // Setup function to initialize particles before each test
    void SetUp() override {
        // Example initialization of particles
        // Replace with actual constructor parameters based on your Particle class
        particles.emplace_back(Particle(1, Vector3D(1.0, 1.0, 1.0), Vector3D(0.0, 0.0, 0.0), Vector3D(0.0, 0.0, 0.0)));
        particles.emplace_back(Particle(2, Vector3D(2.0, 2.0, 2.0), Vector3D(0.5, 0.5, 0.5), Vector3D(1.0, 1.0, 1.0)));
        // ... Add more particles as needed for testing
    }
};
TEST_F(ParticleTest, TestDensityIncreaseFunctions) {
for (size_t i = 0; i < particles.size(); ++i) {
for (size_t j = 0; j < particles.size(); ++j) {
if (i != j) {
double h = 1.0; // Example value for h

// Copy particles to avoid modifying the original ones
Particle particle_i_original = particles[i];
Particle particle_j_original = particles[j];

Particle particle_i_optimized = particles[i];
Particle particle_j_optimized = particles[j];

// Time and execute the original function
auto start = std::chrono::high_resolution_clock::now();
particle_i_original.calculateDensityIncreaseOriginal(h, particle_j_original);
auto end = std::chrono::high_resolution_clock::now();
auto durationOriginal = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

// Time and execute the optimized function
start = std::chrono::high_resolution_clock::now();
particle_i_optimized.calculateDensityIncreaseOptimized(h, particle_j_optimized);
end = std::chrono::high_resolution_clock::now();
auto durationOptimized = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

// Check if the results are the same
ASSERT_EQ(particle_i_original.density, particle_i_optimized.density);
ASSERT_EQ(particle_j_original.density, particle_j_optimized.density);

// Output the time taken for each function
std::cout << "Original function time: " << durationOriginal << " ns, "
<< "Optimized function time: " << durationOptimized << " ns" << std::endl;
}
}
}
}

#endif //FLUID_PARTICLETEST_HPP
*/
/*
void test_boundary(){
    // Lets create 8 random particles within the bounds
    Particle p1 = Particle(0, Vector3D(0.0651, 0.089, 0.064), Vector3D(0.0, 0.0, 0.0), Vector3D(0.0, 0.0, 0.0));
    Particle p2 = Particle(1, Vector3D(-0.0649, -0.08, -0.066), Vector3D(0.0, 0.0, 0.0), Vector3D(0.0, 0.0, 0.0));
    Particle p3 = Particle(2, Vector3D(-0.0649, 0.00, 0.0), Vector3D(0.0, 0.0, 0.0), Vector3D(0.0, 0.0, 0.0));

    Grid grid = Grid();
    open_file(argv[2], grid);

    grid.addParticle(p1);
    grid.addParticle(p2);
    grid.addParticle(p3);

    print("Before updates:");
    print(grid.gridCells[0]);
    print(p1.acceleration);
    print(p2.acceleration);

    Block block1 = grid.gridCells[0];
    print("Block 1 mask: ", block1.maskBoundary(grid.number_of_blocks));
    Block block2 = grid.gridCells[4710];
    print("Block 2 mask: ", block2.maskBoundary(grid.number_of_blocks));
    Block block3 = grid.gridCells[2340];
    print("Block 3 mask: ", block3.maskBoundary(grid.number_of_blocks));

    p1.handleMaskedCollision2(block1.maskBoundary(grid.number_of_blocks));
    p2.handleMaskedCollision2(block2.maskBoundary(grid.number_of_blocks));
    p3.handleMaskedCollision2(block3.maskBoundary(grid.number_of_blocks));

    print("After updates:");
    print(p1.acceleration);
    print(p2.acceleration);
    print(p3.acceleration);

}
 */

void test_boundary_interactor(){
    Particle p1 = Particle(0, Vector3D(0.067, 0.089, 0.064), Vector3D(0.0, 0.0, 0.0), Vector3D(0.0, 0.0, 0.0));
    Particle p2 = Particle(1, Vector3D(-0.0649, -0.085, -0.066), Vector3D(0.0, 0.0, 0.0), Vector3D(0.0, 0.0, 0.0));
    Particle p3 = Particle(2, Vector3D(-0.066, 0.001, 0.066), Vector3D(1.0, 1.0, 1.0), Vector3D(2.0, 2.0, 2.0));

    Grid grid = Grid();
    grid.resetGrid(204);


    grid.addParticle(p1);
    grid.addParticle(p2);
    grid.addParticle(p3);

    grid.print_grid();

    Block block1 = grid.gridCells[4545];
    Vector3D mask = block1.maskBoundary(grid.number_of_blocks);

    Block block2 = grid.gridCells[0];
    Vector3D mask2 = block2.maskBoundary(grid.number_of_blocks);

    print(block1);
    print(mask);

    p3.boundaryInteractor(mask);
    print("p1:-------------------");
    print(block2);
    print(mask2);

    p2.boundaryInteractor(mask2);
}