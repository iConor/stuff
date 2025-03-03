import sys
import json

file = sys.argv[1]

with open(file, 'r') as data_file:
    data_blob = json.load(data_file)

sorted_data = sorted(data_blob)

with open(file, 'w') as test_file:
    json.dump(sorted_data, test_file)