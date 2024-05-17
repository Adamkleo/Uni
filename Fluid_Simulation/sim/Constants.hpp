//
// Created by Adam Kaawach on 5/10/23.
//

#ifndef FLUIDSIMULATION_CONSTANTS_HPP
#define FLUIDSIMULATION_CONSTANTS_HPP
#include "vector.hpp"

// !-- SCALAR CONSTANTS --!

// Radius multiplier
constexpr double RADIUS_MULTIPLIER = 1.695;

// Fluid density (10^3)
constexpr double FLUID_DENSITY = 1e3;

// Stiffness pressure
constexpr double STIFFNESS_PRESSURE = 3.0;

// Stiffness collisions (3 * 10^4)
constexpr double STIFFNESS_COLLISIONS = 3e4;

// Gravity pull
constexpr double GRAVITY_PULL = -9.81;

// Damping
constexpr double DAMPING = 128.0;

// Viscosity
constexpr double VISCOSITY = 0.4;

// Particle size (2 * 10^-4)
constexpr double PARTICLE_SIZE = 2e-4;

// Time step (10^-4)
constexpr double DELTA_TIME = 1e-3;

constexpr double DELTA_TIME_SQ =1e-6;

// Collission delta
constexpr double COLLISION_DELTA = 1e-10;

constexpr double PI = 3.14159265358979323846;

constexpr double DELTA_DOUBLE = 1e-11;

constexpr double T_315 = 315.0;
constexpr double T_45 = 45.0;
constexpr double T_32 = 32.0;
constexpr double T_15 = 15.0;
constexpr double T_64 = 64.0;
constexpr double T_9 = 9.0;
constexpr double T_3 = 3.0;
constexpr double T_2 = 2.0;

constexpr double DIST_MAX = 1e-12;
constexpr double SQUARE_DIST = 1e-6;

// !-- VECTOR CONSTANTS --!
// Constants from the table

constexpr Vector3D EXTERNAL_ACCELERATION(0.0, -9.8, 0.0);                 // External acceleration
constexpr Vector3D B_MAX(0.065, 0.1, 0.065);          // Box upper bound
constexpr Vector3D B_MIN(-0.065, -0.08, -0.065);      // Box lower bound



#endif //FLUIDSIMULATION_CONSTANTS_HPP
