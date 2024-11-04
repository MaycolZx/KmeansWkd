#include "draw.h"
#include <iostream>
using namespace std;

// struct pointS {
//   float x, y;
//   pointS(float _x, float _y) {
//     x = _x;
//     y = _y;
//   }
//   // float colorPoint[3] = {};
//   float colorPoint[3] = {255, 0, 0};
// };

struct nodeBin {
  nodeBin *nodos[2];
  nodeBin(int _n_Dim) {
    n_Dim = _n_Dim;
    nodos[0] = nodos[1] = nullptr;
  }
  int n_Dim = 0;
  float pos[2] = {};
};

class kd_tree {
public:
  void insertS(pointS pointV);
  kd_tree(int _numForD) { numForD = _numForD; }

private:
  // void findS();
  nodeBin *root = nullptr;
  int numForD = 0;
};

void kd_tree::insertS(pointS pointV) {
  if (!root) {
    root = new nodeBin(0);
    root->pos[0] = pointV.x;
    root->pos[1] = pointV.y;
    return;
  }
  nodeBin *tmP = root;
  nodeBin *pF = nullptr;
  int direction = 0;
  float pointNode[2] = {pointV.x, pointV.y};
  int nvlI = tmP->n_Dim;

  while (tmP) {
    pF = tmP;
    if (pointNode[tmP->n_Dim] < tmP->pos[tmP->n_Dim]) {
      direction = 0;
      tmP = tmP->nodos[0];
    } else {
      direction = 1;
      tmP = tmP->nodos[1];
    }
    nvlI = (nvlI + 1) % numForD;
  }
  nodeBin *newNode = new nodeBin(nvlI);
  newNode->pos[0] = pointV.x;
  newNode->pos[1] = pointV.y;

  if (direction == 0) {
    pF->nodos[0] = newNode;
  } else {
    pF->nodos[1] = newNode;
  }
}
