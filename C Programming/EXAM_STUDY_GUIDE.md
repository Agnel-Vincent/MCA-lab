# DSA Lab Exam Comprehensive Study Guide
### Master C Programming & Data Structures from First Principles

> **Context:** This guide is designed specifically for students with zero prior knowledge of C or Data Structures who need to understand, memorize, and explain the logic of 5 essential lab exam programs.

---

## Table of Contents
1. [Crash Course: The 4 C Concepts You Must Know](#1-crash-course-the-4-c-concepts-you-must-know)
2. [Program 1: Hash Table (Separate Chaining & Open Addressing)](#2-program-1-hash-table)
3. [Program 3: Breadth-First Search (BFS) & Shortest Path](#3-program-3-breadth-first-search-bfs--shortest-path)
4. [Program 4: Depth-First Search (DFS), Cycle Detection & Connectivity](#4-program-4-depth-first-search-dfs-cycle-detection--connectivity)
5. [Program 5: Disjoint Set Union (DSU / Union-Find)](#5-program-5-disjoint-set-union-dsu--union-find)
6. [Program 14: Graph Representations (Matrix vs. List)](#6-program-14-graph-representations-matrix-vs-list)
7. [Examiner Viva Q&A Cheat Sheet](#7-examiner-viva-qa-cheat-sheet)

---

## 1. Crash Course: The 4 C Concepts You Must Know

Before looking at the algorithms, you only need to understand four basic building blocks in C:

### 1. Modulo Operator (`%`)
`a % b` gives the **remainder** when `a` is divided by `b`.
* `10 % 7 = 3` (because $7 \times 1 = 7$, remainder is $3$)
* `17 % 7 = 3` (because $7 \times 2 = 14$, remainder is $3$)
* `24 % 7 = 3` (because $7 \times 3 = 21$, remainder is $3$)
* **Why we use it:** No matter how large a number is, `key % 7` will always produce a valid array index between `0` and `6`.

### 2. Structures (`struct`)
A `struct` packages multiple variables together into one custom data type:
```c
struct Node {
    int key;
    int value;
    struct Node* next; // Arrow pointing to the next node in memory
};
```

### 3. Pointers (`*`) and Dynamic Memory (`malloc`)
* A normal variable stores a **value** (`int x = 10;`).
* A pointer stores the **memory address** of another variable (`struct Node* p;`).
* `malloc(sizeof(struct Node))` asks the operating system: *"Give me a new block of RAM to hold one Node."*
* `p->key` means: *"Go to the node that `p` is pointing to, and access its `key`."*

### 4. 2D Arrays (Matrices)
`int adj[MAX][MAX];` is simply a grid (chessboard).
* `adj[u][v] = 1;` means there is a road (edge) between vertex `u` and vertex `v`.
* `adj[u][v] = 0;` means there is no road.

---

## 2. Program 1: Hash Table
**File:** `1_hash_table.c`

### What Problem Are We Solving?
Imagine you have student roll numbers (Keys) and their marks (Values).
* If you store them in a simple list of 1,000 students and want to find roll number 942, you have to search through elements one by one ($O(N)$ time). That is slow.
* A **Hash Table** allows you to jump directly to the answer in **$O(1)$ time (instant lookup)** by mathematically calculating where the item is stored.

### The Math: The Hash Function
```c
int hash(int key) {
    int idx = key % SIZE;
    return (idx < 0) ? idx + SIZE : idx;
}
```
If table size is `7`:
* Key `10` $\to 10 \% 7 =$ Slot `3`
* Key `5` $\to 5 \% 7 =$ Slot `5`

### The Big Problem: Collisions
What happens if we insert Key `17`?
$17 \% 7 = 3$. But Slot `3` is already holding Key `10`!
Two different keys wanting the exact same slot is called a **Collision**.
The exam requires you to demonstrate the two standard ways to solve this:

---

### Technique A: Separate Chaining (Closed Addressing)
**Analogy:** Each table slot is a coat hook. If multiple coats have the same number, you don't throw them away; you hang them one after another on the same hook as a chain (Linked List).

```
Slot [0]: NULL
Slot [1]: NULL
Slot [2]: NULL
Slot [3]: [Key 17 | Val 170] -> [Key 10 | Val 100] -> NULL   <-- Colliding keys chained together!
Slot [4]: NULL
Slot [5]: [Key 5  | Val 50 ] -> NULL
Slot [6]: NULL
```

#### How `insertChain(k, v)` works:
1. Calculate slot: `h = hash(k);`
2. Walk through the list at `chain[h]`. If the key already exists, simply update its value and return.
3. Otherwise, create a new node with `malloc`.
4. Put the new node at the **front (head)** of the chain:
   ```c
   n->next = chain[h];
   chain[h] = n;
   ```
   *Why at the front?* Inserting at the front takes $O(1)$ time (no need to walk to the end of the list).

#### How `searchChain(k)` works:
1. Jump directly to `h = hash(k);`.
2. Walk down that specific chain: `for (p = chain[h]; p != NULL; p = p->next)`.
3. If `p->key == k`, we found it! Print the value. If we reach `NULL`, it does not exist.

---

### Technique B: Open Addressing with Linear Probing
**Analogy:** A parking lot. If parking space `3` is already taken, you don't stack cars on top of each other. You simply drive forward to space `4`. If `4` is taken, check `5`, and so on.

```
Slot [0]: EMPTY
Slot [1]: EMPTY
Slot [2]: EMPTY
Slot [3]: (Key 10, Val 100)  <-- Landed here first
Slot [4]: (Key 17, Val 170)  <-- Collided at 3! Moved forward to slot 4
Slot [5]: (Key 5,  Val 50 )
Slot [6]: EMPTY
```

#### How `insertOpen(k, v)` works:
1. Calculate `h = hash(k);`.
2. Check slots in a circular loop:
   ```c
   for (int i = 0; i < SIZE; i++) {
       int idx = (h + i) % SIZE;
       // If empty or already has this key, store it!
       if (!used[idx] || oKey[idx] == k) {
           oKey[idx] = k; oVal[idx] = v; used[idx] = 1;
           return;
       }
   }
   ```
3. If the loop finishes without finding an empty slot, the table is completely full.

#### How `searchOpen(k)` works:
1. Start at `h = hash(k);`.
2. Walk forward: `idx = (h + i) % SIZE;`.
3. **Crucial Rule:** If you hit an **EMPTY** slot (`!used[idx]`), you **stop immediately**. Why? Because if the key had been inserted, it would have been placed there or earlier. If you find `oKey[idx] == k`, you found it!

---

## 3. Program 3: Breadth-First Search (BFS) & Shortest Path
**File:** `3_bfs_shortest_path.c`

### What is a Graph?
A graph is a network of **Vertices** (points/cities) connected by **Edges** (roads).
* `adj[u][v] = 1; adj[v][u] = 1;` means an unweighted, two-way road connects city `u` and city `v`.

### What is BFS?
**Analogy:** Throwing a stone into water. Ripples expand outward layer-by-layer:
* Layer 0: The start vertex.
* Layer 1: All immediate neighbors (1 step away).
* Layer 2: All neighbors of neighbors (2 steps away).
* Layer 3: Nodes 3 steps away, and so on.

To process nodes layer by layer, BFS strictly uses a **Queue (FIFO: First-In, First-Out)**:
* `q[rear++] = src;` (Add to queue / Enqueue)
* `u = q[front++];`  (Take out of queue / Dequeue)

```
        0 (Start)
       / \
      1   2     <-- Layer 1 (Distance = 1)
     / \   \
    3   4---5   <-- Layer 2 (Distance = 2)
```

### Why Does BFS Guarantee the Shortest Path?
Because BFS visits every node at distance 1 before visiting anything at distance 2, and every node at distance 2 before distance 3! The very first time BFS touches your destination, it is **guaranteed** to be via the shortest possible number of edges.

### How Path Reconstruction Works (The Breadcrumb Trail):
We keep two helper arrays:
1. `dist[v]`: Stores how many steps it took to reach `v` from source (`dist[v] = dist[u] + 1;`).
2. `parent[v]`: Remembers who discovered `v` (`parent[v] = u;`).

When we reach the destination `dest`, we trace the `parent` pointers backward:
```c
int curr = dest;
while (curr != -1) {
    printf("%d <- ", curr);
    curr = parent[curr]; // Walk backwards to start
}
```
*Example:* `5 <- 4 <- 2 <- 0`. Reversing this gives: `0 -> 2 -> 4 -> 5`!

---

## 4. Program 4: Depth-First Search (DFS), Cycle Detection & Connectivity
**File:** `4_dfs_cycle_connectivity.c`

### What is DFS?
**Analogy:** Exploring a dark maze. You pick a path and walk as deep as possible until you hit a dead end. When you hit a dead end, you **backtrack** to the last junction and try the other branch.
* DFS is implemented naturally using **Recursion** (functions calling themselves).

### 1. The Core DFS Recursion:
```c
void dfs(int u) {
    visited[u] = 1; // Mark this room visited
    printf("%d ", u);

    for (int v = 0; v < n; v++) {
        if (adj[u][v] && !visited[v]) {
            dfs(v); // Go deeper!
        }
    }
}
```

### 2. How Cycle Detection Works:
What is a **Cycle**? A loop where you can walk in circles and return to where you started.
In an undirected graph, when you are standing at node `u` looking at neighbor `v`:
* If `v` has already been visited, is it automatically a cycle? **NO!** Because `v` might just be the parent who brought you to `u` in the first place (walking back across the same edge)!
* **The Golden Rule of Cycle Detection:**
  A cycle exists **if and only if** you see a neighbor `v` that has already been visited AND `v != parent`.
  ```c
  if (visited[v] && v != parent) {
      return 1; // Cycle found! This is a back-edge!
  }
  ```

```
     0 ----- 1
     |       |
     |       |
     4 ----- 3    <-- Walking 0 -> 1 -> 3 -> 4 -> 0:
                      When at 4, neighbor 0 is already visited and is NOT parent (3).
                      CYCLE DETECTED!
```

### 3. How Connectivity Checking Works:
A graph is **Connected** if you can travel from any city to any other city.
* If a graph has disconnected islands (components), a single DFS from node `0` will only visit island 1; it will never reach the other islands.
* **The Logic:**
  ```c
  int components = 0;
  for (int i = 0; i < n; i++) {
      if (!visited[i]) {
          components++;     // Found a new unvisited island!
          dfs(i);           // Explore entire island
      }
  }
  ```
* If `components == 1` $\to$ The graph is **CONNECTED**.
* If `components > 1` $\to$ The graph is **DISCONNECTED**.

---

## 5. Program 5: Disjoint Set Union (DSU / Union-Find)
**File:** `5_dsu_union_find.c`

### What Problem Are We Solving?
Imagine a social network where people make friendships dynamically:
* "Person 0 and 1 are friends."
* "Person 1 and 2 are friends."
* Query: *"Are Person 0 and Person 2 connected?"* $\to$ Yes!
* Query: *"Are Person 0 and Person 5 connected?"* $\to$ No!

We need a data structure that can merge groups (`union`) and test connectivity (`find`) in **near $O(1)$ instant time**.

### The Structure: Trees in an Array
Every element `i` points to a `parent[i]`.
Initially, everyone is alone: `parent[i] = i;` (each node is its own boss/root).

```
Initial State:
Node:   0   1   2   3   4
Parent: 0   1   2   3   4   (5 independent sets)
```

### Optimization 1: Path Compression in `findSet(v)`
When looking for the root of `v`, why climb through 5 parents every single time?
Path compression **flattens the tree**: during `findSet`, every node on the path is updated to point **directly to the head root**!
```c
int findSet(int v) {
    if (v == parent[v]) return v;
    return parent[v] = findSet(parent[v]); // One line magic!
}
```

```
Before Path Compression:       After Path Compression:
      0 (Root)                         0 (Root)
      |                              / | \
      1                             1  2  3  (All point directly to 0!)
      |
      2
      |
      3
```

### Optimization 2: Union by Rank in `unionSets(a, b)`
When merging two trees, should Tree A hang under Tree B, or B under A?
* `rnk[i]` keeps track of tree height.
* **Rule:** Always attach the **shorter tree under the taller tree**. This prevents tall, skewed chains from forming.
* If both trees have equal rank, attach one under the other and increase the winner's rank by 1.
```c
if (rnk[rootA] < rnk[rootB]) {
    parent[rootA] = rootB;
} else if (rnk[rootA] > rnk[rootB]) {
    parent[rootB] = rootA;
} else {
    parent[rootB] = rootA;
    rnk[rootA]++;
}
```

### Dynamic Connectivity Check:
Are `a` and `b` connected?
Simply check if they have the same representative root:
```c
return findSet(a) == findSet(b);
```

---

## 6. Program 14: Graph Representations (Matrix vs. List)
**File:** `14_graph_representations.c`

How do you store a graph in a computer's memory? There are two primary techniques:

### Representation 1: Adjacency Matrix (2D Grid)
* A grid `mat[MAX][MAX]`.
* If an edge exists between `u` and `v`, set `mat[u][v] = 1; mat[v][u] = 1;`.
* **Advantage:** Checking if an edge exists takes instant $O(1)$ time (`if (mat[u][v] == 1)`).
* **Disadvantage:** Takes $\Theta(V^2)$ memory. If you have 10,000 vertices and only 5 edges, you waste 100,000,000 integers of memory filled with zeros!

### Representation 2: Adjacency List (Array of Linked Lists)
* An array of pointers: `struct Node* adj[MAX];`.
* Each vertex `u` has a singly linked list containing only its **actual neighbors**.
* To add edge $(u, v)$:
  * Add $v$ to $u$'s list:
    ```c
    struct Node* n1 = malloc(sizeof(struct Node));
    n1->v = v; n1->next = adj[u]; adj[u] = n1;
    ```
  * Add $u$ to $v$'s list:
    ```c
    struct Node* n2 = malloc(sizeof(struct Node));
    n2->v = u; n2->next = adj[v]; adj[v] = n2;
    ```
* **Advantage:** Takes $\Theta(V + E)$ memory. Only stores edges that actually exist (ideal for sparse real-world graphs like road maps).
* **Disadvantage:** To check if edge $(u, v)$ exists, you must iterate down $u$'s linked list ($O(\text{degree}(u))$).

---

## 7. Examiner Viva Q&A Cheat Sheet

| Question | What the Examiner is Testing | Your Confident Answer |
| :--- | :--- | :--- |
| **Why is modulo (`%`) used in hashing?** | Basic hash function design | *"Modulo maps any integer key into a fixed valid range $[0, \text{SIZE}-1]$ corresponding to array indices."* |
| **What is a collision?** | Definition of collision | *"When two distinct keys produce the exact same hash index: $h(k_1) == h(k_2)$."* |
| **What is the difference between Chaining and Open Addressing?** | Structural understanding | *"Chaining uses linked lists outside the table (closed addressing). Open addressing stores all elements inside the table slots by probing forward on collision."* |
| **Why does BFS find the shortest path in unweighted graphs?** | Algorithm invariant | *"Because BFS expands outward layer by layer using a FIFO queue, visiting all nodes at distance $d$ before distance $d+1$."* |
| **How do you detect a cycle in an undirected graph using DFS?** | DFS back-edges | *"During DFS, if we encounter an adjacent node that is already visited and is NOT the immediate parent, a back-edge (cycle) exists."* |
| **What is Path Compression in DSU?** | DSU optimization | *"During `findSet`, we point every visited node directly to the root, flattening the tree so future lookups take $O(1)$ amortized time."* |
| **Why do we need Union by Rank in DSU?** | Balanced trees | *"It attaches shallower trees under deeper trees to prevent tall, degenerate chains, keeping tree height minimal."* |
| **When should you use Adjacency Matrix vs. Adjacency List?** | Space-time trade-off | *"Use Matrix for dense graphs ($E \approx V^2$) or frequent $O(1)$ edge checks. Use List for sparse graphs ($E \ll V^2$) to save memory."* |

---

### Compile and Run Reminder:
```bash
gcc 1_hash_table.c -o hash && ./hash
gcc 3_bfs_shortest_path.c -o bfs && ./bfs
gcc 4_dfs_cycle_connectivity.c -o dfs && ./dfs
gcc 5_dsu_union_find.c -o dsu && ./dsu
gcc 14_graph_representations.c -o graph && ./graph
```

