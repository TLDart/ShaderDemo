uniform vec3 Light_dir;
uniform vec3 Obs_pos;

varying vec3 nNormal;
varying vec3 v_pos3;

float ks = 1.0;
float ka = 0.4;
float kd = 1.0;

vec4 color = vec4(0.2549, 0.902, 0.0, 1.0);
void main(void) {
    float ambient, diffuse, specular, specAngle;
    vec3 userVect;

    userVect = normalize((Obs_pos - v_pos3)); // Getting a vector from user to point
    vec3 specInvRay = reflect(Light_dir,nNormal);
    specAngle = max(dot(specInvRay, userVect), 0.0); //The product between the position of the camera and and Specular inverse ray
    //Ambient
    ambient = ka * 0.4;

    //Diffuse
    diffuse = kd * max(dot(Light_dir, nNormal), 0.0);

    //Specular
    specular = ks * pow(specAngle,2.1);

    gl_FragColor   = (ambient + diffuse + specular)* color ;
}
