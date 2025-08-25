# Mastering Binary Search: The Efficient O(logn) Search Algorithm

Binary search stands as one of the most fundamental and efficient algorithms in programming, beloved for its **O(logn) time complexity**—a game-changer compared to linear search’s O(n) when dealing with sorted datasets. Whether you’re hunting for a specific value in an array or solving complex optimization problems, binary search streamlines the process by repeatedly halving the search interval. In this blog, we’ll break down its two core variants—integer binary search and real number binary search—and walk through their practical implementations, focusing on avoiding common pitfalls.


## The Core of Binary Search: Why It Works
At its heart, binary search relies on a simple principle: for a **sorted dataset**, you can eliminate half the remaining elements with a single check. By comparing a "midpoint" value to your target or a problem-specific condition, you narrow the search space to either the left or right half. This halving process continues until you find the answer or exhaust the search interval—resulting in logarithmic time complexity that scales exceptionally well for large datasets (e.g., searching through 1 million elements takes just ~20 steps).


## I. Integer Binary Search: For Discrete Sorted Data
Integer binary search is used when working with discrete, sorted values—think arrays of integers, indices, or counts. The key to success here lies in two critical details:  
1. Writing a **problem-specific check function** (to determine if a midpoint is "valid" for your goal).  
2. Choosing the correct midpoint calculation to avoid infinite loops (a common trap for beginners).  

The check function varies by use case: it might verify if a value at the midpoint meets a requirement (e.g., "is this element greater than the target?" or "can we complete the task with this number of resources?"). Once defined, we split the search interval `[l, r]` into two parts—here are the two most common and reliable ways to do that.


### Variant 1: Finding the Largest Valid Value  
This variant is for scenarios where you need the **largest value** that satisfies your check function. We split the interval `[l, r]` into `[l, mid - 1]` (invalid half) and `[mid, r]` (valid half, if mid passes the check).  

#### Critical Note: Midpoint Calculation  
To avoid infinite loops—especially when the interval shrinks to `l + 1 = r`—we calculate the midpoint as `(l + r + 1) >> 1` (a bitwise shortcut for `(l + r + 1) / 2`) instead of `(l + r) >> 1`. Here’s why:  
If you use `(l + r) >> 1` when `l = 2` and `r = 3`, mid becomes 2. If the check function returns `true` (meaning 2 is valid and larger values might also be valid), setting `l = mid` leaves the interval unchanged (`l = 2`, `r = 3`), causing an infinite loop. Adding 1 to the midpoint formula fixes this, ensuring the interval always shrinks.  

#### Implementation Code  
```cpp
int binary_search1() {
    int l = 1, r = n;
    while (l < r) {
        int mid = (l + r + 1) >> 1;
        if (check(mid)) l = mid;
        else r = mid - 1;
    }

    return r;
}
```


### Variant 2: Finding the Smallest Valid Value  
This variant targets the **smallest value** that passes the check function. We split the interval `[l, r]` into `[l, mid]` (valid half, if mid passes) and `[mid + 1, r]` (invalid half).  

#### Critical Note: Midpoint Calculation  
Here, we use `mid = (l + r) >> 1` (no `+1`). Using `(l + r + 1) >> 1` would risk infinite loops: if `l = 2` and `r = 3`, mid becomes 3. If the check function returns `true` (3 is valid, but smaller values might also be valid), setting `r = mid` keeps the interval `[2, 3]` unchanged. Sticking to `(l + r) >> 1` ensures the interval shrinks correctly.  

#### Implementation Code  
```cpp
int binary_search2() {
    int l = 1, r = n;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (check(mid)) r = mid;
        else l = mid + 1;
    }

    return r;
}
```


## II. Real Number Binary Search: For Continuous Ranges
Real number binary search is used when the answer lies in a **continuous range** (e.g., floating-point values like temperatures, distances, or square roots). Unlike integer binary search, we don’t rely on discrete indices—instead, we narrow the interval until it’s small enough to meet the problem’s precision requirements.


### Key Step: Defining Precision  
The first rule of real number binary search is to set a **precision (eps)** that’s slightly stricter than the problem’s requirement. For example, if the problem asks for an answer accurate to 6 decimal places, use `eps = 1e-8` (two extra decimal places). This ensures rounding errors don’t affect the final result—we treat any value beyond the `eps` threshold as negligible (effectively zero).


### Implementation Code  
```cpp
double binary_search3() {
    double eps = 1e-8;
    double l = -100, r = 100;
    while (r - l > eps) {
        double mid = (l + r) / 2;
        if (check(mid)) l = mid;
        else r = mid;
    }
    return l;
}
```

#### How It Works:  
- We start with a range `[l, r]` (adjusted to fit your problem—e.g., `[-1e9, 1e9]` for large values).  
- In each iteration, we calculate `mid` as the average of `l` and `r` (no bitwise shifts here, since we’re working with doubles).  
- The check function determines if `mid` is on the "valid" side of the range: if yes, we move `l` to `mid`; if not, we move `r` to `mid`.  
- We stop when the interval `r - l` is smaller than `eps`—at this point, `l` (or `r`) is sufficiently close to the true answer.


## Common Pitfalls to Avoid
1. **Forgetting Sorted Data**: Binary search only works on sorted datasets. Always ensure your data is sorted (ascending or descending) before starting.  
2. **Incorrect Midpoint Calculation**: As we saw, using `(l + r) >> 1` for the "largest valid" variant (or `+1` for the "smallest valid" variant) causes infinite loops. Memorize the two variants’ midpoint rules.  
3. **Ignoring Precision in Real Number Search**: Using too loose a precision (e.g., `1e-6` for a problem requiring `1e-8`) leads to incorrect answers. Always add 2 extra decimal places to `eps`.  
4. **Vague Check Functions**: The check function is the backbone of binary search. If it’s unclear (e.g., "does this midpoint get me close to the target?"), your algorithm will fail. Define it to answer a clear yes/no question about validity.


## When to Use Binary Search
Binary search isn’t just for "finding a value in an array"—it’s a versatile tool for:  
- **Optimization Problems**: Finding the minimum/maximum value that satisfies a condition (e.g., "the maximum number of students that can fit in a classroom").  
- **Range Queries**: Determining the first/last occurrence of a value in a sorted array.  
- **Mathematical Problems**: Calculating square roots, cube roots, or solving equations (e.g., finding x where `x² = 25`).  


## Final Thoughts
Binary search is a cornerstone of efficient programming, and mastering its two variants will save you time and effort across countless projects. The key to success is understanding **how to split the interval** and **why the midpoint calculation matters**—once you nail these, you’ll avoid infinite loops and build reliable algorithms.  

Start practicing with simple problems (e.g., finding a target in a sorted array) and gradually move to complex optimization tasks. With time, binary search will become second nature—and you’ll wonder how you ever coded without it!