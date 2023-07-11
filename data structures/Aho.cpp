#include <bits/stdc++.h>
using namespace std;

#define FOR(x,n) for(int x=0;x<n;x++)
using ll = long long;
using ii = pair<int,int>;

struct Aho {
  struct Vertex {
    vector<int> ch;
    int par, idx, dep, id = -1, suf_link = 0, out_link = 0;
    Vertex() : Vertex(-1, -1, 0) {}
    Vertex(int _par, int _idx, int _dep) : par(_par), idx(_idx), dep(_dep) {
      ch = vector<int>(26);
    }
  };
  vector<Vertex> t;
  Aho() : Aho(vector<string>()) {}
  Aho(const vector<string>& words) {
    t.push_back(Vertex());
    FOR(i,(int)words.size()) add(words[i], i);
    build();
  }
  bool add(const string& s, int id) {
    int cur = 0;
    FOR(i,(int)s.length()) {
      int idx = s[i] - 'a';
      if(!t[cur].ch[idx]) {
        t[cur].ch[idx] = (int)t.size();
        t.push_back(Vertex(cur, idx, i + 1));
      }
      cur = t[cur].ch[idx];
    }
    if(t[cur].id != -1) return false;
    t[cur].id = id;
    return true;
  }
  void build() {
    deque<int> q = {0};
    while(!q.empty()) {
      int cur = q.front();
      q.pop_front();
      if(cur) {
        if(t[cur].dep > 1)
          t[cur].suf_link = _transition(t[t[cur].par].suf_link, t[cur].idx);
        int suf = t[cur].suf_link;
        t[cur].out_link = (t[suf].id + 1) ? suf : t[suf].out_link;
      }
      for(int v : t[cur].ch)
        if(v) q.push_back(v);
    }
  }
  void match(const string& s, function<void(int, int)> f) {
    int cur = 0;
    FOR(i,(int)s.length()) {
      cur = _transition(cur, s[i] - 'a');
      for(int o = cur; o; o = t[o].out_link) 
        if(t[o].id != -1) f(i - t[o].dep + 1, t[o].id);
    }
  }
  int _transition(int j, int idx) {
    while(j && !t[j].ch[idx]) j = t[j].suf_link;
    return t[j].ch[idx];
  }
};

string text = "ahishersshesheshe";
vector<string> pattern = {"his", "he", "she", "hers"};

void f(int i, int j) {
  cout << pattern[j] << " found at position " << i << '\n';
}

int main() {
  Aho a = Aho(pattern);
  a.match(text, f);
}
