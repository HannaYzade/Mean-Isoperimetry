#ifndef RISO_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define RISO_H

#include<bits/stdc++.h>
using namespace std;

const int MAXN = 446; //maximum possible number of vertices
const int MAXK = 10; //maximum possible number of clusters
const int MAX_RHO = 10; //maximum possible rho
const int MAX_SUMPI = 446; //maximum possible amount for sum of pi[v]s
const int INF = INT_MAX / 3; //This constraint avoids overflow! Also since (sum w_i) <= 3*10^8 -> ans_value < 2*sum w_i <= 6*10^8 < INT_MAX/3 = INF

int ans[MAXN + 2];
double ans_value = INF;
int sum_pi, sz[MAXN + 2]; //sum_pi is sum of pi[i]'s and sz[v] is the sum of pi[i]'s in the v's subtree
vector <int> child[MAXN + 2], c[MAXN + 2]; //the tree's children list, the corresponding edge weights

double dp[MAXK + 1][MAX_SUMPI + 2][MAX_SUMPI + 2][MAX_RHO + 1][2]; 
//dp[v][k][w][d][rho][b]: bar{phi}_{k,w,d,rho,b}(T_v) in the paper 
//and the first dimension is dropped due to memory limits. 
//For each v dp[v][][][][][] is saved in dp/v.txt.
double par_dp[2][MAXK + 1][MAX_SUMPI + 2][MAX_SUMPI + 2][MAX_RHO + 1][2]; 
//par_dp[v][k][w][d][rho][b]: bar{phi}_{k,w,d,rho,b}(T_{par v, ind v in par v's children}) in the paper
//according to the way of update, at each moment we only need par_dp for two vertices. So the size of the first dimension is 2.
//For each v par_dp[v][][][][][] is saved in par_dp/v.txt.

//since the dp only calculates the cost of optimal solution and not the clustering, we need to keep track of updates.
//node is a struct that help us to keep track of the path of dp
//each cell of dp gets updated from some other cells, 
//the necessory information to figure those cells out later is stored in the cell's corresponding node.
struct node {
    int k, w, d, rho;
    bool b, b2;
    node (int _k = INF, int _w = 0, int _d = 0, int _rho = 0, bool _b = false, bool _b2 = false) {
        k = _k, w = _w, d = _d, rho = _rho;
        b = _b, b2 = _b2;
    }
} par_dp_path[MAXK + 1][MAX_SUMPI + 2][MAX_SUMPI + 2][MAX_RHO + 1][2];
//the first dimension of par_dp_path is also dropped due to memory limitations
//par_dp_path[v][][][][][] is stored in par_dp_path/v.txt



void init_dp() {
    for (int _k = 0; _k < MAXK + 1; _k ++)
        for (int _w = 0; _w < MAX_SUMPI + 2; _w ++)
            for (int _d = 0; _d < MAX_SUMPI + 2; _d ++)
                for (int _rho = 0; _rho < MAX_RHO + 1; _rho ++)
                    for (int _b = 0; _b < 2; _b ++)
                        dp[_k][_w][_d][_rho][_b] = INF;
    return;
}

void init_par_dp(int ind) {
    for (int _k = 0; _k < MAXK + 1; _k ++)
        for (int _w = 0; _w < MAX_SUMPI + 2; _w ++)
            for (int _d = 0; _d < MAX_SUMPI + 2; _d ++)
                for (int _rho = 0; _rho < MAX_RHO + 1; _rho ++)
                    for (int _b = 0; _b < 2; _b ++) {
                        par_dp[ind][_k][_w][_d][_rho][_b] = INF;
                        par_dp_path[_k][_w][_d][_rho][_b] = node();
                    }
    return;
}

void dfs(int v, int n, int k, int rho, int pi[], pair<int, int> par[]) {
    sz[v] = pi[v];
    if ((int) child[v].size() == 0) { //leaf
        //store the dp in disk
        ofstream dpv ("../DP Algorithm/dp/" + to_string(v) + ".txt");
        for (int _k = 0; _k <= k; _k ++) {
            for (int _w = 0; _w <= sz[v]; _w ++) {
                for (int _d = 0; _d <= sum_pi; _d ++) {
                    for (int _rho = 0; _rho <= rho; _rho ++) {
                        for (int _b = 0; _b < 2; _b ++) {
                            if (_k == 0 && _w == 0 && _d == 0 && _b == 0 && _rho > 0) 
                                dpv << 0 << '\n';
                            else if (_k == 1 && _w == pi[v] && _d > 0)
                                dpv << setprecision(12) << fixed << (double)par[v].second / _d << '\n';
                            else
                                dpv << INF << '\n';
                        }
                    }
                }
            }
        }
        dpv.close();
        return;
    }

    for (int i = 0; i < (int)child[v].size(); i ++) {
        dfs (child[v][i], n, k, rho, pi, par);
        sz[v] += sz[child[v][i]];
    }

    //load dp of the first child of v from disk
    int u = child[v][0], w = c[v][0];
    ifstream dpu ("../DP Algorithm/dp/" + to_string(u) + ".txt");
    init_dp();
    for (int _k = 0; _k <= k; _k ++) 
        for (int _w = 0; _w <= sz[u]; _w ++) 
            for (int _d = 0; _d <= sum_pi; _d ++) 
                for (int _rho = 0; _rho <= rho; _rho ++) 
                    for (int _b = 0; _b < 2; _b ++) 
                        dpu >> dp[_k][_w][_d][_rho][_b];
    dpu.close();

    //update par_dp and par_dp_path for the first child of v
    init_par_dp(0);
    //case 1: i = 0 and w = 0 -> d = 0 and b = 0
    for (int _k = 0; _k <= k; _k ++)
        for (int _rho = 1; _rho <= rho; _rho ++) 
            for (int _w1 = 0; _w1 <= sz[u]; _w1 ++)
                for (int _b1 = 0; _b1 < 2; _b1 ++)
                    if (dp[_k][_w1][_w1][_rho - 1][_b1] != INF && par_dp[0][_k][0][0][_rho][0] > dp[_k][_w1][_w1][_rho - 1][_b1]) {
                        par_dp[0][_k][0][0][_rho][0] = dp[_k][_w1][_w1][_rho - 1][_b1];
                        par_dp_path[_k][0][0][_rho][0] = node(_k, _w1, _w1, _rho - 1, _b1); 
                    }
    //case 2: i = 0 and w > 0 and b = false -> w = pi[v]
    for (int _k = 1; _k <= k; _k ++)
        for (int _d = 1; _d <= sum_pi; _d ++) 
            for (int _rho = 0; _rho <= rho; _rho ++)
                for (int _w1 = 0; _w1 <= sz[u]; _w1 ++)
                    for (int _b1 = 0; _b1 < 2; _b1 ++) {
                        if (dp[_k - 1][_w1][_w1][_rho][_b1] != INF && par_dp[0][_k][pi[v]][_d][_rho][0] > dp[_k - 1][_w1][_w1][_rho][_b1] + (double)(par[v].second + w) / _d) {
                            par_dp[0][_k][pi[v]][_d][_rho][0] = dp[_k - 1][_w1][_w1][_rho][_b1] + (double)(par[v].second + w) / _d;
                            par_dp_path[_k][pi[v]][_d][_rho][0] = node(_k - 1, _w1, _w1, _rho, _b1);
                        }
                    }
    //case 3: i = 0 and w > 0 and b = true
    for (int _k = 1; _k <= k; _k ++)
        for (int _w = pi[v] + 1; _w <= sz[v]; _w ++)
            for (int _d = 1; _d <= sum_pi; _d ++) 
                for (int _rho = 0; _rho <= rho; _rho ++)
                    for (int _b1 = 0; _b1 < 2; _b1 ++) 
                        if (dp[_k][_w - pi[v]][_d][_rho][_b1] != INF && par_dp[0][_k][_w][_d][_rho][1] > dp[_k][_w - pi[v]][_d][_rho][_b1] + (double)(par[v].second - w) / _d) {
                            par_dp[0][_k][_w][_d][_rho][1] = dp[_k][_w - pi[v]][_d][_rho][_b1] + (double)(par[v].second - w) / _d;
                            par_dp_path[_k][_w][_d][_rho][1] = node(_k, _w - pi[v], _d, _rho, _b1);
                        }
    
    //store par_dp and par_dp_path of v's first child in disk
    ofstream par_dpu ("../DP Algorithm/par_dp/" + to_string(u) + ".txt");
    ofstream par_dp_pathu ("../DP Algorithm/par_dp_path/" + to_string(u) + ".txt");
    for (int _k = 0; _k <= k; _k ++) 
        for (int _w = 0; _w <= sz[v]; _w ++) 
            for (int _d = 0; _d <= sum_pi; _d ++) 
                for (int _rho = 0; _rho <= rho; _rho ++) 
                    for (int _b = 0; _b < 2; _b ++) {
                        par_dpu << setprecision(12) << fixed << par_dp[_k][_w][_d][_rho][_b] << '\n';
                        node n = par_dp_path[_k][_w][_d][_rho][_b];
                        par_dp_pathu << n.k << ' ' << n.w << ' ' << n.d << ' ' << n.rho << ' ' << n.b << ' ' << n.b2 << '\n';
                    } 
    par_dpu.close();
    par_dp_pathu.close();

    //update par_dp and par_dp_path of other children of v
    for (int i = 1; i < (int)child[v].size(); i ++) {
        u = child[v][i], w = c[v][i];
        int pu = child[v][i - 1], cur = i % 2, pcur = (i - 1) % 2;
        //load dp[u][][][][][] from disk
        ifstream dpu ("../DP Algorithm/dp/" + to_string(u) + ".txt");
        init_dp();
        for (int _k = 0; _k <= k; _k ++) 
            for (int _w = 0; _w <= sz[u]; _w ++) 
                for (int _d = 0; _d <= sum_pi; _d ++) 
                    for (int _rho = 0; _rho <= rho; _rho ++) 
                        for (int _b = 0; _b < 2; _b ++) 
                            dpu >> dp[_k][_w][_d][_rho][_b];
        dpu.close();
        init_par_dp(cur);

        //case 4: i > 0, w = 0 -> d = 0 and b = 0
        for (int _k = 0; _k <= k; _k ++)
            for (int _rho = 1; _rho <= rho; _rho ++)
                for (int _k1 = 0; _k1 <= _k; _k1 ++)
                    for (int _w1 = 0; _w1 <= sz[u]; _w1 ++)
                        for (int _rho1 = 1; _rho1 <= _rho; _rho1 ++)
                            for (int _b1 = 0; _b1 < 2; _b1 ++)
                                if (par_dp[pcur][_k1][0][0][_rho1][0] < INF && dp[_k - _k1][_w1][_w1][_rho - _rho1][_b1] < INF && par_dp[cur][_k][0][0][_rho][0] > par_dp[pcur][_k1][0][0][_rho1][0] + dp[_k - _k1][_w1][_w1][_rho - _rho1][_b1]) {
                                    par_dp[cur][_k][0][0][_rho][0] = par_dp[pcur][_k1][0][0][_rho1][0] + dp[_k - _k1][_w1][_w1][_rho - _rho1][_b1];
                                    par_dp_path[_k][0][0][_rho][0] = node(_k - _k1, _w1, _w1, _rho - _rho1, _b1, false);
                                }
        //case 5: i > 0 and w > 0 and b = false
        for (int _k = 1; _k <= k; _k ++)
            for (int _w = pi[v]; _w <= sz[v]; _w ++)
                for (int _d = 1; _d <= sum_pi; _d ++) 
                    for (int _rho = 0; _rho <= rho; _rho ++)
                        for (int _k1 = 1; _k1 <= _k; _k1 ++)
                            for (int _rho1 = 0; _rho1 <= _rho; _rho1 ++)
                                for (int _w1 = 0; _w1 <= sz[u]; _w1 ++)
                                    for (int _b1 = 0; _b1 < 2; _b1 ++)
                                        for (int _b2 = 0; _b2 < 2; _b2 ++)
                                            if(par_dp[pcur][_k1][_w][_d][_rho1][_b1] < INF && dp[_k - _k1][_w1][_w1][_rho - _rho1][_b2] < INF &&  par_dp[cur][_k][_w][_d][_rho][0] > par_dp[pcur][_k1][_w][_d][_rho1][_b1] + dp[_k - _k1][_w1][_w1][_rho - _rho1][_b2] + (double)w / _d) {
                                                par_dp[cur][_k][_w][_d][_rho][0] = par_dp[pcur][_k1][_w][_d][_rho1][_b1] + dp[_k - _k1][_w1][_w1][_rho - _rho1][_b2] + (double)w / _d;
                                                par_dp_path[_k][_w][_d][_rho][0] = node(_k - _k1, _w1, _w1, _rho - _rho1, _b2, _b1);
                                            }
        //case 6: i > 0 and w > 0 and b = true
        for (int _k = 1; _k <= k; _k ++)
            for (int _w = pi[v] + 1; _w <= sz[v]; _w ++)
                for (int _d = 1; _d <= sum_pi; _d ++) 
                    for (int _rho = 0; _rho <= rho; _rho ++)
                        for (int _k1 = 1; _k1 <= _k; _k1 ++)
                            for (int _rho1 = 0; _rho1 <= _rho; _rho1 ++)
                                for (int _w1 = pi[v]; _w1 <= _w; _w1 ++)
                                    for (int _b1 = 0; _b1 < 2; _b1 ++)
                                        for (int _b2 = 0; _b2 < 2; _b2 ++)
                                            if(par_dp[pcur][_k1][_w1][_d][_rho1][_b1] < INF && dp[_k - _k1 + 1][_w - _w1][_d][_rho - _rho1][_b2] < INF && par_dp[cur][_k][_w][_d][_rho][1] > par_dp[pcur][_k1][_w1][_d][_rho1][_b1] + dp[_k - _k1 + 1][_w - _w1][_d][_rho - _rho1][_b2] - (double)w / _d) {
                                                par_dp[cur][_k][_w][_d][_rho][1] = par_dp[pcur][_k1][_w1][_d][_rho1][_b1] + dp[_k - _k1 + 1][_w - _w1][_d][_rho - _rho1][_b2] - (double)w / _d;
                                                par_dp_path[_k][_w][_d][_rho][1] = node(_k - _k1 + 1, _w - _w1, _d, _rho - _rho1, _b2, _b1);
                                            }

        //store par_dp[u] and par_dp_path[u] in disk                                
        ofstream par_dpu ("../DP Algorithm/par_dp/" + to_string(u) + ".txt");
        ofstream par_dp_pathu ("../DP Algorithm/par_dp_path/" + to_string(u) + ".txt");
        for (int _k = 0; _k <= k; _k ++) 
            for (int _w = 0; _w <= sz[v]; _w ++) 
                for (int _d = 0; _d <= sum_pi; _d ++) 
                    for (int _rho = 0; _rho <= rho; _rho ++) 
                        for (int _b = 0; _b < 2; _b ++) {
                            par_dpu << setprecision(12) << fixed << par_dp[_k][_w][_d][_rho][_b] << '\n';
                            node n = par_dp_path[_k][_w][_d][_rho][_b];
                            par_dp_pathu << n.k << ' ' << n.w << ' ' << n.d << ' ' << n.rho << ' ' << n.b << ' ' << n.b2 << '\n';
                        } 
        par_dpu.close();
        par_dp_pathu.close();
    }

    //update dp[v][][][][][] from par_dp[v's last child][][][][][]
    for (int _k = 0; _k <= k; _k ++)
        for (int _w = 0; _w <= sz[v]; _w ++)
            for (int _d = 0; _d <= sum_pi; _d ++) 
                for (int _rho = 0; _rho <= rho; _rho ++)
                    for (int _b = 0; _b < 2; _b ++)
                        dp[_k][_w][_d][_rho][_b] = par_dp[((int)child[v].size() - 1) % 2][_k][_w][_d][_rho][_b];
   
    //store dp[v][][][][][][] into disk
    ofstream dpv ("../DP Algorithm/dp/" + to_string(v) + ".txt");
    for (int _k = 0; _k <= k; _k ++) 
        for (int _w = 0; _w <= sz[v]; _w ++) 
            for (int _d = 0; _d <= sum_pi; _d ++) 
                for (int _rho = 0; _rho <= rho; _rho ++) 
                    for (int _b = 0; _b < 2; _b ++) 
                        dpv << setprecision(12) << fixed << dp[_k][_w][_d][_rho][_b] << '\n';
    dpv.close();
    return;
}


//this function alternatively points out to a cell of dp and then to the corresponding cell in par_dp
//note that dp[v][][][][][] = par_dp[last child of v][][][][][]
//in the case of pointing out to dp, v get assigned to a cluster
//is_par_dp shows the function is pointing out to a cell of dp or par_dp
//in_par_cluster is valid only if is_par_dp is false and it shows if we should be in its par's cluster
//in_child_cluster is true if v's last child should be in the v's cluster

int smallest_unused_color = 1;
void find_path(int n, int k, int rho, int pi[], pair<int, int> par[], int v, int _k, int w, int d, int _rho,  bool in_par_cluster, bool in_child_cluster, bool is_par_dp) {
    if(!is_par_dp) { //dp
        if (w == 0)
            ans[v] = 0;
        else 
            if (in_par_cluster)
                ans[v] = ans[par[v].first];
            else    
                ans[v] = smallest_unused_color ++;
        if ((int)child[v].size() == 0)
            return;
        find_path (n, k, rho, pi, par, v, _k, w, d, _rho, false, in_child_cluster, true);
    }
    else { //par_dp
        //find the path of par_dp for v's children
        for (int i = (int)child[v].size() - 1; i >= 0; i --) {
            int u = child[v][i];

            //load par_dp_path from disk
            ifstream par_dp_pathu ("../DP Algorithm/par_dp_path/" + to_string(u) + ".txt");
            init_par_dp(0);
            for (int _k_ = 0; _k_ <= k; _k_ ++) 
                for (int _w = 0; _w <= sz[v]; _w ++) 
                    for (int _d = 0; _d <= sum_pi; _d ++) 
                        for (int _rho_ = 0; _rho_ <= rho; _rho_ ++) 
                            for (int _b = 0; _b < 2; _b ++) 
                                par_dp_pathu >> par_dp_path[_k_][_w][_d][_rho_][_b].k >> par_dp_path[_k_][_w][_d][_rho_][_b].w >> par_dp_path[_k_][_w][_d][_rho_][_b].d >> par_dp_path[_k_][_w][_d][_rho_][_b].rho >> par_dp_path[_k_][_w][_d][_rho_][_b].b >> par_dp_path[_k_][_w][_d][_rho_][_b].b2;
            par_dp_pathu.close();

            node _par = par_dp_path[_k][w][d][_rho][in_child_cluster];
            find_path(n, k, rho, pi, par, u, _par.k, _par.w, _par.d, _par.rho, in_child_cluster, _par.b, false);
            _k -= _par.k;
            if (w > 0 && in_child_cluster == true) {
                _k ++;
                w -= _par.w;
            }
            _rho -= _par.rho;
            in_child_cluster = _par.b2;
        }
    }
    return;
}

//take n, k, rho, the array of vertices' weights and the array of vertices' {par, edge weight to par}
//return the pair of {opt value, pointer to array of opt clustering}
pair<double, int*> get_riso(int n, int k, int rho, int pi[], pair<int, int> par[]) {
    //initialize
    init_dp();
    init_par_dp(0), init_par_dp(1);
    par[0] = {-1, 0};
    
    //fill the adj list
    for (int i = 1; i < n; i ++) {
        child [par[i].first].push_back(i);
        c[par[i].first].push_back(par[i].second);
    }

    for (int i = 0; i < n; i ++)
        sum_pi += pi[i];

    //filling dp / par_dp / par_dp_path
    dfs (0, n, k, rho, pi, par);
    //calculating the minimum cost
    node root;
    for (int _w = 0; _w <= sz[0]; _w ++)
        for (int _b = 0; _b < 2; _b ++)
            if (dp[k][_w][_w][rho][_b] != INF && ans_value > dp[k][_w][_w][rho][_b]) {
                ans_value = dp[k][_w][_w][rho][_b];
                root = node(k, _w, _w, rho, _b); //we need the corresponding node of optimal cost to find the dp's path
            }

    //finding the dp's path recursively        
    find_path(n, k, rho, pi, par, 0, root.k, root.w, root.d, root.rho, false, root.b, false); //function inputs:n, k, rho, pi, par, _v, _k, _w, _d, _rho, in_par_cluster, in_child_cluster, is_par_dp
    //note: size of ans is n as the input
    return {ans_value, ans};
}

#endif