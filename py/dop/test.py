import pygame
import os
path = os.path.dirname(__file__) + "/"

pygame.init()

xwin=1280 #размер окна
ywin=1024 #размер окна
win=pygame.display.set_mode((xwin, ywin)) #размер окна
pygame.display.set_caption('HULK_TEST') #имя окна

walkright = [pygame.image.load(path + 'right1.png'),
pygame.image.load(path + 'right2.png'),pygame.image.load(path + 'right3.png'),
pygame.image.load(path + 'right4.png'),pygame.image.load(path + 'right5.png')]

walkleft = [pygame.image.load(path + 'left1.png'),
pygame.image.load(path + 'left3.png'),
pygame.image.load(path + 'left4.png'),pygame.image.load(path + 'left5.png')]

jumppng = [pygame.image.load(path + 'jump2.png')]

bg= pygame.image.load(path + 'backforest.jpg')
playerstand=pygame.image.load(path + 'jump1.png')

clock=pygame.time.Clock()
# параметры запуска игрока
x = 200 #spawn
y = 900 #spawn
width = 117 #ширина фигуры
height = 140 #высота фигуры
speed = 7 #скорость

jump=False #прыжок
jumpcount=10 #высота прыжка

left=False
right=False
animcount=0

def drawwindow():
    global animcount
    win.blit(bg,(0,0))
    if animcount + 1 >= 30:
        animcount=0
    if left:
        win.blit(walkleft[animcount // 6],(x,y))
        animcount+=1
    elif right:
        win.blit(walkright[animcount // 6],(x,y))
        animcount+=1
    elif jump:
        win.blit(jumppng[animcount //30],(x,y))

    else:
        win.blit(playerstand,(x,y))

    pygame.display.update()

run = True
while run:
    clock.tick(30)
    pygame.time.delay(20) #темп игры

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            run = False
    keys=pygame.key.get_pressed()

    if keys[pygame.K_a] and x>7:
        x-=speed
        left=True
        right=False
    elif keys[pygame.K_d] and x<xwin-width-7:
        x+=speed
        left=False
        right=True
    else:
        left=False
        right=False
        animcount=0
    if not(jump):
        if keys[pygame.K_w] and y>250:
            y-=speed
        if keys[pygame.K_s] and y<ywin-height-7:
            y+=speed
        if keys[pygame.K_SPACE] and y>7+jumpcount:
            jump=True
    else:
        if jumpcount >=-10:
            if jumpcount<0:
                y+=(jumpcount**2) / 2
            else:
                y-=(jumpcount**2) / 2
            jumpcount-=1
        else:
            jump=False
            jumpcount=10
    drawwindow()
pygame.quit()
