#ifndef common_funcs__h
#define common_funcs__h
#include "TMath.h"
#include "TRandom3.h"
#include <iostream>
#include <vector>
using namespace std;
//TRandom3 ran_gen;
//double param_2D[8];
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

#endif
