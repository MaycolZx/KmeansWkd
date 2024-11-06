#include "kdTree.h"
#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <thread>
#include <vector>
using namespace std;

#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

vector<vector<float>> colorSbl;

void generationColor(int _k) {
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
  vector<pointS> datos = {};
  ifstream fileS(filename);
  if (!fileS.is_open()) {
    cout << "El archivo no se pudo abrir";
    return datos;
  }
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

void generarArchivoCSV(string filename, int id,
                       vector<vector<float>> &dataVector) {
  ofstream archivo(filename);
  if (!archivo.is_open()) {
    std::cerr << "Error al abrir el archivo." << std::endl;
    return;
  }
  if (id == 1) {
    archivo << "num_points,kmeans_time,kdtree_time\n";
  } else {
    archivo << "num_k,kmeans_time,kdtree_time\n";
  }
  for (int i = 0; i < dataVector.size(); i++) {
    archivo << dataVector[i][0] << "," << dataVector[i][1] << "\n";
  }
  archivo.close();
  cout << "data save" << endl;
}

class kmeans {
public:
  bool insert(pointS *valueN) { return false; }
  void insertGroup(vector<pointS> &vectDG, int _k, int _n);
  void insertGroup_KDT(vector<pointS> &vectDG, int _k, int _n);
  vector<pointS> genRandomP_02(vector<pointS> &vectDpoints, int _k);

private:
  vector<pointS> genRandomP_01(vector<pointS> &vectDpoints, int _k);
  void averagePoints(vector<vector<pointS>> &data_P, vector<pointS> &data_PCI);
};

vector<pointS> kmeans::genRandomP_01(vector<pointS> &vectDpoints, int _k) {
  vector<pointS> pointC_index;
  vector<int> numerosRandom;
  std::srand(std::time(0));
  for (int i = 0; i < _k; i++) {
    int numRandom = std::rand() % vectDpoints.size() + 1;
    numerosRandom.push_back(numRandom);
    pointC_index.push_back(vectDpoints[numRandom]);
  }
  return pointC_index;
}
vector<pointS> kmeans::genRandomP_02(vector<pointS> &vectDpoints, int _k) {
  vector<pointS> pointC_index;
  std::vector<int> numeros;
  for (int i = 0; i < vectDpoints.size(); ++i) {
    numeros.push_back(i);
  }
  std::random_device rd;
  std::mt19937 gen(rd());
  std::shuffle(numeros.begin(), numeros.end(), gen);
  std::vector<int> numerosAleatoriosUnicos(numeros.begin(),
                                           numeros.begin() + _k);
  for (int i = 0; i < _k; i++) {
    pointC_index.push_back(vectDpoints[numeros[i]]);
  }
  return pointC_index;
}

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

void kmeans::insertGroup(vector<pointS> &vectDpoints, int _k, int _n) {
  // vector<pointS> vectDpoints = genRandomP_02(vectDG, _n);
  vector<pointS> pointC_index = genRandomP_02(vectDpoints, _k);
  vector<pointS> poinTmp = pointC_index;
  int contI = 0;
  while (true) {
    // datosCentrosG.push_back(pointC_index);
    // for (int i = 0; i < pointC_index.size(); i++) {
    //   cout << contI << "-center point: " << pointC_index[i].x << ","
    //        << pointC_index[i].y << endl;
    //   cout << pointC_index[i].colorPoint[0] << ","
    //        << pointC_index[i].colorPoint[1] << ","
    //        << pointC_index[i].colorPoint[2] << endl;
    // }
    vector<vector<pointS>> datosF_C(_k);
    for (int i = 0; i < _n; i++) {
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
      // if (colorSbl.empty())
      //   return;
      vectDpoints[i].colorPoint[0] = colorSbl[indexC][0];
      vectDpoints[i].colorPoint[1] = colorSbl[indexC][1];
      vectDpoints[i].colorPoint[2] = colorSbl[indexC][2];
    }
    // updateCentro
    averagePoints(datosF_C, pointC_index);
    int verif = 0;
    for (int i = 0; i < pointC_index.size(); i++) {
      if (pointC_index[i].x == poinTmp[i].x &&
          pointC_index[i].y == poinTmp[i].y)
        verif++;
    }
    if (verif == pointC_index.size())
      break;
    poinTmp = pointC_index;
    //  std::this_thread::sleep_for(std::chrono::seconds(1));
    contI++;
  }
}

void kmeans::insertGroup_KDT(vector<pointS> &vectDG, int _k, int _n) {
  vector<pointS> vectDpoints = genRandomP_02(vectDG, _n);
  vector<pointS> pointC_index = genRandomP_02(vectDpoints, _k);
  vector<pointS> poinTmp = pointC_index;
  kd_tree myKdTree(2);
  for (int i = 0; i < pointC_index.size(); i++) {
    myKdTree.insertS(pointC_index[i], i);
  }
  int contI = 0;
  while (true) {
    // datosCentrosG.push_back(pointC_index);
    // for (int i = 0; i < pointC_index.size(); i++) {
    //   cout << contI << "-center point: " << pointC_index[i].x << ","
    //        << pointC_index[i].y << endl;
    // }
    vector<vector<pointS>> datosF_C(_k);
    for (int i = 0; i < vectDpoints.size(); i++) {
      int indexC = 0;
      nodeBin *puntoC = myKdTree.findS_NN(vectDpoints[i]);
      datosF_C[puntoC->indexCluster].push_back(
          vectDpoints[puntoC->indexCluster]);
      if (colorSbl.empty()) {
        cout << "no hay colores para asignar" << endl;
        return;
      }
      vectDpoints[i].colorPoint[0] = colorSbl[puntoC->indexCluster][0];
      vectDpoints[i].colorPoint[1] = colorSbl[puntoC->indexCluster][1];
      vectDpoints[i].colorPoint[2] = colorSbl[puntoC->indexCluster][2];
    }
    // updateCentro
    averagePoints(datosF_C, pointC_index);
    int verif = 0;
    for (int i = 0; i < pointC_index.size(); i++) {
      if (pointC_index[i].x == poinTmp[i].x &&
          pointC_index[i].y == poinTmp[i].y)
        verif++;
    }
    if (verif == pointC_index.size())
      break;
    poinTmp = pointC_index;
    myKdTree.cleanKD();
    for (int i = 0; i < pointC_index.size(); i++) {
      myKdTree.insertS(pointC_index[i], i);
    }
    // std::this_thread::sleep_for(std::chrono::seconds(1));
    contI++;
  }
}

int main(int argc, char *argv[]) {
  int k_P = 18;
  kmeans myKmeans;
  myVectorPoints = leerArchivo("../src/data2k.csv");
  generationColor(k_P);
  vector<int> k_P01 = {5, 15, 25, 50, 75};
  vector<vector<float>> vData01 = {{1000}, {1150}, {1300}, {1450}, {1600},
                                   {1750}, {1900}, {2050}, {2200}, {2400}};
  auto inicio = std::chrono::high_resolution_clock::now();
  myKmeans.insertGroup(myVectorPoints, 200, 1000);
  auto fin = std::chrono::high_resolution_clock::now();
  auto duracion =
      std::chrono::duration_cast<std::chrono::microseconds>(fin - inicio);
  cout << "Time: mys` " << duracion.count() << endl;

  ////////////////////////////////////////////////////////
  // for (int i = 0; i < k_P01.size(); i++) {
  //   auto inicio = std::chrono::high_resolution_clock::now();
  //   myKmeans.insertGroup(myVectorPoints, 25, 1000);
  //   auto fin = std::chrono::high_resolution_clock::now();
  //   auto duracion =
  //       std::chrono::duration_cast<std::chrono::microseconds>(fin - inicio);
  //   cout << "Time: mys` " << duracion.count() << endl;
  // }
  // vector<vector<float>> vData02 = {{500}, {1000}, {2000}};
  // for (int j = 0; j < k_P01.size(); j++) {
  //   for (int i = 0; i < vData01.size(); i++) {
  //     auto inicio = std::chrono::high_resolution_clock::now();
  //     myKmeans.insertGroup(myVectorPoints, k_P01[j], vData01[i][0]);
  //     auto fin = std::chrono::high_resolution_clock::now();
  //     auto duracion =
  //         std::chrono::duration_cast<std::chrono::microseconds>(fin -
  //         inicio);
  //     vData01[i].push_back(duracion.count());
  //////////////////////////////////////////////////////////////
  // auto inicio01 = std::chrono::high_resolution_clock::now();
  // myKmeans.insertGroup_KDT(myVectorPoints, k_P01[j], vData01[i][0]);
  // auto fin01 = std::chrono::high_resolution_clock::now();
  // auto duracion01 =
  // std::chrono::duration_cast<std::chrono::microseconds>(
  //     fin01 - inicio01);
  // vData01[i].push_back(duracion01.count());
  // }
  // }
  // generarArchivoCSV("data01.csv", 1, vData01);
  // DrawDS(argc, argv);
  return 0;
}
