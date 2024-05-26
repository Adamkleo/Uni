import csv

DEFAULT_COST = 1

class Action:
    
    def __init__(self, name: str, file_name: str, number_of_states: int, costs_file_name=None):
        
        self.name = name
        self.file_name = file_name
        self.__costs_file_name = costs_file_name
        self.__number_of_states = number_of_states
        if self.__costs_file_name:
            self.costs = self.__csv_to_list(self.__costs_file_name)
        else:
            self.costs = (DEFAULT_COST,)*self.__number_of_states
        

        
        
    def __csv_to_list(self, file_name):
        with open(file_name) as f:
            reader = csv.reader(f)
            lst = list(reader)
        return [float(x) for inner in lst for x in inner]
    
        