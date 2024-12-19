import random
import time


# define a class to represent the knights tour problem
class KnightsTour:
    def __init__(self, board_size):
        # initialize the board_size and create a chessboard filled with "-1" (unvisited positions)
        self.board_size = board_size
        self.board = [[-1 for _ in range(board_size)] for _ in range(board_size)]
        # define the possible knight moves and initialize expanded nodes (visited positions)
        self.moves = [(2, 1), (1, 2), (-1, 2), (-2, 1), (-2, -1), (-1, -2), (1, -2), (2, -1)]
        self.expanded_nodes = 0

    # check if the move is withing bounds and on an unvisited positions
    def is_valid_move(self, x, y):
        if 0 <= x < self.board_size and 0 <= y < self.board_size and self.board[x][y] == -1:
            return True
        return False

    # the main solving function
    def solve(self, x_start, y_start):
        # initialize the starting position on a board
        self.board[x_start][y_start] = 0
        # call the recursive solver function
        if self.solve_recursive(x_start, y_start, 1):
            # if a solution has been found, print the solution and number of expanded nodes
            self.print_solution()
            print("Expanded nodes: " + str(self.expanded_nodes))
        else:
            # if a solution hasnt been found or if there were too many moves made, print this
            print("No solution was found.")

    # recursive solver function
    def solve_recursive(self, x, y, move_num):
        # if the number of moves equals the board_size^2, the solution has been found
        if move_num == self.board_size * self.board_size:
            return True

        # iterate through the possible moves and calculate the next move
        for k in range(8):
            next_x = x + self.moves[k][0]
            next_y = y + self.moves[k][1]

            # if it is a valid move, write it into the board and increment visited positions
            if self.is_valid_move(next_x, next_y):
                self.board[next_x][next_y] = move_num
                self.expanded_nodes += 1
                # maximum number of moves
                if self.expanded_nodes >= 10000000:
                    return False
                # recursively explore the next move
                if self.solve_recursive(next_x, next_y, move_num + 1):
                    return True
                # If the recursive call returns False, backtrack by resetting the position
                self.board[next_x][next_y] = -1

        return False

    # format the solution and print it out
    def print_solution(self):
        for row in self.board:
            for num in row:
                if num < 10:
                    print(" " + str(num), end=" ")
                else:
                    print(str(num), end=" ")
            print()


def test_knights_tour():
    board_size = int(input("Enter board size: "))
    # test for 5 random starting positions
    for i in range(5):
        print("\nTest number " + str(i + 1) + ":")

        x = random.randint(0, board_size - 1)
        y = random.randint(0, board_size - 1)
        # first starting position is always set to be lower left corner
        if i == 0:
            x = board_size - 1
            y = 0
        print("Testing for position: " + str(x), str(y))

        knights_tour = KnightsTour(board_size)

        # measure the execution time of solving the problem
        start_time = time.time()
        knights_tour.solve(x, y)
        end_time = time.time()
        solve_time = end_time - start_time
        print("Execution time is " + str(solve_time) + " seconds")


if __name__ == "__main__":

    test_knights_tour()
