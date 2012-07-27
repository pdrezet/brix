#include <iostream>
#include <stdlib.h>

#include <glew.h>
#include <glut.h>
#include "imageloader.h"
#include <vector>
using namespace std;

//Makes the image into a texture, and returns the id of the texture
GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
				 0,                            //0 for now
				 GL_RGB,                       //Format OpenGL uses for image
				 image->width, image->height,  //Width and height
				 0,                            //The border of the image
				 GL_RGB, //GL_RGB, because pixels are stored in RGB format
				 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
				                   //as unsigned numbers
				 image->pixels);               //The actual pixel data
	return textureId; //Returns the id of the texture
}

GLuint _textureId;
//draw function block
void drawFunctionBlock(float blockx, float blocky){

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId);
	//set filtering to decide how pixel colours are calculated
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	//draw function block and add texture
	glBegin(GL_QUADS);
	glColor3f(1.0,1.0,1.0);
	glTexCoord2f(0.0,1.0);
	glVertex2f(blockx, blocky);
	glTexCoord2f(1.0,1.0);
	glVertex2f(blockx + 75, + blocky);
	glTexCoord2f(1.0,0.0);
	glVertex2f(blockx + 75, blocky - 150);
	glTexCoord2f(0.0,0.0);
	glVertex2f(blockx, blocky - 150);
	glEnd();

	glDisable(GL_TEXTURE_2D);

}

//draw ports
void drawPort(float portx, float porty, int a){
	if (a == 1){
	glColor3f(1,0,0);
	glBegin(GL_TRIANGLES);
	glVertex2f(portx, porty + 8);
	glVertex2f(portx - 8, porty);
	glVertex2f(portx, porty - 8);
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	glColor3f(1,0,0);
	glVertex2f(portx, porty + 8);
	glColor3f(1,1,1);
	glVertex2f(portx, porty + 10);
	glColor3f(1,0,0);
	glVertex2f(portx - 8, porty);
	glColor3f(1,1,1);
	glVertex2f(portx - 10, porty);
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	glColor3f(1,0,0);
	glVertex2f(portx, porty - 8);
	glColor3f(1,1,1);
	glVertex2f(portx, porty - 10);
	glColor3f(1,0,0);
	glVertex2f(portx - 8, porty);
	glColor3f(1,1,1);
	glVertex2f(portx - 10, porty);
	glEnd();
	}

	else{
	glColor3f(1,0,0);
	glBegin(GL_TRIANGLES);
	glVertex2f(portx, porty + 8);
	glVertex2f(portx + 8, porty);
	glVertex2f(portx, porty - 8);
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	glColor3f(1,0,0);
	glVertex2f(portx, porty + 8);
	glColor3f(1,1,1);
	glVertex2f(portx, porty + 10);
	glColor3f(1,0,0);
	glVertex2f(portx + 8, porty);
	glColor3f(1,1,1);
	glVertex2f(portx + 10, porty);
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	glColor3f(1,0,0);
	glVertex2f(portx, porty - 8);
	glColor3f(1,1,1);
	glVertex2f(portx, porty - 10);
	glColor3f(1,0,0);
	glVertex2f(portx + 8, porty);
	glColor3f(1,1,1);
	glVertex2f(portx + 10, porty);
	glEnd();
	}


}

//array to store co-ordinates of a bend
float curveCoord[24] = {1.00,0.998,0.990,0.978,0.961,0.940,0.914,0.883,0.848,0.809,0.766,0.719,
						0.669,0.616,0.559,0.500,0.438,0.375,0.309,0.242,0.174,0.105,0.035,0.000};
						

//x,y co-ordinates need for 6 points to paint a line segment
float px1 = 0;
float py1 = 0;
float px2 = 0;
float py2 = 0;
float px3 = 0;
float py3 = 0;
float px4 = 0;
float py4 = 0;
float px5 = 0;
float py5 = 0;
float px6 = 0;
float py6 = 0;


//function to draw a line segment. takes in co-ordinates, stores them in a vertex array and draws a using triangle strips.
void drawLineSeg(float px1, float py1, float px2, float py2, float px3, float py3, float px4, float py4, float px5, float py5, float px6, float py6){

glEnableClientState(GL_VERTEX_ARRAY);
glEnableClientState(GL_COLOR_ARRAY);
//array for vertices
float para_vertex[]=

{ 
	px1,py1,
	px2,py2,
	px3,py3,
	px4,py4,
	px5,py5,
	px6,py6
};
//array for colours. Line blended from white to black and back to white to make line smooth.
float para_color[]=

{ 
	1,1,1,
	1,1,1,
	0,0,0,
	0,0,0,
	1,1,1,
	1,1,1
};

glVertexPointer(2, GL_FLOAT, 0, para_vertex);
glColorPointer(3, GL_FLOAT, 0, para_color);
glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);

glDisableClientState(GL_VERTEX_ARRAY);
glDisableClientState(GL_COLOR_ARRAY);

}


//function to draw a 90 degree bend using a series of line segments. Two paramaters change the position of the bend on the screen.
void drawBend(float x, float y, int a){

float st = 22;//outer radius
float sm = 20;//middle radius
float sb = 18;//inner radius


	int i;
	int j;
	int k = 1;//changes how many points we use to draw a bend


if (a == 1){
	//places the bend in the correct position
	x = x - sm;
	y = y - sm;

	i = 0;
	j = 24;

//++
//calculate the points to draw the first line segment.
 px1 = x + (curveCoord[i] * st);
 py1 = y + (curveCoord[j] * st);

 px2 = x + (curveCoord[i] * st);
 py2 = y + (curveCoord[j] * st);

 px3 = x + (curveCoord[i] * sm);
 py3 = y + (curveCoord[j] * sm);

 px4 = x + (curveCoord[i] * sm);
 py4 = y + (curveCoord[j] * sm);
 
 px5 = x + (curveCoord[i] * sb);
 py5 = y + (curveCoord[j] * sb);

 px6 = x + (curveCoord[i] * sb);
 py6 = y + (curveCoord[j] * sb);

 i =  i + k;//move to the next coordinate. dependant on k
 j = j - k;
 
//call the function to paint the first segment of the line.
 drawLineSeg(px1,py1,px2,py2,px3,py3,px4,py4,px5,py5,px6,py6);

//calculate the points of the next line segments and paint with the draw function.

 while (j >= 0){ 

px1 = px2; //some points reused so no need to calculate again
py1 = py2;

px2 = x + (curveCoord[i] * st);
py2 = y + (curveCoord[j] * st);

px3 = px4;
py3 = py4;

px4 = x + (curveCoord[i] * sm);
py4 = y + (curveCoord[j] * sm);

px5 = px6;
py5 = py6;

px6 = x + (curveCoord[i] * sb);
py6 = y + (curveCoord[j] * sb);

i = i + k;
j = j - k;

drawLineSeg(px1,py1,px2,py2,px3,py3,px4,py4,px5,py5,px6,py6);

 }
 	px4 = px4 + sm;
}

	else if (a == 2){
	
		x = x + sm;
		y = y + sm;

		i = 0;
		j = 24;
		//--
		//calculate the points to draw the first line segment.
		px1 = x + (-1.0 * curveCoord[i] * st);
		py1 = y + (-1.0 * curveCoord[j] * st);

		px2 = x + (-1.0 * curveCoord[i] * st);
		py2 = y + (-1.0 * curveCoord[j] * st);

		px3 = x + (-1.0 * curveCoord[i] * sm);
		py3 = y + (-1.0 * curveCoord[j] * sm);

		px4 = x + (-1.0 * curveCoord[i] * sm);
		py4 = y + (-1.0 * curveCoord[j] * sm);
 
		px5 = x + (-1.0 * curveCoord[i] * sb);
		py5 = y + (-1.0 * curveCoord[j] * sb);

		px6 = x + (-1.0 * curveCoord[i] * sb);
		py6 = y + (-1.0 * curveCoord[j] * sb);

		i = i + k;//move to the next coordinate. dependant on k
		j = j - k;
 
		//call the function to paint the first segment of the line.
		drawLineSeg(px1,py1,px2,py2,px3,py3,px4,py4,px5,py5,px6,py6);

		//calculate the points of the next line segments and paint with the draw function.

		while (j >= 0){ 

		px1 = px2; //some points reused so no need to calculate again
		py1 = py2;

		px2 = x + (-1.0 * curveCoord[i] * st);
		py2 = y + (-1.0 * curveCoord[j] * st);

		px3 = px4;
		py3 = py4;

		px4 = x + (-1.0 * curveCoord[i] * sm);
		py4 = y + (-1.0 * curveCoord[j] * sm);

		px5 = px6;
		py5 = py6;

		px6 = x + (-1.0 * curveCoord[i] * sb);
		py6 = y + (-1.0 * curveCoord[j] * sb);

		i = i + k;
		j = j - k;

		drawLineSeg(px1,py1,px2,py2,px3,py3,px4,py4,px5,py5,px6,py6);

		}

	px4 = px4 - sm;
	}



		else if (a == 3) {
					//-+

					x = x + sm;//places the bend in the correct position
					y = y - sm;

					i = 0;
					j = 24;
					//calculate the points to draw the first line segment.
					px1 = x + (-1.0 * curveCoord[i] * st);
					py1 = y + (curveCoord[j] * st);
	
					px2 = x + (-1.0 * curveCoord[i] * st);
					py2 = y + (curveCoord[j] * st);

					px3 = x + (-1.0 * curveCoord[i] * sm);
					py3 = y + (curveCoord[j] * sm);

					px4 = x + (-1.0 * curveCoord[i] * sm);
					py4 = y + (curveCoord[j] * sm);
 
					px5 = x + (-1.0 * curveCoord[i] * sb);
					py5 = y + (curveCoord[j] * sb);

					px6 = x + (-1.0 * curveCoord[i] * sb);
					py6 = y + (curveCoord[j] * sb);

					i =  i + k;//move to the next coordinate. dependant on k
					j = j - k;
 
					//call the function to paint the first segment of the line.
					drawLineSeg(px1,py1,px2,py2,px3,py3,px4,py4,px5,py5,px6,py6);
	
					//calculate the points of the next line segments and paint with the draw function.

					while (j >= 0){ 
 
					// for (int ii=0;ii<=24;ii+=k) {

					px1 = px2; //some points reused so no need to calculate again
					py1 = py2;

					px2 = x + (-1.0 * curveCoord[i] * st);
					py2 = y + (curveCoord[j] * st);

					px3 = px4;
					py3 = py4;

					px4 = x + (-1.0 * curveCoord[i] * sm);
					py4 = y + (curveCoord[j] * sm);

					px5 = px6;
					py5 = py6;

					px6 = x + (-1.0 * curveCoord[i] * sb);
					py6 = y + (curveCoord[j] * sb);

					i = i + k;
					j = j - k;

					drawLineSeg(px1,py1,px2,py2,px3,py3,px4,py4,px5,py5,px6,py6);

				}

						px4 = px4 - sm;
			}



						else if (a == 4) { 
							//+-
							x = x - sm;//places the bend in the correct position
							y = y + sm;

							i = 0;
							j = 24;
							//calculate the points to draw the first line segment.
							px1 = x + (curveCoord[i] * st);
							py1 = y + (-1.0 * curveCoord[j] * st);

							px2 = x + (curveCoord[i] * st);
							py2 = y + (-1.0 * curveCoord[j] * st);

							px3 = x + (curveCoord[i] * sm);
							py3 = y + (-1.0 * curveCoord[j] * sm);

							px4 = x + (curveCoord[i] * sm);
							py4 = y + (-1.0 * curveCoord[j] * sm);
	
							px5 = x + (curveCoord[i] * sb);
							py5 = y + (-1.0 * curveCoord[j] * sb);

							px6 = x + (curveCoord[i] * sb);
							py6 = y + (-1.0 * curveCoord[j] * sb);

							i =  i + k;//move to the next coordinate. dependant on k
							j = j - k;
 
							//call the function to paint the first segment of the line.
							drawLineSeg(px1,py1,px2,py2,px3,py3,px4,py4,px5,py5,px6,py6);


 
							//calculate the points of the next line segments and paint with the draw function.

						while (j >= 0){ 
 
							// for (int ii=0;ii<=24;ii+=k) {

							px1 = px2; //some points reused so no need to calculate again
							py1 = py2;

							px2 = x + (curveCoord[i] * st);
							py2 = y + (-1.0 * curveCoord[j] * st);
					
							px3 = px4;
							py3 = py4;

							px4 = x + (curveCoord[i] * sm);
							py4 = y + (-1.0 * curveCoord[j] * sm);

							px5 = px6;
							py5 = py6;

							px6 = x + (curveCoord[i] * sb);
							py6 = y + (-1.0 * curveCoord[j] * sb);

							i = i + k;
							j = j - k;

							drawLineSeg(px1,py1,px2,py2,px3,py3,px4,py4,px5,py5,px6,py6);
							}

							px4 = px4 + sm;
	}

}

void drawLine() {
	
	vector<float> xLineCoord;
	xLineCoord.push_back(183);
	xLineCoord.push_back(253);
	xLineCoord.push_back(273);
	xLineCoord.push_back(273);
	xLineCoord.push_back(273);
	xLineCoord.push_back(273);
	xLineCoord.push_back(183);
	xLineCoord.push_back(253);
	xLineCoord.push_back(273);
	xLineCoord.push_back(273);
	xLineCoord.push_back(273);
	xLineCoord.push_back(273);
	

	vector<float> yLineCoord;
	yLineCoord.push_back(300);
	yLineCoord.push_back(300);
	yLineCoord.push_back(300);
	yLineCoord.push_back(280);
	yLineCoord.push_back(245);
	yLineCoord.push_back(225);
	yLineCoord.push_back(100);
	yLineCoord.push_back(100);
	yLineCoord.push_back(100);
	yLineCoord.push_back(120);
	yLineCoord.push_back(155);
	yLineCoord.push_back(175);


	vector<int> bendOrientation;
	bendOrientation.push_back(1);
	bendOrientation.push_back(2);
	bendOrientation.push_back(4);
	bendOrientation.push_back(3);

	float nx1;
	float nx2;
	float nx3;
	float nx4;
	float nx5;
	float nx6;
	float ny1;
	float ny2;
	float ny3;
	float ny4;
	float ny5;
	float ny6;

	float bx;
	float by;
	int a;

	int i = 0;
	int ii = 0;

while(i < 12){
	nx3 = xLineCoord[i];
	ny3 = yLineCoord[i];
	i++;

	nx4 = xLineCoord[i];
	ny4 = yLineCoord[i];
	i++;

	if(ny3 == ny4){

		nx1 = nx3;
		nx5 = nx3;
		nx2 = nx4;
		nx6 = nx4;

		ny1 = ny3 + 2;
		ny5 = ny3 - 2;
		ny2 = ny4 + 2;
		ny6 = ny4 - 2;
	}

	else{
		
		nx1 = nx3 - 2;
		nx5 = nx3 + 2;
		nx2 = nx3 - 2;
		nx6 = nx4 + 2;

		ny1 = ny3;
		ny5 = ny3;
		ny2 = ny4;
		ny6 = ny4;
	}

	drawLineSeg(nx1,ny1,nx2,ny2,nx3,ny3,nx4,ny4,nx5,ny5,nx6,ny6);

	bx = xLineCoord[i];
	by = yLineCoord[i];
	i++;
	a = bendOrientation[ii];
	ii++;

	drawBend(bx,by,a);
}
}


//draw function
void Draw() {

glClearColor(1.0, 1.0, 1.0, 0.0);
glClear(GL_COLOR_BUFFER_BIT);

//draw function blocks

vector<float> Functionx;
Functionx.push_back(100);
Functionx.push_back(100);
Functionx.push_back(300);

vector<float> Functiony;
Functiony.push_back(400);
Functiony.push_back(200);
Functiony.push_back(300);

int i = 0;

while (i < 3){
	drawFunctionBlock(Functionx[i],Functiony[i]);
	i++;
}
i=0;

//draw ports facing right

vector<float> PortsRightx;
PortsRightx.push_back(175);
PortsRightx.push_back(175);
PortsRightx.push_back(175);
PortsRightx.push_back(175);
PortsRightx.push_back(375);
PortsRightx.push_back(375);
PortsRightx.push_back(375);

vector<float> PortsRighty;
PortsRighty.push_back(100);
PortsRighty.push_back(150);
PortsRighty.push_back(300);
PortsRighty.push_back(350);
PortsRighty.push_back(275);
PortsRighty.push_back(225);
PortsRighty.push_back(175);

while (i < 7){
	drawPort(PortsRightx[i],PortsRighty[i],0);
	i++;
}
i = 0;
//draw ports facing left

vector<float> PortsLeftx;
PortsLeftx.push_back(100);
PortsLeftx.push_back(100);
PortsLeftx.push_back(100);
PortsLeftx.push_back(100);
PortsLeftx.push_back(300);
PortsLeftx.push_back(300);
PortsLeftx.push_back(300);

vector<float> PortsLefty;
PortsLefty.push_back(100);
PortsLefty.push_back(150);
PortsLefty.push_back(300);
PortsLefty.push_back(350);
PortsLefty.push_back(275);
PortsLefty.push_back(225);
PortsLefty.push_back(175);


while (i < 7){
	drawPort(PortsLeftx[i],PortsRighty[i],1);
	i++;
}
i = 0;

drawLine();


glFlush();
}

void Initialise() {
	glOrtho(0,500,0,500,0.0f,100.0f);
	glClearDepth(1);
	glClear(GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	Image* image = loadBMP("C:/Users/Lee/functionBlock.bmp");
	_textureId = loadTexture(image);
	delete image;
}

int main(int iArgc, char** cppArgv) {
	glutInit(&iArgc, cppArgv);
	glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB );
	glClearColor(1.0,1.0,1.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glClearDepth(1.0f);
	glClear(GL_DEPTH_BUFFER_BIT);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("window");
	Initialise();
	glutDisplayFunc(Draw);
	glutMainLoop();
	
	return 0;
}