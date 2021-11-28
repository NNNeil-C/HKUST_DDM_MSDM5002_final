# -*- coding: utf-8 -*-
# @Time    : 27/11/2021 3:43 pm
# @Author  : ZIFENG NEIL CHEN
# @FileName: game_gui.py.py
# @Software: PyCharm
# @Github    ：https://github.com/NNNeil-C/
import pygame
import game_utils


class game_ui():
    def __init__(self):
        pygame.init()
        self.screen = pygame.display.set_mode((50 * game_utils.game_board_size, 50 * game_utils.game_board_size))
        pygame.display.set_caption('Interface of Five-in-a-Row')
        size = game_utils.game_board_size
        self.screen.fill((230, 185, 70))
        for x in range(size):
            pygame.draw.line(self.screen, [0, 0, 0], [25 + 50 * x, 25], [25 + 50 * x, size * 50 - 25], 1)
            pygame.draw.line(self.screen, [0, 0, 0], [25, 25 + 50 * x], [size * 50 - 25, 25 + 50 * x], 1)
        pygame.display.update()

    def drop_piece(self, current_piece, col, row):
        pos = [50 * col + 25, 50 * row + 25]
        print(current_piece.color)
        update_rect = pygame.Rect((pos[0]-18, pos[1]-18), (18*2, 18*2))
        pygame.draw.circle(self.screen, current_piece.color, pos, 18, 0)
        pygame.display.update(update_rect)

    @staticmethod
    def winner_info_window(winner: str):
        canvas = pygame.display.set_mode((300, 100))
        pygame.display.set_caption('Game Result')
        canvas.fill((255, 239, 213))
        pygame.font.init()
        my_font = pygame.font.SysFont('Comic Sans MS', 30)
        if winner != 'Black' or 'White':
            winner = 'Nobody'
        text_surface = my_font.render(winner+' wins this game', True, (105, 105, 105))
        canvas.blit(text_surface, (50, 40))
        pygame.display.update()
