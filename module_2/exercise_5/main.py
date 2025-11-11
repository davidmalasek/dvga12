# Author: David Malášek

import pygame
import random
from config import *
from sprites.bat import Bat
from sprites.ball import Ball
from sprites.brick import Brick

pygame.init()
screen = pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT))
pygame.display.set_caption(CAPTION)

clock = pygame.time.Clock()
font = pygame.font.Font(None, 36)

bat = Bat(
    x=SCREEN_WIDTH // 2 - 90,
    y=SCREEN_HEIGHT - 40,
    width=180,
    height=20,
    color=COLOR_BAT,
    speed=BAT_SPEED,
)
ball = Ball(
    x=SCREEN_WIDTH // 2,
    y=SCREEN_HEIGHT // 2,
    radius=10,
    color=COLOR_BALL,
    speed_x=BALL_SPEED_X,
    speed_y=BALL_SPEED_Y,
)

lives = LIVES
score = 0

bricks = []
total_bricks_width = BRICK_COLUMNS * (BRICK_WIDTH - 2)
start_x = (SCREEN_WIDTH - total_bricks_width) // 2

for row in range(BRICK_ROWS):
    for col in range(BRICK_COLUMNS):
        x = start_x + col * (BRICK_WIDTH - 2)
        y = row * BRICK_HEIGHT + BRICK_Y_OFFSET + 60

        if random.choice([True, False]):
            hits = BRICK_DEFAULT
            points = BRICK_DEFAULT_POINTS
            color = BRICK_DEFAULT_COLOR
        else:
            hits = BRICK_MULTI_HIT
            points = BRICK_MULTI_HIT_POINTS
            color = BRICK_MULTI_HIT_COLOR

        brick = Brick(x, y, BRICK_WIDTH - 2, BRICK_HEIGHT - 2, color, hits, points)
        bricks.append(brick)

running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    bat.update(screen)
    ball.update(screen)

    if ball.rect.colliderect(bat.rect):
        ball.speed_y *= -1
        ball.y = bat.y - ball.height
        ball.update_rect()

    i = 0
    while i < len(bricks):
        brick = bricks[i]
        if ball.rect.colliderect(brick.rect):
            ball.speed_y *= -1
            destroyed = brick.hit()
            if destroyed:
                score += brick.points
                del bricks[i]
                continue
        i += 1

    if len(bricks) == 0:
        running = False

    if ball.y > SCREEN_HEIGHT:
        lives -= 1
        if lives > 0:
            ball.x = SCREEN_WIDTH // 2
            ball.y = SCREEN_HEIGHT // 2
            ball.speed_x = BALL_SPEED_X
            ball.speed_y = -BALL_SPEED_Y
            ball.update_rect()
            pygame.time.wait(1000)
        else:
            running = False

    screen.fill(COLOR_BACKGROUND)
    bat.draw(screen)
    ball.draw(screen)
    for brick in bricks:
        brick.draw(screen)

    text_color = COLOR_TEXT
    screen.blit(font.render(f"Lives: {lives}", True, text_color), (20, 20))
    screen.blit(font.render(f"Score: {score}", True, text_color), (20, 60))

    pygame.display.flip()
    clock.tick(FPS)

screen.fill(COLOR_BACKGROUND)
if lives <= 0:
    message = "YOU LOST!"
elif len(bricks) == 0:
    message = "YOU WIN!"
else:
    message = "Thanks for playing!"

end_text = font.render(message, True, COLOR_TEXT)
text_rect = end_text.get_rect(center=(SCREEN_WIDTH // 2, SCREEN_HEIGHT // 2))
screen.blit(end_text, text_rect)
pygame.display.flip()
pygame.time.wait(2000)
pygame.quit()
