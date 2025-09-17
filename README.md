<h1>📘 <span style="color:#007acc">Data Structures & Algorithms – From Scratch</span></h1>

<p>This repository is a <b>from-scratch</b> implementation of fundamental data structures and their classical problems & algorithms.<br>
<i>Goal:</i> <span style="color:#2ecc40">mastery</span> — not just using STL/Java Collections/Python built-ins, but <b>building</b>, <b>understanding</b>, and <b>applying</b> them.</p>

<h2>📂 Table of Contents</h2>

<ul>
	<li>🟦 <b>Arrays</b></li>
	<li>🟩 <b>Linked Lists</b></li>
	<li>🟧 <b>Stacks</b></li>
	<li>🟨 <b>Queues</b></li>
	<li>🟪 <b>Heaps</b></li>
	<li>🌳 <b>Binary Trees</b></li>
	<li>🌲 <b>Binary Search Trees</b></li>
	<li>🕸️ <b>Graphs</b></li>
</ul>

<h3>🔹 1. Arrays</h3>

<b>Implementation:</b>
<ul>
	<li>Static & dynamic arrays</li>
	<li>Insert, delete, search, resize</li>
</ul>

<b>Classical Problems:</b>
<ul>
	<li>🔄 Reverse array</li>
	<li>🔁 Rotate array (k steps)</li>
	<li>❓ Find missing number (1..n)</li>
	<li>➕ Two Sum / Subarray sum</li>
	<li>💪 Kadane’s algorithm (max subarray sum)</li>
	<li>📊 Prefix sum problems</li>
</ul>

<b>Algorithms:</b>
<ul>
	<li>🪟 Sliding Window</li>
	<li>🔍 Binary Search (and variants: first/last occurrence, upper/lower bound)</li>
	<li>🧮 Sorting (Quicksort, Mergesort)</li>
</ul>

🔹 2. Linked Lists

Implementation

🟦 Singly Linked List (SLL) — insert at head/tail/pos, delete, search

🟩 Doubly Linked List (DLL) — insert at head/tail/pos, delete, search

🟨 Circular Linked List — tail → head maintenance, insert/delete by pos

Classical Problems

🔁 Reverse linked list — iterative & recursive

🔍 Detect cycle (Floyd’s tortoise & hare)

🔗 Merge two sorted lists (in-place)

🔢 Remove nth node from end (two-pointer)

🎯 Find middle node (fast/slow)

🗂️ LRU Cache (DLL + hashmap)

Algorithms / Concepts

🐢🐇 Fast & slow pointers (cycle detection, middle node)

🔀 Merge sort on linked list (O(n log n), no extra arrays)

🔹 3. Stacks

Implementation

📚 Array-based stack (fixed-capacity)

🔗 Linked list stack (dynamic)

Classical Problems

✅ Balanced parentheses / bracket matching

🔼 Next greater element (stack / monotonic stack)

🧮 MinStack — O(1) getMin()

🧾 Evaluate postfix & prefix expressions

🏗️ Largest rectangle in histogram (monotonic stack)

Algorithms / Concepts

🧰 Monotonic stack patterns (next/previous smaller/greater)

✍️ Infix → Postfix conversion (Shunting-Yard algorithm)

🔹 4. Queues

Implementation

🔁 Array queue (circular/ring buffer)

🔗 Linked list queue (front/tail pointers)

↔️ Deque (double-ended queue) — push/pop both ends

Classical Problems

🔁 Implement stack using queues

⚖️ Implement queue using stacks

🪟 Sliding window maximum (deque trick)

🧪 Rotten Oranges (BFS on grid)

🔡 First non-repeating character in a stream

Algorithms / Concepts

🌐 BFS (graph / grid traversal)

🔍 Sliding window (two-pointer / deque patterns)

🔹 5. Heaps (Priority Queue)

Implementation

⬆️ Max-heap & ⬇️ Min-heap (array-backed binary heap)

⚙️ Heapify, push (insert), pop (extract)

Classical Problems

🧹 Heap sort (in-place)

#️⃣ K-th largest / smallest element

🔀 Merge k sorted arrays / lists (use heap)

🔝 Top K frequent elements

🧮 Median of data stream (two-heap trick)

Algorithms / Concepts

🛠️ heapify in O(n) (bottom-up build)

🗓️ Priority scheduling & task queues

🔹 6. Binary Trees

Implementation

🌳 Basic TreeNode structure (left/right child)

🔁 Recursive & iterative traversals (inorder, preorder, postorder)

Classical Problems

🔁 Inorder / Preorder / Postorder / Level-order traversals

📏 Height / Depth of a tree

🌉 Diameter of tree

🧭 Lowest Common Ancestor (LCA) — recursive and binary-lifting (optional)

➕ Path sum problems (root→leaf sums, k-sum paths)

🔄 Serialize & Deserialize tree (string / vector forms)

Algorithms / Concepts

🔍 DFS (recursive & iterative with stack)

🌐 BFS (level-order using queue)

🔁 Recursion + backtracking patterns

🔹 7. Binary Search Trees (BST)

Implementation

🌿 BST insert, search, delete

🔁 BST traversals (inorder = sorted order)

Classical Problems

✅ Validate BST

#️⃣ K-th smallest / largest element (inorder traversal)

🧭 LCA in BST (use ordering property)

🔁 Convert sorted array → balanced BST (divide & conquer)

〈Floor & Ceil〉 operations in BST

Algorithms / Concepts

🔁 Inorder traversal yields sorted list

⚖️ Self-balancing trees (AVL, Red-Black) — advanced topics

🔹 8. Graphs

Implementation

🗂️ Adjacency list & adjacency matrix representations

↔️ Directed / Undirected graphs

⚖️ Weighted / Unweighted graphs

Classical Problems

🔎 DFS & BFS traversals

🔁 Cycle detection (directed via DFS colors; undirected via parent check)

📜 Topological sort (DFS & Kahn’s algorithm)

🧭 Shortest paths: Dijkstra, Bellman-Ford

🌲 Minimum Spanning Tree: Kruskal, Prim

🧩 Connected components (Union-Find / DFS)

⚖️ Bipartite check

🌉 Bridges & articulation points (Tarjan’s algorithm)

Algorithms / Concepts

🧷 Disjoint Set Union (Union-Find)

⛳ Dijkstra, Bellman-Ford, Floyd-Warshall

🧰 Kruskal & Prim for MST

🔄 Tarjan’s SCC, Kosaraju’s SCC

✅ Goal

🔨 Implement all data structures from scratch (no STL shortcuts)

🧩 Solve their classical problems and edge cases

🧠 Master the algorithms built on top of each data structure

🧪 Write tests / drivers and clear README docs for each module