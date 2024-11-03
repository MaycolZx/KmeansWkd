#include "draw.h"
#include <chrono>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <thread>
#include <vector>
using namespace std;

void DBG_v() {
  // int contador = 0;
  // for (auto &x : myVectorPoints) {
  //   cout << contador << ": " << x.x << "#" << x.y << endl;
  //   contador++;
  // }
  //////////////////
  // int contador = 0;
  // for (auto &x : myVectorPoints) {
  //   cout << contador << ": " << x.x << ";" << x.y
  //        << " Color:" << x.colorPoint[0] << "," << x.colorPoint[1] << ","
  //        << x.colorPoint[2] << endl;
  //   contador++;
  // }
}

vector<vector<float>> colorSbl;
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
  void averagePoints(vector<vector<pointS>> &data_P, vector<pointS> &data_PCI);
};

void kmeans::averagePoints(vector<vector<pointS>> &data_P,
                           vector<pointS> &data_PCI) {
  for (int i = 0; i < data_P.size(); i++) {
    float xAvg = 0, yAvg = 0;
    for (int j = 0; j < data_P[i].size(); j++) {
      xAvg += data_P[i][j].x;
      yAvg += data_P[i][j].y;
    }
    xAvg /= data_P[i].size();
    yAvg /= data_P[i].size();
    pointS tmPoint(xAvg, yAvg);
    tmPoint.colorPoint[0] = data_P[i][0].colorPoint[0];
    tmPoint.colorPoint[1] = data_P[i][0].colorPoint[1];
    tmPoint.colorPoint[2] = data_P[i][0].colorPoint[2];
    data_PCI[i] = tmPoint;
  }
}

void kmeans::insertGroup(vector<pointS> &vectDpoints, int _k) {
  vector<pointS> pointC_index;
  std::srand(std::time(0));
  for (int i = 0; i < _k; i++) {
    int numRandom = std::rand() % vectDpoints.size() + 1;
    pointC_index.push_back(vectDpoints[numRandom]);
  }
  int contI = 0;
  while (contI < 100) {
    // for (int i = 0; i < pointC_index.size(); i++) {
    //   cout << contI << "-center point: " << pointC_index[i].x << ","
    //        << pointC_index[i].y << endl;
    //   cout << "Color: " << pointC_index[i].colorPoint[0] << ","
    //        << pointC_index[i].colorPoint[1] << ","
    //        << pointC_index[i].colorPoint[2] << endl;
    // }
    // cout << "======" << endl;
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
    }
    // updateCentro
    averagePoints(datosF_C, pointC_index);
    // std::this_thread::sleep_for(std::chrono::seconds(1));
    contI++;
    // break;
  }
}

int main(int argc, char *argv[]) {
  int k_P = 200;
  kmeans myKmeans;
  myVectorPoints = leerArchivo("../src/data2k.csv");
  generationColor(k_P);
  auto inicio = std::chrono::high_resolution_clock::now();
  // thread(&kmeans::insertGroup, std::ref(myKmeans), std::ref(myVectorPoints),
  // k_P)
  // .detach();
  myKmeans.insertGroup(myVectorPoints, k_P);
  // std::thread t(&kmeans::insertGroup, std::ref(myKmeans),
  // std::ref(myVectorPoints), k_P);
  // t.join();
  auto fin = std::chrono::high_resolution_clock::now();
  auto duracion =
      std::chrono::duration_cast<std::chrono::microseconds>(fin - inicio);
  std::cout << "Tiempo de ejecución: " << duracion.count() << " microsegundos"
            << std::endl;
  // thread(DrawDS, ref(argc), ref(argv)).detach();
  DrawDS(argc, argv);
  // t.join();
  return 0;
}
