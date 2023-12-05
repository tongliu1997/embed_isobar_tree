#include "../pp_reference/hist_pp.h"
#include "out_hist.h"
void outhist_plot(
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

TCanvas* c[8];

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
    gPad->SetLogy();
    if(isys==0){gPad->SetRightMargin(0.02); gPad->SetLeftMargin(0.15);}
    else{gPad->SetLeftMargin(0.02);gPad->SetRightMargin(0.15);}
//    c[isys]=new TCanvas(Form("c_%i",isys),"",700,600);
//    c[isys]->SetLogy();
//    c[isys]->SetLeftMargin(0.15);
//    double raw_ymin=raw_spec[isys][ncent-1]->GetBinContent(nbins)/2;
    TLegend* lg=new TLegend(0.55,0.6,0.84,0.98);
    TH1D* raw_copy[ncent];
    for(int i=0;i<ncent;i++){
	raw_copy[i]=(TH1D*)nominal[isys]->raw_spec[i]->Clone();
	double inv_yield=0;
   	for(int ibin=1;ibin<=raw_copy[i]->GetNbinsX();ibin++){
	    inv_yield+=6.28*raw_copy[i]->GetBinContent(ibin)*raw_copy[i]->GetBinWidth(ibin)*(raw_copy[i]->GetBinLowEdge(ibin)+0.5*raw_copy[i]->GetBinWidth(ibin));
	    cout<<raw_copy[i]->GetBinContent(ibin)<<"\t"<<raw_copy[i]->GetBinWidth(ibin)<<"\t"<<raw_copy[i]->GetBinLowEdge(ibin)<<"\t"<<inv_yield<<endl;
 	}
	cout<<"Raw "<<sys<<"\t"<<(i?Form("%i%%-%i%%",bins[i],bins[i+1]):"0%-10%")<<"\t"<<inv_yield*2<<"\t"<<inv_yield/ncoll[isys][i]<<endl;
    	raw_copy[i]->Scale(1.0/pow(5,i));
//    	raw_copy[i]->SetTitle("");
	const string sysname=isys?"Zr":"Ru";
    	raw_copy[i]->SetTitle(Form("%s + %s",sysname.c_str(),sysname.c_str()));
    	raw_copy[i]->GetXaxis()->SetRangeUser(0.1,30);
    	raw_copy[i]->GetYaxis()->SetRangeUser(rawmin,rawmax);
    	raw_copy[i]->SetXTitle("p_{T} (GeV/c)");
     	if(isys==0)raw_copy[i]->SetYTitle("#frac{1}{N_{ev} p_{T} } #frac{d^{3} N}{d p_{T} d #eta d #phi}");
	else{
	    raw_copy[i]->GetYaxis()->SetLabelSize(0);
	    raw_copy[i]->GetYaxis()->SetLabelOffset(100);

	}
    	raw_copy[i]->SetLineWidth(line_width);
	raw_copy[i]->SetMarkerStyle(markers[i]);
	raw_copy[i]->SetMarkerSize(marker_size);
	raw_copy[i]->SetLineColor(colors[i]);
	raw_copy[i]->SetMarkerColor(colors[i]);
	raw_copy[i]->SetBarOffset(bar_offset*i);
    	raw_copy[i]->Draw("same");
    	if(isys)lg->AddEntry(raw_copy[i],i?Form("%i%%-%i%% / 5^%i",bins[i],bins[i+1],i):"0%-10%");
    }
    if(isys){lg->SetBorderSize(0);lg->Draw();}
}

c[0]->SaveAs(Form("prelim_plots/RawSpec_%i.pdf",ncent));


c[1]=new TCanvas("c1","",1200,600);
c[1]->Divide(2,1,0.0);
double unfold_ymin[2],unfold_ymax[2];
for(int isys=0;isys<2;isys++){
    unfold_ymax[isys]=nominal[isys]->unfold_spec[0]->GetBinContent(4)*5;
    unfold_ymin[isys]=nominal[isys]->unfold_spec[ncent-1]->GetBinContent(nbins-2)/pow(5,ncent-1)/2;
}
 
double unfoldmax=unfold_ymax[0]>unfold_ymax[1]?unfold_ymax[0]:unfold_ymax[1];  
double unfoldmin=unfold_ymin[0]<unfold_ymin[1]?unfold_ymin[0]:unfold_ymin[1];  
for(int isys=0;isys<2;isys++){
//Unfolded
    string sys=isys?"Zr":"Ru";
    c[1]->cd(isys+1);
    gPad->SetLogy();
    if(isys==0){gPad->SetRightMargin(0.02); gPad->SetLeftMargin(0.15);}
    else{gPad->SetLeftMargin(0.02);gPad->SetRightMargin(0.15);}

    double unfold_ymax=nominal[isys]->unfold_spec[0]->GetBinContent(4)*2;
    double unfold_ymin=nominal[isys]->unfold_spec[ncent-1]->GetBinContent(nbins-3)/pow(5,ncent-1)/2;
    TLegend* lg_unfold=new TLegend(0.40,0.55,0.84,0.93);
    TH1D* unfold_copy[ncent];
    for(int i=0;i<ncent;i++){
	
    	unfold_copy[i]=(TH1D*)nominal[isys]->unfold_spec[i]->Clone();
	double inv_yield=0;
   	for(int ibin=1;ibin<=unfold_copy[i]->GetNbinsX();ibin++){
//	    cout<<unfold_copy[i]->GetBinContent(ibin)<<"\t"<<unfold_copy[i]->GetBinWidth(ibin)<<"\t"<<unfold_copy[i]->GetBinLowEdge(ibin)<<endl;
	    inv_yield+=6.28*unfold_copy[i]->GetBinContent(ibin)*unfold_copy[i]->GetBinWidth(ibin)*(unfold_copy[i]->GetBinLowEdge(ibin)+0.5*unfold_copy[i]->GetBinWidth(ibin));
 	}
	cout<<"Unfolded "<<sys<<"\t"<<(i?Form("%i%%-%i%%",bins[i],bins[i+1]):"0%-10%")<<"\t"<<inv_yield*2<<"\t"<<inv_yield/ncoll[isys][i]<<endl;
    	unfold_copy[i]->Scale(1.0/pow(5,i));
    	unfold_copy[i]->GetXaxis()->SetRangeUser(0,20);
    	unfold_copy[i]->GetYaxis()->SetRangeUser(unfoldmin,unfoldmax);
    	unfold_copy[i]->SetTitle(Form("%s+%s",sys.c_str(),sys.c_str()));
    	unfold_copy[i]->SetXTitle("p_{T} (GeV/c)");
    	if(isys==0){
	    unfold_copy[i]->SetYTitle("#frac{1}{N_{ev} p_{T}} #frac{d^{3} N}{d p_{T} d #eta d #phi}");
    	    unfold_copy[i]->GetYaxis()->SetTitleSize(0.04);
	}
	else {
	    unfold_copy[i]->GetYaxis()->SetLabelSize(0);
	    unfold_copy[i]->GetYaxis()->SetLabelOffset(100);
	}
    	unfold_copy[i]->SetLineWidth(line_width);
	unfold_copy[i]->SetMarkerStyle(markers[i]);
	unfold_copy[i]->SetMarkerSize(marker_size);
	unfold_copy[i]->SetMarkerColor(colors[i]);
	unfold_copy[i]->SetLineColor(colors[i]);
	unfold_copy[i]->SetBarOffset(bar_offset*i);
    	unfold_copy[i]->Draw("same p0");
    	if(i==0)lg_unfold->AddEntry(unfold_copy[i],"0%-10%");
	else if(i==1) lg_unfold->AddEntry(unfold_copy[i],"10%-20% / 5");
	else lg_unfold->AddEntry(unfold_copy[i],Form("%i%%-%i%% / 5^%i",bins[i],bins[i+1],i));
    }
  if(isys){lg_unfold->SetBorderSize(0);lg_unfold->Draw();}
}
c[1]->cd(1);
prelim_tag.SetTextAlign(23);
prelim_tag.SetTextSize(0.05);
prelim_tag.SetNDC();
prelim_tag.DrawLatex(0.7,0.85,"STAR #bf{#it{Preliminary}}");
prelim_tag.DrawLatex(0.7,0.78,"Isobar #sqrt{s_{NN}}=200 GeV");
prelim_tag.DrawLatex(0.7,0.7,"(h^{+}+h^{-})/2");
c[1]->SaveAs(Form("prelim_plots/Isobar_UnfoldSpec_%i.pdf",ncent));


// Raa
c[2]=new TCanvas("c2","",1200,600);
c[2]->Divide(2,1,0);
vector<int> cent_prelim={0,10,20,40,60,80};
bool is_qm_nominal=false;
if(bins==cent_prelim){
    cout<<"Check!"<<endl;
    is_qm_nominal=true;
}

double error_nominal[2][5]={{8.5215/351.84,2.8646/231.99,1.3177/118.21,0.337/41.04,0.0594/11.79},
{8.2371/347.52,2.609/224.65,1.1188/110.84,0.276/37.64,0.0567/10.64}};

float raa_xmin=0.1,raa_xmax=10.49;
TLine *line_raa=new TLine(raa_xmin,1,raa_xmax,1);
line_raa->SetLineStyle(8);


for(int isys=0;isys<2;isys++){
    string sys=isys?"Zr":"Ru";
    c[2]->cd(isys+1);  
    if(!isys)gPad->SetTicky();
    if(isys==0){gPad->SetRightMargin(0.0); gPad->SetLeftMargin(0.15);}
    else{gPad->SetLeftMargin(0.0);gPad->SetRightMargin(0.05);}
    TLegend* lg_raa=new TLegend(0.11,0.13,0.7,0.3);
    TH1D* unfold_raa[ncent];
    TGraphErrors* raa_sys[ncent];
    TLine* line_npart[ncent];

    TH1D* dummy_plot=new TH1D(Form("raa_dummy_%i",isys),"",10,raa_xmin,raa_xmax);
    dummy_plot->GetXaxis()->SetRangeUser(raa_xmin,raa_xmax); 
    dummy_plot->GetYaxis()->SetRangeUser(0.01,1.449); 
    dummy_plot->SetXTitle("p_{T} (GeV/c)");
    dummy_plot->GetXaxis()->SetLabelSize(0.04);
    dummy_plot->GetXaxis()->SetTitleSize(0.04);
    if(isys==0){dummy_plot->SetYTitle("R_{AA}");dummy_plot->GetYaxis()->SetTitleSize(0.06);}
    else{
	dummy_plot->GetYaxis()->SetLabelSize(0);	 
	dummy_plot->GetYaxis()->SetLabelOffset(100);	 
    }
    dummy_plot->DrawClone("same");
    delete dummy_plot;
    TH1D* pp_err=(TH1D*)pp_hist_noerr->Clone();
    pp_err->SetName("pp_errorbar");
    pp_err->Divide(pp_hist);

    pp_err->SetTitle(Form("%s+%s",sys.c_str(),sys.c_str()));
    pp_err->SetFillColorAlpha(15,0.5);
    pp_err->SetXTitle("p_{T} (GeV/c)");
    pp_err->GetXaxis()->SetLabelSize(0.04);
    pp_err->GetXaxis()->SetTitleSize(0.04);
    pp_err->SetLineColor(15);
    pp_err->SetMarkerColor(15);
    if(isys==0){pp_err->SetYTitle("R_{AA}");pp_err->GetYaxis()->SetTitleSize(0.06);}
    else{
	pp_err->GetYaxis()->SetLabelSize(0);	 
	pp_err->GetYaxis()->SetLabelOffset(100);	 
    }
    pp_err->Draw("same e3");  
    lg_raa->AddEntry(pp_err,"pp uncertainty");
    line_raa->Draw("same");
    double pp_scaling_err=3.5/30;
    TBox* box_pp_scaling=new TBox(raa_xmax-0.15,1-pp_scaling_err,raa_xmax,1+pp_scaling_err);
    box_pp_scaling->SetFillColor(15);
    box_pp_scaling->Draw("same");

    for(int i=0;i<ncent;i++){
 	double npart_scale=npart[isys][i]/ncoll[isys][i];
	line_npart[i]=new TLine(0.1,npart_scale,2,npart_scale);
	line_npart[i]->SetLineColor(colors[i]);
	line_npart[i]->SetLineStyle(2);
//	line_npart[i]->Draw("same");
    	double xcent[nbins-8];
    	double xerr[nbins-8];
    	for(int ibin=4;ibin<=nbins-5;ibin++){
	    xcent[ibin-4]=nominal[isys]->unfold_spec[0]->GetBinCenter(ibin)+bar_offset*i*nominal[isys]->unfold_spec[0]->GetBinWidth(ibin);
	    //xcent[ibin-4]=nominal[isys]->unfold_spec[0]->GetBinCenter(ibin);
	    xerr[ibin-4]=0.05;
    	}	


	double ycent[nbins-8],yerr[nbins-8];
    	unfold_raa[i]=(TH1D*)nominal[isys]->unfold_spec[i]->Clone();
//    	unfold_raa[i]=(TH1D*)raw_spec[isys][i]->Clone();

    	unfold_raa[i]->SetName(Form("%s_raa_%i_%i",sys.c_str(),bins[i],bins[i+1]));
	cout<<sys<<"\t"<<(i?Form("%i%%-%i%%",bins[i],bins[i+1]):"0%-10%")<<" Npart= "<<npart[isys][i]<<"\t Ncoll= "<<ncoll[isys][i]<<endl; 
   	unfold_raa[i]->Scale(1.0/ncoll[isys][i]);
    	unfold_raa[i]->SetTitle(Form("%s+%s",sys.c_str(),sys.c_str()));
    	unfold_raa[i]->Divide(pp_hist_noerr);
    	unfold_raa[i]->GetXaxis()->SetRangeUser(0.4,10);
    	unfold_raa[i]->GetYaxis()->SetRangeUser(0.1,1.5);
	if(isys==0){
	    unfold_raa[i]->SetYTitle("R_{AA}");
	}
 	else{
	    unfold_raa[i]->GetYaxis()->SetLabelSize(0);
	    unfold_raa[i]->GetYaxis()->SetLabelOffset(100);
	}
	unfold_raa[i]->GetXaxis()->SetTitle("p_{T} (GeV/c)");
	for(int j=4;j<=nbins-5;j++){
//	    ycent[j-4]=unfold_spec[isys][i]->GetBinContent(j)/pp_hist->GetBinContent(j-3);
	    ycent[j-4]=unfold_raa[i]->GetBinContent(j);
	    yerr[j-4]=sys_plot[isys]->unfold_spec[i]->GetBinError(j)/sys_plot[isys]->unfold_spec[i]->GetBinContent(j);
//	    cout<<sys<<"\t"<<j<<"\tsystematic percentage "<<yerr[j-4]<<endl;
	    yerr[j-4]*=ycent[j-4];
	}
	raa_sys[i]=new TGraphErrors(nbins-8,xcent,ycent,xerr,yerr);
	raa_sys[i]->SetName(Form("%s_raa_sys_%i_%i",sys.c_str(),bins[i],bins[i+1]));
 
//        raa_sys[i]=(TH1D*)unfold_raa[i]->Clone();


	unfold_raa[i]->SetXTitle("p_{T} (GeV/c)");
    	unfold_raa[i]->SetYTitle("R_{AA}");
    	unfold_raa[i]->SetLineWidth(line_width);
	unfold_raa[i]->SetMarkerSize(marker_size);
	unfold_raa[i]->SetMarkerStyle(markers[i]);
	unfold_raa[i]->SetBarOffset(bar_offset*i);
	unfold_raa[i]->SetMarkerColor(colors[i]);
	unfold_raa[i]->SetLineColor(colors[i]);
	raa_sys[i]->SetMarkerSize(0);
// 	raa_sys[i]->SetBarWidth(0.4);
	raa_sys[i]->SetLineWidth(1);
        raa_sys[i]->SetLineColor(colors[i]);
        raa_sys[i]->SetFillColorAlpha(0,0);
//	raa_sys[i]->SetBarOffset(0.05*i)
	raa_sys[i]->Draw("s=0.5 same");
    	unfold_raa[i]->Draw("same e ");
	
    	lg_raa->AddEntry(unfold_raa[i],Form("%i%%-%i%%",bins[i],bins[i+1]));

	double scaling_err=(is_qm_nominal)?error_nominal[isys][i]:nominal[isys]->nbin_err(i)/nominal[isys]->nbin(i);
	
	TBox* scale_box=new TBox(raa_xmax-0.15*(i+2),1-scaling_err,raa_xmax-0.15*(i+1),1+scaling_err);
	scale_box->SetFillColor(colors[i]);
	scale_box->DrawClone("same");
    }

    if(isys){
	lg_raa->SetBorderSize(0);
	lg_raa->SetNColumns(2);
	lg_raa->Draw();
    }
    TLatex* sys_label=new TLatex(isys?0.465:0.535,0.9,Form("%s+%s",sys.c_str(),sys.c_str()));
    sys_label->SetTextAlign(12);
    sys_label->SetTextFont(32);
    sys_label->SetTextSize(0.05);
    sys_label->SetNDC();
    sys_label->Draw();
	
}


c[2]->cd(1);

prelim_tag.SetTextAlign(23);
prelim_tag.SetTextSize(0.05);
prelim_tag.SetNDC();
prelim_tag.DrawLatex(0.4,0.35,"STAR #bf{#it{Preliminary}}");
prelim_tag.DrawLatex(0.4,0.28,"Isobar #sqrt{s_{NN}}=200 GeV");
prelim_tag.DrawLatex(0.4,0.2,"(h^{+}+h^{-})/2");

c[2]->SaveAs(Form("prelim_plots/Raa_%i.pdf",ncent));

//Rcp
c[3]=new TCanvas("c3","",1200,600);
c[3]->Divide(2,1,0);
for(int isys=0;isys<2;isys++){
    string sys=isys?"Zr":"Ru";
    c[3]->cd(isys+1);
    if(isys==0){gPad->SetRightMargin(0.0); gPad->SetLeftMargin(0.15);}
    else{gPad->SetLeftMargin(0.0);gPad->SetRightMargin(0.1);}
    TLegend* lg_rcp=new TLegend(0.15,0.1,0.4,0.3);
    TH1D* unfold_rcp[ncent-1];


    TH1D* dummy_plot=new TH1D(Form("rcp_dummy_%i",isys),"",10,0.1,14.99);
    dummy_plot->GetXaxis()->SetRangeUser(0.1,14.99); 
    dummy_plot->GetYaxis()->SetRangeUser(0.01,1.29); 
    dummy_plot->SetXTitle("p_{T} (GeV/c)");
    dummy_plot->GetXaxis()->SetLabelSize(0.04);
    dummy_plot->GetXaxis()->SetTitleSize(0.04);
    dummy_plot->DrawClone();
    delete dummy_plot;

    TLine* line_npart[ncent];
    for(int i=0;i<ncent-1;i++){
	double npart_factor=npart[isys][i]/npart[isys][ncent-1];
	npart_factor/=ncoll[isys][i]/ncoll[isys][ncent-1];
	line_npart[i]=new TLine(0.1,npart_factor,2,npart_factor);
	line_npart[i]->SetLineColor(colors[i]);
	line_npart[i]->Draw("same");	
    	unfold_rcp[i]=(TH1D*)nominal[isys]->unfold_spec[i]->Clone();
    	unfold_rcp[i]->SetName(Form("%s_rcp_%i_%i",sys.c_str(),bins[i],bins[i+1]));
     	unfold_rcp[i]->Scale(ncoll[isys][ncent-1]/ncoll[isys][i]);
     	unfold_rcp[i]->SetTitle(Form("%s+%s R_{CP}",sys.c_str(),sys.c_str()));
    	unfold_rcp[i]->Divide(nominal[isys]->unfold_spec[ncent-1]);
    	unfold_rcp[i]->GetXaxis()->SetRangeUser(0,15);
    	unfold_rcp[i]->GetYaxis()->SetRangeUser(0.1,1.5);
	
    	unfold_rcp[i]->SetXTitle("p_{T} (GeV/c)");
    	if(!isys)unfold_rcp[i]->SetYTitle("R_{CP}");
	else{
	    unfold_rcp[i]->GetYaxis()->SetLabelSize(0);
	    unfold_rcp[i]->GetYaxis()->SetLabelOffset(100);
	}
    	unfold_rcp[i]->SetLineWidth(line_width);
	unfold_rcp[i]->SetMarkerSize(marker_size);
 	unfold_rcp[i]->SetMarkerStyle(markers[i]);
	unfold_rcp[i]->SetBarOffset(bar_offset*i);
	unfold_rcp[i]->SetMarkerColor(colors[i]);
	unfold_rcp[i]->SetLineColor(colors[i]);

    	unfold_rcp[i]->Draw("same");
    	lg_rcp->AddEntry(unfold_rcp[i],Form("%i%%-%i%%",bins[i],bins[i+1]));
    }
    if(isys==1){lg_rcp->SetBorderSize(0);lg_rcp->Draw();}
}

c[3]->SaveAs(Form("prelim_plots/Rcp_%i.pdf",ncent));

TCanvas* ru_vs_zr=new TCanvas("ru_vs_zr","",700,800);
TH1D* species_ratio[3][ncent];
//TH1D* nbin_ratio[ncent];
//ru_vs_zr->Divide(1,ncent,0.3,0.01);
//ru_vs_zr->Divide(1,2);
//ru_vs_zr->cd(1);
//gPad->SetBottomMargin(0.01);
//gPad->SetTopMargin(0.16);
//ru_vs_zr->cd(2);
//gPad->SetTopMargin(0.0);
//gPad->SetBottomMargin(0.16);
TPad* ratio_pads[3];
ratio_pads[0]=new TPad("raw","",0,0.57,1,1);
ratio_pads[0]->SetBottomMargin(0);
ratio_pads[0]->SetTopMargin(1./7);
ratio_pads[1]=new TPad("ncoll","",0,0.285,1,0.57);
ratio_pads[1]->SetBottomMargin(0);
ratio_pads[1]->SetTopMargin(0);
ratio_pads[2]=new TPad("ncoll","",0,0,1,0.285);
ratio_pads[2]->SetBottomMargin(1./7);
ratio_pads[2]->SetTopMargin(0);

double xmin=0.1,xmax=9.99;
TLegend* lg_ratio=new TLegend(0.15,0.66,0.75,0.96);
lg_ratio->SetNColumns(3);


TGraph** theory_plots=wilke_pt_raa();

for(int i=0;i<ncent;i++){
    for(int p=0;p<3;p++){
    	species_ratio[p][i]=(TH1D*)nominal[0]->unfold_spec[i]->Clone();
    	species_ratio[p][i]->Divide(nominal[1]->unfold_spec[i]);
	species_ratio[p][i]->SetTitle("");
	species_ratio[p][i]->SetBarOffset(0.07*i);
    	species_ratio[p][i]->SetMarkerStyle(markers[i]);
    	species_ratio[p][i]->SetMarkerSize(marker_size);
    	species_ratio[p][i]->SetLineWidth(line_width);
    	species_ratio[p][i]->GetXaxis()->SetNdivisions(205);
    	species_ratio[p][i]->GetYaxis()->SetLabelSize(0.08);
	if(p!=2){
	    species_ratio[p][i]->GetXaxis()->SetLabelSize(0);
	    species_ratio[p][i]->GetXaxis()->SetLabelOffset(100);
	}
    }

    species_ratio[1][i]->Scale(ncoll[1][i]/ncoll[0][i]);
    species_ratio[2][i]->Scale(npart[1][i]/npart[0][i]);
    species_ratio[2][i]->SetXTitle("p_{T} (GeV/c)");
    species_ratio[2][i]->GetXaxis()->SetLabelSize(0.06);
    species_ratio[2][i]->GetXaxis()->SetTitleSize(0.06);
    for(int p=0;p<3;p++){
	ru_vs_zr->cd();
	ratio_pads[p]->Draw();
	if(p)ratio_pads[p]->SetTickx();
	ratio_pads[p]->SetTicky();
	ratio_pads[p]->cd();
    if(i==0){
        TH1D* dummy_plot=new TH1D(Form("ratio_dummy_%i",p),"",10,xmin,xmax);
        dummy_plot->GetXaxis()->SetRangeUser(xmin,xmax); 
	if(p==0) {
	    dummy_plot->GetYaxis()->SetRangeUser(0.961,1.139);
            dummy_plot->SetYTitle("Ru+Ru/Zr+Zr");
            dummy_plot->GetYaxis()->SetTitleSize(0.09);
            dummy_plot->GetYaxis()->SetLabelSize(0.06);
            dummy_plot->GetYaxis()->SetTitleOffset(0.5);
	}
	if(p==1) {
		dummy_plot->GetYaxis()->SetRangeUser(0.941,1.059);
    		dummy_plot->GetYaxis()->SetLabelSize(0.09);
	}
	if(p==2) {dummy_plot->GetYaxis()->SetRangeUser(0.941,1.059);
            dummy_plot->SetXTitle("p_{T} (GeV/c)");
            dummy_plot->GetXaxis()->SetLabelSize(0.08);
            dummy_plot->GetXaxis()->SetTitleOffset(0.5);
            dummy_plot->GetXaxis()->SetTitleSize(0.08);
    	    dummy_plot->GetYaxis()->SetLabelSize(0.09);
	}
	dummy_plot->GetXaxis()->SetNdivisions(205);
    	dummy_plot->GetYaxis()->SetNdivisions(210);
    	dummy_plot->GetYaxis()->SetTickSize(0.01);
        dummy_plot->DrawClone("same");
	delete dummy_plot;
    }
    species_ratio[p][i]->GetXaxis()->SetRangeUser(xmin,xmax);
    species_ratio[p][i]->SetLineColor(colors[i]);
    species_ratio[p][i]->SetMarkerColor(colors[i]);
    species_ratio[p][i]->Draw("same");
    if(p==0){
      theory_plots[i]->SetLineColor(colors[i]);
      theory_plots[i]->SetMarkerColor(colors[i]);
      theory_plots[i]->SetMarkerStyle(107);
      theory_plots[i]->SetMarkerSize(1);
      theory_plots[i]->SetLineWidth(2);
      theory_plots[i]->SetLineStyle(2);
      theory_plots[i]->Draw("samepl");
      if(i==3){

	TLegend* lg_tra=new TLegend(0.5,0.05,0.8,0.15);
	lg_tra->AddEntry(theory_plots[i],"Trajectum");
 	lg_tra->SetBorderSize(0);
	lg_tra->Draw();
      }

    }
    
  }
  lg_ratio->AddEntry(species_ratio[2][i],Form("%i%%-%i%%",bins[i],bins[i+1]));

}

ratio_pads[1]->cd();
lg_ratio->SetBorderSize(0);
lg_ratio->Draw();

TLine* lvs=new TLine(xmin,1,xmax,1);
lvs->SetLineStyle(8);
for(int p=0;p<3;p++){
    ratio_pads[p]->cd();
    lvs->DrawClone("same");
}
TLatex* vs_label[3];
vs_label[0]=new TLatex(0.15,0.1,"per event yield");
vs_label[1]=new TLatex(0.15,0.1,"#LT N_{coll} #GT scaled");
vs_label[1]->SetTextColor(kRed);
vs_label[2]=new TLatex(0.15,0.3,"#LT N_{part} #GT scaled");
vs_label[2]->SetTextColor(kBlue);
for(int p=0;p<3;p++){
    vs_label[p]->SetTextAlign(12);
    vs_label[p]->SetTextFont(43);
    vs_label[p]->SetTextSize(24);
    vs_label[p]->SetNDC();

    ratio_pads[p]->cd();
    vs_label[p]->Draw("same");
}

ratio_pads[2]->cd();
prelim_tag.SetTextAlign(23);
prelim_tag.SetTextSize(0.1);
prelim_tag.SetNDC();
prelim_tag.DrawLatex(0.6,0.46,"STAR #bf{#it{Preliminary}}");
prelim_tag.DrawLatex(0.6,0.36,"Isobar #sqrt{s_{NN}}=200 GeV");
prelim_tag.DrawLatex(0.6,0.23,"(h^{+}+h^{-})/2");

ru_vs_zr->SaveAs(Form("prelim_plots/ru_vs_zr_%i.pdf",ncent));
}
