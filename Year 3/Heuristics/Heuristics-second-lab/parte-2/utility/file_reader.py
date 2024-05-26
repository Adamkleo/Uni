import csv

def parse_map(file_path):
    elements = {'N': 'non_contagious_patient', 'C': 'contagious_patient',
                'CC': 'contagious_care_center', 'CN': 'non_contagious_care_center',
                'P': 'parking', 'X': 'obstacle'}
    grid = []
    interests = {'parking': None, 'contagious_patients': [],
                 'non_contagious_patients': [], 'contagious_care_center': None,
                 'non_contagious_care_center': None}
    
    with open(file_path, mode='r') as file:
        reader = csv.reader(file, delimiter=';')
        for row_idx, row in enumerate(reader):
            grid_row = [int(value) if value.isdigit() else value for value in row]
            grid.append(grid_row)
            for col_idx, value in enumerate(row):
                if value in elements.keys():
                    if value == 'P':
                        interests['parking'] = (row_idx, col_idx)
                    elif value == 'C':
                        interests['contagious_patients'].append((row_idx, col_idx))
                    elif value == 'N':
                        interests['non_contagious_patients'].append((row_idx, col_idx))
                    elif value == 'CC':
                        interests['contagious_care_center'] = (row_idx, col_idx)
                    elif value == 'CN':
                        interests['non_contagious_care_center'] = (row_idx, col_idx)
    return grid, interests
