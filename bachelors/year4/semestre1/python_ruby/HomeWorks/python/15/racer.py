import pygame
import random

pygame.init()

display_width = 800
display_height = 600

black = (0, 0, 0)
white = (255, 255, 255)
red = (150, 0, 0)
bright_red = (255, 0, 0)
green = (0, 150, 0)
bright_green = (0, 255, 0)

block_color = (53, 115, 255)

car_width = 73

pause = False

gameDisplay = pygame.display.set_mode((display_width, display_height))
pygame.display.set_caption('A bit Racey')
clock = pygame.time.Clock()

carImg = pygame.image.load('racecar.png')

gameIcon = pygame.image.load('racecar.png')
pygame.display.set_icon(gameIcon)


def things(thingx, thingy, thingw, thingh, colour):
    pygame.draw.rect(gameDisplay, colour, [thingx, thingy, thingw, thingh])


def car(x, y):
    gameDisplay.blit(carImg, (x, y))


def text_objects(text, font):
    textSurface = font.render(text, True, black)
    return textSurface, textSurface.get_rect()


def message_display(text):
    largeText = pygame.font.SysFont('comicsansms', 115)
    TextSurf, TextRect = text_objects(text, largeText)
    TextRect.center = (display_width / 2, display_height / 2)
    gameDisplay.blit(TextSurf, TextRect)
    pygame.display.update()


def things_dodged(count):
    font = pygame.font.SysFont(None, 25)
    text = font.render("Dodged: %d" % count, True, black)
    gameDisplay.blit(text, (0, 0))


def button(msg, x, y, w, h, ac, ic, action=None):
    mouse = pygame.mouse.get_pos()
    click = pygame.mouse.get_pressed()
    # print(click)

    if x < mouse[0] < x+w and y < mouse[1] < y+h:
        pygame.draw.rect(gameDisplay, ac, (x, y, w, h))

        if click[0] == 1 and action != None:
            action()
    else:
        pygame.draw.rect(gameDisplay, ic, (x, y, w, h))

    smallText = pygame.font.SysFont('comicsansms', 20)
    textSurf, textRect = text_objects(msg, smallText)
    textRect.center = (x+w/2, y+h/2)
    gameDisplay.blit(textSurf, textRect)


def quitgame():
    pygame.quit()
    quit()


def unpause():
    global pause
    pause = False


def paused():
    message_display("Paused")

    global pause
    while pause:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                quitgame()

        button("Continue", 150, 450, 100, 50, bright_green, green, unpause)
        button("Quit", 550, 450, 100, 50, bright_red, red, quitgame)

        pygame.display.update()
        clock.tick(15)


def crash():
    message_display("You crashed!")

    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                quitgame()

        button("Play again", 150, 450, 100, 50, bright_green, green, game_loop)
        button("Quit", 550, 450, 100, 50, bright_red, red, quitgame)

        pygame.display.update()
        clock.tick(15)


def game_intro():
    intro = True

    while intro:
        for event in pygame.event.get():
            print(event)
            if event.type == pygame.QUIT:
                quitgame()

        gameDisplay.fill(white)
        message_display("A bit Racey")

        button("GO!", 150, 450, 100, 50, bright_green, green, game_loop)
        button("Quit", 550, 450, 100, 50, bright_red, red, quitgame)
        pygame.display.update()

        clock.tick(15)


def game_loop():
    x = (display_width * 0.45)
    y = (display_height * 0.8)
    x_change = 0

    thing_startx = random.randrange(0, display_width)
    thing_starty = -600
    thing_speed = 7
    thing_width = 100
    thing_height = 100

    dodged = 0

    gameExit = False
    global pause

    while not gameExit:

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                quitgame()
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_LEFT:
                    x_change = -5
                if event.key == pygame.K_RIGHT:
                    x_change = 5
                if event.key == pygame.K_p:
                    pause = True
                    paused()
            if event.type == pygame.KEYUP:
                if event.key == pygame.K_LEFT or event.key == pygame.K_RIGHT:
                    x_change = 0
            print(event)

        x += x_change

        if x > display_width - car_width or x < 0:
            crash()

        gameDisplay.fill(white)

        things(thing_startx, thing_starty, thing_width, thing_height, block_color)
        thing_starty += thing_speed
        car(x, y)
        things_dodged(dodged)

        if thing_starty > display_height:
            thing_starty = -thing_height
            thing_startx = random.randrange(0, display_width)
            dodged += 1
            thing_speed += 1
            thing_width += dodged * 1.2

        if y < thing_starty + thing_height:
            if thing_startx < x < thing_startx + thing_width or \
                                    thing_startx < x + car_width < thing_startx + thing_width:
                crash()

        pygame.display.update()
        clock.tick(60)


game_intro()
game_loop()
quitgame()