import numpy as np
from z3 import *
from itertools import product
from skimage.morphology import label


ORTHAGONAL_MOVES = [(1,0),(-1,0),(0,1),(0,-1)]
DIAGONAL_MOVES = [(1,1),(-1,1),(1,-1),(-1,-1)]
KNIGHT_MOVES = [(1,2),(2,1),(-1,2),(-2,1),(1,-2),(2,-1),(-1,-2),(-2,-1)]



at_least_one_empty_nxn = lambda n, board: [Or(board[i+di][j+dj]==0 for di,dj in product(range(n), repeat=2)) for i,j in product(range(len(board)-n+1), range(len(board[0])-n+1)]






class PuzzleSolver:
        
    @staticmethod
    def empty_nxn(n: int, board: np.ndarray) -> list[Or]:
        return [Or(board[i+di][j+dj]==0 for di,dj in product(range(n), repeat=2)) for i,j in product(range(len(board)-n+1), range(len(board[0])-n+1))]
    
    @staticmethod
    def empty_2x2(board: np.ndarray) -> list[Or]:
        return PuzzleSolver.empty_nxn(n=2, board=board)
    
    @staticmethod
    def orthagonal_neighbors(i: int, j: int, board: np.ndarray) -> list[tuple[int, int]]:
        return [(i+di,j+dj) for (di,dj) in ORTHAGONAL_MOVES if 0<=i+di<len(board) and 0<=j+dj<len(board[0])]
    
    @staticmethod
    def diagonal_neighbors(i: int, j: int, board: np.ndarray) -> list[tuple[int, int]]:
        return [(i+di,j+dj) for (di,dj) in ORTHAGONAL_MOVES if 0<=i+di<len(board) and 0<=j+dj<len(board[0])]
    
    @staticmethod
    def orthagonal_diagonal_neighbors(i: int, j: int, board: np.ndarray) -> list[tuple[int, int]]:
        return PuzzleSolver.orthagonal_neighbors(i=i,j=j,board=board) + PuzzleSolver.diagonal_neighbors(i=i,j=j,board=board)
    
    @staticmethod
    def knight_neighbors(i: int, j: int, board: np.ndarray) -> list[tuple[int, int]]:
        return [(i+di,j+dj) for di,dj in KNIGHT_MOVES if 0<=i+di<len(board) and 0<=j+dj<len(board[0])]
    
    @staticmethod
    def knight_moves(board: np.ndarray) -> list[Or]:
        return [Or(val==0, val==1, PbEq([(board[k][l]==val-1, 1) for k,l in PuzzleSolver.knight_neighbors(i=i,j=j,board=board)], 1)) for (i,j),val in np.ndenumerate(board)]

    @staticmethod
    def partial_orthagonal_connection(board: np.ndarray) -> list[Implies]:
        return [Implies(board[i][j]!=0, Or([board[ni][nj]!=0 for (ni,nj) in PuzzleSolver.diagonal_neighbors(i=i,j=j,board=board)])) for (i,j),_ in np.ndenumerate(board)]
        
    @staticmethod
    def one_needs_to_change(board: np.ndarray, output: np.ndarray) -> Or:
        return Or([board[i][j]!=output[i][j] for (i,j),_ in np.ndenumerate(board)])

    @staticmethod
    def fully_connected(output: np.ndarray) -> bool:
        return np.max(label(output!=0, connectivity=1)) == 1
