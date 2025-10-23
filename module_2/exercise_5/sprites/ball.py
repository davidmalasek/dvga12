# Author: David Malášek

import pygame
from sprites.sprite import Sprite


class Ball(Sprite):
    def __init__(self, x, y, radius, color, speed_x, speed_y):
        super().__init__(x - radius, y - radius, radius * 2, radius * 2, color)

        self.radius = radius
        self.speed_x = speed_x
        self.speed_y = speed_y

        self.rect = pygame.Rect(self.x, self.y, self.width, self.height)

    def update(self, screen):
        self.x += self.speed_x
        self.y += self.speed_y

        if self.x <= 0 or self.x + self.width >= screen.get_width():
            self.speed_x *= -1

        if self.y <= 0:
            self.speed_y *= -1

        self.update_rect()

    def draw(self, surface):
        center_x = int(self.x + self.radius)
        center_y = int(self.y + self.radius)
        pygame.draw.circle(surface, self.color, (center_x, center_y), self.radius)
