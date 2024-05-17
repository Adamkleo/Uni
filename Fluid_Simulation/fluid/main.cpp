#include <iostream>
#include "progargs.hpp"
#include "Grid.hpp"
#include "particle.hpp"
#include "vector.hpp"
#include "Fluid_simulation.hpp"
//#include "ParticleTest.hpp"

#include "helpers.hpp"

#include <chrono>

#include <cmath>
#include "traces.hpp"

/*
 *
 * For windows we must 1:
 * Ensure all folders use \ instead of /
 * We must set the working directory to the main folder
 * not the build folder
 */


int main(int argc, char** argv) { // NOLINT (It excedes it because of the comments)
    // Uncomment to be able to test traces
    /*
    const char *filePath1 = "trz/small/repos-base-4.trz";   // Check up to -28
    Grid TracesGrid = Grid();
    TracesGrid.resetGrid(204); // I
    check_trace(filePath1, TracesGrid);
     */


    check_main_parameters(argc, argv);

    Grid grid = Grid();
    open_file(argv[2], grid, "in"); // If we want to specify the folder directly into the argv don't include "in" //NOLINT

    int number_of_steps = std::stoi(argv[1]); // NOLINT
    FluidSimulation smallSimulation = FluidSimulation(grid, number_of_steps);
    smallSimulation.simulate();


    writeParticlesToBinaryFile(grid, argv[3]); //NOLINT

    /*
    Grid should_be_same = Grid();
    open_file(argv[3], should_be_same); //NOLINT


    grid.compare(should_be_same);

    smallSimulation.grid.printGridSummary();

    smallSimulation.grid.compare(TracesGrid);

    std::vector <Particle> particles = smallSimulation.grid.get_ordered_particles();
    std::vector <Particle> particles2 = TracesGrid.get_ordered_particles();

    print("Particle 0: ", particles[0]); // specify particle to compare
    print("Particle 0: ", particles2[0]);
     //*/
    return 0;

}