import math

class Circle:
    def __init__(self, radius):
        self.__radius = radius

    def get_radius(self):
        return self.__radius
    
    def set_radius(self, new_radius):
        self.__radius = new_radius
    
    def get_area(self):
        return math.pi * pow(self.__radius, 2)

    def get_circumference(self):
        return 2 * math.pi * self.__radius

if __name__ == "__main__":
    r = float(input("Enter the radius: "))
    c = Circle(r)
    print("Area:", c.get_area())
    print("Circumference:", c.get_circumference())