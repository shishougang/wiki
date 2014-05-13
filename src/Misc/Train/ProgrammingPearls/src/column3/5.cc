#include <iostream> // NOLINT
using std::cout;
using std::endl;
#include <vector>
using std::vector;
#include <string>
using std::string;
#include <cstring>
#include <algorithm>
using std::reverse;

const char *kHyphWords[] = {"et-ic", "al-is-tic", "s-tic", "p-tic", "-lyt-ic",
                      "ot-ic", "an-tic", "n-tic", "c-tic", "at-ic",
                      "h-nic", "n-ic", "m-ic", "l-lic", "b-lic",
                      "-clic", "l-ic", "h-ic", "f-ic", "d-ic",
                      "-bic", "a-ic", "-mac", "i-ac"};

static vector<string> *reverse_hyphs = NULL;

void ReverseHypenation(const char *word, char *reverse_word) {
  const char kHypen = '-';
  int len = strlen(word) - 1;
  int i, j;
  for (i = 0, j = 0; i <= len; ++i) {
    if (word[len - i] == kHypen)
      continue;
    reverse_word[j++] = word[len - i];
  }
  reverse_word[j] = '\0';
}

void RerverseWord(const string &word, string *reverse_word) {
  *reverse_word = word;
  reverse(reverse_word->begin(), reverse_word->end());
}

void PreProcessHyphenation() {
  if (reverse_hyphs != NULL) {
    return;
  } else {
    reverse_hyphs = new vector<string>();
    int n = sizeof(kHyphWords) / sizeof(kHyphWords[0]);
    for (int i = 0; i < n; ++i) {
      const int kMaxLen = 10;
      char reverse_word[kMaxLen];
      ReverseHypenation(kHyphWords[i], reverse_word);
      reverse_hyphs->push_back(string(reverse_word));
    }
  }
}

bool IsBeginWith(const string &word, const string &begin_letter) {
  if (word.size() < begin_letter.size()) {
    return false;
  }
  for (int i = 0; i < begin_letter.size(); ++i) {
    if (begin_letter[i] != word[i]) {
      return false;
    }
  }
  return true;
}

string FindHyphenation(const string &word) {
  PreProcessHyphenation();
  string reverse_word;
  RerverseWord(word, &reverse_word);
  for (int i = 0; i < reverse_hyphs->size(); ++i) {
    if (IsBeginWith(reverse_word, reverse_hyphs->at(i))) {
      return string(kHyphWords[i]);
    }
  }
  return "";
}

int main(int argc, char *argv[]) {
  string word = "ethnic";
  string hyph;
  hyph = FindHyphenation(word);
  if (hyph == "") {
    cout << "not find the hyphenation of " << word << endl;
  } else {
    cout << "find the hyphenation is: " << hyph << endl;
  }
  return 0;
}
