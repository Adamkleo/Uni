import csv


class ProbabilityGeneration:
    
    
    def __init__(self, actions: tuple):
        
        self.actions = actions
        self.transitions_per_action = self.__populate_transitions()
        
                
    def __populate_transitions(self): 
        transitions = {}
        for action in self.actions:
            transitions[action.name] = self.__csv_to_list(action.file_name)
            
        return transitions
        
        
    def __csv_to_list(self, file_name):
        with open(file_name) as f:
            reader = csv.reader(f)
            lst = list(reader)
        return [[float(x) for x in inner] for inner in lst]
            
            
    
