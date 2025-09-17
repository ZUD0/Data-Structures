# 📘 Data Structures & Algorithms – From Scratch

This repository is a **from-scratch** implementation of fundamental data structures and their classical problems & algorithms.
**Goal:** mastery — not just *using* STL/Java Collections/Python built-ins, but **building**, **understanding**, and **applying** them.

---

## 📂 Table of Contents

* 🟦 **Arrays**
* 🟩 **Linked Lists**
* 🟧 **Stacks**
* 🟨 **Queues**
* 🟪 **Heaps**
* 🌳 **Binary Trees**
* 🌲 **Binary Search Trees**
* 🕸️ **Graphs**

---

## 🔹 1. Arrays

**Implementation**

* Static & dynamic arrays
* Insert, delete, search, resize

**Classical Problems**

* 🔄 Reverse array
* 🔁 Rotate array (k steps)
* ❓ Find missing number (1..n)
* ➕ Two Sum / Subarray sum
* 💪 Kadane’s algorithm (max subarray sum)
* 📊 Prefix sum problems

**Algorithms**

* 🪟 Sliding Window
* 🔍 Binary Search (variants: first/last occurrence, upper/lower bound)
* 🧮 Sorting (Quicksort, Mergesort)

---

## 🔹 2. Linked Lists

**Implementation**

* 🟦 Singly Linked List (SLL) — insert at head/tail/pos, delete, search
* 🟩 Doubly Linked List (DLL) — insert at head/tail/pos, delete, search
* 🟨 Circular Linked List — tail → head maintenance, insert/delete by pos

**Classical Problems**

* 🔁 Reverse linked list — iterative & recursive
* 🔍 Detect cycle (Floyd’s tortoise & hare)
* 🔗 Merge two sorted lists (in-place)
* 🔢 Remove nth node from end (two-pointer)
* 🎯 Find middle node (fast/slow)
* 🗂️ LRU Cache (DLL + hashmap)

**Algorithms / Concepts**

* 🐢🐇 Fast & slow pointers (cycle detection, middle node)
* 🔀 Merge sort on linked list (O(n log n), no extra arrays)

---

## 🔹 3. Stacks

**Implementation**

* 📚 Array-based stack (fixed-capacity)
* 🔗 Linked list stack (dynamic)

**Classical Problems**

* ✅ Balanced parentheses / bracket matching
* 🔼 Next greater element (monotonic stack)
* 🧮 MinStack — O(1) getMin()
* 🧾 Evaluate postfix & prefix expressions
* 🏗️ Largest rectangle in histogram

**Algorithms / Concepts**

* 🧰 Monotonic stack patterns (next/previous smaller/greater)
* ✍️ Infix → Postfix conversion (Shunting-Yard algorithm)

---

## 🔹 4. Queues

**Implementation**

* 🔁 Array queue (circular/ring buffer)
* 🔗 Linked list queue (front/tail pointers)
* ↔️ Deque (double-ended queue) — push/pop both ends

**Classical Problems**

* 🔁 Implement stack using queues
* ⚖️ Implement queue using stacks
* 🪟 Sliding window maximum (deque trick)
* 🧪 Rotten Oranges (BFS on grid)
* 🔡 First non-repeating character in a stream

**Algorithms / Concepts**

* 🌐 BFS (graph / grid traversal)
* 🔍 Sliding window (two-pointer / deque patterns)

---

## 🔹 5. Heaps (Priority Queue)

**Implementation**

* ⬆️ Max-heap & ⬇️ Min-heap (array-backed binary heap)
* ⚙️ Heapify, push (insert), pop (extract)

**Classical Problems**

* 🧹 Heap sort (in-place)
* \#️⃣ K-th largest / smallest element
* 🔀 Merge k sorted arrays / lists
* 🔝 Top K frequent elements
* 🧮 Median of data stream (two-heap trick)

**Algorithms / Concepts**

* 🛠️ Heapify in O(n) (bottom-up build)
* 🗓️ Priority scheduling & task queues

---

## 🔹 6. Binary Trees

**Implementation**

* 🌳 Basic TreeNode structure (left/right child)
* 🔁 Recursive & iterative traversals (inorder, preorder, postorder)

**Classical Problems**

* 🔁 Inorder / Preorder / Postorder / Level-order traversals
* 📏 Height / Depth of a tree
* 🌉 Diameter of tree
* 🧭 Lowest Common Ancestor (LCA)
* ➕ Path sum problems (root→leaf sums, k-sum paths)
* 🔄 Serialize & Deserialize tree (string / vector)

**Algorithms / Concepts**

* 🔍 DFS (recursive & iterative)
* 🌐 BFS (level-order with queue)
* 🔁 Recursion + backtracking patterns

---

## 🔹 7. Binary Search Trees (BST)

**Implementation**

* 🌿 BST insert, search, delete
* 🔁 BST traversals (inorder = sorted order)

**Classical Problems**

* ✅ Validate BST
* \#️⃣ K-th smallest / largest element
* 🧭 LCA in BST (ordered property)
* 🔁 Sorted array → balanced BST
* 〈Floor & Ceil〉 operations in BST

**Algorithms / Concepts**

* 🔁 Inorder traversal yields sorted list
* ⚖️ Self-balancing trees (AVL, Red-Black) — advanced topics

---

## 🔹 8. Graphs

**Implementation**

* 🗂️ Adjacency list & adjacency matrix
* ↔️ Directed / Undirected graphs
* ⚖️ Weighted / Unweighted graphs

**Classical Problems**

* 🔎 DFS & BFS traversals
* 🔁 Cycle detection (directed/undirected)
* 📜 Topological sort (DFS & Kahn’s)
* 🧭 Shortest paths: Dijkstra, Bellman-Ford
* 🌲 Minimum Spanning Tree: Kruskal, Prim
* 🧩 Connected components (Union-Find / DFS)
* ⚖️ Bipartite check
* 🌉 Bridges & articulation points (Tarjan’s)

**Algorithms / Concepts**

* 🧷 Disjoint Set Union (Union-Find)
* ⛳ Dijkstra, Bellman-Ford, Floyd-Warshall
* 🧰 Kruskal & Prim for MST
* 🔄 Tarjan’s SCC, Kosaraju’s SCC

---

## ✅ Goal

* 🔨 Implement all data structures from scratch (no STL shortcuts)
* 🧩 Solve their classical problems and edge cases
* 🧠 Master the algorithms built on top of each data structure
* 🧪 Write tests / drivers and clear README docs for each module
