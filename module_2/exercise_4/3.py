# Author: David Malášek

array = []

for i in range(5):
    string = input()
    array.append(string)


sorted_array = sorted(array)

print()

for i in sorted_array:
    print(i)