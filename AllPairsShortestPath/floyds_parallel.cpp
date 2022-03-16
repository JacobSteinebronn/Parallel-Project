#include <bits/stdc++.h>
#include <thread>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

template<class T, class U> istream& operator>>(istream &is, pair<T, U>& p) { is >> p.first >> p.second; return is; }
template<class T> istream& operator>>(istream& is, vector<T>& vec) { for(auto &x : vec) cin >> x; return is; } 
template<class T, class U> ostream& operator<<(ostream &os, pair<T, U>& p) { os << "<" << p.first << "," << p.second << ">"; return os; }
template<class T> ostream& operator<<(ostream& os, vector<T>& vec) { os << "["; for(auto x : vec) os << x << " "; os << "]"; return os; }
ll oo = ll(1e15);

const int MAXN = 5000;
ll adj[MAXN][MAXN];

const int NUM_THREADS = 4;

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n, m, q; cin >> n >> m >> q;
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) adj[i][j] = oo;
    rep(i,0,n) adj[i][i] = 0;
    for(int i = 0; i < m; i++){
        int u, v; ll w; cin >> u >> v >> w; u--; v--;
        adj[u][v] = adj[v][u] = min(adj[u][v], w);
    }

    // APSP HERE
    
    auto threadEx = [&](int tnum, int k) -> void {
        rep(i, 0, n) {
            if(i % NUM_THREADS == tnum)
                rep(j, 0, n)
                    if(adj[i][k] + adj[k][j] < adj[i][j]) 
                        adj[i][j] = adj[i][k] + adj[k][j];
        }
    };

    rep(k, 0, n) {
        vector<thread*> threads;
        rep(i, 0, NUM_THREADS) threads.push_back(new thread(threadEx, i, k));
        for(auto cur : threads) cur->join();
    }
    // END APSP HERE

    for(int i = 0; i < q; i++){
        int u, v; cin >> u >> v;
        ll res = adj[u-1][v-1];
        if(res >= oo/3) res = -1;
        cout << res << "\n";
    }

    return 0;
}
