import pygame,sys

pygame.init()
vinfo = pygame.display.Info()
size = width,height = vinfo.current_w,vinfo.current_h
speed = [0,0]
BLACK = 0,0,0
screen = pygame.display.set_mode(size,pygame.FULLSCREEN)
pygame.display.set_caption("pygame壁球")
ball = pygame.image.load("地球.png")
ballrect = ball.get_rect()
fps = 300
fclock = pygame.time.Clock()

while True:
	for event in pygame.event.get():
		if event.type == pygame.QUIT:
			sys.exit()
		elif event.type == pygame.KEYDOWN:
			if event.key == pygame.K_LEFT:
				speed[0] = speed[0] if speed[0] == 0 else (abs(speed[0])-1)*int(speed[0]/abs(speed[0]))
			elif event.key == pygame.K_RIGHT:
				speed[0] = speed[0]+1 if speed[0] > 0 else speed[0]-1
			elif event.key == pygame.K_UP:
				speed[1] = speed[1]+1 if speed[1] > 0 else speed[1]-1
			elif event.key == pygame.K_DOWN:
				speed[1] = speed[1] if speed[1] == 0 else (abs(speed[1])-1)*int(speed[1]/abs(speed[1]))
			elif event.key == pygame.K_ESCAPE:
				sys.exit()
	ballrect = ballrect.move(speed[0],speed[1])
	if ballrect.left < 0 or ballrect.right > width:
		speed[0] = -speed[0]
	if ballrect.top < 0 or ballrect.bottom >height:
		speed[1] = -speed[1]
		
	screen.fill(BLACK)
	screen.blit(ball,ballrect)
	pygame.display.update()
	fclock.tick(fps)
	
 