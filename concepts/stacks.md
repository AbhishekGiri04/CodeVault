# 📚 Stacks — Complete Professional Guide

<div align="center">

<img src="https://www.scaler.com/topics/images/application-of-stack-thumbnail.webp" alt="Stack Applications" width="600" height="300"/>

![Stacks](https://img.shields.io/badge/Stacks-LIFO_Structure-dc3545?style=for-the-badge&logo=stack&logoColor=white)
![Difficulty](https://img.shields.io/badge/Difficulty-Beginner-green?style=for-the-badge)
![Importance](https://img.shields.io/badge/Importance-High-red?style=for-the-badge)

*Master Last-In-First-Out data structure for efficient operations*

</div>

---

## 🎯 Introduction

**Stacks** follow the Last-In-First-Out (LIFO) principle where elements are added and removed from the same end called the "top".

## 📊 Stack Applications Gallery

<div align="center">

<img src="https://dotnettrickscloud.blob.core.windows.net/article/data%20structures/5320250722232438.png" alt="Stack Data Structure" width="400" height="250"/>
<img src="https://media.geeksforgeeks.org/wp-content/uploads/20250903181529839843/Applications-of-Stacks.webp" alt="Stack Applications" width="400" height="250"/>

</div>

### 🌊 Stack Operations Flow

```mermaid
graph TD
    A[Stack Operations] --> B[Push]
    A --> C[Pop]
    A --> D[Top/Peek]
    A --> E[isEmpty]
    
    B --> F[Add to top - O(1)]
    C --> G[Remove from top - O(1)]
    D --> H[View top element - O(1)]
    E --> I[Check if empty - O(1)]
    
    J[LIFO Principle] --> K[Last In]
    K --> L[First Out]
```

### 🔑 Stack Operations

```mermaid
graph TD
    A[Stack Operations] --> B[Push - Add to top]
    A --> C[Pop - Remove from top]
    A --> D[Top/Peek - View top element]
    A --> E[isEmpty - Check if empty]
    
    B --> F[O(1)]
    C --> G[O(1)]
    D --> H[O(1)]
    E --> I[O(1)]
```

### 💻 Basic Implementation

```cpp
class Stack {
private:
    vector<int> data;
    
public:
    void push(int val) {
        data.push_back(val);
    }
    
    void pop() {
        if (!empty()) {
            data.pop_back();
        }
    }
    
    int top() {
        if (!empty()) {
            return data.back();
        }
        throw runtime_error("Stack is empty");
    }
    
    bool empty() {
        return data.empty();
    }
    
    int size() {
        return data.size();
    }
};
```

---

## 🎯 Applications

### 🔧 Expression Evaluation

```cpp
class ExpressionEvaluator {
public:
    bool isValidParentheses(string s) {
        stack<char> stk;
        
        for (char c : s) {
            if (c == '(' || c == '[' || c == '{') {
                stk.push(c);
            } else {
                if (stk.empty()) return false;
                
                char top = stk.top();
                stk.pop();
                
                if ((c == ')' && top != '(') ||
                    (c == ']' && top != '[') ||
                    (c == '}' && top != '{')) {
                    return false;
                }
            }
        }
        
        return stk.empty();
    }
    
    int evaluatePostfix(vector<string>& tokens) {
        stack<int> stk;
        
        for (string token : tokens) {
            if (token == "+" || token == "-" || token == "*" || token == "/") {
                int b = stk.top(); stk.pop();
                int a = stk.top(); stk.pop();
                
                if (token == "+") stk.push(a + b);
                else if (token == "-") stk.push(a - b);
                else if (token == "*") stk.push(a * b);
                else stk.push(a / b);
            } else {
                stk.push(stoi(token));
            }
        }
        
        return stk.top();
    }
};
```

### 🔧 Monotonic Stack

```cpp
class MonotonicStack {
public:
    vector<int> nextGreaterElement(vector<int>& nums) {
        vector<int> result(nums.size(), -1);
        stack<int> stk; // Store indices
        
        for (int i = 0; i < nums.size(); i++) {
            while (!stk.empty() && nums[i] > nums[stk.top()]) {
                result[stk.top()] = nums[i];
                stk.pop();
            }
            stk.push(i);
        }
        
        return result;
    }
    
    int largestRectangleArea(vector<int>& heights) {
        stack<int> stk;
        int maxArea = 0;
        
        for (int i = 0; i <= heights.size(); i++) {
            int h = (i == heights.size()) ? 0 : heights[i];
            
            while (!stk.empty() && h < heights[stk.top()]) {
                int height = heights[stk.top()];
                stk.pop();
                
                int width = stk.empty() ? i : i - stk.top() - 1;
                maxArea = max(maxArea, height * width);
            }
            
            stk.push(i);
        }
        
        return maxArea;
    }
};
```

---

## 🏆 Best Practices

### ✅ Do's

```cpp
// 1. Always check if stack is empty before pop/top
int safePop(stack<int>& stk) {
    if (stk.empty()) {
        throw runtime_error("Stack underflow");
    }
    int val = stk.top();
    stk.pop();
    return val;
}

// 2. Use stack for recursive problems iteratively
vector<int> inorderTraversal(TreeNode* root) {
    vector<int> result;
    stack<TreeNode*> stk;
    TreeNode* current = root;
    
    while (current || !stk.empty()) {
        while (current) {
            stk.push(current);
            current = current->left;
        }
        
        current = stk.top();
        stk.pop();
        result.push_back(current->val);
        current = current->right;
    }
    
    return result;
}
```

---

## 🎓 Summary

Stacks are essential for LIFO operations:

✅ **LIFO Principle**: Last-In-First-Out access pattern  
✅ **O(1) Operations**: Push, pop, top, isEmpty  
✅ **Applications**: Expression evaluation, function calls, undo operations  
✅ **Monotonic Stack**: For next greater/smaller element problems  

---

<div align="center">

**📚 Stack Up Your Knowledge**

*LIFO: The foundation of recursive thinking*

</div>