#include "unfold_funcs.h"
#include "../isobar_hist_process/isobar_hist.h"
void get_raw_spec(
const string system="zr",
float eta_start=-1,
float eta_end=1,
std::vector<int> cent_in={0,10,20,30,40,50,60,70,80}
)
{
int iszr=0;
if(system=="zr")iszr=1;
const char* data_name=(iszr)?"/gpfs/gibbs/project/caines/tl543/Isobar_Hist/zr_hadd.root":
"/gpfs/gibbs/project/caines/tl543/Isobar_Hist/ru_hadd.root";


int etabin_start=2*eta_start+3;
int etabin_end=2*eta_end+2;
TH1::SetDefaultSumw2(true);
TH2::SetDefaultSumw2(true);

std::vector<int> centrality;
std::vector<int> embed_stack_bin;//Centrality bins used for embbedding data extraction
std::vector<int> data_stack_bin;//Centrality bins used for real data extraction

int nstack=cent_in.size()-1;
for(int i=0;i<=nstack;i++){
    centrality.push_back(cent_in[nstack-i]);
    embed_stack_bin.push_back(17-cent_in[nstack-i]/5);
    data_stack_bin.push_back(cent_in[i]/5);
}


for(int i=0;i<data_stack_bin.size();i++)cout<<data_stack_bin[i]<<endl;

isobar_hist tester(data_name);
TH1D** hpt_diff=tester.stack(data_stack_bin,0,0); 
for(int i=0;i<nstack;i++){
  cout<<tester.nev_cent(cent_in[i],cent_in[i+1])<<endl;
  int ib=1,start,end;
  while(hpt_diff[i]->GetBinCenter(ib)<5.1)ib++;
  start=ib;
  while(hpt_diff[i]->GetBinCenter(ib)<10)ib++;
  end=ib-1;
  double err;
  double integral=hpt_diff[i]->IntegralAndError(start,end,err);
  cout<<integral<<"\t"<<err<<endl;
  double int_ex=0,err_ex=0;
  for(ib=start;ib<=hpt_diff[i]->GetNbinsX();ib++){
    double weight=1/(TMath::Pi()*2*hpt_diff[i]->GetBinCenter(ib));
    if(i==0)cout<<ib<<"\t"<<hpt_diff[i]->GetBinCenter(ib)<<"\t"<<hpt_diff[i]->GetBinContent(ib)<<"\t"<<pow(hpt_diff[i]->GetBinError(ib),2)*2<<"\t"<<hpt_diff[i]->GetBinContent(ib)/weight<<endl;

    int_ex+=hpt_diff[i]->GetBinContent(ib);
    err_ex+=pow(hpt_diff[i]->GetBinError(ib),2);
  }
//  err_ex=TMath::Sqrt(err_ex);
//  cout<<int_ex<<"\t"<<err_ex<<endl;
}
hpt_diff[nstack-1]->Draw();


}
