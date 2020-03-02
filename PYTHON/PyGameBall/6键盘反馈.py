import pygame,sys

pygame.init()
screen = pygame.display.set_mode((600,400))
pygame.display.set_caption("键盘反馈")

while True:
	for event in pygame.event.get():
		if event.type == pygame.QUIT:
			sys.exit()
		elif event.type == pygame.KEYDOWN:
			if event.unicode == '':
				print('[KEYDOWN]:','#',event.key,event.mod)
			else:
				print('[KEYDOWN]:',event.unicode,event.key,event.mod)
	pygame.display.update()
