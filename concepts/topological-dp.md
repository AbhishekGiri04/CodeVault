# Topological DP — Complete Professional <div align="center">Guide</div>

<div align="center">

![Topological DP](https://img.shields.io/badge/Topological_DP-DAG_Optimization-FF6B6B?style=for-the-badge&logo=databricks&logoColor=white)
![Difficulty](https://img.shields.io/badge/Difficulty-Advanced-4ECDC4?style=for-the-badge)
![Importance](https://img.shields.io/badge/Importance-Critical-darkred?style=for-the-badge)

**Master Dynamic Programming on Directed Acyclic Graphs**

</div>

---

## Table of Contents

1. [Introduction](#introduction)
2. [Core Concepts](#core-concepts)
3. [Algorithm Framework](#algorithm-framework)
4. [Common DP Types](#common-dp-types)
5. [Implementation Examples](#implementation-examples)
6. [Interview Problems](#interview-problems)
7. [Best Practices](#best-practices)

---

## Introduction

**Topological DP** is a powerful technique that combines Dynamic Programming with Directed Acyclic Graphs (DAGs) using Topological Sorting to ensure optimal substructure and dependency resolution. This approach is essential for solving complex optimization problems on graphs.

<div align="center">
<img src="https://camo.githubusercontent.com/86574a9fe26ea0d2ba98a0b637db0aaabaf734c0f9f4cc050593035ed53d054a/68747470733a2f2f6d656469612e6765656b73666f726765656b732e6f72672f77702d636f6e74656e742f75706c6f6164732f32303233313031363131333532342f6578616d706c652e706e67" alt="Topological DP Example" width="650" height="400"/>
</div>

### Core Concept

```mermaid
flowchart TD
    A["📌 Topological DP"] --> B["DAG Structure"]
    A --> C["Topological Order"]
    A --> D["DP State Definition"]
    A --> E["Dependency Resolution"]
    
    B --> F["Directed edges"]
    B --> G["No cycles"]
    B --> H["Finite vertices"]
    
    C --> I["Process dependencies first"]
    C --> J["Kahn's algorithm"]
    C --> K["DFS-based sorting"]
    
    D --> L["State at each node"]
    D --> M["Base cases"]
    D --> N["Transition function"]
    
    E --> O["Correct processing order"]
    E --> P["Optimal substructure"]
    E --> Q["Memoization benefits"]
    
    classDef default fill:#f9f9f9,stroke:#333,stroke-width:2px,color:#000
    classDef topodp fill:#e3f2fd,stroke:#2196f3,stroke-width:2px,color:#000
    classDef structure fill:#fff3e0,stroke:#ff9800,stroke-width:2px,color:#000
    classDef order fill:#e8f5e8,stroke:#4caf50,stroke-width:2px,color:#000
    classDef state fill:#f3e5f5,stroke:#9c27b0,stroke-width:2px,color:#000
    classDef dependency fill:#ffebee,stroke:#f44336,stroke-width:2px,color:#000
    class A topodp
    class B,F,G,H structure
    class C,I,J,K order
    class D,L,M,N state
    class E,O,P,Q dependency
```

---

## Core Concepts

### Algorithm Requirements

<div align="center">
<img src="https://camo.githubusercontent.com/c8b5f3e72448e3f22e8b1f2b69849678283ea6ec9ca565761aa1092d51375833/68747470733a2f2f6d656469612e6765656b73666f726765656b732e6f72672f77702d636f6e74656e742f75706c6f6164732f73686f72746573747061746873746172742e6a7067" alt="Shortest Path in DAG" width="650" height="400"/>
</div>

### Essential Requirements

```mermaid
flowchart TD
    A["Topological DP Requirements"] --> B["DAG Structure"]
    A --> C["Dependency Order"]
    A --> D["State Definition"]
    A --> E["Transition Function"]
    
    B --> F["Directed graph"]
    B --> G["Acyclic property"]
    B --> H["Finite vertices"]
    
    C --> I["Process prerequisites first"]
    C --> J["Topological ordering"]
    C --> K["Dependency resolution"]
    
    D --> L["dp[node] = optimal value"]
    D --> M["Base cases defined"]
    D --> N["State space bounded"]
    
    E --> O["dp[v] = f(dp[u], edge)"]
    E --> P["Relaxation updates"]
    E --> Q["Optimal substructure"]
    
    classDef default fill:#f9f9f9,stroke:#333,stroke-width:2px,color:#000
    classDef requirements fill:#e3f2fd,stroke:#2196f3,stroke-width:2px,color:#000
    classDef structure fill:#fff3e0,stroke:#ff9800,stroke-width:2px,color:#000
    classDef order fill:#e8f5e8,stroke:#4caf50,stroke-width:2px,color:#000
    classDef state fill:#f3e5f5,stroke:#9c27b0,stroke-width:2px,color:#000
    classDef transition fill:#ffebee,stroke:#f44336,stroke-width:2px,color:#000
    class A requirements
    class B,F,G,H structure
    class C,I,J,K order
    class D,L,M,N state
    class E,O,P,Q transition
```

### Core Algorithm Template

```cpp
class TopologicalDP {
public:
    vector<int> topologicalSort(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<int> indegree(n, 0);
        
        for (int u = 0; u < n; u++) {
            for (int v : graph[u]) {
                indegree[v]++;
            }
        }
        
        queue<int> q;
        for (int i = 0; i < n; i++) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }
        
        vector<int> topoOrder;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            topoOrder.push_back(u);
            
            for (int v : graph[u]) {
                indegree[v]--;
                if (indegree[v] == 0) {
                    q.push(v);
                }
            }
        }
        
        return topoOrder.size() == n ? topoOrder : vector<int>();
    }
};
```

---

## Algorithm Framework

### Topological Sorting Applications

<div align="center">
<img src="https://camo.githubusercontent.com/0ca87d9de119ecef215d9bb25ae7c80dae4aca9180a1e248c6e0b5899de2a709/68747470733a2f2f7363616c65722e636f6d2f746f706963732f696d616765732f70726163746963652d70726f626c656d2d62617365642d6f6e2d746f706f6c6f676963616c2d736f72742d6164646974696f6e2d736576656e2e77656270" alt="Topological Sort Applications" width="650" height="400"/>
</div>

### Step-by-Step Process

```mermaid
flowchart TD
    A["Topological DP Algorithm"] --> B["Step 1: Validate DAG"]
    B --> C["Step 2: Topological Sort"]
    C --> D["Step 3: Initialize DP"]
    D --> E["Step 4: Process in Order"]
    E --> F["Step 5: Extract Result"]
    
    B --> G["Check for cycles"]
    G --> H["Verify directed edges"]
    
    C --> I["Kahn's Algorithm"]
    C --> J["DFS-based approach"]
    
    D --> K["Set base cases"]
    D --> L["Initialize states"]
    
    E --> M["For each node u"]
    M --> N["Update neighbors v"]
    N --> O["dp[v] = f(dp[u], edge)"]
    
    F --> P["Return optimal value"]
    
    classDef default fill:#f9f9f9,stroke:#333,stroke-width:2px,color:#000
    classDef algorithm fill:#e3f2fd,stroke:#2196f3,stroke-width:2px,color:#000
    classDef validate fill:#fff3e0,stroke:#ff9800,stroke-width:2px,color:#000
    classDef sort fill:#e8f5e8,stroke:#4caf50,stroke-width:2px,color:#000
    classDef process fill:#f3e5f5,stroke:#9c27b0,stroke-width:2px,color:#000
    classDef result fill:#ffebee,stroke:#f44336,stroke-width:2px,color:#000
    class A algorithm
    class B,G,H validate
    class C,I,J sort
    class D,E,K,L,M,N,O process
    class F,P result
```

---

## Common DP Types

### Problem Categories

```mermaid
flowchart TD
    A["Topological DP Types"] --> B["Path Problems"]
    A --> C["Counting Problems"]
    A --> D["Optimization Problems"]
    A --> E["Dependency Problems"]
    
    B --> F["Longest path in DAG"]
    B --> G["Shortest path in DAG"]
    B --> H["Path with constraints"]
    
    C --> I["Number of paths"]
    C --> J["Ways to reach target"]
    C --> K["Path counting variants"]
    
    D --> L["Maximum/minimum cost"]
    D --> M["Resource optimization"]
    D --> N["Weighted problems"]
    
    E --> O["Course scheduling"]
    E --> P["Task dependencies"]
    E --> Q["Build systems"]
    
    classDef default fill:#f9f9f9,stroke:#333,stroke-width:2px,color:#000
    classDef types fill:#e3f2fd,stroke:#2196f3,stroke-width:2px,color:#000
    classDef path fill:#fff3e0,stroke:#ff9800,stroke-width:2px,color:#000
    classDef counting fill:#e8f5e8,stroke:#4caf50,stroke-width:2px,color:#000
    classDef optimization fill:#f3e5f5,stroke:#9c27b0,stroke-width:2px,color:#000
    classDef dependency fill:#ffebee,stroke:#f44336,stroke-width:2px,color:#000
    class A types
    class B,F,G,H path
    class C,I,J,K counting
    class D,L,M,N optimization
    class E,O,P,Q dependency
```

---

## Implementation Examples

### Core Algorithms

```cpp
class TopologicalDPSolver {
public:
    // Longest path in DAG
    int longestPath(vector<vector<pair<int, int>>>& graph, int source) {
        int n = graph.size();
        vector<int> dp(n, INT_MIN);
        dp[source] = 0;
        
        vector<int> topoOrder = topologicalSort(graph);
        
        for (int u : topoOrder) {
            if (dp[u] != INT_MIN) {
                for (auto& edge : graph[u]) {
                    int v = edge.first;
                    int weight = edge.second;
                    dp[v] = max(dp[v], dp[u] + weight);
                }
            }
        }
        
        return *max_element(dp.begin(), dp.end());
    }
    
    // Count paths in DAG
    long long countPaths(vector<vector<int>>& graph, int source, int target) {
        int n = graph.size();
        vector<long long> dp(n, 0);
        dp[source] = 1;
        
        vector<int> topoOrder = topologicalSort(graph);
        
        for (int u : topoOrder) {
            for (int v : graph[u]) {
                dp[v] += dp[u];
            }
        }
        
        return dp[target];
    }
    
private:
    vector<int> topologicalSort(vector<vector<pair<int, int>>>& graph) {
        int n = graph.size();
        vector<int> indegree(n, 0);
        
        for (int u = 0; u < n; u++) {
            for (auto& edge : graph[u]) {
                indegree[edge.first]++;
            }
        }
        
        queue<int> q;
        for (int i = 0; i < n; i++) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }
        
        vector<int> topoOrder;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            topoOrder.push_back(u);
            
            for (auto& edge : graph[u]) {
                indegree[edge.first]--;
                if (indegree[edge.first] == 0) {
                    q.push(edge.first);
                }
            }
        }
        
        return topoOrder;
    }
};
```

---

## Interview Problems

### Common Problem Patterns

```cpp
class InterviewProblems {
public:
    // Course Schedule II
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> graph(numCourses);
        vector<int> indegree(numCourses, 0);
        
        for (auto& prereq : prerequisites) {
            graph[prereq[1]].push_back(prereq[0]);
            indegree[prereq[0]]++;
        }
        
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
            
            for (int next : graph[course]) {
                indegree[next]--;
                if (indegree[next] == 0) {
                    q.push(next);
                }
            }
        }
        
        return order.size() == numCourses ? order : vector<int>();
    }
    
    // Parallel Courses
    int minimumSemesters(int n, vector<vector<int>>& relations) {
        vector<vector<int>> graph(n + 1);
        vector<int> indegree(n + 1, 0);
        
        for (auto& relation : relations) {
            graph[relation[0]].push_back(relation[1]);
            indegree[relation[1]]++;
        }
        
        queue<int> q;
        for (int i = 1; i <= n; i++) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }
        
        int semesters = 0;
        int studied = 0;
        
        while (!q.empty()) {
            int size = q.size();
            semesters++;
            
            for (int i = 0; i < size; i++) {
                int course = q.front();
                q.pop();
                studied++;
                
                for (int next : graph[course]) {
                    indegree[next]--;
                    if (indegree[next] == 0) {
                        q.push(next);
                    }
                }
            }
        }
        
        return studied == n ? semesters : -1;
    }
};
```

---

## Best Practices

### Algorithm Selection Guidelines

```mermaid
flowchart TD
    A["Choose Topological DP Approach"] --> B{"Graph Properties?"}
    B -->|"Dense Graph"| C["Adjacency Matrix"]
    B -->|"Sparse Graph"| D["Adjacency List"]
    
    A --> E{"Problem Type?"}
    E -->|"Path Optimization"| F["Longest/Shortest Path DP"]
    E -->|"Counting"| G["Path Counting DP"]
    E -->|"Dependencies"| H["Topological Sort + DP"]
    
    A --> I{"Memory Constraints?"}
    I -->|"Limited"| J["Space-optimized DP"]
    I -->|"Abundant"| K["Standard DP"]
    
    classDef default fill:#f9f9f9,stroke:#333,stroke-width:2px,color:#000
    classDef selection fill:#e3f2fd,stroke:#2196f3,stroke-width:2px,color:#000
    classDef properties fill:#fff3e0,stroke:#ff9800,stroke-width:2px,color:#000
    classDef type fill:#e8f5e8,stroke:#4caf50,stroke-width:2px,color:#000
    classDef memory fill:#f3e5f5,stroke:#9c27b0,stroke-width:2px,color:#000
    class A selection
    class B,C,D properties
    class E,F,G,H type
    class I,J,K memory
```

### Common Pitfalls and Solutions

```cpp
class BestPractices {
public:
    // ✅ Always validate DAG
    bool isDAG(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<int> color(n, 0);
        
        function<bool(int)> dfs = [&](int u) {
            color[u] = 1;
            for (int v : graph[u]) {
                if (color[v] == 1) return false;
                if (color[v] == 0 && !dfs(v)) return false;
            }
            color[u] = 2;
            return true;
        };
        
        for (int i = 0; i < n; i++) {
            if (color[i] == 0 && !dfs(i)) {
                return false;
            }
        }
        return true;
    }
    
    // ✅ Handle unreachable nodes
    vector<int> robustDP(vector<vector<pair<int, int>>>& graph, int source) {
        int n = graph.size();
        vector<int> dp(n, INT_MIN);
        dp[source] = 0;
        
        vector<int> topoOrder = topologicalSort(graph);
        
        for (int u : topoOrder) {
            if (dp[u] != INT_MIN) {
                for (auto& edge : graph[u]) {
                    int v = edge.first;
                    int weight = edge.second;
                    dp[v] = max(dp[v], dp[u] + weight);
                }
            }
        }
        
        return dp;
    }
};
```

---

## Summary

**Topological DP** combines the power of dynamic programming with graph theory to solve complex optimization problems on DAGs. Key insights:

### Essential Concepts
- **DAG Requirement**: Directed Acyclic Graphs are mandatory for topological ordering
- **Dependency Resolution**: Topological sort ensures correct processing order
- **State Definition**: Clear DP state definition at each vertex
- **Optimal Substructure**: Problems must exhibit optimal substructure property

### Core Applications
- **Path Optimization**: Longest and shortest path problems in DAGs
- **Counting Problems**: Number of paths, ways to reach destinations
- **Scheduling**: Course scheduling, task dependencies, project planning
- **Resource Allocation**: Optimal resource distribution with dependencies

### Best Practices
- Always validate that the graph is a DAG before applying topological DP
- Choose appropriate topological sorting algorithm based on graph properties
- Handle unreachable nodes and edge cases properly
- Consider space optimization for large sparse graphs
- Use memoization when subproblems overlap

> **Master's Insight**: Topological DP transforms complex dependency problems into manageable sequential computations. The key is recognizing when dependencies form a DAG structure and leveraging topological ordering for optimal solution computation.

---

<div align="center">

**📌 Master Topological DP • Solve Dependency Problems • Optimize Graph Computations**

*From Theory to Practice • Dependencies to Solutions • Understanding to Mastery*

</div>