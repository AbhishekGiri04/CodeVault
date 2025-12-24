# 🚶 Queues — Complete Professional Guide

<div align="center">

<img src="https://www.scaler.com/topics/images/queue-in-data-structure_thumbnail.webp" alt="Queue Data Structure" width="600" height="300"/>

![Queues](https://img.shields.io/badge/Queues-FIFO_Structure-17a2b8?style=for-the-badge&logo=queue&logoColor=white)
![Difficulty](https://img.shields.io/badge/Difficulty-Beginner-green?style=for-the-badge)
![Importance](https://img.shields.io/badge/Importance-High-red?style=for-the-badge)

*Master First-In-First-Out data structure for sequential processing*

</div>

---

## 🎯 Introduction

**Queues** follow the First-In-First-Out (FIFO) principle where elements are added at the rear and removed from the front.

## 📊 Queue Visualization Gallery

<div align="center">

<img src="https://scaler.com/topics/images/queue-in-data-structure-image3.webp" alt="Queue Operations" width="450" height="300"/>
<img src="https://scaler.com/topics/images/queue-in-data-structure-image2.webp" alt="Queue Implementation" width="450" height="300"/>

</div>

### 🌊 Queue Operations Flow

```mermaid
graph TD
    A[Queue Operations] --> B[Enqueue]
    A --> C[Dequeue]
    A --> D[Front/Peek]
    A --> E[isEmpty]
    
    B --> F[Add to rear - O(1)]
    C --> G[Remove from front - O(1)]
    D --> H[View front element - O(1)]
    E --> I[Check if empty - O(1)]
    
    J[FIFO Principle] --> K[First In]
    K --> L[First Out]
    
    M[Queue Types] --> N[Simple Queue]
    M --> O[Circular Queue]
    M --> P[Priority Queue]
    M --> Q[Deque]
```

### 🔑 Queue Operations

```mermaid
graph TD
    A[Queue Operations] --> B[Enqueue - Add to rear]
    A --> C[Dequeue - Remove from front]
    A --> D[Front - View front element]
    A --> E[isEmpty - Check if empty]
    
    B --> F[O(1)]
    C --> G[O(1)]
    D --> H[O(1)]
    E --> I[O(1)]
```

### 💻 Basic Implementation

```cpp
class Queue {
private:
    vector<int> data;
    int frontIndex;
    int rearIndex;
    int count;
    
public:
    Queue(int capacity) : data(capacity), frontIndex(0), rearIndex(-1), count(0) {}
    
    void enqueue(int val) {
        if (count == data.size()) {
            throw runtime_error("Queue overflow");
        }
        
        rearIndex = (rearIndex + 1) % data.size();
        data[rearIndex] = val;
        count++;
    }
    
    int dequeue() {
        if (empty()) {
            throw runtime_error("Queue underflow");
        }
        
        int val = data[frontIndex];
        frontIndex = (frontIndex + 1) % data.size();
        count--;
        return val;
    }
    
    int front() {
        if (empty()) {
            throw runtime_error("Queue is empty");
        }
        return data[frontIndex];
    }
    
    bool empty() {
        return count == 0;
    }
    
    int size() {
        return count;
    }
};
```

---

## 🎯 Types of Queues

### 🔧 Priority Queue

```cpp
class PriorityQueue {
private:
    priority_queue<int> maxHeap; // Max heap by default
    
public:
    void push(int val) {
        maxHeap.push(val);
    }
    
    int top() {
        return maxHeap.top();
    }
    
    void pop() {
        maxHeap.pop();
    }
    
    bool empty() {
        return maxHeap.empty();
    }
};

// Min Priority Queue
priority_queue<int, vector<int>, greater<int>> minHeap;
```

### 🔧 Deque (Double-ended Queue)

```cpp
class DequeOperations {
public:
    vector<int> slidingWindowMaximum(vector<int>& nums, int k) {
        deque<int> dq; // Store indices
        vector<int> result;
        
        for (int i = 0; i < nums.size(); i++) {
            // Remove elements outside window
            while (!dq.empty() && dq.front() <= i - k) {
                dq.pop_front();
            }
            
            // Remove smaller elements from rear
            while (!dq.empty() && nums[dq.back()] < nums[i]) {
                dq.pop_back();
            }
            
            dq.push_back(i);
            
            // Add to result if window is complete
            if (i >= k - 1) {
                result.push_back(nums[dq.front()]);
            }
        }
        
        return result;
    }
};
```

---

## 🎯 Applications

### 🔧 BFS Traversal

```cpp
class BFSTraversal {
public:
    vector<int> levelOrder(TreeNode* root) {
        if (!root) return {};
        
        vector<int> result;
        queue<TreeNode*> q;
        q.push(root);
        
        while (!q.empty()) {
            TreeNode* node = q.front();
            q.pop();
            
            result.push_back(node->val);
            
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        
        return result;
    }
    
    vector<vector<int>> levelOrderGrouped(TreeNode* root) {
        if (!root) return {};
        
        vector<vector<int>> result;
        queue<TreeNode*> q;
        q.push(root);
        
        while (!q.empty()) {
            int levelSize = q.size();
            vector<int> currentLevel;
            
            for (int i = 0; i < levelSize; i++) {
                TreeNode* node = q.front();
                q.pop();
                
                currentLevel.push_back(node->val);
                
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
            
            result.push_back(currentLevel);
        }
        
        return result;
    }
};
```

---

## 🏆 Best Practices

### ✅ Do's

```cpp
// 1. Check bounds before operations
int safeDequeue(queue<int>& q) {
    if (q.empty()) {
        throw runtime_error("Queue is empty");
    }
    int val = q.front();
    q.pop();
    return val;
}

// 2. Use appropriate queue type
void chooseQueueType() {
    queue<int> normalQueue;        // FIFO operations
    priority_queue<int> pq;        // Priority-based
    deque<int> doubleEndedQueue;   // Both ends access
}
```

---

## 🎓 Summary

Queues are essential for FIFO operations:

✅ **FIFO Principle**: First-In-First-Out access pattern  
✅ **O(1) Operations**: Enqueue, dequeue, front, isEmpty  
✅ **Types**: Normal, priority, deque, circular  
✅ **Applications**: BFS, task scheduling, buffer management  

---

<div align="center">

**🚶 Queue Up for Success**

*FIFO: Fair and orderly data processing*

</div>