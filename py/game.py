import pygame
import os

res_path = os.path.dirname(__file__) + "/dop/"


class Hulk():

    walkright = [pygame.image.load(res_path + 'right1.gif'), pygame.image.load(res_path + 'right2.gif')]

    walkleft = [pygame.image.load(res_path + 'left1.gif'), pygame.image.load(res_path + 'left2.gif')]

    walkup = [pygame.image.load(res_path + 'up1.gif'), pygame.image.load(res_path + 'up2.gif')]

    walkdown = [pygame.image.load(res_path + 'down1.gif'), pygame.image.load(res_path + 'down2.gif')]

    bg = pygame.image.load(res_path + 'background.jpg')
    playerstand = pygame.image.load(res_path + 'down1.gif')
    x = 200  # spawn
    y = 900  # spawn
    width = 117  # ширина фигуры
    height = 140  # высота фигуры
    speed = 7  # скорость
    jump = False  # прыжок
    jumpcount = 10  # высота прыжка
    left = False
    right = False
    animcount = 0


class Window():

    xwin = 1280  # размер окна
    ywin = 1024  # размер окна
    win = pygame.display.set_mode((xwin, ywin))  # размер окна
    pygame.display.set_caption('HULK_TEST')  # имя окна
        

    def drawwindow(self, hulk):
        win.blit(hulk.bg, (0, 0))
        if hulk.animcount + 1 >= 30:
            hulk.animcount = 0
        if hulk.left:
            win.blit(
                hulk.walkleft[hulk.animcount // 6], (hulk.x, hulk.y))
            hulk.animcount += 1
        elif hulk.right:
            win.blit(
                hulk.walkright[hulk.animcount // 6], (hulk.x, hulk.y))
            hulk.animcount += 1
        elif hulk.jump:
            win.blit(
                hulk.jumppng[hulk.animcount // 30], (hulk.x, hulk.y))
        else:
            win.blit(hulk.playerstand, (hulk.x, hulk.y))

        pygame.display.update()


class Game():

    pygame.init()
    clock = pygame.time.Clock()
    hulk = Hulk()
    window = Window()

    def run(self):
        run = True
        while run:
            clock.tick(30)
            pygame.time.delay(20)  # темп игры

            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    run = False
            keys = pygame.key.get_pressed()

            if keys[pygame.K_a] and hulk.x > 7:
                hulk.x -= hulk.speed
                hulk.left = True
                hulk.right = False
            elif keys[pygame.K_d] and hulk.x < window.xwin-hulk.width-7:
                hulk.x += hulk.speed
                hulk.left = False
                hulk.right = True
            else:
                hulk.left = False
                hulk.right = False
                hulk.animcount = 0
            if not(hulk.jump):
                if keys[pygame.K_w] and hulk.y > 250:
                    hulk.y -= hulk.speed
                if keys[pygame.K_s] and hulk.y < window.ywin-hulk.height-7:
                    hulk.y += hulk.speed
                if keys[pygame.K_SPACE] and hulk.y > 7 + hulk.jumpcount:
                    hulk.jump = True
            else:
                if hulk.jumpcount >= -10:
                    if hulk.jumpcount < 0:
                        hulk.y += (hulk.jumpcount**2) / 2
                    else:
                        hulk.y -= (hulk.jumpcount**2) / 2
                    hulk.jumpcount -= 1
                else:
                    hulk.jump = False
                    hulk.jumpcount = 10
            window.drawwindow(hulk)
        pygame.quit()


def main():
    game = Game()
    game.run()


main()
