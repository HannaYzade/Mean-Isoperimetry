#include "riso.h"
using namespace std; 

int n, k, rho, pi[1000];
pair<int, int> par[1000];

int main() {
    ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0); //for fast I/O

    //input
    cin >> n >> k >> rho;
    for (int i = 0; i < n; i ++)
        cin >> pi[i];
    for (int i = 1; i < n; i ++) {
        int _par, _w;
        cin >> _par >> _w;
        par[i] = {_par, _w};
    }
    
    //solve
    pair<double, int*> p = get_riso(n, k, rho, pi, par);
    
    //output
    cout << "Minimum Cost: " << setprecision(7) << fixed << p.first << endl << "Clustering: ";
    for (int i = 0; i < n; i ++)
        cout << (p.second)[i] << " ";
    cout << endl;
    return 0;
}