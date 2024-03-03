#include<windows.h>
#include <GL/glut.h>
#include <math.h>
#include<stdio.h>


#define PI 3.1416


///Global Variable
float boundary = 100; /// Scene boundary
float border = 80;   /// Game boundary

///Agent1 Parameters(green)
float RAgent = 6.0;
float CAgentX = -60.0, CAgentY = 0.0;
float agentSpeed = 5;
bool isAgentDestroyed = false;

///Agent2 Parameters(blue)
float RAgent1 = 6.0;
float CAgentX1 = 60.0, CAgentY1 = 0.0;
bool isAgentDestroyed1 = false;
float agentSpeed1 = 5;

///Enemy1 Parameters
float REnemy = 4.0;
float CEnemyX = 0.0, CEnemyY = border;
int state = 1;
float enemySpeed = 0.05;

///Enemy2 parameters
float REnemy1 = 4.0;
float CEnemyX1 = border, CEnemyY1 = -border;
int position = 1;
float enemySpeed1 = 0.05;


float score=0.0;
int x=1;

void circle(float radius_x, float radius_y)
{
	int i=0;
	float angle = 0.0;

	glBegin(GL_POLYGON);

		for(i = 0; i < 100; i++)
		{
			angle = 2 * PI * i / 100;
			glVertex2f (cos(angle) * radius_x, sin(angle) * radius_y);
			//glVertex2f (cos(angle) * radius_x+5, sin(angle) * radius_y);
		}

	glEnd();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0,1.0,1.0);
    glBegin(GL_LINE_STRIP);
        glVertex2f(-border, border);
        glVertex2f(border, border);
        glVertex2f(border, -border);
        glVertex2f(-border, -border);
        glVertex2f(-border, border);
    glEnd();

	if(!isAgentDestroyed)
    {
        glPushMatrix();             //Green Circle
        glTranslatef(CAgentX, CAgentY,0);
        glColor3f(0,1,0);
        circle(RAgent,RAgent);
        glPopMatrix();
    }

    if(!isAgentDestroyed1)
    {
        glPushMatrix();             //blue Circle
        glTranslatef(CAgentX1, CAgentY1,0);
        glColor3f(0.2,0.6,1);
        circle(RAgent1,RAgent1);
        glPopMatrix();
    }

    glPushMatrix();             //Red circle enemy1 (Static)
	glTranslatef(CEnemyX, CEnemyY,0);
    glColor3f(1.0, 0.0, 0.0);
	circle(REnemy,REnemy);
	glPopMatrix();

	glPushMatrix();             //Red circle enemy2 (Static)
	glTranslatef(CEnemyX1, CEnemyY1,0);
    glColor3f(1.0, 0.0, 0.0);
	circle(REnemy1,REnemy1);
	glPopMatrix();

	glFlush();
}


void animate()
{

   if(isAgentDestroyed && isAgentDestroyed1){

     if (x==1){
     x=2;
     printf("Your Score is: ");
     printf("%.0f",score);
     }
   }

   else {
      score= score+0.005;

   }


    ///Enemy1 Movement
    if(state == 1)
    {
        CEnemyX -= enemySpeed;
        CEnemyY -= enemySpeed;

 /// CEnemyX value is 0 and CEnemyY is border=80 and will continue up to X<-80 and Y<0, when both condition fulfilled then state=2

        if(CEnemyX<-border && CEnemyY<0)
        {
            state = 2;
        }
    }
    else if(state == 2)
    {
        CEnemyX += enemySpeed;
        CEnemyY = 0;

 /// CEnemyX value is -80 and continue until x>80, when condition fulfilled then state=3

        if(CEnemyX>border )
        {
            state = 3;
        }
    }
    else if(state == 3)
    {
        CEnemyX -= enemySpeed;
        CEnemyY -= enemySpeed;

 /// CEnemyX value is 80 and CEnemyY is 0 and will continue up to X<0 and Y<-80, when both condition fulfilled then state=4

        if(CEnemyX<0 && CEnemyY<-border) {
            state = 4;
        }
    }
    else if(state == 4){
        CEnemyX = 0;
        CEnemyY += enemySpeed;

 /// CEnemyY value is -80 and will continue up to border=80, when greater than border=80 then state=1

        if( CEnemyY>border)
        {
            state = 1;
        }
    }

 /// Enemy2 Movement

    if (position==1){
        CEnemyX1 -= enemySpeed1;
        CEnemyY1 += enemySpeed1;

 /// CEnemyX1=80 and CEnemyY1=-80 will continue up to x<-80 and y>80, when both conditions become true then position=2

      if(CEnemyX1<-border && CEnemyY1>border)
        {
            position = 2;
        }

    }


     else if(position == 2)
    {
        CEnemyX1 += enemySpeed1;
        CEnemyX1 += enemySpeed1;
        CEnemyY1 -= enemySpeed1;

 /// CEnemyX1=-80 and CEnemyY1=80 and continue until x>80 and y<0, when condition fulfilled then position=3

        if(CEnemyX1>border && CEnemyY1<0)
        {
            position = 3;
        }
    }

    else if (position==3){
        CEnemyX1 -= enemySpeed1;
        CEnemyY1 += enemySpeed1;


 /// CEnemyX1=80 and CEnemyY1=0 and continue until x<0 and y>80, when condition fulfilled then position=4

        if(CEnemyX1<0 && CEnemyY1>border)
        {
            position = 4;
        }

    }

     else if (position==4){
        CEnemyX1 += enemySpeed1;
        CEnemyY1 -= enemySpeed1;
        CEnemyY1 -= enemySpeed1;


 /// CEnemyX1=0 and CEnemyY1=80 and continue until x>80 and y<-80, when condition fulfilled then position=3

        if(CEnemyX1>border && CEnemyY1<-border)
        {
            position = 1;
        }

    }

    ///Attack Agent1 by Enemy1 and Enemy2 Logic
    float distance = sqrt((CAgentX-CEnemyX)*(CAgentX-CEnemyX) + (CAgentY-CEnemyY)*(CAgentY-CEnemyY));
    float distance1 = sqrt((CAgentX-CEnemyX1)*(CAgentX-CEnemyX1) + (CAgentY-CEnemyY1)*(CAgentY-CEnemyY1));
    if(distance <= RAgent+REnemy || distance1 <= RAgent+REnemy1)
    {
        isAgentDestroyed = true;
    }

    ///Attack Agent2 by Enemy1 and Enemy2 Logic
    float distance2 = sqrt((CAgentX1-CEnemyX)*(CAgentX1-CEnemyX) + (CAgentY1-CEnemyY)*(CAgentY1-CEnemyY));
    float distance3 = sqrt((CAgentX1-CEnemyX1)*(CAgentX1-CEnemyX1) + (CAgentY1-CEnemyY1)*(CAgentY1-CEnemyY1));
    if(distance2 <= RAgent1+REnemy || distance3 <= RAgent1+REnemy1)
    {
        isAgentDestroyed1 = true;
    }


    glutPostRedisplay();
}



void init(void)
{
	glClearColor (0.0, 0.0, 0.0, 0.0);
	glOrtho(-boundary, boundary, -boundary, boundary, -boundary, boundary);
}


void spe_key(int key, int x, int y)
{

	switch (key) {

		case GLUT_KEY_LEFT:
                CAgentX -= agentSpeed;

                if(CAgentX<0 && -CAgentX>border-RAgent)
                {
                    isAgentDestroyed = true;
                }
				glutPostRedisplay();
				break;


		case GLUT_KEY_RIGHT:
                CAgentX += agentSpeed;

                if(CAgentX>0 && CAgentX>border-RAgent)
                {
                    isAgentDestroyed = true;
                }
				glutPostRedisplay();
				break;

        case GLUT_KEY_DOWN:
                CAgentY -= agentSpeed;
                if(CAgentY<0 && -CAgentY>border - RAgent)
                {
                    isAgentDestroyed = true;
                }
				glutPostRedisplay();
				break;

		case GLUT_KEY_UP:
                CAgentY += agentSpeed;
                if(CAgentY>0 && CAgentY>border-RAgent)
                {
                    isAgentDestroyed = true;
                }
				glutPostRedisplay();
				break;
	  default:
			break;
	}
}

/*void spe_key1(int key, int x, int y)
{

	switch (key) {

		case GLUT_KEY_F2:
                CAgentX1 -= agentSpeed1;

                if(CAgentX1<0 && -CAgentX1>border-RAgent1)
                {
                    isAgentDestroyed = true;
                }
				glutPostRedisplay();
				break;


		case GLUT_KEY_F3:
                CAgentX1 += agentSpeed1;

                if(CAgentX1>0 && CAgentX1>border-RAgent1)
                {
                    isAgentDestroyed1 = true;
                }
				glutPostRedisplay();
				break;

        case GLUT_KEY_F4:
                CAgentY1 -= agentSpeed1;
                if(CAgentY1<0 && -CAgentY1>border - RAgent1)
                {
                    isAgentDestroyed1= true;
                }
				glutPostRedisplay();
				break;

		case GLUT_KEY_F5:
                CAgentY1 += agentSpeed1;
                if(CAgentY1>0 && CAgentY1>border-RAgent1)
                {
                    isAgentDestroyed1 = true;
                }
				glutPostRedisplay();
				break;
	  default:
			break;
	}
}

*/

void keyboard_action(unsigned char key, int x, int y)
{

		if(key == 'l'){

                CAgentX1 -= agentSpeed1;

                if(CAgentX1<0 && -CAgentX1>border-RAgent1)
                {
                    isAgentDestroyed1 = true;
                }
				glutPostRedisplay();

		   }

	  else if(key== 'r'){
                CAgentX1 += agentSpeed1;

                if(CAgentX1>0 && CAgentX1>border-RAgent1)
                {
                    isAgentDestroyed1 = true;
                }
				glutPostRedisplay();

		    }

        else if(key== 'd'){
                CAgentY1 -= agentSpeed1;
                if(CAgentY1<0 && -CAgentY1>border - RAgent1)
                {
                    isAgentDestroyed1 = true;
                }
				glutPostRedisplay();

            }

		 else if(key == 'u'){
                CAgentY1 += agentSpeed1;
                if(CAgentY1>0 && CAgentY1>border-RAgent1)
                {
                    isAgentDestroyed1 = true;
                }
				glutPostRedisplay();

		 }


}

/*void mouse_action(int button,int state,int x, int y)
{
    if(button == GLUT_LEFT_BUTTON)
    {
        glutPostRedisplay();
    }
    else if(button == GLUT_RIGHT_BUTTON)
    {
        glutPostRedisplay();
    }
    else if(button == GLUT_MIDDLE_BUTTON)
    {
        glutPostRedisplay();
    }
} */


int main()
{
	glutInitWindowSize (800, 800);
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("2D Game");
	init();
	glutDisplayFunc(display);
	glutIdleFunc(animate);

	glutSpecialFunc(spe_key);
	//glutSpecialFunc(spe_key1);
    glutKeyboardFunc(keyboard_action);
	//glutMouseFunc(mouse_action);
	glutMainLoop();
	return 0;
}
