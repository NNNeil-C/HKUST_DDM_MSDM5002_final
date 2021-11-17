'''
Author: Cynthia G
Last Edit: 2021/11/17 11:33

Work remained by far: Reformation of classes
                      Modification of board update function
                      Include the situation that mouse click off board
                      Message showing the winner

'''

import pygame
import UI


# class Piece:
#     def __init__(self):
#         self.__color = 1
#
#     def set_color(self, color: int):
#         self.__color = color
#
#     def get_color(self):
#         if self.__color == 'black':
#             return [0, 0, 0]
#         if self.__color == 'white':
#             return [255, 255, 255]

# class

def update_by_man(event):
    """
    This method detects the mouse click on the game window. Update the state matrix of the game.
    input:
        event:pygame event, which are either quit or mouse click)
    """

    x, y = event.pos
    row = round((y - 25) / 50)
    col = round((x - 25) / 50)
    piece = UI.Piece(col, row, 1)
    return piece



# def update_by_machine(self):
#     pygame.event.set_blocked(None)
#     position = Gamer.find_best_action()
#     pygame.event.set_allowed([pygame.QUIT, pygame.MOUSEBUTTONDOWN])
#     x, y = position
#     piece = UI.Piece(x, y, -1)
#     return piece


def check_for_done(mat, piece):
    up = (0, 1)
    down = (0, -1)
    lft = (-1, 0)
    rgt = (1, 0)
    up_lft = (-1, 1)
    up_rgt = (1, 1)
    down_lft = (-1, -1)
    down_rgt = (1, -1)

    vertical = __count_pieces(mat, piece, up) + __count_pieces(mat, piece, down) - 1
    if vertical == 5:
        return True

    horizontal = __count_pieces(mat, piece, lft) + __count_pieces(mat, piece, rgt) - 1
    if horizontal == 5:
        return True

    diagonal = __count_pieces(mat, piece, up_lft) + __count_pieces(mat, piece, down_rgt) - 1
    if diagonal == 5:
        return True

    bck_diagonal = __count_pieces(mat, piece, up_rgt) + __count_pieces(mat, piece, down_lft) - 1
    if bck_diagonal == 5:
        return True

    return False

def __count_pieces(mat: UI.GameBoard, piece: UI.Piece, direct):
    count = 0
    x, y = piece.get_pos()

    while 0 <= x < mat.width and 0 <= y < mat.height and mat.board[x][y] == piece.gamer:
        count += 1
        x, y = x + direct[0], y + direct[1]
    return count


if __name__ == '__main__':
    pygame.init()
    M = 8
    screen = pygame.display.set_mode((50 * M, 50 * M))
    pygame.display.set_caption('Interface of Five-in-a-Row')
    game = UI.GameBoard(M, M)
    game.ini_screen(screen)
    print(game.board)
    done = False
    while not done:
        for e in pygame.event.get():
            if e.type == pygame.QUIT:
                done = True
            elif e.type == pygame.MOUSEBUTTONDOWN:
                piece = update_by_man(e)
                game.place_piece(piece)
                print(game.board)
                done = check_for_done(game, piece)
                game.update_ui(screen, M, M)
