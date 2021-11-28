# -*- coding: utf-8 -*-
# @Time    : 27/11/2021 4:06 pm
# @Author  : ZIFENG NEIL CHEN
# @FileName: game.py.py
# @Software: PyCharm
# @Github    ：https://github.com/NNNeil-C/
import game_gui
import pygame
import game_utils
from models import piece, player
import numpy as np


def make_drop(board, current_player, row, col, Alice, ui):
    # drop on board
    board[row, col] = 1 if current_player is Alice else -1
    print(board)
    # update ui
    current_type = piece.piece.black_piece if current_player is Alice else piece.piece.white_piece
    current_piece = piece.piece(current_type)
    ui.drop_piece(current_piece, col, row)


def do_something_after_wins(win_player, Alice):
    if win_player is Alice:
        print("Black wins")
    else:
        print("White wins")


if __name__ == '__main__':
    ui = game_gui.game_ui()
    clock = pygame.time.Clock()
    Alice = player.player(piece.piece.black_piece)
    Bob = player.player(piece.piece.white_piece, is_ai=True)
    current_player = Alice
    so_file_path = r"./mcst_helper*.dll"
    game_utils.load_dynamic_lib(so_file_path)

    game_board = np.zeros((game_utils.game_board_size, game_utils.game_board_size), dtype=np.int64)

    pygame.event.set_blocked([pygame.KEYUP, pygame.KEYDOWN, pygame.MOUSEMOTION])
    while True:
        clock.tick(60)
        for event in pygame.event.get():
            # quit game
            if event.type == pygame.QUIT:
                pygame.quit()
                exit()
            # click down
            if event.type == pygame.MOUSEBUTTONDOWN:
                if event.button == 1:
                    if not current_player.is_ai:
                        # get position
                        row, col = game_utils.get_click_position(event)
                        # check position
                        if game_utils.is_valid_position(game_board, col, row):
                            make_drop(game_board, current_player, row, col, Alice, ui)
                            # check if the last drop wins
                            if game_utils.check_win_cpp(game_board, row, col):
                                print("someone wins")
                                do_something_after_wins(current_player, Alice)
                                exit()
                            #player switch
                            current_player = Alice if current_player is Bob else Bob
                            if current_player.is_ai:
                                pygame.event.set_blocked(pygame.MOUSEBUTTONDOWN)
                                x, y = game_utils.ask_monte_carlo_search_tree(game_board, row, col, game_board[row, col])
                                make_drop(game_board, current_player, x, y, Alice, ui)
                                # check if the last drop wins
                                if game_utils.check_win_cpp(game_board, x, y):
                                    print("someone wins")
                                    do_something_after_wins(current_player, Alice)
                                    exit()
                                current_player = Alice if current_player is Bob else Bob
                                pygame.event.clear()
                                pygame.event.set_allowed(pygame.MOUSEBUTTONDOWN)
