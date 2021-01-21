uniform vec3 Light_dir;
uniform vec3 userPos;

varying vec3 nNormal;
varying vec3 vPos3;

float ks = 0.8;
float ka = 0.4;
float kd = 0.3;

vec4 color = vec4(0.2549, 0.902, 0.0, 1.0);
void main(void) {
    float ambient, diffuse, specular;
    vec3 V,N, R, I;
    I = normalize(Light_dir);
    N = normalize(nNormal);
    V = normalize((userPos - vPos3)); // Getting a vector from user to point

    //Ambient
    ambient = ka * 0.4;

    //Diffuse
    diffuse = kd * max(dot(-I, N), 0.0);

    //Specular
    R = reflect(-I,N);
    specular = ks * pow(max(dot(R, -V), 0.0),22.0);

    gl_FragColor   = (ambient + diffuse + specular)* color ;
}
