import math
from .constants import CONTAGIOUS_SEATS, NON_CONTAGIOUS_SEATS




""" HEURISTIC 1 UTILITY FUNCTIONS """

def calculate_distance(position_1, position_2):
    if position_2 is not None:
        return math.sqrt((position_1[0] - position_2[0]) ** 2 + (position_1[1] - position_2[1]) ** 2)
    else:
        return float('inf')

def calculate_target_distance(state, patient_positions_n, patient_positions_c, parking_position, cn_position, cc_position):
    if ((len(patient_positions_n) + len(patient_positions_c) + len(state.contagious_seats) + len(state.non_contagious_seats)) == 0):
        return calculate_distance(state.vehicle_pos, parking_position)
    if "C" in state.contagious_seats:
        return calculate_distance(state.vehicle_pos, cc_position) if len(patient_positions_c) == 0 or len(state.contagious_seats) == CONTAGIOUS_SEATS else min_distance_to_patients(state, patient_positions_c)
    if not "C" in state.contagious_seats:
        return calculate_distance(state.vehicle_pos, cn_position) if len(patient_positions_n) == 0 or len(state.non_contagious_seats) == NON_CONTAGIOUS_SEATS else min_distance_to_patients(state, patient_positions_n)
    return float('inf')

def min_distance_to_patients(state, patient_positions):
    return min(calculate_distance(state.vehicle_pos, pos) for pos in patient_positions)


""" HEURISTIC 2 UTLITY FUNCTIONS """

def calculate_heuristic_2(state, patient_positions_n, patient_positions_c, parking_position, cn_position, cc_position):
    # When no patients are left, direct to parking
    if not patient_positions_n and not patient_positions_c and not state.contagious_seats and not state.non_contagious_seats:
        return calculate_distance(state.vehicle_pos, parking_position)

    # Dropping off contagious patients
    if "C" in state.contagious_seats and (not patient_positions_c or len(state.contagious_seats) == CONTAGIOUS_SEATS):
        return drop_off_contagious(state, patient_positions_c, cc_position)

    # Dropping off non-contagious patients
    if not state.contagious_seats and (not patient_positions_n or len(state.non_contagious_seats) == NON_CONTAGIOUS_SEATS):
        return calculate_distance(state.vehicle_pos, cn_position)

    # Picking up nearest non-contagious patient
    if not state.contagious_seats:
        return pick_up_nearest(state, patient_positions_n, cn_position)

    # Picking up nearest contagious patient
    return pick_up_nearest(state, patient_positions_c, cc_position)

def drop_off_contagious(state, patient_positions_c, cc_position):
    distance_to_cc = calculate_distance(state.vehicle_pos, cc_position)
    if patient_positions_c:
        nearest_c_patient_pos = min(patient_positions_c, key=lambda pos: calculate_distance(state.vehicle_pos, pos))
        distance_to_nearest_c = calculate_distance(state.vehicle_pos, nearest_c_patient_pos)
        return min(distance_to_cc, distance_to_nearest_c)
    return distance_to_cc

def pick_up_nearest(state, patient_positions, center_position):
    nearest_patient_pos = min(patient_positions, key=lambda pos: calculate_distance(state.vehicle_pos, pos))
    distance_to_nearest = calculate_distance(state.vehicle_pos, nearest_patient_pos)
    return min(distance_to_nearest, calculate_distance(state.vehicle_pos, center_position))
