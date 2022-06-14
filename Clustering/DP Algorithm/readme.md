## What?

**Input $\to$** A test case in the following form:

$n\ k\ \rho$

$\pi(0)\ \pi(1) \dots \pi(n - 1)$

$p_1\ w_1$

$p_2\ w_2$

$\vdots$

$p_{n-1}\ w_{n-1}$

All numbers are non-negative integers. Vertices are supposed to be labled with $\{0, 1, 2, \dots, n - 1\}$ and the tree is supposed to be rooted from vertex $0$. 

$k$ is the number of clusters and $\rho$ is the maximum possible number of outliers. $\pi(i)$ is the weight of vertex $i$ and $p_i$ is the parent of vertex $i$. $w_i$ is the weight of the edge between $i$ and $p_i$.

There are also the following constraints:

- $1 \leq n \leq$ MAXN  ,   $1 \leq k \leq$ MAXK   ,   $0 \leq \rho \leq$ MAX_RHO
- $w_i \geq 1$   ,   $\sum_{i = 0\ \text{to}\ n - 1} w_i \leq 3\times10^8$   ,   $\sum_{i = 0\ \text{to}\ n - 1} \pi(i) \leq$ MAX_SUMPI
- There is at least one valid clustering for the input.

**Output $\to$** The cost of optimal clustering and the clustering itself, i.e., a sequence of $n$ numbers $\text{ans}(0), \text{ans}(1), \dots, \text{ans}(n-1)$ where $\text{ans}(i)$ is 0 for outliers and is the number of cluster containing $i$ otherwise. 

**Implementation $\to$** The algorithm is described in the [paper](/../Mean%20Isoperimetry%20with%20Control%20on%20Outliers.pdf) [Section 3]. To use less memory, code stores some parts of dp arrays in disk. Also since the dp only finds the value of clustering, there are additional arrays and functions to manage finding the clusters. More detail is commented in the [code](main.cpp).
