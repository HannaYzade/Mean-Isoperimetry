#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MINN = 5; //minimum possible number of vertices
const int MAXN = 20; //maximum possible number of vertices
const int MAXK = 10; //maximum possible number of clusters
const int MAX_RHO = 10; //maximum possible rho
const int MAX_SUMPI = 85; //maximum possible amount for sum of pi[v]s
const int MAX_EDGE = 1000 * 1000; //maximum possible w_i

int pi[MAXN];

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

ll rand(ll l, ll r) { //this function generates an integer number in [l, r] randomly
	return l + rng() % (r - l + 1);
}

int main(int argc, char*argv[]){
    ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0); //for fast I/O
	srand(stoi(argv[1]));

	int n = rand(MINN, MAXN);
	int k = rand(2, min(n, MAXK));
	int rho = rand(0, min(n - k, MAX_RHO));
	
	//filling pi such that sum of pi[v]s be at most MAX_SUMPI
	int sum = MAX_SUMPI - n;
	for (int i = 0; i < n; i ++) {
		int a = rand(0, sum);
		sum -= a;
		pi[i] = a + 1;
		//pi[i] = 1; //uncomment this line in the case of unweighted vertices (pi = 1)
	}
	random_shuffle(pi, pi + n);

	//output
	cout << n << " " << k << " " << rho << endl;
	for (int i = 0; i < n; i ++)
		cout << pi[i] << " ";
	cout << endl;
	for (int i = 1; i < n; i ++)
		cout << rand(0, i - 1) << " " << rand(1, MAX_EDGE) << endl;
    return 0;
}