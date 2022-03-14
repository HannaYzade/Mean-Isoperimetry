#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000 * 1000, MAXM = 100 * 1000 * 1000; //maximum possible number of vertices and edges respectively

int n, m; //number of vertices and edges of input graph
int h[MAXN], dsu_par[MAXN + 5]; //height and par in dsu algorithm
int dfs_par[MAXN + 5]; //par in rooted tree
vector <int> adj[MAXN + 5]; //the adjacency list of MST
bool mark[MAXN + 5]; //dfs' mark

struct edge {
    int u, v, w, ind;
    edge (int _u = 0, int _v = 0, int _w = 0, int _ind = 0) {
        u = _u, v = _v, w = _w;
        ind = _ind;
    }
} e[MAXM + 5];

bool cmp(edge e1, edge e2) { //used for sorting edges
    if (e1.w < e2.w)
        return true;
    if (e2.w < e1.w)
        return false;
    return (e1.ind < e2.ind);
}

void dfs(int v) { //dfs is used at the end to output a rooted tree
    mark[v] = true;
    for (int i = 0; i < (int)adj[v].size(); i ++) {
        int ind = adj[v][i];
        int u = e[ind].v;
        if (u == v)
            u = e[ind].u;
        if (! mark[u]) {
            dfs_par[u] = ind; //index of the edge between u and par_u
            dfs (u);
        }
    }
    return;
}

int find_par(int v) {
    if (dsu_par[v] == v)
        return v;
    dsu_par[v] = find_par(dsu_par[v]);
    return dsu_par[v];
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0); //for fast I/O

    //input
    cin >> n >> m;
    for (int i = 0; i < m; i ++) {
        cin >> e[i].v >> e[i].u >> e[i].w;
        e[i].ind = i;
    }

    //initialize
    for (int i = 0; i < n; i ++)
        dsu_par[i] = i;

    //kruskal
    sort(e, e + m, cmp);
    for (int i = 0; i < m; i ++) {
        int paru = find_par(e[i].u), parv = find_par(e[i].v);
        if (paru != parv) { //if u and v aren't in the same component
            adj[e[i].u].push_back(i), adj[e[i].v].push_back(i);
            if(h[paru] < h[parv])
                dsu_par[paru] = parv;
            else if(h[paru] > h[parv])
                dsu_par[parv] = paru;
            else {
                dsu_par[paru] = parv;
                h[parv] ++;
            }
        }
    }

    //make the tree rooted
    dfs (0);

    //output
    cout << n << endl;
    for (int i = 1; i < n; i ++) {
        int ind = dfs_par[i];
        if (e[ind].v == i)
            cout << e[ind].u << " " << e[ind].w << endl;
        else
            cout << e[ind].v << " " << e[ind].w << endl;
    }
    return 0;
}