The folder contains a headerfile ([MST.h](./MST.h)) including the implementation of Kruskal and Prim algorithms, and a runnable code ([MST.cpp](./MST.cpp)) that uses the prim and kruskal implemented in [MST.h](./MST.h).

## [MST.h](./MST.h)
The file contains two functions prim($n$, $m$, $\text{edges}$) and kruskal($n$, $m$, $\text{edges}$). Both functions take a weighted graph as input and return a Minimum Spanning Tree of the input graph. The Input and Output format is the same for both and in the following format:

**Input $\to$** 
$n$, 
$m$, 
$\text{edges}$ 
where 
$1 \leq n \leq$ 
MAXN and 
$1 \leq m \leq$ 
MAXM are number of vertices and edges of the input graph respectively. (MAXN and MAXM are changable and declared in [MST.h](./MST.h)) 
$\text{edges}$
is an array of `pair<pair<int, int>, int>` of size 
$m$
containing the list of graph's esges, i.e., 
$\text{edges} = \{[[v_0, u_0], w_0], [[v_1, u_1], w_0], ..., [[v_{m-1}, u_{m-1}], w_{m-1}]\}$
that 
$w_i$
is the weight of the edge between 
$v_i$ and $u_i$. 
Vertices are supposed to be labled with 
$\{0, 1, 2, \dots, n - 1\}$, so $0 \leq v, u < n$.

**Returning Value $\to$** An array of `pair<int, int>` of size 
$n$
representing the MST rooted from 0, i.e., 
$\text{tree} = \{[-1, 0], [p_1, w_1], [p_2, w_2], ..., [p_{n-1}, w_{n-1}]\}$ 
where $p_i$ is the parent of vertex $i$ and $w_i$ is the weight of the edge between $i$ and $p_i$.

**Invoking $\to$** To use the functions prim and kruskal, put [MST.h](./MST.h) in your code's folder and simply add `#include "MST.h"` in the first line of your code. 

Note that there are some variables defined globally in [MST.h](./MST.h), make sure not to reuse those variables' names for a global variable in your code. 

## [MST.cpp](./MST.cpp)
This is a sample code that uses prim and kruskal function.

**Input $\to$** A test case in the following form:

$n$ $m$

$u_0$ $v_0$ $w_0$

$u_1$ $v_1$ $w_1$

$\vdots$

$u_{m-1}$ $v_{m-1}$ $w_{m-1}$

Such that 
$n$
, 
$m$
, 
$\text{edges}= \{ [[v_0, u_0], w_0], [[v_1, u_1], w_0], ..., [[v_{m-1}, u_{m-1}], w_{m-1}] \}$
is a valid input for prim and kruscal in [MST.h](./MST.h) described earlier.

**Output $\to$** The returning value of kruskal and then the returning value of prim.

**Running the Code $\to$**
For compiling and running the code, run the following terminal command from the code's folder ([MST](../MST/)):
```
g++ MST.cpp -o MST && ./MST
```
