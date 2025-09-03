# Maze-Solver
This project implements a maze solver in C++ using two fundamental graph traversal algorithms: Breadth-First Search (BFS) and Depth-First Search (DFS). Given a maze represented as a grid, the program finds a path from the start position to the goal if one exists, marking the path in the maze.
Here is a simple, point-wise README for the Maze Solver project in C++:

Maze Solver using BFS & DFS
Project: Maze solver in C++ using Breadth-First Search (BFS) and Depth-First Search (DFS).

Goal: Find a path from start (s) to goal (g) in a maze grid.

Maze Symbols:

# = Wall

- = Open path

s = Start point

g = Goal point

. = Visited path

Features:

DFS with recursion and backtracking

BFS with queue for shortest path

Marks path found in the maze

How to Run:

Compile: g++ -o maze_solver MazeSolver.cpp

Run: ./maze_solver

Output: Prints the maze with the path marked if found.

Future Enhancements:

Support for custom maze inputs from files

Visual step-by-step solving

Additional algorithms (A*, Dijkstra)

Graphical user interface (GUI)
