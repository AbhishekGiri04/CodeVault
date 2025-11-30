<div align="center">

# 🧠 Day 11: Greedy Algorithms - Optimal Choice Strategy Mastery

*Understanding Local Optimization for Global Solutions*

---

![Greedy](https://img.shields.io/badge/Topic-Greedy_Algorithms-FF6B6B?style=for-the-badge&logo=target&logoColor=white)
![Difficulty](https://img.shields.io/badge/Level-Intermediate_to_Advanced-4ECDC4?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Completed-45B7D1?style=for-the-badge)

</div>

---

## 🎯 **Learning Objectives**

> *Master the art of making optimal local choices for global optimization*

- 🏗️ Understand greedy algorithm principles and design patterns
- ⚡ Master greedy choice property and optimal substructure
- 🧩 Learn classic greedy problems and solution techniques
- 🚀 Apply greedy strategies in optimization scenarios

---

## 📖 **1. Greedy Algorithm Fundamentals**

<div align="center">

### 🧠 **What Makes Greedy Algorithms Special?**

</div>

<table>
<tr>
<td width="50%">

### 🎯 **Core Philosophy**
- **🎯 Local Optimization**: Make best choice at each step
- **🚫 No Backtracking**: Never reconsider previous decisions
- **⚡ Immediate Decisions**: Choose based on current information
- **🎪 Hope for Global Optimum**: Trust local choices lead to best solution

</td>
<td width="50%">

### ⚡ **Why Greedy Algorithms Matter?**
- **🚀 Efficiency**: Often faster than dynamic programming
- **💡 Simplicity**: Easy to understand and implement
- **📊 Real-World Applications**: Many practical optimization problems
- **💼 Interview Favorite**: Common in coding interviews

</td>
</tr>
</table>

### 🧮 **Greedy vs Other Approaches**

```
Problem: Coin Change (Amount = 11, Coins = [1, 5, 10])

Greedy Approach:
Step 1: Choose 10 (largest ≤ 11) → Remaining: 1
Step 2: Choose 1 (largest ≤ 1) → Remaining: 0
Result: [10, 1] → 2 coins

Dynamic Programming:
Considers all possibilities: [5, 5, 1] → 3 coins
But greedy gave optimal solution with 2 coins!

Note: Greedy works for canonical coin systems
```

---

## 📚 **2. Greedy Algorithm Properties**

<div align="center">

### 📊 **Essential Characteristics for Greedy Success**

</div>

<table>
<tr>
<td width="50%">

#### 🎯 **Greedy Choice Property**
```
At each step, a locally optimal choice 
leads to a globally optimal solution.

Example: Activity Selection
- Always choose activity with earliest finish time
- This local choice guarantees maximum activities
```

**Verification Steps:**
1. Assume greedy choice is not optimal
2. Show that swapping to greedy choice doesn't worsen solution
3. Prove greedy choice is at least as good as any other choice

#### ⚖️ **Optimal Substructure**
```
Optimal solution contains optimal solutions 
to subproblems.

Example: Fractional Knapsack
- After choosing item with best value/weight ratio
- Remaining problem is also a fractional knapsack
- Optimal solution to remaining gives overall optimal
```

</td>
<td width="50%">

#### 🔍 **When Greedy Works**
```cpp
bool isGreedyApplicable(Problem p) {
    return hasGreedyChoiceProperty(p) && 
           hasOptimalSubstructure(p);
}
```

**Success Indicators:**
- ✅ Clear ordering/sorting criterion
- ✅ Local choice doesn't affect future choices
- ✅ Problem has matroid structure
- ✅ Exchange argument applies

#### ⚠️ **When Greedy Fails**
```
Counter-example: 0/1 Knapsack
Items: [(value=10, weight=5), (value=20, weight=10), (value=15, weight=15)]
Capacity: 20

Greedy (by value/weight): Item1 + Item2 = value 30
Optimal: Item2 + Item3 = value 35

Greedy fails because items can't be fractioned!
```

</td>
</tr>
</table>

---

## 🧩 **3. Classic Greedy Problems**

<div align="center">

### 🎯 **Master These Essential Patterns**

</div>

<table>
<tr>
<td width="50%">

#### 📅 **Activity Selection Problem**
```cpp
struct Activity {
    int start, finish;
};

int maxActivities(vector<Activity>& activities) {
    // Sort by finish time (greedy choice)
    sort(activities.begin(), activities.end(), 
         [](const Activity& a, const Activity& b) {
             return a.finish < b.finish;
         });
    
    int count = 1;
    int lastFinish = activities[0].finish;
    
    for (int i = 1; i < activities.size(); i++) {
        if (activities[i].start >= lastFinish) {
            count++;
            lastFinish = activities[i].finish;
        }
    }
    
    return count;
}

// Time: O(n log n), Space: O(1)
// Greedy Choice: Earliest finish time
```

#### 🎒 **Fractional Knapsack**
```cpp
struct Item {
    int value, weight;
    double ratio;
};

double fractionalKnapsack(vector<Item>& items, int capacity) {
    // Calculate value/weight ratio
    for (auto& item : items) {
        item.ratio = (double)item.value / item.weight;
    }
    
    // Sort by ratio (greedy choice)
    sort(items.begin(), items.end(), 
         [](const Item& a, const Item& b) {
             return a.ratio > b.ratio;
         });
    
    double totalValue = 0;
    int currentWeight = 0;
    
    for (const auto& item : items) {
        if (currentWeight + item.weight <= capacity) {
            // Take whole item
            currentWeight += item.weight;
            totalValue += item.value;
        } else {
            // Take fraction of item
            int remaining = capacity - currentWeight;
            totalValue += item.ratio * remaining;
            break;
        }
    }
    
    return totalValue;
}

// Time: O(n log n), Space: O(1)
// Greedy Choice: Highest value/weight ratio
```

</td>
<td width="50%">

#### 💰 **Job Scheduling with Deadlines**
```cpp
struct Job {
    int id, deadline, profit;
};

int maxProfit(vector<Job>& jobs) {
    // Sort by profit (greedy choice)
    sort(jobs.begin(), jobs.end(), 
         [](const Job& a, const Job& b) {
             return a.profit > b.profit;
         });
    
    int maxDeadline = 0;
    for (const auto& job : jobs) {
        maxDeadline = max(maxDeadline, job.deadline);
    }
    
    vector<bool> slot(maxDeadline + 1, false);
    int totalProfit = 0;
    
    for (const auto& job : jobs) {
        // Find free slot before deadline
        for (int j = job.deadline; j > 0; j--) {
            if (!slot[j]) {
                slot[j] = true;
                totalProfit += job.profit;
                break;
            }
        }
    }
    
    return totalProfit;
}

// Time: O(n²), Space: O(max_deadline)
// Greedy Choice: Highest profit first
```

#### 🪙 **Coin Change (Canonical Systems)**
```cpp
int minCoins(vector<int>& coins, int amount) {
    // Sort coins in descending order
    sort(coins.rbegin(), coins.rend());
    
    int coinCount = 0;
    
    for (int coin : coins) {
        while (amount >= coin) {
            amount -= coin;
            coinCount++;
        }
    }
    
    return amount == 0 ? coinCount : -1;
}

// Time: O(n log n + amount/min_coin), Space: O(1)
// Greedy Choice: Largest coin first
// Note: Only works for canonical coin systems!
```

</td>
</tr>
</table>

---

## 🌳 **4. Graph-Based Greedy Algorithms**

<div align="center">

### 🚀 **Advanced Greedy Techniques**

</div>

<table>
<tr>
<td width="50%">

#### 🛤️ **Dijkstra's Shortest Path**
```cpp
vector<int> dijkstra(vector<vector<pair<int,int>>>& graph, 
                     int start) {
    int n = graph.size();
    vector<int> dist(n, INT_MAX);
    priority_queue<pair<int,int>, 
                   vector<pair<int,int>>, 
                   greater<pair<int,int>>> pq;
    
    dist[start] = 0;
    pq.push({0, start});
    
    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();
        
        if (d > dist[u]) continue;
        
        for (auto& edge : graph[u]) {
            int v = edge.first;
            int weight = edge.second;
            
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }
    
    return dist;
}

// Time: O((V + E) log V), Space: O(V)
// Greedy Choice: Minimum distance vertex
```

#### 🌳 **Prim's Minimum Spanning Tree**
```cpp
int primMST(vector<vector<pair<int,int>>>& graph) {
    int n = graph.size();
    vector<bool> inMST(n, false);
    vector<int> key(n, INT_MAX);
    priority_queue<pair<int,int>, 
                   vector<pair<int,int>>, 
                   greater<pair<int,int>>> pq;
    
    key[0] = 0;
    pq.push({0, 0});
    int mstWeight = 0;
    
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        
        if (inMST[u]) continue;
        
        inMST[u] = true;
        mstWeight += key[u];
        
        for (auto& edge : graph[u]) {
            int v = edge.first;
            int weight = edge.second;
            
            if (!inMST[v] && weight < key[v]) {
                key[v] = weight;
                pq.push({weight, v});
            }
        }
    }
    
    return mstWeight;
}

// Time: O((V + E) log V), Space: O(V)
// Greedy Choice: Minimum weight edge to MST
```

</td>
<td width="50%">

#### 🔗 **Kruskal's MST with Union-Find**
```cpp
class UnionFind {
    vector<int> parent, rank;
public:
    UnionFind(int n) : parent(n), rank(n, 0) {
        iota(parent.begin(), parent.end(), 0);
    }
    
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    
    bool unite(int x, int y) {
        int px = find(x), py = find(y);
        if (px == py) return false;
        
        if (rank[px] < rank[py]) swap(px, py);
        parent[py] = px;
        if (rank[px] == rank[py]) rank[px]++;
        return true;
    }
};

struct Edge {
    int u, v, weight;
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

int kruskalMST(vector<Edge>& edges, int n) {
    sort(edges.begin(), edges.end());
    UnionFind uf(n);
    
    int mstWeight = 0;
    int edgesUsed = 0;
    
    for (const Edge& e : edges) {
        if (uf.unite(e.u, e.v)) {
            mstWeight += e.weight;
            edgesUsed++;
            if (edgesUsed == n - 1) break;
        }
    }
    
    return mstWeight;
}

// Time: O(E log E), Space: O(V)
// Greedy Choice: Minimum weight edge (no cycle)
```

#### 🗜️ **Huffman Coding**
```cpp
struct Node {
    char ch;
    int freq;
    Node* left;
    Node* right;
    
    Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

Node* huffmanTree(vector<pair<char, int>>& frequencies) {
    priority_queue<Node*, vector<Node*>, Compare> pq;
    
    // Create leaf nodes
    for (auto& p : frequencies) {
        pq.push(new Node(p.first, p.second));
    }
    
    // Build Huffman tree
    while (pq.size() > 1) {
        Node* right = pq.top(); pq.pop();
        Node* left = pq.top(); pq.pop();
        
        Node* merged = new Node('\0', left->freq + right->freq);
        merged->left = left;
        merged->right = right;
        
        pq.push(merged);
    }
    
    return pq.top();
}

// Time: O(n log n), Space: O(n)
// Greedy Choice: Merge two minimum frequency nodes
```

</td>
</tr>
</table>

---

## 📊 **5. Greedy vs Dynamic Programming**

<div align="center">

### ⚖️ **When to Choose Which Approach**

</div>

| Aspect | Greedy Algorithm | Dynamic Programming |
|:-------|:-----------------|:-------------------|
| **Decision Making** | Local optimal choice | Consider all possibilities |
| **Backtracking** | No reconsideration | Can revise decisions |
| **Time Complexity** | Usually O(n log n) | Usually O(n²) or higher |
| **Space Complexity** | O(1) or O(n) | O(n) or O(n²) |
| **Guarantee** | May not be optimal | Always optimal |
| **Examples** | Activity Selection, MST | 0/1 Knapsack, LCS |

---

## 🎯 **6. Greedy Algorithm Design Strategy**

<div align="center">

### 🛠️ **Step-by-Step Design Process**

</div>

```
1. 🎯 IDENTIFY THE GREEDY CHOICE
   - What local decision seems best?
   - How to order/prioritize elements?

2. 🔍 PROVE GREEDY CHOICE PROPERTY
   - Show local optimal leads to global optimal
   - Use exchange argument or contradiction

3. ⚖️ VERIFY OPTIMAL SUBSTRUCTURE
   - After greedy choice, remaining is subproblem
   - Optimal solution contains optimal subsolutions

4. 🏗️ IMPLEMENT THE ALGORITHM
   - Sort elements by greedy criterion
   - Make greedy choices iteratively
   - Build solution step by step

5. 🧪 ANALYZE COMPLEXITY
   - Time: Usually dominated by sorting O(n log n)
   - Space: Often O(1) additional space
```

---

## 🔥 **7. Interview Problem Categories**

<div align="center">

### 🎯 **Must-Know Problem Types**

</div>

| Category | Problems | Difficulty | Key Technique |
|:---------|:---------|:-----------|:--------------|
| **📅 Scheduling** | Activity Selection, Meeting Rooms | 🟡 Medium | Sort by end time |
| **🎒 Optimization** | Fractional Knapsack, Gas Station | 🟡 Medium | Sort by ratio/criteria |
| **💰 Profit Maximization** | Job Scheduling, Stock Trading | 🟡 Medium | Sort by profit/value |
| **🌳 Graph MST** | Minimum Spanning Tree | 🟡 Medium | Kruskal's, Prim's |
| **🛤️ Shortest Path** | Dijkstra's Algorithm | 🟡 Medium | Priority queue |
| **🗜️ Compression** | Huffman Coding | 🔴 Hard | Priority queue, trees |

---

## 🎯 **8. Key Takeaways & Best Practices**

<div align="center">

### 💡 **Essential Insights**

</div>

> 🧠 **Greedy Choice**: Always identify the clear local optimization criterion  
> 🔍 **Proof Requirement**: Verify greedy choice property before implementation  
> ⚖️ **Trade-offs**: Understand when greedy works vs when DP is needed  
> 📊 **Sorting**: Most greedy algorithms start with sorting by some criterion  
> 🧪 **Testing**: Always test with counter-examples to verify correctness  

---

## 📚 **9. Next Learning Path**

<table>
<tr>
<td width="50%">

### 🎯 **Immediate Next Steps**
- [ ] Master all classic greedy problems
- [ ] Practice greedy vs DP decision making
- [ ] Learn graph-based greedy algorithms
- [ ] Understand proof techniques

</td>
<td width="50%">

### 🚀 **Advanced Topics**
- [ ] Matroid theory and greedy algorithms
- [ ] Approximation algorithms
- [ ] Online algorithms
- [ ] Advanced optimization techniques

</td>
</tr>
</table>

---

<div align="center">

### 📊 **Learning Progress**

![Progress](https://img.shields.io/badge/Completion-100%25-success?style=for-the-badge)
![Concepts](https://img.shields.io/badge/Concepts_Learned-15-blue?style=for-the-badge)
![Patterns](https://img.shields.io/badge/Algorithms_Mastered-8-orange?style=for-the-badge)

---

**📅 Session Date**: Day 11 | **🎯 Focus**: Greedy Algorithm Mastery | **⏰ Duration**: Comprehensive Strategy Analysis

*"Greedy algorithms teach us that sometimes the best global solution comes from consistently making the best local choices"*

</div>