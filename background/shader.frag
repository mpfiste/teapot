varying vec3 ec_vnormal, ec_vposition, ec_vtangent, ec_vbitangent;
uniform sampler2D myDiffuse;
uniform sampler2D myNormal;
uniform sampler2D mySpecular;

void main() {
   mat3 tform;
   vec3 P, N, L, V, H, mapN, tcolor, scolor;
   vec4 diffuse_color, specular_color;
   float shininess = gl_FrontMaterial.shininess;
   float pi = 3.14159;

   tform = mat3(ec_vtangent, ec_vbitangent, ec_vnormal);
   P = ec_vposition;
   L = normalize(gl_LightSource[0].position - P);
   V = normalize(-P);
   H = normalize(L+V);

   mapN = vec3(texture2D(myNormal, gl_TexCoord[0].st));
   mapN.xy = 2.0*mapN.xy - vec2(1.0, 1.0);
   N = normalize(tform*normalize(mapN));

   tcolor = vec3(texture2D(myDiffuse, gl_TexCoord[0].st));
   diffuse_color = vec4(tcolor, 1.0)*max(dot(N,L), 0.0);
   specular_color = gl_FrontMaterial.specular*pow(max(dot(H,N), 0.0), shininess);
   specular_color *= (shininess+2.0)/(8.0*pi);

//   scolor = vec3(texture2D(mySpecular, gl_TexCoord[0].st));
//   specular_color *= vec4(scolor, 1.0);

   gl_FragColor = 0.8 * (diffuse_color + specular_color);
}
