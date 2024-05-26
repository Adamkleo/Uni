//
// Created by Mohammed Motia on 3/10/23.
//

#ifndef FLUIDSIMULATION_PROGARGS_HPP
#define FLUIDSIMULATION_PROGARGS_HPP


#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>
#include <string>
#include "Grid.hpp"
#include "Constants.hpp"
#include "particle.hpp"
#include "vector.hpp"
#include "helpers.hpp"
#include "block.hpp"
#include <algorithm>


/**
 * @brief Reads a particle from a binary file.
 *
 * @param file The file to read from.
 * @param i The index of the particle to read.
 * @return The particle read from the file.
 */
inline Particle readParticle(std::ifstream &file, int i) {
    float temp = 0.0;
    Particle particle_buffer(i);
    // We read the particles from the file, we have to use reinterpret_cast
    file.read(reinterpret_cast<char*>(&temp), sizeof(float)); //NOLINT
    particle_buffer.position.x = static_cast<double>(temp);
    file.read(reinterpret_cast<char*>(&temp), sizeof(float)); //NOLINT
    particle_buffer.position.y = static_cast<double>(temp);
    file.read(reinterpret_cast<char*>(&temp), sizeof(float)); //NOLINT
    particle_buffer.position.z = static_cast<double>(temp);
    file.read(reinterpret_cast<char*>(&temp), sizeof(float)); //NOLINT
    particle_buffer.gradient.x = static_cast<double>(temp);
    file.read(reinterpret_cast<char*>(&temp), sizeof(float)); //NOLINT
    particle_buffer.gradient.y = static_cast<double>(temp);
    file.read(reinterpret_cast<char*>(&temp), sizeof(float)); //NOLINT
    particle_buffer.gradient.z = static_cast<double>(temp);
    file.read(reinterpret_cast<char*>(&temp), sizeof(float)); //NOLINT
    particle_buffer.velocity.x = static_cast<double>(temp);
    file.read(reinterpret_cast<char*>(&temp), sizeof(float)); //NOLINT
    particle_buffer.velocity.y = static_cast<double>(temp);
    file.read(reinterpret_cast<char*>(&temp), sizeof(float)); //NOLINT
    particle_buffer.velocity.z = static_cast<double>(temp);

    return particle_buffer;
}


inline void processParticles(int n_p, std::ifstream& file, Grid& grid) {
    int p_id = 0;
    for (int i = 0; i < n_p; ++i) {
        Particle particle = readParticle(file, i);
        particle.id = p_id ;
        grid.addParticle(particle);
        p_id++;
    }
}

inline void writeparticle(std::ofstream& file, Particle particle) {
    float temp = 0.0;
    // We read the particles from the file, we have to use reinterpret_cast
    temp = static_cast<float>(particle.position.x);
    file.write(reinterpret_cast<char*>(&temp), sizeof(float)); //NOLINT
    temp = static_cast<float>(particle.position.y);
    file.write(reinterpret_cast<char*>(&temp), sizeof(float)); //NOLINT
    temp = static_cast<float>(particle.position.z);
    file.write(reinterpret_cast<char*>(&temp), sizeof(float)); //NOLINT
    temp = static_cast<float>(particle.gradient.x);
    file.write(reinterpret_cast<char*>(&temp), sizeof(float)); //NOLINT
    temp = static_cast<float>(particle.gradient.y);
    file.write(reinterpret_cast<char*>(&temp), sizeof(float)); //NOLINT
    temp = static_cast<float>(particle.gradient.z);
    file.write(reinterpret_cast<char*>(&temp), sizeof(float)); //NOLINT
    temp = static_cast<float>(particle.velocity.x);
    file.write(reinterpret_cast<char*>(&temp), sizeof(float)); //NOLINT
    temp = static_cast<float>(particle.velocity.y);
    file.write(reinterpret_cast<char*>(&temp), sizeof(float)); //NOLINT
    temp = static_cast<float>(particle.velocity.z);
    file.write(reinterpret_cast<char*>(&temp), sizeof(float)); //NOLINT
}




inline std::string getFullPath(const std::string& filename, const std::string& folder = "") {
    try {
        std::filesystem::path currentPath = std::filesystem::current_path();
        currentPath /= folder;      // append folder to the current directory
        currentPath /= filename;  // append filename to the current directory
        return currentPath.string();
    } catch (const std::filesystem::filesystem_error& e) {

        //std::cerr << "Error: " << e.what() << '\n';
        return "";
    }
}

inline void open_file(const char* filename, Grid& grid, const std::string& folder = "") {
    std::string const full = getFullPath(filename, folder);
    std::ifstream file(full, std::ios::binary);
    std::vector<Particle> const particles;
    print("We managed to open the file");
    //std::cout << "Opening file: " << full << '\n';
    print("Path: ", full);
    if (!file.is_open()) {
        std::cout << "Failed to open file" << '\n';
        exit(-1);
    }
    // Read header
    float ppm = 0.0;
    int n_p = 0.0;
    file.read(reinterpret_cast<char*>(&ppm), sizeof(ppm)); //NOLINT
    file.read(reinterpret_cast<char*>(&n_p), sizeof(n_p)); //NOLINT
    grid.resetGrid(ppm);
    processParticles(n_p, file, grid);
    file.close();
}


inline void check_main_parameters(int argc, char** argv) {
    // Check if the number of arguments is correct
    if (argc != 4) {
        std::cerr << "Error: Invalid number of arguments: " << argc << '\n';
        exit(-1);
    }

    // Check if the first argument is a number, otherwise return error
    try {
        // We must use pointer arithmetic to compare the arguments
        if (std::stoi(argv[1]) <= 0) { // NOLINT
            std::cerr << "Error: Invalid number of time steps." << '\n';
            exit(-2);
        }
    } catch (std::invalid_argument& e) {
        std::cerr << "Error: time steps must be numeric." << '\n';
        exit(-1);
    }
}


inline void writeParticlesToBinaryFile(const Grid & grid , const std::string& filename) {
    std::vector<Particle> const sortedParticles = grid.get_ordered_particles();
    // Open the output binary file for writing.
    std::ofstream outputFile(filename, std::ios::binary);
    if (!outputFile) {
        std::cerr << "Error: Unable to open the output file: " << filename << '\n';
        return;
    }

    // Write ppm to the output file in single precision (float) format.
    auto floatValue = static_cast<float>(grid.ppm);
    outputFile.write(reinterpret_cast<const char*>(&floatValue), sizeof(float)); //NOLINT

    // Write np to the output file in single precision (float) format.
    auto floatValue1 = static_cast<int>(grid.number_of_particles);
    outputFile.write(reinterpret_cast<const char*>(&floatValue1), sizeof(int)); //NOLINT

    // Write the particles to the output file in single precision (float) format.
    for (const auto& particle : sortedParticles) {
        writeparticle(outputFile, particle);
    }

    // Close the output file.
    outputFile.close();
}

#endif //FLUIDSIMULATION_PROGARGS_HPP
