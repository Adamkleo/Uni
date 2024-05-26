from probability import ProbabilityGeneration
from action import Action



NUMBER_OF_ITERATIONS = 50


class ThermostatMDP:
    
    
    
    def __init__(self, goal_state: int, actions: tuple):
        self.states = tuple(x + y for x in range(16, 26) for y in (0, 0.5) if x + y <= 25)
        self.actions = actions
        self.goal_state = goal_state
        self.transitions_per_action = ProbabilityGeneration(self.actions).transitions_per_action


        
    def __bellman(self, num_iterations):
        goal_state_index = self.states.index(self.goal_state)
        number_of_states = len(self.states)
        v = [[0] * num_iterations for _ in range(number_of_states)]
        last_action_indices = [0] * number_of_states  # Store the action indices at the last iteration

        for i in range(len(v[goal_state_index])):
            v[goal_state_index][i] = 0

        for i in range(number_of_states):
            if i == 0:
                v[i][1] = round(min(action.costs[0] for action in self.actions), 2)
            else:
                v[i][0] = 0

        for k in range(1, num_iterations):
            for i in range(number_of_states):
                action_values = []

                for action in self.actions:
                    value = action.costs[i]

                    for j in range(number_of_states):
                        value += self.transitions_per_action[action.name][i][j] * v[j][k-1]

                    action_values.append(value)

                if i != goal_state_index:
                    min_value = min(action_values)
                    v[i][k] = round(min_value, 2)
                    if k == num_iterations - 1:
                        last_action_indices[i] = action_values.index(min_value)  # Store the index of the minimum action at the last iteration

        
        best_action_names = [self.actions[index].name for index in last_action_indices]

        return v, best_action_names


    
    def __str__(self):
        path = ""
        counter = 0
        v_simulation, best_actions = self.__bellman(NUMBER_OF_ITERATIONS)
        for state_iterations, best_action in zip(v_simulation, best_actions):
            last_iteration = len(state_iterations) - 1
            path += f"At temperature {counter + 16} with V({counter + 16}) = {state_iterations[last_iteration]}, the best action to take is {best_action}\n"
            counter += 0.5
        return path



"""
HOW TO USE:


For any given MDP, input your number of states, create as many actions as you ned for your MDP.
The bellman function works for an arbitrary number of actions. The file path to the probability
dsitribution tables are required. If you have unique costs for each state, the file path to the
costs of each action are required, but if no costs_file_name is put, the costs for the action
will default to 1. Number of states is a constant for your given MDP. Actions are passed as a
tuple and simply printing the MDP instance, in this case the thermostat, will give the desired
output.  

"""

# Number of states
NUMBER_OF_STATES = 19

# Actions for our MDP task
action_on = Action(name="ON", file_name="Data/ON.csv", costs_file_name="Data/ON_COSTS.csv", number_of_states=NUMBER_OF_STATES)
action_off = Action(name="OFF", file_name="Data/OFF.csv", costs_file_name="Data/OFF_COSTS.csv", number_of_states=NUMBER_OF_STATES)

# Creation of the thermostat
Thermostat = ThermostatMDP(goal_state = 22.0, actions = (action_on, action_off))
print(Thermostat)

