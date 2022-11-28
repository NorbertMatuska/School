import threading
import time
import random
# import sys

'''
    * class for defining a problem
    * a problem instance is created with board size(n) and time limit arguments
'''


# sys.setrecursionlimit(5000)
class Problem:
    def __init__(self, n, timelimit, initialState):

        # initial state or starting point of the knight
        self.initialState = [1, 1]

        # actions a knight can take is set
        self.actions = [[-2, 1], [-2, -1], [-1, 2], [1, 2],
                        [2, 1], [2, -1], [1, -2], [-1, -2]]
        # self.actions = [[2, -1], [2, 1], [-1, -2], [1, -2],
        #                [-2, 1], [-2, -1], [-1, 2], [1, 2]]

        # board size is set
        self.n = n

        # timeout flag for breaking the search algorithm
        self.timeout = False

        # timer initialization
        # timer works on a thread and stopExecution method will be invoked once timelimit is reached
        self.timer = threading.Timer(timelimit, self.stopExecution)

    # sets timeout flag to True so that search algorithm finishes with timeout
    def stopExecution(self):
        self.timeout = True

    # goal test implementation; checks if the state length is equal to the number of tiles on board
    # an element of a node's state indicates a unique tile that is already visited
    def goalTest(self, state):
        if len(state) == (self.n * self.n):
            return True
        else:
            return False


'''
    * class for defining a node
    * a node can be created with four arguments but passing parent, action, state arguments is not mandatory
    * since root node does not have a parent node or an action that is taken to reach itself
    * or a state except the initial one
'''


class Node:

    def __init__(self, problem, parent=None, action=None, state=None):

        # location of node on board
        self.location = None

        # problem that the node belongs to
        self.problem = problem

        # parent of the node
        self.parent = parent

        # action that is taken to reach this node
        self.action = action

        # if node doesn't have a parent, then it is the root node so its state is initialized with the initial state
        # location is set to initial state as well
        if self.parent is None:
            self.state = []
            self.state.append(self.problem.initialState)
            self.location = self.problem.initialState

        # if it is not the root node enters here to set its state and location
        # gets the state of its parent and then current location of the node is appended to state
        else:
            self.state = self.parent.state[:]
            new_x = self.parent.location[0] + self.action[0]
            new_y = self.parent.location[1] + self.action[1]
            self.state.append([new_x, new_y])
            self.location = [new_x, new_y]


# checks if a child node is already in the frontier or not
def isChildInFrontier(frontier, child):
    for node in frontier:
        if node.state == child.state:
            return True
    return False


# generate 5 random starting positions, which are used while testing the program
def generate_starting_positions(size):
    positions = [[1, size]]

    while len(positions) != 5:
        duplicate = False
        y = random.randint(1, size)
        x = random.randint(1, size)
        for i in range(len(positions)):
            # checks if the starting position is a duplicate
            if y == positions[i][1] and x == positions[i][0]:
                duplicate = True
                break
        if duplicate:
            continue
        positions.append([x, y])
    return positions


# function for solving the knights tour problem using depth first search
def dfs(problem):
    # thread which will terminate the process once timelimit is reached is started
    problem.timer.start()
    # starting time of the algorithm is saved
    start_time = time.time()

    # root node is created
    node = Node(problem)
    # applies goal test to root node
    if problem.goalTest(node.state):
        print("A solution found. ")
        print(node.state)
        print("Execution time is %s seconds" % (time.time() - start_time))
        return

    # frontier is initialized
    frontier = []
    frontier.append(node)
    # explored set is initialized
    explored = []
    # goalNotFound variable is used to determine whether the search ends successfully or unsuccessfully,
    # and it is initialized to 0
    goalNotFound = True
    # keeps the number of nodes that are expanded
    num_expnded_node = 0
    # as long as frontier has nodes and timeout doesn't occur and the goal state is not found loop continues
    while not problem.timeout and goalNotFound and frontier:
        # last element in the frontier is retrieved(acts as a stack) and number of expanded nodes is increased by 1
        node = frontier.pop()
        num_expnded_node += 1
        # state of the newly popped node is put into explored set
        explored.append(node.state)
        # for each action that a knight can take from its current location
        # location of the tile that will be visited by that action is found
        # and if it is inside of the board a child node is created
        # if this child node is not already visited(not in node.state)
        # if it is not in the explored set
        # and if child is not in frontier, then goal test will be applied on it
        # if state of the child is the goal state then goalNotFound is set to False to indicate that a solution is found
        # otherwise child will be put into frontier
        for action in problem.actions:
            temp_x = node.location[0] + action[0]
            temp_y = node.location[1] + action[1]
            if temp_x > 0 and temp_x <= problem.n and temp_y > 0 and temp_y <= problem.n:
                child = Node(problem, node, action)
                if child.location not in node.state and child.state not in explored and not isChildInFrontier(frontier,
                                                                                                              child):
                    if problem.goalTest(child.state):
                        goalNotFound = False
                        break
                    frontier.append(child)

    # a solution is found; timeout didn't occur and a goal state is found (goalNotFound becomes false)
    if not goalNotFound and not problem.timeout:
        print("A solution found. ")
        print(child.state)
        print("Execution time is %s seconds" % (time.time() - start_time))
    # a solution is not found; timeout didn't occur and a goal state is not found (goalNotFound remains true)
    elif goalNotFound and not problem.timeout:
        print("No solution exists. ")
        print(child.state)
    # timeout occurred; a goal state is not found (goalNotFound remains true) and timeout occurred
    elif goalNotFound and problem.timeout:
        print("Timeout")
    # prints the search method and number of expanded nodes
    print("Searched with depth first search method. ")
    print("Number of nodes expanded: " + str(num_expnded_node))


# it gets board size and timelimit
choice = True
while choice:
    n = int(input("Enter board size: "))
    timelimit = int(input("Enter timelimit: "))
    initialState = generate_starting_positions(n)
    print("Initial starting positions:\n ")
    print(initialState)
    for i in range(len(initialState)):
        print("\nTest number " + str(i+1) + ":")
        print("For initial state: " + str(initialState[i]))
        if n % 2 == 1 and n > 3:
            # an if statement so we dont have to search unsolvable problems and save time
            # if u want to know more, see program documentation, it is explained why the if statement is like this
            if initialState[i][0] % 2 == 0 and initialState[i][1] % 2 == 1:
                print("Unable to find a solution, because the starting point is on a white tile")
                print("See program documentation for more information")
                continue
            elif initialState[i][0] % 2 == 1 and initialState[i][1] % 2 == 0:
                print("Unable to find a solution, because the starting point is on a white tile")
                print("See program documentation for more information")
                continue
        problem = Problem(n, timelimit, initialState[i])
        dfs(problem)
    cont = input("Continue with testing? Y/N: ")
    if cont == "N" or cont == "n":
        exit(0)
