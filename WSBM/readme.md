## What?
The impiementation of Weighted Stochastic Block Model, with a slight change on [this paper](/Weighted%20Stochastic%20Block%20Model%20.pdf) [Secotion 2.1] for handling outliers.

**Input $\to$** Two positive integers $n \leq \text{MAXN}$ and $k \leq \text{MAXK}$ are given in the first line which are the number of vertices and clusters respectively.

In the next line, $k$ numbers are given which are the size of $k$ clusters. Sum of these numbers is at most $n$.

Then 4 number $0 \leq a, b, c, d \leq 1$ are given which are the probabilty of presence of an edge
- inside a cluster
- between two clusters
- between two outliers
- between an outlier and a cluster

respecitvely.

Then 4 probability distributions $p_0, p_1, p_2, p_3$ are given such that each of them is either exponentional or uniform and they describe the distributions of edge weights
- inside a cluster
- between two clusters
- between two outliers
- between an outlier and a cluster

respectively.

**Output $\to$** The final graph. The first line of the outputs contains $n$ and $m$, number of vertices and edges of the graph. In each of the next $m$ lines an edge is described by $0 \leq u < n$, $0 \leq v < n$ and $w$.

**Implementation $\to$** Details are commented on [the code](/WSBM.cpp).
