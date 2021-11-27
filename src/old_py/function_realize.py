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
import models
import ctypes
import glob
import platform


class HumanPlayer:
    def __init__(self):
        self.piece = UI.Piece()

    def update_by_human(self, event):
        x, y = event.pos
        row = round((x - 25) / 50)
        col = round((y - 25) / 50)
        self.piece.set_pos(row, col)
        if is_valid_position(models.gameboard.board, row, col):
            models.gameboard.board[row, col] = self.piece.get_color()
            return True
        return False


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
                        if human.update_by_human(e):
                            print("human drop true")
                            self.mat.place_piece(human.piece)
                            print(self.mat.board)
                            win.check(self.mat, human.piece)
                            if win.done:
                                self.winner = self.player1
                            self.mat.update_ui(screen)
                            pygame.event.set_blocked(pygame.MOUSEBUTTONDOWN)
                            ai = UI.Piece()
                            ai.set_color(-1)
                            last_x, last_y = human.piece.get_pos()
                            x, y = mcst_helper(models.gameboard.board, last_x, last_y, human.piece.get_color(), 5000)
                            # to do: check ai drop
                            models.gameboard.board[x, y] = ai.get_color()
                            ai.set_pos(x, y)
                            win.check(self.mat, ai)
                            self.mat.place_piece(ai)
                            self.mat.update_ui(screen)
                            pygame.event.clear()
                            pygame.event.set_allowed(pygame.MOUSEBUTTONDOWN)


def is_valid_position(board, row, col):
    if row < 0 or row > models.gameboard.number_of_rows or col < 0 or col > models.gameboard.number_of_columns:
        return False
    if board[row, col] != models.gameboard.none:
        return False
    return True


def mcst_helper(board, last_x, last_y, last_piece, time_limit=5000):
    so_file_path = ""
    if "Win" in platform.platform():
        so_file_path = r'./build/lib.windows-10-x64-3.7/mcst_helper*.dll'
    else:
        so_file_path = r'../mcst_helper.cpython-38-darwin.so'
    print(so_file_path)
    libfile = glob.glob(so_file_path)[0]
    mylib = ctypes.CDLL(libfile)
    mylib.hello.restype = ctypes.c_void_p
    mylib.hello()

    INPUT = ctypes.c_int * 64
    mylib.getNextPosition.argtype = [INPUT, ctypes.c_int, ctypes.c_int, ctypes.c_int, ctypes.c_int]
    mylib.getNextPosition.restype = ctypes.c_int
    input = INPUT()
    for i in range(64):
        input[i] = 0
    for i in range(models.gameboard.number_of_rows):
        for j in range(models.gameboard.number_of_columns):
            input[i * models.gameboard.number_of_columns + j] = board[i, j]
    getNextPosition = mylib.getNextPosition
    ans = getNextPosition(input, last_x, last_y, last_piece, time_limit)
    x = ans // 10
    y = ans % 10
    return x, y


if __name__ == '__main__':
    gomoku = Game('Human', 8)
    gomoku.start()