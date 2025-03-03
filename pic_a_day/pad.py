import random
import json

# Temporarily disable techniques while I figure out how to handle my broken camera.
# file_list = [ "pad_subjects.json", "pad_techniques.json", "pad_themes.json" ]
file_list = [ "pad_subjects.json", "pad_themes.json" ]

rand_max = len(file_list) - 1
rand_one = random.randint(0, rand_max)
rand_two = random.randint(0, rand_max)

while rand_two == rand_one:
    rand_two = random.randint(0, rand_max)

data_one = []
data_two = []

with open(file_list[rand_one]) as file_one:
    data_one = json.load(file_one)

with open(file_list[rand_two]) as file_two:
    data_two = json.load(file_two)

item_one = random.randint(0, len(data_one)-1)
item_two = random.randint(0, len(data_two)-1)

prompt_one = data_one[item_one]
prompt_two = data_two[item_two]

print(prompt_one)
print(prompt_two)
