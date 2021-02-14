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
 52;
 3.43715;-0.64278;0.98589;,
 4.02469;-0.73487;0.11042;,
 4.27905;-0.21547;0.11322;,
 3.70355;-0.16443;1.08113;,
 3.34374;-0.47713;-0.99231;,
 3.63886;-0.05691;-0.89397;,
 1.83090;-0.46124;1.05210;,
 1.84192;-0.51045;0.17788;,
 2.55032;-0.54057;0.10722;,
 2.53134;-0.52406;1.09589;,
 1.98313;0.62078;0.17840;,
 2.03099;0.08630;1.13202;,
 2.79774;0.06194;1.19113;,
 2.72769;0.51922;0.22674;,
 1.23199;-0.18088;-0.65688;,
 2.44275;-0.30055;-0.92672;,
 1.45248;0.20196;-0.56400;,
 2.73786;0.19223;-0.82839;,
 0.13372;0.16021;0.78917;,
 0.12250;-0.27779;0.75286;,
 0.62828;-0.33210;0.75927;,
 0.69541;0.13833;0.80849;,
 0.11088;-0.73198;0.05019;,
 0.62336;-0.67910;0.08799;,
 0.02561;-0.07596;-0.45846;,
 0.24659;-0.06304;-0.41225;,
 0.03355;0.23419;-0.38111;,
 0.31746;0.22465;-0.47940;,
 0.14843;0.73487;0.32715;,
 0.69369;0.72511;0.08400;,
 2.26611;-0.20025;-1.59368;,
 2.33698;0.14992;-1.51173;,
 2.26001;0.12181;-1.18692;,
 2.31169;-0.23635;-1.26562;,
 0.38735;0.30875;-0.76559;,
 0.32959;-0.11506;-0.75597;,
 1.36834;0.31447;-0.82739;,
 1.27976;-0.23143;-0.81361;,
 0.91938;-0.05894;-1.39263;,
 0.99025;0.29123;-1.31068;,
 1.88209;0.24582;-1.68875;,
 1.81122;-0.10435;-1.77070;,
 1.35194;0.26854;-0.87906;,
 1.80512;0.24601;-1.25713;,
 1.40361;-0.17678;-0.97195;,
 1.85680;-0.19931;-1.35001;,
 3.57327;-0.73424;0.06752;,
 3.13319;-0.66949;1.05847;,
 3.39959;-0.08349;1.15370;,
 3.75185;0.29007;0.18704;,
 3.04150;-0.46063;-0.96871;,
 3.33661;0.03214;-0.87038;;
 
 48;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;6,7,8,9;,
 4;10,11,12,13;,
 4;11,6,9,12;,
 4;7,14,15,8;,
 4;14,16,17,15;,
 4;16,10,13,17;,
 4;18,19,20,21;,
 4;19,22,23,20;,
 4;22,24,25,23;,
 4;24,26,27,25;,
 4;26,28,29,27;,
 4;28,18,21,29;,
 4;21,20,6,11;,
 4;20,23,7,6;,
 4;23,25,14,7;,
 4;30,31,32,33;,
 4;27,29,10,16;,
 4;29,21,11,10;,
 4;25,27,34,35;,
 4;27,16,36,34;,
 4;16,14,37,36;,
 4;14,25,35,37;,
 4;38,39,40,41;,
 4;39,42,43,40;,
 4;42,44,45,43;,
 4;44,38,41,45;,
 4;41,40,31,30;,
 4;40,43,32,31;,
 4;43,45,33,32;,
 4;45,41,30,33;,
 4;35,34,39,38;,
 4;34,36,42,39;,
 4;36,37,44,42;,
 4;37,35,38,44;,
 4;9,8,46,47;,
 4;13,12,48,49;,
 4;12,9,47,48;,
 4;8,15,50,46;,
 4;15,17,51,50;,
 4;17,13,49,51;,
 4;49,48,3,2;,
 4;51,49,2,5;,
 4;50,51,5,4;,
 4;46,50,4,1;,
 4;47,46,1,0;,
 4;48,47,0,3;;
 
 MeshMaterialList {
  7;
  48;
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4;;
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
  70;
  -0.139039;-0.990158;0.015983;,
  -0.154815;-0.983144;-0.097261;,
  0.139549;0.988703;0.054700;,
  0.134493;0.890010;0.435653;,
  -0.168553;-0.963242;-0.209177;,
  0.013748;0.677819;-0.735100;,
  -0.032009;-0.537579;0.842606;,
  -0.027125;-0.864726;0.501512;,
  -0.200788;0.802425;-0.561960;,
  0.062286;0.335946;0.939819;,
  0.044974;-0.284441;-0.957638;,
  -0.153421;0.474591;-0.866732;,
  -0.046032;0.390677;0.919376;,
  -0.092346;-0.584900;0.805831;,
  -0.034760;-0.997040;0.068579;,
  0.012869;-0.492323;-0.870317;,
  -0.087476;0.605209;-0.791246;,
  -0.082458;0.806251;-0.585799;,
  0.003668;0.859553;0.511034;,
  -0.041612;-0.987790;0.150131;,
  -0.063459;-0.988221;-0.139253;,
  -0.088614;-0.971598;-0.219418;,
  -0.040578;0.730371;-0.681845;,
  0.022204;0.999659;0.013738;,
  -0.536531;0.241026;-0.808728;,
  0.027311;0.985026;-0.170230;,
  0.841392;-0.101891;0.530733;,
  0.011731;0.225601;-0.974149;,
  0.136720;0.989458;0.047763;,
  0.240881;-0.175625;0.954532;,
  0.998353;-0.037981;0.042993;,
  -0.858383;0.178127;-0.481093;,
  0.015318;0.999881;-0.001630;,
  0.975527;-0.197213;0.097229;,
  0.396192;-0.678328;0.618791;,
  0.454253;-0.819507;0.349374;,
  0.742639;-0.440417;0.504499;,
  0.504930;-0.380161;0.774934;,
  0.748505;-0.379579;-0.543746;,
  0.372341;0.829594;0.416096;,
  0.380184;0.923128;0.057398;,
  -0.024715;0.218060;-0.975622;,
  -0.126955;-0.970680;-0.204114;,
  -0.104500;-0.991541;-0.076978;,
  -0.080140;-0.995423;0.052074;,
  -0.158764;-0.091329;0.983083;,
  -0.028045;-0.145492;0.988962;,
  -0.182429;0.313234;-0.931989;,
  -0.098817;0.259910;-0.960563;,
  0.159156;-0.583048;-0.796696;,
  0.142275;0.697299;0.702518;,
  0.054465;0.768191;0.637900;,
  -0.961837;0.151279;-0.228000;,
  0.029957;0.940053;0.339709;,
  0.958331;-0.281167;-0.050469;,
  -0.093461;-0.974546;0.203777;,
  -0.073657;-0.996915;-0.027107;,
  -0.094739;-0.973573;-0.207799;,
  -0.116417;-0.980899;-0.155831;,
  0.384056;0.135998;-0.913239;,
  0.217401;0.972175;0.087253;,
  -0.201841;-0.230064;0.952014;,
  -0.093576;-0.983719;-0.153430;,
  0.110744;-0.220530;0.969073;,
  0.336026;0.890125;-0.307837;,
  0.509458;0.755643;0.411650;,
  0.517524;0.854091;0.051935;,
  0.453576;0.833691;-0.315006;,
  -0.035270;0.232232;-0.972021;,
  -0.024457;-0.972721;-0.230685;;
  48;
  4;34,35,36,37;,
  4;38,38,38,38;,
  4;19,20,1,0;,
  4;23,18,3,2;,
  4;45,45,46,46;,
  4;20,21,4,1;,
  4;47,22,5,48;,
  4;22,23,2,5;,
  4;9,6,13,12;,
  4;6,7,14,13;,
  4;49,10,15,49;,
  4;10,11,16,15;,
  4;11,8,17,16;,
  4;50,9,12,51;,
  4;12,13,45,45;,
  4;13,14,20,19;,
  4;14,15,21,20;,
  4;30,30,30,30;,
  4;16,17,23,22;,
  4;51,12,18,23;,
  4;52,52,31,31;,
  4;53,53,32,32;,
  4;54,54,33,33;,
  4;21,55,56,56;,
  4;24,24,27,27;,
  4;25,25,28,28;,
  4;26,26,29,29;,
  4;57,57,58,58;,
  4;27,27,59,59;,
  4;28,28,60,60;,
  4;29,29,61,61;,
  4;58,58,62,62;,
  4;31,31,24,24;,
  4;32,32,25,25;,
  4;33,33,26,26;,
  4;56,56,57,57;,
  4;0,1,43,44;,
  4;2,3,39,40;,
  4;46,46,63,63;,
  4;1,4,42,43;,
  4;48,5,41,41;,
  4;5,2,40,64;,
  4;40,39,65,66;,
  4;64,40,66,67;,
  4;41,41,68,68;,
  4;43,42,69,69;,
  4;44,43,35,34;,
  4;63,63,34,37;;
 }
 MeshTextureCoords {
  52;
  0.125000;0.125000;,
  0.250000;0.125000;,
  0.250000;0.250000;,
  0.125000;0.250000;,
  0.375000;0.125000;,
  0.375000;0.250000;,
  0.125000;0.125000;,
  0.250000;0.125000;,
  0.250000;0.125000;,
  0.125000;0.125000;,
  0.250000;0.250000;,
  0.125000;0.250000;,
  0.125000;0.250000;,
  0.250000;0.250000;,
  0.375000;0.125000;,
  0.375000;0.125000;,
  0.375000;0.250000;,
  0.375000;0.250000;,
  0.125000;0.250000;,
  0.125000;0.125000;,
  0.125000;0.125000;,
  0.125000;0.250000;,
  0.250000;0.125000;,
  0.250000;0.125000;,
  0.375000;0.125000;,
  0.375000;0.125000;,
  0.375000;0.250000;,
  0.375000;0.250000;,
  0.250000;0.250000;,
  0.250000;0.250000;,
  0.375000;0.125000;,
  0.375000;0.250000;,
  0.375000;0.250000;,
  0.375000;0.125000;,
  0.375000;0.250000;,
  0.375000;0.125000;,
  0.375000;0.250000;,
  0.375000;0.125000;,
  0.375000;0.125000;,
  0.375000;0.250000;,
  0.375000;0.250000;,
  0.375000;0.125000;,
  0.375000;0.250000;,
  0.375000;0.250000;,
  0.375000;0.125000;,
  0.375000;0.125000;,
  0.250000;0.125000;,
  0.125000;0.125000;,
  0.125000;0.250000;,
  0.250000;0.250000;,
  0.375000;0.125000;,
  0.375000;0.250000;;
 }
}
