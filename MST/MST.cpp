#include "MST.h"
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0); //for fast I/O
    int n, m;
    pair< pair<int, int>, int> edges[10000];
    //input
    cin >> n >> m;
    for (int i = 0; i < m; i ++)
        cin >> edges[i].first.first >> edges[i].first.second >> edges[i].second;
    
    //invoke
    pair<int, int>* krus_ans = kruskal(n, m, edges);
    pair<int, int>* prim_ans = prim(n, m, edges);

    //output
    cout << endl;
    cout << "Kruskal's Output:" << endl;
    for (int i = 1; i < n; i ++)
        cout << krus_ans[i].first << " " << krus_ans[i].second << endl;
    cout << endl;

    cout << "Prim's Output:" << endl;
    for (int i = 1; i < n; i ++)
        cout << prim_ans[i].first << " " << prim_ans[i].second << endl;
    return 0;
}