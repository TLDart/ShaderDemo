#include <stdio.h>				
#include <fstream>				

#include <string>
#include <fstream>

#include <errno.h>
#include <GL/glew.h>			
#include <GL/freeglut.h>		
#include <math.h>	

#pragma comment(lib,"glew32.lib")
#pragma comment(lib,"glu32.lib")
#pragma comment(lib,"opengl32.lib")
#define PI 3.14159

GLint	width = 800, height = 800;	
GLfloat  rProjection = 15, aProjection = 0.5* PI, incProjection = 0.25;
float obsP[] = {0,0,4};
GLfloat  obsT[] = { obsP[0] - rProjection * cos(aProjection), obsP[1], obsP[2] - rProjection * sin(aProjection) };
GLfloat		worldMax = 30.0;	
int type = 0;	
GLint  uniOp[2];
GLint  uniDir[2];
GLint  uniUserPos[2];
float  Direcao[] = {0, -1, 1 };
float  opcao = 0;

char* VertexShaderSource;
char* FragmentShaderSource;
GLuint  VertexShader[2], FragmentShader[2];
GLuint  ShaderProgram[2];


char* readShaderFile(char* FileName) {

	char* DATA = NULL;
	int   flength = 0;
	FILE* filepoint;

	filepoint = fopen(FileName, "r");
	if (filepoint) {
		fseek(filepoint, 0, SEEK_END);
		flength = ftell(filepoint);
		rewind(filepoint);

		DATA = (char*)malloc(sizeof(char) * (flength + 1));
		flength = fread(DATA, sizeof(char), flength, filepoint);

		DATA[flength] = '\0';
		fclose(filepoint);
		return DATA;
	}
	else {
		printf(" --------  Error while reading  %s ", FileName);
		return NULL;
	}
}


//============================================= 2. Criar, compilar, linkar, e usar
void BuiltShader(char * f1, char* f2, int n) {


	GLEW_ARB_vertex_shader;
	GLEW_ARB_fragment_shader;

	//......................................................... Criar
	VertexShader[n] = glCreateShader(GL_VERTEX_SHADER);
	FragmentShader[n] = glCreateShader(GL_FRAGMENT_SHADER);
	VertexShaderSource = readShaderFile(f1);
	FragmentShaderSource = readShaderFile(f2);

	const char* VS = VertexShaderSource;
	const char* FS = FragmentShaderSource;
	glShaderSource(VertexShader[n], 1, &VS, NULL);
	glShaderSource(FragmentShader[n], 1, &FS, NULL);
	free(VertexShaderSource);
	free(FragmentShaderSource);

	//......................................................... Compilar
	glCompileShaderARB(VertexShader[n]);
	glCompileShaderARB(FragmentShader[n]);

	//......................................................... Criar e Linkar
	ShaderProgram[n] = glCreateProgramObjectARB();
	glAttachShader(ShaderProgram[n], VertexShader[n]);
	glAttachShader(ShaderProgram[n], FragmentShader[n]);
	glLinkProgram(ShaderProgram[n]);

	//......................................................... Usar
	glUseProgramObjectARB(ShaderProgram[n]);
}


void InitShader(void) {

	//------------------------ Criar+linkar
	char filenameV[] = "Shader/VShader/gouraudV.glsl";
	char filenameF[] = "Shader/FShader/gouraudF.glsl";
	BuiltShader(filenameV, filenameF, 0);
	glUseProgramObjectARB(ShaderProgram[0]);
	uniDir[0] = glGetUniformLocation(ShaderProgram[0], "lightDir");
	glUniform3fv(uniDir[0], 1, Direcao);
	uniUserPos[0] = glGetUniformLocation(ShaderProgram[0], "userPos");
	glUniform3fv (uniUserPos[0], 1, obsP);

	char filenameV1[] = "Shader/VShader/PhongV.glsl";
	char filenameF1[] = "Shader/FShader/PhongF.glsl";
	BuiltShader(filenameV1, filenameF1, 1);
	glUseProgramObjectARB(ShaderProgram[1]);
	uniDir[1] = glGetUniformLocation(ShaderProgram[1], "lightDir");
	glUniform3fv(uniDir[1], 1, Direcao);
	uniUserPos[1] = glGetUniformLocation(ShaderProgram[1], "userPos");
	glUniform3fv (uniUserPos[1], 1, obsP);
	
}


//============================================= 3.Libertar os Shaders
void DeInitShader(int n) {
	glDetachShader(ShaderProgram[n], VertexShader[n]);
	glDetachShader(ShaderProgram[n], FragmentShader[n]);
	glDeleteShader(ShaderProgram[n]);
}

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 1.0);	//....	Cor para apagar ecran (Preto)

	glShadeModel(GL_SMOOTH);				//....  Interpolacao de cor com base na cor dos vertices
	glEnable(GL_DEPTH_TEST);

}

void Desenha(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(type ==0)
		glOrtho(-5, 5, -5, 5, -5, 5);
	else
		gluPerspective(90, 1, 0.1, 10.0);


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if(type == 0)
		gluLookAt(obsP[0],obsP[1],obsP[2], obsT[0], obsT[1], obsT[2], 0, 1, 0);
	else
		gluLookAt(obsP[0],obsP[1],obsP[2], obsT[0], obsT[1], obsT[2], 0, 1, 0);
	
	Direcao[0] = cos(3.14*opcao/180.0);
	Direcao[2] = sin(3.14 * opcao / 180.0);

	glUseProgramObjectARB(ShaderProgram[1]);
	glUniform1f(uniOp[0], opcao);
	glUniform3fv(uniDir[0], 1, Direcao);
	glUniform3fv (uniUserPos[0], 1, obsP);

	glColor3f(1,1,0);
	glPushMatrix();
		glTranslatef(2, 0, 0);
		//glutSolidTeapot(1);
		glutSolidSphere(0.8,32,32);
	glPopMatrix();
	
	glUseProgramObjectARB(ShaderProgram[0]);
	glUniform1f(uniOp[1], opcao);
	glUniform3fv(uniDir[1], 1, Direcao);
	glUniform3fv (uniUserPos[1], 1, obsP);


	glColor3f(1,0,0);
	glPushMatrix();
		glTranslatef(-2, 0, 0);
		//glutSolidTeapot(1);
		glutSolidSphere(0.8,32,32);
	glPopMatrix();

	glutSwapBuffers();						
}

void Teclado(unsigned char key, int x, int y) {

	switch (key) {
		case 't':
			type = !type;

		case 'o':
		case 'O':
			opcao = opcao+10;
			glutPostRedisplay();
			break;
		case 27:					//ESC
			exit(0);
			break;
	}
}

GLvoid resize(GLsizei w, GLsizei h) {
	width= w;
	height = h;
	glViewport(0, 0, width, height);
	glutPostRedisplay();
}

void arrowKeys(int key, int x, int y) {
		
		if (key == GLUT_KEY_UP)    {obsP[0] = obsP[0] + incProjection * cos(aProjection); obsP[2] = obsP[2] - incProjection * sin(aProjection); }
		if (key == GLUT_KEY_DOWN)  {obsP[0] = obsP[0] - incProjection * cos(aProjection); obsP[2] = obsP[2] + incProjection * sin(aProjection); }
		if (key == GLUT_KEY_LEFT)  aProjection += 0.1;
		if (key == GLUT_KEY_RIGHT) aProjection -= 0.1;

		if (obsP[1] > worldMax)   obsP[1] = worldMax;
		if (obsP[1] < -worldMax)  obsP[1] = -worldMax;

		obsT[0] = obsP[0] + rProjection * cos(aProjection);
		obsT[2] = obsP[2] - rProjection* sin(aProjection);
		   
	    glutPostRedisplay();

}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);							//===1:Inicia janela
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 800);					//		:dimensoes (pixeis)
	glutInitWindowPosition(500, 40);				//		:localizacao
	glutCreateWindow("Phong and Gouraud Shader Demo");
	glutReshapeFunc(resize);
	init();

	GLenum err = glewInit();
	InitShader();


	glutSpecialFunc(arrowKeys); 
	

	glutDisplayFunc(Desenha);						
	glutKeyboardFunc(Teclado);						
	glutIdleFunc(Desenha);

	
	glutMainLoop();								
	DeInitShader(0);
	DeInitShader(1);
	return 1;
}
