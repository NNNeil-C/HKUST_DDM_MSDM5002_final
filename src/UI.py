import pygame
import numpy as np


class Piece:

    def __init__(self):
        self.__row = None
        self.__col = None
        self.__gamer = None

    def set_pos(self, x: int, y: int):
        self.__row = x
        self.__col = y

    def get_pos(self):
        return self.__row, self.__col

    def set_color(self, color: int):
        self.__gamer = color

    def get_color(self):
        if self.__gamer == 1:
            return 1
        elif self.__gamer == -1:
            return -1
        else:
            return False


class GameBoard:
    def __init__(self, width=8, height=8):
        self.width = width
        self.height = height
        self.board = np.zeros((self.width, self.height))

    def ini_screen(self, screen):
        size = self.width
        screen.fill((230, 185, 70))
        for x in range(size):
            pygame.draw.line(screen, [0, 0, 0], [25 + 50 * x, 25], [25 + 50 * x, size * 50 - 25], 1)
            pygame.draw.line(screen, [0, 0, 0], [25, 25 + 50 * x], [size * 50 - 25, 25 + 50 * x], 1)
        pygame.display.update()

    def update_ui(self, screen):
        black_color = [0, 0, 0]
        white_color = [255, 255, 255]
        for i in range(self.width):
            for j in range(self.height):
                pos = [50 * i + 25, 50 * j + 25]
                if self.board[i][j] == 1:
                    pygame.draw.circle(screen, black_color, pos, 18, 0)
                elif self.board[i][j] == -1:
                    pygame.draw.circle(screen, white_color, pos, 18, 0)
        pygame.display.update()

    def place_piece(self, piece: Piece):
        self.board[piece.get_pos()] = piece.get_color()



# if __name__ == '__main__':
#     pygame.init()
#     M = 12
#     piece = Piece(row=11, col=11, gamer=1)
#     screen = pygame.display.set_mode((50 * M, 50 * M))
#     pygame.display.set_caption('Interface of Five-in-a-Row')
#     game = GameBoard(M, M)
#     game.ini_screen(screen=screen)
#     game.place_piece(piece)
#     print(game.board)
#     game.update_ui(screen=screen)
#     done = False
#     while not done:
#         for e in pygame.event.get():
#             if e.type == pygame.QUIT:
#                 done = True
