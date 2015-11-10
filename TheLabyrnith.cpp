/*

 * TheLabyrnith.cpp
 *
 *  Created on: Nov 9, 2015
 *      Author: k1
 */

#include "mylibs.h"

class LabyrnithNode {
    vi pos;
    int goal_cost;
public:
    static vi goal;
    static int board_length;
    bool visited;
    int start_cost;
    LabyrnithNode *came_from;
    LabyrnithNode(vi p, const LabyrnithNode *nptr): pos(p) {
        came_from = nptr;
        start_cost = nptr->start_cost + 1;
        visited = false;
        goal_cost = abs(pos[0] - goal[0]) + abs(pos[1] - goal[1]);
    };
    int total_cost(void) const { return start_cost + goal_cost;}
    int lex_order(void) const { return pos[0] * board_length + pos[1]; }
};

class HeapComparison {
  bool reverse;
public:
  HeapComparison(const bool& revparam=false)
    {reverse=revparam;}
  bool operator() (const LabyrnithNode& lhs, const LabyrnithNode&rhs) const
  {
    if (reverse) return (lhs.total_cost() > rhs.total_cost());
    else return (lhs.total_cost() < rhs.total_cost());
  }
};

class SetComparison {
public:
 bool operator() (const LabyrnithNode& lhs, const LabyrnithNode&rhs) const
  { return (lhs.lex_order() < rhs.lex_order()); }
};

void find_best_path(vvi &labyrnith, vi start, vi goal) {
    set<vi> visited;
    priority_queue<vi> min_heap (heapComparison());


}
void print_matrix(const vvi labyrnith, int n_len) {
    for (int i = 0; i < n_len; ++i) {
        for (int j = 0; j < n_len; ++j)
            cout << labyrnith[i][j] << " ";
        cout << endl;
    }
}

vi LabyrnithNode::goal = {0, 0};
int LabyrnithNode::board_length = 0;

int main(int argc, char *argv[]) {
    ifstream stream(argv[1]);
    string line;
    if (!getline(stream, line))
        return 0;
    int n_len = line.length();
    LabyrnithNode::board_length = n_len;
    vvi labyrnith = vvi(n_len, vi(n_len));
    vi start, goal;
    int row = 0;
    do {
        if (!line.length())
            continue;
        for (int col = 0; col < line.length(); ++col) {
            labyrnith[row][col] = (line[col] == '*') ? 1 : 0;
            if (row == 0 && labyrnith[0][col] == 0)
                start = {row, col};
            if (row == n_len - 1 && labyrnith[row][col] == 0)
                LabyrnithNode::goal = {row, col};
        }
        row++;
    } while (getline(stream, line));
    find_best_path(labyrnith, start, goal);
//    print_matrix(labyrnith, n_len);
    return 0;
}
