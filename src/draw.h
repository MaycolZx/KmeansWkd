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
  float colorPoint[3] = {255, 0, 0};
};
vector<pointS> myVectorPoints;
vector<vector<pointS>> datosCentrosG;

void init() {
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glColor3f(1.0, 0.0, 0.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

void drawPoinsF() {
  glLineWidth(2.0f);
  for (int i = 0; i < myVectorPoints.size(); i++) {
    glBegin(GL_POINTS);
    glColor3f(myVectorPoints[i].colorPoint[0], myVectorPoints[i].colorPoint[1],
              myVectorPoints[i].colorPoint[2]);
    glVertex2f(myVectorPoints[i].x / 500 - 0.5,
               myVectorPoints[i].y / 500 - 0.25);
    glEnd();
  }
  for (int i = 0; i < datosCentrosG.size(); i++) {
    for (int j = 0; j < datosCentrosG[i].size(); j++) {
      glBegin(GL_POLYGON);
      glColor3f(255, 0, 0);
      pointS centroD = datosCentrosG[i][j];
      float vNormX = (centroD.x / 500) - 0.75;
      float vNormY = (centroD.y / 500) - 0.5;
      float rectSize = 0.005;
      glVertex2f(vNormX - rectSize, vNormY - rectSize);
      glVertex2f(vNormX - rectSize, vNormY + rectSize);
      glVertex2f(vNormX + rectSize, vNormY + rectSize);
      glVertex2f(vNormX + rectSize, vNormY - rectSize);
      glEnd();
    }
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

void timer(int) {
  glutPostRedisplay();         // Fuerza la actualización de la ventana
  glutTimerFunc(16, timer, 0); // Llama a timer cada 16 ms (~60 FPS)
}

void DrawDS(int argc, char **argv) {
  if (myVectorPoints.empty()) {
    cout << "no se cargaron los datos correctamente" << endl;
    return;
  }
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(500, 500);
  glutCreateWindow("Kmens-viClusters");
  init();
  glutDisplayFunc(display);
  glutTimerFunc(0, timer, 0);
  glutMainLoop();
}
