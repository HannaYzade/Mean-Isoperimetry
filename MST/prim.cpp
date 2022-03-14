#include <bits/stdc++.h>

using namespace std; 

const int MAXN = 1000 * 1000 + 5, MAXM = 100 * 1000 * 1000 + 5;
int n, m, prim_w[MAXN], prim_par[MAXN];
vector<int> adj[MAXN], w[MAXN];
set<pair<int, int> > mys;
bool prim_mark[MAXN];

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> m;
    int u, v, wei;
    for (int i = 0; i < m; i ++) {
        cin >> u >> v >> wei;
        //u --; v --;
        adj[u].push_back(v), adj[v].push_back(u);
        w[u].push_back(wei), w[v].push_back(wei);
    }

    mys.insert({0, 0});
    prim_w[0] = 0;
    prim_par[0] = -1;
    for (int i = 1; i < n; i ++) {
        mys.insert({INT_MAX, i});
        prim_w[i] = INT_MAX;
    }
    for (int i = 0; i < n; i ++) {
        v = mys.begin() -> second;
        
        mys.erase(mys.begin());
        prim_mark[v] = true;
        for (int j = 0; j < (int)adj[v].size(); j ++) {
            u = adj[v][j], wei = w[v][j];
            if (!prim_mark[u] && prim_w[u] > wei) {
                mys.erase({prim_w[u], u});
                prim_w[u] = wei;
                prim_par[u] = v;
                mys.insert({prim_w[u], u});
            }
        }
    }
    
    cout << n << endl;
    for (int i = 1; i < n; i ++) 
        cout << prim_par[i] + 1 << " " << prim_w[i] << endl;
    return 0;
}