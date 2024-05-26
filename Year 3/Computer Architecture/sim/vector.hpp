//
// Created by Carlos Barboza on 10/10/23.
//

#ifndef FLUIDSIMULATION_VECTOR_HPP
#define FLUIDSIMULATION_VECTOR_HPP

#include <iostream>
#include <cmath>

constexpr double TOLERANCE = 1e-10; ///< A tolerance value used for comparing floating point numbers.
/**
 * @class Vector3D
 * @brief Represents a three-dimensional vector with double precision.
 *
 * This class models a 3D vector and provides various functionalities
 * for vector arithmetic, including dot product, addition, subtraction,
 * multiplication, and division. It supports comparison and masking operations,
 * and allows for calculation of vector length and squared length.
 */

class Vector3D {
public:
    double x, y, z; ///< Public member variables representing the x, y, z components of the vector.

    constexpr Vector3D() : x(0), y(0), z(0) {}; ///< Default constructor initializing the vector to (0,0,0).

    constexpr Vector3D(double xVal, double yVal, double zVal): x(xVal), y(yVal), z(zVal) {}; ///< Parameterized constructor for creating a vector with specified components.





    // Overloaded operators for vector arithmetic.
    bool operator==(const Vector3D& other) const; ///< Checks equality of two vectors
    bool operator!=(const Vector3D& other) const; ///< Checks inequality of two vectors
    Vector3D operator+(const Vector3D& other) const; ///< Adds two vectors.
    Vector3D operator+(const double& other) const; ///< Adds a scalar to all components of the vector.

    Vector3D operator-(const Vector3D& other) const; ///< Subtracts two vectors.
    Vector3D operator-(const double& other) const; ///< Subtracts a scalar from all components of the vector.

    Vector3D operator-() const {
        return {-x, -y, -z};
    }

    Vector3D operator*(const Vector3D& other) const; ///< Multiplies two vectors element-wise.
    Vector3D operator*(const double& other) const; ///< Multiplies all components of the vector by a scalar.

    Vector3D operator/(const double& other) const; ///< Divides all components of the vector by a scalar.
    Vector3D operator/(const Vector3D& other) const; ///< Divides two vectors element-wise.

    Vector3D& operator+=(const Vector3D& other); ///< Adds another vector to this vector.
    Vector3D& operator-=(const Vector3D& other); ///< Subtracts another vector from this vector.
    Vector3D& operator*=(const Vector3D& other); ///< Multiplies this vector by another vector element-wise.
    Vector3D& operator*=(const double& other); ///< Multiplies this vector by a scalar.

    bool operator<=(const Vector3D& other) const; ///< Compares if this vector is less than or equal to another vector.
    bool operator<=(const double& other) const; ///< Compares if this vector is less than or equal to a scalar.
    bool operator>=(const Vector3D& other) const; ///< Compares if this vector is greater than or equal to another vector.
    Vector3D operator >=(const double& other) const; ///< Compares if this vector is greater than or equal to a scalar.
    Vector3D operator <(const double& other) const; ///< Compares if this vector is less than a scalar.

    friend std::ostream& operator<<(std::ostream& os, const Vector3D& v) {
        os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
        return os;
    }


    // Overloaded operators for vector masking.
    Vector3D operator&(const Vector3D& other) const; ///< Performs bitwise AND operation between two vectors.
    Vector3D operator&(int mask) const; ///< Performs bitwise AND operation with an integer mask.
    Vector3D operator^(const Vector3D& other) const; ///< Performs bitwise XOR operation between two vectors.
    Vector3D operator^(int mask) const; ///< Performs bitwise XOR operation with an integer mask.


    [[nodiscard]] double squaredLength() const; ///< Returns the squared magnitude (length) of the vector.

private:
    static bool areEqual(double a, double b) {
        return std::abs(a - b) < TOLERANCE;
    }
};

/**
 * @class Integer3D
 * @brief Represents a three-dimensional integer vector.
 *
 * This class models a 3D vector with integer components. It provides a basic
 * functionality to print the coordinates of the vector.
 */
class Integer3D {
public:
    int x, y, z; ///< Public member variables representing the x, y, z components of the integer vector.

    Integer3D operator-(const Integer3D& other) const; ///< Subtracts two integer vectors.
    void printCoordinates() const; ///< Method to print the integer vector's coordinates.
    inline int get_relative_mask(Integer3D &other) const {
        int const d_x = other.x - this->x + 1; // Range from -1 to 1 to 0 to 2
        int const d_y = other.y - this->y + 1;
        int const d_z = other.z - this->z + 1;

        constexpr int dy_multiplier = 3;
        constexpr int dz_multiplier = 9;

        return 1 << (d_x + (d_y * dy_multiplier ) + (d_z * dz_multiplier ));
    }



    friend std::ostream& operator<<(std::ostream& os, const Integer3D& v) {
        os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
        return os;
    }
    [[nodiscard]] bool not_zero() const; ///< Method to check if the vector is not zero.

    bool operator==(const Integer3D& other) const; ///< Checks equality of two integer vectors.

    Integer3D operator >=(const double& other) const; ///< Compares if this vector is greater than or equal to a scalar.
    Integer3D operator <(const double& other) const; ///< Compares if this vector is less than a scalar.
    Integer3D operator >=(const Vector3D& other) const; ///< Compares if this vector is greater than or equal to another vector.
};


#endif //FLUIDSIMULATION_VECTOR_HPP
