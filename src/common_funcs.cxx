#include "TMath.h"
#include "TRandom3.h"
#include "common_funcs.h"
#include <iostream>
#include "TH1F.h"
#include "TFile.h"
#include <vector>

using namespace std;
TRandom3 ran_gen;
double param_2D[8];
//vector<double> vz_par_;
//vector<double> zdc_par_;
double vz_range[2]={-30,30};
double zdc_range[2]={0,20000};
//double vz_norm=0;
//double zdc_norm=10300;
//vector<double> vz_par_zr={300.3, 0.03587, -0.0005492, 0.0002321, 
//			5.868e-06,-2.919e-07, -6.337e-09};
//vector<double> vz_par_ru={302.0, 0.02703, -0.00178, 0.0002438, 
//			1.185e-05,-3.312e-07, -1.227e-08}; 
//vector<double> zdc_par_zr={98.412, -1.3917e-04};
//vector<double> zdc_par_ru={98.113, -1.162e-05};

//vector<double> weight_par={1.34842, -12.8629, 0.767038, 4.2547, -0.00264771,
//			  357.779, 5.10897e-06}; 

TH1F* trk_eff_lumi[4];
TH1F* trk_eff_all;
//int lumi_edge[5]={0,8000,15000,23000,50000};

void rand_seed(){
  ran_gen.SetSeed(0);
}
void load_param_2D(char* filename,double* container){
  FILE* fp=fopen(filename,"r");
  char string[100];
  fgets(string,100,fp); 
  for(int i=0;i<8;i++){
    fscanf(fp,"%le\n",&container[i]);
    param_2D[i]=container[i];
    cout<<"Parameter number "<<i<<" is "<<container[i]<<endl;
  }
};

void load_param_2D(char* filename){
  FILE* fp=fopen(filename,"r");
  char string[100];
  fgets(string,100,fp); 
  for(int i=0;i<8;i++){
    fscanf(fp,"%le\n",&param_2D[i]);
    cout<<"Parameter number "<<i<<" is "<<param_2D[i]<<endl;
  }
};

Double_t factor_2D(double zdcx,double vz,Double_t *par=param_2D){
//First number means order in zdcx (0,1), second means order in vz (0-3)
  double buf_factor=0;
  for(int p_vz=0;p_vz<4;p_vz++){
    buf_factor+=par[p_vz*2]*std::pow(vz,1.0*p_vz);
    buf_factor+=par[p_vz*2+1]*std::pow(vz,1.0*p_vz)*zdcx;
  }
  return buf_factor/par[0];
};


Double_t factor_2D(double zdcx,double vz){
//First number means order in zdcx (0,1), second means order in vz (0-3)
  double buf_factor=0;
  for(int p_vz=0;p_vz<4;p_vz++){
    buf_factor+=param_2D[p_vz*2]*std::pow(vz,1.0*p_vz);
    buf_factor+=param_2D[p_vz*2+1]*std::pow(vz,1.0*p_vz)*zdcx;
  }
  return buf_factor/param_2D[0];
};

void load_efficiency(const char* eff_name="/home/tl543/embed_tree/lumi_efficiency.root"){
    TFile* eff_file=new TFile(eff_name);
    for(int i=0;i<4;i++){
	trk_eff_lumi[i]=(TH1F*)eff_file->Get(Form("rebin_weight_reco_lumi_%i",i));	
    }
    trk_eff_all=(TH1F*)eff_file->Get("weight_reco_all");
}




int smear_to_int(double input){
  int base=(int)input;
  double diff=input-1.0*base;
  int chance=0;
  double dice=(double)ran_gen.Uniform(0,1);
  if(dice<diff)chance=1;
  else chance=0;
  return base+chance;
};
/*
double array_mean(int array[]){
    int size=sizeof(array)/sizeof(int);
    cout<<"array size "<<size<<endl;
    double sum=0;
    for(int i=0;i<size;i++){
	sum+=1.0*array[i];
    }
    sum/=(1.0*size);
    return sum;
}

double array_dev(int array[]){
    int size=sizeof(array)/sizeof(int);
    double mean=array_mean(array);
    double variance=0;
    for(int i=0;i<size;i++){
	double diff=array[i]-mean;
	variance+=diff*diff;
    }
    variance/=(1.0*size);
    return sqrt(variance);

};
*/

/*
double refmult_corr(int refmult,double zdcx,double vz){
  double zdc_standard = zdc_par_[0] + zdc_par_[1] * zdc_norm /1000.0;
  double zdc_scale = zdc_par_[0] + zdc_par_[1] * zdc / 1000.0;   

  double vz_standard = 0;
  double vz_scale = 0;

  for(int i=0;i<vz_par_.size();i++){
    vz_standard += vz_par_[i]*pow(vz_norm,i);
    vz_scale += vz_par_[i]*pow(vz,i); 
  }
  double zdc_correction=zdc_standard/zdc_scale;
  double vz_correction=1.0;
  if(vz_scale > 0 ) vz_correction = vz_standard / vz_scale ;
  
  double corrected = refmult * vz_correction * zdc_correction;
  return corrected;
}
*/
