	/* ===================================================================================
	Departamento Eng. Informatica - FCTUC
	Computacao Grafica - 2020/21
	................................................... JHenriques / EPolisciuc / Cteixeira
	======================================================================================= */

//.................................................... Bibliotecas necessarias
#include <stdio.h>				// printf
#include <fstream>				// printf

#include <string>
#include <fstream>

#include <errno.h>
#include <GL/glew.h>			// openGL
#include <GL/freeglut.h>		// openGL

#pragma comment(lib,"glew32.lib")
#pragma comment(lib,"glu32.lib")
#pragma comment(lib,"opengl32.lib")

//.................................................... Variaveis
GLint	wScreen = 800, hScreen = 800;		//.. janela

//------------------------------------------------------------ Observador 
// LUZ
// n�o � necess�rio definir propriedades da luz
// Vamos fazer as contas !!!


										   //------------------------------------------ Defini��o dos ficheiros dos shaders: vertices + fragmentos

//---------------------------------------------------------- SHADERS variaveis
char* VertexShaderSource;
char* FragmentShaderSource;
GLuint  VertexShader, FragmentShader;
GLuint  ShaderProgram[2];


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
void BuiltShader(char* fv, char* ff, int n) {

	//GLEW_ARB_vertex_shader;
	//GLEW_ARB_fragment_shader;

	//......................................................... Criar
	VertexShader = glCreateShader(GL_VERTEX_SHADER);
	FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	VertexShaderSource = readShaderFile(fv);
	FragmentShaderSource = readShaderFile(ff);

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
	ShaderProgram[n] = glCreateProgramObjectARB();
	glAttachShader(ShaderProgram[n], VertexShader);
	glAttachShader(ShaderProgram[n], FragmentShader);
	glLinkProgram(ShaderProgram[n]);

	//......................................................... Usar
}


void InitShader(void) {

	//------------------------ Criar+linkar
char filenameV[] = "Shader/VShader/gouraudV.txt";
char filenameF[] = "Shader/FShader/gouraudF.txt";
BuiltShader(filenameV,filenameF,0);
char filenameV1[] = "Shader/VShader/Vshader_pervertex1.txt";
BuiltShader(filenameV1,filenameF,1);

}


//============================================= 3.Libertar os Shaders
void DeInitShader(int n) {
	glDetachShader(ShaderProgram[n], VertexShader);
	glDetachShader(ShaderProgram[n], FragmentShader);
	glDeleteShader(ShaderProgram[n]);
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
	glEnable(GL_NORMALIZE);
}


//-----------------------------------------------------------------------------------
//-------------------------------------------------------------------- INTERACCAO
//-----------------------------------------------------------------------------------

//---------------------------------------- Fun��o callback de desenho (principal)
void Desenha(void)
{

	glUseProgramObjectARB(ShaderProgram[1]);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, wScreen, hScreen);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(80, 1, 0.1, 10.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 1, 6, 0, 0, 0, 0, 1, 0);
	
	
	glColor3f(1, 0.5, 0);   // cor  A
	glPushMatrix();
	glTranslatef(-1, -1, 0);
	glutSolidTeapot(1);
	glPopMatrix();

	glUseProgramObjectARB(ShaderProgram[0]);
	glPushMatrix();
	glTranslatef(3, -1, 0);
	glutSolidTeapot(1);
	glPopMatrix();

	glutSwapBuffers();						//.. actualiza ecran
}

void Teclado(unsigned char key, int x, int y) {

	switch (key) {
	case 27:					//ESC
		exit(0);
		break;
	}
}



int main(int argc, char** argv)
{
	glutInit(&argc, argv);							//===1:Inicia janela
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 800);					//		:dimensoes (pixeis)
	glutInitWindowPosition(500, 40);				//		:localizacao
	glutCreateWindow(" :::::::: Exemplo | per Vertex  | jh/ep/ct @dei - 2020/21  :::::::: ");

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Inicializa();

	//------------------------------------  GLEW
	GLenum err = glewInit();
	InitShader();
	DeInitShader(0);
	   
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//===3:Definicao callbaks	
	glutDisplayFunc(Desenha);						//		:desenho
	glutKeyboardFunc(Teclado);						//		:eventos teclado
	glutIdleFunc(Desenha);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	glutMainLoop();								//===4:Inicia processamento
	return 1;
}
