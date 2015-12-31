import pygame

pygame.init()

display_width = 800
display_height = 600


white = (255, 255, 255)
black = (0, 0, 0)
green = (0, 200, 0)
bright_green = (0, 255, 0)
red = (200, 0, 0)
bright_red = (255, 0, 0)

gameDisplay = pygame.display.set_mode((display_width, display_height))
pygame.display.set_caption('Labyrinth')
clock = pygame.time.Clock()

image_width = 16
image_height = 16
wall_img = pygame.image.load('img/wall.bmp')
chip_img = pygame.image.load('img/chip.bmp')
free_img = pygame.image.load('img/free.bmp')
stone_img = pygame.image.load('img/stone.bmp')


def text_objects(text, font):
    textSurface = font.render(text, True, black)
    return textSurface, textSurface.get_rect()


def message_display(text, size, x, y):
    largeText = pygame.font.SysFont('comicsansms', size)
    TextSurf, TextRect = text_objects(text, largeText)
    TextRect.center = (x, y)
    gameDisplay.blit(TextSurf, TextRect)
    pygame.display.update()


def display_level(level):
    font = pygame.font.SysFont(None, 25)
    text = font.render("Level: %d" % level, True, black)
    gameDisplay.blit(text, (0, 0))


def button(msg, x, y, w, h, act_col, ina_col, action=None):
    mouse = pygame.mouse.get_pos()
    click = pygame.mouse.get_pressed()

    if x < mouse[0] < x+w and y < mouse[1] < y+h:
        pygame.draw.rect(gameDisplay, act_col, (x, y, w, h))
        if click[0] == 1 and action is not None:
            action()
    else:
        pygame.draw.rect(gameDisplay, ina_col, (x, y, w, h))

    message_display(msg, 20, x+w/2, y+h/2)


def quit_game():
    pygame.quit()
    quit()


def intro_loop():
    intro = True

    while intro:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                quit_game()

        gameDisplay.fill(white)
        message_display("Labyrinth", 115, display_width/2, display_height/2)

        button("GO!", 150, 450, 100, 50, bright_green, green, game_loop)
        button("Quit", 550, 450, 100, 50, bright_red, red, quit_game)

        pygame.display.update()
        clock.tick(15)


def win_loop():
    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                quit_game()

        gameDisplay.fill(white)
        message_display("You Won!", 115, display_width/2, display_height/2)

        button("Start new!", 150, 450, 100, 50, bright_green, green, game_loop)
        button("Quit", 550, 450, 100, 50, bright_red, red, quit_game)

        pygame.display.update()
        clock.tick(15)


def can_move(maze, x, y):
    if 0 <= x < len(maze) and 0 <= y < len(maze[0]):
        return maze[x][y] == ' '
    return False


def can_move_rect(maze, x, y, rows, cols):
    return 0 <= x <= len(maze) - rows and 0 <= y <= len(maze[0]) - cols


def game_loop():
    global display_width, display_height
    level = 0
    newLevel = True
    pressed_keys = {}
    while level <= 10:
        if newLevel:
            newLevel = False
            level += 1
            with open('mazes/%d.txt' % level, 'r') as f:
                maze = f.read().splitlines()
            rows = len(maze)
            cols = len(maze[0])
            # print(rows, cols)
            game_rect_x, game_rect_y = 0, 0
            game_rect_cols, game_rect_rows = min(cols, 80), min(rows, 40)

            display_width = game_rect_cols * image_width
            display_height = game_rect_rows * image_height
            pygame.display.set_mode((display_width, display_height))
            x, y = 1, 0

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                quit_game()
            if event.type == pygame.KEYDOWN:
                pressed_keys[event.key] = True
            if event.type == pygame.KEYUP:
                del pressed_keys[event.key]

        if pygame.K_UP in pressed_keys and can_move(maze, x - 1, y):
            x -= 1
        if pygame.K_DOWN in pressed_keys and can_move(maze, x + 1, y):
            x += 1
        if pygame.K_LEFT in pressed_keys and can_move(maze, x, y - 1):
            y -= 1
        if pygame.K_RIGHT in pressed_keys and can_move(maze, x, y + 1):
            y += 1

        if pygame.K_w in pressed_keys and \
            can_move_rect(maze, game_rect_x - 1, game_rect_y, game_rect_rows, game_rect_cols):
            game_rect_x -= 1
        if pygame.K_s in pressed_keys and \
            can_move_rect(maze, game_rect_x + 1, game_rect_y, game_rect_rows, game_rect_cols):
            game_rect_x += 1
        if pygame.K_a in pressed_keys and \
            can_move_rect(maze, game_rect_x, game_rect_y - 1, game_rect_rows, game_rect_cols):
            game_rect_y -= 1
        if pygame.K_d in pressed_keys and \
            can_move_rect(maze, game_rect_x, game_rect_y + 1, game_rect_rows, game_rect_cols):
            game_rect_y += 1

        # print(game_rect_x, game_rect_y, game_rect_rows, game_rect_cols)
        for i in range(game_rect_x, game_rect_x+game_rect_rows):
            for j in range(game_rect_y, game_rect_y+game_rect_cols):
                if maze[i][j] == ' ':
                    gameDisplay.blit(free_img, ((j - game_rect_y) * image_width, (i - game_rect_x) * image_height))
                else:
                    gameDisplay.blit(wall_img, ((j - game_rect_y) * image_width, (i - game_rect_x) * image_height))

        display_level(level)

        if game_rect_x <= x < game_rect_x+game_rect_rows and \
            game_rect_y <= y < game_rect_y+game_rect_cols:
            gameDisplay.blit(chip_img, ((y - game_rect_y) * image_width, (x - game_rect_x) * image_height))

        if game_rect_x <= rows - 2 < game_rect_x+game_rect_rows and \
            game_rect_y <= cols - 1 < game_rect_y+game_rect_cols:
            gameDisplay.blit(stone_img, ((cols - 1 - game_rect_y) * image_width, (rows - 2 - game_rect_x) * image_height))

        if x == rows - 2 and y == cols - 1:
            newLevel = True

        pygame.display.update()
        clock.tick(30)

    win_loop()


intro_loop()
game_loop()
quit_game()
