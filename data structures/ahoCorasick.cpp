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

int main() {
  vector<string> pattern = {"his", "he", "she", "hers"};
  Aho automaton = Aho(pattern);
}
