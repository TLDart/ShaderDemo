uniform vec3 Light_dir;
uniform vec3 Obs_pos;

varying vec3 nNormal;
varying vec3 v_pos3;

float A_intensity;
float D_intensity;
float S_intensity;

float ka = 0.6;
float kd = 0.6;
float ks = 0.8;

vec4 ra_color = vec4(0, 0.3, 0.3, 1.0);
vec4 rd_color = vec4(0, 0.5, 0.5, 1.0);
vec4 rs_color = vec4(0, 0.9, 0.9, 1.0);

vec4 Light = vec4(1, 1, 1, 1);

vec4 color;

void main(void) {


    vec3 r = 2.0 * dot(Light_dir, nNormal) * nNormal - Light_dir;
    vec3 v = Obs_pos - v_pos3;

    A_intensity = 0.1;
    D_intensity = max(dot(Light_dir, nNormal), 0.0);
    S_intensity = pow(max (dot(r, v), 0.0), 16.0);

    vec4 ambient = ka * ra_color * Light;
    vec4 difuse = kd * rd_color * Light;
    vec4 specular = ks * rs_color * Light;

    //color = (A_intensity + D_intensity + S_intensity) * cor;
    //color = (A_intensity + D_intensity) * cor;
    color = (A_intensity * ambient) + (D_intensity * difuse) + (S_intensity * specular);

    gl_FragColor = color;
    //gl_FragColor = vec4(1,1,0,1);
}
