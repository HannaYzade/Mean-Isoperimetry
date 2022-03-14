//brute force
#include<bits/stdc++.h>

using namespace std;

const int MAXN = 20; //maximum possible number of vertices
const int INF = INT_MAX / 3; //This constraint is for avoiding overflow but since all test cases are small, always ans_value < INF.

int n, k, rho, pi[MAXN + 2], ans[MAXN + 2];
double ans_value = INF;
int col[MAXN + 2]; //used to store the current clustering. 
vector <int> adj[MAXN + 2], c[MAXN + 2]; //the tree's adjacency list, the corresponding edge weights
pair <int, int> par[MAXN + 2]; //pair of {p_i, w_i}
int smallest_unused_color = 1, outliers = 0; //the smallest number that hasn't been used yet, the number of outliers.


void check () {
    if (smallest_unused_color != k + 1) //number of clusters is not k
        return;
    if (outliers > rho) //number of outliers is more than rho
        return;
    //calculating the cost of the clustering
    double res = 0;
    for (int i = 1; i <= k; i ++) {
        int edg = 0, ver = 0;
        for (int j = 0; j < n; j ++)
            if (col[j] == i) {
                ver += pi[j];
                for (int l = 0; l < (int)adj[j].size(); l ++)
                    if(col[adj[j][l]] != i)
                        edg += c[j][l];
            }
        res += (double)edg / ver;
    }
    //update the ans if the current clustering is optimal so far
    if (res < ans_value) {
        ans_value = res;
        for (int i = 0; i < n; i ++)
            ans[i] = col[i];
    }
    return;
}

void perm(int v) { //this function generates all connected-clusterings recursively.
    //bad cases
    if (smallest_unused_color > k + 1) { //there are already more than k clusters
        return;
    }
    if (outliers > rho) { //there are more than rho outliers
        return;
    }

    //base case
    if (v == n) { //all vertices are done
        check(); //check validity
        return;
    }

    if(par[v].first != -1 && col[par[v].first] != 0) { //v is not root and its parent is not outlier
        col[v] = col[par[v].first]; //put v in its parent's cluster
                                    //note since p_i < i, the parent's cluster is known.
        perm (v + 1); //recursion
    }

    col[v] = 0; //consider v is an outlier
    outliers ++;
    perm(v + 1); //recursion
    outliers --;

    col[v] = smallest_unused_color ++; //put v in a new cluster
    perm(v + 1); //recursion
    smallest_unused_color --;
    return;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie (0); cout.tie (0); //for fast I/O

    //input
    cin >> n >> k >> rho;
    for (int i = 0; i < n; i ++)
        cin >> pi[i];
    for (int i = 1; i < n; i ++) {
        int _par, _w;
        cin >> _par >> _w;
        par[i] = {_par, _w};
        adj[_par].push_back(i), c[_par].push_back(_w);
        adj[i].push_back(_par), c[i].push_back(_w);
    }

    //solve
    par[0] = {-1, 0};
    perm (0);

    //output
    cout << "Minimum Cost: " << setprecision(7) << fixed << ans_value << endl << "Clustering: ";
    for (int i = 0; i < n; i ++)
        cout << ans[i] << " ";
    cout << endl;
    return 0;
}