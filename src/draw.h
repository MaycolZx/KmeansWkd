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
};

vector<pointS> datosP;

void init() {
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glColor3f(1.0, 0.0, 0.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

void drawMBRS() {
  glLineWidth(2.0f);
  for (int i = 0; i < datosP.size(); i++) {
    glBegin(GL_POINTS);
    glColor3f(0, 0, 0);
    glVertex2f(datosP[i].x / 500 - 0.5, datosP[i].y / 500);
    glEnd();
  }
  glBegin(GL_LINE_LOOP);
  glVertex2f(-0.5, -0.5); // inferior-izquierda
  glVertex2f(-0.5, 0.5);  // inferior-derecha
  glVertex2f(0.5, 0.5);   // superior-derecha
  glVertex2f(0.5, -0.5);  // superior-izquierda
  glEnd();
}

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  drawMBRS();
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
  glutCreateWindow("Kmens-viClusters");
  init();
  glutDisplayFunc(display);
  glutMainLoop();
}
