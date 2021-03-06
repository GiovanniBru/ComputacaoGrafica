#include <GL/glut.h>
#include <stdio.h>

int firstRun = 1;
int depthEnabled = 1;

void drawAxis(){
    glColor3f(1, 0, 0);
    glBegin(GL_LINES);
        glVertex3f(0, 0, 0);
        glVertex3f(100, 0, 0);
    glEnd();

    glColor3f(0, 1, 0);
    glBegin(GL_LINES);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 100, 0);
    glEnd();

    glColor3f(0, 0, 1);
    glBegin(GL_LINES);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 0, 100);
    glEnd();
}

void renderSomething(){
    glClearColor(0,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
//    glClearDepth(1.0f);

	if(depthEnabled)
		glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL); 

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

	glFrustum(-3, 3, -3, 3, 1, 50);

    glMatrixMode(GL_MODELVIEW);
    
	//right
	glViewport(0, 0, 500, 500); // drawing in perspective

    //drawAxis();

    if(firstRun){
        glRotated(90, 1, 0, 0);
		glTranslated(0, -12	, 0);
        firstRun = 0;
    }

    glPushMatrix();
    glTranslated(20, 0, 0);
    // PLOT EARTH
    glColor3d(0,1,1);
    glutSolidSphere(1, 10, 10);
    glTranslated(-20, 0, 0);
    glPopMatrix();
    
    // PLOT MARS   
    glPushMatrix();
    glTranslated(10, 0, 0);
    glColor3d(1,0,0);
    glutSolidSphere(1, 10, 10);
    glTranslated(-10, 0, 0);
    glPopMatrix();
    
    // PLOT SUN
    glColor3d(1,1,0);
    glutWireSphere(5, 10, 10);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // left VIEWPORT
    glViewport(500, 0, 500, 500);
    glOrtho(-100.0,100.0,-100.0,100.0, -100, 100);
    glMatrixMode(GL_MODELVIEW);

   // drawAxis();

    if(firstRun){
        glClearDepth(1.0f);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glRotated(90, 1, 0, 0);
    }

    glPushMatrix();
    glTranslated(80, 0, 0);
    glRotated(4, 0, 0, 1);
    // PLOT EARTH
    glColor3d(0,1,1);
    glutSolidSphere(5, 10, 10);
    //glColorMask(1,0,0,0);
    glTranslated(-80, 0, 0);
    glPopMatrix();
  

   // PLOT MARS    
    glPushMatrix();
    glTranslated(30, 0, 0);
    glColor3d(1,0,0);
    glutSolidSphere(5, 10, 10);
    glTranslated(-10, 0, 0);
    glPopMatrix();
    

    // PLOT SUN
    glColor3d(1,1,0);
    glutWireSphere(18, 10, 10);
    // glColorMask(0,0,1,0);


    glFlush();
}

void arrowsAction(int key, int x, int y){
    switch(key){
        case GLUT_KEY_RIGHT:
            glRotated(10, 0, 0, 1);
            glutPostRedisplay();
            break;
        case GLUT_KEY_LEFT:
            glRotated(-10, 0, 0, 1);
            glutPostRedisplay();
            break;
        case GLUT_KEY_UP:
            glRotated(10, 0, 1, 0);
            glutPostRedisplay();
            break;
        case GLUT_KEY_DOWN:
            glRotated(-10, 0, 1, 0);
            glutPostRedisplay();
            break;
    }
}

void keysAction(unsigned char key, int x, int y){
	switch(key){
		case 'd':
			if(depthEnabled){
				depthEnabled = 0;
				glutPostRedisplay();
			
			}
			else{
				depthEnabled = 1;
				glutPostRedisplay();
			}
				break;
            case 'q':
                exit(1);
                break;

	}
	
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_DEPTH);
    glutInitWindowSize(1500, 1500);
    glutCreateWindow("Giovanni");

    glutDisplayFunc(renderSomething);

    glutSpecialFunc(arrowsAction);
	glutKeyboardFunc(keysAction);

    glutMainLoop();
}
