## What?
This folder contains codes used to compare the outputs of a [brute force code](/Brute%20Force%20Algorithm/brute_force_code.cpp) and [dp code](../DP%20Algorithm/main.cpp) to check whether the implementation of dp algorithm is OK.

**test_generator.cpp $\to$** Outputs a test case in the following form:

$n\ k\ \rho$

$\pi(0)\ \pi(1) \dots \pi(n - 1)$

$p_1\ w_1$

$p_2\ w_2$

$\vdots$

$p_{n-1}\ w_{n-1}$

All numbers are non-negative integers. Vertices are supposed to be labled with $\{0, 1, 2, \dots, n - 1\}$ and the tree is supposed to be rooted from vertex $0$. 

$k$ is the number of clusters and $\rho$ is the maximum possible number of outliers. $\pi(i)$ is the weight of vertex $i$ and $p_i$ is the parent of vertex $i$. $w_i$ is the weight of the edge between $i$ and $p_i$.

There are also the following constraints:

- $\text{MINN} \leq n \leq \text{MAXN} \quad , \quad 2 \leq k \leq \text{MAXK} \quad , \quad 0 \leq \rho \leq \text{MAX\_RHO}$
- $1 \leq w_i \leq \text{MAX\_EDGE} \quad , \quad p_i < i \quad , \quad \sum_{i = 0}^{n-1} \pi(i) \leq \text{MAX\_SUMPI}$
- There is at least one valid clustering for the test case.

**input_maker.bash $\to$** Generates 50 test cases by running [test_generator.cpp](/test_generator.cpp).

**output_maker.bash $\to$** First runs the [brute force code](/Brute%20Force%20Algorithm/brute_force_code.cpp) on the generated inputs and store the results in the [Brute Force Outputs](/Outputs/Brute%20Force%20Outputs/) folder. Then runs the [dp code](../DP%20Algorithm/main.cpp) on generated inputs and store the results in the [DP Outputs](/Outputs/DP%20Outputs/) folder.

**diff_maker.bash $\to$** Outputs the differences between outputs in [Brute Force Outputs](/Outputs/Brute%20Force%20Outputs/) folder and [DP Outputs](/Outputs/DP%20Outputs/) folder.

## How?
Open the terminal from "Correctenss Testing" folder.

To generate inputs and outputs, run the following commands:
```
./input_maker.bash
./output_maker.bash
```
To get the differences of exisiting outputs, run the following command:
```
./diff_maker.bash
```