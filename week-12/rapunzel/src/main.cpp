#include <bits/stdc++.h>

using namespace std;

int n, m, k;
vector<vector<int>> children;
vector<int> brightness;
set<int> result;
vector<int> parent;

multiset<int> path_b;
deque<int> path;


void dfs(int curr) {
  path.push_back(curr);
  path_b.insert(brightness[curr]);
  
  
  if(path.size() > m) {
    int front = path.front();
    path.pop_front();
    path_b.erase(path_b.find(brightness[front]));
  }
  
  if(path.size() == m && (*path_b.rbegin()) - (*path_b.begin()) <= k) {
    result.insert(path.front());
  }
  
  for(const auto &child : children[curr]) {
    dfs(child);
  }
  
  path.pop_back();
  path_b.erase(path_b.find(brightness[curr]));
  
  if(path[0] != 0) {
    int p = parent[path.front()];
    path.push_front(p);
    path_b.insert(brightness[p]);
  }
}

void testcase() {
  cin >> n >> m >> k;
  
  brightness = vector<int>(n);
  for(int i = 0; i < n; i++) {
    cin >> brightness[i];
  }
  
  path_b = multiset<int>();
  children = vector<vector<int>>(n);
  parent = vector<int>(n);
  for(int i = 0; i < n-1; i++) {
    int u, v; cin >> u >> v;
    children[u].push_back(v);
    parent[v] = u;
  }
  
  result = set<int>();
  dfs(0);
  
  // sort(result.begin(), result.end());
  
  // int prev = -1;
  for(auto it = result.begin(); it != result.end(); it++) {
    
    cout << *it << " ";
  }
  
  if(result.empty()) cout << "Abort mission";
  cout << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  int t; cin >> t;
  while(t--) testcase();
}