uniform vec3 lightDir;
uniform vec3 userPos;

varying vec3 nNormal;
varying vec3 vPos3;



vec4 mat = vec4(0.4,0.3,0.8, 22.0); //Defines ka,ks,kd and shininess of the material
vec4 matP = vec4(0.2549, 0.902, 0.0, 1.0); // Color of the mat
vec4 lightP = vec4(1.0,1.0,1.0, 1.0); //Color of the light

/* What is what
According to slide 110 T6
N -> Normalize normal vector
R -> Specular Direction Vector
I -> Inverse Direction of light, since we have light direction we use -I
V -> Inverse (Vector -> User ) User Vector 
*/
void main(void) {
    float ambient, diffuse, specular;
    vec3 V,N, R, I;
    I = normalize(lightDir);
    N = normalize(nNormal);
    V = normalize((userPos - vPos3)); // Getting a vector from user to point

    //Ambient
    ambient = mat[0] * 0.4;

    //Diffuse
    diffuse = mat[1] * max(dot(-I, N), 0.0);

    //Specular
    R = reflect(-I,N);
    specular = mat[2] * pow(max(dot(R, -V), 0.0),mat[3]);

    gl_FragColor   = (ambient + diffuse + specular)* matP * lightP ;
}
