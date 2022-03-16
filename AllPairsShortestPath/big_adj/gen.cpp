#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

// template<class T, class U> istream& operator>>(istream &is, pair<T, U>& p) { is >> p.first >> p.second; return is; }
// template<class T> istream& operator>>(istream& is, vector<T>& vec) { for(auto &x : vec) cin >> x; return is; } 
// template<class T, class U> ostream& operator<<(ostream &os, pair<T, U>& p) { os << "<" << p.first << "," << p.second << ">"; return os; }
// template<class T> ostream& operator<<(ostream& os, vector<T>& vec) { os << "["; for(auto x : vec) os << x << " "; os << "]"; return os; }
int oo = -1^1<<31;

typedef vector<vector<int>> tcase;

vector<tcase> cases;

void genCase(int n, int maxedge){
    vector<vector<int>> res(n, vector<int>(n));
    for(int i = 0; i < n; i++){
        for(int j = i; j < n; j++){
            if(i == j) res[i][j] = 0;
            else res[j][i] = res[i][j] = rand()%maxedge;
        }
    }
    cases.push_back(res);
}

void printCase(tcase &tc){
    cout << tc.size() << "\n";
    for(auto &row : tc) {
        for(auto x : row) cout << x << " ";
        cout << "\n";
    }
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    genCase(3000, 1e9);

    for(auto &tc : cases) printCase(tc);

    return 0;
}
