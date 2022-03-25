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

int num_threads = 12;

int main(int argc, char *argv[]){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    if(argc > 1) num_threads = stoi(argv[1]);

    int n; cin >> n;
    rep(i, 0, n) rep(j, 0, n) cin >> adj[i][j];

    // APSP HERE
    auto threadEx = [&](int tnum, int k) -> void {
        for(int i = tnum; i < n; i += num_threads) {
            rep(j, 0, n)
                if(adj[i][k] + adj[k][j] < adj[i][j]) 
                    adj[i][j] = adj[i][k] + adj[k][j];
        }
    };
    
    for(int k = 0; k < n; k++){
        vector<thread*> threads;
        rep(i, 0, num_threads) threads.push_back(new thread(threadEx, i, k));
        for(auto cur : threads) cur->join();
    }

    // END APSP HERE
    cout << n << endl;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++) cout << adj[i][j] << " ";
        cout << "\n";
    } 

    return 0;
}
