xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 40;
 -9.50000;4.75000;-10.00000;,
 9.50000;4.75000;-10.00000;,
 9.50000;0.25000;-10.00000;,
 -9.50000;0.25000;-10.00000;,
 9.14640;5.00000;-9.64640;,
 -9.14640;5.00000;-9.64640;,
 10.00000;0.25000;-9.50000;,
 10.00000;4.75000;-9.50000;,
 -9.50000;0.00000;-9.50000;,
 9.50000;0.00000;-9.50000;,
 -10.00000;4.75000;-9.50000;,
 -10.00000;0.25000;-9.50000;,
 -9.64640;5.00000;-9.14640;,
 9.64640;5.00000;-9.14640;,
 10.00000;4.75000;9.50000;,
 10.00000;0.25000;9.50000;,
 9.64640;5.00000;9.14640;,
 9.50000;0.25000;10.00000;,
 9.50000;4.75000;10.00000;,
 9.50000;0.00000;9.50000;,
 9.14640;5.00000;9.64640;,
 -9.50000;4.75000;10.00000;,
 -9.50000;0.25000;10.00000;,
 -9.14640;5.00000;9.64640;,
 -10.00000;0.25000;9.50000;,
 -10.00000;4.75000;9.50000;,
 -9.50000;0.00000;9.50000;,
 -9.64640;5.00000;9.14640;,
 -8.50000;5.00000;8.50000;,
 8.50000;5.00000;8.50000;,
 8.50000;5.00000;-8.50000;,
 -8.50000;5.00000;-8.50000;,
 8.85360;5.00000;9.35360;,
 -8.85360;5.00000;9.35360;,
 9.35360;5.00000;-8.85360;,
 9.35360;5.00000;8.85360;,
 -8.85360;5.00000;-9.35360;,
 8.85360;5.00000;-9.35360;,
 -9.35360;5.00000;8.85360;,
 -9.35360;5.00000;-8.85360;;
 
 42;
 4;0,1,2,3;,
 4;4,1,0,5;,
 4;6,2,1,7;,
 4;8,3,2,9;,
 4;10,0,3,11;,
 4;10,12,5,0;,
 4;4,13,7,1;,
 3;6,9,2;,
 3;8,11,3;,
 4;7,14,15,6;,
 4;16,14,7,13;,
 4;17,15,14,18;,
 4;9,6,15,19;,
 4;16,20,18,14;,
 3;17,19,15;,
 4;18,21,22,17;,
 4;23,21,18,20;,
 4;24,22,21,25;,
 4;19,17,22,26;,
 4;23,27,25,21;,
 3;24,26,22;,
 4;25,10,11,24;,
 4;12,10,25,27;,
 4;26,24,11,8;,
 4;26,8,9,19;,
 4;28,29,30,31;,
 4;32,29,28,33;,
 4;34,30,29,35;,
 4;36,31,30,37;,
 4;38,28,31,39;,
 3;38,33,28;,
 3;32,35,29;,
 3;34,37,30;,
 3;36,39,31;,
 4;35,16,13,34;,
 4;20,16,35,32;,
 4;37,34,13,4;,
 4;33,23,20,32;,
 4;27,23,33,38;,
 4;39,12,27,38;,
 4;5,12,39,36;,
 4;37,4,5,36;;
 
 MeshMaterialList {
  2;
  42;
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.492800;0.661600;0.282400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.564800;0.464000;0.279200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  36;
  -0.312282;0.522143;-0.793629;,
  0.312282;0.522143;-0.793629;,
  0.441386;-0.323117;-0.837122;,
  -0.441386;-0.323117;-0.837122;,
  0.904034;0.323135;-0.279831;,
  0.793629;0.522143;0.312282;,
  0.837122;-0.323117;0.441386;,
  0.782011;-0.522117;-0.340370;,
  0.279831;0.323135;0.904034;,
  -0.312282;0.522143;0.793629;,
  -0.441386;-0.323117;0.837122;,
  0.340370;-0.522117;0.782011;,
  -0.904034;0.323135;0.279831;,
  -0.904034;0.323135;-0.279831;,
  -0.782011;-0.522117;-0.340370;,
  -0.782011;-0.522117;0.340370;,
  -0.224949;-0.948049;0.224949;,
  -0.224949;-0.948049;-0.224949;,
  0.224949;-0.948049;-0.224949;,
  0.224949;-0.948049;0.224949;,
  0.000000;1.000000;0.000000;,
  0.233282;0.968898;0.082555;,
  0.233282;0.968898;-0.082555;,
  -0.082555;0.968898;0.233282;,
  0.082555;0.968898;0.233282;,
  -0.233282;0.968898;-0.082555;,
  -0.233282;0.968898;0.082555;,
  0.082555;0.968898;-0.233282;,
  -0.082555;0.968898;-0.233282;,
  0.000000;-0.894427;-0.447214;,
  -0.316195;0.894451;-0.316195;,
  0.316195;0.894451;-0.316195;,
  0.447214;-0.894427;-0.000000;,
  0.316195;0.894451;0.316195;,
  0.000000;-0.894427;0.447214;,
  -0.316195;0.894451;0.316195;;
  42;
  4;0,1,2,3;,
  4;27,1,0,28;,
  4;7,2,1,4;,
  4;17,29,29,18;,
  4;13,0,3,14;,
  4;30,25,28,0;,
  4;27,22,31,1;,
  3;7,18,2;,
  3;17,14,3;,
  4;4,5,6,7;,
  4;21,5,4,22;,
  4;11,6,5,8;,
  4;18,7,32,19;,
  4;21,24,33,5;,
  3;11,19,6;,
  4;8,9,10,11;,
  4;23,9,8,24;,
  4;15,10,9,12;,
  4;19,11,34,16;,
  4;23,26,35,9;,
  3;15,16,10;,
  4;12,13,14,15;,
  4;25,13,12,26;,
  4;16,15,14,17;,
  4;16,17,18,19;,
  4;20,20,20,20;,
  4;20,20,20,20;,
  4;20,20,20,20;,
  4;20,20,20,20;,
  4;20,20,20,20;,
  3;20,20,20;,
  3;20,20,20;,
  3;20,20,20;,
  3;20,20,20;,
  4;20,21,22,20;,
  4;24,21,20,20;,
  4;20,20,22,27;,
  4;20,23,24,20;,
  4;26,23,20,20;,
  4;20,25,26,20;,
  4;28,25,20,20;,
  4;20,27,28,20;;
 }
}
