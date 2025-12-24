# 🔍 Searching — Complete Professional Guide

<div align="center">

<img src="https://www.scaler.com/topics/images/searching-in-data-structure-thumbnail.webp" alt="Searching Algorithms" width="600" height="300"/>

![Searching](https://img.shields.io/badge/Searching-Find_Elements-17a2b8?style=for-the-badge&logo=search&logoColor=white)
![Difficulty](https://img.shields.io/badge/Difficulty-Fundamental-green?style=for-the-badge)
![Importance](https://img.shields.io/badge/Importance-Critical-red?style=for-the-badge)

*Master efficient algorithms for finding elements in data structures*

</div>

---

## 🎯 Introduction

**Searching** algorithms find the location of specific elements within data structures efficiently.

## 📊 Searching Algorithm Gallery

<div align="center">

<img src="https://www.scaler.com/topics/images/linear-search-in-c-thumbnail.webp" alt="Linear Search" width="400" height="250"/>
<img src="https://deen3evddmddt.cloudfront.net/uploads/content-images/binary-search-alogrithm.webp" alt="Binary Search" width="400" height="250"/>

<img src="https://www.w3schools.com/dsa/img_binarysearch_timecomplexity.png" alt="Binary Search Complexity" width="500" height="300"/>

</div>

### 🌊 Search Algorithm Flow

```mermaid
graph TD
    A[Searching Algorithms] --> B[Linear Search]
    A --> C[Binary Search]
    A --> D[Advanced Search]
    
    B --> E[O(n) - Unsorted data]
    B --> F[Sequential scan]
    
    C --> G[O(log n) - Sorted data]
    C --> H[Divide and conquer]
    
    D --> I[Interpolation O(log log n)]
    D --> J[Exponential O(log n)]
    D --> K[Ternary Search]
```

### 🔑 Search Algorithm Types

```mermaid
graph TD
    A[Searching Algorithms] --> B[Linear Search]
    A --> C[Binary Search]
    A --> D[Interpolation Search]
    A --> E[Exponential Search]
    
    B --> F[O(n) - Unsorted data]
    C --> G[O(log n) - Sorted data]
    D --> H[O(log log n) - Uniformly distributed]
    E --> I[O(log n) - Unbounded arrays]
```

---

## 🎯 Linear Search

### 💻 Implementation

```cpp
class LinearSearch {
public:
    int search(vector<int>& arr, int target) {
        for (int i = 0; i < arr.size(); i++) {
            if (arr[i] == target) {
                return i;
            }
        }
        return -1;
    }
    
    // Find all occurrences
    vector<int> findAll(vector<int>& arr, int target) {
        vector<int> indices;
        for (int i = 0; i < arr.size(); i++) {
            if (arr[i] == target) {
                indices.push_back(i);
            }
        }
        return indices;
    }
    
    // Search in 2D array
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        for (const auto& row : matrix) {
            for (int val : row) {
                if (val == target) return true;
            }
        }
        return false;
    }
};
```

---

## 🎯 Binary Search

### 💻 Basic Implementation

```cpp
class BinarySearch {
public:
    int search(vector<int>& arr, int target) {
        int left = 0, right = arr.size() - 1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            if (arr[mid] == target) {
                return mid;
            } else if (arr[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return -1;
    }
    
    // Recursive version
    int searchRecursive(vector<int>& arr, int target, int left, int right) {
        if (left > right) return -1;
        
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            return searchRecursive(arr, target, mid + 1, right);
        } else {
            return searchRecursive(arr, target, left, mid - 1);
        }
    }
    
    // Find first occurrence
    int findFirst(vector<int>& arr, int target) {
        int left = 0, right = arr.size() - 1;
        int result = -1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            if (arr[mid] == target) {
                result = mid;
                right = mid - 1; // Continue searching left
            } else if (arr[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return result;
    }
    
    // Find last occurrence
    int findLast(vector<int>& arr, int target) {
        int left = 0, right = arr.size() - 1;
        int result = -1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            if (arr[mid] == target) {
                result = mid;
                left = mid + 1; // Continue searching right
            } else if (arr[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return result;
    }
};
```

### 🔧 Binary Search Variants

```cpp
class BinarySearchVariants {
public:
    // Search in rotated sorted array
    int searchRotated(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            if (nums[mid] == target) return mid;
            
            if (nums[left] <= nums[mid]) { // Left half is sorted
                if (target >= nums[left] && target < nums[mid]) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            } else { // Right half is sorted
                if (target > nums[mid] && target <= nums[right]) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
        }
        
        return -1;
    }
    
    // Find peak element
    int findPeakElement(vector<int>& nums) {
        int left = 0, right = nums.size() - 1;
        
        while (left < right) {
            int mid = left + (right - left) / 2;
            
            if (nums[mid] > nums[mid + 1]) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        
        return left;
    }
    
    // Search 2D matrix (sorted)
    bool searchMatrix2D(vector<vector<int>>& matrix, int target) {
        if (matrix.empty() || matrix[0].empty()) return false;
        
        int m = matrix.size(), n = matrix[0].size();
        int left = 0, right = m * n - 1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            int midValue = matrix[mid / n][mid % n];
            
            if (midValue == target) {
                return true;
            } else if (midValue < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return false;
    }
    
    // Find minimum in rotated sorted array
    int findMin(vector<int>& nums) {
        int left = 0, right = nums.size() - 1;
        
        while (left < right) {
            int mid = left + (right - left) / 2;
            
            if (nums[mid] > nums[right]) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        
        return nums[left];
    }
};
```

---

## 🎯 Advanced Search Algorithms

### 🔧 Interpolation Search

```cpp
int interpolationSearch(vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    
    while (left <= right && target >= arr[left] && target <= arr[right]) {
        if (left == right) {
            return arr[left] == target ? left : -1;
        }
        
        // Interpolation formula
        int pos = left + ((double)(target - arr[left]) / (arr[right] - arr[left])) * (right - left);
        
        if (arr[pos] == target) {
            return pos;
        } else if (arr[pos] < target) {
            left = pos + 1;
        } else {
            right = pos - 1;
        }
    }
    
    return -1;
}
```

### 🔧 Exponential Search

```cpp
int exponentialSearch(vector<int>& arr, int target) {
    if (arr[0] == target) return 0;
    
    int bound = 1;
    while (bound < arr.size() && arr[bound] < target) {
        bound *= 2;
    }
    
    // Binary search in the found range
    int left = bound / 2;
    int right = min(bound, (int)arr.size() - 1);
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return -1;
}
```

---

## 🎯 Search Applications

### 🔧 Binary Search on Answer

```cpp
class BinarySearchOnAnswer {
public:
    // Find square root
    int mySqrt(int x) {
        if (x < 2) return x;
        
        int left = 2, right = x / 2;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            long long square = (long long)mid * mid;
            
            if (square == x) {
                return mid;
            } else if (square < x) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        
        return right;
    }
    
    // Capacity to ship packages within D days
    int shipWithinDays(vector<int>& weights, int D) {
        int left = *max_element(weights.begin(), weights.end());
        int right = accumulate(weights.begin(), weights.end(), 0);
        
        while (left < right) {
            int mid = left + (right - left) / 2;
            
            if (canShip(weights, D, mid)) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        
        return left;
    }
    
private:
    bool canShip(vector<int>& weights, int D, int capacity) {
        int days = 1, currentWeight = 0;
        
        for (int weight : weights) {
            if (currentWeight + weight > capacity) {
                days++;
                currentWeight = weight;
            } else {
                currentWeight += weight;
            }
        }
        
        return days <= D;
    }
};
```

---

## 🏆 Best Practices

### ✅ Do's

```cpp
// 1. Use appropriate search for data type
void chooseSearchAlgorithm(vector<int>& arr, bool isSorted) {
    if (isSorted) {
        // Use binary search - O(log n)
        binary_search(arr.begin(), arr.end(), target);
    } else {
        // Use linear search - O(n)
        find(arr.begin(), arr.end(), target);
    }
}

// 2. Handle edge cases
int safeBinarySearch(vector<int>& arr, int target) {
    if (arr.empty()) return -1;
    
    int left = 0, right = arr.size() - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2; // Avoid overflow
        
        if (arr[mid] == target) return mid;
        else if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    
    return -1;
}

// 3. Use STL algorithms when appropriate
void useSTLSearch() {
    vector<int> arr = {1, 2, 3, 4, 5};
    
    // Binary search (requires sorted array)
    bool found = binary_search(arr.begin(), arr.end(), 3);
    
    // Lower bound
    auto it = lower_bound(arr.begin(), arr.end(), 3);
    
    // Upper bound
    auto it2 = upper_bound(arr.begin(), arr.end(), 3);
}
```

---

## 🎓 Summary

Searching algorithms are fundamental for data retrieval:

✅ **Linear Search**: O(n) for unsorted data  
✅ **Binary Search**: O(log n) for sorted data  
✅ **Variants**: Handle rotated arrays, 2D matrices, duplicates  
✅ **Applications**: Search space reduction, optimization problems  
✅ **STL Support**: Use built-in functions when possible  

---

<div align="center">

**🔍 Search Smart, Find Fast**

*Efficient algorithms for data discovery*

</div>