# Instructions  

The goal of this exercise is to understand and implement Djikstra's algorithm to find the shortest path between two nodes in a directed and weighted graph.

See the
[slides](https://docs.google.com/presentation/d/1CU9JPFpyhRlgBSjQIaPYpfa2Vt0lU1_nOTby7iBOCPs/edit?usp=sharing)
for a walkthrough of Djikstra's algorithm using the below example input.

## Data Structures

I used several data structures in my implementation
* Vector (to hold the graph)
* Map (map of name to index, and the reverse)
* Priority Queue (heap)
* Stack (for reversing the path)
* Set (visitor set)

You may use this snippet of code for your priority queue.

```
struct Edge {
  Edge(int dist, int from, int to) : dist(dist), from(from), to(to) {}
  int dist;
  int from;
  int to;
};

// Custom sort lambda to indicate that edges with smaller distances
// should be sorted first in the priority queue.
auto cmp = [](Edge left, Edge right) {
  // Return true to indicate selecting the right.
  return left.dist > right.dist;
};

// Define a `queue` that holds Edges and sorts them using our custom comparator.
std::priority_queue<Edge, std::vector<Edge>, decltype(cmp)> queue(cmp);
```

## Input / Output

The first line of input will be an integer N that indicates the number of nodes in the graph.

The second line of input will be N strings indicating the names of each node.

The third line of input will be an integer M that indicates the number of edges in the graph.

M lines follow listing each edge as a tuple of start, end, and weight.

Finally, the last line will contain two strings indicating the two nodes to find the shortest path between.

**Example Input**
```
8
a b c d e f g h
11
a b 2
a c 5
b c 3
b d 4
c d 2
c e 4
d f 7
e h 19
f g 3
f h 10
g h 1
a h
```

Your program must output a single line. First, the shortest distance between the start and end nodes must be printed, then the names of each node along the path.

**Example Output**
```
17 a b d f g h
```