#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

#define PI 3.14159265

int angle = 10;
int rotation = 145;

/* Initializing the 2d space*/
void init3D(float r, float g, float b)
{
	glClearColor(r,g,b,0.0);
	glMatrixMode (GL_PROJECTION);
  	glLoadIdentity();
	glOrtho(-100.0,100.0,-100.0,100.0,0,200);
}

drawOrbit(int radius){
	glBegin(GL_LINE_STRIP);
	int i;
	for (i=0; i < 361; i++)
            {
                glVertex3f(radius* (float)sin(i * PI / 180),0 ,radius* (float)cos(i * PI / 180) );
            }
glEnd();

}

drawPlanet(float radius,int colorCount){
	switch(colorCount){

	case 0:
		glColor3f(1, 1, 0);
		break;
	case 1:
		glColor3f(0, 1, 0);
		break;
	case 2:
		glColor3f(0, 0, 1);
		break;
	case 3:
		glColor3f(0.5, 1, 0.5);
		break;
	case 4:
		glColor3f(0, 1, 1);
		break;
	case 5:
		glColor3f(1, 1, 0);
		break;
	case 6:
		glColor3f(1, 0, 1);
		break;
	case 7:
		glColor3f(1, 0, 0);
		break;
	case 8:
		glColor3f(1, 0.5, 0.5);
		break;
	case 9:
		glColor3f(0.5, 0.5, 0.5);
		break;

}


	glutSolidSphere(radius,50,50);

}

void ESPECIAL(int tecla,int xx , int yy){
	switch(tecla){
		case GLUT_KEY_LEFT: angle-=2;
				glutPostRedisplay();
				break;
		case GLUT_KEY_RIGHT: angle+=2;
				glutPostRedisplay();
				break;
		case GLUT_KEY_UP : rotation+=2;
				glutPostRedisplay();
				break;
		case GLUT_KEY_DOWN : rotation-=2;
				glutPostRedisplay();
				break;
	}
}



/*General begin to display function*/
void display(){
     //Clear information from last draw
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslated(0,0,-80);
    glRotated(rotation,1,0,0);
    glRotated(rotation,0,1,0);


int i;
int radius = 5;
for(i = 0;i<10;i++){
	drawOrbit(radius);



	radius +=10;

}
radius = 5;
int x = angle;
if(angle>360)
 angle = 0;
int increase = 15;
printf("angle : %d\n",angle);
for(i = 0; i<10; i++){
	drawPlanet(5,i);
	glPushMatrix();

	if(i!=0){
		glTranslated(-1 * increase,0,0);
		glRotated(-1*x,0,1,0);
		increase += 10;

		glTranslated(increase,0,0);
	}
	else{
		glTranslated(increase,0,0);
		glRotated(angle,0,1,0);
	}
	x +=30;
}



   // glutWireTeapot(10.0f);
    glFlush();

}



/* Creating a window, setting Name property and Algorithm that is
* goint to be used in glutDisplayFunc
*/
void createWindow(char *windowName)
{
  glutInitWindowPosition(300,100);
	glutInitWindowSize(800, 800);
	glutCreateWindow(windowName);
	init3D(1.0,1.0,1.0);
	glutDisplayFunc(display);
}



int main(int argc, char ** argv)
{

  glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	createWindow("Rotation Example");
	glutSpecialFunc(ESPECIAL);

	glutMainLoop(); //Start the main loop

	return 0;

}
