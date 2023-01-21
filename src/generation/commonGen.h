#pragma once
#include "common.h"

struct region{
  int x2;
  int y2;
  int x1;
  int y1;

  //apaño para compatibilidad
  int& operator[](int i){
    if(i==0) return x2;
    if(i==1) return y2;
    if(i==2) return x1;
    if(i==3) return y1;
    return x2;
  }
};