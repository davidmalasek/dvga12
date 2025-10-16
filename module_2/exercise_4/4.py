# Author: David Malášek

import random

def roll_dice():
    return random.randint(1, 6)

array = []

for i in range(100):
    array.append(roll_dice() + roll_dice())

print(str(array.count(2)) + " times the sum was 2")
print(str(array.count(3)) + " times the sum was 3")
print(str(array.count(4)) + " times the sum was 4")
print(str(array.count(5)) + " times the sum was 5")
print(str(array.count(6)) + " times the sum was 6")
print(str(array.count(7)) + " times the sum was 7")
print(str(array.count(8)) + " times the sum was 8")
print(str(array.count(9)) + " times the sum was 9")
print(str(array.count(10)) + " times the sum was 10")
print(str(array.count(11)) + " times the sum was 11")
print(str(array.count(12)) + " times the sum was 12")