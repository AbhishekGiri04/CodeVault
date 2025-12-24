# 🔐 Hashing — Complete Professional Guide

<div align="center">

![Hashing](https://img.shields.io/badge/Hashing-Fast_Access-ffc107?style=for-the-badge&logo=hash&logoColor=white)
![Difficulty](https://img.shields.io/badge/Difficulty-Intermediate-orange?style=for-the-badge)
![Importance](https://img.shields.io/badge/Importance-Critical-red?style=for-the-badge)

<img src="https://deen3evddmddt.cloudfront.net/uploads/content-images/what-is-hash-table.webp" alt="What is Hash Table" width="700" height="400"/>

<img src="https://logicmojo.com/assets/dist/new_pages/images/Hashing%20Uses.jpg" alt="Hashing Uses and Applications" width="650" height="350"/>

*Master hash tables for O(1) average-case operations*

</div>

---

## 🎯 Introduction

**Hashing** is a technique that maps keys to array indices using a hash function, enabling fast data retrieval.

### 🔑 Hash Table Components

```mermaid
mindmap
  root))🔐 Hash Table((
    📊 Hash Function
      Maps keys to indices
      Uniform distribution
      Fast computation
      Deterministic
    📦 Buckets/Slots
      Store key-value pairs
      Fixed size array
      Direct access
      Memory efficient
    ⚔️ Collision Resolution
      Handle same index
      Chaining method
      Open addressing
      Performance impact
    📊 Load Factor
      Size/Capacity ratio
      Performance indicator
      Resize trigger
      Optimal: < 0.75
```

### 💻 Basic Implementation

```cpp
class HashTable {
private:
    struct Node {
        int key;
        int value;
        Node* next;
        
        Node(int k, int v) : key(k), value(v), next(nullptr) {}
    };
    
    vector<Node*> table;
    int capacity;
    int size;
    
    int hashFunction(int key) {
        return abs(key) % capacity;
    }
    
public:
    HashTable(int cap = 10) : capacity(cap), size(0) {
        table.resize(capacity, nullptr);
    }
    
    void insert(int key, int value) {
        int index = hashFunction(key);
        
        if (!table[index]) {
            table[index] = new Node(key, value);
            size++;
        } else {
            Node* current = table[index];
            while (current) {
                if (current->key == key) {
                    current->value = value; // Update existing
                    return;
                }
                if (!current->next) break;
                current = current->next;
            }
            current->next = new Node(key, value);
            size++;
        }
    }
    
    bool search(int key, int& value) {
        int index = hashFunction(key);
        Node* current = table[index];
        
        while (current) {
            if (current->key == key) {
                value = current->value;
                return true;
            }
            current = current->next;
        }
        
        return false;
    }
    
    bool remove(int key) {
        int index = hashFunction(key);
        
        if (!table[index]) return false;
        
        if (table[index]->key == key) {
            Node* temp = table[index];
            table[index] = table[index]->next;
            delete temp;
            size--;
            return true;
        }
        
        Node* current = table[index];
        while (current->next) {
            if (current->next->key == key) {
                Node* temp = current->next;
                current->next = current->next->next;
                delete temp;
                size--;
                return true;
            }
            current = current->next;
        }
        
        return false;
    }
};
```

---

## 🎯 Hash Functions

### 🔧 Hash Function Properties

```mermaid
flowchart TD
    A["📊 Good Hash Function"] --> B["Uniform Distribution"]
    A --> C["Fast Computation"]
    A --> D["Deterministic"]
    A --> E["Avalanche Effect"]
    
    B --> F["Minimizes collisions"]
    B --> G["Even spread across table"]
    
    C --> H["O(1) computation time"]
    C --> I["Simple operations"]
    
    D --> J["Same input = same output"]
    D --> K["Reproducible results"]
    
    E --> L["Small input change"]
    E --> M["Large output change"]
    
    style A fill:#e3f2fd
    style B fill:#c8e6c9
    style C fill:#c8e6c9
    style D fill:#c8e6c9
    style E fill:#c8e6c9
```

```cpp
class HashFunctions {
public:
    // Division method
    int divisionHash(int key, int tableSize) {
        return abs(key) % tableSize;
    }
    
    // Multiplication method
    int multiplicationHash(int key, int tableSize) {
        const double A = 0.6180339887; // (sqrt(5) - 1) / 2
        double fractional = key * A - floor(key * A);
        return floor(tableSize * fractional);
    }
    
    // String hash function
    int stringHash(const string& str, int tableSize) {
        int hash = 0;
        int prime = 31;
        
        for (char c : str) {
            hash = (hash * prime + c) % tableSize;
        }
        
        return abs(hash);
    }
    
    // Polynomial rolling hash
    long long rollingHash(const string& str) {
        long long hash = 0;
        long long prime = 31;
        long long mod = 1e9 + 7;
        long long power = 1;
        
        for (char c : str) {
            hash = (hash + (c * power) % mod) % mod;
            power = (power * prime) % mod;
        }
        
        return hash;
    }
};
```

---

## 🎯 Collision Resolution

### 🔧 Collision Resolution Strategies

```mermaid
flowchart TD
    A["Collision Resolution"] --> B["Chaining"]
    A --> C["Open Addressing"]
    
    B --> D["Linked Lists"]
    B --> E["Dynamic Arrays"]
    B --> F["Balanced Trees"]
    
    C --> G["Linear Probing"]
    C --> H["Quadratic Probing"]
    C --> I["Double Hashing"]
    
    D --> J["Simple implementation"]
    D --> K["No table size limit"]
    
    G --> L["Next available slot"]
    G --> M["Primary clustering"]
    
    H --> N["i² step size"]
    H --> O["Reduces clustering"]
    
    I --> P["Second hash function"]
    I --> Q["Best distribution"]
    
    style A fill:#e3f2fd
    style B fill:#c8e6c9
    style C fill:#fff3e0
```

```cpp
// Open Addressing - Linear Probing
class LinearProbingHashTable {
private:
    struct Entry {
        int key;
        int value;
        bool deleted;
        
        Entry() : key(-1), value(-1), deleted(false) {}
        Entry(int k, int v) : key(k), value(v), deleted(false) {}
    };
    
    vector<Entry> table;
    int capacity;
    int size;
    
    int hashFunction(int key) {
        return abs(key) % capacity;
    }
    
public:
    LinearProbingHashTable(int cap = 10) : capacity(cap), size(0) {
        table.resize(capacity);
    }
    
    void insert(int key, int value) {
        if (size >= capacity * 0.7) { // Load factor check
            resize();
        }
        
        int index = hashFunction(key);
        
        while (table[index].key != -1 && !table[index].deleted) {
            if (table[index].key == key) {
                table[index].value = value;
                return;
            }
            index = (index + 1) % capacity;
        }
        
        table[index] = Entry(key, value);
        size++;
    }
    
    bool search(int key, int& value) {
        int index = hashFunction(key);
        int originalIndex = index;
        
        while (table[index].key != -1) {
            if (table[index].key == key && !table[index].deleted) {
                value = table[index].value;
                return true;
            }
            index = (index + 1) % capacity;
            if (index == originalIndex) break;
        }
        
        return false;
    }
    
private:
    void resize() {
        vector<Entry> oldTable = table;
        capacity *= 2;
        table.clear();
        table.resize(capacity);
        size = 0;
        
        for (const Entry& entry : oldTable) {
            if (entry.key != -1 && !entry.deleted) {
                insert(entry.key, entry.value);
            }
        }
    }
};
```

---

## 🎯 Applications

### 🔧 Hash Table Use Cases

```mermaid
mindmap
  root))🔐 Hash Table Applications((
    📊 Database Indexing
      Primary keys
      Foreign keys
      Query optimization
      B+ tree alternatives
    💾 Caching Systems
      LRU Cache
      Web caching
      Memory caching
      CDN systems
    🔍 Search & Retrieval
      Symbol tables
      Dictionary lookup
      Spell checkers
      Autocomplete
    🔢 Algorithm Optimization
      Two Sum problems
      Duplicate detection
      Frequency counting
      Set operations
    🌐 Distributed Systems
      Consistent hashing
      Load balancing
      Sharding
      DHT systems
```

```cpp
class HashTableProblems {
public:
    // Two Sum
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> numToIndex;
        
        for (int i = 0; i < nums.size(); i++) {
            int complement = target - nums[i];
            
            if (numToIndex.count(complement)) {
                return {numToIndex[complement], i};
            }
            
            numToIndex[nums[i]] = i;
        }
        
        return {};
    }
    
    // Group Anagrams
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> groups;
        
        for (const string& str : strs) {
            string key = str;
            sort(key.begin(), key.end());
            groups[key].push_back(str);
        }
        
        vector<vector<string>> result;
        for (const auto& pair : groups) {
            result.push_back(pair.second);
        }
        
        return result;
    }
    
    // Longest Consecutive Sequence
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> numSet(nums.begin(), nums.end());
        int maxLength = 0;
        
        for (int num : numSet) {
            if (!numSet.count(num - 1)) { // Start of sequence
                int currentNum = num;
                int currentLength = 1;
                
                while (numSet.count(currentNum + 1)) {
                    currentNum++;
                    currentLength++;
                }
                
                maxLength = max(maxLength, currentLength);
            }
        }
        
        return maxLength;
    }
    
    // LRU Cache
    class LRUCache {
    private:
        struct Node {
            int key, value;
            Node* prev;
            Node* next;
            
            Node(int k = 0, int v = 0) : key(k), value(v), prev(nullptr), next(nullptr) {}
        };
        
        unordered_map<int, Node*> cache;
        Node* head;
        Node* tail;
        int capacity;
        
        void addToHead(Node* node) {
            node->prev = head;
            node->next = head->next;
            head->next->prev = node;
            head->next = node;
        }
        
        void removeNode(Node* node) {
            node->prev->next = node->next;
            node->next->prev = node->prev;
        }
        
        Node* removeTail() {
            Node* last = tail->prev;
            removeNode(last);
            return last;
        }
        
    public:
        LRUCache(int cap) : capacity(cap) {
            head = new Node();
            tail = new Node();
            head->next = tail;
            tail->prev = head;
        }
        
        int get(int key) {
            if (cache.count(key)) {
                Node* node = cache[key];
                removeNode(node);
                addToHead(node);
                return node->value;
            }
            return -1;
        }
        
        void put(int key, int value) {
            if (cache.count(key)) {
                Node* node = cache[key];
                node->value = value;
                removeNode(node);
                addToHead(node);
            } else {
                Node* newNode = new Node(key, value);
                
                if (cache.size() >= capacity) {
                    Node* tail = removeTail();
                    cache.erase(tail->key);
                    delete tail;
                }
                
                cache[key] = newNode;
                addToHead(newNode);
            }
        }
    };
};
```

---

## 🏆 Best Practices

### ✅ Do's

```cpp
// 1. Choose appropriate hash function
class GoodHashPractices {
public:
    // Use built-in hash for standard types
    void useBuiltInHash() {
        unordered_map<string, int> stringMap;
        unordered_set<int> intSet;
    }
    
    // Custom hash for custom objects
    struct Point {
        int x, y;
        
        bool operator==(const Point& other) const {
            return x == other.x && y == other.y;
        }
    };
    
    struct PointHash {
        size_t operator()(const Point& p) const {
            return hash<int>()(p.x) ^ (hash<int>()(p.y) << 1);
        }
    };
    
    void useCustomHash() {
        unordered_set<Point, PointHash> pointSet;
    }
};

// 2. Handle load factor
void maintainLoadFactor() {
    unordered_map<int, int> map;
    map.reserve(1000); // Pre-allocate for better performance
}
```

---

## 🎓 Summary

Hashing provides fast data access:

✅ **O(1) Average**: Insert, search, delete operations  
✅ **Hash Functions**: Map keys to indices efficiently  
✅ **Collision Resolution**: Chaining vs open addressing  
✅ **Applications**: Caching, indexing, duplicate detection  
✅ **Load Factor**: Keep below 0.75 for good performance  

---

<div align="center">

**🔐 Hash Your Way to Speed**

*Fast access through intelligent mapping*

</div>