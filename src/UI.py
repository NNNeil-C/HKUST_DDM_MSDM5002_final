import pygame
import numpy as np


class Piece:

    def __init__(self, x, y, gamer):
        self.x = x
        self.y = y
        self.gamer = gamer

    def get_pos(self):

        return self.x, self.y

    def get_color(self):
        if self.gamer == 1:
            return 'black'
        elif self.gamer == -1:
            return 'white'
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

    def place_piece(self, piece: Piece):
        self.board[piece.get_pos()] = piece.gamer

    def update_ui(self, screen, x=8, y=8):
        black_color = [0, 0, 0]
        white_color = [255, 255, 255]
        d = int(560 / 7)
        for i in range(x):
            for j in range(y):
                pos = [50 * i + 25, 50 * j + 25]
                if self.board[i][j] == 1:
                    pygame.draw.circle(screen, black_color, pos, 18, 0)
                elif self.board[i][j] == -1:
                    pygame.draw.circle(screen, white_color, pos, 18, 0)
        pygame.display.update()


if __name__ == '__main__':
    pygame.init()
    M = 12
    piece = Piece(x=11, y=11, gamer=1)
    screen = pygame.display.set_mode((50 * M, 50 * M))
    pygame.display.set_caption('Interface of Five-in-a-Row')
    game = GameBoard(M, M)
    game.ini_screen(screen=screen)
    game.place_piece(piece)
    print(game.board)
    game.update_ui(screen=screen)
    done = False
    while not done:
        for e in pygame.event.get():
            if e.type == pygame.QUIT:
                done = True
