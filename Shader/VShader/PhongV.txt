varying vec3 nNormal;
varying vec3 v_pos3;

void main() {
  nNormal = normalize (gl_Normal);
  //vec4 v_pos4 = normalize( gl_ModelViewMatrix * gl_Vertex );
  vec4 v_pos4 = gl_Vertex;
  v_pos3 = vec3(v_pos4) / v_pos4.w;
  gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}




