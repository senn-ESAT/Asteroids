#include <stdio.h>
#include <math.h>

namespace mm {
  // vertor o punto
  struct Vec2 {
    float x, y;
  };

  struct Vec3 {
    float x, y, z;
  };

  struct Vec4 {
    float x, y, z, w;
  };

  struct Mat2 {
    /*
      m = 0 2
          1 3
    */
    float m[4];
  };
  
  struct Mat3 {
    /*
      m = 0 3 6
          1 4 7
          2 5 8
    */
    float m[9];
  };
  
  struct Mat4 {
    /*
      m = 0 4 8  12
          1 5 9  13
          2 6 10 14
          3 7 11 15
    */
    float m[16];
  };
  
  /*
  TO_DO
--- Vect
  Suma de vectores    v
  Resta de vectores   v
  Multiplicación por un escalar   v 
  División por un escalar   v
  hipotenusa    v
  Algún método de “print”   v
  Normalizar un vector    v
  ¿Está normalizado?    v
  Perpendicular 2D método 1 ???
  Perpendicular 2D método 2 ???
  */
  
  // ---------- VECTOR ----------

  // - SUM -

  Vec2 sumVec2(Vec2 v1, Vec2 v2){
    Vec2 temp = {{v1.x + v2.x}, {v1.y + v2.y}};
    return temp;
  }

  Vec3 sumVec3(Vec3 v1, Vec3 v2){
    Vec3 temp = {{v1.x + v2.x}, {v1.y + v2.y}, {v1.z + v2.z}};
    return temp;
  }

  Vec4 sumVec4(Vec4 v1, Vec4 v2){
    Vec4 temp = {{v1.x + v2.x}, {v1.y + v2.y}, {v1.z + v2.z}, {v1.w + v2.w}};
    return temp;
  }

  // - SUB -

  Vec2 subVec2(Vec2 v1, Vec2 v2){
    Vec2 temp = {{v1.x - v2.x}, {v1.y - v2.y}};
    return temp;
  }

  Vec3 subVec3(Vec3 v1, Vec3 v2){
    Vec3 temp = {{v1.x - v2.x}, {v1.y - v2.y}, {v1.z - v2.z}};
    return temp;
  }

  Vec4 subVec4(Vec4 v1, Vec4 v2){
    Vec4 temp = {{v1.x - v2.x}, {v1.y - v2.y}, {v1.z - v2.z}, {v1.w - v2.w}};
    return temp;
  }

  // - MULT - 

  Vec2 scaleV2(Vec2 v1, float n){
    Vec2 temp = {{v1.x * n}, {v1.y *n}};
    return temp;
  }

  Vec3 scaleV3(Vec3 v1, float n){
    Vec3 temp = {{v1.x * n}, {v1.y * n}, {v1.z * n}};
    return temp;
  }

  Vec4 scaleV4(Vec4 v1, float n){
    Vec4 temp = {{v1.x * n}, {v1.y * n}, {v1.z * n}, {v1.w * n}};
    return temp;
  }

  // - HIPOTENUSA

  float magnitudeV2(Vec2 v1){
    float temp;
    temp = sqrtf(v1.x*v1.x + v1.y*v1.y);
    return temp;
  }

  float magnitudeV3(Vec3 v1){
    float temp;
    temp = sqrtf(v1.x*v1.x + v1.y*v1.y + v1.z*v1.z);
    return temp;
  }

  float magnitudeV4(Vec4 v1){
    float temp;
    temp = sqrtf(v1.x*v1.x + v1.y*v1.y + v1.z*v1.z + v1.w*v1.w);
    return temp;
  }

  // - NORM -

  Vec2 normalize(Vec2 v1){
    Vec2 temp;
    temp = {v1.x/magnitudeV2(v1), v1.y/magnitudeV2(v1)};
    return temp;
  }

  bool isVec2Normalized (Vec2 v){
    if(magnitudeV2(v) > 0.95f && magnitudeV2(v) < 1.05f){
      return true;
    }
    return false;
  }

  bool isVec3Normalized (Vec3 v){
    if(magnitudeV3(v) > 0.95f && magnitudeV3(v) < 1.05f){
      return true;
    }
    return false;
  }

  bool isVec4Normalized (Vec4 v){
    if(magnitudeV4(v) > 0.95f && magnitudeV4(v) < 1.05f){
      return true;
    }
    return false;
  }

  // - Perpendicular 2D -
  
  Vec2 perp2D1(Vec2 v){
    Vec2 temp = {{-v.y}, {v.x}};
    return temp;
  }

  Vec2 perp2D2(Vec2 v){
    Vec2 temp = {{v.y}, {-v.x}};
    return temp;
  }

  // - PRINT -

  void Vec2Print(Vec2 v) {
    printf("[X]: %f [Y]: %f\n", v.x, v.y);
  }

  void Vec3Print(Vec3 v) {
    printf("[X]: %f [Y]: %f [Z]: %f\n", v.x, v.y, v.z);
  }

  void Vec4Print(Vec4 v) {
    printf("[X]: %f [Y]: %f [Z]: %f [W]: %f\n", v.x, v.y, v.z, v.w);
  }

  /*
  --- Mat
  Suma de matrices  v
  Resta de matrices   v
  Multiplicación por un escalar   v
  División por un escalar   v
  Multiplicación de matrices 
  Vector por matriz
  Algún método de “print” 
  Iniciar como identidad
  ¿Otro método de inicialización?
  */

  // ---------- MAT ----------

  // - SUM - 
  
  Mat2 sumMat2(Mat2 m1, Mat2 m2){
    Mat2 temp;
    for(int i = 0; i < 4; i++){
      temp.m[i] = m1.m[i]+m2.m[i];
    }
    return temp;
  }

  Mat3 sumMat3(Mat3 m1, Mat3 m2){
    Mat3 temp;
    for(int i = 0; i < 9; i++){
      temp.m[i] = m1.m[i]+m2.m[i];
    }
    return temp;
  }

  Mat4 sumMat4(Mat4 m1, Mat4 m2){
    Mat4 temp;
    for(int i = 0; i < 16; i++){
      temp.m[i] = m1.m[i]+m2.m[i];
    }
    return temp;
  }

  // - SUB - 

  Mat2 subMat2(Mat2 m1, Mat2 m2){
    Mat2 temp;
    for(int i = 0; i < 4; i++){
      temp.m[i] = m1.m[i]-m2.m[i];
    }
    return temp;
  }

  Mat3 subMat3(Mat3 m1, Mat3 m2){
    Mat3 temp;
    for(int i = 0; i < 9; i++){
      temp.m[i] = m1.m[i]-m2.m[i];
    }
    return temp;
  }

  Mat4 subMat4(Mat4 m1, Mat4 m2){
    Mat4 temp;
    for(int i = 0; i < 16; i++){
      temp.m[i] = m1.m[i]-m2.m[i];
    }
    return temp;
  }

  // - MAT x NUM -

  Mat2 scaleM2(Mat2 m1, float n){
    Mat2 temp;
    for(int i = 0; i < 4; i++){
      temp.m[i] = m1.m[i]*n;
    }
    return temp;
  }
    
  Mat3 scaleM3(Mat3 m1, float n){
    Mat3 temp;
    for(int i = 0; i < 9; i++){
      temp.m[i] = m1.m[i]*n;
    }
    return temp;
  }  
  
  Mat4 scaleM4(Mat4 m1, float n){
    Mat4 temp;
    for(int i = 0; i < 16; i++){
      temp.m[i] = m1.m[i]*n;
    }
    return temp;
  }

  // - MAT / NUM - 

  Mat2 divM2(Mat2 m1, float n){
    Mat2 temp;
    for(int i = 0; i < 4; i++){
      temp.m[i] = m1.m[i]/n;
    }
    return temp;
  }
    
  Mat3 divM3(Mat3 m1, float n){
    Mat3 temp;
    for(int i = 0; i < 9; i++){
      temp.m[i] = m1.m[i]/n;
    }
    return temp;
  }  
  
  Mat4 divM4(Mat4 m1, float n){
    Mat4 temp;
    for(int i = 0; i < 16; i++){
      temp.m[i] = m1.m[i]/n;
    }
    return temp;
  }

  // - MAT x MAT -

  // Mat2 Mat2multiplication(Mat2 m1, Mat2 m2){
  // Mat2 temp;

  //   //???????????????????

  // }





  // // ---------- COMBO ----------

  // Vec2 Vec2MultMat2Vec2(Mat2 mat, Vec2 vec) {
  //   Vec2 tmp = {
  //     mat.m[0] * vec.x + mat.m[2] * vec.y,
  //     mat.m[1] * vec.x + mat.m[3] * vec.y
  //   };
  //   return tmp;
  // };
  
}