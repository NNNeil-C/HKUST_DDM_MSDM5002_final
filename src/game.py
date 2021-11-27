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


if __name__ == '__main__':
    ui = game_gui.game_ui()
    clock = pygame.time.Clock()
    Alice = player.player(piece.piece.black_piece)
    Bob = player.player(piece.piece.white_piece, is_ai=True)
    current_player = Alice
    so_file_path = r"./mcst_helper*"

    game_board = np.zeros((game_utils.game_board_size, game_utils.game_board_size), dtype=np.int64)

    while True:
        clock.tick(60)
        for event in pygame.event.get():
            # quit game
            if event.type == pygame.QUIT:
                pygame.quit()
                exit()
            # click down
            if event.type == pygame.MOUSEBUTTONDOWN:
                if not current_player.is_ai:
                    # get position
                    row, col = game_utils.get_click_position(event)
                    # check position
                    if game_utils.is_valid_position(game_board, col, row):
                        make_drop(game_board, current_player, row, col, Alice, ui)
                        # player switch
                        current_player = Alice if current_player is Bob else Bob
                        if current_player.is_ai:
                            x, y = game_utils.ask_monte_carlo_search_tree(so_file_path,
                                                                   game_board, row, col, game_board[row, col])
                            make_drop(game_board, current_player, x, y, Alice, ui)

