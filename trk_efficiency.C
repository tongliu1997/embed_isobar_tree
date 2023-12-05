#include "../pp_reference/hist_pp.h"
#include "out_hist.h"
void trk_efficiency(
const char* ru_name="outhist_ru_2_3.root",
const char* zr_name="outhist_zr_2_3.root",

const char* ru_sys="systematics_ru_2_3.root",
const char* zr_sys="systematics_zr_2_3.root",
std::vector<int> bins={0,10,20,30,50,70}
){
const int ncent=bins.size()-1;
double bar_offset=0.07;
double marker_size=1.8;
double line_width=2;
out_hist* nominal[2];


nominal[0]=new out_hist(ru_name,bins,"ru","");
nominal[1]=new out_hist(zr_name,bins,"zr","");


out_hist* sys_plot[2];
sys_plot[0]=new out_hist(ru_sys,bins,"ru","_systematics");
sys_plot[1]=new out_hist(zr_sys,bins,"zr","_systematics");



TLatex prelim_tag;
double npart[2][ncent],npart_err[2][ncent],ncoll[2][ncent],ncoll_err[2][ncent];

for(int isys=0;isys<2;isys++){

    for(int i=0;i<ncent;i++){
	npart[isys][i]=nominal[isys]->npart(i); 
	npart_err[isys][i]=nominal[isys]->npart_err(i); 
	ncoll[isys][i]=nominal[isys]->ncoll(i); 
	ncoll_err[isys][i]=nominal[isys]->ncoll_err(i); 
	
    }
}
int colors[20]={418,879,600,1,632,3,9,20,30,40,810,397,434,844,618,624,797,38,46,43};
int markers[20]={20,21,22,47,29,33,34,37,39,43,45,46,23,48,49,33,34,2,3,5};
TH1D* pp_hist=hist_pp(true);
pp_hist->SetName("pp_hist_witherr");
TH1D* pp_hist_noerr=hist_pp(false);
pp_hist_noerr->SetName("pp_hist_noerr");

pp_hist->Scale(5./7.);
pp_hist_noerr->Scale(5./7.);

gStyle->SetPalette(kVisibleSpectrum);
gStyle->SetOptStat(0);
gStyle->SetErrorX(0);
//gStyle->SetOptTitle(0);

TCanvas* c[2];

c[0]=new TCanvas("c0","",1200,600);
c[0]->Divide(2,1,0.0);

//Raw
double raw_ymax[2];
double raw_ymin[2];
double rawmax,rawmin;
for(int isys=0;isys<2;isys++){
    raw_ymax[isys]=nominal[isys]->raw_spec[0]->GetBinContent(4)*5;
    raw_ymin[isys]=nominal[isys]->raw_spec[ncent-1]->GetBinContent(nbins)/pow(5,ncent-1)/2;
}
 
rawmax=raw_ymax[0]>raw_ymax[1]?raw_ymax[0]:raw_ymax[1];  
rawmin=raw_ymin[0]<raw_ymin[1]?raw_ymin[0]:raw_ymin[1];  
for(int isys=0;isys<2;isys++){
    string sys=isys?"zr":"ru";

    c[0]->cd(isys+1);
    if(isys==0){gPad->SetRightMargin(0.02); gPad->SetLeftMargin(0.15);}
    else{gPad->SetLeftMargin(0.02);gPad->SetRightMargin(0.15);}
    TLegend* lg=new TLegend(0.55,0.12,0.84,0.5);
    TH1D* raw_copy[ncent];
    for(int i=0;i<ncent;i++){
	for(int ibin=1;ibin<=nominal[isys]->unfold_spec[i]->GetNbinsX();ibin++)
	  nominal[isys]->unfold_spec[i]->SetBinError(ibin,0);
	raw_copy[i]=(TH1D*)nominal[isys]->raw_spec[i]->Clone();
	raw_copy[i]->Divide(nominal[isys]->unfold_spec[i]);
	double inv_yield=0;
	cout<<"Raw "<<sys<<"\t"<<(i?Form("%i%%-%i%%",bins[i],bins[i+1]):"0%-10%")<<"\t"<<inv_yield*2<<"\t"<<inv_yield/ncoll[isys][i]<<endl;
	const string sysname=isys?"Zr":"Ru";
    	raw_copy[i]->SetTitle(Form("%s + %s",sysname.c_str(),sysname.c_str()));
    	raw_copy[i]->GetXaxis()->SetRangeUser(0.1,9.9);
    	raw_copy[i]->GetYaxis()->SetRangeUser(0.75,0.99);
    	raw_copy[i]->SetXTitle("p_{T} (GeV/c)");
     	if(isys==0)raw_copy[i]->SetYTitle("Tracking Efficiency");
	else{
	    raw_copy[i]->GetYaxis()->SetLabelSize(0);
	    raw_copy[i]->GetYaxis()->SetLabelOffset(100);

	}
    	raw_copy[i]->SetLineWidth(line_width);
	raw_copy[i]->SetMarkerStyle(markers[i]);
	raw_copy[i]->SetMarkerSize(marker_size);
	raw_copy[i]->SetLineColor(colors[i]);
	raw_copy[i]->SetMarkerColor(colors[i]);
    	raw_copy[i]->Draw("same");
    	if(isys)lg->AddEntry(raw_copy[i],Form("%i%%-%i%%",bins[i],bins[i+1]));
    }
    if(isys){lg->SetBorderSize(0);lg->Draw();}
}


c[0]->SaveAs("isobar_eff.pdf");
//c[1]->SaveAs(Form("prelim_plots/Isobar_UnfoldSpec_%i.pdf",ncent));

}
