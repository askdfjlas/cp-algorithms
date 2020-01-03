#include <bits/stdc++.h>
using namespace std;

#define FOR(x,n) for(int x=0;x<n;x++)
#define mp make_pair
typedef long long ll;
typedef pair<int,int> iPair;

const int ALPHABETSIZE = 26;
const char ALPHABEGIN = 'a';

struct Vertex {
  int children[ALPHABETSIZE];
  int parentId = -1;
  char parentChar;
  int suffixLink;
  int outputLink;
  bool isWord = false;
  int wordId = -1;

  Vertex() {
    memset(children, -1, ALPHABETSIZE*sizeof(int));
  }
};

class Aho {
public:
  vector<string> words;
  vector<Vertex> trie;

  void buildTrie() {
    FOR(i,words.size()) {
      int curr = 0;
      for(auto c : words[i]) {
	Vertex& currVertex = trie[curr];
	int charIndex = c - ALPHABEGIN;
	  
	if(currVertex.children[charIndex] == -1) {
	  Vertex v = Vertex();
	  v.parentChar = c;
	  v.parentId = curr;
	  currVertex.children[charIndex] = trie.size();
	  trie.push_back(v);
	}

	curr = trie[curr].children[charIndex];
      }

      trie[curr].isWord = true;
      trie[curr].wordId = i;
    }
  }

  void buildLinks() {
    deque<int> queue;
    queue.push_back(0);

    while(!queue.empty()) {
      int curr = queue.front();
      Vertex& currVertex = trie[curr];
      queue.pop_front();

      if(curr == 0 || currVertex.parentId == 0) {
	currVertex.suffixLink = 0;
	currVertex.outputLink = 0;
      }
      else {
	char pch = currVertex.parentChar;
	int pCharIndex = pch - ALPHABEGIN;
	int next = trie[currVertex.parentId].suffixLink;
	
	while(true) {
	  Vertex& nextVertex = trie[next];
	  if(nextVertex.parentId == -1) {
	    if(nextVertex.children[pCharIndex] != -1)
	      currVertex.suffixLink = nextVertex.children[pCharIndex];
	    else
	      currVertex.suffixLink = 0;
	    break;
	  }
	  else if(nextVertex.children[pCharIndex] != -1) {
	    currVertex.suffixLink = nextVertex.children[pCharIndex];
	    break;
	  }

	  next = nextVertex.suffixLink;
	}
      }

      if(trie[currVertex.suffixLink].isWord)
	currVertex.outputLink = currVertex.suffixLink;
      else
	currVertex.outputLink = trie[currVertex.suffixLink].outputLink;

      FOR(i,ALPHABETSIZE) {
	if(currVertex.children[i] != -1)
	  queue.push_back(currVertex.children[i]);
      }
    }
  }

  Aho(vector<string> pat) {
    words = pat;
    trie.push_back(Vertex());  // root
    
    buildTrie();
    buildLinks();
  }
};

vector<iPair> aho_corasick(string& text, Aho& automaton) {
  vector<iPair> res;
  
  int curr = 0;
  FOR(i,text.length()) {
    char c = text[i];
    int charIndex = c - ALPHABEGIN;
    Vertex& currVertex = automaton.trie[curr];
    
    if(currVertex.children[charIndex] != -1) {
      curr = currVertex.children[charIndex];
    }
    else {
      do {
	curr = automaton.trie[curr].suffixLink;
	Vertex& v = automaton.trie[curr];
	if(v.children[charIndex] != -1) {
	  curr = v.children[charIndex];
	  break;
	}
      } while(curr != 0);
    }

    if(automaton.trie[curr].isWord)
      res.push_back(mp(i, automaton.trie[curr].wordId));
    
    int output = automaton.trie[curr].outputLink;
    while(output != 0) {
      res.push_back(mp(i, automaton.trie[output].wordId));
      output = automaton.trie[output].outputLink;
    }
  }

  return res;
}

int main() {
  string text = "ahishersshesheshe";
  vector<string> pattern = {"his", "he", "she", "hers"};
  Aho automaton = Aho(pattern);

  cout << automaton.trie[7].wordId << '\n';
  cout << automaton.trie[7].outputLink << '\n';
  cout << automaton.trie[6].suffixLink << '\n';

  vector<iPair> matches = aho_corasick(text, automaton);
  for(auto p : matches) {
    string& word = pattern[p.second];
    cout << word << " found at index " << p.first - word.length() + 1 << '\n';
  }
}
