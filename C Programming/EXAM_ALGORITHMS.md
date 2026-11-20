# DSA Lab Exam: Pure Plain English Algorithms (Zero Code)

> **Instructions for Exam:** These algorithms contain **zero code** and **zero programming syntax**. You can memorize these plain English steps and write them word-for-word on your answer paper.

---

## 1. Hash Table (Separate Chaining and Open Addressing)

### Aim:
To store and search key-value pairs in a hash table using Separate Chaining and Open Addressing techniques.

### Algorithm:
* **Step 1:** Start.
* **Step 2:** Create an empty hash table of a fixed size and mark all locations as empty.
* **Step 3:** Choose the collision technique: Separate Chaining or Open Addressing.
* **Step 4:** To insert an item, calculate its slot number by dividing the key by the table size and taking the remainder.
* **Step 5 (Separate Chaining):** Go to the calculated slot. If a collision occurs, attach the new item as a linked node in that slot's chain.
* **Step 6 (Open Addressing):** Go to the calculated slot. If it is already occupied, check the next slots one by one until an empty slot is found, and place the item there.
* **Step 7 (Search):** Calculate the slot number using the remainder. For chaining, search through the chain at that slot. For open addressing, check consecutive slots until the key is found or an empty slot is reached.
* **Step 8 (Display):** Print the contents of all slots and chains to show where each item is stored.
* **Step 9:** Stop.

---

## 3. Breadth-First Search (BFS) and Shortest Path

### Aim:
To explore a graph level by level using Breadth-First Search and find the shortest path between two points.

### Algorithm:
* **Step 1:** Start.
* **Step 2:** Set up the graph by taking the total number of points and connecting them with edges.
* **Step 3:** Choose a starting point and a destination point.
* **Step 4:** Mark all points as unvisited, set their distances to unknown, and prepare an empty waiting line (queue).
* **Step 5:** Mark the starting point as visited, set its distance to zero, and add it to the waiting line.
* **Step 6:** While the waiting line is not empty, take out the first point in line and print it.
* **Step 7:** For every unvisited neighbor of this point:
  * Mark the neighbor as visited.
  * Set its distance to one step more than the current point.
  * Record the current point as its parent.
  * Add this neighbor to the back of the waiting line.
* **Step 8:** When the destination is reached, print its total distance in steps.
* **Step 9:** Trace backward from the destination to the start point using the recorded parents to print the shortest path.
* **Step 10:** Stop.

---

## 4. Depth-First Search (DFS), Cycle Detection and Connectivity

### Aim:
To explore a graph deeply using Depth-First Search, check if it contains a closed loop (cycle), and check if all points are connected.

### Algorithm:
* **Step 1:** Start.
* **Step 2:** Set up the graph with all its points and connections, and mark all points as unvisited.
* **Step 3 (DFS Traversal):** Start at a point, mark it as visited, and print it.
* **Step 4:** Move deeply into its first unvisited neighbor and repeat the visit. Keep going deeper until reaching a point with no unvisited neighbors, then backtrack.
* **Step 5 (Cycle Detection):** While exploring, if you see a neighbor that is already visited and is not the point you just came from, declare that a cycle (loop) exists.
* **Step 6 (Connectivity Check):** After finishing, check if any points remain unvisited. If yes, start a new exploration from an unvisited point and count it as a separate component.
* **Step 7:** If the entire graph was explored in a single run (one component), declare the graph as CONNECTED. Otherwise, declare it as DISCONNECTED.
* **Step 8:** Stop.

---

## 5. Disjoint Set Union (Union-Find) with Dynamic Connectivity

### Aim:
To manage separate groups of elements, merge them dynamically, and check if any two elements are connected.

### Algorithm:
* **Step 1:** Start.
* **Step 2:** Create separate groups such that every element is initially its own leader with a rank of zero.
* **Step 3 (Find Operation):** To find an element's group leader, follow the chain upward to the top leader.
* **Step 4 (Path Compression):** While finding the leader, re-attach all visited elements directly to the top leader so future searches become instant.
* **Step 5 (Union Operation):** To connect two elements, find the leaders of both elements.
* **Step 6 (Union by Rank):** If they have different leaders, attach the shorter group under the leader of the taller group. If both groups have equal height, increase the winning leader's rank by one.
* **Step 7 (Connectivity Query):** To check if two elements are connected, find the leader of each. If both have the exact same leader, they are CONNECTED; otherwise, they are NOT CONNECTED.
* **Step 8:** Stop.

---

## 14. Graph Representations (Adjacency Matrix and Adjacency List)

### Aim:
To represent a graph using a 2D grid (Adjacency Matrix) and linked lists (Adjacency List) with basic operations.

### Algorithm:
* **Step 1:** Start.
* **Step 2:** Take the total number of points in the graph.
* **Step 3 (Initialization):** Create a 2D grid filled with zeros, and create an empty list of neighbors for each point.
* **Step 4 (Add Connection):** For each connection between two points:
  * In the Matrix: Put a 1 in the grid cell connecting both points in both directions.
  * In the List: Add each point to the beginning of the other point's neighbor list.
* **Step 5 (Display Matrix):** Print the 2D grid row by row showing 1 where connections exist and 0 where they do not.
* **Step 6 (Display List):** For every point, print its name followed by the chain of all its connected neighbors.
* **Step 7 (Check Connection):** To check if two points are connected, see if their grid cell contains 1, or search for one point inside the other point's neighbor list.
* **Step 8:** Stop.
