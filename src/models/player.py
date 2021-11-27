# -*- coding: utf-8 -*-
# @Time    : 27/11/2021 4:35 pm
# @Author  : ZIFENG NEIL CHEN
# @FileName: player.py
# @Software: PyCharm
# @Github    ：https://github.com/NNNeil-C/
import copy


class player():
    def __init__(self, piece_type, is_ai=False):
        self.piece_type = copy.deepcopy(piece_type)
        self.is_ai = is_ai

    def set_ai(self, is_ai):
        self.is_ai = is_ai


