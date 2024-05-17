from typing import List, Tuple
import re
from .vehicle import Vehicle

def convert_to_boolean(char: str) -> bool:
    """Converts a character to a boolean.
    
    Args:
    char (str): The character to convert ('C' or 'X').

    Returns:
    bool: True if 'C', False if 'X'.

    Raises:ß
    ValueError: If the character is not 'C' or 'X'.
    """
    if char == 'C':
        return True
    elif char == 'X':
        return False
    else:
        raise ValueError("Invalid character for boolean conversion.")

def parse_dimensions(line: str) -> Tuple[int, int]:
    """Parses the dimensions line to extract rows and columns.

    Args:
    line (str): The line containing dimensions in 'NxM' format.

    Returns:
    Tuple[int, int]: A tuple containing rows (N) and columns (M).

    Raises:
    ValueError: If the line doesn't match the expected format.
    """

    # Match the line with the NxM digits regular expression
    if not re.match(r"\d+x\d+", line):
        raise ValueError("Invalid dimensions format.")
    
    # Map the value before the 'x' to rows and after the x to columns
    rows, columns = map(int, line.split('x'))
    return rows, columns

def parse_electric_spaces(line: str) -> List[Tuple[int, int]]:
    """Parses the electric spaces line to extract coordinates.

    Args:
    line (str): The line containing electric spaces in 'PE:(x1,y1)(x2,y2)...' format.

    Returns:
    List[Tuple[int, int]]: A list of tuples each representing a coordinate.

    Raises:
    ValueError: If the line doesn't match the expected format.
    """

    # Match the line with the input PE:(x1,y1)(x2,y2)... regular expression
    if not re.match(r"PE:(\(\d+,\d+\))*", line):
        raise ValueError("Invalid electric spaces format.")
    
    # Split the line into two parts using ':' as the delimiter and take the second part.
    # This removes the 'PE:' prefix from the line. For example, "PE:(1,1)(1,2)" becomes "(1,1)(1,2)".
    parts = line.split(':')[1].split(')')

    # Process each part to extract electric space coordinates.
    # The loop iterates over each substring representing an electric space, like "(1,1)".
    electric_spaces = [
        tuple(map(int, space.strip('(').split(',')))  # Remove the parentheses and split by comma.
        for space in parts if space  # Ensure the part is not empty to avoid processing empty strings.
    ]

    # Each substring is converted into a tuple of integers. For example, "(1,1)" becomes (1, 1).
    # The resulting list of tuples represents the electric spaces as coordinates.
    return electric_spaces


def parse_vehicles(lines: List[str]) -> List[Vehicle]:
    """Parses the vehicle lines to create Vehicle objects.

    Args:
    lines (List[str]): The lines containing vehicle information in 'ID-Type-C/X' format.

    Returns:
    List[Vehicle]: A list of Vehicle objects.

    Raises:
    ValueError: If a line doesn't match the expected format.
    """

    # Initialize an empty list to store Vehicle objects.
    vehicles = []

    # Iterate through each line representing a vehicle.
    for line in lines:
        # Validate the format of the vehicle line using regex.
        # The pattern checks for lines in the format "ID-Type-C/X".
        if not re.match(r"\d+-[A-Z]+-[CX]", line):
            raise ValueError(f"Invalid vehicle format in line: {line}")

        # Split the line into parts separated by '-'.
        # For example, "1-TSU-C" is split into ['1', 'TSU', 'C'].
        parts = line.split('-')

        # Extract the vehicle ID, type, and charging status.
        # Convert the ID to an integer and the charging status to a boolean.
        id, type, charging = int(parts[0]), parts[1], convert_to_boolean(parts[2])

        # Create a Vehicle object and add it to the vehicles list.
        vehicles.append(Vehicle(id, type, charging))

    # Return 
    return vehicles


def read_file_line_by_line(file_path: str) -> Tuple[int, int, List[Tuple[int, int]], List[Vehicle]]:
    """Reads a file line by line and parses its content.

    Args:
    file_path (str): The path to the file.

    Returns:
    Tuple[int, int, List[Tuple[int, int]], List[Vehicle]]: Parsed rows, columns, electric spaces, and vehicles.

    Raises:
    FileNotFoundError: If the file is not found.
    IOError: If an error occurs during file reading.
    """
    
    # Try to open and read the file.
    try:
        # Open the file at the given path with read and UTF-8 encoding.
        with open(file_path, 'r', encoding='utf-8') as file:
            # Read all lines from the file.
            lines = file.readlines()

            # Parse the first line to get the dimensions (rows and columns).
            rows, columns = parse_dimensions(lines[0].strip())

            # Parse the second line to get the electric spaces.
            electric_spaces = parse_electric_spaces(lines[1].strip())

            # Parse the remaining lines to get the vehicle information.
            # Stripping each line to remove leading/trailing whitespaces.
            vehicles = parse_vehicles([line.strip() for line in lines[2:]])

            # Return the parsed data as a tuple.
            return rows, columns, electric_spaces, vehicles

    # Handle specific exceptions related to file operations.
    except FileNotFoundError:
        # Raise an error if the file is not found.
        raise FileNotFoundError(f"The file '{file_path}' was not found.")
    except IOError as e:
        # Raise an error if there's an IO problem (e.g., permission issues).
        raise IOError(f"An error occurred while reading the file '{file_path}': {e}")
