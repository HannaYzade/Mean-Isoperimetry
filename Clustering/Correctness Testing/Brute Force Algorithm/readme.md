## What?

**Input $\to$** A test case in the following form:

$n\ k\ \rho$

$\pi(0)\ \pi(1) \dots \pi(n - 1)$

$p_1\ w_1$

$p_2\ w_2$

$\vdots$

$p_{n-1}\ w_{n-1}$

All numbers are non-negative integers. Vertices are supposed to be labled with $\{0, 1, 2, \dots, n - 1\}$ and the tree is supposed to be rooted from vertex $0$. 

$k$ is the number of clusters and 
$\rho$ is the maximum possible number of outliers. 
$\pi(i)$ is the weight of vertex 
$i$ and 
$p_i$ is the parent of vertex $i$. 
$w_i$ is the weight of the edge between $i$ and $p_i$.

There are also the following constraints:

- $1 \leq n \leq \text{MAXN}$
- $w_i \geq 1 \ , \ p_i < i$
- There is at least one valid clustering for the input.

**Output $\to$** The cost of optimal clustering and the clustering itself, i.e., a sequence of $n$ numbers 
$\text{cluster}(0), \text{cluster}(1), \dots, \text{cluster}(n-1)$
where 
$\text{cluster}(i)$
is 0 for outliers and is the number of cluster containing $i$ otherwise. 

**Implementation $\to$** According to [paper](/../Mean%20Isoperimetry%20with%20Control%20on%20Outliers.pdf) [Page 4], there is always an optimal solution whose clusters are connected. Using this fact, the algorithm recursively puts each vertex in its parent's cluster, in a new cluster or consider it as an outlier. Once all vertices are done, it checks whether the clusteting is valid and it has a lower cost compared to previous clusterings.
