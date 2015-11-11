/*

 * TheLabyrnith.cpp
 *
 *  Created on: Nov 9, 2015
 *      Author: k1
 */

#include "mylibs.h"

class LabyrnithNode {
    int goal_cost;
public:
    vi pos;
    static vi goal;
    static int board_length;
    int start_cost;
    vi came_from;
    LabyrnithNode(vi p, vi cf, int cs): pos(p) {
        came_from = cf;
        start_cost = cs;
        goal_cost = abs(pos[0] - goal[0]) + abs(pos[1] - goal[1]);
    };
    int total_cost(void) const { return start_cost + goal_cost;}
    int lex_order(void) const { return pos[0] * board_length + pos[1]; }
    bool is_goal(void) const { return (pos[0] == goal[0] && pos[1] == goal[1]); }
    friend std::ostream& operator<<(std::ostream& os, const LabyrnithNode& node);
};

std::ostream& operator<<(std::ostream& os, const LabyrnithNode& node) {
    os << "Node(" << node.pos[0] << "," << node.pos[1] << ") with " << node.start_cost << " and " << node.goal_cost << " total of " << node.total_cost() << endl;
    return os;
}
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
typedef priority_queue<LabyrnithNode, vector<LabyrnithNode>, HeapComparison> my_pq;

void find_best_path(vvi &labyrnith, vi start) {
    set<LabyrnithNode, SetComparison> visited;
    my_pq pq(HeapComparison(true));
    LabyrnithNode current = LabyrnithNode(start, vi(2, -1), 0);
    pq.push(current);
    vvi neighbors = vvi(4, vi(2, 0));
    while (!pq.empty()) {
        current = pq.top();
        pq.pop();
        if (current.is_goal())
            break;
        visited.insert(current);
        neighbors[0][0] = (current.pos[0] > 0) ? current.pos[0] - 1 : 0;
        neighbors[0][1] = current.pos[1];
        neighbors[1][0] = (current.pos[0] < current.board_length - 1) ? current.pos[0] + 1 : current.pos[0];
        neighbors[1][1] = current.pos[1];
        neighbors[2][0] = current.pos[0];
        neighbors[2][1] = (current.pos[1] > 0) ? current.pos[1] - 1 : 0;
        neighbors[3][0] = current.pos[0];
        neighbors[3][1] = (current.pos[1] < current.board_length - 1) ? current.pos[1] + 1 : current.pos[1];
        for (vvi::iterator it = neighbors.begin(); it != neighbors.end(); ++it) {
            if (labyrnith[(*it)[0]][(*it)[1]] == 0) {
                LabyrnithNode neighbor = LabyrnithNode((*it), current.pos , current.start_cost + 1);
                if (visited.find(neighbor) == visited.end()) {
                    pq.push(neighbor);
                }
            }
        }
    }
    while (current.came_from[0] != -1) {
        labyrnith[current.pos[0]][current.pos[1]] = -1;
        current = (*(visited.find(LabyrnithNode(current.came_from, vi(2, 0) , 0))));
    }
    labyrnith[current.pos[0]][current.pos[1]] = -1;
}

void print_labyrnith(const vvi labyrnith, int n_len) {
    for (int i = 0; i < n_len; ++i) {
        for (int j = 0; j < n_len; ++j) {
            if (labyrnith[i][j] == 0)
                cout << ' ';
            else if (labyrnith[i][j] == 1)
                cout << '*';
            else
                cout << '+';
        }
        cout << endl;
    }
}

vi LabyrnithNode::goal = vi(2, 0);
int LabyrnithNode::board_length = 0;

int main(int argc, char *argv[]) {
    ifstream stream(argv[1]);
    string line;
    if (!getline(stream, line))
        return 0;
    int n_len = line.length();
    if (n_len == 1) {
        cout << "+" << endl;
        return 0;
    }
    LabyrnithNode::board_length = n_len;
    vvi labyrnith = vvi(n_len, vi(n_len));
    vi start = vi(2,0);
    int row = 0;
    do {
        if (!line.length())
            continue;
        for (int col = 0; col < line.length(); ++col) {
            labyrnith[row][col] = (line[col] == '*') ? 1 : 0;
            if (row == 0 && labyrnith[0][col] == 0)
                start[1] = col;
            if (row == n_len - 1 && labyrnith[row][col] == 0) {
                LabyrnithNode::goal[0] = row;
                LabyrnithNode::goal[1] = col;
            }
        }
        row++;
    } while (getline(stream, line));
    find_best_path(labyrnith, start);
    print_labyrnith(labyrnith, n_len);
    return 0;
}
