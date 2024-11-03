#include "draw.h"
#include <chrono>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<vector<float>> colorSbl;
// float *colorSbl;
void generationColor(int _k) {
  // float *colorG_arr[3] = new float[_k][3];
  // vector<float[3]> colorG_arr;
  vector<vector<float>> colorG_arr;
  std::srand(std::time(0));
  for (int i = 0; i < _k; i++) {
    vector<float> tmpC;
    int numR = (std::rand() % 7) * 35;
    int numG = (std::rand() % 7) * 35;
    int numB = (std::rand() % 7) * 35;
    tmpC.push_back(numR);
    tmpC.push_back(numG);
    tmpC.push_back(numB);
    colorG_arr.push_back(tmpC);
  }
  colorSbl = colorG_arr;
}

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
  void insertGroup(vector<pointS> &vectDpoints, int _k);
  void insertG_C();

private:
};

void kmeans::insertGroup(vector<pointS> &vectDpoints, int _k) {
  vector<pointS> pointC_index;
  std::srand(std::time(0));
  for (int i = 0; i < _k; i++) {
    int numRandom = std::rand() % vectDpoints.size() + 1;
    pointC_index.push_back(vectDpoints[numRandom]);
    cout << i << "-center point: " << vectDpoints[numRandom].x << ","
         << vectDpoints[numRandom].y << endl;
  }
  // delete[] pointC_index;
  // vector<pointS> possCentro = {vectDpoints[0]};
  // pointS *tmPos;
  // float distMax = 0;
  // int contI = 0;
  while (true) {
    vector<vector<pointS>> datosF_C(_k);
    for (int i = 0; i < vectDpoints.size(); i++) {
      float min_V = 0;
      int indexC = 0;
      for (int j = 0; j < _k; j++) {
        float euclidiana = sqrt(pow(vectDpoints[i].y - pointC_index[j].y, 2) +
                                pow(vectDpoints[i].x - pointC_index[j].x, 2));
        if (j == 0) {
          min_V = euclidiana;
          continue;
        } else if (euclidiana < min_V) {
          min_V = euclidiana;
          indexC = j;
        }
      }
      datosF_C[indexC].push_back(vectDpoints[i]);
      if (colorSbl.empty())
        return;
      vectDpoints[i].colorPoint[0] = colorSbl[indexC][0];
      vectDpoints[i].colorPoint[1] = colorSbl[indexC][1];
      vectDpoints[i].colorPoint[2] = colorSbl[indexC][2];
      // for (int j = 0; j < possCentro.size(); j++) {
      //   if (vTcmp[j] >= distMax) {
      //     if (possCentro.size() > 1 && vTcmp[possCentro.size()] < vTcmp[j]) {
      //       tmPos = new pointS(vectDpoints[i].x, vectDpoints[i].y);
      //       continue;
      //     }
      //     distMax = vTcmp[j];
      //     tmPos = new pointS(vectDpoints[i].x, vectDpoints[i].y);
      //   }
      // }
    }
    // updateCentro

    // possCentro.push_back(*tmPos);
    // contI++;
    break;
  }
}

int main(int argc, char *argv[]) {
  int k_P = 2;
  kmeans myKmeans;
  vector<pointS> myVectorPoints = leerArchivo("../src/data2k.csv");
  generationColor(k_P);
  // int contador = 0;
  // for (auto &x : myVectorPoints) {
  //   cout << contador << ": " << x.x << "#" << x.y << endl;
  //   contador++;
  // }
  auto inicio = std::chrono::high_resolution_clock::now();
  myKmeans.insertGroup(myVectorPoints, k_P);
  auto fin = std::chrono::high_resolution_clock::now();
  auto duracion =
      std::chrono::duration_cast<std::chrono::microseconds>(fin - inicio);
  std::cout << "Tiempo de ejecución: " << duracion.count() << " microsegundos"
            << std::endl;
  // int contador = 0;
  // for (auto &x : myVectorPoints) {
  //   cout << contador << ": " << x.x << ";" << x.y
  //        << " Color:" << x.colorPoint[0] << "," << x.colorPoint[1] << ","
  //        << x.colorPoint[2] << endl;
  //   contador++;
  // }

  DrawDS(argc, argv, myVectorPoints);
  return 0;
}
