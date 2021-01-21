//Defining the material coeficients, set to 1 for testing
float ks = 0.8;
float ka = 0.4;
float kd = 0.3;
uniform vec3 lightDir;
uniform vec3 userPos;

vec4 mat = vec4(0.4,0.3,0.8, 22.0); //Defines ka,ks,kd and shininess of the material
vec4 matP = vec4(0.0275, 0.4118, 0.9922, 1.0); // Color of the material
vec4 lightP = vec4(1.0,1.0,1.0, 1.0);// Color of the light 


//Notes:
// In the gouraud method the vertex are calculated using the Phong method and the Fragments are calculated using an interpolation of the Vertex

/* What is what
According to slide 110 T6
N -> Normalize normal vector
R -> Specular Direction Vector
I -> Inverse Direction of light, since we have light direction we use -I
V -> Inverse (Vector -> User ) User Vector 
*/

void main(void) { 
        float ambient, diffuse, specular;
        vec3 N, vpos, V , R, I = lightDir;

        N = normalize(gl_Normal);
	I  = normalize(I); 

        vpos = vec3(gl_Vertex) / gl_Vertex.w; // Getting the position of the vector in 3 space 
        
        //Ambient 
        ambient = mat[0] * 0.4;

        //Difuse
        diffuse = mat[1] * max(dot(-I, N), 0.0);

        //Specular
        V = normalize((userPos - vpos)); // Getting a vector from user to point
        R = reflect(-I,N);
        specular = mat[2] * pow(max(dot(R, -V), 0.0),mat[3]);

        //Calculating the color
        gl_FrontColor   = (ambient + diffuse + specular)* matP * lightP;
        gl_Position     = gl_ModelViewProjectionMatrix * gl_Vertex;	
}

