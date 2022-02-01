#ifndef loc_funcs__h
#define loc_funcs__h

#include <array>
#include "TH1D.h"
#include "TH2D.h"

using namespace std;

#define PI           3.141592653589793116
#define TWO_PI       6.283185307179586232
#define PI_MINUS_ONE 2.141592653589793116
#define PI0MASS2     0.0182196

int eta_binner(const float& eta); 
int i_eta_binner(const float& eta); 
float dphi(float A, float B); 
float abs_dphi(float A, float B); 
bool is_phi_tran(float trigger, float obj);

#endif
