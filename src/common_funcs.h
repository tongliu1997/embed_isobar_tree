#ifndef common_funcs__h
#define common_funcs__h
#include "TMath.h"
#include "TRandom3.h"
#include <iostream>
#include <vector>
#include "loc_funcs.h"
using namespace std;
//TRandom3 ran_gen;
//double param_2D[8];


const int pt_bin=600;
const double pt_min=0;
const double pt_max=30;

const int ntrk_bin=10;
const double ntrk_min=-0.5;
const double ntrk_max=9.5;

const int phi_bin=96;
const double phi_min=0;
const double phi_max=TWO_PI;

const vector<double> vz_bound={-35,-20,-5,10,25};
const vector<double> ea_bound={0,9, 12, 16, 21, 27, 35, 45, 56, 70, 86, 104, 126, 152, 181, 217, 259,10000};
const vector<double> lumi_bound={0,5000,10000,15000,20000};
const vector<double> eta_bound={-1,-0.5,0,0.5,1};

const int lumi_bins=lumi_bound.size()-1;
const int eta_bins=eta_bound.size()-1;
const int ea_bins=ea_bound.size()-1;
const int vz_bins=vz_bound.size()-1;



void ran_seed();
void load_param_2D(char* filename, double* container); 
void load_param_2D(char* filename); 
Double_t factor_2D(double zdcx,double vz,double* par);
Double_t factor_2D(double zdcx,double vz);
void load_efficiency(const char* eff_name);
int smear_to_int(double input);

double refmult_corr(int refmult, double zdcx, double vz);


template <typename T>
double array_mean(vector<T> &array){
    int size=array.size();
    double sum=0;
    
    for(int i=0;i<size;i++){
        sum+=1.0*array[i];
    }
    sum/=(1.0*size);
    return sum;
};

template <typename T>
double array_dev(vector<T> &array){
    int size=array.size();
    double mean=array_mean(array);
    double variance=0;
    for(int i=0;i<size;i++){
        double diff=array[i]-mean;
        variance+=diff*diff;
    }
    variance/=(1.0*size);
    return sqrt(variance);
};

int define_bin(double param,vector<double> bound);


#endif
