//Defining the material coeficients, set to 1 for testing
float ks = 0.8;
float ka = 0.4;
float kd = 0.3;
attribute vec3 position;
varying vec3 vertPos;
uniform vec3 Direcao;
uniform vec3 userPos;
vec3 I = Direcao;
varying vec3  R;	


//Notes:
// In the gouraud method the vertex are calculated using the Phong method and the Fragments are calculated using an interpolation of the Vertex

vec4 color = vec4(0.0275, 0.4118, 0.9922, 1.0);
void main(void) { 
        float ambient, diffuse, specular;
        vec3 N, vpos3, V;

        N = normalize(gl_Normal);
	I  = normalize(I); 

        vpos3 = vec3(gl_Vertex) / gl_Vertex.w; // Getting the position of the vector in 3 space 
        
        //Ambient 
        ambient = ka * 0.4;

        //Difuse
        diffuse = kd * max(dot(-I, N), 0.0);

        //Specular
        V = normalize((userPos - vpos3)); // Getting a vector from user to point
        R = reflect(-I,N);
        specular = ks * pow(max(dot(R, -V), 0.0),22.0);

        //Calculating the color
        //after calculating the intensity we can then determine the color a determined point
        gl_FrontColor   = (ambient + diffuse + specular)* color ;
        gl_Position     = gl_ModelViewProjectionMatrix * gl_Vertex;	
}

