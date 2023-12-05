#include "../pp_reference/hist_pp.h"
#include "out_hist.h"
void outhist_previous(
){
double bar_offset=0.07;
double marker_size=1.8;
double line_width=2;


TLatex prelim_tag;

int colors[20]={1,879,600,418,632,3,9,20,30,40,810,397,434,844,618,624,797,38,46,43};
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

double pp_buff=0,pp_err_buff=0;
for(int i=1;i<=nbins;i++){
    if(pp_hist->GetBinCenter(i)<5.1 || pp_hist->GetBinCenter(i)>10)continue;
     pp_buff+=(pp_hist->GetBinContent(i)*pp_hist->GetBinWidth(i));	    
     pp_err_buff+=pow(pp_hist->GetBinError(i)*pp_hist->GetBinWidth(i),2);	    
}

cout<<"pp fractional error: "<<sqrt(pp_err_buff)/pp_buff<<endl;
pp_err_buff=sqrt(pp_err_buff)/pp_buff;


TH1D** auau_hist=hist_auau();

double auau_mod_5GeV[7],auau_err_5GeV[7];
for(int i=0;i<7;i++){
    if(i==1)continue;
    double raa_buff=0,err_buff=0;	
    for(int j=1;j<=nbins;j++){
	if(auau_hist[i]->GetBinCenter(j)<5.1 || auau_hist[i]->GetBinCenter(j)>10)continue;
	
	raa_buff+=auau_hist[i]->GetBinContent(j)*auau_hist[i]->GetBinWidth(j);
	err_buff+=pow(auau_hist[i]->GetBinError(j)*auau_hist[i]->GetBinWidth(j),2);
    }
	
    raa_buff/=aa_nbin[i];
    err_buff/=pow(aa_nbin[i],2);
    int raabin=(i>1)?i-1:i;
    auau_mod_5GeV[raabin]=raa_buff/pp_buff;
    auau_err_5GeV[raabin]=sqrt(err_buff)/raa_buff;
    auau_err_5GeV[raabin]*=auau_mod_5GeV[raabin];
}


TGraphErrors* mod_auau=new TGraphErrors(6,auau_npart,auau_mod_5GeV,auau_npart_err,auau_err_5GeV);
cout<<"Au+Au plot created."<<endl;

TH1D** dau_hist=hist_dau();

double dau_mod_5GeV[2],dau_err_5GeV[2];
for(int i=0;i<2;i++){
    double raa_buff=0,err_buff=0;	
    for(int j=1;j<=nbins;j++){
	if(dau_hist[i]->GetBinCenter(j)<5.1 || dau_hist[i]->GetBinCenter(j)>10)continue;

	raa_buff+=dau_hist[i]->GetBinContent(j)*dau_hist[i]->GetBinWidth(j);
	err_buff+=pow(dau_hist[i]->GetBinError(j)*dau_hist[i]->GetBinWidth(j),2);
    }
	
    raa_buff/=dau_nbin[i];
    err_buff/=pow(dau_nbin[i],2);
    dau_mod_5GeV[i]=raa_buff/pp_buff;
    dau_err_5GeV[i]=sqrt(err_buff)/raa_buff;
//   dau_err_5GeV[i]=sqrt(err_buff/(raa_buff*raa_buff)+pp_err_buff*pp_err_buff); 
    dau_err_5GeV[i]*=dau_mod_5GeV[i];
}

TGraphErrors* mod_dau=new TGraphErrors(2,dau_npart,dau_mod_5GeV,dau_npart_err,dau_err_5GeV);

cout<<"d+Au plot created."<<endl;

TCanvas* compile_raa=new TCanvas("compile_raa","",1000,760);
compile_raa->SetLogx();
compile_raa->Draw();
compile_raa->cd();
compile_raa->SetTopMargin(0.02);
compile_raa->SetRightMargin(0.02);
double compile_xmin=5;
double compile_xmax=375;
TH1D* compile_dummy=new TH1D("comp_dummy","",200,compile_xmin,compile_xmax);
compile_dummy->GetXaxis()->SetRangeUser(compile_xmin,compile_xmax);
compile_dummy->GetYaxis()->SetRangeUser(0,2);
compile_dummy->SetXTitle("#LT N_{part} #GT");
compile_dummy->GetXaxis()->SetTitleSize(0.06);
compile_dummy->GetXaxis()->SetLabelSize(0.04);
compile_dummy->GetXaxis()->SetTitleOffset(0.6);
//compile_dummy->SetTitle("Hadron R_{AA} for p_{T} > 5 GeV");
compile_dummy->SetYTitle("R_{AA}");
compile_dummy->GetYaxis()->SetLabelSize(0.04);
compile_dummy->GetYaxis()->SetTitleSize(0.06);
compile_dummy->GetYaxis()->SetTitleOffset(0.65);
compile_dummy->DrawClone();
delete compile_dummy;
prelim_tag.SetTextAlign(23);
prelim_tag.SetTextSize(0.04);
prelim_tag.SetNDC();
prelim_tag.DrawLatex(0.32,0.25,"STAR #bf{#sqrt{s_{NN}}=200 GeV}");
prelim_tag.DrawLatex(0.32,0.19,"#bf{(h^{+}+h^{-})/2  p_{T} > 5.1 GeV/#it{c}}");
pp_err_buff=sqrt(pp_err_buff*pp_err_buff+3.5*3.5/900);
TBox* pp_errbox=new TBox(compile_xmax-20,1-pp_err_buff,compile_xmax,1+pp_err_buff);
pp_errbox->SetFillColor(15);
pp_errbox->SetLineColor(15);
pp_errbox->Draw("same");

TGraphErrors* pion_cucu=cucu_pion();

float width=2;
mod_auau->SetLineColor(12);
mod_auau->SetMarkerColor(12);
mod_auau->SetMarkerSize(1.5);
mod_auau->SetLineWidth(width);
mod_auau->GetXaxis()->SetTitle("#langle N_{part} #rangle");
mod_auau->GetYaxis()->SetTitle("R_{AA}");
mod_auau->SetTitle("Inclusive hadron R_{AA} for p_{T} > 5 GeV");
mod_auau->SetMarkerStyle(32);


pion_cucu->SetLineColor(kMagenta+3);
pion_cucu->SetMarkerStyle(27);
pion_cucu->SetMarkerColor(kMagenta+3);
pion_cucu->SetMarkerSize(1.5);
pion_cucu->SetLineWidth(width);

mod_dau->SetLineColor(kOrange+4);
mod_dau->SetMarkerColor(kOrange+4);
mod_dau->SetLineWidth(width);
mod_dau->SetMarkerStyle(25);
mod_dau->SetMarkerSize(1.5);

mod_auau->SetLineWidth(width);
pion_cucu->SetLineWidth(width);

TLegend* lg_compile=new TLegend(0.16,0.74,0.42,0.91);
lg_compile->AddEntry(pp_errbox,"pp uncertainty","f");
lg_compile->SetBorderSize(0);
lg_compile->Draw();

TLine* l=new TLine(compile_xmin,1,compile_xmax,1);
l->SetLineStyle(8);
l->Draw("same");

prelim_tag.DrawLatex(0.32,0.95,"#bf{Data}");

TLegend* lg_compare=new TLegend(0.42,0.70,0.66,0.91);
lg_compare->AddEntry(mod_auau,"Au+Au");
lg_compare->AddEntry(mod_dau,"d+Au");
lg_compare->AddEntry(pion_cucu,"Cu+Cu #frac{#pi^{+}+#pi^{-}}{2}");

lg_compare->SetBorderSize(0);
lg_compare->Draw();


mod_auau->Draw("samep");
mod_dau->Draw("samep");
pion_cucu->Draw("samep");
compile_raa->SaveAs("prelim_plots/raa_summary_previous.pdf");

//*/
}
