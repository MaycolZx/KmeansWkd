#include "draw.h"
#include <cmath>
#include <iostream>
#include <stack>
using namespace std;

struct nodeBin {
  nodeBin *nodos[2];
  nodeBin(int _n_Dim) {
    n_Dim = _n_Dim;
    nodos[0] = nodos[1] = nullptr;
  }
  int n_Dim = 0;
  float pos[2] = {};
  int indexCluster = 0;
};

class kd_tree {
public:
  void insertS(pointS pointV, int i_Cluster);
  nodeBin *findS_NN(pointS pointV);
  kd_tree(int _numForD) { numForD = _numForD; }

private:
  nodeBin *root = nullptr;
  int numForD = 0;
};

nodeBin *kd_tree::findS_NN(pointS pointV) {
  stack<nodeBin *> backSnode;
  stack<int> indexAcc;
  nodeBin *tmP = root;
  float pointNode[2] = {pointV.x, pointV.y};
  int indexLevel = 0;

  while (tmP) {
    backSnode.push(tmP);
    indexLevel = tmP->n_Dim;
    if (pointNode[indexLevel] < tmP->pos[indexLevel]) {
      tmP = tmP->nodos[0];
      indexAcc.push(0);
    } else {
      tmP = tmP->nodos[1];
      indexAcc.push(1);
    }
  }

  tmP = backSnode.top();
  backSnode.pop();
  float minDist2 =
      pow(pointV.x - tmP->pos[0], 2) + pow(pointV.y - tmP->pos[1], 2);
  nodeBin *nearestNode = tmP;

  while (!backSnode.empty()) {
    tmP = backSnode.top();
    backSnode.pop();
    float dist2 =
        pow(pointV.x - tmP->pos[0], 2) + pow(pointV.y - tmP->pos[1], 2);
    if (dist2 < minDist2) {
      minDist2 = dist2;
      nearestNode = tmP;
    }
    float distPerp = pow(pointNode[tmP->n_Dim] - tmP->pos[tmP->n_Dim], 2);
    if (distPerp < minDist2) {
      nodeBin *secOpt = tmP->nodos[1 - indexAcc.top()];
      indexAcc.pop();
      // Si el nodo alternativo es válido, revisa si es el más cercano
      if (secOpt) {
        float altDist2 = pow(pointV.x - secOpt->pos[0], 2) +
                         pow(pointV.y - secOpt->pos[1], 2);
        if (altDist2 < minDist2) {
          minDist2 = altDist2;
          nearestNode = secOpt;
        }
      }
    } else {
      indexAcc.pop();
    }
  }
  return nearestNode;
}

/////////////////////////////////////////////////
void kd_tree::insertS(pointS pointV, int i_Cluster) {
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
  newNode->indexCluster = i_Cluster;

  if (direction == 0) {
    pF->nodos[0] = newNode;
  } else {
    pF->nodos[1] = newNode;
  }
}
