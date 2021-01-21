varying vec3 nNormal;
varying vec3 vPos3;

void main() {
  nNormal = normalize (gl_Normal);
  vPos3 = vec3(gl_Vertex) / gl_Vertex.w;
  gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}




