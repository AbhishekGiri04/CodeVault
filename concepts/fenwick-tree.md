# 🌲 Fenwick Tree — Complete Professional <div align="center">Guide</div>

<div align="center">

![Fenwick Tree](https://img.shields.io/badge/Fenwick_Tree-Binary_Indexed_Tree-FF6B6B?style=for-the-badge&logo=tree&logoColor=white)
![Difficulty](https://img.shields.io/badge/Difficulty-Advanced-red?style=for-the-badge)
![Importance](https://img.shields.io/badge/Importance-High-darkred?style=for-the-badge)

**Master space-efficient data structure for dynamic prefix sum queries**

</div>

---

## 📑 Table of Contents

1. [Introduction](#introduction)
2. [Core Concepts](#core-concepts)
3. [Basic Operations](#basic-operations)
4. [Implementation](#implementation)
5. [Advanced Variants](#advanced-variants)
6. [Applications](#applications)
7. [Interview Problems](#interview-problems)
8. [Best Practices](#best-practices)

---

## Introduction

**Fenwick Tree (Binary Indexed Tree - BIT)** is a space-efficient data structure that supports prefix sum queries and point updates in O(log n) time, making it ideal for dynamic array problems with frequent updates and range queries.

<div align="center">
<img src="https://www.scaler.com/topics/images/frenwich_tree_thumbnail.webp" alt="Fenwick Tree Overview" width="650" height="400"/>
</div>

### Key Features

```mermaid
flowchart TD
    A["🌲 Fenwick Tree"] --> B["⚡ Efficient Operations"]
    A --> C["💾 Space Efficient"]
    A --> D["🔧 Implementation"]
    A --> E["🎯 Applications"]
    
    B --> F["O(log n) updates"]
    B --> G["O(log n) queries"]
    B --> H["Fast prefix sums"]
    
    C --> I["O(n) space"]
    C --> J["Array-based"]
    C --> K["Cache friendly"]
    
    D --> L["Bit manipulation"]
    D --> M["LSB operations"]
    D --> N["Simple code"]
    
    E --> O["Range queries"]
    E --> P["Frequency counting"]
    E --> Q["Inversion counting"]
    
    classDef default fill:#f9f9f9,stroke:#333,stroke-width:2px,color:#000
    classDef concept fill:#e3f2fd,stroke:#2196f3,stroke-width:2px,color:#000
    classDef operations fill:#fff3e0,stroke:#ff9800,stroke-width:2px,color:#000
    classDef space fill:#e8f5e8,stroke:#4caf50,stroke-width:2px,color:#000
    classDef implementation fill:#f3e5f5,stroke:#9c27b0,stroke-width:2px,color:#000
    classDef applications fill:#ffebee,stroke:#f44336,stroke-width:2px,color:#000
    class A concept
    class B,F,G,H operations
    class C,I,J,K space
    class D,L,M,N implementation
    class E,O,P,Q applications
```

### When to Use Fenwick Tree

```mermaid
flowchart TD
    A["Problem Analysis"] --> B{"Frequent Updates?"}
    B -->|Yes| C{"Range Queries?"}
    B -->|No| D["Use Prefix Sum Array"]
    
    C -->|Yes| E{"Point Updates Only?"}
    C -->|No| F["Use Simple Array"]
    
    E -->|Yes| G["🌲 Use Fenwick Tree"]
    E -->|No| H["Consider Segment Tree"]
    
    G --> I["Perfect for:"]
    I --> J["Dynamic prefix sums"]
    I --> K["Frequency counting"]
    I --> L["Inversion counting"]
    I --> M["Range sum queries"]
    
    classDef default fill:#f9f9f9,stroke:#333,stroke-width:2px,color:#000
    classDef analysis fill:#e3f2fd,stroke:#2196f3,stroke-width:2px,color:#000
    classDef decision fill:#fff3e0,stroke:#ff9800,stroke-width:2px,color:#000
    classDef solution fill:#e8f5e8,stroke:#4caf50,stroke-width:2px,color:#000
    classDef applications fill:#f3e5f5,stroke:#9c27b0,stroke-width:2px,color:#000
    class A analysis
    class B,C,E decision
    class G solution
    class I,J,K,L,M applications
```

---

## Core Concepts

### Binary Index Manipulation

<div align="center">
<img src="https://scaler.com/topics/images/different_operations_of_fenwick_tree.webp" alt="Fenwick Tree Operations" width="650" height="400"/>
</div>

```mermaid
flowchart TD
    A["Binary Index Magic"] --> B["LSB Operation"]
    A --> C["Index Responsibility"]
    A --> D["Tree Structure"]
    
    B --> E["x & (-x)"]
    B --> F["Isolates rightmost 1-bit"]
    B --> G["Determines range size"]
    
    C --> H["Each index covers range"]
    C --> I["Range size = LSB value"]
    C --> J["Hierarchical coverage"]
    
    D --> K["Implicit tree structure"]
    D --> L["Parent-child relationships"]
    D --> M["Efficient traversal"]
    
    classDef default fill:#f9f9f9,stroke:#333,stroke-width:2px,color:#000
    classDef concept fill:#e3f2fd,stroke:#2196f3,stroke-width:2px,color:#000
    classDef lsb fill:#fff3e0,stroke:#ff9800,stroke-width:2px,color:#000
    classDef responsibility fill:#e8f5e8,stroke:#4caf50,stroke-width:2px,color:#000
    classDef structure fill:#f3e5f5,stroke:#9c27b0,stroke-width:2px,color:#000
    class A concept
    class B,E,F,G lsb
    class C,H,I,J responsibility
    class D,K,L,M structure
```

### LSB Demonstration

```cpp
class BinaryIndexConcepts {
public:
    // Least Significant Bit (LSB) - Core operation
    int LSB(int x) {
        return x & (-x);
    }
    
    void demonstrateLSB() {
        cout << "LSB Demonstration:" << endl;
        cout << "==================" << endl;
        
        vector<int> examples = {1, 2, 3, 4, 5, 6, 7, 8, 12, 16};
        
        for (int x : examples) {
            int lsb = LSB(x);
            cout << "x = " << x << " (binary: " << bitset<8>(x) 
                 << "), LSB = " << lsb << endl;
        }
    }
    
    // Understanding index responsibility
    void explainResponsibility() {
        cout << "\nIndex Responsibility in Fenwick Tree:" << endl;
        cout << "====================================" << endl;
        
        for (int i = 1; i <= 16; i++) {
            int lsb = LSB(i);
            int start = i - lsb + 1;
            int end = i;
            
            cout << "BIT[" << i << "] covers range [" << start << ", " << end 
                 << "] (size: " << lsb << ")" << endl;
        }
    }
};
```

---

## Basic Operations

### Standard Fenwick Tree Implementation

<div align="center">
<img src="https://scaler.com/topics/images/binary_representation_of_number.webp" alt="Binary Representation in Fenwick Tree" width="650" height="400"/>
</div>

```mermaid
flowchart TD
    A["Fenwick Tree Operations"] --> B["Update Operation"]
    A --> C["Query Operation"]
    A --> D["Range Query"]
    
    B --> E["Start at index i"]
    E --> F["Add value to BIT[i]"]
    F --> G["i += i & (-i)"]
    G --> H{"i <= n?"}
    H -->|Yes| F
    H -->|No| I["Done"]
    
    C --> J["Start at index i"]
    J --> K["Add BIT[i] to sum"]
    K --> L["i -= i & (-i)"]
    L --> M{"i > 0?"}
    M -->|Yes| K
    M -->|No| N["Return sum"]
    
    D --> O["query(r) - query(l-1)"]
    
    classDef default fill:#f9f9f9,stroke:#333,stroke-width:2px,color:#000
    classDef operation fill:#e3f2fd,stroke:#2196f3,stroke-width:2px,color:#000
    classDef update fill:#fff3e0,stroke:#ff9800,stroke-width:2px,color:#000
    classDef query fill:#e8f5e8,stroke:#4caf50,stroke-width:2px,color:#000
    classDef range fill:#f3e5f5,stroke:#9c27b0,stroke-width:2px,color:#000
    class A operation
    class B,E,F,G,H,I update
    class C,J,K,L,M,N query
    class D,O range
```

---

## Implementation

### Complete Fenwick Tree Class

```cpp
class FenwickTree {
private:
    vector<int> BIT;
    int n;
    
public:
    FenwickTree(int size) : n(size) {
        BIT.assign(n + 1, 0); // 1-indexed
    }
    
    FenwickTree(vector<int>& arr) : n(arr.size()) {
        BIT.assign(n + 1, 0);
        
        // Build tree from array
        for (int i = 0; i < n; i++) {
            update(i + 1, arr[i]); // Convert to 1-indexed
        }
    }
    
    // Point update: add val to index i
    void update(int i, int val) {
        while (i <= n) {
            BIT[i] += val;
            i += i & (-i); // Move to next responsible parent
        }
    }
    
    // Prefix sum query: sum from 1 to i
    int query(int i) {
        int sum = 0;
        while (i > 0) {
            sum += BIT[i];
            i -= i & (-i); // Move to parent
        }
        return sum;
    }
    
    // Range sum query: sum from l to r (1-indexed)
    int rangeQuery(int l, int r) {
        if (l > r) return 0;
        return query(r) - query(l - 1);
    }
    
    // Set value at index i (not add)
    void setValue(int i, int val) {
        int currentVal = rangeQuery(i, i);
        update(i, val - currentVal);
    }
    
    // Get current value at index i
    int getValue(int i) {
        return rangeQuery(i, i);
    }
};
```

---

## Advanced Variants

### Range Update Point Query (RUPQ)

```mermaid
flowchart TD
    A["RUPQ Fenwick Tree"] --> B["Difference Array Approach"]
    B --> C["Range Update"]
    B --> D["Point Query"]
    
    C --> E["Add val at start"]
    C --> F["Subtract val at end+1"]
    C --> G["Lazy propagation effect"]
    
    D --> H["Query prefix sum"]
    D --> I["Get accumulated difference"]
    
    classDef default fill:#f9f9f9,stroke:#333,stroke-width:2px,color:#000
    classDef concept fill:#e3f2fd,stroke:#2196f3,stroke-width:2px,color:#000
    classDef approach fill:#fff3e0,stroke:#ff9800,stroke-width:2px,color:#000
    classDef update fill:#e8f5e8,stroke:#4caf50,stroke-width:2px,color:#000
    classDef query fill:#f3e5f5,stroke:#9c27b0,stroke-width:2px,color:#000
    class A concept
    class B approach
    class C,E,F,G update
    class D,H,I query
```

```cpp
class FenwickTreeRUPQ {
private:
    FenwickTree diff; // Difference array BIT
    
public:
    FenwickTreeRUPQ(int n) : diff(n) {}
    
    // Range update: add val to range [l, r]
    void rangeUpdate(int l, int r, int val) {
        diff.update(l, val);      // Start of range
        diff.update(r + 1, -val); // End of range + 1
    }
    
    // Point query: get value at index i
    int pointQuery(int i) {
        return diff.query(i);
    }
};
```

### 2D Fenwick Tree

```cpp
class FenwickTree2D {
private:
    vector<vector<long long>> BIT;
    int n, m;
    
public:
    FenwickTree2D(int rows, int cols) : n(rows), m(cols) {
        BIT.assign(n + 1, vector<long long>(m + 1, 0));
    }
    
    void update(int x, int y, long long val) {
        for (int i = x; i <= n; i += i & (-i)) {
            for (int j = y; j <= m; j += j & (-j)) {
                BIT[i][j] += val;
            }
        }
    }
    
    long long query(int x, int y) {
        long long sum = 0;
        for (int i = x; i > 0; i -= i & (-i)) {
            for (int j = y; j > 0; j -= j & (-j)) {
                sum += BIT[i][j];
            }
        }
        return sum;
    }
    
    long long rangeQuery(int x1, int y1, int x2, int y2) {
        return query(x2, y2) - query(x1 - 1, y2) - 
               query(x2, y1 - 1) + query(x1 - 1, y1 - 1);
    }
};
```

---

## Applications

### Frequency Counting

```mermaid
flowchart TD
    A["Frequency Counting Applications"] --> B["Coordinate Compression"]
    A --> C["Dynamic Frequency Updates"]
    A --> D["Range Frequency Queries"]
    
    B --> E["Map large values to indices"]
    B --> F["Maintain sorted unique values"]
    B --> G["Enable BIT usage"]
    
    C --> H["Add/Remove elements"]
    C --> I["Update frequencies"]
    C --> J["Real-time processing"]
    
    D --> K["Count elements ≤ value"]
    D --> L["Count in range"]
    D --> M["Percentile queries"]
    
    classDef default fill:#f9f9f9,stroke:#333,stroke-width:2px,color:#000
    classDef application fill:#e3f2fd,stroke:#2196f3,stroke-width:2px,color:#000
    classDef compression fill:#fff3e0,stroke:#ff9800,stroke-width:2px,color:#000
    classDef updates fill:#e8f5e8,stroke:#4caf50,stroke-width:2px,color:#000
    classDef queries fill:#f3e5f5,stroke:#9c27b0,stroke-width:2px,color:#000
    class A application
    class B,E,F,G compression
    class C,H,I,J updates
    class D,K,L,M queries
```

```cpp
class FrequencyCounter {
private:
    FenwickTree ft;
    unordered_map<int, int> compressed;
    vector<int> values;
    
public:
    FrequencyCounter(vector<int>& nums) : ft(nums.size()) {
        // Coordinate compression
        values = nums;
        sort(values.begin(), values.end());
        values.erase(unique(values.begin(), values.end()), values.end());
        
        for (int i = 0; i < values.size(); i++) {
            compressed[values[i]] = i + 1;
        }
    }
    
    void add(int val) {
        int idx = compressed[val];
        ft.update(idx, 1);
    }
    
    void remove(int val) {
        int idx = compressed[val];
        ft.update(idx, -1);
    }
    
    int countLessEqual(int val) {
        auto it = upper_bound(values.begin(), values.end(), val);
        if (it == values.begin()) return 0;
        
        int idx = compressed[*(--it)];
        return ft.query(idx);
    }
};
```

### Inversion Count

```cpp
class InversionCounter {
public:
    long long countInversions(vector<int>& arr) {
        // Coordinate compression
        vector<int> sorted = arr;
        sort(sorted.begin(), sorted.end());
        sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end());
        
        unordered_map<int, int> compressed;
        for (int i = 0; i < sorted.size(); i++) {
            compressed[sorted[i]] = i + 1;
        }
        
        FenwickTree ft(sorted.size());
        long long inversions = 0;
        
        for (int i = arr.size() - 1; i >= 0; i--) {
            int idx = compressed[arr[i]];
            inversions += ft.query(idx - 1);
            ft.update(idx, 1);
        }
        
        return inversions;
    }
};
```

---

## Interview Problems

### Count Smaller Numbers After Self

```cpp
class CountSmallerAfterSelf {
public:
    vector<int> countSmaller(vector<int>& nums) {
        int n = nums.size();
        vector<int> result(n);
        
        // Coordinate compression
        vector<int> sorted = nums;
        sort(sorted.begin(), sorted.end());
        sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end());
        
        FenwickTree ft(sorted.size());
        
        // Process from right to left
        for (int i = n - 1; i >= 0; i--) {
            int pos = lower_bound(sorted.begin(), sorted.end(), nums[i]) - sorted.begin() + 1;
            
            // Count smaller elements
            result[i] = ft.query(pos - 1);
            
            // Add current element
            ft.update(pos, 1);
        }
        
        return result;
    }
};
```

### Range Sum Query - Mutable

```cpp
class NumArray {
private:
    FenwickTree ft;
    vector<int> nums;
    
public:
    NumArray(vector<int>& nums) : nums(nums), ft(nums.size()) {
        for (int i = 0; i < nums.size(); i++) {
            ft.update(i + 1, nums[i]);
        }
    }
    
    void update(int index, int val) {
        int diff = val - nums[index];
        nums[index] = val;
        ft.update(index + 1, diff);
    }
    
    int sumRange(int left, int right) {
        return ft.rangeQuery(left + 1, right + 1);
    }
};
```

---

## Best Practices

### Implementation Guidelines

```mermaid
flowchart TD
    A["Fenwick Tree Best Practices"] --> B["Index Management"]
    A --> C["Common Patterns"]
    A --> D["Optimization Tips"]
    A --> E["Error Prevention"]
    
    B --> F["Always use 1-based indexing"]
    B --> G["Convert input to 1-based"]
    B --> H["Handle range queries correctly"]
    
    C --> I["LSB calculation: i & (-i)"]
    C --> J["Update: i += i & (-i)"]
    C --> K["Query: i -= i & (-i)"]
    
    D --> L["Coordinate compression"]
    D --> M["Use appropriate data types"]
    D --> N["Consider 2D variants"]
    
    E --> O["Check bounds"]
    E --> P["Validate input ranges"]
    E --> Q["Handle edge cases"]
    
    classDef default fill:#f9f9f9,stroke:#333,stroke-width:2px,color:#000
    classDef practice fill:#e3f2fd,stroke:#2196f3,stroke-width:2px,color:#000
    classDef index fill:#fff3e0,stroke:#ff9800,stroke-width:2px,color:#000
    classDef patterns fill:#e8f5e8,stroke:#4caf50,stroke-width:2px,color:#000
    classDef optimization fill:#f3e5f5,stroke:#9c27b0,stroke-width:2px,color:#000
    classDef prevention fill:#ffebee,stroke:#f44336,stroke-width:2px,color:#000
    class A practice
    class B,F,G,H index
    class C,I,J,K patterns
    class D,L,M,N optimization
    class E,O,P,Q prevention
```

### Performance Comparison

| Data Structure | Update | Range Query | Space | Implementation |
|----------------|--------|-------------|-------|----------------|
| **Array** | O(1) | O(n) | O(n) | Very Easy |
| **Prefix Sum** | O(n) | O(1) | O(n) | Easy |
| **Fenwick Tree** | O(log n) | O(log n) | O(n) | Medium |
| **Segment Tree** | O(log n) | O(log n) | O(4n) | Hard |

### Common Pitfalls and Solutions

```cpp
class FenwickTreeBestPractices {
public:
    // ✅ Correct: 1-based indexing
    void correctImplementation() {
        FenwickTree ft(n);
        ft.update(1, value);  // 1-based
        int sum = ft.query(5); // 1-based
    }
    
    // ❌ Wrong: 0-based indexing
    void wrongImplementation() {
        FenwickTree ft(n);
        ft.update(0, value);  // Wrong!
    }
    
    // ✅ Correct: Range query
    int correctRangeQuery(FenwickTree& ft, int l, int r) {
        return ft.query(r) - ft.query(l - 1);
    }
    
    // ❌ Wrong: Direct range calculation
    int wrongRangeQuery(FenwickTree& ft, int l, int r) {
        return ft.query(r) - ft.query(l); // Wrong!
    }
    
    // ✅ Correct: Coordinate compression for large values
    void handleLargeValues(vector<int>& nums) {
        vector<int> sorted = nums;
        sort(sorted.begin(), sorted.end());
        sorted.erase(unique(sorted.begin(), sorted.end()), sorted.end());
        
        unordered_map<int, int> compressed;
        for (int i = 0; i < sorted.size(); i++) {
            compressed[sorted[i]] = i + 1;
        }
        
        FenwickTree ft(sorted.size());
        // Use compressed[nums[i]] as index
    }
};
```

---

## Summary

**Fenwick Tree** is a powerful and elegant data structure for dynamic range operations. Key insights:

### Essential Concepts
- **Binary Index Magic**: LSB operation (x & -x) drives the efficiency
- **1-Based Indexing**: Critical for correct implementation
- **Implicit Tree Structure**: Array-based with parent-child relationships
- **Range Responsibility**: Each index covers a specific range

### Core Operations
- **Update**: O(log n) point updates using LSB traversal
- **Query**: O(log n) prefix sum queries
- **Range Query**: query(r) - query(l-1) for range sums
- **Space Efficiency**: O(n) space vs O(4n) for segment trees

### Best Practices
- Always use 1-based indexing for BIT operations
- Apply coordinate compression for large value ranges
- Consider 2D variants for matrix problems
- Use appropriate data types to prevent overflow

> **Master's Insight**: Fenwick Tree's elegance lies in its bit manipulation foundation. The LSB operation creates an implicit tree structure that enables logarithmic operations with minimal space overhead.

---

<div align="center">

**🌲 Master Fenwick Trees • Optimize Range Operations • Build Efficient Solutions**

*From Theory to Practice • Bit Manipulation to Implementation • Understanding to Mastery*

</div>