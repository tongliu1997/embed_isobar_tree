#include "TMath.h"
#include "loc_funcs.h"
#include "TH1D.h"
#include "TFile.h"
#include <iostream>

int eta_binner(const float &eta) {
    if (eta < -0.3) return 0;
    if (eta <  0.3) return 1;
    return 2;
};
int i_eta_binner(const float &eta) {
    if (eta < -0.3) return 0;
    if (eta <  0.3) return 1;
    return 2;
};
float abs_dphi(float A, float B) {
    return TMath::Abs(dphi(A,B));
}

float dphi(float A, const float B) {
    float delta { A - B };
    while (delta < -PI) delta += TWO_PI;
    while (delta >  PI) delta -= TWO_PI;
    return delta;
};

bool is_phi_tran(float trigger, float obj) {
    float delta { TMath::Abs(dphi(trigger, obj)) };
    return ( (delta >= 1.) && (delta <= PI_MINUS_ONE));
};

