## What?
The folder contains two algorithms, [Kruskal](/kruskal.cpp) and [Prim](/prim.cpp), for finding MST. Input and output formats of them is the same and in the following form:

**Input $\to$** Two positive integers $n \leq \text{MAXN}$ and $m \leq \text{MAXM}$ are given in the first line which are the number of vertices and edges of the input graph respectively. Vertices of the graph are supposed to be labled with $\{0, 1, 2, \dots, n - 1\}$.

In each of the following $m$ line a weighted edge is described, i.e, 3 integers $0 \leq u < n$, $0 \leq v < n$ and $w$.

More Specifically:

$n$ $m$

$u_1$ $v_1$ $w_1$

$u_2$ $v_2$ $w_2$

$\vdots$

$u_m$ $v_m$ $w_m$

**Output $\to$** An MST of the input graph, rooted from vertex 0:

$n$

$p_1\ w_1$

$p_2\ w_2$

$\vdots$

$p_{n-1}\ w_{n-1}$

$p_i$ is the parent of vertex $i$ and $w_i$ is the weight of the edge between $i$ and $p_i$.

**Implementation $\to$** Prim and Kruskal!