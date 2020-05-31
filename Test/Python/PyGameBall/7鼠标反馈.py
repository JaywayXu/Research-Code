import pygame,sys

pygame.init()
screen = pygame.display.set_mode((600,400))
pygame.display.set_caption("鼠标反馈")

while True:
	for event in pygame.event.get():
		if event.type == pygame.QUIT:
			sys.exit()
		elif event.type == pygame.MOUSEMOTION:
			print("[MOUSEMOTION]:",event.pos,event.rel,event.buttons)
		elif event.type == pygame.MOUSEBUTTONUP:
			print("[MOUSEBUTTONUP]:",event.pos,event.button)
		elif event.type == pygame.MOUSEBUTTONDOWN:
			print("[MOUSEBUTTONDOWN]",event.pos,event.button)
	pygame.display.update()
