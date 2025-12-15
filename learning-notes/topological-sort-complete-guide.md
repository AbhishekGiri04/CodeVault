# 🔄 Topological Sort — Complete Professional Guide

<div align="center">

![Topological Sort](https://img.shields.io/badge/Topological_Sort-Graph_Ordering-4ECDC4?style=for-the-badge&logo=sort&logoColor=white)
![Difficulty](https://img.shields.io/badge/Difficulty-Intermediate-yellow?style=for-the-badge)
![Importance](https://img.shields.io/badge/Importance-High-red?style=for-the-badge)

*Master dependency resolution and task scheduling through linear ordering of directed acyclic graphs*

</div>

---

## 📑 Table of Contents

1. [Introduction](#-introduction)
2. [Prerequisites & Properties](#-prerequisites--properties)
3. [Kahn's Algorithm (BFS)](#-kahns-algorithm-bfs)
4. [DFS-Based Approach](#-dfs-based-approach)
5. [Cycle Detection](#-cycle-detection)
6. [Algorithm Comparison](#-algorithm-comparison)
7. [Applications](#-applications)
8. [Advanced Topics](#-advanced-topics)
9. [Interview Problems](#-interview-problems)
10. [Complexity Analysis](#-complexity-analysis)
11. [Implementation Variations](#-implementation-variations)
12. [Best Practices](#-best-practices)

---

## 🎯 Introduction

**Topological Sort** is a linear ordering of vertices in a Directed Acyclic Graph (DAG) such that for every directed edge u → v, vertex u appears before vertex v in the ordering.

### 🔑 Key Concept

```
For edge u → v:
u must come before v in topological order

Example:
If A depends on B, then B appears before A in the sorted order
```

### 💡 Real-World Analogy

Think of it as **dependency resolution**:
- **Course Prerequisites**: Take Math before Physics
- **Build Systems**: Compile dependencies before main program
- **Task Scheduling**: Complete prerequisite tasks first

---

## 📋 Prerequisites & Properties

### ✅ Requirements

1. **Directed Graph**: Edges have direction
2. **Acyclic**: No cycles allowed (DAG)
3. **Finite**: Graph must be finite

### 🎯 Properties

```
✓ Only exists for DAGs
✓ Multiple valid orderings possible
✓ Linear time complexity O(V + E)
✓ Essential for dependency problems
✗ Impossible if cycles exist
```

### 🚫 When Topological Sort is NOT Possible

```
Cycle Example:
A → B → C → A

No valid ordering exists because:
- A must come before B
- B must come before C  
- C must come before A
- Contradiction!
```

---

## 🔄 Kahn's Algorithm (BFS)

### 🎯 Core Idea

**Process nodes with zero incoming edges first**, then remove them and update dependencies.

### 📊 Algorithm Steps

1. **Calculate in-degrees** of all vertices
2. **Enqueue vertices** with in-degree = 0
3. **Process queue**: Remove vertex, add to result
4. **Update neighbors**: Decrease their in-degrees
5. **Repeat** until queue is empty

### 💻 Implementation

```cpp
vector<int> topologicalSort(int V, vector<vector<int>>& adj) {
    // Step 1: Calculate in-degrees
    vector<int> indegree(V, 0);
    for (int u = 0; u < V; u++) {
        for (int v : adj[u]) {
            indegree[v]++;
        }
    }
    
    // Step 2: Initialize queue with zero in-degree vertices
    queue<int> q;
    for (int i = 0; i < V; i++) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }
    
    // Step 3: Process vertices
    vector<int> topoOrder;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        topoOrder.push_back(u);
        
        // Step 4: Update neighbors
        for (int v : adj[u]) {
            indegree[v]--;
            if (indegree[v] == 0) {
                q.push(v);
            }
        }
    }
    
    return topoOrder;
}
```

### 🔍 Step-by-Step Example

```
Graph: 0→1, 0→2, 1→3, 2→3

Step 1: Calculate in-degrees
indegree = [0, 1, 1, 2]

Step 2: Queue vertices with in-degree 0
queue = [0]

Step 3: Process 0
- Add 0 to result: [0]
- Update neighbors: indegree[1]=0, indegree[2]=0
- queue = [1, 2]

Step 4: Process 1
- Add 1 to result: [0, 1]  
- Update neighbors: indegree[3]=1
- queue = [2]

Step 5: Process 2
- Add 2 to result: [0, 1, 2]
- Update neighbors: indegree[3]=0
- queue = [3]

Step 6: Process 3
- Add 3 to result: [0, 1, 2, 3]
- queue = []

Result: [0, 1, 2, 3]
```

---

## 🌳 DFS-Based Approach

### 🎯 Core Idea

**Use DFS and add vertices to result in reverse order of completion**.

### 📊 Algorithm Steps

1. **Perform DFS** on all unvisited vertices
2. **After visiting all neighbors**, add vertex to stack
3. **Pop from stack** to get topological order

### 💻 Implementation

```cpp
class TopologicalSortDFS {
private:
    void dfs(int u, vector<vector<int>>& adj, vector<bool>& visited, stack<int>& topoStack) {
        visited[u] = true;
        
        // Visit all neighbors first
        for (int v : adj[u]) {
            if (!visited[v]) {
                dfs(v, adj, visited, topoStack);
            }
        }
        
        // Add to stack after visiting all neighbors
        topoStack.push(u);
    }
    
public:
    vector<int> topologicalSort(int V, vector<vector<int>>& adj) {
        vector<bool> visited(V, false);
        stack<int> topoStack;
        
        // Perform DFS on all unvisited vertices
        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                dfs(i, adj, visited, topoStack);
            }
        }
        
        // Pop from stack to get topological order
        vector<int> result;
        while (!topoStack.empty()) {
            result.push_back(topoStack.top());
            topoStack.pop();
        }
        
        return result;
    }
};
```

### 🔍 DFS Execution Trace

```
Graph: 0→1, 0→2, 1→3, 2→3

DFS(0):
  DFS(1):
    DFS(3): stack = [3]
  stack = [3, 1]
  DFS(2):
    3 already visited
  stack = [3, 1, 2]
stack = [3, 1, 2, 0]

Pop stack: [0, 2, 1, 3]
```

---

## 🔍 Cycle Detection

### 🎯 Using Kahn's Algorithm

```cpp
bool hasCycle(int V, vector<vector<int>>& adj) {
    vector<int> topoOrder = topologicalSort(V, adj);
    return topoOrder.size() != V;  // If size < V, cycle exists
}
```

### 🎯 Using DFS (Three Colors)

```cpp
class CycleDetection {
private:
    enum Color { WHITE, GRAY, BLACK };
    
    bool dfs(int u, vector<vector<int>>& adj, vector<Color>& color) {
        color[u] = GRAY;  // Currently processing
        
        for (int v : adj[u]) {
            if (color[v] == GRAY) {
                return true;  // Back edge found - cycle detected
            }
            if (color[v] == WHITE && dfs(v, adj, color)) {
                return true;
            }
        }
        
        color[u] = BLACK;  // Finished processing
        return false;
    }
    
public:
    bool hasCycle(int V, vector<vector<int>>& adj) {
        vector<Color> color(V, WHITE);
        
        for (int i = 0; i < V; i++) {
            if (color[i] == WHITE) {
                if (dfs(i, adj, color)) {
                    return true;
                }
            }
        }
        return false;
    }
};
```

---

## 🆚 Algorithm Comparison

### 📊 Kahn's vs DFS Comparison

<table>
<thead>
<tr>
<th>Feature</th>
<th>Kahn's Algorithm (BFS)</th>
<th>DFS-Based</th>
</tr>
</thead>
<tbody>
<tr>
<td><strong>Approach</strong></td>
<td>In-degree based</td>
<td>Recursion based</td>
</tr>
<tr>
<td><strong>Data Structure</strong></td>
<td>Queue</td>
<td>Stack (implicit/explicit)</td>
</tr>
<tr>
<td><strong>Cycle Detection</strong></td>
<td>Easy (count vertices)</td>
<td>Requires color coding</td>
</tr>
<tr>
<td><strong>Space Complexity</strong></td>
<td>O(V)</td>
<td>O(V) + recursion stack</td>
</tr>
<tr>
<td><strong>Implementation</strong></td>
<td>Iterative</td>
<td>Recursive</td>
</tr>
<tr>
<td><strong>Preferred For</strong></td>
<td>Cycle detection, interviews</td>
<td>Simple implementation</td>
</tr>
</tbody>
</table>

### 🎯 When to Use Which?

```
Use Kahn's Algorithm when:
✓ Need cycle detection
✓ Want iterative solution
✓ Processing dependencies incrementally

Use DFS when:
✓ Simple implementation preferred
✓ Part of larger DFS traversal
✓ Memory constraints (no extra indegree array)
```

---

## 🎯 Applications

### 🌐 Real-World Applications

#### 1️⃣ Course Scheduling
```cpp
class CourseScheduler {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> adj(numCourses);
        vector<int> indegree(numCourses, 0);
        
        // Build graph
        for (auto& prereq : prerequisites) {
            adj[prereq[1]].push_back(prereq[0]);
            indegree[prereq[0]]++;
        }
        
        // Kahn's algorithm
        queue<int> q;
        for (int i = 0; i < numCourses; i++) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }
        
        vector<int> order;
        while (!q.empty()) {
            int course = q.front();
            q.pop();
            order.push_back(course);
            
            for (int next : adj[course]) {
                if (--indegree[next] == 0) {
                    q.push(next);
                }
            }
        }
        
        return order.size() == numCourses ? order : vector<int>();
    }
};
```

#### 2️⃣ Build System Dependencies
```cpp
class BuildSystem {
public:
    vector<string> getBuildOrder(vector<string>& projects, 
                                vector<pair<string, string>>& dependencies) {
        unordered_map<string, vector<string>> graph;
        unordered_map<string, int> indegree;
        
        // Initialize
        for (string& project : projects) {
            indegree[project] = 0;
        }
        
        // Build dependency graph
        for (auto& dep : dependencies) {
            graph[dep.first].push_back(dep.second);
            indegree[dep.second]++;
        }
        
        // Topological sort
        queue<string> q;
        for (auto& p : indegree) {
            if (p.second == 0) {
                q.push(p.first);
            }
        }
        
        vector<string> buildOrder;
        while (!q.empty()) {
            string current = q.front();
            q.pop();
            buildOrder.push_back(current);
            
            for (string& dependent : graph[current]) {
                if (--indegree[dependent] == 0) {
                    q.push(dependent);
                }
            }
        }
        
        return buildOrder.size() == projects.size() ? buildOrder : vector<string>();
    }
};
```

#### 3️⃣ Task Scheduling
```cpp
class TaskScheduler {
public:
    bool canFinish(int numTasks, vector<vector<int>>& dependencies) {
        vector<vector<int>> adj(numTasks);
        vector<int> indegree(numTasks, 0);
        
        for (auto& dep : dependencies) {
            adj[dep[1]].push_back(dep[0]);
            indegree[dep[0]]++;
        }
        
        queue<int> q;
        for (int i = 0; i < numTasks; i++) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }
        
        int completed = 0;
        while (!q.empty()) {
            int task = q.front();
            q.pop();
            completed++;
            
            for (int next : adj[task]) {
                if (--indegree[next] == 0) {
                    q.push(next);
                }
            }
        }
        
        return completed == numTasks;
    }
};
```

---

## 🎓 Advanced Topics

### 🔥 Topological Sort + Dynamic Programming

#### Longest Path in DAG
```cpp
int longestPath(int V, vector<vector<pair<int, int>>>& adj) {
    vector<int> topoOrder = topologicalSort(V, adj);
    vector<int> dist(V, INT_MIN);
    
    // Initialize source
    dist[topoOrder[0]] = 0;
    
    // Process vertices in topological order
    for (int u : topoOrder) {
        if (dist[u] != INT_MIN) {
            for (auto& edge : adj[u]) {
                int v = edge.first;
                int weight = edge.second;
                dist[v] = max(dist[v], dist[u] + weight);
            }
        }
    }
    
    return *max_element(dist.begin(), dist.end());
}
```

#### Counting Paths in DAG
```cpp
int countPaths(int V, vector<vector<int>>& adj, int source, int target) {
    vector<int> topoOrder = topologicalSort(V, adj);
    vector<int> pathCount(V, 0);
    pathCount[source] = 1;
    
    for (int u : topoOrder) {
        for (int v : adj[u]) {
            pathCount[v] += pathCount[u];
        }
    }
    
    return pathCount[target];
}
```

### 🎪 Lexicographically Smallest Topological Order

```cpp
vector<int> lexicographicallySmallest(int V, vector<vector<int>>& adj) {
    vector<int> indegree(V, 0);
    for (int u = 0; u < V; u++) {
        for (int v : adj[u]) {
            indegree[v]++;
        }
    }
    
    // Use min-heap instead of queue
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = 0; i < V; i++) {
        if (indegree[i] == 0) {
            pq.push(i);
        }
    }
    
    vector<int> result;
    while (!pq.empty()) {
        int u = pq.top();
        pq.pop();
        result.push_back(u);
        
        for (int v : adj[u]) {
            if (--indegree[v] == 0) {
                pq.push(v);
            }
        }
    }
    
    return result;
}
```

---

## 🏆 Interview Problems

### ✅ Common LeetCode Problems

1. **Course Schedule** (LeetCode 207)
2. **Course Schedule II** (LeetCode 210)
3. **Alien Dictionary** (LeetCode 269)
4. **Minimum Height Trees** (LeetCode 310)
5. **Parallel Courses** (LeetCode 1136)

### 🔥 Sample Problem: Alien Dictionary

```cpp
string alienOrder(vector<string>& words) {
    unordered_map<char, unordered_set<char>> graph;
    unordered_map<char, int> indegree;
    
    // Initialize indegree for all characters
    for (string& word : words) {
        for (char c : word) {
            indegree[c] = 0;
        }
    }
    
    // Build graph from adjacent words
    for (int i = 0; i < words.size() - 1; i++) {
        string word1 = words[i], word2 = words[i + 1];
        
        // Check for invalid case
        if (word1.length() > word2.length() && 
            word1.substr(0, word2.length()) == word2) {
            return "";
        }
        
        // Find first different character
        for (int j = 0; j < min(word1.length(), word2.length()); j++) {
            if (word1[j] != word2[j]) {
                if (graph[word1[j]].find(word2[j]) == graph[word1[j]].end()) {
                    graph[word1[j]].insert(word2[j]);
                    indegree[word2[j]]++;
                }
                break;
            }
        }
    }
    
    // Topological sort
    queue<char> q;
    for (auto& p : indegree) {
        if (p.second == 0) {
            q.push(p.first);
        }
    }
    
    string result;
    while (!q.empty()) {
        char c = q.front();
        q.pop();
        result += c;
        
        for (char next : graph[c]) {
            if (--indegree[next] == 0) {
                q.push(next);
            }
        }
    }
    
    return result.length() == indegree.size() ? result : "";
}
```

---

## ⏱️ Complexity Analysis

### Time Complexity

| Operation | Kahn's Algorithm | DFS-Based |
|:----------|:----------------|:----------|
| **Build Graph** | O(E) | O(E) |
| **Calculate In-degrees** | O(V + E) | - |
| **Traversal** | O(V + E) | O(V + E) |
| **Overall** | **O(V + E)** | **O(V + E)** |

### Space Complexity

| Component | Kahn's Algorithm | DFS-Based |
|:----------|:----------------|:----------|
| **Adjacency List** | O(V + E) | O(V + E) |
| **In-degree Array** | O(V) | - |
| **Queue/Stack** | O(V) | O(V) |
| **Recursion Stack** | - | O(V) |
| **Overall** | **O(V + E)** | **O(V + E)** |

---

## 🔄 Implementation Variations

### 🎯 Using Adjacency Matrix

```cpp
vector<int> topoSortMatrix(vector<vector<int>>& matrix) {
    int V = matrix.size();
    vector<int> indegree(V, 0);
    
    // Calculate in-degrees
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (matrix[i][j] == 1) {
                indegree[j]++;
            }
        }
    }
    
    queue<int> q;
    for (int i = 0; i < V; i++) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }
    
    vector<int> result;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        result.push_back(u);
        
        for (int v = 0; v < V; v++) {
            if (matrix[u][v] == 1) {
                if (--indegree[v] == 0) {
                    q.push(v);
                }
            }
        }
    }
    
    return result;
}
```

### 🎯 All Topological Orders

```cpp
void allTopologicalOrders(vector<vector<int>>& adj, vector<int>& indegree, 
                         vector<int>& current, vector<vector<int>>& result) {
    bool flag = false;
    
    for (int i = 0; i < adj.size(); i++) {
        if (indegree[i] == 0) {
            // Include this vertex
            current.push_back(i);
            
            // Reduce indegree of neighbors
            for (int neighbor : adj[i]) {
                indegree[neighbor]--;
            }
            
            indegree[i] = -1;  // Mark as visited
            
            allTopologicalOrders(adj, indegree, current, result);
            
            // Backtrack
            indegree[i] = 0;
            for (int neighbor : adj[i]) {
                indegree[neighbor]++;
            }
            current.pop_back();
            
            flag = true;
        }
    }
    
    if (!flag) {
        result.push_back(current);
    }
}
```

---

## 💎 Best Practices

### ✅ Implementation Guidelines

```
✓ Always check if graph is DAG before sorting
✓ Use Kahn's algorithm for cycle detection
✓ Handle disconnected components properly
✓ Consider lexicographical ordering when needed
✓ Validate input for self-loops and multiple edges
✓ Use appropriate data structures (queue vs priority_queue)
```

### 🔧 Common Pitfalls

```
✗ Forgetting to check for cycles
✗ Not handling disconnected components
✗ Using wrong data structure for specific requirements
✗ Incorrect in-degree calculation
✗ Not considering multiple valid orderings
```

### 🎯 Optimization Tips

```cpp
// Memory-efficient in-degree calculation
vector<int> calculateIndegree(int V, vector<vector<int>>& adj) {
    vector<int> indegree(V, 0);
    for (int u = 0; u < V; u++) {
        for (int v : adj[u]) {
            indegree[v]++;
        }
    }
    return indegree;
}

// Early termination for cycle detection
bool hasCycleEarly(int V, vector<vector<int>>& adj) {
    vector<int> indegree = calculateIndegree(V, adj);
    queue<int> q;
    
    for (int i = 0; i < V; i++) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }
    
    int processed = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        processed++;
        
        for (int v : adj[u]) {
            if (--indegree[v] == 0) {
                q.push(v);
            }
        }
    }
    
    return processed != V;
}
```

---

## 🎓 Key Takeaways

<div align="center">

### 🌟 Master These Concepts

</div>

```
1. 🔄 Topological Sort = Linear ordering respecting dependencies
2. 📊 Kahn's Algorithm = BFS with in-degree tracking
3. 🌳 DFS Approach = Recursion with post-order processing
4. 🔍 Cycle Detection = Essential for validation
5. 🎯 Applications = Course scheduling, build systems, task dependencies
6. ⚡ Complexity = O(V + E) time, O(V) space
7. 🎪 Variations = Lexicographical, all orders, longest paths
8. 💡 DAG Requirement = Only works on directed acyclic graphs
```

---

## 📚 Practice Resources

- **LeetCode**: Topological Sort tag problems
- **GeeksforGeeks**: Graph algorithms section
- **Codeforces**: Graph theory contests
- **InterviewBit**: Dependency resolution problems

---

## 🎯 Interview Tips

1. **Understand Requirements**: DAG vs general graph
2. **Choose Right Algorithm**: Kahn's for cycle detection, DFS for simplicity
3. **Handle Edge Cases**: Empty graph, single vertex, cycles
4. **Explain Applications**: Connect to real-world scenarios
5. **Analyze Complexity**: Always mention time and space complexity
6. **Code Cleanly**: Use meaningful variable names and comments

---

<div align="center">

### 🔥 One-Line Summary

**Topological Sort = Linear ordering of DAG vertices respecting dependency constraints, essential for scheduling and dependency resolution**

---

**💻 Master dependencies, master systems!**

*"In the world of dependencies, topological sort is the key to proper ordering and conflict resolution."*

</div>