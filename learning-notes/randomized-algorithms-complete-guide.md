# 🎲 Randomized Algorithms Complete Guide

## 📋 Table of Contents
- [Introduction](#introduction)
- [Types of Randomized Algorithms](#types-of-randomized-algorithms)
- [Monte Carlo Algorithms](#monte-carlo-algorithms)
- [Las Vegas Algorithms](#las-vegas-algorithms)
- [Randomized Sorting](#randomized-sorting)
- [Randomized Selection](#randomized-selection)
- [Probabilistic Data Structures](#probabilistic-data-structures)
- [Applications in Practice](#applications-in-practice)
- [Analysis Techniques](#analysis-techniques)
- [Interview Problems](#interview-problems)
- [Best Practices](#best-practices)

---

## 🎯 Introduction

**Randomized Algorithms** use random numbers to make decisions during execution, providing elegant solutions to complex problems while avoiding worst-case scenarios through probabilistic guarantees.

### 🔑 Key Principles
- **Random Choices**: Use randomness to guide algorithm decisions
- **Probabilistic Analysis**: Expected performance rather than worst-case
- **Worst-Case Avoidance**: Eliminate adversarial input scenarios
- **Simplicity**: Often simpler than deterministic counterparts

### 🌟 Why Randomization?
- **Performance**: Better average-case complexity
- **Robustness**: Resistant to malicious inputs
- **Simplicity**: Elegant solutions to hard problems
- **Practical**: Excellent real-world performance

---

## 🎭 Types of Randomized Algorithms

### 🎰 Monte Carlo Algorithms
**Fixed time, probabilistic correctness**

```cpp
class MonteCarloAlgorithm {
public:
    // Template for Monte Carlo algorithms
    template<typename Input, typename Output>
    Output monteCarloSolve(Input& input, double errorProbability) {
        // Fixed number of iterations
        int iterations = calculateIterations(errorProbability);
        
        for (int i = 0; i < iterations; i++) {
            Output candidate = randomizedSolution(input);
            if (isGoodEnough(candidate, input)) {
                return candidate;
            }
        }
        
        // Return best effort (may be incorrect)
        return getBestEffort(input);
    }
    
    // Reduce error probability by repetition
    template<typename Input, typename Output>
    Output amplifyCorrectness(Input& input, double targetError) {
        int repetitions = ceil(log(targetError) / log(0.5)); // For 1/2 error
        
        map<Output, int> votes;
        for (int i = 0; i < repetitions; i++) {
            Output result = monteCarloSolve(input, 0.5);
            votes[result]++;
        }
        
        // Return majority vote
        return getMajorityVote(votes);
    }
    
private:
    virtual int calculateIterations(double errorProb) = 0;
    virtual bool isGoodEnough(const Output& candidate, const Input& input) = 0;
};
```

### 🎯 Las Vegas Algorithms
**Always correct, random time**

```cpp
class LasVegasAlgorithm {
public:
    // Template for Las Vegas algorithms
    template<typename Input, typename Output>
    Output lasVegasSolve(Input& input) {
        while (true) {
            Output candidate = randomizedAttempt(input);
            if (isCorrect(candidate, input)) {
                return candidate; // Always correct when returned
            }
            // Retry with different randomization
        }
    }
    
    // Expected time analysis
    double expectedTime(double successProbability) {
        return 1.0 / successProbability; // Geometric distribution
    }
    
private:
    virtual Output randomizedAttempt(const Input& input) = 0;
    virtual bool isCorrect(const Output& candidate, const Input& input) = 0;
};
```

### 📊 Comparison Framework

```cpp
class AlgorithmComparison {
public:
    void compareRandomizedTypes() {
        cout << "Monte Carlo vs Las Vegas Algorithms:" << endl;
        cout << "====================================" << endl;
        
        cout << "Correctness:" << endl;
        cout << "  Monte Carlo: Probabilistic (may be wrong)" << endl;
        cout << "  Las Vegas: Always correct" << endl;
        
        cout << "Running Time:" << endl;
        cout << "  Monte Carlo: Fixed/Bounded" << endl;
        cout << "  Las Vegas: Random (expected bound)" << endl;
        
        cout << "Error Handling:" << endl;
        cout << "  Monte Carlo: Accept small error probability" << endl;
        cout << "  Las Vegas: No errors, but time varies" << endl;
        
        cout << "Use Cases:" << endl;
        cout << "  Monte Carlo: Approximation, when speed matters" << endl;
        cout << "  Las Vegas: When correctness is mandatory" << endl;
    }
};
```

---

## 🎰 Monte Carlo Algorithms

### 🔢 Miller-Rabin Primality Test
**Probabilistic primality testing**

```cpp
class MillerRabinTest {
private:
    // Fast modular exponentiation
    long long modPow(long long base, long long exp, long long mod) {
        long long result = 1;
        base %= mod;
        
        while (exp > 0) {
            if (exp & 1) result = (result * base) % mod;
            base = (base * base) % mod;
            exp >>= 1;
        }
        
        return result;
    }
    
    // Single Miller-Rabin test
    bool millerRabinSingle(long long n, long long a) {
        if (n <= 1) return false;
        if (n == 2) return true;
        if (n % 2 == 0) return false;
        
        // Write n-1 as d * 2^r
        long long d = n - 1;
        int r = 0;
        while (d % 2 == 0) {
            d /= 2;
            r++;
        }
        
        // Compute a^d mod n
        long long x = modPow(a, d, n);
        if (x == 1 || x == n - 1) return true;
        
        // Square x repeatedly
        for (int i = 0; i < r - 1; i++) {
            x = (x * x) % n;
            if (x == n - 1) return true;
        }
        
        return false;
    }
    
public:
    // Monte Carlo primality test
    bool isProbablyPrime(long long n, int k = 10) {
        if (n <= 1) return false;
        if (n <= 3) return true;
        if (n % 2 == 0) return false;
        
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<long long> dis(2, n - 2);
        
        // Perform k rounds of testing
        for (int i = 0; i < k; i++) {
            long long a = dis(gen);
            if (!millerRabinSingle(n, a)) {
                return false; // Definitely composite
            }
        }
        
        return true; // Probably prime (error ≤ 4^(-k))
    }
    
    // Calculate error probability
    double errorProbability(int rounds) {
        return pow(0.25, rounds); // 4^(-k)
    }
    
    // Determine rounds needed for target error
    int roundsForError(double targetError) {
        return ceil(log(targetError) / log(0.25));
    }
};

// Usage Example
void testPrimality() {
    MillerRabinTest tester;
    
    vector<long long> candidates = {97, 100, 1009, 1013, 982451653};
    
    for (long long n : candidates) {
        bool isPrime = tester.isProbablyPrime(n, 20);
        double error = tester.errorProbability(20);
        
        cout << n << " is " << (isPrime ? "probably prime" : "composite")
             << " (error probability: " << error << ")" << endl;
    }
}
```

### 🎯 Monte Carlo Integration
**Numerical integration using random sampling**

```cpp
class MonteCarloIntegration {
public:
    // Estimate integral using random sampling
    double integrate(function<double(double)> f, double a, double b, int samples) {
        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<double> dis(a, b);
        
        double sum = 0.0;
        for (int i = 0; i < samples; i++) {
            double x = dis(gen);
            sum += f(x);
        }
        
        return (b - a) * sum / samples;
    }
    
    // Estimate π using unit circle
    double estimatePi(int samples) {
        random_device rd;
        mt19937 gen(rd());
        uniform_real_distribution<double> dis(-1.0, 1.0);
        
        int insideCircle = 0;
        for (int i = 0; i < samples; i++) {
            double x = dis(gen);
            double y = dis(gen);
            
            if (x * x + y * y <= 1.0) {
                insideCircle++;
            }
        }
        
        return 4.0 * insideCircle / samples;
    }
    
    // Multi-dimensional integration
    double integrateND(function<double(vector<double>&)> f, 
                      vector<pair<double, double>>& bounds, int samples) {
        int dimensions = bounds.size();
        random_device rd;
        mt19937 gen(rd());
        
        vector<uniform_real_distribution<double>> distributions;
        double volume = 1.0;
        
        for (auto& bound : bounds) {
            distributions.emplace_back(bound.first, bound.second);
            volume *= (bound.second - bound.first);
        }
        
        double sum = 0.0;
        vector<double> point(dimensions);
        
        for (int i = 0; i < samples; i++) {
            for (int d = 0; d < dimensions; d++) {
                point[d] = distributions[d](gen);
            }
            sum += f(point);
        }
        
        return volume * sum / samples;
    }
};
```

### 🎲 Randomized SAT Solver
**Monte Carlo approach to Boolean satisfiability**

```cpp
class RandomizedSAT {
private:
    struct Clause {
        vector<int> literals; // Positive: variable, Negative: -variable
    };
    
public:
    // Monte Carlo SAT solver
    vector<bool> solveSAT(vector<Clause>& formula, int numVars, 
                         int maxTries = 1000, int maxFlips = 10000) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> varDis(0, numVars - 1);
        uniform_real_distribution<double> probDis(0.0, 1.0);
        
        for (int try_count = 0; try_count < maxTries; try_count++) {
            // Random initial assignment
            vector<bool> assignment(numVars);
            for (int i = 0; i < numVars; i++) {
                assignment[i] = probDis(gen) < 0.5;
            }
            
            // Local search with random flips
            for (int flip = 0; flip < maxFlips; flip++) {
                vector<int> unsatisfied = getUnsatisfiedClauses(formula, assignment);
                
                if (unsatisfied.empty()) {
                    return assignment; // Solution found
                }
                
                // Pick random unsatisfied clause
                int clauseIdx = unsatisfied[gen() % unsatisfied.size()];
                Clause& clause = formula[clauseIdx];
                
                // Pick random literal from clause and flip it
                int literalIdx = gen() % clause.literals.size();
                int literal = clause.literals[literalIdx];
                int var = abs(literal) - 1;
                
                assignment[var] = !assignment[var];
            }
        }
        
        return vector<bool>(); // No solution found
    }
    
private:
    vector<int> getUnsatisfiedClauses(vector<Clause>& formula, vector<bool>& assignment) {
        vector<int> unsatisfied;
        
        for (int i = 0; i < formula.size(); i++) {
            if (!evaluateClause(formula[i], assignment)) {
                unsatisfied.push_back(i);
            }
        }
        
        return unsatisfied;
    }
    
    bool evaluateClause(Clause& clause, vector<bool>& assignment) {
        for (int literal : clause.literals) {
            int var = abs(literal) - 1;
            bool value = assignment[var];
            
            if ((literal > 0 && value) || (literal < 0 && !value)) {
                return true;
            }
        }
        return false;
    }
};
```

---

## 🎯 Las Vegas Algorithms

### 🔄 Randomized QuickSort
**Always correct, expected O(n log n)**

```cpp
class RandomizedQuickSort {
private:
    random_device rd;
    mt19937 gen;
    
public:
    RandomizedQuickSort() : gen(rd()) {}
    
    void quickSort(vector<int>& arr, int low, int high) {
        if (low < high) {
            int pivotIndex = randomizedPartition(arr, low, high);
            quickSort(arr, low, pivotIndex - 1);
            quickSort(arr, pivotIndex + 1, high);
        }
    }
    
    void sort(vector<int>& arr) {
        quickSort(arr, 0, arr.size() - 1);
    }
    
private:
    int randomizedPartition(vector<int>& arr, int low, int high) {
        // Choose random pivot
        uniform_int_distribution<int> dis(low, high);
        int randomIndex = dis(gen);
        
        // Swap random element with last element
        swap(arr[randomIndex], arr[high]);
        
        // Standard partition with last element as pivot
        return partition(arr, low, high);
    }
    
    int partition(vector<int>& arr, int low, int high) {
        int pivot = arr[high];
        int i = low - 1;
        
        for (int j = low; j < high; j++) {
            if (arr[j] <= pivot) {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        
        swap(arr[i + 1], arr[high]);
        return i + 1;
    }
};

// Performance analysis
class QuickSortAnalysis {
public:
    // Expected number of comparisons
    double expectedComparisons(int n) {
        if (n <= 1) return 0;
        return 2 * (n + 1) * harmonicNumber(n + 1) - 4 * n;
    }
    
    // Probability of worst-case
    double worstCaseProbability(int n) {
        return 1.0 / factorial(n); // Very small for large n
    }
    
private:
    double harmonicNumber(int n) {
        double sum = 0.0;
        for (int i = 1; i <= n; i++) {
            sum += 1.0 / i;
        }
        return sum;
    }
    
    double factorial(int n) {
        double result = 1.0;
        for (int i = 2; i <= n; i++) {
            result *= i;
        }
        return result;
    }
};
```

### 🎯 Randomized Selection (QuickSelect)
**Find k-th smallest element in expected O(n)**

```cpp
class RandomizedSelection {
private:
    random_device rd;
    mt19937 gen;
    
public:
    RandomizedSelection() : gen(rd()) {}
    
    int quickSelect(vector<int>& arr, int k) {
        return quickSelectHelper(arr, 0, arr.size() - 1, k - 1);
    }
    
    // Find k-th smallest (0-indexed)
    int quickSelectHelper(vector<int>& arr, int low, int high, int k) {
        if (low == high) return arr[low];
        
        int pivotIndex = randomizedPartition(arr, low, high);
        
        if (k == pivotIndex) {
            return arr[k];
        } else if (k < pivotIndex) {
            return quickSelectHelper(arr, low, pivotIndex - 1, k);
        } else {
            return quickSelectHelper(arr, pivotIndex + 1, high, k);
        }
    }
    
    // Find median
    int findMedian(vector<int>& arr) {
        int n = arr.size();
        return quickSelect(arr, (n + 1) / 2);
    }
    
    // Find multiple order statistics
    vector<int> findOrderStatistics(vector<int>& arr, vector<int>& ranks) {
        vector<int> result;
        vector<int> temp = arr; // Work on copy
        
        for (int rank : ranks) {
            result.push_back(quickSelect(temp, rank));
        }
        
        return result;
    }
    
private:
    int randomizedPartition(vector<int>& arr, int low, int high) {
        uniform_int_distribution<int> dis(low, high);
        int randomIndex = dis(gen);
        
        swap(arr[randomIndex], arr[high]);
        return partition(arr, low, high);
    }
    
    int partition(vector<int>& arr, int low, int high) {
        int pivot = arr[high];
        int i = low - 1;
        
        for (int j = low; j < high; j++) {
            if (arr[j] <= pivot) {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        
        swap(arr[i + 1], arr[high]);
        return i + 1;
    }
};

// Usage Example
void testRandomizedSelection() {
    RandomizedSelection selector;
    vector<int> arr = {3, 6, 8, 10, 1, 2, 1};
    
    cout << "Array: ";
    for (int x : arr) cout << x << " ";
    cout << endl;
    
    cout << "3rd smallest: " << selector.quickSelect(arr, 3) << endl;
    cout << "Median: " << selector.findMedian(arr) << endl;
    
    vector<int> ranks = {1, 3, 5};
    vector<int> orderStats = selector.findOrderStatistics(arr, ranks);
    
    cout << "Order statistics: ";
    for (int x : orderStats) cout << x << " ";
    cout << endl;
}
```

---

## 📊 Probabilistic Data Structures

### 🎲 Bloom Filter
**Space-efficient probabilistic membership testing**

```cpp
class BloomFilter {
private:
    vector<bool> bitArray;
    int size;
    int numHashes;
    vector<hash<string>> hashFunctions;
    
public:
    BloomFilter(int expectedElements, double falsePositiveRate) {
        // Calculate optimal size and number of hash functions
        size = ceil(-expectedElements * log(falsePositiveRate) / (log(2) * log(2)));
        numHashes = ceil(size * log(2) / expectedElements);
        
        bitArray.resize(size, false);
        hashFunctions.resize(numHashes);
    }
    
    void insert(const string& item) {
        for (int i = 0; i < numHashes; i++) {
            int hashValue = hashFunctions[i](item + to_string(i)) % size;
            bitArray[hashValue] = true;
        }
    }
    
    bool mightContain(const string& item) {
        for (int i = 0; i < numHashes; i++) {
            int hashValue = hashFunctions[i](item + to_string(i)) % size;
            if (!bitArray[hashValue]) {
                return false; // Definitely not present
            }
        }
        return true; // Might be present
    }
    
    double actualFalsePositiveRate(int insertedElements) {
        double p = 1.0 - exp(-numHashes * insertedElements / (double)size);
        return pow(p, numHashes);
    }
    
    void getStatistics() {
        int setBits = count(bitArray.begin(), bitArray.end(), true);
        cout << "Bloom Filter Statistics:" << endl;
        cout << "Size: " << size << " bits" << endl;
        cout << "Hash functions: " << numHashes << endl;
        cout << "Set bits: " << setBits << " (" << (100.0 * setBits / size) << "%)" << endl;
    }
};
```

### 🎯 Skip List
**Probabilistic balanced search structure**

```cpp
class SkipList {
private:
    struct Node {
        int value;
        vector<Node*> forward;
        
        Node(int val, int level) : value(val), forward(level + 1, nullptr) {}
    };
    
    Node* header;
    int maxLevel;
    int currentLevel;
    double probability;
    random_device rd;
    mt19937 gen;
    uniform_real_distribution<double> dis;
    
public:
    SkipList(int maxLvl = 16, double p = 0.5) 
        : maxLevel(maxLvl), currentLevel(0), probability(p), gen(rd()), dis(0.0, 1.0) {
        header = new Node(-1, maxLevel);
    }
    
    int randomLevel() {
        int level = 0;
        while (dis(gen) < probability && level < maxLevel) {
            level++;
        }
        return level;
    }
    
    void insert(int value) {
        vector<Node*> update(maxLevel + 1);
        Node* current = header;
        
        // Find position to insert
        for (int i = currentLevel; i >= 0; i--) {
            while (current->forward[i] && current->forward[i]->value < value) {
                current = current->forward[i];
            }
            update[i] = current;
        }
        
        current = current->forward[0];
        
        if (!current || current->value != value) {
            int newLevel = randomLevel();
            
            if (newLevel > currentLevel) {
                for (int i = currentLevel + 1; i <= newLevel; i++) {
                    update[i] = header;
                }
                currentLevel = newLevel;
            }
            
            Node* newNode = new Node(value, newLevel);
            
            for (int i = 0; i <= newLevel; i++) {
                newNode->forward[i] = update[i]->forward[i];
                update[i]->forward[i] = newNode;
            }
        }
    }
    
    bool search(int value) {
        Node* current = header;
        
        for (int i = currentLevel; i >= 0; i--) {
            while (current->forward[i] && current->forward[i]->value < value) {
                current = current->forward[i];
            }
        }
        
        current = current->forward[0];
        return current && current->value == value;
    }
    
    void remove(int value) {
        vector<Node*> update(maxLevel + 1);
        Node* current = header;
        
        for (int i = currentLevel; i >= 0; i--) {
            while (current->forward[i] && current->forward[i]->value < value) {
                current = current->forward[i];
            }
            update[i] = current;
        }
        
        current = current->forward[0];
        
        if (current && current->value == value) {
            for (int i = 0; i <= currentLevel; i++) {
                if (update[i]->forward[i] != current) break;
                update[i]->forward[i] = current->forward[i];
            }
            
            delete current;
            
            while (currentLevel > 0 && !header->forward[currentLevel]) {
                currentLevel--;
            }
        }
    }
    
    void display() {
        for (int i = currentLevel; i >= 0; i--) {
            cout << "Level " << i << ": ";
            Node* current = header->forward[i];
            while (current) {
                cout << current->value << " ";
                current = current->forward[i];
            }
            cout << endl;
        }
    }
};
```

---

## 🎯 Interview Problems

### Problem 1: Reservoir Sampling
```cpp
class ReservoirSampling {
public:
    // Sample k elements from stream of unknown size
    vector<int> reservoirSample(vector<int>& stream, int k) {
        vector<int> reservoir(k);
        random_device rd;
        mt19937 gen(rd());
        
        // Fill reservoir with first k elements
        for (int i = 0; i < k && i < stream.size(); i++) {
            reservoir[i] = stream[i];
        }
        
        // Process remaining elements
        for (int i = k; i < stream.size(); i++) {
            uniform_int_distribution<int> dis(0, i);
            int j = dis(gen);
            
            if (j < k) {
                reservoir[j] = stream[i];
            }
        }
        
        return reservoir;
    }
    
    // Online version for streaming data
    class OnlineReservoir {
    private:
        vector<int> reservoir;
        int k, n;
        mt19937 gen;
        
    public:
        OnlineReservoir(int size) : k(size), n(0), gen(random_device{}()) {
            reservoir.resize(k);
        }
        
        void addElement(int element) {
            if (n < k) {
                reservoir[n] = element;
            } else {
                uniform_int_distribution<int> dis(0, n);
                int j = dis(gen);
                if (j < k) {
                    reservoir[j] = element;
                }
            }
            n++;
        }
        
        vector<int> getSample() {
            return vector<int>(reservoir.begin(), reservoir.begin() + min(k, n));
        }
    };
};
```

### Problem 2: Randomized Load Balancing
```cpp
class RandomizedLoadBalancer {
private:
    vector<int> serverLoads;
    int numServers;
    mt19937 gen;
    
public:
    RandomizedLoadBalancer(int servers) : numServers(servers), gen(random_device{}()) {
        serverLoads.resize(servers, 0);
    }
    
    // Simple random assignment
    int assignRandom() {
        uniform_int_distribution<int> dis(0, numServers - 1);
        int server = dis(gen);
        serverLoads[server]++;
        return server;
    }
    
    // Power of two choices
    int assignPowerOfTwo() {
        uniform_int_distribution<int> dis(0, numServers - 1);
        
        int server1 = dis(gen);
        int server2 = dis(gen);
        
        // Choose server with lower load
        int chosen = (serverLoads[server1] <= serverLoads[server2]) ? server1 : server2;
        serverLoads[chosen]++;
        return chosen;
    }
    
    // Weighted random selection
    int assignWeighted(vector<double>& weights) {
        discrete_distribution<int> dis(weights.begin(), weights.end());
        int server = dis(gen);
        serverLoads[server]++;
        return server;
    }
    
    void printLoadDistribution() {
        cout << "Server loads: ";
        for (int load : serverLoads) {
            cout << load << " ";
        }
        cout << endl;
        
        double variance = calculateVariance();
        cout << "Load variance: " << variance << endl;
    }
    
private:
    double calculateVariance() {
        double mean = accumulate(serverLoads.begin(), serverLoads.end(), 0.0) / numServers;
        double variance = 0.0;
        
        for (int load : serverLoads) {
            variance += (load - mean) * (load - mean);
        }
        
        return variance / numServers;
    }
};
```

### Problem 3: Randomized Graph Algorithms
```cpp
class RandomizedGraphAlgorithms {
public:
    // Randomized minimum cut (Karger's algorithm)
    int kargerMinCut(vector<vector<int>>& graph) {
        int n = graph.size();
        vector<vector<int>> adj = graph;
        random_device rd;
        mt19937 gen(rd());
        
        // Contract edges until 2 vertices remain
        while (n > 2) {
            // Choose random edge
            vector<pair<int, int>> edges;
            for (int i = 0; i < adj.size(); i++) {
                for (int j = i + 1; j < adj.size(); j++) {
                    for (int k = 0; k < adj[i][j]; k++) {
                        edges.push_back({i, j});
                    }
                }
            }
            
            if (edges.empty()) break;
            
            uniform_int_distribution<int> dis(0, edges.size() - 1);
            auto [u, v] = edges[dis(gen)];
            
            // Contract edge (u, v)
            contractEdge(adj, u, v);
            n--;
        }
        
        // Count remaining edges
        int minCut = 0;
        for (int i = 0; i < adj.size(); i++) {
            for (int j = i + 1; j < adj.size(); j++) {
                minCut += adj[i][j];
            }
        }
        
        return minCut;
    }
    
    // Randomized graph coloring
    vector<int> randomizedColoring(vector<vector<int>>& graph, int colors) {
        int n = graph.size();
        vector<int> coloring(n, -1);
        random_device rd;
        mt19937 gen(rd());
        
        vector<int> vertices(n);
        iota(vertices.begin(), vertices.end(), 0);
        shuffle(vertices.begin(), vertices.end(), gen);
        
        for (int v : vertices) {
            vector<bool> usedColors(colors, false);
            
            // Mark colors used by neighbors
            for (int u = 0; u < n; u++) {
                if (graph[v][u] && coloring[u] != -1) {
                    usedColors[coloring[u]] = true;
                }
            }
            
            // Find available colors
            vector<int> availableColors;
            for (int c = 0; c < colors; c++) {
                if (!usedColors[c]) {
                    availableColors.push_back(c);
                }
            }
            
            if (!availableColors.empty()) {
                uniform_int_distribution<int> dis(0, availableColors.size() - 1);
                coloring[v] = availableColors[dis(gen)];
            }
        }
        
        return coloring;
    }
    
private:
    void contractEdge(vector<vector<int>>& adj, int u, int v) {
        // Merge vertex v into vertex u
        for (int i = 0; i < adj.size(); i++) {
            if (i != u && i != v) {
                adj[u][i] += adj[v][i];
                adj[i][u] += adj[i][v];
            }
        }
        
        // Remove self-loops
        adj[u][u] = 0;
        
        // Remove vertex v
        adj.erase(adj.begin() + v);
        for (auto& row : adj) {
            row.erase(row.begin() + v);
        }
    }
};
```

---

## 💡 Best Practices

### 🎯 Random Number Generation
```cpp
class RandomNumberBestPractices {
public:
    // Proper random number generator setup
    class ProperRNG {
    private:
        random_device rd;
        mt19937 gen;
        
    public:
        ProperRNG() : gen(rd()) {
            // Seed with high-quality randomness
            array<int, mt19937::state_size> seed_data;
            generate(seed_data.begin(), seed_data.end(), ref(rd));
            seed_seq seq(seed_data.begin(), seed_data.end());
            gen.seed(seq);
        }
        
        mt19937& getGenerator() { return gen; }
    };
    
    // Thread-safe random number generation
    class ThreadSafeRNG {
    private:
        static thread_local mt19937 gen;
        static thread_local bool initialized;
        
    public:
        static mt19937& getGenerator() {
            if (!initialized) {
                random_device rd;
                gen.seed(rd());
                initialized = true;
            }
            return gen;
        }
    };
    
    // Avoid common pitfalls
    void demonstratePitfalls() {
        cout << "Common Random Number Generation Pitfalls:" << endl;
        
        // BAD: Creating new generator each time
        // for (int i = 0; i < 1000; i++) {
        //     mt19937 gen(time(nullptr)); // Same seed!
        //     uniform_int_distribution<int> dis(1, 6);
        //     cout << dis(gen) << " ";
        // }
        
        // GOOD: Reuse generator
        mt19937 gen(random_device{}());
        uniform_int_distribution<int> dis(1, 6);
        for (int i = 0; i < 10; i++) {
            cout << dis(gen) << " ";
        }
        cout << endl;
    }
};

thread_local mt19937 RandomNumberBestPractices::ThreadSafeRNG::gen;
thread_local bool RandomNumberBestPractices::ThreadSafeRNG::initialized = false;
```

### 🧪 Testing Randomized Algorithms
```cpp
class RandomizedAlgorithmTesting {
public:
    // Statistical testing framework
    template<typename Algorithm>
    void testRandomizedAlgorithm(Algorithm& algo, int trials = 1000) {
        vector<double> results;
        
        for (int i = 0; i < trials; i++) {
            double result = algo.run();
            results.push_back(result);
        }
        
        // Statistical analysis
        double mean = calculateMean(results);
        double variance = calculateVariance(results, mean);
        double stddev = sqrt(variance);
        
        cout << "Statistical Analysis (" << trials << " trials):" << endl;
        cout << "Mean: " << mean << endl;
        cout << "Standard Deviation: " << stddev << endl;
        cout << "95% Confidence Interval: [" 
             << mean - 1.96 * stddev / sqrt(trials) << ", "
             << mean + 1.96 * stddev / sqrt(trials) << "]" << endl;
    }
    
    // Test correctness with known distributions
    bool testDistribution(function<int()> generator, vector<double>& expectedProbs, 
                         int trials = 10000, double significance = 0.05) {
        vector<int> observed(expectedProbs.size(), 0);
        
        for (int i = 0; i < trials; i++) {
            int outcome = generator();
            if (outcome >= 0 && outcome < observed.size()) {
                observed[outcome]++;
            }
        }
        
        // Chi-square goodness of fit test
        double chiSquare = 0.0;
        for (int i = 0; i < expectedProbs.size(); i++) {
            double expected = trials * expectedProbs[i];
            chiSquare += (observed[i] - expected) * (observed[i] - expected) / expected;
        }
        
        // Compare with critical value (simplified)
        double criticalValue = 9.488; // For df=4, α=0.05
        return chiSquare < criticalValue;
    }
    
private:
    double calculateMean(const vector<double>& data) {
        return accumulate(data.begin(), data.end(), 0.0) / data.size();
    }
    
    double calculateVariance(const vector<double>& data, double mean) {
        double variance = 0.0;
        for (double x : data) {
            variance += (x - mean) * (x - mean);
        }
        return variance / (data.size() - 1);
    }
};
```

---

## 📊 Complexity Analysis

### ⏰ Expected Time Complexity
- **Randomized QuickSort**: O(n log n) expected, O(n²) worst-case
- **Randomized Selection**: O(n) expected, O(n²) worst-case
- **Miller-Rabin**: O(k log³ n) for k rounds
- **Monte Carlo Integration**: O(n) for n samples

### 💾 Space Complexity
- **Las Vegas**: Same as deterministic version
- **Monte Carlo**: Often O(1) additional space
- **Probabilistic Data Structures**: Space-efficient with trade-offs

### 🎯 Error Analysis
- **Monte Carlo Error**: Decreases with more iterations
- **False Positive Rate**: Controllable in probabilistic structures
- **Confidence Intervals**: Statistical guarantees on performance

---

## 🌟 Key Takeaways

1. **Randomization Benefits**: Avoids worst-case, simplifies algorithms
2. **Algorithm Types**: Monte Carlo (fast, may err) vs Las Vegas (correct, variable time)
3. **Practical Performance**: Often superior to deterministic alternatives
4. **Error Control**: Amplification techniques reduce error probability
5. **Testing**: Statistical methods essential for validation
6. **Applications**: Widespread in modern computing systems

### 🎯 Interview Quick Reference
- **Randomized Algorithm**: Uses random choices during execution
- **Monte Carlo**: Fixed time, probabilistic correctness
- **Las Vegas**: Always correct, random time
- **Why Randomization**: Avoid worst-case inputs, better average performance
- **Examples**: QuickSort, Miller-Rabin, Bloom filters
- **Analysis**: Expected complexity, error probability

---

*Master randomized algorithms to build robust, efficient solutions that perform excellently in practice! 🎲*