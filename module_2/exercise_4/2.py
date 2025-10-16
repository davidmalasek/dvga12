# Author: David Malášek

input_char = ''
characters = []
uppercase_count = 0

while input_char != '?':
    input_char = input()
    characters.append(input_char)

for i in characters:
    if i.isupper():
        uppercase_count+= 1

print(uppercase_count)