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
    diffuse = kd * max(dot(Light_dir, nNormal), 0.0);

    gl_FragColor =  diffuse * color;
    //gl_FragColor = vec4(1,1,0,1);
}
