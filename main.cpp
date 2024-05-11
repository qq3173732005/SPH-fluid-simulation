#define GL_SILENCE_DEPRECATION
#if __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <vector>
using namespace std;

#include <eigen3/Eigen/Dense>
using namespace Eigen;

// solver parameters
const static Vector2d G(0.f, -10.f);   // external (gravitational) forces
const static float REST_DENS = 300.f;  // rest density
const static float GAS_CONST = 2000.f; // const for equation of state
const static float H = 16.f;		   // kernel radius
const static float HSQ = H * H;		   // radius^2 for optimization
const static float MASS = 2.5f;		   // assume all particles have the same mass
const static float VISC = 200.f;	   // viscosity constant
const static float DT = 0.0007f;	   // integration timestep

// adapted to 2D per "SPH Based Shallow Water Simulation" by Solenthaler et al.
const static float POLY6 = 4.f / (M_PI * pow(H, 8.f));
const static float SPIKY_GRAD = -10.f / (M_PI * pow(H, 5.f));
const static float VISC_LAP = 40.f / (M_PI * pow(H, 5.f));

// simulation parameters
const static float EPS = H; // boundary epsilon
const static float BOUND_DAMPING = -0.5f;




// interaction
const static int MAX_PARTICLES = 2500;
const static int DAM_PARTICLES = 500;
const static int BLOCK_PARTICLES = 250;

// rendering projection parameters
const static int WINDOW_WIDTH = 800;
const static int WINDOW_HEIGHT = 600;
const static double VIEW_WIDTH = 1.5 * 800.f;
const static double VIEW_HEIGHT = 1.5 * 600.f;



// PARTICLE STRUCT
struct Particle
{
    // position (x), velocity (v), force (f), density (rho), pressure (p)
    // uses Eigen library
	Particle(float _x, float _y) : x(_x, _y), v(0.f, 0.f), f(0.f, 0.f), rho(0), p(0.f) {}
	Vector2d x, v, f;
	float rho, p;
};

// solver data
static vector<Particle> particles;

// RENDERING SYSTEMS
void InitGL(void){
    // initializes GL: sets background color, point smoothing, 
    glClearColor(0.9f, 0.9f, 0.9f, 1);
	glEnable(GL_POINT_SMOOTH);
	glPointSize(H / 2.f);
	glMatrixMode(GL_PROJECTION);
}
void Render(void){
    // clears GL and sets up coord system, particle color
    // loops through particles array and places vertex at x/y
    glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();
	glOrtho(0, VIEW_WIDTH, 0, VIEW_HEIGHT, 0, 1);

	glColor4f(0.2f, 0.6f, 1.f, 1);
	glBegin(GL_POINTS);
	for (auto &p : particles)
	{
		glVertex2f(p.x(0), p.x(1));
	}
	glEnd();

	glutSwapBuffers();
}

// SOLVER
void InitSPH(void){}
void Integrate(void){}
void ComputeDensityPressure(void){}
void ComputeForces(void){}
void Update(void){
    // called between frame renders to step sim state forward
    // according to SPH, first compute densities, then compute pressure
    // then use densities and pressure to calculate the forces acting on each particle, which are used by Integrate()
    ComputeDensityPressure();
	ComputeForces();
	Integrate();

	glutPostRedisplay();
}

// MAIN
void Keyboard(unsigned char c){}

int main(int argc, char **argv)
{
	return 0;
}