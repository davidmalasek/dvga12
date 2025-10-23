# Author: David Malášek

import pygame
from sprites.sprite import Sprite


class Brick(Sprite):
    def __init__(self, x, y, width, height, color, hits=1, points=10):
        super().__init__(x, y, width, height, color)
        self.hits = hits
        self.points = points

    def hit(self):
        self.hits -= 1
        if self.hits <= 0:
            return True
        else:
            r = self.color[0] - 80
            g = self.color[1] - 80
            b = self.color[2] - 80
            if r < 0:
                r = 0
            if g < 0:
                g = 0
            if b < 0:
                b = 0
            self.color = (r, g, b)
            return False

    def draw(self, surface):
        pygame.draw.rect(surface, self.color, self.rect)
        pygame.draw.rect(surface, (0, 0, 0), self.rect, 2)
