#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <math.h>
#include <vector>
#include <iostream>

GLfloat chair_width, chair_height, chair_length;
GLfloat leg_width, leg_height, leg_length;
GLfloat table_width, table_height, table_length;
GLfloat tleg_width, tleg_height, tleg_length;

GLfloat chairPosX, chairPosY, chairPosZ;
GLfloat tablePosX, tablePosY, tablePosZ;

void takeChairInput() {
    std::cout << "Enter chair width: ";
    std::cin >> chair_width;
    
    std::cout << "Enter chair height: ";
    std::cin >> chair_height;
    
    std::cout << "Enter chair length: ";
    std::cin >> chair_length;
    
    std::cout << "Enter leg width: ";
    std::cin >> leg_width;
    
    std::cout << "Enter leg height: ";
    std::cin >> leg_height;
    
    std::cout << "Enter leg length: ";
    std::cin >> leg_length;
    
    std::cout << "Enter chair coordinates (x, y, z): ";
    std::cin >> chairPosX >> chairPosY >> chairPosZ;
}

void takeTableInput() {
    std::cout << "Enter table width: ";
    std::cin >> table_width;
    
    std::cout << "Enter table height: ";
    std::cin >> table_height;
    
    std::cout << "Enter table length: ";
    std::cin >> table_length;
    
    std::cout << "Enter table leg width: ";
    std::cin >> tleg_width;
    
    std::cout << "Enter table leg height: ";
    std::cin >> tleg_height;
    
    std::cout << "Enter table leg length: ";
    std::cin >> tleg_length;
    
    std::cout << "Enter table coordinates (x, y, z): ";
    std::cin >> tablePosX >> tablePosY >> tablePosZ;
}


struct ChairPosition {
    GLfloat x, y, z;
};
std::vector<ChairPosition> chairList;
void addChair(GLfloat x, GLfloat y, GLfloat z) {
    ChairPosition newChair = {x, y, z};
    chairList.push_back(newChair);
}
void chair(); // Add this prototype

void displayChairs() {
    for (int i = 0; i < chairList.size(); i++) { // Use size() if chairList is a vector
        ChairPosition chairPos = chairList[i]; // Access each element by index
        glPushMatrix();
        glTranslatef(chairPos.x, chairPos.y, chairPos.z);
        chair(); // Call the chair function
        glPopMatrix();
    }
}

struct TablePosition {
    GLfloat x, y, z;
};
std::vector<TablePosition> tableList;

void addTable(GLfloat x, GLfloat y, GLfloat z) {
    TablePosition newTable = {x, y, z};
    tableList.push_back(newTable);
}
void table();
void displayTables() {
    for (int i = 0; i < tableList.size(); i++) {
        TablePosition tablePos = tableList[i];
        glPushMatrix();
        glTranslatef(tablePosX, tablePosY, tablePosZ);
        table(); // Call the table function
        glPopMatrix();
    }
}

GLfloat alpha = 0.0, theta = 0.0, axis_x=0.0, axis_y=0.0, Calpha= 360.0, C_hr_alpha=360.0;
GLboolean bRotate = false, fRotate= true, cRotate= true, xz_rotate=false,l_on=true;
const int width = 1000;
const int height = 1000;
GLboolean amb=true, spec=true, dif=true;


bool l_on1 = false;
bool l_on2 = false;
bool l_on3 = false;



double spt_cutoff=40;


GLfloat eyeX = 5;
GLfloat eyeY = 15;
GLfloat eyeZ = -30;

GLfloat lookX = 0;
GLfloat lookY = 0;
GLfloat lookZ = 0;

static GLfloat v_Cube[8][3] =
{
    {0.0, 0.0, 0.0},
    {2.0, 0.0, 0.0},
    {0.0, 2.0, 0.0},
    {0.0, 0.0, 2.0},
    {2.0, 2.0, 0.0},
    {0.0, 2.0, 2.0},
    {2.0, 0.0, 2.0},
    {2.0, 2.0, 2.0}
};


static GLubyte quadIndices[6][4] =
{
    {1, 4, 7, 6},
    {7, 4, 2, 5},
    {3, 5, 2, 0},
    {3, 6, 7, 5},
    {0, 2, 4, 1},
    {1, 6, 3, 0}
};



static void getNormal3p
(GLfloat x1, GLfloat y1,GLfloat z1, GLfloat x2, GLfloat y2,GLfloat z2, GLfloat x3, GLfloat y3,GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2-x1;
    Uy = y2-y1;
    Uz = z2-z1;

    Vx = x3-x1;
    Vy = y3-y1;
    Vz = z3-z1;

    Nx = Uy*Vz - Uz*Vy;
    Ny = Uz*Vx - Ux*Vz;
    Nz = Ux*Vy - Uy*Vx;

    glNormal3f(Nx,Ny,Nz);
}

void cube(GLfloat colr1, GLfloat colr2, GLfloat colr3)
{



    GLfloat cube_no[] = {0, 0, 0, 1.0};
    GLfloat cube_amb[] = {colr1*0.3,colr2*0.3,colr3*0.3,1};
    GLfloat cube_dif[] = {colr1,colr2,colr3,1};
    GLfloat cube_spec[] = {1,1,1,1};
    GLfloat cube_sh[] = {10};


    glMaterialfv(GL_FRONT, GL_AMBIENT, cube_amb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, cube_dif);
    glMaterialfv(GL_FRONT, GL_SPECULAR, cube_spec);
    glMaterialfv(GL_FRONT, GL_SHININESS, cube_sh);

    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        getNormal3p(v_Cube[quadIndices[i][0]][0], v_Cube[quadIndices[i][0]][1], v_Cube[quadIndices[i][0]][2],
                    v_Cube[quadIndices[i][1]][0], v_Cube[quadIndices[i][1]][1], v_Cube[quadIndices[i][1]][2],
                    v_Cube[quadIndices[i][2]][0], v_Cube[quadIndices[i][2]][1], v_Cube[quadIndices[i][2]][2]);
        for (GLint j=0; j<4; j++)
        {
            glVertex3fv(&v_Cube[quadIndices[i][j]][0]);
        }

    }
    glEnd();


}
static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, width / ar);

}

void flooor()
{

    glPushMatrix();

    glScalef(50,1,50);
    glTranslatef(-1,-1,-1);
    cube(0.663, 0.663, 0.663);
    glPopMatrix();


}

void wall(GLfloat col1,GLfloat col2,GLfloat col3)
{
    glPushMatrix();
    glScalef(50,1,50);
    glTranslatef(-1,-1,-1);
    cube(col1, col2, col3);
    glPopMatrix();


}





void fan_leg()
{
    glPushMatrix();
    glScalef(5,0.01113,2);
    glTranslatef(-1,-1,-1);
    cube(0.392, 0.584, 0.929);
    glPopMatrix();
}

void fan_face()
{
    glPushMatrix();
    glScalef(1.5,0.2,1.5);
    glTranslatef(-1,-1,-1);
    cube(1.000, 1.000, 1.000);
    glPopMatrix();


}

void fan_stand()
{
    glPushMatrix();
    glTranslatef(0,3.5,0);
    glScalef(0.3,6,0.3);
    glTranslatef(-1,-1,-1);
    cube(0.627, 0.322, 0.176);
    glPopMatrix();
}
void fan_set()
{
    glPushMatrix();
    glPushMatrix();
    fan_face();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-6,0,0); //leg1
    fan_leg();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(6,0,0); //leg2
    fan_leg();
    glPopMatrix();




    glPushMatrix();

    glRotatef(90,0,1,0);
    glTranslatef(6,0,0); //leg3
    fan_leg();
    glPopMatrix();


    glPushMatrix();

    glRotatef(90,0,1,0);
    glTranslatef(-6,0,0); //leg4
    fan_leg();
    glPopMatrix();
}

void fan()
{


    glPushMatrix();
    glRotatef(alpha,0,1,0);
    fan_set();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,2.5,0);
    fan_stand();
    glPopMatrix();

}

void clock()
{
    glPushMatrix();

    glPushMatrix(); //clk_leg1

    glScalef(1.5,1,1);
    glTranslatef(-.5,0.2,0);
    glScalef(0.8,0.01,0.1);
    glTranslatef(-1,-1,-1);
    cube(0,0,0);
    glPopMatrix();

    glPushMatrix(); //clk_leg2
    glRotatef( C_hr_alpha,0, 1, 0.0 );
    glScalef(1.5,1,1);
    glTranslatef(0.8,0.2,0);
    glScalef(0.8,0.01,0.1);
    glTranslatef(-1,-1,-1);
    cube(0,0,0);
    glPopMatrix();

    glPushMatrix(); //clk_leg3
    glRotatef( Calpha,0, 1, 0.0 );
    glRotatef(90,0,1,0);
    glScalef(1.5,1,1);
    glTranslatef(0.8,0.2,0);
    glScalef(0.8,0.01,0.1);
    glTranslatef(-1,-1,-1);
    cube(0,0,0);
    glPopMatrix();



    glScalef(4,0.2,3.5);
    glTranslatef(-1,-1,-1);
    cube(0.000, 0.000, 0.804);

    glPopMatrix();
}
void door()
{

    glPushMatrix(); // door_lock

    glTranslatef(44,2,13);
    glRotatef(90,0,1,0);
    glTranslatef(-0.6,5,4.5);
    glScalef(0.40,1.5, 0.5/5.5);
    glTranslatef(-1,-1,-1);
    cube(0,0,0);
    glPopMatrix();

    glPushMatrix();  //door
    glTranslatef(49,6,20);
    glRotatef(90,0,1,0);
    glScalef(8,15,.5);
    glTranslatef(-1,-1,-1);
    cube(0.647, 0.165, 0.165);
    glPopMatrix();

}
void room()
{
    glPushMatrix(); // Front wall
    glTranslatef(0, 0, 45);
    glRotatef(270, 1, 0, 0);

    // Light on front wall
    glPushMatrix(); 
    glTranslatef(3, 2, 36);
    glRotatef(90, 1, 0, 0);
    glScalef(12, 0.8, 0.8);
    glTranslatef(-1, -1, -1);
    cube(1.000, 0.843, 0.000); // Light
    glPopMatrix();

    // Blackboard
    glPushMatrix();  
    glTranslatef(0, 1, 18);
    glScalef(30, 0.5, 8);
    glTranslatef(-1, -1, -1);
    cube(0.000, 0.000, 0.000); // Blackboard
    glPopMatrix();

    // Clock
    glPushMatrix();
    glTranslatef(3, 1, 31);
    clock();
    glPopMatrix();

    wall(1.000, 1.000, 0.878); // Draw the front wall
    glPopMatrix();   // End of front wall

    // Top wall fan
    glPushMatrix();
    glScalef(0.8, 1, 1);
    glTranslatef(-5, 30, 0);
    fan(); // Ensure proper placement for the fan
    glPopMatrix();

    // Back wall
    glPushMatrix();
    glTranslatef(0.0, 0, -50);
    glRotatef(90, 1, 0, 0);
    wall(0.863, 0.863, 0.863); // Back wall
    glPopMatrix();

    // Left side wall start
    glPushMatrix();
    
    // Light on the left side
    glPushMatrix(); 
    glTranslatef(42, 30, -5);
    glRotatef(90, 0, 1, 0);
    glScalef(12, 1, 0.8);
    glTranslatef(-1, -1, -1);
    cube(1.000, 0.843, 0.000); // Light
    glPopMatrix();

    door(); // Assuming this is defined elsewhere
    glTranslatef(50.0, 0, -1);
    glRotatef(90, 0, 0, 1);
    wall(1.000, 0.894, 0.882); // Left side wall
    glPopMatrix(); // End of left side wall

    // Right side wall start
    glPushMatrix();
    
    // Light on the right side
    glPushMatrix(); 
    glTranslatef(-42, 30, -5);
    glRotatef(90, 0, 1, 0);
    glScalef(12, 1, 0.8);
    glTranslatef(-1, -1, -1);
    cube(1.000, 0.843, 0.000); // Light
    glPopMatrix();

    glTranslatef(-50.0, 0, -1);
    glRotatef(90, 0, 0, 1);
    wall(1.000, 0.894, 0.882); // Right side wall
    glPopMatrix(); // End of right side wall

    // Top wall
    glPushMatrix();
    glTranslatef(0, 40, -5);
    glRotatef(90, 0, 1, 0);
    wall(0.663, 0.663, 0.663); // Top wall
    glPopMatrix();

    // Floor
    glPushMatrix();
    glTranslatef(0, -10, 0);
    
    // Teacher's floor
    glPushMatrix();
    glTranslatef(-40, 2, 25);
    glScaled(40, 1, 10);
    cube(0.647, 0.165, 0.165); // Teacher's floor color
    glPopMatrix();

    flooor(); // Assuming this is defined elsewhere
    glPopMatrix(); // End of floor
}
 


void classRoom()
{
    glPushMatrix();
    room();
    glPopMatrix();

}

void light()
{

    //light

    GLfloat l_amb[] = {0.2, 0.2, 0.2, 1.0};
    GLfloat l_dif[] = {0.961, 0.871, 0.702};
    GLfloat l_spec[] = {0.2,0.2,0.2,1};
    GLfloat l_no[] = {0, 0, 0, 1.0};
    GLfloat l_pos1[] = {20,20,20,1.0}; //front side light
    GLfloat l_pos2[] = {44,30,-5,1.0}; //right side
    GLfloat l_pos3[] = {10,60,-30,1.0}; //left side



    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);

    if(l_on1)
    {
        if(amb==true)
        {
            glLightfv(GL_LIGHT0,GL_AMBIENT,l_amb);
        }
        else
        {
            glLightfv(GL_LIGHT0,GL_AMBIENT,l_no);
        }

        if(dif==true)
        {
            glLightfv(GL_LIGHT0,GL_DIFFUSE,l_dif);
        }
        else
        {
            glLightfv(GL_LIGHT0,GL_DIFFUSE,l_no);
        }
        if(spec==true)
        {
            glLightfv(GL_LIGHT0,GL_SPECULAR,l_spec);
        }
    }
    else
    {
        glLightfv(GL_LIGHT0,GL_AMBIENT,l_no);
        glLightfv(GL_LIGHT0,GL_DIFFUSE,l_no);

    }
    glLightfv(GL_LIGHT0,GL_POSITION,l_pos1);



    // glLightfv(GL_LIGHT0, GL_SPOT_CUTOFF, spt_cut);



    if(l_on2)
    {
        if(amb==true)
        {
            glLightfv(GL_LIGHT1,GL_AMBIENT,l_amb);
        }
        else
        {
            glLightfv(GL_LIGHT1,GL_AMBIENT,l_no);
        }

        if(dif==true)
        {
            glLightfv(GL_LIGHT1,GL_DIFFUSE,l_dif);
        }
        else
        {
            glLightfv(GL_LIGHT1,GL_DIFFUSE,l_no);
        }
    }
    else
    {
        glLightfv(GL_LIGHT1,GL_AMBIENT,l_no);
        glLightfv(GL_LIGHT1,GL_DIFFUSE,l_no);

    }
    glLightfv(GL_LIGHT1,GL_POSITION,l_pos2);



    if(l_on3)
    {
        if(amb==true)
        {
            glLightfv(GL_LIGHT2,GL_AMBIENT,l_amb);
        }
        else
        {
            glLightfv(GL_LIGHT2,GL_AMBIENT,l_no);
        }

        if(dif==true)
        {
            glLightfv(GL_LIGHT2,GL_DIFFUSE,l_dif);
        }
        else
        {
            glLightfv(GL_LIGHT2,GL_DIFFUSE,l_no);
        }
    }
    else
    {
        glLightfv(GL_LIGHT2,GL_AMBIENT,l_no);
        glLightfv(GL_LIGHT2,GL_DIFFUSE,l_no);
    }

    glLightfv(GL_LIGHT2,GL_POSITION,l_pos3);

    GLfloat spot_direction[] = { 0.0, -1.0, 0.0 };
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_direction);
    GLfloat spt_ct[] = {spt_cutoff};
    glLightfv(GL_LIGHT2, GL_SPOT_CUTOFF, spt_ct);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-3, 3, -3, 3, 2.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eyeX,eyeY,eyeZ, lookX,lookY,lookZ, 0,1,0); //eyeX,eyeY,eyeZ //5,10,-20

    glRotatef(theta, axis_x,axis_y,0);

    light();
    classRoom();
    glPushMatrix();
    glTranslatef(chairPosX, chairPosY, chairPosZ);
    chair();
    glTranslatef(tablePosX, tablePosY, tablePosZ);
    table();
    glPopMatrix();

    // Draw all additional chairs
    displayChairs();
    displayTables();

    
    glFlush();
    glutSwapBuffers();
}
// Chair definition (simple model using cubes)
void chair()
{

    glPushMatrix();



    glPushMatrix();  //upper_base

    glTranslatef((chair_width-leg_width)/2-1.1,(chair_length-leg_length)/2+7,(chair_height-leg_length)/2-2);
    glScalef(chair_width,chair_length*4.5, chair_height/6);
    glTranslatef(-1,-1,-1);
    cube(0.627, 0.322, 0.176);
    glPopMatrix();



    glPushMatrix();
    glScalef(chair_width,chair_length, chair_height); //base
    glTranslatef(-1,-1,-1);
    cube(0.722, 0.525, 0.043);
    glPopMatrix();


    glPushMatrix();
    glTranslatef((chair_width-leg_width)/2+1.125,(chair_length-leg_length)/2-3,(chair_height-leg_length)/2-1.6); //leg1
    glScalef(leg_width,leg_length, leg_height);
    glTranslatef(-1,-1,-1);
    cube(0.545, 0.271, 0.075);
    glPopMatrix();


    glPushMatrix();
    glTranslatef((chair_width-leg_width)/2-3.5,(chair_length-leg_length)/2-3,(chair_height-leg_length)/2+2.6); //leg2
    glScalef(leg_width,leg_length, leg_height);
    glTranslatef(-1,-1,-1);
    cube(0.545, 0.271, 0.075);
    glPopMatrix();



    glPushMatrix();
    glTranslatef((chair_width-leg_width)/2+1.1,(chair_length-leg_length)/2-3,(chair_height-leg_length)/2+2.5); //leg3
    glScalef(leg_width,leg_length, leg_height);
    glTranslatef(-1,-1,-1);
    cube(0.545, 0.271, 0.075);
    glPopMatrix();


    glPushMatrix();
    glTranslatef((chair_width-leg_width)/2-3.4,(chair_length-leg_length)/2-3,(chair_height-leg_length)/2-1.6); //leg4
    glScalef(leg_width,leg_length, leg_height);
    glTranslatef(-1,-1,-1);
    cube(0.545, 0.271, 0.075);
    glPopMatrix();

    glPopMatrix();



}

void table()
{


    glPushMatrix();
    glScalef(table_width,table_length, table_height); //base
    glTranslatef(-1,-1,-1);
    cube(0.53,0.39,0.28);
    glPopMatrix();


    glPushMatrix();
    glTranslatef((table_width-tleg_width)/2+2.2,(table_length-tleg_length)/2-5,(table_height-tleg_length)/2+0.5); //leg1
    glScalef(tleg_width,tleg_length, tleg_height);
    glTranslatef(-1,-1,-1);
    cube(0.53,0.39,0.28);
    glPopMatrix();


    glPushMatrix();
    glTranslatef((table_width-tleg_width)/2-6.5,(table_length-tleg_length)/2-5,(table_height-tleg_length)/2+0.5); //leg2
    glScalef(tleg_width,tleg_length, tleg_height);
    glTranslatef(-1,-1,-1);
    cube(0.53,0.39,0.28);
    glPopMatrix();


    glPushMatrix();
    glTranslatef((table_width-tleg_width)/2-6.5,(table_length-tleg_length)/2-5,(table_height-tleg_length)/2+4.5); //leg3
    glScalef(tleg_width,tleg_length, tleg_height);
    glTranslatef(-1,-1,-1);
    cube(0.53,0.39,0.28);
    glPopMatrix();


    glPushMatrix();
    glTranslatef((table_width-tleg_width)/2+2.1,(table_length-tleg_length)/2-5,(table_height-tleg_length)/2+4.5); //leg3
    glScalef(tleg_width,tleg_length, tleg_height);
    glTranslatef(-1,-1,-1);
    cube(0.53,0.39,0.28);
    glPopMatrix();




}
void myKeyboardFunc( unsigned char key, int x, int y )
{
    switch ( key )
    {
    case 'R':
    case 'r':
        bRotate = !bRotate;
        axis_x=0.0;
        axis_y=1.0;
        break;
    case '+': //zoom in
        eyeZ++;
        lookZ++;
        break;
    case '-': //zoom out
        eyeZ--;
        lookZ--;
        break;
    case '*': //zoom up
        eyeY++;
        lookY++;
        break;
    case '/': //zoom down
        eyeY--;
        lookY--;
        break;

    case 'x':
        eyeX++;
        lookX++;
        break;
    case 'z':
        eyeX--;
        lookX--;
        break;



    case '1': //light
        l_on1=!l_on1;
        break;
    case '2':
        l_on2=!l_on2;
        break;
    case '3':
        l_on3=!l_on3;
        break;

    case 'a':  //poperties of light
        amb= !amb;
        break;
    case 's':
        spec =!spec;
        break;
    case 'd':
        dif=!dif;
        break;
    case 'f':   //fan
    case 'F':
        fRotate = !fRotate;
        axis_x=0.0;
        axis_y=1.0;
        break;

case 'c':  // Add a new chair
        takeChairInput();
        addChair(chairPosX, chairPosY, chairPosZ);  // Add a chair with offset
        break;
case 'T':  // Add a table when 'T' is pressed
        case 't':
        	takeTableInput();
            addTable(tablePosX, tablePosY, tablePosZ); // Add table at the same position as chair
            break;
    case 27:	// Escape key
        exit(1);

    }
}


void animate()
{
    if (bRotate == true)
    {
        theta += 0.1;
        if(theta > 360.0)
            theta -= 360.0*floor(theta/360.0);
    }


    if (fRotate == true)
    {
        alpha += 0.8;
        if(alpha > 360.0)
            alpha -= 360.0*floor(alpha/360.0);
    }

    if (cRotate == true)  //for clock
    {
        Calpha -= 0.075;
        C_hr_alpha -=0.009;
        if(Calpha < 1.0)
            Calpha = 360.0;
        if(C_hr_alpha < 1.0)
            C_hr_alpha = 360.0;
    }

    glutPostRedisplay();

}



int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(0,0);
    glutInitWindowSize(height, width);
    glutCreateWindow("ClassRoom");

    glutReshapeFunc(resize);
    
    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );
    glEnable(GL_NORMALIZE);

    glEnable(GL_LIGHTING);

    glutKeyboardFunc(myKeyboardFunc);
    glutDisplayFunc(display);
    glutIdleFunc(animate);
    printf("CLASSROOM VISUALIZATION MENU\n\n");
    printf("Use '1' to on/off light  from the front side.\n");
    printf("Use '2' to on/off light  from the right side.\n");
    printf("Use '3' to on/off spot light from the left side.\n");
    
    printf("Use 'r' to rotate the scene. \n");

    printf("Use '+' to zoom in and '-' to zoom out.\n");
    printf("Use '*' to look up, '/' to look down, 'z' to look right, and 'x' to look left.\n");
    printf("Press 'c' to add a new chair.\n");
    printf("Press 't' to add a new table.\n");

    printf("Use 'f' to on/off the fan.\n");


    glutMainLoop();


    return 0;
}
