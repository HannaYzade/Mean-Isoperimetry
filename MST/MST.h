#ifndef MST_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define MST_H

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000 * 1000, MAXM = 100 * 1000 * 1000; //maximum possible number of vertices and edges respectively

//prim variables
vector<int> adj[MAXN], w[MAXN]; //prim input's adjacency list and corresponding weights
set<pair<int, int> > mys;
bool prim_mark[MAXN];
pair<int, int> prim_edges[MAXN]; //pair of [par, weight of edge to par] in the MST rooted from 0

//kruskal variables
int h[MAXN], dsu_par[MAXN + 5]; //height and par in dsu algorithm
int dfs_par[MAXN + 5]; //par in rooted tree
vector <int> MST_kruskal_adj[MAXN + 5]; //the adjacency list of kruskal MST
bool dfs_mark[MAXN + 5]; //dfs's mark
pair<int, int> kruskal_edges[MAXN + 5]; //pair of [par, weight of edge to par] in the MST rooted from 0

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
    dfs_mark[v] = true;
    for (int i = 0; i < (int)MST_kruskal_adj[v].size(); i ++) {
        int ind = MST_kruskal_adj[v][i];
        int u = e[ind].v;
        if (u == v)
            u = e[ind].u;
        if (! dfs_mark[u]) {
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

pair<int, int>* kruskal (int n, int m, pair<pair<int, int>, int>  edges[]) {
     //initialize
    for (int i = 0; i < n; i ++)
        dsu_par[i] = i;
    for (int i = 0; i < m; i ++)
        e[i] = edge(edges[i].first.first, edges[i].first.second, edges[i].second, i);


    //kruskal
    sort(e, e + m, cmp);
    for (int i = 0; i < m; i ++) {
        int paru = find_par(e[i].u), parv = find_par(e[i].v);
        if (paru != parv) { //if u and v aren't in the same component
            MST_kruskal_adj[e[i].u].push_back(i), MST_kruskal_adj[e[i].v].push_back(i);
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

    kruskal_edges[0] = {-1, 0};
    for (int i = 1; i < n; i ++) {
        int ind = dfs_par[i];
        if (e[ind].v == i)
            kruskal_edges[i] = {e[ind].u, e[ind].w};
        else
            kruskal_edges[i] = {e[ind].v, e[ind].w};
    }
    
    return kruskal_edges;
}

pair<int, int>* prim(int n, int m, pair<pair<int, int>, int> edges[]) {
    for (int i = 0; i < m; i ++) {
        int u = edges[i].first.first, v = edges[i].first.second, wei = edges[i].second;
        adj[u].push_back(v), adj[v].push_back(u);
        w[u].push_back(wei), w[v].push_back(wei);
    }
    mys.insert({0, 0});
    prim_edges[0] = {-1, 0};
    for (int i = 1; i < n; i ++) {
        mys.insert({INT_MAX, i});
        prim_edges[i] = {-1, INT_MAX};
    }
    for (int i = 0; i < n; i ++) {
        int v = mys.begin() -> second;
        
        mys.erase(mys.begin());
        prim_mark[v] = true;
        for (int j = 0; j < (int)adj[v].size(); j ++) {
            int u = adj[v][j], wei = w[v][j];
            if (!prim_mark[u] && prim_edges[u].second > wei) {
                mys.erase({prim_edges[u].second, u});
                prim_edges[u] = {v, wei};
                mys.insert({prim_edges[u].second, u});
            }
        }
    }

    return prim_edges;
}

#endif