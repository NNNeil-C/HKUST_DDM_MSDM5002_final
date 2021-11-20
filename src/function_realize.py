'''
Author: Cynthia G
Fist Edit: 2021/11/13
Last Edit: 2021/11/20 23:13:47

Work remained by far: Reformation of classes
                      Modification of board update method
                      Include the situation that mouse click off board
                      Message showing the winner
                      Interface for AI
'''

import pygame
import UI


class HumanPlayer:
    def __init__(self):
        self.piece = UI.Piece()

    def update_by_human(self, event):
        x, y = event.pos
        row = round((x - 25) / 50)
        col = round((y - 25) / 50)
        self.piece.set_pos(row, col)


class AIPlayer:
    def __init__(self):
        self.piece = UI.Piece()

    # def update_by_machine(self):
    #     pygame.event.set_blocked(None)
    #     position = Gamer.find_best_action()
    #     pygame.event.set_allowed([pygame.QUIT, pygame.MOUSEBUTTONDOWN])
    #     x, y = position
    #     self.piece = UI.Piece(x, y, -1)


class CheckWinning:
    def __init__(self):
        self.done = False

    def check(self, mat: UI.GameBoard, piece: UI.Piece):
        up = (0, 1)
        down = (0, -1)
        lft = (-1, 0)
        rgt = (1, 0)
        up_lft = (-1, 1)
        up_rgt = (1, 1)
        down_lft = (-1, -1)
        down_rgt = (1, -1)

        vertical = self.__count_pieces(mat, piece, up) + self.__count_pieces(mat, piece, down) - 1
        horizontal = self.__count_pieces(mat, piece, lft) + self.__count_pieces(mat, piece, rgt) - 1
        diagonal = self.__count_pieces(mat, piece, up_lft) + self.__count_pieces(mat, piece, down_rgt) - 1
        bck_diagonal = self.__count_pieces(mat, piece, up_rgt) + self.__count_pieces(mat, piece, down_lft) - 1

        if 5 in [vertical, horizontal, diagonal, bck_diagonal]:
            self.done = True

    def __count_pieces(self, mat: UI.GameBoard, piece: UI.Piece, direct):
        count = 0
        x, y = piece.get_pos()

        while 0 <= x < mat.width and 0 <= y < mat.height and mat.board[x][y] == piece.get_color():
            count += 1
            x, y = x + direct[0], y + direct[1]
        return count


class Game:
    def __init__(self, fst: str, size: int):
        self.player1 = fst
        self.mat = UI.GameBoard(width=size, height=size)
        self.winner = None

    def start(self):
        pygame.init()
        screen = pygame.display.set_mode((50 * self.mat.width, 50 * self.mat.height))
        pygame.display.set_caption('Interface of Five-in-a-Row')
        self.mat.ini_screen(screen)
        print(self.mat.board)
        win = CheckWinning()
        if self.player1 == 'Human':
            while not win.done:
                for e in pygame.event.get():
                    if e.type == pygame.QUIT:
                        win.done = True
                    elif e.type == pygame.MOUSEBUTTONDOWN:
                        human = HumanPlayer()
                        human.piece.set_color(1)
                        human.update_by_human(e)
                        self.mat.place_piece(human.piece)
                        print(self.mat.board)
                        win.check(self.mat, human.piece)
                        if win.done:
                            self.winner = self.player1
                        self.mat.update_ui(screen)




if __name__ == '__main__':
    gomoku = Game('Human', 8)
    gomoku.start()