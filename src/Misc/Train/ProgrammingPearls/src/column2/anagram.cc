#include <iostream> // NOLINT
using std::cout;
using std::endl;
using std::cin;
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <map>
using std::multimap;
#include <algorithm>
using std::sort;
#include <utility>
using std::pair;

struct classcomp {
  bool operator() (const string &lhs, const string &rhs) const {
    if (lhs.compare(rhs) < 0) {
      return true;
    } else {
      return false;
    }
  }
};

bool stringcomp(char a, char b) {
  return a < b;
}

void signWord(multimap<string, string, classcomp> *words_map,
              const string &word) {
  string sign = word;
  sort(sign.begin(), sign.end(), stringcomp);
  words_map->insert(pair<string, string>(sign, word));
}

void squash(multimap<string, string, classcomp> *words_map,
            vector<vector<string> > *anagram_words) {
  string old_sig;
  old_sig = words_map->begin()->first;
  vector<string> anagram_vector;
  for (multimap<string, string, classcomp>::iterator it = words_map->begin();
       it != words_map->end(); ++it) {
    if ((*it).first == old_sig) {
      anagram_vector.push_back((*it).second);
    } else {
      anagram_words->push_back(anagram_vector);
      old_sig = (*it).first;
      anagram_vector.clear();
      anagram_vector.push_back(old_sig);
    }
  }
}

int main(int argc, char *argv[]) {
  string word;
  multimap<string, string, classcomp> *words_map = new
      multimap<string, string, classcomp>();
  while (cin >> word) {
    signWord(words_map, word);
  }
  vector<vector<string> > *anagram_words = new vector<vector<string> >();
  squash(words_map, anagram_words);

  for (vector<vector<string> >::iterator it = anagram_words->begin();
       it != anagram_words->end(); ++it) {
    for (vector<string>::iterator it_inter = it->begin();
        it_inter != it->end(); ++it_inter) {
      cout << *it_inter << " ";
    }
    cout << endl;
  }

  return 0;
}
