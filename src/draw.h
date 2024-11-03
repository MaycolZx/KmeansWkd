#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
using namespace std;
struct pointS {
  float x, y;
  pointS(float _x, float _y) {
    x = _x;
    y = _y;
  }
  // float colorPoint[3] = {};
  float colorPoint[3];
};

vector<pointS> datosP;

void init() {
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glColor3f(1.0, 0.0, 0.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

void drawPoinsF() {
  glLineWidth(2.0f);
  for (int i = 0; i < datosP.size(); i++) {
    glBegin(GL_POINTS);
    glColor3f(datosP[i].colorPoint[0], datosP[i].colorPoint[1],
              datosP[i].colorPoint[2]);
    glVertex2f(datosP[i].x / 500 - 0.5, datosP[i].y / 500 - 0.25);
    glEnd();
  }
  glBegin(GL_LINE_LOOP);
  glColor3f(255, 0, 255);
  glVertex2f(-0.6, -0.6); // inferior-izquierda
  glVertex2f(-0.6, 0.6);  // inferior-derecha
  glVertex2f(0.6, 0.6);   // superior-derecha
  glVertex2f(0.6, -0.6);  // superior-izquierda
  glEnd();
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  drawPoinsF();
  glFlush();
}

void DrawDS(int argc, char **argv, vector<pointS> &_datos) {
  datosP = _datos;
  if (datosP.empty()) {
    cout << "no se cargaron los datos correctamente" << endl;
    return;
  }
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(500, 500);
  // glClearColor(0.0, 255.0, 0.0, 1.0);
  glutCreateWindow("Kmens-viClusters");
  init();
  glutDisplayFunc(display);
  glutMainLoop();
}
