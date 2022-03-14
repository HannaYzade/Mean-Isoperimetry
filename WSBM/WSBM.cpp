#include <bits/stdc++.h>

using namespace std;

//p0 ... p3 respectively are the distribution of weights of edges inside a cluster, between two clusters, between 2 outliers, between an outlier and a cluster

const int MAXK = 1000; //maximum possible number of clusters
const int MAXN = 10000; //maximum possible number of vertices
const int MAXD = 1000 * 1000; //maximum possible size for the domain of uniform distribution

int n, k, clus_size[MAXK + 5]; //number of vertices, number of clusters and their sizes
int cluster[MAXN + 5]; //cluster of each vertex
double in_presence, bet_presence, outout_presence, outclus_presence; //the probability of presence an edge inside a cluster / between 2 clusters / between 2 outliers / between an outlier and a cluster
double  lambda[4]; //parameters of pi s if they are exponential distribution
bool is_exp[4], is_range[4];
int _min[4], _max[4]; //ranges of pi s if they are uniform from a range
int dist_sz[4], dist[4][MAXD + 5]; //size of distribution domain and its elements
int m; //number of edges in the final graph
bool adj[MAXN + 5][MAXN + 5]; //adjecency matrix


void input() {
    cout << "Enter n and k followed by size of clusters." << endl;
    cin >> n >> k;
    int np = 0;
    for (int i = 1; i <= k; i ++) {
        cin >> clus_size[i];
        for (int j = 0; j < clus_size[i]; j ++) 
            cluster[np ++] = i;
    }
    random_shuffle(cluster, cluster + n);

    cout << "Enter the probability of presence of an edge inside a cluster / between two clusters / between two outliers / between an outlier and a cluster." << endl;
    cin >> in_presence >> bet_presence >> outout_presence >> outclus_presence;
    
    for (int  i = 0; i < 4; i ++) {
        cout << "The distribution of p" << i << ". Is it exponential or uniform? (type 1/0 for exp/uni)" << endl;
        cin >> is_exp[i];
        if (is_exp[i]) {
            cout << "Enter lambda" << endl;
            cin >> lambda[i];
        }
        else {
            cout << "Type 1 to enter a range and 0 to enter a set as the domain of distribution." << endl;
            cin >> is_range[i];
            if (is_range[i]) {
                cout << "Enter min and max for the range min, min + 1, min + 2 ..., max. (Natural number less than " << RAND_MAX << ".)" << endl;
                cin >> _min[i] >> _max[i];
            }
            else {
                cout << "Enter the size of set followed by list of elements. (Size less than " << MAXD << " and elements natural number less than " << RAND_MAX << ".)" << endl;
                cin >> dist_sz[i];
                for (int j = 0; j < dist_sz[i]; j ++)
                    cin >> dist[i][j];
            }
        }
    }
    return;
}

int main () {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0); //for fast I/O
    srand(time(0)); //for random generators

    input();

    random_device rand_dev;
    default_random_engine generator(rand_dev());
    bernoulli_distribution inside_clus(in_presence), between_clus(bet_presence), outout(outout_presence), outclus(outclus_presence);
    for (int i = 0; i < n; i ++) {
        for (int j = i + 1; j < n; j ++) {
            if (cluster[i] + cluster[j] == 0) //both vertices are outliers
                adj[i][j] = adj[j][i] = outout(generator);
            else if (cluster[i] == 0 || cluster[j] == 0) //exactly one vertex is outlier
                adj[i][j] = adj[j][i] = outclus(generator);
            else if (cluster[i] == cluster[j]) //vertices are in the same cluster
                adj[i][j] = adj[j][i] = inside_clus(generator);
            else //vertices in different clusters
                adj[i][j] = adj[j][i] = between_clus(generator);
            m += adj[i][j]; //counting number of edges
        }
    }

    //uniform range
    uniform_int_distribution <int> p0(_min[0], _max[0]), p1(_min[1], _max[1]), p2(_min[2], _max[2]), p3(_min[3], _max[3]);
    //uniform set
    uniform_int_distribution <int> pp0(0, dist_sz[0] - 1), pp1(0, dist_sz[1] - 1), pp2(0, dist_sz[2] - 1), pp3(0, dist_sz[3] - 1);
    //exponential
    exponential_distribution <double> ppp0(lambda[0]), ppp1(lambda[1]), ppp2(lambda[2]), ppp3(lambda[3]);

    cout << n << " " << m << endl;
    for (int i = 0; i < n; i ++) {
        for (int j = i + 1; j < n; j ++) {
            if (adj[i][j]) { //if the edge exists
                cout << i << " " << j << " ";
                int w = 0;
                if (cluster[i] + cluster[j] == 0) { //both vertices are outliers -> p2 distribution
                    if (is_exp[2]) 
                        w = ppp2(generator);
                    else if (is_range[2])
                        w = p2(generator);
                    else   
                        w = dist[2][pp2(generator)]; 
                }
                else if (cluster[i] == 0 || cluster[j] == 0) { //exactly one vertex is outlier -> p3 distribution
                    if (is_exp[3]) 
                        w = ppp3(generator);
                    else if (is_range[3])
                        w = p3(generator);
                    else   
                        w = dist[3][pp3(generator)]; 
                }
                else if (cluster[i] == cluster[j]) { //vertices are in the same cluster -> p0
                    if (is_exp[0]) 
                        w = ppp0(generator);
                    else if (is_range[0])
                        w = p0(generator);
                    else   
                        w = dist[0][pp0(generator)]; 
                }
                else { //vertices in different clusters -> p1
                    if (is_exp[1]) 
                        w = ppp1(generator);
                    else if (is_range[1])
                        w = p1(generator);
                    else   
                        w = dist[1][pp1(generator)]; 
                }
                cout << w << endl;
            }
        }
    }
    return 0;
}