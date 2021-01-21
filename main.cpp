/* ===================================================================================
	Departamento Eng. Informatica - FCTUC
	Computacao Grafica - 2019/20
	................................................... JHenriques / EPolisciuc
	======================================================================================= */


	//.................................................... Bibliotecas necessarias
#include <stdio.h>				// printf
#include <fstream>				// printf

#include <string>
#include <fstream>

#include <errno.h>
#include <GL/glew.h>			// openGL
#include <GL/freeglut.h>		// openGL
#include <math.h>		// openGL

#pragma comment(lib,"glew32.lib")
#pragma comment(lib,"glu32.lib")
#pragma comment(lib,"opengl32.lib")

//.................................................... Variaveis
GLint	wScreen = 800, hScreen = 800;		//.. janela

//------------------------------------------------------------ Observador 

GLint  uniOp  ;
GLint  uniDir ;
GLint  uniUserPos;
float  Direcao[] = { 1, 0, 1 };
float userPos[] = {0,1,6};
float  opcao = -45;

//------------------------------------------ Defini��o dos ficheiros dos shaders: vertices + fragmentos
char filenameV[] = "Shader/VShader/gouraudV.txt";
char filenameF[] = "Shader/FShader/gouraudF.txt";

//---------------------------------------------------------- SHADERS variaveis
char* VertexShaderSource;
char* FragmentShaderSource;
GLuint  VertexShader, FragmentShader;
GLuint  ShaderProgram;


//============================================= 1. Ler um ficheiro com um shader
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
	}
}


//============================================= 2. Criar, compilar, linkar, e usar
void BuiltShader(void) {

	GLEW_ARB_vertex_shader;
	GLEW_ARB_fragment_shader;

	//......................................................... Criar
	VertexShader = glCreateShader(GL_VERTEX_SHADER);
	FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	VertexShaderSource = readShaderFile(filenameV);
	FragmentShaderSource = readShaderFile(filenameF);

	const char* VS = VertexShaderSource;
	const char* FS = FragmentShaderSource;
	glShaderSource(VertexShader, 1, &VS, NULL);
	glShaderSource(FragmentShader, 1, &FS, NULL);
	free(VertexShaderSource);
	free(FragmentShaderSource);

	//......................................................... Compilar
	glCompileShaderARB(VertexShader);
	glCompileShaderARB(FragmentShader);

	//......................................................... Criar e Linkar
	ShaderProgram = glCreateProgramObjectARB();
	glAttachShader(ShaderProgram, VertexShader);
	glAttachShader(ShaderProgram, FragmentShader);
	glLinkProgram(ShaderProgram);

	//......................................................... Usar
	glUseProgramObjectARB(ShaderProgram);
}


void InitShader(void) {

	//------------------------ Criar+linkar
	BuiltShader();

	//------------------------------------  UYNIORM
	
	uniDir = glGetUniformLocation(ShaderProgram, "Direcao");
	glUniform3fv(uniDir, 1, Direcao);
	uniOp = glGetUniformLocation(ShaderProgram, "opcao");
	glUniform1f (uniOp, opcao);
	uniUserPos = glGetUniformLocation(ShaderProgram, "userPos");
	glUniform3fv (uniUserPos, 1, userPos);
}


//============================================= 3.Libertar os Shaders
void DeInitShader(void) {
	glDetachShader(ShaderProgram, VertexShader);
	glDetachShader(ShaderProgram, FragmentShader);
	glDeleteShader(ShaderProgram);
}


//=========================================================================== 
//==================================================================  SHADERS
//=========================================================================== 



//-----------------------------------------------------------------------------------
//																		Inicializacao
//-----------------------------------------------------------------------------------
void Inicializa(void)
{
	glClearColor(0.0, 0.0, 0.0, 1.0);	//....	Cor para apagar ecran (Preto)

	glShadeModel(GL_SMOOTH);				//....  Interpolacao de cor com base na cor dos vertices
	glEnable(GL_DEPTH_TEST);

}


//-----------------------------------------------------------------------------------
//-------------------------------------------------------------------- INTERACCAO
//-----------------------------------------------------------------------------------

//---------------------------------------- Fun��o callback de desenho (principal)
void Desenha(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, wScreen, hScreen);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, 1, 0.1, 10.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(userPos[0],userPos[1],userPos[2], 0, 0, 0, 0, 1, 0);
	
	glUniform1f(uniOp, opcao);
	glUniform3fv(uniDir, 1, Direcao);

	Direcao[0] = cos(3.14*opcao/180.0);
	Direcao[2] = sin(3.14 * opcao / 180.0);
	glUseProgramObjectARB(ShaderProgram);
	glColor3f(1,1,0);
	glPushMatrix();
		glTranslatef(2, 0, 0);
		glutSolidTeapot(1);
	glPopMatrix();
	

	
	glColor3f(1,0,0);
	glPushMatrix();
		glTranslatef(-2, 0, 0);
		glutSolidTeapot(1);
	glPopMatrix();

	glutSwapBuffers();						//.. actualiza ecran
}


// -----------------------------------------------------------------------

//����������������������������������������Fun��o callback eventos teclado 
void Teclado(unsigned char key, int x, int y) {

	switch (key) {

	case 'o':
	case 'O':
		opcao = opcao+10;
		glutPostRedisplay();
		break;
	case 'w':
		userPos[0]++;
		glutPostRedisplay();
		break;
	case 's':
		userPos[0]--;
		glutPostRedisplay();
		break;
	case 'a':
		userPos[1]++;
		glutPostRedisplay();
		break;
	case 'd':
		userPos[1]--;
		glutPostRedisplay();
		break;
	case 27:					//ESC
		exit(0);
		break;
	}
}



//-----------------------------------------------------------------------------------
//																		         MAIN
//-----------------------------------------------------------------------------------
int main(int argc, char** argv)
{
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	glutInit(&argc, argv);							//===1:Inicia janela
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 800);					//		:dimensoes (pixeis)
	glutInitWindowPosition(500, 40);				//		:localizacao
	glutCreateWindow(" ::: #Varying1 | Teclas O  | jh/ct/ep @dei - 2020/21  :::::::: ");

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Inicializa();

	//------------------------------------  GLEW
	GLenum err = glewInit();
	InitShader();

	DeInitShader();



	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
													//===3:Definicao callbaks	
	glutDisplayFunc(Desenha);						//		:desenho
	glutKeyboardFunc(Teclado);						//		:eventos teclado
	glutIdleFunc(Desenha);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	glutMainLoop();								//===4:Inicia processamento
	return 1;
}
