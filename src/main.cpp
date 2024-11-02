// #include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct pointS {
  float x, y;
  pointS(float _x, float _y) {
    x = _x;
    y = _y;
  }
};

vector<pointS> leerArchivo(string filename) {
  ifstream fileS(filename);
  if (!fileS.is_open()) {
    cout << "El archivo no se pudo abrir";
  }
  vector<pointS> datos;
  string valorStr;
  while (fileS >> valorStr) {
    size_t pos = valorStr.find(',');
    if (valorStr == "x,y")
      continue;
    string tmp = valorStr.substr(0, pos), tmp00 = valorStr.substr(pos + 1);
    pointS vPointmp(stof(tmp), stof(tmp00));
    datos.push_back(vPointmp);
  }
  fileS.close();
  return datos;
}

class kmeans {
public:
  int algo();
  void init() { cout << "Este es el init"; }
  bool insert(pointS *valueN) { return false; }
  void insertGroup(vector<pointS> &vectDpoints);

private:
};

void kmeans::insertGroup(vector<pointS> &vectDpoints) {
  vector<pointS> possCentro = {vectDpoints[0]};
  pointS *tmPos;
  float distMax = 0;
  while (true) {
    for (int i = 0; i < vectDpoints.size(); i++) {
      float vTcmp[possCentro.size()];
      for (int j = 0; j < possCentro.size(); j++) {
        float euclidiana = sqrt(pow(vectDpoints[i].y - possCentro[j].y, 2) +
                                pow(vectDpoints[i].x - possCentro[j].x, 2));
        vTcmp[j] = euclidiana;
      }
      for (int j = 0; j < possCentro.size(); j++) {
        if (vTcmp[j] >= distMax) {
          if (possCentro.size() > 1 && vTcmp[possCentro.size()] < vTcmp[j]) {
            tmPos = new pointS(vectDpoints[i].x, vectDpoints[i].y);
            continue;
          }
          distMax = vTcmp[j];
          tmPos = new pointS(vectDpoints[i].x, vectDpoints[i].y);
        }
      }
    }
    possCentro.push_back(*tmPos);
  }
}

int main() {
  kmeans myKmeans;
  vector<pointS> myVectorPoints = leerArchivo("../src/data2k.csv");
  int contador = 0;
  for (auto &x : myVectorPoints) {
    cout << contador << ": " << x.x << "#" << x.y << endl;
    contador++;
  }
  return 0;
}
