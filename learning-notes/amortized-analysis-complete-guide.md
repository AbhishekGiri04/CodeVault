# ⚖️ Amortized Analysis Complete Guide

## 📋 Table of Contents
- [Introduction](#introduction)
- [Core Concepts](#core-concepts)
- [Aggregate Method](#aggregate-method)
- [Accounting Method](#accounting-method)
- [Potential Method](#potential-method)
- [Dynamic Array Analysis](#dynamic-array-analysis)
- [Stack Operations](#stack-operations)
- [Binary Counter](#binary-counter)
- [Splay Trees](#splay-trees)
- [Fibonacci Heap](#fibonacci-heap)
- [Interview Problems](#interview-problems)
- [Best Practices](#best-practices)

---

## 🎯 Introduction

**Amortized Analysis** is a technique for analyzing the average time per operation over a sequence of operations, providing guaranteed performance bounds without probabilistic assumptions.

### 🔑 Key Principles
- **Average Performance**: Analyze cost over sequence of operations
- **Worst-Case Guarantee**: No probabilistic assumptions needed
- **Cost Distribution**: Expensive operations balanced by cheap ones
- **Practical Bounds**: More realistic than pure worst-case analysis

### 🌟 Why Amortized Analysis?
- **Realistic Performance**: Better than pessimistic worst-case
- **Guaranteed Bounds**: Unlike probabilistic average-case
- **Design Insight**: Helps optimize data structure operations
- **Interview Relevance**: Common in technical discussions

---

## 🧩 Core Concepts

### 📊 Amortized vs Other Analysis Types

```cpp
class AnalysisComparison {
public:
    void compareAnalysisTypes() {
        cout << "Analysis Type Comparison:" << endl;
        cout << "========================" << endl;
        
        cout << "Worst-Case Analysis:" << endl;
        cout << "  - Maximum cost of any single operation" << endl;
        cout << "  - Often too pessimistic" << endl;
        cout << "  - Example: Dynamic array resize O(n)" << endl;
        
        cout << "Average-Case Analysis:" << endl;
        cout << "  - Expected cost assuming input distribution" << endl;
        cout << "  - Requires probabilistic assumptions" << endl;
        cout << "  - May not guarantee performance" << endl;
        
        cout << "Amortized Analysis:" << endl;
        cout << "  - Average cost over sequence of operations" << endl;
        cout << "  - Guaranteed performance bounds" << endl;
        cout << "  - No probabilistic assumptions" << endl;
        cout << "  - Example: Dynamic array insertion O(1)" << endl;
    }
    
    // Demonstrate the difference with dynamic array
    void demonstrateDynamicArray() {
        vector<int> arr;
        int operations = 1000;
        
        auto start = chrono::high_resolution_clock::now();
        
        for (int i = 0; i < operations; i++) {
            arr.push_back(i);
        }
        
        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
        
        cout << "Dynamic Array Performance:" << endl;
        cout << "Operations: " << operations << endl;
        cout << "Total time: " << duration.count() << " microseconds" << endl;
        cout << "Amortized time per operation: " 
             << (double)duration.count() / operations << " microseconds" << endl;
        cout << "Worst-case single operation: O(n) for resize" << endl;
        cout << "Amortized per operation: O(1)" << endl;
    }
};
```

---

## 📈 Aggregate Method

### 📝 Definition
Calculate total cost of n operations, then divide by n.

**Formula**: Amortized Cost = Total Cost of n operations / n

```cpp
class AggregateMethod {
public:
    // Dynamic Array using Aggregate Method
    class DynamicArrayAnalysis {
    public:
        // Analyze n insertions with doubling strategy
        double analyzeInsertions(int n) {
            int totalCost = 0;
            int capacity = 1;
            int size = 0;
            
            for (int i = 0; i < n; i++) {
                if (size == capacity) {
                    // Resize operation: copy all elements
                    totalCost += size; // Cost of copying
                    capacity *= 2;
                }
                
                totalCost += 1; // Cost of insertion
                size++;
            }
            
            cout << "Aggregate Method Analysis:" << endl;
            cout << "Total operations: " << n << endl;
            cout << "Total cost: " << totalCost << endl;
            cout << "Amortized cost per operation: " << (double)totalCost / n << endl;
            
            return (double)totalCost / n;
        }
        
        // Theoretical analysis
        double theoreticalAnalysis(int n) {
            // Resizes happen at sizes: 1, 2, 4, 8, ..., largest power of 2 ≤ n
            int totalResizeCost = 0;
            
            for (int capacity = 1; capacity < n; capacity *= 2) {
                totalResizeCost += capacity;
            }
            
            int totalInsertCost = n; // Each insertion costs 1
            int totalCost = totalInsertCost + totalResizeCost;
            
            cout << "Theoretical Aggregate Analysis:" << endl;
            cout << "Insert cost: " << totalInsertCost << endl;
            cout << "Resize cost: " << totalResizeCost << endl;
            cout << "Total cost: " << totalCost << endl;
            cout << "Amortized: " << (double)totalCost / n << endl;
            
            // Total resize cost ≤ 2n, so amortized cost ≤ 3
            return (double)totalCost / n;
        }
    };
    
    // Binary Counter using Aggregate Method
    class BinaryCounterAnalysis {
    public:
        int countBitFlips(int n) {
            int totalFlips = 0;
            
            // Count flips for each bit position
            for (int bit = 0; bit < 32; bit++) {
                // Bit i flips every 2^i operations
                int flipFrequency = 1 << bit;
                totalFlips += n / flipFrequency;
            }
            
            cout << "Binary Counter Aggregate Analysis:" << endl;
            cout << "Operations: " << n << endl;
            cout << "Total bit flips: " << totalFlips << endl;
            cout << "Amortized flips per increment: " << (double)totalFlips / n << endl;
            
            return totalFlips;
        }
        
        // Simulate actual counting
        int simulateCounter(int n) {
            int counter = 0;
            int totalFlips = 0;
            
            for (int i = 0; i < n; i++) {
                int oldCounter = counter;
                counter++;
                
                // Count bit flips
                int xorResult = oldCounter ^ counter;
                totalFlips += __builtin_popcount(xorResult);
            }
            
            cout << "Simulated Binary Counter:" << endl;
            cout << "Final counter value: " << counter << endl;
            cout << "Total flips: " << totalFlips << endl;
            cout << "Average flips per increment: " << (double)totalFlips / n << endl;
            
            return totalFlips;
        }
    };
};
```

---

## 💰 Accounting Method (Banker's Method)

### 📝 Definition
Assign artificial costs to operations and store extra cost as credit for future expensive operations.

```cpp
class AccountingMethod {
public:
    // Dynamic Array with Accounting Method
    class DynamicArrayAccounting {
    private:
        vector<int> arr;
        int capacity;
        double totalCredit;
        
    public:
        DynamicArrayAccounting() : capacity(1), totalCredit(0) {
            arr.reserve(capacity);
        }
        
        void insert(int value) {
            // Charge 3 units per insertion
            double chargedCost = 3.0;
            double actualCost = 1.0; // Normal insertion cost
            
            if (arr.size() == capacity) {
                // Resize needed
                actualCost += capacity; // Cost of copying elements
                
                // Use stored credit for resize
                double resizeCost = capacity;
                if (totalCredit >= resizeCost) {
                    totalCredit -= resizeCost;
                    cout << "Resize cost " << resizeCost << " paid from credit" << endl;
                } else {
                    cout << "Insufficient credit for resize!" << endl;
                }
                
                capacity *= 2;
                arr.reserve(capacity);
            }
            
            arr.push_back(value);
            
            // Store excess charge as credit
            double excessCredit = chargedCost - 1.0; // 1.0 is base insertion cost
            totalCredit += excessCredit;
            
            cout << "Insert " << value << ": Charged=" << chargedCost 
                 << ", Actual=" << actualCost << ", Credit=" << totalCredit << endl;
        }
        
        void analyzeCredits() {
            cout << "Accounting Method Analysis:" << endl;
            cout << "Current size: " << arr.size() << endl;
            cout << "Current capacity: " << capacity << endl;
            cout << "Available credit: " << totalCredit << endl;
            cout << "Amortized cost per insertion: 3 units" << endl;
        }
    };
    
    // Stack with Multipop using Accounting Method
    class StackAccounting {
    private:
        stack<int> st;
        double totalCredit;
        
    public:
        StackAccounting() : totalCredit(0) {}
        
        void push(int value) {
            // Charge 2 units per push
            double chargedCost = 2.0;
            double actualCost = 1.0; // Actual push cost
            
            st.push(value);
            
            // Store 1 unit as credit for future pop
            totalCredit += 1.0;
            
            cout << "Push " << value << ": Charged=" << chargedCost 
                 << ", Credit=" << totalCredit << endl;
        }
        
        void pop() {
            if (st.empty()) return;
            
            // Use 1 unit of credit for pop
            double actualCost = 1.0;
            totalCredit -= 1.0;
            
            int value = st.top();
            st.pop();
            
            cout << "Pop " << value << ": Used 1 credit, Remaining=" << totalCredit << endl;
        }
        
        void multipop(int k) {
            cout << "Multipop " << k << " elements:" << endl;
            
            for (int i = 0; i < k && !st.empty(); i++) {
                pop();
            }
        }
        
        void analyzeCredits() {
            cout << "Stack Accounting Analysis:" << endl;
            cout << "Stack size: " << st.size() << endl;
            cout << "Available credit: " << totalCredit << endl;
            cout << "Credit should equal stack size: " << (totalCredit == st.size()) << endl;
        }
    };
};
```

---

## ⚡ Potential Method

### 📝 Definition
Uses a potential function Φ that maps data structure state to a number representing stored work.

**Formula**: Amortized Cost = Actual Cost + (Φ_after - Φ_before)

```cpp
class PotentialMethod {
public:
    // Dynamic Array with Potential Method
    class DynamicArrayPotential {
    private:
        vector<int> arr;
        int capacity;
        
        // Potential function: Φ = 2 * size - capacity
        double potential() {
            return 2.0 * arr.size() - capacity;
        }
        
    public:
        DynamicArrayPotential() : capacity(1) {
            arr.reserve(capacity);
        }
        
        double insert(int value) {
            double potentialBefore = potential();
            double actualCost = 1.0; // Base insertion cost
            
            if (arr.size() == capacity) {
                // Resize operation
                actualCost += capacity; // Cost of copying
                capacity *= 2;
                arr.reserve(capacity);
            }
            
            arr.push_back(value);
            double potentialAfter = potential();
            
            double amortizedCost = actualCost + (potentialAfter - potentialBefore);
            
            cout << "Insert " << value << ":" << endl;
            cout << "  Actual cost: " << actualCost << endl;
            cout << "  Potential before: " << potentialBefore << endl;
            cout << "  Potential after: " << potentialAfter << endl;
            cout << "  Potential change: " << (potentialAfter - potentialBefore) << endl;
            cout << "  Amortized cost: " << amortizedCost << endl;
            
            return amortizedCost;
        }
        
        void analyzePotential() {
            cout << "Potential Method Analysis:" << endl;
            cout << "Size: " << arr.size() << endl;
            cout << "Capacity: " << capacity << endl;
            cout << "Current potential: " << potential() << endl;
            cout << "Potential function: Φ = 2 * size - capacity" << endl;
        }
    };
    
    // Binary Counter with Potential Method
    class BinaryCounterPotential {
    private:
        int counter;
        
        // Potential function: number of 1 bits
        double potential() {
            return __builtin_popcount(counter);
        }
        
    public:
        BinaryCounterPotential() : counter(0) {}
        
        double increment() {
            double potentialBefore = potential();
            
            // Count bit flips (actual cost)
            int oldCounter = counter;
            counter++;
            int bitFlips = __builtin_popcount(oldCounter ^ counter);
            double actualCost = bitFlips;
            
            double potentialAfter = potential();
            double amortizedCost = actualCost + (potentialAfter - potentialBefore);
            
            cout << "Increment to " << counter << ":" << endl;
            cout << "  Bit flips (actual cost): " << actualCost << endl;
            cout << "  Potential before: " << potentialBefore << endl;
            cout << "  Potential after: " << potentialAfter << endl;
            cout << "  Amortized cost: " << amortizedCost << endl;
            
            return amortizedCost;
        }
        
        void analyzePotential() {
            cout << "Binary Counter Potential Analysis:" << endl;
            cout << "Counter value: " << counter << endl;
            cout << "Binary: " << bitset<8>(counter) << endl;
            cout << "Current potential (1-bits): " << potential() << endl;
        }
    };
    
    // Splay Tree with Potential Method
    class SplayTreePotential {
    private:
        struct Node {
            int key;
            Node* left;
            Node* right;
            int size; // Subtree size
            
            Node(int k) : key(k), left(nullptr), right(nullptr), size(1) {}
        };
        
        Node* root;
        
        // Potential function: sum of log(size) for all nodes
        double potential(Node* node) {
            if (!node) return 0;
            return log2(node->size) + potential(node->left) + potential(node->right);
        }
        
        void updateSize(Node* node) {
            if (!node) return;
            node->size = 1;
            if (node->left) node->size += node->left->size;
            if (node->right) node->size += node->right->size;
        }
        
        Node* rotateRight(Node* y) {
            Node* x = y->left;
            y->left = x->right;
            x->right = y;
            updateSize(y);
            updateSize(x);
            return x;
        }
        
        Node* rotateLeft(Node* x) {
            Node* y = x->right;
            x->right = y->left;
            y->left = x;
            updateSize(x);
            updateSize(y);
            return y;
        }
        
    public:
        SplayTreePotential() : root(nullptr) {}
        
        double splay(int key) {
            double potentialBefore = potential(root);
            int rotations = 0;
            
            // Simplified splay operation (actual implementation more complex)
            root = splayHelper(root, key, rotations);
            
            double potentialAfter = potential(root);
            double actualCost = rotations;
            double amortizedCost = actualCost + (potentialAfter - potentialBefore);
            
            cout << "Splay " << key << ":" << endl;
            cout << "  Rotations (actual cost): " << actualCost << endl;
            cout << "  Potential change: " << (potentialAfter - potentialBefore) << endl;
            cout << "  Amortized cost: " << amortizedCost << endl;
            
            return amortizedCost;
        }
        
    private:
        Node* splayHelper(Node* node, int key, int& rotations) {
            // Simplified splay implementation
            if (!node || node->key == key) return node;
            
            if (key < node->key && node->left) {
                rotations++;
                node = rotateRight(node);
            } else if (key > node->key && node->right) {
                rotations++;
                node = rotateLeft(node);
            }
            
            return node;
        }
    };
};
```

---

## 📊 Dynamic Array Analysis

### 🔄 Complete Analysis Using All Three Methods

```cpp
class DynamicArrayComplete {
public:
    // Comprehensive analysis of dynamic array operations
    void completeAnalysis(int n) {
        cout << "=== DYNAMIC ARRAY AMORTIZED ANALYSIS ===" << endl;
        cout << "Analyzing " << n << " insertions with doubling strategy" << endl;
        
        // Method 1: Aggregate Analysis
        aggregateAnalysis(n);
        cout << endl;
        
        // Method 2: Accounting Analysis
        accountingAnalysis(n);
        cout << endl;
        
        // Method 3: Potential Analysis
        potentialAnalysis(n);
        cout << endl;
        
        // Comparison
        compareResults();
    }
    
private:
    void aggregateAnalysis(int n) {
        cout << "1. AGGREGATE METHOD:" << endl;
        cout << "-------------------" << endl;
        
        // Calculate total cost
        int insertCost = n; // Each insertion costs 1
        int resizeCost = 0;
        
        // Sum of resize costs: 1 + 2 + 4 + 8 + ... < 2n
        for (int capacity = 1; capacity < n; capacity *= 2) {
            resizeCost += capacity;
        }
        
        int totalCost = insertCost + resizeCost;
        double amortizedCost = (double)totalCost / n;
        
        cout << "Insert cost: " << insertCost << endl;
        cout << "Resize cost: " << resizeCost << endl;
        cout << "Total cost: " << totalCost << endl;
        cout << "Amortized cost: " << amortizedCost << " ≤ 3" << endl;
    }
    
    void accountingAnalysis(int n) {
        cout << "2. ACCOUNTING METHOD:" << endl;
        cout << "--------------------" << endl;
        
        cout << "Charge 3 units per insertion:" << endl;
        cout << "- 1 unit for actual insertion" << endl;
        cout << "- 2 units saved as credit" << endl;
        cout << "When resize happens:" << endl;
        cout << "- Use accumulated credit to pay for copying" << endl;
        cout << "- Credit available = 2 * (size/2) = size" << endl;
        cout << "- Resize cost = size (exactly matches credit)" << endl;
        cout << "Amortized cost: 3 units per insertion" << endl;
    }
    
    void potentialAnalysis(int n) {
        cout << "3. POTENTIAL METHOD:" << endl;
        cout << "-------------------" << endl;
        
        cout << "Potential function: Φ = 2 * size - capacity" << endl;
        cout << "Normal insertion:" << endl;
        cout << "- Actual cost = 1" << endl;
        cout << "- Potential change = +2" << endl;
        cout << "- Amortized cost = 1 + 2 = 3" << endl;
        
        cout << "Resize insertion:" << endl;
        cout << "- Actual cost = 1 + size (copy cost)" << endl;
        cout << "- Potential before = 2*size - size = size" << endl;
        cout << "- Potential after = 2*(size+1) - 2*size = 2" << endl;
        cout << "- Potential change = 2 - size" << endl;
        cout << "- Amortized cost = (1 + size) + (2 - size) = 3" << endl;
    }
    
    void compareResults() {
        cout << "COMPARISON OF METHODS:" << endl;
        cout << "=====================" << endl;
        
        cout << "Method          | Amortized Cost | Difficulty | Insight" << endl;
        cout << "----------------|----------------|------------|--------" << endl;
        cout << "Aggregate       | ≤ 3           | Easy       | Total cost bound" << endl;
        cout << "Accounting      | = 3           | Medium     | Credit mechanism" << endl;
        cout << "Potential       | = 3           | Hard       | Energy function" << endl;
        
        cout << "\nAll methods prove O(1) amortized cost per insertion!" << endl;
    }
};
```

---

## 📚 Stack Operations

### 🔄 Stack with Multipop Analysis

```cpp
class StackMultipop {
private:
    stack<int> st;
    
public:
    void push(int x) {
        st.push(x);
    }
    
    int pop() {
        if (st.empty()) return -1;
        int val = st.top();
        st.pop();
        return val;
    }
    
    vector<int> multipop(int k) {
        vector<int> result;
        for (int i = 0; i < k && !st.empty(); i++) {
            result.push_back(pop());
        }
        return result;
    }
    
    // Amortized analysis of stack operations
    void analyzeOperations() {
        cout << "STACK WITH MULTIPOP ANALYSIS:" << endl;
        cout << "=============================" << endl;
        
        // Aggregate Method
        cout << "Aggregate Method:" << endl;
        cout << "- Each element pushed at most once" << endl;
        cout << "- Each element popped at most once" << endl;
        cout << "- Total cost for n operations ≤ 2n" << endl;
        cout << "- Amortized cost = O(1) per operation" << endl;
        
        // Accounting Method
        cout << "\nAccounting Method:" << endl;
        cout << "- Charge 2 units for push operation" << endl;
        cout << "- 1 unit for actual push, 1 unit as credit" << endl;
        cout << "- Pop operations use stored credit" << endl;
        cout << "- Amortized cost: Push = 2, Pop = 0" << endl;
        
        // Potential Method
        cout << "\nPotential Method:" << endl;
        cout << "- Potential function: Φ = stack size" << endl;
        cout << "- Push: actual cost = 1, potential change = +1" << endl;
        cout << "- Amortized push cost = 1 + 1 = 2" << endl;
        cout << "- Pop: actual cost = 1, potential change = -1" << endl;
        cout << "- Amortized pop cost = 1 + (-1) = 0" << endl;
    }
    
    // Demonstrate with actual operations
    void demonstrateOperations() {
        cout << "\nDEMONSTRATION:" << endl;
        cout << "==============" << endl;
        
        // Push operations
        for (int i = 1; i <= 5; i++) {
            push(i);
            cout << "Push " << i << ", stack size: " << st.size() << endl;
        }
        
        // Multipop operation
        cout << "\nMultipop 3 elements:" << endl;
        vector<int> popped = multipop(3);
        cout << "Popped: ";
        for (int x : popped) cout << x << " ";
        cout << "\nStack size after multipop: " << st.size() << endl;
        
        // Analysis
        cout << "\nTotal operations: 5 pushes + 1 multipop(3)" << endl;
        cout << "Total actual cost: 5 (pushes) + 3 (pops) = 8" << endl;
        cout << "Amortized analysis: 5 * 2 (push) + 3 * 0 (pop) = 10" << endl;
        cout << "Amortized bound holds: 10 ≥ 8" << endl;
    }
};
```

---

## 🎯 Interview Problems

### Problem 1: Implement Dynamic Array with Analysis
```cpp
class AnalyzedDynamicArray {
private:
    int* arr;
    int size;
    int capacity;
    int totalOperations;
    int totalCost;
    
public:
    AnalyzedDynamicArray() : size(0), capacity(1), totalOperations(0), totalCost(0) {
        arr = new int[capacity];
    }
    
    ~AnalyzedDynamicArray() {
        delete[] arr;
    }
    
    void push_back(int value) {
        totalOperations++;
        int operationCost = 1; // Base insertion cost
        
        if (size == capacity) {
            // Resize needed
            int* newArr = new int[capacity * 2];
            
            // Copy elements (additional cost)
            for (int i = 0; i < size; i++) {
                newArr[i] = arr[i];
                operationCost++; // Cost of copying each element
            }
            
            delete[] arr;
            arr = newArr;
            capacity *= 2;
            
            cout << "Resize at operation " << totalOperations 
                 << ", cost: " << operationCost << endl;
        }
        
        arr[size++] = value;
        totalCost += operationCost;
        
        if (operationCost > 1) {
            cout << "Operation " << totalOperations << ": cost = " << operationCost << endl;
        }
    }
    
    void printAnalysis() {
        cout << "\nDynamic Array Analysis:" << endl;
        cout << "Total operations: " << totalOperations << endl;
        cout << "Total cost: " << totalCost << endl;
        cout << "Amortized cost: " << (double)totalCost / totalOperations << endl;
        cout << "Current size: " << size << endl;
        cout << "Current capacity: " << capacity << endl;
    }
    
    // Test with different growth strategies
    void compareGrowthStrategies() {
        cout << "Growth Strategy Comparison:" << endl;
        cout << "==========================" << endl;
        
        // Doubling strategy
        cout << "Doubling (×2): Amortized O(1)" << endl;
        cout << "- Resize costs: 1, 2, 4, 8, ..., n/2" << endl;
        cout << "- Total resize cost ≤ 2n" << endl;
        
        // Increment strategy
        cout << "Increment (+k): Amortized O(n)" << endl;
        cout << "- Resize costs: k, 2k, 3k, ..., nk" << endl;
        cout << "- Total resize cost = O(n²)" << endl;
        
        // Golden ratio strategy
        cout << "Golden ratio (×φ): Amortized O(1)" << endl;
        cout << "- φ = (1+√5)/2 ≈ 1.618" << endl;
        cout << "- Better space utilization than doubling" << endl;
    }
};
```

### Problem 2: Fibonacci Heap Operations
```cpp
class FibonacciHeapAnalysis {
public:
    // Simplified Fibonacci Heap for analysis
    struct Node {
        int key;
        int degree;
        bool marked;
        Node* parent;
        Node* child;
        Node* left;
        Node* right;
        
        Node(int k) : key(k), degree(0), marked(false), 
                     parent(nullptr), child(nullptr), left(this), right(this) {}
    };
    
private:
    Node* minNode;
    int numNodes;
    
    // Potential function: Φ = trees + 2 * marked_nodes
    int potential() {
        return countTrees() + 2 * countMarkedNodes();
    }
    
    int countTrees() {
        if (!minNode) return 0;
        
        int count = 1;
        Node* current = minNode->right;
        while (current != minNode) {
            count++;
            current = current->right;
        }
        return count;
    }
    
    int countMarkedNodes() {
        // Simplified counting (actual implementation would traverse all nodes)
        return 0; // Placeholder
    }
    
public:
    FibonacciHeapAnalysis() : minNode(nullptr), numNodes(0) {}
    
    // Insert operation analysis
    double insert(int key) {
        int potentialBefore = potential();
        
        Node* newNode = new Node(key);
        
        if (!minNode) {
            minNode = newNode;
        } else {
            // Add to root list
            newNode->right = minNode->right;
            newNode->left = minNode;
            minNode->right->left = newNode;
            minNode->right = newNode;
            
            if (key < minNode->key) {
                minNode = newNode;
            }
        }
        
        numNodes++;
        
        int potentialAfter = potential();
        int actualCost = 1; // O(1) actual work
        double amortizedCost = actualCost + (potentialAfter - potentialBefore);
        
        cout << "Insert " << key << ":" << endl;
        cout << "  Actual cost: " << actualCost << endl;
        cout << "  Potential change: " << (potentialAfter - potentialBefore) << endl;
        cout << "  Amortized cost: " << amortizedCost << endl;
        
        return amortizedCost;
    }
    
    // Extract-min operation analysis
    double extractMin() {
        if (!minNode) return 0;
        
        int potentialBefore = potential();
        
        // Actual work: O(D(n)) where D(n) is max degree
        int actualCost = log2(numNodes) + 1; // Simplified
        
        // Simplified extract-min (actual implementation more complex)
        Node* oldMin = minNode;
        
        // Add children to root list and find new minimum
        // ... complex consolidation process ...
        
        numNodes--;
        
        int potentialAfter = potential();
        double amortizedCost = actualCost + (potentialAfter - potentialBefore);
        
        cout << "Extract-min:" << endl;
        cout << "  Actual cost: " << actualCost << endl;
        cout << "  Potential change: " << (potentialAfter - potentialBefore) << endl;
        cout << "  Amortized cost: " << amortizedCost << endl;
        
        return amortizedCost;
    }
    
    void analyzeComplexity() {
        cout << "Fibonacci Heap Amortized Analysis:" << endl;
        cout << "==================================" << endl;
        cout << "Operation     | Actual    | Amortized" << endl;
        cout << "--------------|-----------|----------" << endl;
        cout << "Insert        | O(1)      | O(1)" << endl;
        cout << "Find-min      | O(1)      | O(1)" << endl;
        cout << "Extract-min   | O(n)      | O(log n)" << endl;
        cout << "Decrease-key  | O(n)      | O(1)" << endl;
        cout << "Delete        | O(n)      | O(log n)" << endl;
        
        cout << "\nPotential function: Φ = trees + 2 * marked_nodes" << endl;
        cout << "Key insight: Expensive operations reduce potential" << endl;
    }
};
```

### Problem 3: Disjoint Set Union with Path Compression
```cpp
class DisjointSetAnalysis {
private:
    vector<int> parent;
    vector<int> rank;
    int numSets;
    
public:
    DisjointSetAnalysis(int n) : parent(n), rank(n, 0), numSets(n) {
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    
    // Find with path compression
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]); // Path compression
        }
        return parent[x];
    }
    
    // Union by rank
    void unionSets(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        
        if (rootX != rootY) {
            if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
            numSets--;
        }
    }
    
    void analyzeComplexity() {
        cout << "Disjoint Set Union Analysis:" << endl;
        cout << "============================" << endl;
        
        cout << "Without optimization:" << endl;
        cout << "- Find: O(n) worst case" << endl;
        cout << "- Union: O(n) worst case" << endl;
        
        cout << "\nWith Union by Rank:" << endl;
        cout << "- Tree height ≤ log n" << endl;
        cout << "- Find: O(log n)" << endl;
        cout << "- Union: O(log n)" << endl;
        
        cout << "\nWith Path Compression:" << endl;
        cout << "- Flattens paths during find" << endl;
        cout << "- Amortized analysis needed" << endl;
        
        cout << "\nWith Both Optimizations:" << endl;
        cout << "- Amortized time: O(α(n)) per operation" << endl;
        cout << "- α(n) is inverse Ackermann function" << endl;
        cout << "- Practically constant: α(n) ≤ 4 for all practical n" << endl;
        
        cout << "\nInverse Ackermann Growth:" << endl;
        cout << "α(16) = 3, α(65536) = 4, α(2^65536) = 5" << endl;
    }
    
    // Demonstrate path compression effect
    void demonstratePathCompression() {
        cout << "\nPath Compression Demonstration:" << endl;
        cout << "===============================" << endl;
        
        // Create a chain: 0 -> 1 -> 2 -> 3 -> 4
        for (int i = 1; i < 5; i++) {
            parent[i] = i - 1;
        }
        
        cout << "Initial chain: 4 -> 3 -> 2 -> 1 -> 0" << endl;
        cout << "Find(4) traverses 4 nodes" << endl;
        
        int root = find(4);
        cout << "After find(4), path compressed:" << endl;
        cout << "All nodes point directly to root " << root << endl;
        
        cout << "Subsequent find operations: O(1)" << endl;
    }
};
```

---

## 💡 Best Practices

### 🎯 Choosing the Right Method
```cpp
class AmortizedAnalysisBestPractices {
public:
    void chooseMethod() {
        cout << "Choosing Amortized Analysis Method:" << endl;
        cout << "==================================" << endl;
        
        cout << "Use Aggregate Method when:" << endl;
        cout << "- Simple total cost calculation" << endl;
        cout << "- All operations have similar structure" << endl;
        cout << "- Quick rough analysis needed" << endl;
        
        cout << "\nUse Accounting Method when:" << endl;
        cout << "- Operations have clear cost relationships" << endl;
        cout << "- Intuitive credit/debit model applies" << endl;
        cout << "- Need to explain cost distribution" << endl;
        
        cout << "\nUse Potential Method when:" << endl;
        cout << "- Complex data structure state changes" << endl;
        cout << "- Need rigorous mathematical proof" << endl;
        cout << "- Other methods are insufficient" << endl;
    }
    
    void commonPitfalls() {
        cout << "\nCommon Pitfalls:" << endl;
        cout << "================" << endl;
        
        cout << "1. Negative potential:" << endl;
        cout << "   - Ensure Φ(initial) = 0 and Φ(any state) ≥ 0" << endl;
        
        cout << "2. Insufficient credits:" << endl;
        cout << "   - Credits must never go negative" << endl;
        cout << "   - Verify credit balance for all operation sequences" << endl;
        
        cout << "3. Wrong potential function:" << endl;
        cout << "   - Must reflect actual work stored in structure" << endl;
        cout << "   - Should decrease when expensive operations occur" << endl;
        
        cout << "4. Confusing amortized with average:" << endl;
        cout << "   - Amortized: guaranteed bound over any sequence" << endl;
        cout << "   - Average: expected over random inputs" << endl;
    }
    
    void designGuidelines() {
        cout << "\nDesign Guidelines:" << endl;
        cout << "==================" << endl;
        
        cout << "1. Identify expensive operations" << endl;
        cout << "2. Find what makes them expensive" << endl;
        cout << "3. Determine how to 'pay' for expensive operations" << endl;
        cout << "4. Choose appropriate analysis method" << endl;
        cout << "5. Verify bounds hold for all sequences" << endl;
        
        cout << "\nPotential Function Design:" << endl;
        cout << "- Should be 0 initially" << endl;
        cout << "- Should be non-negative always" << endl;
        cout << "- Should increase with 'stored work'" << endl;
        cout << "- Should decrease when work is 'released'" << endl;
    }
};
```

---

## 📊 Complexity Analysis

### ⏰ Time Complexity Summary
- **Dynamic Array**: O(1) amortized insertion
- **Stack with Multipop**: O(1) amortized per operation
- **Binary Counter**: O(1) amortized increment
- **Splay Trees**: O(log n) amortized access
- **Fibonacci Heap**: O(1) amortized insert/decrease-key

### 💾 Space Complexity
- **Analysis overhead**: O(1) additional space
- **Potential tracking**: Usually implicit in data structure
- **Credit storage**: Conceptual, no actual storage needed

### 🎯 Practical Applications
- **Dynamic arrays**: std::vector, ArrayList
- **Hash tables**: Resizing operations
- **Garbage collection**: Mark-and-sweep analysis
- **Database systems**: B-tree operations

---

## 🌟 Key Takeaways

1. **Guaranteed Performance**: Amortized analysis provides worst-case guarantees over sequences
2. **Three Methods**: Aggregate, Accounting, and Potential each have their strengths
3. **Real-World Relevance**: Many practical data structures rely on amortized bounds
4. **Design Tool**: Helps optimize data structure operations
5. **Interview Importance**: Common topic in technical interviews

### 🎯 Interview Quick Reference
- **Amortized Analysis**: Average cost over sequence of operations
- **Aggregate Method**: Total cost divided by number of operations
- **Accounting Method**: Prepay cheap operations for expensive ones
- **Potential Method**: Use potential function to track stored work
- **Dynamic Array**: Classic example with O(1) amortized insertion
- **Key Insight**: Expensive operations are rare and balanced by cheap ones

---

*Master amortized analysis to understand and design efficient data structures with guaranteed performance! ⚖️*