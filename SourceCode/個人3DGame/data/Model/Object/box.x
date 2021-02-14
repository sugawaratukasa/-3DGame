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
 111;
 -11.59792;-8.85629;-14.61748;,
 9.52232;11.13428;-14.61748;,
 -11.59792;-11.13428;-14.61748;,
 -7.89459;-11.13428;-14.61748;,
 11.59792;7.15914;-14.61748;,
 11.59792;11.13428;-14.61748;,
 -8.77383;14.26892;11.56755;,
 11.37142;14.26892;11.56755;,
 11.37142;14.26892;-8.54639;,
 9.52232;11.13428;14.15004;,
 0.00000;11.13428;14.15004;,
 -11.59792;11.13428;14.15004;,
 -11.59792;-8.85629;14.15004;,
 -15.00000;-15.00000;-15.00000;,
 0.00000;-15.00000;-15.00000;,
 -15.00000;-15.00000;15.00000;,
 0.00000;-15.00000;15.00000;,
 15.00000;-15.00000;15.00000;,
 15.00000;-15.00000;-15.00000;,
 14.55134;-11.15413;11.46461;,
 14.55134;-11.15413;8.81537;,
 14.55134;-8.22327;11.46461;,
 14.55134;11.15412;-9.61404;,
 14.55134;7.97410;-11.46463;,
 14.55134;11.15412;-11.46463;,
 -14.18701;-8.22327;11.46461;,
 -14.18701;11.15412;11.46461;,
 -14.18701;11.15412;-9.61404;,
 15.00000;-15.00000;-15.00000;,
 15.00000;-11.15413;-11.46463;,
 15.00000;-11.15413;11.46461;,
 15.00000;-15.00000;15.00000;,
 15.00000;11.15412;11.46461;,
 15.00000;15.00000;15.00000;,
 15.00000;11.15412;-11.46463;,
 15.00000;15.00000;-15.00000;,
 -15.00000;-15.00000;15.00000;,
 -15.00000;-11.15413;11.46461;,
 -15.00000;-11.15413;-11.46463;,
 -15.00000;-15.00000;-15.00000;,
 -15.00000;11.15412;-11.46463;,
 -15.00000;15.00000;-15.00000;,
 -15.00000;11.15412;11.46461;,
 -15.00000;15.00000;15.00000;,
 14.18701;-11.15413;11.46461;,
 14.18700;-11.15413;8.81537;,
 14.18701;-11.15413;-11.46463;,
 14.18701;-8.22327;11.46461;,
 14.18701;11.15412;11.46461;,
 14.18701;11.15412;-11.46463;,
 14.18701;11.15412;-9.61404;,
 14.18701;7.97410;-11.46463;,
 -14.18701;-11.15413;-11.46463;,
 -14.18700;-11.15413;8.81537;,
 -14.18701;-11.15413;11.46461;,
 -14.18701;7.97410;-11.46463;,
 -14.18701;11.15412;-11.46463;,
 -11.59792;-11.13428;-15.00000;,
 0.00000;-15.00000;-15.00000;,
 11.59792;-11.13428;-15.00000;,
 11.59792;11.13428;-15.00000;,
 -11.59792;11.13428;-15.00000;,
 0.00000;15.00000;-15.00000;,
 -15.00000;15.00000;15.00000;,
 -11.59792;11.13428;15.00000;,
 0.00000;15.00000;15.00000;,
 11.59792;11.13428;15.00000;,
 15.00000;15.00000;15.00000;,
 11.59792;-11.13428;15.00000;,
 -11.59792;-11.13428;15.00000;,
 -11.59792;-11.13428;-14.15004;,
 -7.89459;-11.13428;-14.15004;,
 11.59792;-11.13428;-14.15004;,
 11.59792;7.15914;-14.15004;,
 11.59792;11.13428;-14.15004;,
 -11.59792;-8.85629;-14.15004;,
 -11.59792;11.13428;-14.15004;,
 0.00000;11.13428;-14.15004;,
 9.52232;11.13428;-14.15004;,
 11.59792;11.13428;14.15004;,
 11.59792;7.15914;14.15004;,
 11.59792;-11.13428;14.15004;,
 -11.59792;-11.13428;14.15004;,
 -7.89459;-11.13428;14.15004;,
 -11.37142;15.00000;-11.56755;,
 11.37142;15.00000;-11.56755;,
 -11.37142;15.00000;11.56755;,
 11.37142;15.00000;11.56755;,
 -11.37142;14.26892;-11.56755;,
 7.22654;14.26892;-11.56755;,
 11.37142;14.26892;-11.56755;,
 -11.37142;14.26892;11.56755;,
 -11.37142;14.26892;7.71843;,
 -11.59792;-11.13428;14.61748;,
 -7.89459;-11.13428;14.61748;,
 -11.59792;-8.85629;14.61748;,
 9.52232;11.13428;14.61748;,
 11.59792;7.15914;14.61748;,
 11.59792;11.13428;14.61748;,
 -14.55134;7.97410;-11.46463;,
 -14.55134;-11.15413;8.81537;,
 -14.55134;11.15412;-11.46463;,
 -14.55134;11.15412;-9.61404;,
 -14.55134;-8.22327;11.46461;,
 -14.55134;-11.15413;11.46461;,
 -11.37142;14.66751;11.56755;,
 -8.77383;14.66751;11.56755;,
 -11.37142;14.66751;7.71843;,
 7.22654;14.66751;-11.56755;,
 11.37142;14.66751;-8.54639;,
 11.37142;14.66751;-11.56755;;
 
 158;
 3;0,1,2;,
 3;2,1,3;,
 3;3,1,4;,
 3;4,1,5;,
 3;6,7,8;,
 4;9,10,11,12;,
 3;13,14,15;,
 3;15,14,16;,
 3;16,14,17;,
 3;17,14,18;,
 3;19,20,21;,
 3;21,20,22;,
 3;20,23,22;,
 3;22,23,24;,
 3;25,26,27;,
 4;28,29,30,31;,
 4;30,32,33,31;,
 4;33,32,34,35;,
 4;29,28,35,34;,
 4;36,37,38,39;,
 4;38,40,41,39;,
 4;41,40,42,43;,
 4;37,36,43,42;,
 3;44,30,45;,
 3;45,30,46;,
 3;46,30,29;,
 3;44,47,30;,
 3;48,32,47;,
 3;47,32,30;,
 3;49,34,50;,
 3;50,34,48;,
 3;48,34,32;,
 3;46,29,51;,
 3;51,29,49;,
 3;49,29,34;,
 3;38,37,52;,
 3;52,37,53;,
 3;53,37,54;,
 3;38,52,40;,
 3;40,55,56;,
 3;55,40,52;,
 3;40,56,42;,
 3;42,27,26;,
 3;27,42,56;,
 3;42,26,37;,
 3;37,25,54;,
 3;25,37,26;,
 3;39,57,58;,
 3;57,59,58;,
 3;58,59,28;,
 4;59,60,35,28;,
 4;57,39,41,61;,
 3;41,62,61;,
 3;61,62,60;,
 3;60,62,35;,
 3;63,64,65;,
 3;64,66,65;,
 3;65,66,67;,
 4;66,68,17,67;,
 4;64,63,15,69;,
 3;15,16,69;,
 3;69,16,68;,
 3;68,16,17;,
 3;70,71,57;,
 3;57,71,59;,
 3;59,71,72;,
 3;59,72,60;,
 3;60,73,74;,
 3;73,60,72;,
 3;70,57,75;,
 3;75,57,76;,
 3;76,57,61;,
 3;61,60,76;,
 3;76,60,77;,
 3;77,60,78;,
 3;78,60,74;,
 3;11,10,64;,
 3;64,10,66;,
 3;10,9,66;,
 3;66,9,79;,
 3;79,80,66;,
 3;81,68,80;,
 3;80,68,66;,
 3;69,82,64;,
 3;64,12,11;,
 3;12,64,82;,
 3;82,69,83;,
 3;69,68,83;,
 3;83,68,81;,
 3;41,84,62;,
 3;84,85,62;,
 3;62,85,35;,
 4;63,86,84,41;,
 4;35,85,87,67;,
 3;63,65,86;,
 3;86,65,87;,
 3;87,65,67;,
 3;88,89,84;,
 3;84,89,85;,
 3;85,89,90;,
 3;86,91,84;,
 3;91,92,84;,
 3;84,92,88;,
 3;85,90,87;,
 3;90,8,87;,
 3;87,8,7;,
 3;91,86,6;,
 3;86,87,6;,
 3;6,87,7;,
 4;77,78,75,76;,
 3;83,81,80;,
 3;73,72,71;,
 3;93,94,95;,
 3;95,94,96;,
 3;94,97,96;,
 3;96,97,98;,
 4;78,1,0,75;,
 4;75,0,2,70;,
 4;70,2,3,71;,
 4;71,3,4,73;,
 4;73,4,5,74;,
 4;74,5,1,78;,
 4;82,93,95,12;,
 4;12,95,96,9;,
 4;9,96,98,79;,
 4;79,98,97,80;,
 4;80,97,94,83;,
 4;83,94,93,82;,
 3;52,53,55;,
 3;50,48,47;,
 3;99,100,101;,
 3;101,100,102;,
 3;102,100,103;,
 3;103,100,104;,
 3;46,51,45;,
 4;51,23,20,45;,
 4;45,20,19,44;,
 4;44,19,21,47;,
 4;47,21,22,50;,
 4;50,22,24,49;,
 4;49,24,23,51;,
 4;53,100,99,55;,
 4;55,99,101,56;,
 4;56,101,102,27;,
 4;27,102,103,25;,
 4;25,103,104,54;,
 4;54,104,100,53;,
 3;89,88,92;,
 3;105,106,107;,
 3;107,106,108;,
 3;106,109,108;,
 3;108,109,110;,
 4;91,105,107,92;,
 4;92,107,108,89;,
 4;89,108,110,90;,
 4;90,110,109,8;,
 4;8,109,106,6;,
 4;6,106,105,91;;
 
 MeshMaterialList {
  1;
  158;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.467451;0.316863;0.119216;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  33;
  0.000000;-1.000000;-0.000000;,
  0.000000;-1.000000;-0.000000;,
  -1.000000;0.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;0.000000;1.000000;,
  0.000000;1.000000;0.000000;,
  0.000001;1.000000;-0.000000;,
  -0.000001;1.000000;-0.000000;,
  0.000000;1.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  -0.000001;1.000000;0.000000;,
  0.000001;1.000000;0.000000;,
  0.000000;1.000000;0.000000;,
  -0.000000;1.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  1.000000;0.000000;-0.000000;,
  -1.000000;0.000000;0.000000;,
  -0.369957;0.929049;0.000000;,
  -0.918536;0.395337;0.000000;,
  0.367982;-0.929833;-0.000000;,
  0.917694;-0.397289;-0.000000;,
  -1.000000;0.000000;0.000000;,
  1.000000;0.000000;0.000000;,
  0.000000;-0.396139;-0.918190;,
  0.000000;-0.929371;-0.369146;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.402012;0.915635;,
  0.000000;0.931717;0.363186;,
  -0.927316;0.000000;-0.374279;,
  -0.391056;0.000000;-0.920367;,
  0.923731;0.000000;0.383043;,
  0.382324;0.000000;0.924028;;
  158;
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;10,10,10;,
  4;5,5,5,5;,
  3;0,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;2,2,2;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;4,4,4,4;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  4;2,2,2,2;,
  3;6,13,12;,
  3;12,13,7;,
  3;7,13,10;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,0;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;10,14,8;,
  3;8,14,11;,
  3;11,14,6;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;0,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  4;3,3,3,3;,
  4;3,3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  4;5,5,5,5;,
  4;5,5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,10;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;15,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,0;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,1;,
  3;1,1,0;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;4,4,4;,
  3;4,4,4;,
  3;4,4,4;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,10;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  4;9,9,9,9;,
  4;9,9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;15,4,4;,
  3;4,4,4;,
  3;4,4,16;,
  3;17,2,2;,
  3;2,2,2;,
  3;2,2,17;,
  3;3,3,3;,
  3;3,3,3;,
  3;3,3,3;,
  4;3,3,3,3;,
  3;5,5,5;,
  3;3,3,3;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  3;5,5,5;,
  4;18,18,19,19;,
  4;19,19,2,2;,
  4;1,1,20,20;,
  4;20,20,21,21;,
  4;21,21,4,4;,
  4;9,9,18,18;,
  4;2,2,19,19;,
  4;19,19,18,18;,
  4;18,18,9,9;,
  4;4,4,21,21;,
  4;21,21,20,20;,
  4;20,20,1,1;,
  3;22,22,22;,
  3;4,4,4;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;2,2,2;,
  3;23,23,23;,
  4;24,24,25,25;,
  4;25,25,26,26;,
  4;5,5,27,27;,
  4;27,27,28,28;,
  4;28,28,9,9;,
  4;3,3,24,24;,
  4;25,25,24,24;,
  4;24,24,3,3;,
  4;9,9,28,28;,
  4;28,28,27,27;,
  4;27,27,5,5;,
  4;26,26,25,25;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  4;2,2,29,29;,
  4;29,29,30,30;,
  4;30,30,3,3;,
  4;4,4,31,31;,
  4;31,31,32,32;,
  4;32,32,5,5;;
 }
 MeshTextureCoords {
  111;
  0.375000;0.974426;,
  0.602630;0.750000;,
  0.375000;1.000000;,
  0.414914;1.000000;,
  0.625000;0.794627;,
  0.625000;0.750000;,
  0.403554;0.500000;,
  0.625000;0.500000;,
  0.625000;0.717353;,
  0.602630;0.500000;,
  0.500000;0.500000;,
  0.375000;0.500000;,
  0.375000;0.275574;,
  0.375000;0.000000;,
  0.500000;0.000000;,
  0.375000;0.250000;,
  0.500000;0.250000;,
  0.625000;0.250000;,
  0.625000;0.000000;,
  0.875000;1.000000;,
  0.846115;1.000000;,
  0.875000;0.967155;,
  0.645177;0.750000;,
  0.625000;0.785637;,
  0.625000;0.750000;,
  0.125000;0.967155;,
  0.125000;0.750000;,
  0.354823;0.750000;,
  0.625000;1.000000;,
  0.625000;1.000000;,
  0.875000;1.000000;,
  0.875000;1.000000;,
  0.875000;0.750000;,
  0.875000;0.750000;,
  0.625000;0.750000;,
  0.625000;0.750000;,
  0.125000;1.000000;,
  0.125000;1.000000;,
  0.375000;1.000000;,
  0.375000;1.000000;,
  0.375000;0.750000;,
  0.375000;0.750000;,
  0.125000;0.750000;,
  0.125000;0.750000;,
  0.875000;1.000000;,
  0.846115;1.000000;,
  0.625000;1.000000;,
  0.875000;0.967155;,
  0.875000;0.750000;,
  0.625000;0.750000;,
  0.645177;0.750000;,
  0.625000;0.785637;,
  0.375000;1.000000;,
  0.153885;1.000000;,
  0.125000;1.000000;,
  0.375000;0.785637;,
  0.375000;0.750000;,
  0.375000;1.000000;,
  0.500000;1.000000;,
  0.625000;1.000000;,
  0.625000;0.750000;,
  0.375000;0.750000;,
  0.500000;0.750000;,
  0.375000;0.500000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.625000;0.500000;,
  0.625000;0.250000;,
  0.375000;0.250000;,
  0.375000;1.000000;,
  0.414914;1.000000;,
  0.625000;1.000000;,
  0.625000;0.794627;,
  0.625000;0.750000;,
  0.375000;0.974426;,
  0.375000;0.750000;,
  0.500000;0.750000;,
  0.602630;0.750000;,
  0.625000;0.500000;,
  0.625000;0.455373;,
  0.625000;0.250000;,
  0.375000;0.250000;,
  0.414914;0.250000;,
  0.375000;0.750000;,
  0.625000;0.750000;,
  0.375000;0.500000;,
  0.625000;0.500000;,
  0.375000;0.750000;,
  0.579437;0.750000;,
  0.625000;0.750000;,
  0.375000;0.500000;,
  0.375000;0.541594;,
  0.375000;0.250000;,
  0.414914;0.250000;,
  0.375000;0.275574;,
  0.602630;0.500000;,
  0.625000;0.455373;,
  0.625000;0.500000;,
  0.375000;0.785637;,
  0.153885;1.000000;,
  0.375000;0.750000;,
  0.354823;0.750000;,
  0.125000;0.967155;,
  0.125000;1.000000;,
  0.375000;0.500000;,
  0.403554;0.500000;,
  0.375000;0.541594;,
  0.579437;0.750000;,
  0.625000;0.717353;,
  0.625000;0.750000;;
 }
}
