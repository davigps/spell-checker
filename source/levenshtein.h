#include "spell_checker.h"

int subs[MAXSTRING][MAXSTRING];

int levenshtein(char a[], char b[]) {
  size_t lenA = strlen(a);
  size_t lenB = strlen(b);

  int vi[3] = {0, -1, -1};
  int vj[3] = {-1, -1, 0};

  for (int i = 0; i < lenA + 1; i++) {
    for (int j = 0; j < lenB + 1; j++) {
      if (i == 0) {
        subs[i][j] = j;
      } else {
        if (j == 0) subs[i][j] = i;
        else {
          int smallest = 1000;
          for (int z = 0; z < 3; z++) {
            int currentI = i + vi[z];
            int currentJ = j + vj[z];
            smallest = smallest < subs[currentI][currentJ] ? smallest : subs[currentI][currentJ];
          }
          if (a[i - 1] == b[j - 1]) subs[i][j] = subs[i - 1][j - 1];
          else subs[i][j] = smallest + 1;
        }
      }
    }
  }

  return subs[lenA][lenB];
}
