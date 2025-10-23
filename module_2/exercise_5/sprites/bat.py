# Author: David Malášek

import pygame
from sprites.sprite import Sprite


class Bat(Sprite):
    def __init__(self, x, y, width, height, color, speed):
        super().__init__(x, y, width, height, color)
        self.speed = speed

    def update(self, screen):
        keys = pygame.key.get_pressed()

        if keys[pygame.K_LEFT]:
            self.x -= self.speed
        if keys[pygame.K_RIGHT]:
            self.x += self.speed

        if self.x < 0:
            self.x = 0
        if self.x + self.width > screen.get_width():
            self.x = screen.get_width() - self.width

        self.update_rect()
