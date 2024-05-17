#include "vector.hpp"
#include <iostream>
//#include "helpers.hpp"



/**
 * @brief Checks if two Vector3D objects are equal by comparing their components.
 * @param other A constant reference to another Vector3D object.
 * @return True if the vectors are equal, false otherwise.
 */
bool Vector3D::operator==(const Vector3D& other) const {
    return areEqual(x, other.x) && areEqual(y, other.y) && areEqual(z, other.z);
}

/**
 * @brief Applies a bitwise AND mask to a Vector3D object.
 * @param mask A constant reference to the masking Vector3D object.
 * @return A new Vector3D object after applying the mask.
 */
Vector3D Vector3D::operator&(const Vector3D& mask) const {
    return {mask.x != 0.0 ? x : 0.0, mask.y != 0.0 ? y : 0.0, mask.z != 0.0 ? z : 0.0};
}

/**
 * @brief Applies a NAND mask to a Vector3D object.
 * @param mask A constant reference to the masking Vector3D object.
 * @return A new Vector3D object after applying the NAND mask.
 */
Vector3D Vector3D::operator^(const Vector3D& mask) const {
    return {mask.x != 0.0 ? 0.0 : x, mask.y != 0.0 ? 0.0 : y, mask.z != 0.0 ? 0.0 : z};
}

/**
 * @brief Applies a bitwise AND mask to a Vector3D object using an integer mask.
 * @param mask An integer value used as a mask.
 * @return A new Vector3D object after applying the mask.
 */
Vector3D Vector3D::operator&(int mask) const {
    return {
            (mask & 1) != 0 ? x : 0,
            (mask & 2) != 0 ? y : 0,
            (mask & 4) != 0 ? z : 0
    };
}


/**
 * @brief Applies a NAND mask to a Vector3D object using an integer mask.
 * @param mask An integer value used as a mask.
 * @return A new Vector3D object after applying the NAND mask.
 */
Vector3D Vector3D::operator^(int mask) const {
    return {
            (mask & 1) != 0 ? 0 : x,
            (mask & 2) != 0 ? 0 : y,
            (mask & 4) != 0 ? 0 : z
    };
}

// Arithmetic operators for vector operations.
/**
 * @brief Adds two Vector3D objects.
 * @param other A constant reference to another Vector3D object.
 * @return The sum of the two vectors as a new Vector3D object.
 */
Vector3D Vector3D::operator+(const Vector3D& other) const {
    return {x + other.x, y + other.y, z + other.z};
}

/**
 * @brief Adds a scalar value to all components of a Vector3D object.
 * @param other The scalar value to add.
 * @return A new Vector3D object with each component incremented by the scalar.
 */
Vector3D Vector3D::operator+(const double& other) const {
    return {x + other, y + other, z + other};
}

/**
 * @brief Subtracts another Vector3D object from this vector.
 * @param other A constant reference to another Vector3D object.
 * @return The result of the subtraction as a new Vector3D object.
 */
Vector3D Vector3D::operator-(const Vector3D& other) const {
    return {x - other.x, y - other.y, z - other.z};
}

/**
 * @brief Subtracts a scalar value from all components of a Vector3D object.
 * @param other The scalar value to subtract.
 * @return A new Vector3D object with each component decremented by the scalar.
 */
Vector3D Vector3D::operator-(const double& other) const {
    return {x - other, y - other, z - other};
}

/**
 * @brief Multiplies this Vector3D object with another vector, element-wise.
 * @param other A constant reference to another Vector3D object.
 * @return The element-wise product as a new Vector3D object.
 */
Vector3D Vector3D::operator*(const Vector3D& other) const {
    return {x * other.x, y * other.y, z * other.z};
}

/**
 * @brief Multiplies all components of this Vector3D object by a scalar.
 * @param other The scalar value to multiply with.
 * @return A new Vector3D object with each component scaled by the scalar.
 */
Vector3D Vector3D::operator*(const double& other) const {
    return {x * other, y * other, z * other};
}

/**
 * @brief Divides all components of this Vector3D object by a scalar.
 * @param other The scalar value to divide by.
 * @return A new Vector3D object with each component divided by the scalar.
 */
Vector3D Vector3D::operator/(const double& other) const {
    return {x / other, y / other, z / other};
}

/**
 * @brief Divides this Vector3D object by another vector, element-wise.
 * @param other A constant reference to another Vector3D object.
 * @return The element-wise division result as a new Vector3D object.
 */
Vector3D Vector3D::operator/(const Vector3D& other) const {
    return {x / other.x, y / other.y, z / other.z};
}

// Compound assignment operators for vector operations.
/**
 * @brief Adds another Vector3D object to this vector and assigns the result to this vector.
 * @param other A constant reference to another Vector3D object.
 * @return A reference to this vector after addition.
 */
Vector3D& Vector3D::operator+=(const Vector3D& other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

/**
 * @brief Subtracts another Vector3D object from this vector and assigns the result to this vector.
 * @param other A constant reference to another Vector3D object.
 * @return A reference to this vector after subtraction.
 */
Vector3D& Vector3D::operator-=(const Vector3D& other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

/**
 * @brief Multiplies this vector with another Vector3D object element-wise and assigns the result to this vector.
 * @param other A constant reference to another Vector3D object.
 * @return A reference to this vector after multiplication.
 */
Vector3D& Vector3D::operator*=(const Vector3D& other) {
    x *= other.x;
    y *= other.y;
    z *= other.z;
    return *this;
}

// Comparison operators for vector operations.
/**
 * @brief Checks if this vector is less than or equal to another vector in all components.
 * @param other A constant reference to another Vector3D object.
 * @return True if this vector is less than or equal to the other vector in all components.
 */
bool Vector3D::operator<=(const Vector3D& other) const {
    return (x <= other.x) && (y <= other.y) && (z <= other.z);
}

/**
 * @brief Checks if this vector is less than or equal to a scalar value in all components.
 * @param other The scalar value to compare with.
 * @return True if this vector is less than or equal to the scalar in all components.
 */
bool Vector3D::operator<=(const double& other) const {
    return (x <= other) && (y <= other) && (z <= other);
}

/**
 * @brief Checks if this vector is greater than or equal to another vector in all components.
 * @param other A constant reference to another Vector3D object.
 * @return True if this vector is greater than or equal to the other vector in all components.
 */
bool Vector3D::operator>=(const Vector3D& other) const {
    return (x >= other.x) && (y >= other.y) && (z >= other.z);
}



/**
 * @brief Computes and returns the squared Euclidean length of the vector.
 *        This is more efficient than length() as it avoids the square root calculation.
 * @return The squared length of the vector as a double value.
 */
double Vector3D::squaredLength() const {
    return x * x + y * y + z * z;
}

/**
 * @brief Outputs the integer vector's coordinates to standard output.
 *        This function is part of the Integer3D class.
 */
void Integer3D::printCoordinates() const {
    std::cout << "x: " << x << ", y: " << y << ", z: " << z << "\n";
}


Vector3D Vector3D::operator>=(const double &other) const {
    return {x >= other ? 1.0 : 0.0, y >= other ? 1.0 : 0.0, z >= other ? 1.0 : 0.0};
}

Vector3D Vector3D::operator<(const double &other) const {
    return {x < other ? 1.0 : 0.0, y < other ? 1.0 : 0.0, z < other ? 1.0 : 0.0};
}

Vector3D& Vector3D::operator*=(const double &other) {
    x *= other;
    y *= other;
    z *= other;
    return *this;
}

bool Vector3D::operator!=(const Vector3D &other) const {
    return !(*this == other);
}


/**
 * @brief Subtracts the other vector from this vector.
 * @param other A constant reference to another Integer3D object.
 * @return The result of the subtraction as a new Integer3D object.
 */
Integer3D Integer3D::operator-(const Integer3D &other) const {
    return {this->x - other.x, this->y - other.y, this->z - other.z};
}

/**
 * @brief Calculates a bitmask representing the relative position of the other vector to this vector.
 *        The bitmask is a 6-bit integer where each bit represents the relative position of the other vector
 *        in each dimension (x, y, z). The center position (0, 0, 0) is excluded from the bitmask.
 * @param other A constant reference to another Integer3D object.
 * @return An integer mask where each bit represents the relative position of the other vector in each dimension.
 */

Integer3D Integer3D::operator>=(const double &other) const {
    return {x >= other ? 1 : 0, y >= other ? 1 : 0, z >= other ? 1 : 0};
}

Integer3D Integer3D::operator<(const double &other) const {
    return {x < other ? 1 : 0, y < other ? 1 : 0, z < other ? 1 : 0};
}


bool Integer3D::not_zero() const {
    return x != 0 || y != 0 || z != 0;
}

Integer3D Integer3D::operator>=(const Vector3D &other) const {
    return {x >= other.x ? 1 : 0, y >= other.y ? 1 : 0, z >= other.z ? 1 : 0};
}

bool Integer3D::operator==(const Integer3D &other) const {
    return x == other.x && y == other.y && z == other.z;
}


