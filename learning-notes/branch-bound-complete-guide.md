# 🌳 Branch & Bound Complete Guide

## 📋 Table of Contents
- [Introduction](#introduction)
- [Core Concepts](#core-concepts)
- [State Space Tree](#state-space-tree)
- [Types of Branch & Bound](#types-of-branch--bound)
- [Job Assignment Problem](#job-assignment-problem)
- [0/1 Knapsack Problem](#01-knapsack-problem)
- [Traveling Salesman Problem](#traveling-salesman-problem)
- [Branch & Bound vs Other Techniques](#branch--bound-vs-other-techniques)
- [Implementation Strategies](#implementation-strategies)
- [Interview Problems](#interview-problems)
- [Best Practices](#best-practices)

---

## 🎯 Introduction

**Branch & Bound** is a systematic optimization technique that intelligently explores the solution space by dividing problems into subproblems (branching) and using bounds to eliminate non-promising solutions (pruning).

### 🔑 Key Principles
- **Systematic Exploration**: Divide problem into manageable subproblems
- **Intelligent Pruning**: Eliminate branches that cannot lead to optimal solutions
- **Bound Calculation**: Use upper/lower bounds to guide search
- **Optimization Focus**: Find the best solution, not just any solution

### 🌟 Applications
- **Job Assignment**: Minimize total assignment cost
- **Knapsack Problems**: Maximize profit with weight constraints
- **Traveling Salesman**: Find shortest tour
- **Integer Programming**: Solve discrete optimization problems

---

## 🧩 Core Concepts

### 🌳 Branching
Divide the problem into smaller subproblems by making decisions.

```cpp
class BranchingStrategy {
public:
    // Generic branching for binary decisions
    struct Node {
        vector<int> solution;
        int level;
        double bound;
        double cost;
        bool isComplete;
    };
    
    vector<Node> branch(Node& parent, int decision_point) {
        vector<Node> children;
        
        // Create child nodes based on decision
        for (int choice = 0; choice < getChoiceCount(decision_point); choice++) {
            Node child = parent;
            child.solution[decision_point] = choice;
            child.level = parent.level + 1;
            child.isComplete = (child.level == getTotalDecisions());
            
            children.push_back(child);
        }
        
        return children;
    }
    
private:
    virtual int getChoiceCount(int decision_point) = 0;
    virtual int getTotalDecisions() = 0;
};
```

### 🎯 Bounding
Calculate upper/lower bounds to estimate the best possible solution from a node.

```cpp
class BoundingFunction {
public:
    // Generic bounding interface
    virtual double calculateBound(const Node& node) = 0;
    virtual bool shouldPrune(const Node& node, double bestSolution) = 0;
    
protected:
    // Common bounding utilities
    double linearRelaxation(vector<double>& coefficients, vector<double>& constraints) {
        // Solve linear relaxation for upper bound
        double bound = 0.0;
        // Implementation depends on specific problem
        return bound;
    }
    
    double greedyHeuristic(const Node& node) {
        // Quick greedy solution for lower bound
        double heuristic = 0.0;
        // Problem-specific greedy approach
        return heuristic;
    }
};
```

### ✂️ Pruning
Eliminate branches that cannot lead to better solutions.

```cpp
class PruningStrategy {
public:
    bool shouldPrune(const Node& node, double bestKnown, bool isMinimization) {
        if (isMinimization) {
            return node.bound >= bestKnown; // Prune if bound ≥ best
        } else {
            return node.bound <= bestKnown; // Prune if bound ≤ best
        }
    }
    
    void updateBest(double& bestSolution, double candidate, bool isMinimization) {
        if (isMinimization) {
            bestSolution = min(bestSolution, candidate);
        } else {
            bestSolution = max(bestSolution, candidate);
        }
    }
};
```

---

## 🌲 State Space Tree

### 📊 Structure
```cpp
class StateSpaceTree {
public:
    struct TreeNode {
        int id;
        int level;              // Depth in tree
        vector<int> solution;   // Partial solution
        double cost;            // Current cost
        double bound;           // Estimated bound
        vector<TreeNode*> children;
        TreeNode* parent;
        
        TreeNode(int lvl, vector<int> sol) 
            : level(lvl), solution(sol), cost(0), bound(0), parent(nullptr) {}
    };
    
    TreeNode* root;
    int maxLevel;
    
    StateSpaceTree(int problemSize) : maxLevel(problemSize) {
        root = new TreeNode(0, vector<int>(problemSize, -1));
    }
    
    void buildTree() {
        queue<TreeNode*> q;
        q.push(root);
        
        while (!q.empty()) {
            TreeNode* current = q.front();
            q.pop();
            
            if (current->level < maxLevel) {
                vector<TreeNode*> children = generateChildren(current);
                current->children = children;
                
                for (TreeNode* child : children) {
                    child->parent = current;
                    q.push(child);
                }
            }
        }
    }
    
private:
    vector<TreeNode*> generateChildren(TreeNode* parent) {
        vector<TreeNode*> children;
        int nextLevel = parent->level + 1;
        
        // Generate all possible choices at this level
        for (int choice = 0; choice < getChoicesAtLevel(nextLevel); choice++) {
            vector<int> newSolution = parent->solution;
            newSolution[parent->level] = choice;
            
            TreeNode* child = new TreeNode(nextLevel, newSolution);
            children.push_back(child);
        }
        
        return children;
    }
    
    virtual int getChoicesAtLevel(int level) = 0;
};
```

---

## 🔄 Types of Branch & Bound

### 🟢 LC Branch & Bound (Least Cost)
**Best-First Search using priority queue**

```cpp
class LCBranchAndBound {
private:
    struct Node {
        vector<int> solution;
        int level;
        double cost;
        double bound;
        
        bool operator>(const Node& other) const {
            return bound > other.bound; // Min-heap for minimization
        }
    };
    
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    
public:
    pair<vector<int>, double> solve(Problem& problem) {
        Node root;
        root.solution = vector<int>(problem.size(), -1);
        root.level = 0;
        root.cost = 0;
        root.bound = calculateBound(root, problem);
        
        pq.push(root);
        
        vector<int> bestSolution;
        double bestCost = DBL_MAX;
        
        while (!pq.empty()) {
            Node current = pq.top();
            pq.pop();
            
            // Prune if bound is worse than best known
            if (current.bound >= bestCost) continue;
            
            if (current.level == problem.size()) {
                // Complete solution found
                if (current.cost < bestCost) {
                    bestCost = current.cost;
                    bestSolution = current.solution;
                }
                continue;
            }
            
            // Branch: generate children
            vector<Node> children = generateChildren(current, problem);
            for (Node& child : children) {
                if (child.bound < bestCost) {
                    pq.push(child);
                }
            }
        }
        
        return {bestSolution, bestCost};
    }
    
private:
    virtual double calculateBound(const Node& node, const Problem& problem) = 0;
    virtual vector<Node> generateChildren(const Node& parent, const Problem& problem) = 0;
};
```

### 🔵 FIFO Branch & Bound
**Breadth-First Search using queue**

```cpp
class FIFOBranchAndBound {
private:
    struct Node {
        vector<int> solution;
        int level;
        double cost;
        double bound;
    };
    
    queue<Node> q;
    
public:
    pair<vector<int>, double> solve(Problem& problem) {
        Node root;
        root.solution = vector<int>(problem.size(), -1);
        root.level = 0;
        root.cost = 0;
        root.bound = calculateBound(root, problem);
        
        q.push(root);
        
        vector<int> bestSolution;
        double bestCost = DBL_MAX;
        
        while (!q.empty()) {
            Node current = q.front();
            q.pop();
            
            // Prune if bound is worse than best known
            if (current.bound >= bestCost) continue;
            
            if (current.level == problem.size()) {
                // Complete solution found
                if (current.cost < bestCost) {
                    bestCost = current.cost;
                    bestSolution = current.solution;
                }
                continue;
            }
            
            // Branch: generate children level by level
            vector<Node> children = generateChildren(current, problem);
            for (Node& child : children) {
                if (child.bound < bestCost) {
                    q.push(child);
                }
            }
        }
        
        return {bestSolution, bestCost};
    }
    
private:
    virtual double calculateBound(const Node& node, const Problem& problem) = 0;
    virtual vector<Node> generateChildren(const Node& parent, const Problem& problem) = 0;
};
```

### 📊 Comparison: LC vs FIFO

```cpp
class BranchBoundComparison {
public:
    void compareStrategies() {
        cout << "LC Branch & Bound vs FIFO Branch & Bound:" << endl;
        cout << "===========================================" << endl;
        
        cout << "Node Selection:" << endl;
        cout << "  LC: Least cost (most promising) first" << endl;
        cout << "  FIFO: First-in-first-out order" << endl;
        
        cout << "Data Structure:" << endl;
        cout << "  LC: Priority Queue (Min-Heap)" << endl;
        cout << "  FIFO: Simple Queue" << endl;
        
        cout << "Search Strategy:" << endl;
        cout << "  LC: Best-First Search" << endl;
        cout << "  FIFO: Breadth-First Search" << endl;
        
        cout << "Efficiency:" << endl;
        cout << "  LC: Higher (explores fewer nodes)" << endl;
        cout << "  FIFO: Lower (explores more nodes)" << endl;
        
        cout << "Memory Usage:" << endl;
        cout << "  LC: Higher (priority queue overhead)" << endl;
        cout << "  FIFO: Lower (simple queue)" << endl;
    }
};
```

---

## 💼 Job Assignment Problem

### 📝 Problem Statement
Assign n jobs to n workers to minimize total cost, with each job assigned to exactly one worker.

```cpp
class JobAssignmentBB : public LCBranchAndBound {
private:
    struct JobNode {
        vector<int> assignment; // assignment[i] = worker assigned to job i
        vector<bool> workerUsed;
        int level;
        double cost;
        double bound;
        
        bool operator>(const JobNode& other) const {
            return bound > other.bound;
        }
    };
    
    vector<vector<int>> costMatrix;
    int n;
    
public:
    JobAssignmentBB(vector<vector<int>>& costs) : costMatrix(costs), n(costs.size()) {}
    
    pair<vector<int>, int> solveJobAssignment() {
        priority_queue<JobNode, vector<JobNode>, greater<JobNode>> pq;
        
        // Initialize root node
        JobNode root;
        root.assignment = vector<int>(n, -1);
        root.workerUsed = vector<bool>(n, false);
        root.level = 0;
        root.cost = 0;
        root.bound = calculateJobBound(root);
        
        pq.push(root);
        
        vector<int> bestAssignment;
        int bestCost = INT_MAX;
        
        while (!pq.empty()) {
            JobNode current = pq.top();
            pq.pop();
            
            // Prune if bound is worse than best known
            if (current.bound >= bestCost) continue;
            
            if (current.level == n) {
                // Complete assignment found
                if (current.cost < bestCost) {
                    bestCost = current.cost;
                    bestAssignment = current.assignment;
                }
                continue;
            }
            
            // Branch: try assigning current job to each available worker
            for (int worker = 0; worker < n; worker++) {
                if (!current.workerUsed[worker]) {
                    JobNode child = current;
                    child.assignment[current.level] = worker;
                    child.workerUsed[worker] = true;
                    child.level = current.level + 1;
                    child.cost = current.cost + costMatrix[current.level][worker];
                    child.bound = calculateJobBound(child);
                    
                    if (child.bound < bestCost) {
                        pq.push(child);
                    }
                }
            }
        }
        
        return {bestAssignment, bestCost};
    }
    
private:
    double calculateJobBound(const JobNode& node) {
        double bound = node.cost;
        
        // Add minimum cost for remaining jobs
        for (int job = node.level; job < n; job++) {
            int minCost = INT_MAX;
            for (int worker = 0; worker < n; worker++) {
                if (!node.workerUsed[worker]) {
                    minCost = min(minCost, costMatrix[job][worker]);
                }
            }
            bound += minCost;
        }
        
        return bound;
    }
};

// Usage Example
void solveJobAssignmentExample() {
    vector<vector<int>> costs = {
        {9, 2, 7, 8},
        {6, 4, 3, 7},
        {5, 8, 1, 8},
        {7, 6, 9, 4}
    };
    
    JobAssignmentBB solver(costs);
    auto [assignment, totalCost] = solver.solveJobAssignment();
    
    cout << "Optimal Assignment:" << endl;
    for (int job = 0; job < assignment.size(); job++) {
        cout << "Job " << job << " -> Worker " << assignment[job] 
             << " (Cost: " << costs[job][assignment[job]] << ")" << endl;
    }
    cout << "Total Cost: " << totalCost << endl;
}
```

---

## 🎒 0/1 Knapsack Problem

### 📝 Problem Statement
Select items to maximize profit while staying within weight capacity, each item can be taken at most once.

```cpp
class KnapsackBB : public LCBranchAndBound {
private:
    struct KnapsackNode {
        vector<int> solution; // 1 if item included, 0 otherwise
        int level;
        int weight;
        int profit;
        double bound;
        
        bool operator<(const KnapsackNode& other) const {
            return bound < other.bound; // Max-heap for maximization
        }
    };
    
    struct Item {
        int weight, profit;
        double ratio;
        int index;
        
        bool operator>(const Item& other) const {
            return ratio > other.ratio;
        }
    };
    
    vector<Item> items;
    int capacity;
    int n;
    
public:
    KnapsackBB(vector<int>& weights, vector<int>& profits, int cap) 
        : capacity(cap), n(weights.size()) {
        
        items.resize(n);
        for (int i = 0; i < n; i++) {
            items[i] = {weights[i], profits[i], (double)profits[i]/weights[i], i};
        }
        
        // Sort by profit-to-weight ratio (greedy order)
        sort(items.begin(), items.end(), greater<Item>());
    }
    
    pair<vector<int>, int> solveKnapsack() {
        priority_queue<KnapsackNode> pq;
        
        // Initialize root node
        KnapsackNode root;
        root.solution = vector<int>(n, -1);
        root.level = 0;
        root.weight = 0;
        root.profit = 0;
        root.bound = calculateKnapsackBound(root);
        
        pq.push(root);
        
        vector<int> bestSolution(n, 0);
        int bestProfit = 0;
        
        while (!pq.empty()) {
            KnapsackNode current = pq.top();
            pq.pop();
            
            // Prune if bound is worse than best known
            if (current.bound <= bestProfit) continue;
            
            if (current.level == n) {
                // Complete solution found
                if (current.profit > bestProfit) {
                    bestProfit = current.profit;
                    for (int i = 0; i < n; i++) {
                        bestSolution[items[i].index] = current.solution[i];
                    }
                }
                continue;
            }
            
            // Branch 1: Include current item
            if (current.weight + items[current.level].weight <= capacity) {
                KnapsackNode include = current;
                include.solution[current.level] = 1;
                include.level = current.level + 1;
                include.weight = current.weight + items[current.level].weight;
                include.profit = current.profit + items[current.level].profit;
                include.bound = calculateKnapsackBound(include);
                
                if (include.bound > bestProfit) {
                    pq.push(include);
                }
            }
            
            // Branch 2: Exclude current item
            KnapsackNode exclude = current;
            exclude.solution[current.level] = 0;
            exclude.level = current.level + 1;
            exclude.bound = calculateKnapsackBound(exclude);
            
            if (exclude.bound > bestProfit) {
                pq.push(exclude);
            }
        }
        
        return {bestSolution, bestProfit};
    }
    
private:
    double calculateKnapsackBound(const KnapsackNode& node) {
        if (node.weight > capacity) return 0;
        
        double bound = node.profit;
        int remainingCapacity = capacity - node.weight;
        
        // Add fractional items greedily
        for (int i = node.level; i < n && remainingCapacity > 0; i++) {
            if (items[i].weight <= remainingCapacity) {
                bound += items[i].profit;
                remainingCapacity -= items[i].weight;
            } else {
                // Take fraction of item
                bound += (double)items[i].profit * remainingCapacity / items[i].weight;
                break;
            }
        }
        
        return bound;
    }
};

// Usage Example
void solveKnapsackExample() {
    vector<int> weights = {10, 20, 30};
    vector<int> profits = {60, 100, 120};
    int capacity = 50;
    
    KnapsackBB solver(weights, profits, capacity);
    auto [solution, maxProfit] = solver.solveKnapsack();
    
    cout << "Optimal Knapsack Solution:" << endl;
    int totalWeight = 0;
    for (int i = 0; i < solution.size(); i++) {
        if (solution[i]) {
            cout << "Item " << i << " (Weight: " << weights[i] 
                 << ", Profit: " << profits[i] << ")" << endl;
            totalWeight += weights[i];
        }
    }
    cout << "Total Weight: " << totalWeight << endl;
    cout << "Total Profit: " << maxProfit << endl;
}
```

---

## 🚗 Traveling Salesman Problem

### 📝 TSP using Branch & Bound

```cpp
class TSPBB {
private:
    struct TSPNode {
        vector<int> path;
        vector<bool> visited;
        int level;
        int cost;
        double bound;
        
        bool operator>(const TSPNode& other) const {
            return bound > other.bound;
        }
    };
    
    vector<vector<int>> distMatrix;
    int n;
    
public:
    TSPBB(vector<vector<int>>& distances) : distMatrix(distances), n(distances.size()) {}
    
    pair<vector<int>, int> solveTSP() {
        priority_queue<TSPNode, vector<TSPNode>, greater<TSPNode>> pq;
        
        // Initialize root node (start from city 0)
        TSPNode root;
        root.path = {0};
        root.visited = vector<bool>(n, false);
        root.visited[0] = true;
        root.level = 1;
        root.cost = 0;
        root.bound = calculateTSPBound(root);
        
        pq.push(root);
        
        vector<int> bestTour;
        int bestCost = INT_MAX;
        
        while (!pq.empty()) {
            TSPNode current = pq.top();
            pq.pop();
            
            // Prune if bound is worse than best known
            if (current.bound >= bestCost) continue;
            
            if (current.level == n) {
                // Complete tour found, add return to start
                int totalCost = current.cost + distMatrix[current.path.back()][0];
                if (totalCost < bestCost) {
                    bestCost = totalCost;
                    bestTour = current.path;
                    bestTour.push_back(0); // Return to start
                }
                continue;
            }
            
            // Branch: visit each unvisited city
            for (int city = 0; city < n; city++) {
                if (!current.visited[city]) {
                    TSPNode child = current;
                    child.path.push_back(city);
                    child.visited[city] = true;
                    child.level = current.level + 1;
                    child.cost = current.cost + distMatrix[current.path.back()][city];
                    child.bound = calculateTSPBound(child);
                    
                    if (child.bound < bestCost) {
                        pq.push(child);
                    }
                }
            }
        }
        
        return {bestTour, bestCost};
    }
    
private:
    double calculateTSPBound(const TSPNode& node) {
        double bound = node.cost;
        
        // Add minimum outgoing edge from current city
        if (node.level < n) {
            int currentCity = node.path.back();
            int minEdge = INT_MAX;
            
            for (int city = 0; city < n; city++) {
                if (!node.visited[city]) {
                    minEdge = min(minEdge, distMatrix[currentCity][city]);
                }
            }
            
            if (minEdge != INT_MAX) {
                bound += minEdge;
            }
        }
        
        // Add minimum spanning tree of unvisited cities
        vector<int> unvisited;
        for (int i = 0; i < n; i++) {
            if (!node.visited[i]) {
                unvisited.push_back(i);
            }
        }
        
        if (unvisited.size() > 1) {
            bound += calculateMSTCost(unvisited);
        }
        
        // Add minimum edge back to start
        if (node.level == n - 1) {
            bound += distMatrix[node.path.back()][0];
        }
        
        return bound;
    }
    
    int calculateMSTCost(const vector<int>& cities) {
        if (cities.size() <= 1) return 0;
        
        vector<bool> inMST(cities.size(), false);
        vector<int> key(cities.size(), INT_MAX);
        
        key[0] = 0;
        int mstCost = 0;
        
        for (int count = 0; count < cities.size(); count++) {
            int u = -1;
            for (int v = 0; v < cities.size(); v++) {
                if (!inMST[v] && (u == -1 || key[v] < key[u])) {
                    u = v;
                }
            }
            
            inMST[u] = true;
            mstCost += key[u];
            
            for (int v = 0; v < cities.size(); v++) {
                if (!inMST[v]) {
                    key[v] = min(key[v], distMatrix[cities[u]][cities[v]]);
                }
            }
        }
        
        return mstCost;
    }
};
```

---

## ⚖️ Branch & Bound vs Other Techniques

### 🔄 Comparison Table

```cpp
class TechniqueComparison {
public:
    void compareOptimizationTechniques() {
        cout << "Optimization Technique Comparison:" << endl;
        cout << "=================================" << endl;
        
        cout << "Branch & Bound vs Backtracking:" << endl;
        cout << "  Goal: Optimization vs Feasibility" << endl;
        cout << "  Pruning: Bound-based vs Constraint-based" << endl;
        cout << "  Efficiency: Higher vs Lower" << endl;
        cout << "  Use Case: Best solution vs Any solution" << endl;
        
        cout << "Branch & Bound vs Dynamic Programming:" << endl;
        cout << "  Approach: Tree search vs Table filling" << endl;
        cout << "  Memory: Variable vs O(state space)" << endl;
        cout << "  Pruning: Explicit vs Implicit" << endl;
        cout << "  Optimal: Always vs Always (if applicable)" << endl;
        
        cout << "Branch & Bound vs Greedy:" << endl;
        cout << "  Optimality: Guaranteed vs Not guaranteed" << endl;
        cout << "  Complexity: Exponential vs Polynomial" << endl;
        cout << "  Exploration: Complete vs Local" << endl;
        cout << "  Use Case: Exact solution vs Approximation" << endl;
    }
};
```

### 📊 When to Use Each Technique

```cpp
class TechniqueSelector {
public:
    string selectTechnique(string problemType, int problemSize, bool needOptimal) {
        if (problemType == "optimization" && needOptimal) {
            if (problemSize <= 20) {
                return "Branch & Bound (exact solution feasible)";
            } else if (problemSize <= 1000) {
                return "Dynamic Programming (if applicable) or Approximation";
            } else {
                return "Heuristic or Metaheuristic algorithms";
            }
        } else if (problemType == "feasibility") {
            return "Backtracking with constraint propagation";
        } else if (!needOptimal) {
            return "Greedy algorithm or local search";
        }
        
        return "Analyze problem structure for best approach";
    }
};
```

---

## 🎯 Interview Problems

### Problem 1: Implement Basic Branch & Bound Framework
```cpp
class BasicBranchBound {
public:
    template<typename Problem, typename Solution>
    Solution solve(Problem& problem) {
        priority_queue<Node> pq;
        Node root = createRoot(problem);
        pq.push(root);
        
        Solution bestSolution;
        double bestValue = getWorstValue();
        
        while (!pq.empty()) {
            Node current = pq.top();
            pq.pop();
            
            if (shouldPrune(current, bestValue)) continue;
            
            if (isComplete(current)) {
                if (isBetter(current.value, bestValue)) {
                    bestValue = current.value;
                    bestSolution = extractSolution(current);
                }
                continue;
            }
            
            vector<Node> children = generateChildren(current, problem);
            for (Node& child : children) {
                if (!shouldPrune(child, bestValue)) {
                    pq.push(child);
                }
            }
        }
        
        return bestSolution;
    }
    
private:
    struct Node {
        vector<int> solution;
        int level;
        double value;
        double bound;
        
        bool operator<(const Node& other) const {
            return bound < other.bound; // Adjust for min/max
        }
    };
    
    virtual Node createRoot(const Problem& problem) = 0;
    virtual bool shouldPrune(const Node& node, double bestValue) = 0;
    virtual bool isComplete(const Node& node) = 0;
    virtual vector<Node> generateChildren(const Node& parent, const Problem& problem) = 0;
};
```

### Problem 2: N-Queens using Branch & Bound
```cpp
class NQueensBB {
private:
    struct QueenNode {
        vector<int> queens; // queens[i] = column of queen in row i
        int level;
        int conflicts;
        
        bool operator>(const QueenNode& other) const {
            return conflicts > other.conflicts;
        }
    };
    
    int n;
    
public:
    NQueensBB(int size) : n(size) {}
    
    vector<int> solveNQueens() {
        priority_queue<QueenNode, vector<QueenNode>, greater<QueenNode>> pq;
        
        QueenNode root;
        root.queens = vector<int>(n, -1);
        root.level = 0;
        root.conflicts = 0;
        
        pq.push(root);
        
        while (!pq.empty()) {
            QueenNode current = pq.top();
            pq.pop();
            
            if (current.level == n) {
                return current.queens; // Solution found
            }
            
            // Try placing queen in each column of current row
            for (int col = 0; col < n; col++) {
                if (isSafe(current.queens, current.level, col)) {
                    QueenNode child = current;
                    child.queens[current.level] = col;
                    child.level = current.level + 1;
                    child.conflicts = calculateConflicts(child.queens, child.level);
                    
                    pq.push(child);
                }
            }
        }
        
        return vector<int>(); // No solution
    }
    
private:
    bool isSafe(const vector<int>& queens, int row, int col) {
        for (int i = 0; i < row; i++) {
            if (queens[i] == col || 
                abs(queens[i] - col) == abs(i - row)) {
                return false;
            }
        }
        return true;
    }
    
    int calculateConflicts(const vector<int>& queens, int level) {
        int conflicts = 0;
        // Estimate conflicts for remaining queens
        return conflicts;
    }
};
```

### Problem 3: Subset Sum with Branch & Bound
```cpp
class SubsetSumBB {
private:
    struct SubsetNode {
        vector<int> subset;
        int level;
        int currentSum;
        int bound;
        
        bool operator>(const SubsetNode& other) const {
            return abs(bound - target) > abs(other.bound - target);
        }
    };
    
    vector<int> numbers;
    int target;
    int n;
    
public:
    SubsetSumBB(vector<int>& nums, int t) : numbers(nums), target(t), n(nums.size()) {
        sort(numbers.begin(), numbers.end());
    }
    
    vector<int> findSubsetSum() {
        priority_queue<SubsetNode, vector<SubsetNode>, greater<SubsetNode>> pq;
        
        SubsetNode root;
        root.subset = vector<int>();
        root.level = 0;
        root.currentSum = 0;
        root.bound = calculateBound(root);
        
        pq.push(root);
        
        while (!pq.empty()) {
            SubsetNode current = pq.top();
            pq.pop();
            
            if (current.currentSum == target) {
                return current.subset;
            }
            
            if (current.level >= n || current.currentSum > target) {
                continue;
            }
            
            // Include current number
            SubsetNode include = current;
            include.subset.push_back(numbers[current.level]);
            include.currentSum += numbers[current.level];
            include.level = current.level + 1;
            include.bound = calculateBound(include);
            
            if (include.currentSum <= target) {
                pq.push(include);
            }
            
            // Exclude current number
            SubsetNode exclude = current;
            exclude.level = current.level + 1;
            exclude.bound = calculateBound(exclude);
            
            pq.push(exclude);
        }
        
        return vector<int>(); // No solution
    }
    
private:
    int calculateBound(const SubsetNode& node) {
        int bound = node.currentSum;
        int remaining = target - node.currentSum;
        
        for (int i = node.level; i < n && remaining > 0; i++) {
            if (numbers[i] <= remaining) {
                bound += numbers[i];
                remaining -= numbers[i];
            }
        }
        
        return bound;
    }
};
```

---

## 💡 Best Practices

### 🎯 Effective Bounding Strategies
```cpp
class BoundingBestPractices {
public:
    // Tight bounds are crucial for efficiency
    double calculateTightBound(const Node& node, const Problem& problem) {
        // 1. Use problem-specific relaxations
        double relaxationBound = solveLinearRelaxation(node, problem);
        
        // 2. Use greedy heuristics
        double greedyBound = greedyHeuristic(node, problem);
        
        // 3. Use dual bounds from other algorithms
        double dualBound = getDualBound(node, problem);
        
        // Return the tightest bound
        return min({relaxationBound, greedyBound, dualBound});
    }
    
    // Preprocessing can improve bounds
    void preprocessProblem(Problem& problem) {
        // Sort items by efficiency ratios
        // Eliminate dominated options
        // Calculate initial bounds
    }
    
private:
    double solveLinearRelaxation(const Node& node, const Problem& problem) {
        // Solve continuous relaxation of the problem
        return 0.0;
    }
    
    double greedyHeuristic(const Node& node, const Problem& problem) {
        // Quick greedy solution for bound
        return 0.0;
    }
    
    double getDualBound(const Node& node, const Problem& problem) {
        // Use dual problem or Lagrangian relaxation
        return 0.0;
    }
};
```

### 🔧 Implementation Optimization
```cpp
class ImplementationOptimization {
public:
    // Memory management for large search trees
    void optimizeMemoryUsage() {
        // Use object pooling for nodes
        // Implement iterative deepening
        // Use bit manipulation for compact representation
    }
    
    // Parallel branch and bound
    void parallelBranchBound() {
        // Distribute nodes across threads
        // Shared best solution with synchronization
        // Load balancing strategies
    }
    
    // Early termination strategies
    bool shouldTerminateEarly(double currentBest, double targetQuality, 
                             int nodesExplored, int timeLimit) {
        // Stop if good enough solution found
        if (currentBest >= targetQuality) return true;
        
        // Stop if time limit exceeded
        if (getElapsedTime() > timeLimit) return true;
        
        // Stop if too many nodes explored
        if (nodesExplored > getNodeLimit()) return true;
        
        return false;
    }
    
private:
    int getElapsedTime() { return 0; }
    int getNodeLimit() { return 1000000; }
};
```

### 🧪 Testing and Validation
```cpp
class BranchBoundTesting {
public:
    void testBranchBoundSolver() {
        // Test with known optimal solutions
        testKnownInstances();
        
        // Test bound quality
        testBoundTightness();
        
        // Test pruning effectiveness
        testPruningRatio();
        
        // Test scalability
        testPerformance();
    }
    
private:
    void testKnownInstances() {
        cout << "Testing with benchmark instances..." << endl;
    }
    
    void testBoundTightness() {
        cout << "Measuring bound quality..." << endl;
    }
    
    void testPruningRatio() {
        cout << "Analyzing pruning effectiveness..." << endl;
    }
    
    void testPerformance() {
        cout << "Performance testing..." << endl;
    }
};
```

---

## 📊 Complexity Analysis

### ⏰ Time Complexity
- **Worst Case**: O(b^d) where b = branching factor, d = depth
- **Best Case**: O(d) with perfect pruning
- **Average Case**: Depends on bound quality and problem structure

### 💾 Space Complexity
- **LC Branch & Bound**: O(b^d) for priority queue
- **FIFO Branch & Bound**: O(b^h) where h = current level
- **Optimized**: O(d) with careful memory management

### 🎯 Practical Performance
- **Small Problems** (n ≤ 20): Often optimal
- **Medium Problems** (20 < n ≤ 100): Good with tight bounds
- **Large Problems** (n > 100): May need approximation

---

## 🌟 Key Takeaways

1. **Systematic Optimization**: Branch & Bound provides systematic approach to optimization
2. **Intelligent Pruning**: Bounds eliminate non-promising branches early
3. **Strategy Matters**: LC typically outperforms FIFO for optimization
4. **Bound Quality**: Tight bounds are crucial for efficiency
5. **Problem-Specific**: Adapt bounding functions to problem structure
6. **Scalability**: Consider approximation for very large instances

### 🎯 Interview Quick Reference
- **Branching**: Divide problem into subproblems
- **Bounding**: Calculate optimistic estimates
- **Pruning**: Eliminate non-promising branches
- **LC vs FIFO**: Best-first vs breadth-first exploration
- **Applications**: Job assignment, knapsack, TSP
- **Complexity**: Exponential worst-case, often much better in practice

---

*Master Branch & Bound to solve optimization problems systematically and efficiently! 🌳*