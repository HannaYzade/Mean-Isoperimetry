This folder contains a headerfile ([riso.h](./riso.h)) including the implementation of the algorithm [paper](/../Mean%20Isoperimetry%20with%20Control%20on%20Outliers.pdf) [Section 3] and also a runnable program ([main.cpp](./main.cpp)) using the algorithm.

## [riso.h](./riso.h)
The file contains the function get_riso($n , k , \rho , \pi , \text{par}$) that takes a sample input for the problem and returns the optimal clustering and its value.

**get_riso's Input $\to$** 
$n , k , \rho , \pi , \text{par}$ 
where as in the paper, 
$n$ 
is the number of vertices of the tree, 
$k$ 
is the number of clusters and 
$\rho$ 
is the maximum possible number of outliers. Vertices are supposed to be labled with 
$\{0, 1, 2, \dots, n - 1\}$ 
and the tree is supposed to be rooted from vertex 0.

 $\pi$ 
 is an integer array of size 
 $n$
 , i.e., 
 $\pi = \{\pi(0), \ \pi(1), \dots, \pi(n - 1)\}$ 
 and 
 $\pi(i)$ 
 is the weight of vertex 
 $i$.

$\text{par}$ is an array of `pair<int, int>` of size $n$, i.e., 
$\text{par} = \{[-1, 0], [p_1, w_1], [p_2, w_2], ..., [p_{n-1}, w_{n-1}]\}$ 
where 
$p_i$ 
is the parent of vertex $i$ and $w_i$ is the weight of the edge between $i$ and $p_i$.

All aformentioned numbers are non-negative integers and there are also the following constraints: (Parameters that their name start with MAX are changable and declared in [riso.h](./riso.h))

- $1 \leq n \leq$ MAXN   ,   $1 \leq k \leq$ MAXK   ,   $0 \leq \rho \leq$ MAX_RHO
- $w_i \geq 1\   ,\   \sum_{i = 0\ to\ n-1} w_i \leq 3\times10^8\   ,\   \sum_{i = 0\ to\ n-1} \pi(i) \leq$ MAX_SUMPI
- There is at least one valid clustering for the input.

**get_riso's Returning Value $\to$** 
The function returns a pair 
$[\text{value}, \text{clusters}]$
that 
$\text{value}$
is the cost of the optimal clustering and 
$\text{clusters}$
is the clustering itself, i.e., an array of size $n$, i.e, 
$\text{clusters}(0), \text{clusters}(1), \dots, \text{clusters}(n-1)$
, where 
$\text{clusters}(i)$ is 0 if $i$ is an outliers and is the number of cluster containing $i$ otherwise. 

**Implementation $\to$** 
The algorithm is described in the [paper](/../Mean%20Isoperimetry%20with%20Control%20on%20Outliers.pdf) [Section 3]. To use less memory, code stores some parts of dp arrays in disk. Also since the dp only finds the value of clustering, there are additional arrays and functions to manage finding the clusters. More detail is commented in the [code](main.cpp).

**Invoking $\to$** To use the function get_riso, put [riso.h](./riso.h) in your code's folder and create 3 folders with names `dp`, `par_dp`, and `par_dp_path` in the same folder (next to [riso.h](./riso.h)). Then simply add `#include "riso.h"` in the first line of your code. 

Note that there are some variables defined globally in [riso.h](./riso.h), make sure not to reuse those variables' names for a global variable in your code. 

Also, since get_riso uses reletive paths, you can run your code from a folder `dir` only if `dir` is a child of your code's folder's parent, i.e., `../dir` is a relative path for `dir` from code's folder.

## [main.cpp](./main.cpp)

This is a sample code that uses get_riso function. 

**Input $\to$** A test case in the following form:

$n\ k\ \rho$

$\pi(0)\ \pi(1) \dots \pi(n - 1)$

$p_1\ w_1$

$p_2\ w_2$

$\vdots$

$p_{n-1}\ w_{n-1}$

Such that $n,\ k,\ \rho,\ \pi,\ \text{par}=\{[p_1, w_1], [p_2, w_2], ..., [p_{n-1}, w_{n-1}]\}$ is a valid input for get_riso. 

**Output $\to$** Prints the ouput of get_riso($n,\ k,\ \rho,\ \pi,\ \text{par}$).


**Running the Code $\to$**
- Before running the code, make sure 3 folders with names `dp`, `par_dp`, and `par_dp_path` exist in the code's folder. If those folders don't exist then creat them.

- For compiling and running the code, run the following terminal command from the code's folder ([DP Algorithm](../DP%20Algorithm/)):
```
g++ main.cpp -o main && ./main
```


- Because [riso.h](./riso.h) uses reletive paths, you can run the code from a folder `dir` only if `dir` is a child of code's folder's parent, i.e, `../dir` is a relative path for `dir` from code's folder ([DP Algorithm](../DP%20Algorithm/)). In that case make sure to use absolute or reletive paths for compiling and running the code, i.e., run the command `../"DP Algorithm"/main.cpp -o main && ../"DP Algorithm"/main` on terminal.
