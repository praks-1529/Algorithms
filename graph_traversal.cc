
#define MXN 100000
bool visit[MXN];

void 
bfs(vector< set<int> > &vec, int N, vector< list<int> > &con) {
  memset(visit, 0, MXN*sizeof(bool));
  for(int i=0; i<N; i++) {
    if(!visit[i]) {
      set<int> st;
      queue<int> bfs;
      bfs.push(i);
      while(!bfs.empty()) {
        int k = bfs.front();
        bfs.pop();
        visit[k] = true;
        st.insert(k);
        list<int> &lst = con[k];
        list<int>::iterator it;
        FORSTL(it, lst) {
          if(!visit[*it]) {
            bfs.push(*it);
          }
        }
      }
#if DEBUG
      set<int>::iterator it;
      FORSTL(it, st) {
        cout << *it << " ";
      }
      cout << endl;
#endif
      vec.pb(st);
    }
  }
}

void 
dfs(vector< set<int> > &vec, int N, vector< list<int> > &con) {
  memset(visit, 0, MXN*sizeof(bool));
  for(int i=0; i<N; i++) {
    if(!visit[i]) {
      set<int> st;
      stack<int> dfs;
      dfs.push(i);
      while(!dfs.empty()) {
        int k = dfs.top();
        bfs.pop();
        visit[k] = true;
        st.insert(k);
        list<int> &lst = con[k];
        list<int>::iterator it;
        FORSTL(it, lst) {
          if(!visit[*it]) {
            dfs.push(*it);
          }
        }
      }
#if DEBUG
      set<int>::iterator it;
      FORSTL(it, st) {
        cout << *it << " ";
      }
      cout << endl;
#endif
      vec.pb(st);
    }
  }
}
