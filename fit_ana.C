#include "embed_species.h"
void fit_ana(){
TH1::SetDefaultSumw2(true);
TH2::SetDefaultSumw2(true);

const string filename="isobar_trk_eff_ptmix_blend.root";
const string key="blended";
species_plots species(filename,key,key,"pt");
const int stack_dim=1;
vector<int> stack_bin={1,5,9,13,15,17};


TH2F** devs=dev_stack(species,stack_dim,stack_bin);
TH1F* disect[5][10];
for(int i=0;i<5;i++){
    for(int j=0;j<10;j++){
        disect[i][j]=(TH1F*)devs[i]->ProjectionY(Form("dev_proj_%i_%i",i,j),40*j+1,40*(j+1),"");
	disect[i][j]->SetTitle(Form("dev_proj_%i_%i",i,j));
        disect[i][j]->GetXaxis()->SetRangeUser(-0.3,0.3);
    }
}

int nbins=species_plots::obs_bins;

TF1* g1[5][10]; 

TH1F* hist_dev[5];
TH1F* fit_dev[5];

TCanvas* c4=new TCanvas("c4","",1600,800);
//c4->Divide(5,2);
//c4->Draw();
int i=0;
    
    hist_dev[i]=new TH1F(Form("hist_dev_%i",i),"",10,0,20);
    fit_dev[i]=new TH1F(Form("fit_dev_%i",i),"",10,0.1,20.1);
    TProfile* dev_pf=devs[i]->Rebin(40)->ProfileX("",1,-1,"s");
    dev_pf->GetXaxis()->SetRangeUser(0,20);
    for(int j=0;j<10;j++){
//        g1[i][j]=new TF1(Form("fit_%i_%i",i,j),"exp(gaus(0)+[3])",-0.2,0.2);
//This function does fit high pt data better, but it's essentially not integratable. I'm giving up for now
//        double p0=log(disect[i][j]->GetBinContent(0.5*nbins)/disect[i][j]->GetBinContent(0.2*nbins));
//        g1[i][j]->SetParameter(0,p0);
//        g1[i][j]->SetParameter(1,disect[i][j]->GetMean());
//        g1[i][j]->SetParameter(2,disect[i][j]->GetStdDev());
//        g1[i][j]->SetParameter(3,log(disect[i][j]->GetBinContent(0.2*nbins)));
	g1[i][j]=new TF1(Form("Fit_%i_%i",i,j),"gaus",-0.1,0.1);

//	c4->cd(j+1);
//        disect[i][j]->Draw();
        g1[i][j]->SetNpx(0.6*nbins);
        disect[i][j]->Fit(g1[i][j],"R");

	double chisquare=g1[i][j]->GetChisquare();
	int ndf=g1[i][j]->GetNDF();
	const double* param=g1[i][j]->GetParameters();
	const double* error=g1[i][j]->GetParErrors();
	disect[i][j]->GetXaxis()->SetRangeUser(-0.5,0.5);
//	hist_dev[i]->SetBinContent(j+1,disect[i][j]->GetStdDev());
	hist_dev[i]->SetBinContent(j+1,dev_pf->GetBinError(j+1));
	fit_dev[i]->SetBinContent(j+1,param[2]);
	fit_dev[i]->SetBinError(j+1,error[2]);
        
	cout<<"Chisqure is "<<chisquare<<"/"<<ndf<<endl;
    }
    dev_pf->Draw();
    hist_dev[i]->Draw("Lsame");
    fit_dev[i]->SetLineColor(kRed);
    fit_dev[i]->Draw("Lsame");
}
