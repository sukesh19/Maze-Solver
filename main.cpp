#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// Define the size of the maze
const int N = 8;

// Define the maze characters
const char WALL = '#';
const char PATH = '-';
const char START = 's';
const char GOAL = 'g';
const char VISITED = '.';
const char FINAL_PATH = 'o';

// The original maze, a constant reference to a clean state
const char ORIGINAL_MAZE[N][N] = {
    {'#', '#', '#', '#', '#', '#', '#', '#'},
    {'#', 'g', '-', '-', '#', '-', '-', '#'},
    {'#', '#', '#', '-', '-', '-', '#', '#'},
    {'#', '-', '#', '#', '-', '-', '-', '#'},
    {'#', '-', '-', '#', '-', '-', '-', '#'},
    {'#', '-', '-', '-', '-', '#', '#', '#'},
    {'#', '-', '-', '#', '-', '-', 's', '#'},
    {'#', '#', '#', '#', '#', '#', '#', '#'}
};

// The working maze, which will be modified by the algorithms
char maze[N][N];
bool visited[N][N];

// Node structure for BFS, stores coordinates and parent for path reconstruction
struct Node {
    int x, y;
    Node* parent;
    Node(int x_coord, int y_coord, Node* p = nullptr) : x(x_coord), y(y_coord), parent(p) {}
};

// Function to reset the maze and visited array to their original states
void resetMaze() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            maze[i][j] = ORIGINAL_MAZE[i][j];
            visited[i][j] = false;
        }
    }
}

// Function to print the current state of the maze
void printMaze() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << maze[i][j] << " ";
        }
        cout << endl;
    }
}

// Helper function to check if a coordinate is within bounds and is a valid path
bool isValid(int x, int y) {
    return x >= 0 && y >= 0 && x < N && y < N && maze[x][y] != WALL && !visited[x][y];
}

// DFS Implementation (recursive)
bool dfs(int x, int y) {
    if (!isValid(x, y)) {
        return false;
    }

    visited[x][y] = true;
    
    // Base case: if we found the goal, return true
    if (maze[x][y] == GOAL) {
        return true;
    }

    // Mark the current cell as visited, but not if it's the start or goal
    if (maze[x][y] != START) {
        maze[x][y] = VISITED;
    }

    // Recursively try all four directions
    if (dfs(x - 1, y) || dfs(x + 1, y) || dfs(x, y - 1) || dfs(x, y + 1)) {
        // If a path was found, mark the current cell as part of the path
        if (maze[x][y] != START && maze[x][y] != GOAL) {
            maze[x][y] = FINAL_PATH;
        }
        return true;
    }

    return false;
}

// BFS Implementation (iterative with a queue)
bool bfs(int sx, int sy) {
    queue<Node*> q;
    Node* startNode = new Node(sx, sy);
    q.push(startNode);
    visited[sx][sy] = true;

    while (!q.empty()) {
        Node* curr = q.front();
        q.pop();

        if (maze[curr->x][curr->y] == GOAL) {
            // Reconstruct the path from the goal to the start
            Node* temp = curr;
            while (temp->parent != nullptr) {
                if (maze[temp->x][temp->y] != START && maze[temp->x][temp->y] != GOAL) {
                    maze[temp->x][temp->y] = FINAL_PATH;
                }
                temp = temp->parent;
            }
            return true;
        }

        // Mark current cell as visited
        if (maze[curr->x][curr->y] != START) {
            maze[curr->x][curr->y] = VISITED;
        }

        // Directions: up, down, left, right
        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};
        for (int d = 0; d < 4; d++) {
            int nx = curr->x + dx[d];
            int ny = curr->y + dy[d];
            if (isValid(nx, ny)) {
                visited[nx][ny] = true;
                Node* nextNode = new Node(nx, ny, curr);
                q.push(nextNode);
            }
        }
    }
    return false;
}

int main() {
    int sx = 0, sy = 0;
    // Find the start position from the original maze
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (ORIGINAL_MAZE[i][j] == START) {
                sx = i;
                sy = j;
                break;
            }
        }
    }

    // ---
    // DFS Section
    // ---
    cout << "Starting DFS search...\n";
    resetMaze();
    if (dfs(sx, sy)) {
        cout << "Path found using DFS!\n";
    } else {
        cout << "No path found using DFS.\n";
    }
    cout << "\nResult Maze (DFS):\n";
    printMaze();

    cout << "\n-------------------\n";

    // ---
    // BFS Section
    // ---
    cout << "Starting BFS search...\n";
    resetMaze();
    if (bfs(sx, sy)) {
        cout << "Path found using BFS!\n";
    } else {
        cout << "No path found using BFS.\n";
    }
    cout << "\nResult Maze (BFS):\n";
    printMaze();

    return 0;
}
