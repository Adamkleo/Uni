import sys
import time
from utility.file_reader import parse_map
from utility.state import State

""" A* """


def a_star(initial_state):
    open_list = [initial_state]
    closed_list = []
    success = False
    while len(open_list) > 0 and not success:
        index_state, current_state = min(
            enumerate(open_list), key=lambda state: state[1].total_cost)
        closed_list.append(open_list.pop(index_state))
        if check_final_state(current_state):
            return current_state, len(open_list) + len(closed_list)
        for operator in ("up", "down", "right", "left"):
            new_state = current_state.move(operator)
            if not valid_state(new_state):
                continue
            if new_state in open_list:
                old_index = open_list.index(new_state)
                if new_state.total_cost < open_list[old_index].total_cost:
                    open_list.pop(old_index)
                    open_list.append(new_state)
            else:
                open_list.append(new_state)
    return None, len(open_list) + len(closed_list)





""" PROBLEM CREATION AND UPDATING """

def grid_data(grid):
    positions = {"N": [], "C": [], "P": [], "CN": [], "CC": []}
    for i, row in enumerate(grid):
        for j, cell in enumerate(row):
            if cell in positions:
                if cell in ["CN", "CC", "P"]:
                    positions[cell] = [i, j]
                else:
                    positions[cell].append([i, j])
    return positions['N'], positions['C'], positions['P'], positions['CN'], positions['CC']


def find_parking_cell(grid):
    for i, row in enumerate(grid):
        for j, cell in enumerate(row):
            if cell == "P":
                return [i, j]
    return None  # Return None if no parking cell is found


def generate_initial_state(grid):
    parking_index = find_parking_cell(grid)
    if parking_index is None:
        raise ValueError("No parking cell found in the grid")
    return State(grid, parking_index, [], [], 51, None)


def check_final_state(state):
    data = grid_data(state.grid)
    return all([
        not (data[0] or data[1]),  # No patients left
        not state.contagious_seats,     # No contagious seats
        not state.non_contagious_seats, # No non-contagious seats
        state.grid[state.vehicle_pos[0]][state.vehicle_pos[1]] == "P"  # Vehicle is at parking
    ])


def valid_state(state):
    return state is not None and state.energy > 0


def reconstruct_path(final_state):
    current_state = final_state
    path = []
    while current_state is not None:
        path.append(current_state)
        current_state = current_state.parent
    path.reverse()  # Reversing the path to start from the initial state
    energy_cost = path[-1].actual_cost if path else 0
    plan_length = len(path)
    return path, energy_cost, plan_length


def generate_solution_file(path, solution, filename):
    with open(f"{filename.replace('.csv', '')}-{sys.argv[2]}.output", 'w') as file:
        for state in solution:
            file.write(f"({state.vehicle_pos[0]},{state.vehicle_pos[1]}):{state.grid[state.vehicle_pos[0]][state.vehicle_pos[1]]}:{state.energy}\n")

def generate_statistics_file(time, cost, length, expanded_nodes, filename):
    with open(f"{filename.replace('.csv', '')}-{sys.argv[2]}.stat", 'w') as file:
        file.write(f"Total time: {time: .2f}\n")
        file.write(f"Total cost: {cost}\n")
        file.write(f"Plan length: {length}\n")
        file.write(f"Expanded nodes: {expanded_nodes}\n")

def main():
    input_path = sys.argv[1]
    grid, interests = parse_map(input_path)
    initial_state = generate_initial_state(grid)

    start = time.time()
    final_state, expanded_nodes = a_star(initial_state)
    end = time.time()
    elapsed_time = end - start

    if final_state is None:
        print("No solution found.")
    else:
        path, total_cost, plan_length = reconstruct_path(final_state)
        generate_output(path, grid, elapsed_time, total_cost,
                        plan_length, expanded_nodes)


if __name__ == "__main__":
    main()
