// Roberto Herrera
#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <unordered_set>

struct Edge {
  Edge(int dist, int from, int to) : dist(dist), from(from), to(to) {}
  int dist;
  int from;
  int to;
  Edge(int dist, int to) : dist(dist), to(to) {}
};

// Custom sort lambda to indicate that edges with smaller distances
// should be sorted first in the priority queue.
auto cmp = [](Edge left, Edge right) {
  // Return true to indicate selecting the right.
  return left.dist > right.dist;
};

int main() {
  std::map<std::string, int> node_map;
  // std::map<int, std::string> inv_node_map;
  std::vector<std::string> graph;
  std::vector<Edge> edges;
  std::unordered_set<int> visited;
  std::stack<int> stack;

  // Define a `queue` that holds Edges and sorts them using our custom
  // comparator.
  std::priority_queue<Edge, std::vector<Edge>, decltype(cmp)> queue(cmp);

  int n, m;
  std::cin >> n;

  for (int i = 0; i < n; i++) {
    std::string name;
    std::cin >> name;
    node_map.insert({name, i});
    graph.push_back(name);
  }

  std::vector<std::vector<int>> adj;
  adj.resize(n, std::vector<int>(n, -1));

  std::cin >> m;
  std::string from, to;
  int dist;

  // insert distances between nodes
  for (int i = 0; i < m; i++) {
    std::cin >> from >> to >> dist;
    int f = node_map.find(from)->second;
    int t = node_map.find(to)->second;
    adj[f][t] = dist;
  }

  std::cin >> from >> to;
  dist = 0;

  std::vector<int> solved(n, -1);
  int final_dist;

  int node = node_map.find(from)->second;

  // bfs
  while (true) {
    // insert children of node if node has not been visited
    if (visited.find(node) == visited.end()) {
      for (int j = 0; j < n; j++) {
        if (adj[node][j] != -1) {
          queue.push(Edge(dist + adj[node][j], node, j));
        }
      }
    }

    // visit that node
    visited.insert(node);

    // If children of node has already been visited, pop it
    if (visited.find(queue.top().to) == visited.end()) {
      dist = queue.top().dist;
      solved[queue.top().to] = queue.top().from;
      node = queue.top().to;
    }

    queue.pop();

    if (queue.empty() && solved[node_map.find(to)->second] != -1) {
      final_dist = dist;
      break;
    }
  }

  std::vector<std::string> path;

  // backtrack
  int i = node_map.find(to)->second;
  path.push_back(graph[i]);

  while (true) {
    i = node_map.find(graph[solved[i]])->second;
    path.push_back(graph[i]);
    if (i == node_map.find(from)->second) {
      break;
    }
  }

  // print shortest path and its distance
  std::cout << final_dist;
  for (int i = path.size() - 1; i >= 0; i--) {
    std::cout << " " << path[i];
  }
}
