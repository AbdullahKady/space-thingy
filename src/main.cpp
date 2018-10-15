//	Includes
#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
//-----------------

//	Methods Signatures
void displayCallback(void);
void idleCallback(void);
//-----------------

//	Global Variables
double spaceshipX = 200, spaceshipY = 70;
double missileX = 0, missileY = -100; // To be invisible by default
double enemyX = 0, enemyY = 250, enemyHealth = 100, enemyWIDTH = 20, enemyHEIGHT = 20, enemySpeed = 1, enemySpeedCounter = 0;
bool enemyIsHit = false;
//----------------

void drawSpaceship()
{
  glPushMatrix();
  glPointSize(10.0);
  glLineWidth(8.0);

  // FIRE BARREL THINGY?
  glBegin(GL_LINES);
  glColor3f(1, 0, 1);
  glVertex2f(spaceshipX - 10, spaceshipY + 40);
  glVertex2f(spaceshipX + 10, spaceshipY + 40);
  glEnd();

  // BODY
  glBegin(GL_QUADS);
  glColor3f(0.14, 0.42, 0.55);
  glVertex2f(spaceshipX - 25, spaceshipY + 25);
  glVertex2f(spaceshipX - 25, spaceshipY - 25);
  glVertex2f(spaceshipX + 25, spaceshipY - 25);
  glVertex2f(spaceshipX + 25, spaceshipY + 25);
  glEnd();

  glBegin(GL_LINES);
  glColor3f(0, 0, 0);
  glVertex2f(spaceshipX - 15, spaceshipY - 5);
  glVertex2f(spaceshipX + 15, spaceshipY - 5);
  glEnd();

  // EXHAUST
  glBegin(GL_POINTS);
  glColor3f(1, 0, 0);
  glVertex2f(spaceshipX - 10, spaceshipY - 30);
  glVertex2f(spaceshipX + 10, spaceshipY - 30);
  glEnd();

  // WINGS
  glBegin(GL_TRIANGLES);
  glColor3f(0.2, 0.8, 0.2);
  glVertex2f(spaceshipX + 25, spaceshipY + 25);
  glVertex2f(spaceshipX + 25, spaceshipY - 25);
  glVertex2f(spaceshipX + 45, spaceshipY - 35);
  glEnd();

  glBegin(GL_TRIANGLES);
  glColor3f(0.2, 0.8, 0.2);
  glVertex2f(spaceshipX - 25, spaceshipY + 25);
  glVertex2f(spaceshipX - 25, spaceshipY - 25);
  glVertex2f(spaceshipX - 45, spaceshipY - 35);
  glEnd();

  // UPPER BODY
  glBegin(GL_QUADS);
  glColor3f(0.99, 0.84, 0);
  glVertex2f(spaceshipX - 25, spaceshipY + 25);
  glVertex2f(spaceshipX - 18, spaceshipY + 40);
  glVertex2f(spaceshipX + 18, spaceshipY + 40);
  glVertex2f(spaceshipX + 25, spaceshipY + 25);
  glEnd();
  glPopMatrix();
}

void drawEnemy()
{
  glPushMatrix();
  glBegin(GL_QUADS);
  glColor3f(1, 0, 0);
  glVertex2f(enemyX - enemyWIDTH / 2, enemyY - enemyHEIGHT / 2);
  glVertex2f(enemyX + enemyWIDTH / 2, enemyY - enemyHEIGHT / 2);
  glVertex2f(enemyX + enemyWIDTH / 2, enemyY + enemyHEIGHT / 2);
  glVertex2f(enemyX - enemyWIDTH / 2, enemyY + enemyHEIGHT / 2);
  glEnd();
  glPopMatrix();
}

void drawMissile()
{
  glPushMatrix();
  glPointSize(10.0);
  glBegin(GL_QUADS);
  glColor3f(0.8, 0.8, 0.8);
  glVertex2f(missileX - 3, missileY - 10);
  glVertex2f(missileX + 5, missileY - 10);
  glVertex2f(missileX + 5, missileY + 10);
  glVertex2f(missileX - 3, missileY + 10);
  glEnd();
  glBegin(GL_TRIANGLES);
  glColor3f(1, 0, 0);
  glVertex2f(missileX - 3, missileY + 10);
  glVertex2f(missileX + 5, missileY + 10);
  glVertex2f(missileX + 1, missileY + 18);
  glEnd();

  glBegin(GL_TRIANGLES);
  glColor3f(0, 0, 1);
  glVertex2f(missileX - 2, missileY - 8);
  glVertex2f(missileX - 2, missileY - 15);
  glVertex2f(missileX - 10, missileY - 20);
  glEnd();

  glBegin(GL_TRIANGLES);
  glColor3f(0, 0, 1);
  glVertex2f(missileX + 4, missileY - 8);
  glVertex2f(missileX + 4, missileY - 15);
  glVertex2f(missileX + 12, missileY - 20);
  glEnd();

  glPopMatrix();
  glutPostRedisplay();
}

void onKey(unsigned char key, int x, int y)
{
  switch (key)
  {
  case 'a':
    if (spaceshipX > 40)
      spaceshipX -= 4;
    break;
  case 'd':
    if (spaceshipX < 460)
      spaceshipX += 4;
    break;
  case 'q':
  case '\e':
    exit(0);
    break;
  default: // Any other button will fire a bullet.
    missileY = spaceshipY + 55;
    missileX = spaceshipX;
  }
  glutPostRedisplay();
}

int main(int argc, char **argr)
{
  srand(time(NULL));
  glutInit(&argc, argr);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(800, 500);
  glutCreateWindow("Space thingy!");
  glutDisplayFunc(displayCallback);
  glutKeyboardFunc(onKey);
  glutIdleFunc(idleCallback);
  glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
  gluOrtho2D(0.0, 500.0, 0.0, 500.0);
  glutMainLoop();
  return 0;
}

void displayCallback(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  drawSpaceship();
  drawMissile();
  drawEnemy();
  glFlush();
}

void idleCallback()
{
  if (enemyX > 460 || enemyX < 20)
    enemyX = 20;
  if (enemySpeedCounter > 100)
  {
    enemySpeedCounter = 0;
    enemySpeed = (rand() % 100) * 0.0001;
  }
  enemySpeedCounter++;
  enemyX += enemySpeed;
  if (missileY > 0 && missileY < 600)
  {
    if (abs(missileY - enemyY) < enemyHEIGHT && abs(missileX - enemyX) < enemyWIDTH)
    {
      if (!enemyIsHit)
      {
        missileY = -100;
        enemyIsHit = true;
        enemyHealth -= 10;
        std::cout << "ENEMY HIT!"
                  << "CURRENT HEALTH: " << enemyHealth << "\n";
        if (enemyHealth == 0)
        {
          exit(0);
        }
      }
    }
    else
    {
      enemyIsHit = false;
    }
    missileY += 0.05;
  }
  glutPostRedisplay();
}
