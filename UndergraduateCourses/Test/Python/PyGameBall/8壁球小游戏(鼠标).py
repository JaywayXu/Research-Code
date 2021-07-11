import pygame,sys

pygame.init()
ball = pygame.image.load("地球.png")
pygame.display.set_icon(ball)
size = width,height = 800,600
speed = [1,1]
BLACK = 0,0,0
screen = pygame.display.set_mode(size,pygame.NOFRAME)
pygame.display.set_caption("pygame壁球")
ballrect = ball.get_rect()
fps = 300
fclock = pygame.time.Clock()
click = False

while True:
	for event in pygame.event.get():
		if event.type == pygame.QUIT:
			sys.exit()
		elif event.type == pygame.MOUSEBUTTONDOWN:
			if event.button == 1:
				click = True
		elif event.type == pygame.MOUSEBUTTONUP:
			click = False
			if event.button == 1:
				ballrect = ballrect.move(event.pos[0]-ballrect.left-100,event.pos[1]-ballrect.top-100)
		elif event.type == pygame.MOUSEMOTION:
			if event.buttons[0] == 1:
				ballrect = ballrect.move(event.pos[0]-ballrect.left-100,event.pos[1]-ballrect.top-100)
		elif event.type == pygame.KEYDOWN:
			if event.key == pygame.K_ESCAPE:
				sys.exit()
		elif event.type == pygame.VIDEORESIZE:
			size = width,height = event.size[0],event.size[1]
			screen = pygame.display.set_mode(size,pygame.RESIZABLE)
	if pygame.display.get_active() and not click:
		ballrect = ballrect.move(speed[0],speed[1])
	if ballrect.left < 0 or ballrect.right > width:
		speed[0] = -speed[0]
		if ballrect.right > width and ballrect.right + speed[0] >ballrect.right:
			speed[0] = -speed[0]
		elif ballrect.left < 0 and ballrect.left + speed[0] <ballrect.left:
			speed[0] = -speed[0]
	if ballrect.top < 0 or ballrect.bottom >height:
		speed[1] = -speed[1]
		if ballrect.bottom > height and ballrect.bottom + speed[1] >ballrect.bottom:
			speed[1] = -speed[1]
		elif ballrect.top < 0 and ballrect.top + speed[1] <ballrect.top:
			speed[1] = -speed[1]
		
	screen.fill(BLACK)
	screen.blit(ball,ballrect)
	pygame.display.update()
	fclock.tick(fps)
 