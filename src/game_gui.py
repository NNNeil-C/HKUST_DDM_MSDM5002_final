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
        pygame.draw.circle(self.screen, current_piece.color, pos, 18, 0)
        pygame.display.update()
