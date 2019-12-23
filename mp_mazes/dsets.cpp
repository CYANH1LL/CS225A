/* Your code here! */
#include "dsets.h"

using namespace std;

void  DisjointSets::addelements(int num) {
    for (int i = 0; i < num; i++) {
      elements.push_back(-1);
    }
}

int DisjointSets::findWithoutCompressed(int elem) {
  if (elements[elem] < 0) {
    return elem;
  } else {
    return findWithoutCompressed(elements[elem]);
  }
}

int  DisjointSets::find(int elem) {
    if (elements[elem] < 0) {
      return elem;
    } else {
      int root = find(elements[elem]);
      elements[elem] = root;
      return root;
    }
}

void  DisjointSets::setunion(int a, int b) {
    int rootA = findWithoutCompressed(a);
    int rootB = findWithoutCompressed(b);

    int newSize = elements[rootA] + elements[rootB];

    if (elements[rootA] <= elements[rootB]) {
      elements[rootB] = rootA;
      elements[rootA] = newSize;
    } else {
      elements[rootA] = rootB;
      elements[rootB] = newSize;
    }
}

int  DisjointSets::size(int elem) {
  elem = findWithoutCompressed(elem);
  return elements[elem] * -1;
}
