#include <glew.h>
#include <glut.h>
#include "Lines.h"

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
	int k = 6;//changes how many points we use to draw a bend


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
//nodes
	float nodesX[7] = {50,100,100,200,200,50};
	float nodesY[7] = {250,250,200,200,100,100};

int a = 0;
int i = 0;

float nx1;
float ny1;
float nx2;
float ny2;
float nx3;
float ny3;
float nx4;
float ny4;
float nx5;
float ny5;
float nx6;
float ny6;

//get 1st point
nx3 = nodesX[i];
ny3 = nodesY[i];
i++;

//get next point
nx4 = nodesX[i];
ny4 = nodesY[i];
i++;

	//check horizontal/vertical

	//vertical
	if (nx3 == nx4){
		//calculate extra points
		nx1 = (nx3 + 2);
		ny1 = ny3;

		nx2 = (nx4 + 2);
		ny2 = ny4;

		nx5 = (nx3 - 2);
		ny5 = ny3;

		nx6 = nx4 - 2;
		ny6 = ny4;
		
		//line going down
		if (ny3 > ny4){
		//draw line seg to start of bend
		drawLineSeg(nx1,ny1,nx2,(ny2 + 20),nx3,ny3,nx4,(ny4 + 20),nx5,ny5,nx6,(ny6 + 20));
		
		//get next point
		nx3 = nx4;
		ny3 = ny4;
		nx4 = nodesX[i];
		ny4 = nodesY[i];
		i++;
		//draw bend
			if(nx3 > nx4){
				a = 4;
				drawBend(nx3,ny3,a);
				nx3 = nx3 - 20; 
			}
			else{
				a = 2;
				drawBend(nx3,ny3,a);
				nx3 = nx3 + 20;
			}

		}
		else {
			//line going up
		drawLineSeg(nx1,ny1,nx2,(ny2 - 20),nx3,ny3,nx4,(ny4 - 20),nx5,ny5,nx6,(ny6 - 20));

			if(nx3 > nx4){
				a = 3;
				drawBend(nx3,ny3,a);
				nx3 = (nx3 + 20);
			}
			else{
				a = 1;
				drawBend(nx3,ny3,a);
				nx3 = (nx3 - 20);
				}
			}
	}
	//horizontal
	else if (ny3 == ny4) { 
		
		nx1 = nx3;
		ny1 = (ny3 + 2);

		nx2 = nx4;
		ny2 = (ny4 + 2);

		nx5 = nx3;
		ny5 = (ny3 - 2);

		nx6 = nx4;
		ny6 = (ny4 - 2);
		//line to left
		if(nx3 > nx4){
		drawLineSeg(nx1,ny1,(nx2+20),ny2,nx3,ny3,(nx4+20),ny4,nx5,ny5,(nx6+20),ny6);

		nx3 = nx4;
		ny3 = ny4;
		nx4 = nodesX[i];
		ny4 = nodesY[i];
		i++;

			if(ny3 > ny4){
				a = 3;
				drawBend(nx3,ny3,a);
				py3 = py3 - 20;
			}
			else{
				a = 2;
				drawBend(nx3,ny3,a);
				ny3 = ny3 + 20;
			}

			
		}
		//line to right
		else{
		drawLineSeg(nx1,ny1,(nx2-20),ny2,nx3,ny3,(nx4-20),ny4,nx5,ny5,(nx6-20),ny6);

		nx3 = nx4;
		ny3 = ny4;
		nx4 = nodesX[i];
		ny4 = nodesY[i];
		i++;

			if(ny3 > ny4){
				a = 1;
				drawBend(nx3,ny3,a);
				ny3 = ny3 - 20;
			}
			else{
				a = 4;
				drawBend(nx3,ny3,a);
				ny3 = ny3 + 20;
			}	
		}

	}



while (i < 7){

	//vertical
	if (nx3 == nx4){
		//calculate extra points
		nx1 = (nx3 + 2);
		ny1 = ny3;

		nx2 = (nx4 + 2);
		ny2 = ny4;

		nx5 = (nx3 - 2);
		ny5 = ny3;

		nx6 = nx4 - 2;
		ny6 = ny4;
		
		//line going down
		if (ny3 > ny4){
		//draw line seg to start of bend
		drawLineSeg(nx1,ny1,nx2,(ny2 + 20),nx3,ny3,nx4,(ny4 + 20),nx5,ny5,nx6,(ny6 + 20));
		
		//get next point
		nx3 = nx4;
		ny3 = ny4;
		nx4 = nodesX[i];
		ny4 = nodesY[i];
		i++;
		//draw bend
			if(nx3 > nx4){
				a = 4;
				drawBend(nx3,ny3,a);
				nx3 = nx3 - 20; 
			}
			else{
				a = 2;
				drawBend(nx3,ny3,a);
				nx3 = nx3 + 20;
			}

		}
		else {
			//line going up
		drawLineSeg(nx1,ny1,nx2,(ny2 - 20),nx3,ny3,nx4,(ny4 - 20),nx5,ny5,nx6,(ny6 - 20));

			if(nx3 > nx4){
				a = 3;
				drawBend(nx3,ny3,a);
				nx3 = (nx3 + 20);
			}
			else{
				a = 1;
				drawBend(nx3,ny3,a);
				nx3 = (nx3 - 20);
				}
			}
	}
	//horizontal
	else if (ny3 == ny4) { 
		
		nx1 = nx3;
		ny1 = (ny3 + 2);

		nx2 = nx4;
		ny2 = (ny4 + 2);

		nx5 = nx3;
		ny5 = (ny3 - 2);

		nx6 = nx4;
		ny6 = (ny4 - 2);
		//line to left
		if(nx3 > nx4){
		drawLineSeg(nx1,ny1,(nx2+20),ny2,nx3,ny3,(nx4+20),ny4,nx5,ny5,(nx6+20),ny6);

		nx3 = nx4;
		ny3 = ny4;
		nx4 = nodesX[i];
		ny4 = nodesY[i];
		i++;

			if(ny3 > ny4){
				a = 3;
				drawBend(nx3,ny3,a);
				py3 = py3 - 20;
			}
			else{
				a = 2;
				drawBend(nx3,ny3,a);
				ny3 = ny3 + 20;
			}

			
		}
		//line to right
		else{
		drawLineSeg(nx1,ny1,(nx2-20),ny2,nx3,ny3,(nx4-20),ny4,nx5,ny5,(nx6-20),ny6);

		nx3 = nx4;
		ny3 = ny4;
		nx4 = nodesX[i];
		ny4 = nodesY[i];
		i++;

			if(ny3 > ny4){
				a = 1;
				drawBend(nx3,ny3,a);
				ny3 = ny3 - 20;
			}
			else{
				a = 4;
				drawBend(nx3,ny3,a);
				ny3 = ny3 + 20;
			}	
		}

	}

}


}



//draw function
void Draw() {

glClearColor(1.0, 1.0, 1.0, 0.0);
glClear(GL_COLOR_BUFFER_BIT);



drawLine();


glFlush();
}

//main function
void Initialize() {
	glOrtho(0,300,0,300,0.0f,100.0f);
	glClearDepth(1);
	glClear(GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

int main(int iArgc, char** cppArgv) {
	glutInit(&iArgc, cppArgv);
	glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB );
	glClearColor(1.0,1.0,1.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glClearDepth(1.0f);
	glClear(GL_DEPTH_BUFFER_BIT);
	glutInitWindowSize(300, 300);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("window");
	Initialize();
	glutDisplayFunc(Draw);
	glutMainLoop();
	
	return 0;
}

Lines::Lines(void)
{
}


Lines::~Lines(void)
{
}
