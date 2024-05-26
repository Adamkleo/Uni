import sys, os, csv, time
from constraint import Problem, AllDifferentConstraint
from utility.file_reader import read_file_line_by_line

# Initialize the problem
problem = Problem()



try:
    # Check if a command-line argument is provided
    if len(sys.argv) < 2:
        raise ValueError("No file path provided. Please provide a file path as an argument.")

    # Attempt to read the file and process it
    rows, columns, electric_spaces, vehicles = read_file_line_by_line(sys.argv[1])
    print(f"Rows: {rows}, Columns: {columns}")
    print(f"Electric Spaces: {electric_spaces}")
    print(f"Vehicles: {[str(vehicle) for vehicle in vehicles]}")
    print("\n\n")

except (FileNotFoundError, ValueError) as e:
    print(e)
    sys.exit(1)  # Exit the script after printing the error message
except Exception as e:
    print(f"An error occurred: {e}")
    sys.exit(1)  # Exit the script after printing the error message


vehicles.sort(key=lambda v: (v.v_type == "TSU", v.contains_freezer), reverse=True)


parking_spaces = [(i, j) for i in range(1, rows + 1) for j in range(1, columns + 1)]

# Assign each vehicle's ID a parking space as a variable, with the domain being all parking spaces
for vehicle in vehicles:
    if vehicle.contains_freezer:
        # Assign only electric spaces for vehicles with a freezer
        problem.addVariable(vehicle.v_id, electric_spaces)
    else:
        # Assign all parking spaces for other vehicles
        problem.addVariable(vehicle.v_id, parking_spaces)


# Apply the AllDifferentConstraint to ensure each vehicle is assigned a unique parking space
problem.addConstraint(AllDifferentConstraint())


def tsu_constraint(*positions):
    vehicle_positions = dict(zip([v.v_id for v in vehicles], positions))
    position_to_type = {pos: v.v_type for v, pos in zip(vehicles, positions)}
    checked_rows = set()

    for vehicle in vehicles:
        if vehicle.v_type == "TSU":
            row, tsu_col = vehicle_positions[vehicle.v_id]
            # Check the constraint only for the first TSU vehicle in each row
            if row not in checked_rows:
                checked_rows.add(row)
                for col in range(tsu_col + 1, columns + 1):
                    front_position = (row, col)
                    if front_position in position_to_type and position_to_type[front_position] != "TSU":
                        return False
    return True

# Add the custom constraint to the problem
problem.addConstraint(tsu_constraint, [v.v_id for v in vehicles])

def vertical_adjacency_constraint(*positions):
    rows = max(pos[0] for pos in positions)  # Find the number of rows based on positions
    occupied = set(positions)  # Create a set of occupied positions for efficient lookup

    for pos in positions:
        row, col = pos
        above = (row - 1, col) if row > 1 else None
        below = (row + 1, col) if row < rows else None

        above_occupied = above in occupied if above else False
        below_occupied = below in occupied if below else False

        # If both above and below are occupied, or if it's in the top row and below is occupied, or in the bottom row and above is occupied
        if (above_occupied and below_occupied) or (row == 1 and below_occupied) or (row == rows and above_occupied):
            return False

    return True

# Apply the constraint to the problem
problem.addConstraint(vertical_adjacency_constraint, [v.v_id for v in vehicles])






start_time = time.perf_counter()  # Start high-resolution timing

solution_count = 0
for sol in problem.getSolutionIter():
    # Increment solution counter
    solution_count += 1
    
    # Print the solution number
    print(f"Solution {solution_count}:")

    # Print the formatted solution mapping
    for vehicle in vehicles:
        position = sol[vehicle.v_id]  # Make sure to use vehicle.v_id here
        print(f"{vehicle} at position {position}")
    
    print("-" * 30)  # Add a separator line for better readability

# Check if any solutions were found
if solution_count == 0:
    print("No solution found!")
else:
    print(f"Total solutions found: {solution_count}")

end_time = time.perf_counter()  # End high-resolution timing
print(f"Time taken: {end_time - start_time:.2f} seconds")




def write_first_solution_to_csv(vehicles, columns, rows, solution_count):
    """
    Writes the solution grid to a CSV file in the CSP-tests directory.

    :param vehicles: List of vehicle objects.
    :param columns: Number of columns in the grid.
    :param rows: Number of rows in the grid.
    :param solution_count: The count of solutions found.
    """
    # Extract the base name without the .txt extension
    base_name = os.path.splitext(os.path.basename(sys.argv[1]))[0]
    # Change the output directory to CSP-tests
    output_dir = "CSP-tests"
    filename = f"{output_dir}/{base_name}.csv"
    first_sol = problem.getSolution()

    # Ensure the CSP-tests directory exists
    os.makedirs(output_dir, exist_ok=True)

    # Create vehicle positions from the first solution
    vehicle_positions = {str(vehicle): first_sol[vehicle.v_id] for vehicle in vehicles}

    # Create a 2D grid with None to indicate empty spaces
    grid = [[None for _ in range(columns)] for _ in range(rows)]

    # Write vehicle names at their respective positions
    for vehicle_str, position in vehicle_positions.items():
        row, col = position
        grid[row - 1][col - 1] = vehicle_str.upper()  # Adjust indices to start from 0

    # Write the grid to a CSV file
    with open(filename, 'w', newline='') as csvfile:
        csv_writer = csv.writer(csvfile)

        # Optionally, write the solution_count as a header or comment
        csv_writer.writerow([f"{solution_count}"])

        # Write the grid rows
        for row in grid:
            # Replace None with '--' or similar placeholder for empty spaces
            csv_writer.writerow([cell if cell is not None else '-' for cell in row])

    print(f"CSV file '{filename}' generated successfully.\n\n")

    

# Call the function
write_first_solution_to_csv(vehicles, columns, rows, solution_count)






