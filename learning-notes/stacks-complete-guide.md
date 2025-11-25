<div align="center">

# 📚 Day 5: Stacks - LIFO Data Structure Mastery

*Understanding Last-In-First-Out Operations and Stack-Based Algorithms*

---

![Stacks](https://img.shields.io/badge/Topic-Stacks-FF6B6B?style=for-the-badge&logo=stack&logoColor=white)
![Difficulty](https://img.shields.io/badge/Level-Beginner_to_Intermediate-4ECDC4?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Completed-45B7D1?style=for-the-badge)

</div>

---

## 🎯 **Learning Objectives**

> *Master the fundamental LIFO data structure and its powerful applications*

- 🏗️ Understand stack architecture and LIFO principle
- ⚡ Master stack operations and their implementations
- 🧩 Learn essential stack-based problem patterns
- 🚀 Apply stacks in real-world algorithmic scenarios

---

## 📖 **1. Stack Fundamentals**

<div align="center">

### 📚 **What Makes Stacks Special?**

</div>

<table>
<tr>
<td width="50%">

### 🎯 **Core Characteristics**
- **📚 LIFO Principle**: Last In, First Out ordering
- **🔝 Top Access**: Only top element accessible
- **⚡ Fast Operations**: O(1) push, pop, peek
- **🏗️ Simple Structure**: Linear organization with restricted access

</td>
<td width="50%">

### ⚡ **Why Stacks Matter?**
- **🔄 Recursion Support**: Function call management
- **📝 Expression Parsing**: Mathematical expression evaluation
- **↩️ Undo Operations**: Reversible action tracking
- **💼 Interview Essential**: Core algorithmic concept

</td>
</tr>
</table>

### 🧮 **Visual Stack Representation**

```
Stack Operations:

Push(5) → Push(3) → Push(8) → Pop() → Push(1)

Step 1:     Step 2:     Step 3:     Step 4:     Step 5:
           
           Top → [3]   Top → [8]   Top → [3]   Top → [1]
                 [5]           [3]           [5]           [3]
Bottom → [5]   Bottom → [5]   Bottom → [5]   Bottom → [5]

Result: Stack = [5, 3, 1] (bottom to top)
```

---

## ⚙️ **2. Stack Operations & Complexity Analysis**

<div align="center">

### 📊 **Performance Metrics**

| Operation | Description | Time Complexity | Space Complexity | Use Case |
|:----------|:------------|:----------------|:-----------------|:---------|
| **➕ Push** | Add element to top | **O(1)** | O(1) | Insert new element |
| **➖ Pop** | Remove top element | **O(1)** | O(1) | Remove last element |
| **👁️ Peek/Top** | View top element | **O(1)** | O(1) | Access without removal |
| **❓ Empty** | Check if empty | **O(1)** | O(1) | Validation |
| **📏 Size** | Get element count | **O(1)** | O(1) | Stack status |

</div>

### 🤔 **Why All Operations are O(1)?**

```cpp
// Stack operations only work with the top element
// No traversal or shifting required!

stack.push(x);    // Just add to top
stack.pop();      // Just remove from top  
stack.top();      // Just access top
```

---

## 🏗️ **3. Stack Implementation Methods**

### 💻 **Different Implementation Approaches**

<table>
<tr>
<td width="33%">

#### 🔧 **Array Implementation**
```cpp
class ArrayStack {
    int arr[1000];
    int topIndex;
public:
    ArrayStack() : topIndex(-1) {}
    
    void push(int x) {
        arr[++topIndex] = x;
    }
    
    void pop() {
        if (!empty()) topIndex--;
    }
    
    int top() {
        return arr[topIndex];
    }
    
    bool empty() {
        return topIndex == -1;
    }
};
```
- Fixed size
- Fast operations
- Memory efficient

</td>
<td width="33%">

#### 🔗 **Linked List Implementation**
```cpp
struct Node {
    int data;
    Node* next;
};

class LinkedStack {
    Node* topNode;
public:
    LinkedStack() : topNode(nullptr) {}
    
    void push(int x) {
        Node* newNode = new Node();
        newNode->data = x;
        newNode->next = topNode;
        topNode = newNode;
    }
    
    void pop() {
        if (topNode) {
            Node* temp = topNode;
            topNode = topNode->next;
            delete temp;
        }
    }
};
```
- Dynamic size
- No overflow
- Extra memory for pointers

</td>
<td width="33%">

#### 🚀 **STL Implementation**
```cpp
#include <stack>

stack<int> st;

// Basic operations
st.push(5);
st.push(10);
st.push(15);

cout << st.top(); // 15
st.pop();
cout << st.size(); // 2
cout << st.empty(); // false

// Iterate (requires temp stack)
stack<int> temp = st;
while (!temp.empty()) {
    cout << temp.top() << " ";
    temp.pop();
}
```
- Ready to use
- Optimized implementation
- Standard library support

</td>
</tr>
</table>

---

## 🧠 **4. Essential Stack Patterns**

<div align="center">

### 🎯 **Master These Techniques**

</div>

<table>
<tr>
<td width="25%">

#### 🔍 **Balanced Parentheses**
```cpp
bool isValid(string s) {
    stack<char> st;
    for (char c : s) {
        if (c == '(' || c == '[' || c == '{') {
            st.push(c);
        } else {
            if (st.empty()) return false;
            char top = st.top();
            st.pop();
            if ((c == ')' && top != '(') ||
                (c == ']' && top != '[') ||
                (c == '}' && top != '{')) {
                return false;
            }
        }
    }
    return st.empty();
}
```
*Parentheses validation*

</td>
<td width="25%">

#### 📊 **Next Greater Element**
```cpp
vector<int> nextGreater(vector<int>& nums) {
    vector<int> result(nums.size(), -1);
    stack<int> st; // Store indices
    
    for (int i = 0; i < nums.size(); i++) {
        while (!st.empty() && 
               nums[st.top()] < nums[i]) {
            result[st.top()] = nums[i];
            st.pop();
        }
        st.push(i);
    }
    return result;
}
```
*Monotonic stack pattern*

</td>
<td width="25%">

#### 🧮 **Expression Evaluation**
```cpp
int evaluatePostfix(string exp) {
    stack<int> st;
    for (char c : exp) {
        if (isdigit(c)) {
            st.push(c - '0');
        } else {
            int b = st.top(); st.pop();
            int a = st.top(); st.pop();
            switch(c) {
                case '+': st.push(a + b); break;
                case '-': st.push(a - b); break;
                case '*': st.push(a * b); break;
                case '/': st.push(a / b); break;
            }
        }
    }
    return st.top();
}
```
*Postfix evaluation*

</td>
<td width="25%">

#### 🔄 **Stack Reversal**
```cpp
void reverse(stack<int>& st) {
    if (st.empty()) return;
    
    int temp = st.top();
    st.pop();
    reverse(st);
    insertAtBottom(st, temp);
}

void insertAtBottom(stack<int>& st, int x) {
    if (st.empty()) {
        st.push(x);
        return;
    }
    int temp = st.top();
    st.pop();
    insertAtBottom(st, x);
    st.push(temp);
}
```
*Recursive stack operations*

</td>
</tr>
</table>

---

## 🚀 **5. Real-World Applications**

<div align="center">

### 🌍 **Where Stacks Excel**

</div>

<table>
<tr>
<td width="33%">

#### 💻 **System Programming**
- Function call stack
- Memory management
- Interrupt handling
- Process scheduling

</td>
<td width="33%">

#### 🌐 **Web Development**
- Browser history (back/forward)
- Undo/Redo operations
- Expression parsing
- Syntax checking

</td>
<td width="33%">

#### 🎮 **Applications**
- Game state management
- Backtracking algorithms
- Compiler design
- Calculator implementations

</td>
</tr>
</table>

---

## 🔥 **6. Interview-Level Problem Categories**

<div align="center">

### 🎯 **Must-Know Problem Types**

</div>

| Category | Problems | Difficulty | Key Technique |
|:---------|:---------|:-----------|:--------------|
| **🔍 Validation** | Valid Parentheses, Remove Invalid | 🟢 Easy-Medium | Stack matching |
| **📊 Monotonic Stack** | Next Greater, Daily Temperatures | 🟡 Medium | Decreasing/Increasing stack |
| **🧮 Expression** | Evaluate Expression, Basic Calculator | 🟡 Medium-Hard | Operator precedence |
| **🔄 Stack Operations** | Min Stack, Sort Stack | 🟡 Medium | Auxiliary stack |
| **🏗️ Design** | Implement Queue using Stacks | 🟢 Easy | Two-stack technique |
| **🎯 Advanced** | Largest Rectangle, Trapping Rain Water | 🔴 Hard | Stack + geometry |

---

## 📊 **7. Advantages vs Disadvantages**

<table>
<tr>
<td width="50%">

### ✅ **Advantages**
- **⚡ Fast Operations**: All operations in O(1) time
- **🧠 Simple Logic**: Easy to understand and implement
- **💾 Memory Efficient**: Minimal overhead (array implementation)
- **🔄 Natural Recursion**: Perfect for recursive algorithms
- **🏗️ Versatile**: Wide range of applications

</td>
<td width="50%">

### ❌ **Disadvantages**
- **🚫 No Random Access**: Can only access top element
- **📏 Size Limitation**: Fixed size in array implementation
- **🔍 No Search**: Cannot search middle elements efficiently
- **⚠️ Overflow Risk**: Stack overflow in array implementation
- **🔄 Limited Flexibility**: Restricted access pattern

</td>
</tr>
</table>

---

## 🎯 **8. Key Takeaways & Best Practices**

<div align="center">

### 💡 **Essential Insights**

</div>

> 📚 **LIFO Mastery**: Understand the Last-In-First-Out principle completely  
> 🧠 **Pattern Recognition**: Learn monotonic stack and auxiliary stack patterns  
> 🔍 **Edge Cases**: Always check for empty stack before pop/top operations  
> 📊 **Problem Mapping**: Identify when stack is the right data structure  
> 🧪 **Practice**: Implement stack operations from scratch for deep understanding  

---

## 📚 **9. Advanced Stack Concepts**

<div align="center">

### 🚀 **Next Level Topics**

</div>

<table>
<tr>
<td width="25%">

#### 🎯 **Min/Max Stack**
- Constant time minimum/maximum
- Auxiliary stack technique
- Space-time trade-offs

</td>
<td width="25%">

#### 📊 **Monotonic Stack**
- Increasing/decreasing sequences
- Next greater/smaller elements
- Histogram problems

</td>
<td width="25%">

#### 🔄 **Stack Sorting**
- Sort using additional stacks
- Recursive sorting algorithms
- Optimization techniques

</td>
<td width="25%">

#### 🏗️ **Multi-Stack**
- Multiple stacks in single array
- Dynamic stack allocation
- Memory optimization

</td>
</tr>
</table>

---

## 📚 **10. Next Learning Path**

<table>
<tr>
<td width="50%">

### 🎯 **Immediate Next Steps**
- [ ] Practice 15+ stack problems
- [ ] Master monotonic stack pattern
- [ ] Implement all stack operations
- [ ] Learn expression evaluation

</td>
<td width="50%">

### 🚀 **Advanced Topics**
- [ ] Queue implementation using stacks
- [ ] Advanced stack algorithms
- [ ] System stack understanding
- [ ] Compiler design applications

</td>
</tr>
</table>

---

<div align="center">

### 📊 **Learning Progress**

![Progress](https://img.shields.io/badge/Completion-100%25-success?style=for-the-badge)
![Concepts](https://img.shields.io/badge/Concepts_Learned-8-blue?style=for-the-badge)
![Patterns](https://img.shields.io/badge/Patterns_Mastered-4-orange?style=for-the-badge)

---

**📅 Session Date**: Day 5 | **🎯 Focus**: Stack Mastery | **⏰ Duration**: Comprehensive Deep Dive

*"Stacks teach us that sometimes the last shall be first, and order matters in algorithms"*

</div>