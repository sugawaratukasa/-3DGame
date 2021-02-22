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
 134;
 -2.01362;-1.70542;0.58342;,
 -1.49837;-1.88369;-1.95415;,
 -1.19760;-4.65981;-1.26784;,
 -1.67838;-4.52867;1.22679;,
 0.33619;-1.89421;-2.63230;,
 0.45506;-4.66698;-1.90797;,
 2.17651;-1.79236;-1.28970;,
 2.48578;-1.65600;1.36903;,
 2.31868;-4.49120;1.73036;,
 2.07697;-4.59053;-0.77037;,
 -0.46914;-1.67016;2.26879;,
 -0.40250;-4.42730;2.50481;,
 1.29548;-1.66805;2.31269;,
 1.23094;-4.42539;2.51289;,
 1.43607;-7.35509;0.41533;,
 0.57360;-6.96163;-0.71906;,
 0.37832;-3.86871;-1.42293;,
 1.61188;-3.98443;-0.50208;,
 -1.52236;-1.78191;0.42804;,
 -1.52236;-2.05426;0.42804;,
 -1.11793;-2.09802;-1.64360;,
 -1.11793;-1.82567;-1.64360;,
 -1.11793;-1.82567;-1.64360;,
 -1.11793;-2.09802;-1.64360;,
 0.25945;-2.10041;-2.14726;,
 0.25945;-1.82806;-2.14726;,
 1.71141;-1.80398;-1.02142;,
 1.71141;-2.07633;-1.02142;,
 2.04214;-2.04257;1.15842;,
 2.04214;-1.77022;1.15842;,
 -0.26497;-1.84940;1.76737;,
 -0.26497;-2.26848;1.76737;,
 -1.52236;-2.05426;0.42804;,
 -1.52236;-1.78191;0.42804;,
 2.04214;-1.77022;1.15842;,
 2.04214;-2.04257;1.15842;,
 1.13928;-2.26803;1.76794;,
 1.13928;-1.84895;1.76794;,
 1.13928;-1.84895;1.76794;,
 1.13928;-2.26803;1.76794;,
 -0.26497;-2.26848;1.76737;,
 -0.26497;-1.84940;1.76737;,
 0.25945;-1.82806;-2.14726;,
 0.25945;-2.10041;-2.14726;,
 1.71141;-2.07633;-1.02142;,
 1.71141;-1.80398;-1.02142;,
 -0.81716;-3.98406;-0.95728;,
 -0.27764;-7.36724;0.27383;,
 -0.63185;-7.18949;2.13704;,
 -1.18712;-3.98745;1.07140;,
 1.87504;-3.98771;1.51974;,
 1.78181;-7.17714;1.91705;,
 -0.06994;-7.30336;2.45813;,
 -0.19834;-3.98882;2.00339;,
 1.07473;-3.98857;1.96814;,
 0.95052;-7.29942;2.35338;,
 -1.11793;-1.82567;-1.64360;,
 -1.52236;-1.78191;0.42804;,
 0.25945;-1.82806;-2.14726;,
 2.04214;-1.77022;1.15842;,
 1.71141;-1.80398;-1.02142;,
 -0.26497;-1.84940;1.76737;,
 1.13928;-1.84895;1.76794;,
 0.37832;-3.86871;-1.42293;,
 0.45506;-4.66698;-1.90797;,
 2.07697;-4.59053;-0.77037;,
 1.61188;-3.98443;-0.50208;,
 1.71141;-1.80398;-1.02142;,
 2.17651;-1.79236;-1.28970;,
 0.33619;-1.89421;-2.63230;,
 0.25945;-1.82806;-2.14726;,
 1.24176;-8.01400;1.41180;,
 0.78782;-8.08077;1.65007;,
 1.05297;-8.11118;0.59175;,
 0.58200;-7.89631;-0.02770;,
 0.23058;-8.08293;1.70727;,
 0.11716;-8.11781;0.51449;,
 -0.07626;-8.02074;1.53193;,
 -0.39247;-7.67349;1.87310;,
 0.06008;-7.76520;2.13171;,
 0.88194;-7.76203;2.04734;,
 1.55145;-7.66354;1.69593;,
 1.27300;-7.80687;0.48646;,
 0.57838;-7.48997;-0.42715;,
 -0.10719;-7.81665;0.37250;,
 -0.41943;-0.07601;2.58891;,
 -2.35774;-0.09475;0.12614;,
 -1.49876;-1.94605;0.93511;,
 -0.61982;-2.15905;1.58444;,
 0.64590;-0.05131;2.59797;,
 1.14525;-2.14819;1.64506;,
 1.98318;-0.04692;0.04465;,
 2.00378;-1.92207;0.91579;,
 1.04206;-0.07342;-1.67909;,
 1.56151;-2.11567;-1.07589;,
 -1.16153;-0.11177;-1.86732;,
 0.06702;-0.09986;-2.85055;,
 0.22373;-2.14691;-2.03273;,
 -0.96495;-2.14529;-1.68243;,
 0.27548;1.37131;-0.09811;,
 0.06637;1.36542;-0.48111;,
 -0.02165;1.37033;0.46921;,
 -0.15027;1.35955;-0.74139;,
 -0.25836;1.36484;0.46720;,
 -0.42324;1.35690;-0.52293;,
 -0.68903;1.36068;-0.08001;,
 -2.24080;0.21094;0.10999;,
 -1.11131;0.19486;-1.77228;,
 0.04872;0.20611;-2.70067;,
 0.96938;0.23107;-1.59455;,
 1.85800;0.25609;0.03305;,
 0.59531;0.25195;2.44395;,
 -0.41059;0.22862;2.43540;,
 -2.06325;0.50524;0.08689;,
 -1.03379;0.49059;-1.62868;,
 0.02350;0.50084;-2.47484;,
 0.86262;0.52359;-1.46668;,
 1.67254;0.54640;0.01676;,
 0.52168;0.54262;2.21414;,
 -0.39514;0.52136;2.20635;,
 -1.84547;0.79987;0.05911;,
 -0.93822;0.78696;-1.45280;,
 -0.00644;0.79599;-2.19851;,
 0.73306;0.81605;-1.31003;,
 1.44684;0.83614;-0.00269;,
 0.43260;0.83282;1.93383;,
 -0.37538;0.81408;1.92696;,
 -1.62733;1.06172;0.03156;,
 -0.84224;1.05055;-1.27677;,
 -0.03593;1.05837;-1.92207;,
 0.60401;1.07572;-1.15323;,
 1.22167;1.09311;-0.02192;,
 0.34400;1.09023;1.65386;,
 -0.35519;1.07401;1.64791;;
 
 101;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;6,7,8,9;,
 4;10,0,3,11;,
 4;7,12,13,8;,
 4;12,10,11,13;,
 4;14,15,16,17;,
 4;18,19,20,21;,
 4;22,23,24,25;,
 4;26,27,28,29;,
 4;30,31,32,33;,
 4;34,35,36,37;,
 4;38,39,40,41;,
 4;42,43,44,45;,
 4;46,47,48,49;,
 4;16,15,47,46;,
 4;50,51,14,17;,
 4;49,48,52,53;,
 4;54,55,51,50;,
 4;53,52,55,54;,
 4;5,4,6,9;,
 4;49,3,2,46;,
 4;56,1,0,57;,
 4;46,2,5,16;,
 4;58,4,1,56;,
 4;17,9,8,50;,
 4;59,7,6,60;,
 4;53,11,3,49;,
 4;57,0,10,61;,
 4;50,8,13,54;,
 4;62,12,7,59;,
 4;54,13,11,53;,
 4;61,10,12,62;,
 4;63,64,65,66;,
 4;67,68,69,70;,
 3;71,72,73;,
 3;73,72,74;,
 3;72,75,74;,
 3;74,75,76;,
 3;75,77,76;,
 4;48,78,79,52;,
 4;52,79,80,55;,
 4;55,80,81,51;,
 4;51,81,82,14;,
 4;14,82,83,15;,
 4;15,83,84,47;,
 4;47,84,78,48;,
 4;78,77,75,79;,
 4;79,75,72,80;,
 4;80,72,71,81;,
 4;81,71,73,82;,
 4;82,73,74,83;,
 4;83,74,76,84;,
 4;84,76,77,78;,
 4;85,86,87,88;,
 4;89,85,88,90;,
 4;91,89,90,92;,
 4;93,91,92,94;,
 4;95,96,97,98;,
 4;86,95,98,87;,
 4;94,97,96,93;,
 3;99,100,101;,
 3;100,102,101;,
 3;101,102,103;,
 3;102,104,103;,
 3;104,105,103;,
 4;86,106,107,95;,
 4;95,107,108,96;,
 4;96,108,109,93;,
 4;93,109,110,91;,
 4;91,110,111,89;,
 4;89,111,112,85;,
 4;85,112,106,86;,
 4;106,113,114,107;,
 4;107,114,115,108;,
 4;108,115,116,109;,
 4;109,116,117,110;,
 4;110,117,118,111;,
 4;111,118,119,112;,
 4;112,119,113,106;,
 4;113,120,121,114;,
 4;114,121,122,115;,
 4;115,122,123,116;,
 4;116,123,124,117;,
 4;117,124,125,118;,
 4;118,125,126,119;,
 4;119,126,120,113;,
 4;120,127,128,121;,
 4;121,128,129,122;,
 4;122,129,130,123;,
 4;123,130,131,124;,
 4;124,131,132,125;,
 4;125,132,133,126;,
 4;126,133,127,120;,
 4;127,105,104,128;,
 4;128,104,102,129;,
 4;129,102,100,130;,
 4;130,100,99,131;,
 4;131,99,101,132;,
 4;132,101,103,133;,
 4;133,103,105,127;;
 
 MeshMaterialList {
  7;
  101;
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2;;
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
  124;
  0.960910;0.000000;-0.276862;,
  -0.941681;-0.299254;-0.153893;,
  -0.803276;-0.343391;-0.486653;,
  0.760628;0.000000;0.649188;,
  0.678517;-0.265036;-0.685106;,
  -0.153885;0.000000;0.988089;,
  -0.862349;0.000000;0.506314;,
  0.856840;-0.252174;-0.449705;,
  0.960710;-0.216976;-0.173086;,
  -0.988685;0.000000;0.150006;,
  0.397394;0.000000;-0.917648;,
  -0.262264;-0.259464;0.929460;,
  0.291965;-0.239187;0.926038;,
  -0.292373;0.000000;-0.956304;,
  -0.961079;-0.218824;-0.168649;,
  -0.794493;-0.281185;-0.538252;,
  0.666774;-0.179825;-0.723240;,
  0.870773;-0.132537;-0.473485;,
  0.982271;-0.071169;-0.173433;,
  -0.276160;0.127230;0.952653;,
  0.273150;0.111012;0.955545;,
  -0.956624;-0.055975;0.285898;,
  -0.749453;-0.233577;-0.619485;,
  0.133049;-0.243664;-0.960690;,
  0.860483;-0.130640;-0.492445;,
  0.917105;-0.005257;0.398612;,
  -0.399852;0.072201;0.913731;,
  0.310662;0.070186;0.947926;,
  -0.714399;-0.659275;0.234500;,
  -0.196430;-0.721718;0.663731;,
  0.254857;-0.680267;0.687230;,
  0.591896;-0.694622;0.408851;,
  0.766972;-0.500766;-0.401233;,
  0.613096;-0.475334;-0.631008;,
  -0.734837;-0.537488;-0.413669;,
  -0.503416;-0.852474;0.140925;,
  -0.035021;-0.976218;0.213946;,
  0.060931;-0.972017;0.226869;,
  0.491910;-0.852669;0.176014;,
  0.339130;-0.917662;-0.207093;,
  0.034472;-0.942918;-0.331236;,
  -0.305491;-0.929965;-0.204550;,
  -0.751894;0.062387;0.656326;,
  -0.748402;0.020017;-0.662943;,
  -0.542683;0.048912;-0.838512;,
  0.820950;0.134887;-0.554839;,
  0.976643;0.203422;0.069199;,
  -0.435184;0.042228;0.899351;,
  0.483749;0.123794;0.866408;,
  -0.704822;-0.196108;0.681739;,
  -0.711502;-0.287766;-0.641059;,
  -0.444133;-0.231970;-0.865411;,
  0.830384;-0.074876;-0.552137;,
  0.988529;0.012557;0.150506;,
  -0.388272;-0.336964;0.857730;,
  0.444419;-0.229940;0.865806;,
  -0.695806;0.386170;-0.605580;,
  -0.798748;0.359602;-0.482377;,
  -0.574368;0.402517;-0.712798;,
  0.751487;0.408742;-0.517877;,
  0.886791;0.461943;-0.014514;,
  0.439049;0.548048;0.711955;,
  -0.403564;0.502598;0.764546;,
  -0.655123;0.497177;-0.568884;,
  -0.818756;0.554380;-0.149338;,
  -0.538435;0.515584;-0.666529;,
  0.702700;0.519152;-0.486513;,
  0.816920;0.576516;-0.016481;,
  0.397619;0.664578;0.632642;,
  -0.376281;0.619083;0.689310;,
  -0.627155;0.557636;-0.543800;,
  -0.784015;0.619533;0.038706;,
  -0.514004;0.576399;-0.635266;,
  0.669672;0.579039;-0.465030;,
  0.771251;0.636291;-0.017482;,
  0.371845;0.720706;0.585076;,
  -0.358156;0.676978;0.642982;,
  -0.461361;0.792686;-0.398491;,
  -0.544274;0.838646;0.020933;,
  -0.175570;0.900032;-0.398896;,
  0.480499;0.808154;-0.340600;,
  0.531386;0.846952;-0.017366;,
  0.246114;0.889580;0.384805;,
  -0.257011;0.863140;0.434666;,
  -0.139911;0.982805;-0.120495;,
  -0.202511;0.979280;0.000444;,
  -0.007588;0.994807;-0.101498;,
  0.125081;0.986799;-0.102869;,
  0.184519;0.982747;-0.012721;,
  0.037692;0.996635;0.072781;,
  -0.067924;0.993961;0.086184;,
  -0.559532;0.000000;-0.828809;,
  -0.494237;-0.296237;-0.817296;,
  -0.558519;-0.342220;-0.755607;,
  -0.584051;0.112673;0.803859;,
  -0.575105;-0.257017;0.776657;,
  0.487656;-0.236632;0.840355;,
  0.469888;0.090131;0.878113;,
  0.697854;-0.694090;-0.176747;,
  0.612962;-0.589403;0.526196;,
  -0.004323;0.996093;-0.088200;,
  0.119505;0.987136;-0.106213;,
  -0.089920;-0.575514;0.812833;,
  -0.018970;0.994845;-0.099616;,
  -0.666706;-0.623703;0.408040;,
  -0.625808;-0.736948;-0.255485;,
  -0.170311;0.978458;-0.116680;,
  -0.063758;0.997199;-0.039093;,
  0.259391;-0.765642;-0.588649;,
  0.102268;0.962682;-0.250569;,
  -0.200246;-0.761164;-0.616872;,
  -0.100234;0.957078;-0.271947;,
  0.918277;-0.358069;-0.168979;,
  -0.536366;-0.513649;-0.669684;,
  -0.899337;-0.010509;-0.437129;,
  -0.889980;-0.307611;-0.336617;,
  0.674926;-0.142899;-0.723916;,
  0.719741;0.101733;-0.686748;,
  0.694283;0.416046;-0.587262;,
  -0.724547;0.391447;0.567275;,
  0.647002;0.527653;-0.550427;,
  -0.697872;0.463847;0.545729;,
  0.615239;0.587784;-0.525348;,
  0.602101;0.610191;-0.514919;;
  101;
  4;21,22,22,21;,
  4;22,23,23,22;,
  4;24,25,25,24;,
  4;26,21,21,26;,
  4;25,27,27,25;,
  4;27,26,26,27;,
  4;7,4,16,17;,
  4;0,0,3,3;,
  4;3,3,5,5;,
  4;6,6,9,9;,
  4;10,10,0,0;,
  4;91,91,13,13;,
  4;13,13,10,10;,
  4;5,5,6,6;,
  4;15,2,1,14;,
  4;92,93,2,15;,
  4;18,8,7,17;,
  4;94,95,11,19;,
  4;20,12,96,97;,
  4;19,11,12,20;,
  4;23,23,24,24;,
  4;98,98,99,99;,
  4;100,100,101,101;,
  4;99,99,102,102;,
  4;103,103,100,100;,
  4;104,104,105,105;,
  4;106,106,107,107;,
  4;108,108,98,98;,
  4;101,101,109,109;,
  4;105,105,110,110;,
  4;111,111,106,106;,
  4;110,110,108,108;,
  4;109,109,111,111;,
  4;102,102,104,104;,
  4;107,107,103,103;,
  3;38,37,39;,
  3;39,37,40;,
  3;37,36,40;,
  3;40,36,41;,
  3;36,35,41;,
  4;95,28,29,11;,
  4;11,29,30,12;,
  4;12,30,31,96;,
  4;8,112,32,7;,
  4;7,32,33,4;,
  4;93,113,34,2;,
  4;2,34,28,1;,
  4;28,35,36,29;,
  4;29,36,37,30;,
  4;30,37,38,31;,
  4;31,38,39,32;,
  4;32,39,40,33;,
  4;113,40,41,34;,
  4;34,41,35,28;,
  4;47,42,49,54;,
  4;48,47,54,55;,
  4;46,48,55,53;,
  4;45,46,53,52;,
  4;43,44,51,50;,
  4;114,43,50,115;,
  4;52,116,117,45;,
  3;88,87,89;,
  3;87,86,89;,
  3;89,86,90;,
  3;86,84,90;,
  3;84,85,90;,
  4;114,57,56,43;,
  4;43,56,58,44;,
  4;117,118,59,45;,
  4;45,59,60,46;,
  4;46,60,61,48;,
  4;48,61,62,47;,
  4;47,62,119,42;,
  4;57,64,63,56;,
  4;56,63,65,58;,
  4;118,120,66,59;,
  4;59,66,67,60;,
  4;60,67,68,61;,
  4;61,68,69,62;,
  4;62,69,121,119;,
  4;64,71,70,63;,
  4;63,70,72,65;,
  4;120,122,73,66;,
  4;66,73,74,67;,
  4;67,74,75,68;,
  4;68,75,76,69;,
  4;69,76,71,64;,
  4;71,78,77,70;,
  4;70,77,79,72;,
  4;122,123,80,73;,
  4;73,80,81,74;,
  4;74,81,82,75;,
  4;75,82,83,76;,
  4;76,83,78,71;,
  4;78,85,84,77;,
  4;77,84,86,79;,
  4;79,86,87,80;,
  4;80,87,88,81;,
  4;81,88,89,82;,
  4;82,89,90,83;,
  4;83,90,85,78;;
 }
 MeshTextureCoords {
  134;
  0.463115;0.875000;,
  0.375000;1.000000;,
  0.375000;1.000000;,
  0.463115;0.875000;,
  0.375000;0.968750;,
  0.375000;0.968750;,
  0.375000;0.937500;,
  0.375000;0.875000;,
  0.375000;0.875000;,
  0.375000;0.937500;,
  0.375000;0.750000;,
  0.375000;0.750000;,
  0.375000;0.812500;,
  0.375000;0.812500;,
  0.375000;0.937500;,
  0.375000;0.968750;,
  0.375000;0.968750;,
  0.375000;0.937500;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  1.000000;1.000000;,
  1.000000;0.000000;,
  0.375000;1.000000;,
  0.375000;1.000000;,
  0.463115;0.875000;,
  0.463115;0.875000;,
  0.375000;0.875000;,
  0.375000;0.875000;,
  0.375000;0.750000;,
  0.375000;0.750000;,
  0.375000;0.812500;,
  0.375000;0.812500;,
  0.375000;1.000000;,
  0.463115;0.875000;,
  0.375000;0.968750;,
  0.375000;0.875000;,
  0.375000;0.937500;,
  0.375000;0.750000;,
  0.375000;0.812500;,
  0.463115;0.875000;,
  0.463115;0.875000;,
  0.375000;1.000000;,
  0.375000;1.000000;,
  0.375000;1.000000;,
  0.375000;1.000000;,
  0.463115;0.875000;,
  0.463115;0.875000;,
  0.375000;0.875000;,
  0.375000;0.812500;,
  0.375000;0.937500;,
  0.375000;0.968750;,
  0.375000;0.750000;,
  0.375000;1.000000;,
  0.463115;0.875000;,
  0.463115;0.875000;,
  0.375000;0.750000;,
  0.375000;0.812500;,
  0.375000;0.875000;,
  0.375000;0.937500;,
  0.375000;0.968750;,
  0.375000;1.000000;,
  0.375000;0.750000;,
  0.463115;0.875000;,
  0.463115;0.875000;,
  0.375000;0.750000;,
  0.375000;0.812500;,
  0.375000;0.812500;,
  0.375000;0.875000;,
  0.375000;0.875000;,
  0.375000;0.937500;,
  0.375000;0.937500;,
  0.375000;1.000000;,
  0.375000;0.968750;,
  0.375000;0.968750;,
  0.375000;1.000000;,
  0.375000;0.875000;,
  0.375000;0.937500;,
  0.375000;0.812500;,
  0.375000;0.968750;,
  0.375000;0.750000;,
  0.375000;1.000000;,
  0.463115;0.875000;,
  0.463115;0.875000;,
  0.375000;1.000000;,
  0.375000;0.968750;,
  0.375000;0.937500;,
  0.375000;0.875000;,
  0.375000;0.812500;,
  0.375000;0.750000;,
  0.463115;0.875000;,
  0.375000;1.000000;,
  0.375000;0.968750;,
  0.375000;0.937500;,
  0.375000;0.875000;,
  0.375000;0.812500;,
  0.375000;0.750000;,
  0.463115;0.875000;,
  0.375000;1.000000;,
  0.375000;0.968750;,
  0.375000;0.937500;,
  0.375000;0.875000;,
  0.375000;0.812500;,
  0.375000;0.750000;,
  0.463115;0.875000;,
  0.375000;1.000000;,
  0.375000;0.968750;,
  0.375000;0.937500;,
  0.375000;0.875000;,
  0.375000;0.812500;,
  0.375000;0.750000;;
 }
}
