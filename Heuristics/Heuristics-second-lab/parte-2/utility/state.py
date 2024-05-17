import copy, sys
from .heuristic_handler import *
from .constants import CONTAGIOUS_SEATS, NON_CONTAGIOUS_SEATS


class State:
    def __init__(self, grid, vehicle_pos, contagious_seats, non_contagious_seats, energy, parent):
        self.grid = copy.deepcopy(grid)
        self.vehicle_pos = copy.deepcopy(vehicle_pos)
        self.contagious_seats = copy.deepcopy(contagious_seats)
        self.non_contagious_seats = copy.deepcopy(non_contagious_seats)
        self.energy = energy
        self.parent = parent
        self.actual_cost = 0 if parent is None else self.parent.actual_cost + self.estimated_cost()
        self.total_cost = self.get_total_cost()
    
    def get_total_cost(self):
        return self.actual_cost + self.calculate_hueristic()

    def estimated_cost(self):
        cell_actions = {
            "N": (self.pickup_non_contagious, 1),
            "C": (self.pickup_contagious, 1),
            "P": (self.reset_energy, 1),
            "CN": (self.dropoff_non_contagious, 1),
            "CC": (self.dropoff_contagious, 1)
        }

        current_cell = self.grid[self.vehicle_pos[0]][self.vehicle_pos[1]]
        current_cell_str = str(current_cell)  # Convert current cell to string for isdigit check

        if current_cell_str in cell_actions:
            action, cost = cell_actions[current_cell_str]
        else:
            action = self.default_action
            cost = 0 if not current_cell_str.isdigit() else int(current_cell_str)

        self.energy -= cost
        action()
        return cost

    def reset_energy(self):
        self.energy = 50

    def default_action(self):
        pass

    def move(self, direction):
        direction_deltas = {
            'up': (-1, 0), 'down': (1, 0), 'right': (0, 1), 'left': (0, -1)}
        dx, dy = direction_deltas.get(direction, (0, 0))
        new_position = [self.vehicle_pos[0] + dx, self.vehicle_pos[1] + dy]

        if not (0 <= new_position[0] < len(self.grid) and 0 <= new_position[1] < len(self.grid[0])):
            return None
        if self.grid[new_position[0]][new_position[1]] == "X":
            return None

        return State(self.grid, new_position, self.contagious_seats, self.non_contagious_seats, self.energy, self)
    
    def pickup_non_contagious(self):
        if self.can_pickup("N"):
            self.non_contagious_seats.append("N")
            self.update_grid_cell("1")

    def pickup_contagious(self):
        if self.can_pickup("C"):
            self.contagious_seats.append("C")
            self.update_grid_cell("1")

    def dropoff_non_contagious(self):
        if not self.has_contagious():
            self.clear_seats()

    def dropoff_contagious(self):
        if self.has_contagious():
            self.contagious_seats.clear()

    def can_pickup(self, type):
        if type == "N":
            return (len(self.non_contagious_seats) < NON_CONTAGIOUS_SEATS and
                    not self.has_contagious() and
                    len(self.contagious_seats) < CONTAGIOUS_SEATS)
        elif type == "C":
            return len(self.contagious_seats) < CONTAGIOUS_SEATS and not self.has_non_contagious()

    def has_non_contagious(self):
        return "N" in self.contagious_seats

    def has_contagious(self):
        return "C" in self.contagious_seats

    def clear_seats(self):
        self.non_contagious_seats.clear()
        self.contagious_seats.clear()

    def update_grid_cell(self, value):
        self.grid[self.vehicle_pos[0]][self.vehicle_pos[1]] = value

    def calculate_hueristic(self):



        if sys.argv[2] == "1":
            patient_positions_n, patient_positions_c, parking_position, cn_position, cc_position = grid_data(self.grid)
            target_distance = calculate_target_distance(self, patient_positions_n, patient_positions_c, parking_position, cn_position, cc_position)
            if target_distance > self.energy:
                distance_to_parking = calculate_distance(self.vehicle_pos, parking_position)
                target_distance = float('inf') if distance_to_parking > self.energy else distance_to_parking
            return target_distance + ((len(patient_positions_c) + len(patient_positions_n)) * 5 + len(self.contagious_seats) + len(self.non_contagious_seats)) * 100

        if sys.argv[2] == "2":
            patient_positions_n, patient_positions_c, parking_position, cn_position, cc_position = grid_data(self.grid)
            heuristic_value = calculate_heuristic_2(self, patient_positions_n, patient_positions_c, parking_position, cn_position, cc_position)
            if heuristic_value > self.energy:
                distance_to_parking = calculate_distance(self.vehicle_pos, parking_position)
                heuristic_value = float('inf') if distance_to_parking > self.energy else distance_to_parking
            return heuristic_value + ((len(patient_positions_c) + len(patient_positions_n)) * 2 + len(self.contagious_seats) + len(self.non_contagious_seats)) * 10



    def __repr__(self):
        return (f"State => Vehicle Position: {self.vehicle_pos}\n"
                f"          In Vehicle: {
                    self.contagious_seats + self.non_contagious_seats}\n"
                f"          Energy: {self.energy}\n\n")

    def __eq__(self, other):
        return (self.grid == other.grid and self.vehicle_pos == other.vehicle_pos and
                self.contagious_seats == other.contagious_seats and
                self.energy == other.energy and
                self.non_contagious_seats == other.non_contagious_seats)



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
