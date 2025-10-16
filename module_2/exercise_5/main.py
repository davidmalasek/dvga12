# Author: David Malášek

"""
import pygame
import sys

# Inicializace pygame
pygame.init()

# Nastaveni okna
WIDTH, HEIGHT = 800, 600
window = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("My First Pygame Window")

# Barvy (R, G, B)
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)

# Hlavni herni smycka
while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            sys.exit()

    window.fill(BLACK)
    pygame.draw.circle(window, WHITE, (WIDTH // 2, HEIGHT // 2), 50)
    pygame.display.flip()
"""