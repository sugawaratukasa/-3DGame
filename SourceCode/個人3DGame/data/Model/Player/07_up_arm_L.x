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
 24;
 -0.12583;-0.84283;1.44097;,
 -0.16174;0.70570;1.51560;,
 -1.13850;0.70262;1.46033;,
 -1.09425;-0.86172;1.15934;,
 -0.17864;1.64769;0.34044;,
 -1.08205;1.49372;0.35763;,
 -0.11329;-1.19603;-0.28197;,
 -0.92261;-1.34048;-0.19580;,
 -0.15615;0.61638;-1.08723;,
 -1.03692;0.72891;-0.97352;,
 -0.13404;-0.35135;-1.08891;,
 -0.99372;-0.50537;-0.96144;,
 -4.27306;0.47728;1.28376;,
 -4.24584;-0.54223;1.13621;,
 -4.26826;1.33627;0.40511;,
 -4.17577;-1.15796;-0.06740;,
 -4.23842;0.56886;-0.79194;,
 -4.21531;-0.20907;-0.87082;,
 -7.29224;-2.10367;0.05695;,
 -7.33549;0.03247;-1.82510;,
 -7.35929;0.92625;-1.53648;,
 -7.40205;2.19749;1.04130;,
 -7.36007;0.71872;2.78387;,
 -7.32511;-0.49837;2.62899;;
 
 18;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;6,0,3,7;,
 4;4,8,9,5;,
 4;8,10,11,9;,
 4;10,6,7,11;,
 4;3,2,12,13;,
 4;2,5,14,12;,
 4;7,3,13,15;,
 4;5,9,16,14;,
 4;9,11,17,16;,
 4;11,7,15,17;,
 4;17,15,18,19;,
 4;16,17,19,20;,
 4;14,16,20,21;,
 4;12,14,21,22;,
 4;13,12,22,23;,
 4;15,13,23,18;;
 
 MeshMaterialList {
  7;
  18;
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
  1;;
  Material {
   0.400000;0.400000;0.400000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.408000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.040000;0.112000;0.152000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.328000;0.056000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.760000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.760000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  31;
  -0.164949;-0.120346;0.978932;,
  -0.098438;0.179542;0.978813;,
  -0.100695;-0.453598;0.885499;,
  -0.077849;0.794353;0.602448;,
  -0.069530;0.780024;0.621875;,
  0.081534;-0.957252;0.277525;,
  0.007373;-0.942137;0.335147;,
  -0.115067;0.472304;-0.873893;,
  -0.087463;0.490334;-0.867135;,
  -0.058729;-0.371412;-0.926609;,
  -0.061501;-0.352394;-0.933829;,
  0.423075;0.325372;0.845660;,
  0.380019;-0.523181;0.762802;,
  0.187636;0.857123;-0.479722;,
  0.169178;-0.641259;-0.748442;,
  0.253901;0.579893;-0.774118;,
  0.248345;-0.242375;-0.937859;,
  0.096715;-0.891035;0.443513;,
  0.090894;-0.292367;-0.951977;,
  0.101300;0.552177;-0.827550;,
  0.139661;0.746898;0.650106;,
  0.202986;-0.142585;0.968745;,
  0.168369;-0.585095;0.793294;,
  -0.063860;0.836958;-0.543529;,
  -0.062207;0.844729;-0.531567;,
  0.029022;-0.681967;-0.730807;,
  -0.022450;-0.672852;-0.739436;,
  0.064056;0.861557;-0.503603;,
  0.048018;-0.656455;-0.752835;,
  0.334795;0.698174;0.632824;,
  0.257344;-0.836484;0.483806;;
  18;
  4;0,0,1,2;,
  4;3,3,4,3;,
  4;5,5,5,6;,
  4;23,7,8,24;,
  4;7,9,10,8;,
  4;9,25,26,10;,
  4;2,1,21,22;,
  4;1,4,20,20;,
  4;6,2,22,17;,
  4;24,8,19,27;,
  4;8,10,18,19;,
  4;10,26,28,18;,
  4;18,28,14,16;,
  4;19,18,16,15;,
  4;27,19,15,13;,
  4;20,20,29,11;,
  4;22,21,11,12;,
  4;17,22,12,30;;
 }
 MeshTextureCoords {
  24;
  0.125000;0.125000;,
  0.125000;0.250000;,
  0.125000;0.250000;,
  0.125000;0.125000;,
  0.250000;0.250000;,
  0.250000;0.250000;,
  0.250000;0.125000;,
  0.250000;0.125000;,
  0.375000;0.250000;,
  0.375000;0.250000;,
  0.375000;0.125000;,
  0.375000;0.125000;,
  0.125000;0.250000;,
  0.125000;0.125000;,
  0.250000;0.250000;,
  0.250000;0.125000;,
  0.375000;0.250000;,
  0.375000;0.125000;,
  0.250000;0.125000;,
  0.375000;0.125000;,
  0.375000;0.250000;,
  0.250000;0.250000;,
  0.125000;0.250000;,
  0.125000;0.125000;;
 }
}
