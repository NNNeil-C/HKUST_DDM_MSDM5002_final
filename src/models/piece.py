# -*- coding: utf-8 -*-
# @Time    : 27/11/2021 4:14 pm
# @Author  : ZIFENG NEIL CHEN
# @FileName: piece.py
# @Software: PyCharm
# @Github    ：https://github.com/NNNeil-C/
class piece():
    _black_color = [0] * 3
    _white_color = [255] * 3
    black_piece = r'black'
    white_piece = r'white'

    def __init__(self, type):
        if type == piece.black_piece:
            self.color = piece._black_color[:]
        else:
            self.color = piece._white_color[:]

if __name__ == '__main__':
    pass