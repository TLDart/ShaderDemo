//Defining the material coeficients, set to 1 for testing
float ks = 1.0;
float ka = 0.4;
float kd = 1.0;
attribute vec3 position;
varying vec3 vertPos;
uniform vec3 Direcao;
uniform vec3 userPos;
vec3 lightDir = Direcao;
varying vec3  specInvRay;	


//Notes:
// In the gouraud method the vertex are calculated using the Phong method and the Fragments are calculated using an interpolation of the Vertex

void main(void) { 
        float ambient, diffuse, specular, specAngle;
        vec3 normal, vpos3, userVect;
        normal   = normalize(gl_Normal);
	lightDir  = normalize (lightDir);   
        vpos3 = vec3(gl_Vertex) / gl_Vertex.w; // Getting the position of the vector in 3 space 
        userVect = normalize((userPos - vpos3)); // Getting a vector from user to point
        specInvRay = reflect(lightDir,normal);
        specAngle = max(dot(specInvRay, userVect), 0.0); //The product between the position of the camera and and Specular inverse ray
        //Ambient 
        ambient = ka * 0.4;

        //Difuse
        diffuse = kd * max(dot(lightDir, normal), 0.0);

        //Specular
        specular = ks * pow(specAngle,2.1);

        //Calculating the color
        //after calculating the intensity we can then determine the color a determined point
        gl_FrontColor   = (ambient + diffuse + specular)* gl_Color ;
        gl_Position     = gl_ModelViewProjectionMatrix * gl_Vertex;	
}

