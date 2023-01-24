#include "../pp_reference/hist_pp.h"
#include "out_hist.h"
void outhist_hgpythia(
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

double raa_5GeV[2][ncent],raa_err_5GeV[2][ncent],raa_sys_5GeV[2][ncent],npart_width[2][ncent];
double raa_xbins[4]={0,5.1,10,30};
double pp_buff=0,pp_err_buff=0;
for(int i=1;i<=nbins;i++){
    if(pp_hist->GetBinCenter(i)<5.1 || pp_hist->GetBinCenter(i)>10)continue;
//    cout<<pp_hist->GetBinCenter(i)<<endl;
     pp_buff+=(pp_hist->GetBinContent(i)*pp_hist->GetBinWidth(i));	    
     pp_err_buff+=pow(pp_hist->GetBinError(i)*pp_hist->GetBinWidth(i),2);	    

}

cout<<"pp fractional error: "<<sqrt(pp_err_buff)/pp_buff<<endl;
pp_err_buff=sqrt(pp_err_buff)/pp_buff;


TGraphErrors* integrated_raa[2];
TGraphErrors* sys_err_raa[2];

for(int isys=0;isys<2;isys++){
   for(int i=0;i<ncent;i++){
	double isobar_buff=0,isobar_err_buff=0,isobar_sys_buff=0;	
	for(int j=1;j<=nbins;j++){
	    if(nominal[isys]->unfold_spec[i]->GetBinCenter(j)<5.1 || nominal[isys]->unfold_spec[i]->GetBinCenter(j)>10)continue;
	    isobar_buff+=nominal[isys]->unfold_spec[i]->GetBinContent(j)*nominal[isys]->unfold_spec[i]->GetBinWidth(j);
	    isobar_err_buff+=pow(nominal[isys]->unfold_spec[i]->GetBinError(j)*nominal[isys]->unfold_spec[i]->GetBinWidth(j),2);	    

//	    cout<<"test "<<sys_plot[isys]->unfold_spec[i]->GetBinError(j)/sys_plot[isys]->unfold_spec[i]->GetBinContent(j)<<endl;
	    isobar_sys_buff+=sys_plot[isys]->unfold_spec[i]->GetBinError(j)*sys_plot[isys]->unfold_spec[i]->GetBinWidth(j);
	}
	isobar_sys_buff/=isobar_buff;
 	cout<<"test "<<isobar_sys_buff<<endl;
	isobar_buff/=ncoll[isys][i];
	isobar_sys_buff=sqrt(pow(isobar_sys_buff,2)+pow(nominal[isys]->nbin_err(i)/nominal[isys]->nbin(i),2));
	isobar_sys_buff*=isobar_buff/pp_buff;
	isobar_err_buff/=pow(ncoll[isys][i],2);
	raa_5GeV[isys][i]=isobar_buff/pp_buff;
	raa_sys_5GeV[isys][i]=isobar_sys_buff;
	cout<<(isys?"zr\t":"ru\t")<<ncoll[isys][i]<<"\t"<<npart[isys][i]<<"\t"<<raa_5GeV[isys][i]<<"\t"<<raa_sys_5GeV[isys][i]/raa_5GeV[isys][i]<<"\t"<<nominal[isys]->nbin_err(i)/nominal[isys]->nbin(i)<<endl;


//	raa_err_5GeV[isys][i]=sqrt(isobar_err_buff/(isobar_buff*isobar_buff)+pp_err_buff*pp_err_buff);
	raa_err_5GeV[isys][i]=sqrt(isobar_err_buff)/isobar_buff;
	raa_err_5GeV[isys][i]*=raa_5GeV[isys][i];
	
	npart_width[isys][i]=0.03*npart[isys][i];
    }

    integrated_raa[isys]=new TGraphErrors(ncent,npart[isys],raa_5GeV[isys],npart_err[isys],raa_err_5GeV[isys]);
    sys_err_raa[isys]=new TGraphErrors(ncent,npart[isys],raa_5GeV[isys],npart_width[isys],raa_sys_5GeV[isys]);
}

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
//    auau_err_5GeV[raabin]=sqrt(err_buff/(raa_buff*raa_buff)+pp_err_buff*pp_err_buff);
    auau_err_5GeV[raabin]=sqrt(err_buff)/raa_buff;
    auau_err_5GeV[raabin]*=auau_mod_5GeV[raabin];
//    cout<<raabin<<"\t"<<auau_npart[raabin]<<"\t"<<auau_npart_err[raabin]<<"\t"<<auau_mod_5GeV[raabin]<<"\t"<<auau_err_5GeV[raabin]<<endl;
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

TH1D* plot_displace=(TH1D*)nominal[0]->unfold_spec[0]->Clone();
for(int i=1;i<=plot_displace->GetNbinsX();i++){
    plot_displace->SetBinContent(i,-0.2);
    plot_displace->SetBinError(i,0);
}


TCanvas* compile_raa=new TCanvas("compile_raa","",1000,760);
compile_raa->SetLogx();
compile_raa->Draw();
compile_raa->cd();
compile_raa->SetTopMargin(0.02);
compile_raa->SetRightMargin(0.02);
double compile_xmin=6;
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
prelim_tag.DrawLatex(0.45,0.24,"STAR #bf{#it{Preliminary}}");
prelim_tag.DrawLatex(0.45,0.20,"#bf{#sqrt{s_{NN}}=200 GeV}");
prelim_tag.DrawLatex(0.45,0.15,"#bf{(h^{+}+h^{-})/2  p_{T} > 5.1 GeV/#it{c}}");
pp_err_buff=sqrt(pp_err_buff*pp_err_buff+3.5*3.5/900);
TBox* pp_errbox=new TBox(compile_xmax-20,1-pp_err_buff,compile_xmax,1+pp_err_buff);
pp_errbox->SetFillColor(15);
pp_errbox->SetLineColor(15);
pp_errbox->Draw("same");

TGraphErrors* pion_cucu=cucu_pion();

float width=2;
mod_auau->SetLineColor(12);
mod_auau->SetMarkerColor(12);
mod_auau->SetMarkerSize(2);
mod_auau->SetLineWidth(width);
mod_auau->GetXaxis()->SetTitle("#langle N_{part} #rangle");
mod_auau->GetYaxis()->SetTitle("R_{AA}");
mod_auau->SetTitle("Inclusive hadron R_{AA} for p_{T} > 5 GeV");
mod_auau->SetMarkerStyle(32);
integrated_raa[0]->SetLineColor(kBlue);//Ru
integrated_raa[1]->SetLineColor(kRed);//Zr
integrated_raa[0]->SetMarkerStyle(21);
integrated_raa[1]->SetMarkerStyle(20);
integrated_raa[0]->SetMarkerColor(kBlue);
integrated_raa[1]->SetMarkerColor(kRed);

sys_err_raa[0]->SetLineColor(kBlue);
sys_err_raa[1]->SetLineColor(kRed);
sys_err_raa[0]->SetMarkerSize(0);
sys_err_raa[1]->SetMarkerSize(0);
sys_err_raa[0]->SetLineWidth(1);
sys_err_raa[1]->SetLineWidth(1);
sys_err_raa[0]->SetFillColorAlpha(0,0);
sys_err_raa[1]->SetFillColorAlpha(0,0);


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
integrated_raa[0]->SetLineWidth(width+1);
integrated_raa[1]->SetLineWidth(width+1);
integrated_raa[0]->SetMarkerSize(2);
integrated_raa[1]->SetMarkerSize(2);
pion_cucu->SetLineWidth(width);

TLegend* lg_compile=new TLegend(0.12,0.74,0.39,0.91);
lg_compile->AddEntry(integrated_raa[0],"Ru+Ru");
lg_compile->AddEntry(integrated_raa[1],"Zr+Zr");
lg_compile->AddEntry(pp_errbox,"pp uncertainty","f");
lg_compile->SetBorderSize(0);
lg_compile->Draw();
sys_err_raa[0]->Draw("s=0.5 same");
sys_err_raa[1]->Draw("s=0.5 same");
integrated_raa[0]->Draw("samep");
integrated_raa[1]->Draw("samep");


TLine* l=new TLine(compile_xmin,1,compile_xmax,1);
l->SetLineStyle(8);
l->Draw("same");

prelim_tag.DrawLatex(0.32,0.95,"#bf{Data}");

compile_raa->SaveAs(Form("prelim_plots/raa_summary_0_%ibin.pdf",ncent));


TLegend* lg_compare=new TLegend(0.39,0.74,0.66,0.91);
lg_compare->AddEntry(mod_auau,"Au+Au");
lg_compare->AddEntry(mod_dau,"d+Au");
lg_compare->AddEntry(pion_cucu,"Cu+Cu #frac{#pi^{+}+#pi^{-}}{2}");

lg_compare->SetBorderSize(0);
lg_compare->Draw();


mod_auau->Draw("samep");
mod_dau->Draw("samep");
pion_cucu->Draw("samep");


//phenix_uu_pi[1]->Draw("s=0.5 same");
//phenix_uu_pi[0]->Draw("samep");

//phenix_auau_pi[1]->Draw("s=0.5 same");
//phenix_auau_pi[0]->Draw("samep");

//phenix_cuau_pi[1]->Draw("s=0.5 same");
//phenix_cuau_pi[0]->Draw("samep");


sys_err_raa[0]->Draw("s=0.5 same");
sys_err_raa[1]->Draw("s=0.5 same");
integrated_raa[0]->Draw("samep");
integrated_raa[1]->Draw("samep");

compile_raa->SaveAs(Form("prelim_plots/raa_summary_1_%ibin.pdf",ncent));



TGraphErrors** model=hgpythia_ref();
TGraphErrors** model_nhard=hgpythia_nhard();
model[0]->SetFillStyle(3002);
model[0]->SetFillColorAlpha(kBlue,0.5);
model[1]->SetFillStyle(3001);
model[1]->SetFillColorAlpha(kRed,0.5);

model[0]->SetMarkerStyle(1);
model[0]->SetMarkerSize(0);
model[0]->SetLineWidth(0);
model[1]->SetMarkerStyle(1);
model[1]->SetMarkerSize(0);
model[1]->SetLineWidth(0);


model_nhard[0]->SetLineColor(kBlue-2);
model_nhard[1]->SetLineColor(kRed-2);
model_nhard[0]->SetLineWidth(3);
model_nhard[1]->SetLineWidth(3);
model_nhard[0]->SetMarkerStyle(48);
model_nhard[1]->SetMarkerStyle(49);

model_nhard[0]->SetMarkerSize(1.5);
model_nhard[1]->SetMarkerSize(1.5);
model_nhard[0]->SetMarkerColor(kBlue-2);
model_nhard[1]->SetMarkerColor(kRed-2);

bool get_nhard=true;
if(get_nhard){
  prelim_tag.DrawLatex(0.79,0.95,"#bf{HG-PYTHIA}");
  model_nhard[0]->Draw("samepl");
  model_nhard[1]->Draw("samepl");
  TLegend* lg_model=new TLegend(0.7,0.78,0.97,0.91);
  lg_model->AddEntry(model_nhard[0],"Ru+Ru N_{hard}     ");
  lg_model->AddEntry(model_nhard[1],"Zr+Zr N_{hard}     ");
  lg_model->SetBorderSize(0);
  lg_model->Draw();

  sys_err_raa[0]->Draw("s=0.5 same");
  sys_err_raa[1]->Draw("s=0.5 same");
  integrated_raa[0]->Draw("samep");
  integrated_raa[1]->Draw("samep");
  compile_raa->SaveAs(Form("prelim_plots/raa_summary_nhard_%ibin.pdf",ncent));
}


bool get_pythia=true;
if(get_pythia){
  model[0]->Draw("same e3");
  model[1]->Draw("same e3");

  TLegend* lg_mych5=new TLegend(0.7,0.65,0.97,0.91);
  lg_mych5->AddEntry(model_nhard[0],"Ru+Ru N_{hard}     ");
  lg_mych5->AddEntry(model_nhard[1],"Zr+Zr N_{hard}     ");
  lg_mych5->AddEntry(model[0],"Ru+Ru Y^{ch}");
  lg_mych5->AddEntry(model[1],"Zr+Zr Y^{ch}");
  lg_mych5->SetBorderSize(0);
  lg_mych5->Draw();
  prelim_tag.DrawLatex(0.79,0.95,"#bf{HG-PYTHIA}");

  sys_err_raa[0]->Draw("s=0.5 same");
  sys_err_raa[1]->Draw("s=0.5 same");
  integrated_raa[0]->Draw("samep");
  integrated_raa[1]->Draw("samep");

  compile_raa->SaveAs(Form("prelim_plots/raa_summary_pythia_%ibin.pdf",ncent));
}




bool get_phenix=true;
if(get_phenix){
  TGraphErrors** phenix_uu_pi=phenix_uu_pion();
  phenix_set_style(phenix_uu_pi,26,kGreen+3,width);

  TGraphErrors** phenix_cuau_pi=phenix_cuau_pion();
  phenix_set_style(phenix_cuau_pi,28,kYellow+3,width);

  TGraphErrors** phenix_auau_pi=phenix_auau_pion();
  phenix_set_style(phenix_auau_pi,38,kViolet+3,width);

  prelim_tag.DrawLatex(0.88,0.52,"#bf{PHENIX #pi^{0}}");

  phenix_uu_pi[1]->Draw("s=0.5 same");
  phenix_uu_pi[0]->Draw("samep");

  phenix_auau_pi[1]->Draw("s=0.5 same");
  phenix_auau_pi[0]->Draw("samep");

  phenix_cuau_pi[1]->Draw("s=0.5 same");
  phenix_cuau_pi[0]->Draw("samep");

  TLegend* lg_phenix=new TLegend(0.8,0.32,0.95,0.48);
  lg_phenix->AddEntry(phenix_uu_pi[0],"U+U");
  lg_phenix->AddEntry(phenix_auau_pi[0],"Au+Au");
  lg_phenix->AddEntry(phenix_cuau_pi[0],"Cu+Au");
  lg_phenix->SetBorderSize(0);
  lg_phenix->Draw();
  compile_raa->Draw();

  compile_raa->SaveAs(Form("prelim_plots/raa_summary_phenix_%ibin.pdf",ncent));
}

//*/
}
