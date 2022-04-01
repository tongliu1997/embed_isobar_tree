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
    	raw_copy[i]->Scale(1.0/pow(5,i));
//    	raw_copy[i]->SetTitle("");
	const string sysname=isys?"Zr":"Ru";
    	raw_copy[i]->SetTitle(Form("%s + %s",sysname.c_str(),sysname.c_str()));
    	raw_copy[i]->GetXaxis()->SetRangeUser(0.1,30);
    	raw_copy[i]->GetYaxis()->SetRangeUser(rawmin,rawmax);
    	raw_copy[i]->SetXTitle("p_{T} (GeV/c)");
     	if(isys==0)raw_copy[i]->SetYTitle("#frac{1}{2#pi p_{T} } #frac{d^{2} N}{d p_{T} d #eta}");
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
    TLegend* lg_unfold=new TLegend(0.55,0.6,0.84,0.98);
    TH1D* unfold_copy[ncent];
    for(int i=0;i<ncent;i++){
	
    	unfold_copy[i]=(TH1D*)nominal[isys]->unfold_spec[i]->Clone();
    	unfold_copy[i]->Scale(1.0/pow(5,i));
    	unfold_copy[i]->GetXaxis()->SetRangeUser(0,20);
    	unfold_copy[i]->GetYaxis()->SetRangeUser(unfoldmin,unfoldmax);
    	unfold_copy[i]->SetTitle(Form("%s+%s",sys.c_str(),sys.c_str()));
    	unfold_copy[i]->SetXTitle("p_{T} (GeV/c)");
    	if(isys==0)unfold_copy[i]->SetYTitle("#frac{1}{2#pi p_{T}} #frac{d^{2} N}{d p_{T} d #eta}");
	else {
	    unfold_copy[i]->GetYaxis()->SetLabelSize(0);
	    unfold_copy[i]->GetYaxis()->SetLabelOffset(100);
	}
    	unfold_copy[i]->SetLineWidth(line_width);
	unfold_copy[i]->SetMarkerStyle(markers[i]);
	unfold_copy[i]->SetMarkerSize(marker_size);
	unfold_copy[i]->SetMarkerColor(colors[i]);
	unfold_copy[i]->SetLineColor(colors[i]);
    	unfold_copy[i]->Draw("same p0");
    	lg_unfold->AddEntry(unfold_copy[i],i?Form("%i%%-%i%% / 5^%i",bins[i],bins[i+1],i):"0%-10%");
    }
  if(isys){lg_unfold->SetBorderSize(0);lg_unfold->Draw();}
}

c[1]->SaveAs(Form("prelim_plots/UnfoldSpec_%i.pdf",ncent));


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
	    xerr[ibin-4]=0.05;
    	}	


	double ycent[nbins-8],yerr[nbins-8];
    	unfold_raa[i]=(TH1D*)nominal[isys]->unfold_spec[i]->Clone();
//    	unfold_raa[i]=(TH1D*)raw_spec[isys][i]->Clone();

    	unfold_raa[i]->SetName(Form("%s_raa_%i_%i",sys.c_str(),bins[i],bins[i+1]));
	cout<<sys<<" Npart= "<<npart[isys][i]<<"\t Ncoll= "<<ncoll[isys][i]<<endl; 
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

TCanvas* ru_vs_zr=new TCanvas("ru_vs_zr","",800,800);
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
ratio_pads[0]=new TPad("raw","",0,0.65,1,1);
ratio_pads[0]->SetBottomMargin(0);
ratio_pads[0]->SetTopMargin(1./7);
ratio_pads[1]=new TPad("ncoll","",0,0.35,1,0.65);
ratio_pads[1]->SetBottomMargin(0);
ratio_pads[1]->SetTopMargin(0);
ratio_pads[2]=new TPad("ncoll","",0,0,1,0.35);
ratio_pads[2]->SetBottomMargin(1./7);
ratio_pads[2]->SetTopMargin(0);

double xmin=0.1,xmax=9.99;
TLegend* lg_ratio=new TLegend(0.2,0.15,0.8,0.5);
lg_ratio->SetNColumns(2);


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
	ratio_pads[p]->cd();
    if(i==0){
        TH1D* dummy_plot=new TH1D(Form("ratio_dummy_%i",p),"",10,xmin,xmax);
        dummy_plot->GetXaxis()->SetRangeUser(xmin,xmax); 
	if(p==0) {
	    dummy_plot->GetYaxis()->SetRangeUser(0.955,1.195);
            dummy_plot->SetYTitle("Ru+Ru/Zr+Zr ratio");
            dummy_plot->GetYaxis()->SetTitleSize(0.1);
            dummy_plot->GetYaxis()->SetTitleOffset(0.45);
	}
	if(p==1) dummy_plot->GetYaxis()->SetRangeUser(0.88,1.12);
	if(p==2) {dummy_plot->GetYaxis()->SetRangeUser(0.88,1.12);
            dummy_plot->SetXTitle("p_{T} (GeV/c)");
            dummy_plot->GetXaxis()->SetLabelSize(0.08);
            dummy_plot->GetXaxis()->SetTitleOffset(0.5);
            dummy_plot->GetXaxis()->SetTitleSize(0.08);
	}
	dummy_plot->GetXaxis()->SetNdivisions(205);
    	dummy_plot->GetYaxis()->SetNdivisions(203);
    	dummy_plot->GetYaxis()->SetLabelSize(0.1);
        dummy_plot->DrawClone("same");
	delete dummy_plot;
    }
    	species_ratio[p][i]->GetXaxis()->SetRangeUser(xmin,xmax);
	species_ratio[p][i]->SetLineColor(colors[i]);
	species_ratio[p][i]->SetMarkerColor(colors[i]);
 	species_ratio[p][i]->Draw("same");
    }
    lg_ratio->AddEntry(species_ratio[2][i],Form("%i%%-%i%%",bins[i],bins[i+1]));
    

}
ratio_pads[2]->cd();
lg_ratio->SetBorderSize(0);
lg_ratio->Draw();

TLine* lvs=new TLine(xmin,1,xmax,1);
lvs->SetLineStyle(8);
for(int p=0;p<3;p++){
    ratio_pads[p]->cd();
    lvs->DrawClone("same");
}
TLatex* vs_label[3];
vs_label[0]=new TLatex(0.15,0.75,"per event yield");
vs_label[1]=new TLatex(0.15,0.85,"#color[2]{ #LT N_{coll} #GT scaling}");
vs_label[2]=new TLatex(0.15,0.85,"#color[4]{ #LT N_{part} #GT scaling}");
for(int p=0;p<3;p++){
    vs_label[p]->SetTextAlign(12);
    vs_label[p]->SetTextFont(43);
    vs_label[p]->SetTextSize(24);
    vs_label[p]->SetNDC();

    ratio_pads[p]->cd();
    vs_label[p]->Draw("same");
}

ratio_pads[1]->cd();
prelim_tag.SetTextAlign(23);
prelim_tag.SetTextSize(0.1);
prelim_tag.SetNDC();
prelim_tag.DrawLatex(0.5,0.35,"STAR #bf{#it{Preliminary}}");
prelim_tag.DrawLatex(0.5,0.25,"Isobar #sqrt{s_{NN}}=200 GeV");
prelim_tag.DrawLatex(0.5,0.12,"(h^{+}+h^{-})/2");

ru_vs_zr->SaveAs(Form("prelim_plots/ru_vs_zr_%i.pdf",ncent));

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





TCanvas* compile_raa=new TCanvas("compile_raa","",1000,800);
compile_raa->SetLogx();
compile_raa->Draw();
compile_raa->cd();
double compile_xmin=6;
double compile_xmax=375;
TH1D* compile_dummy=new TH1D("comp_dummy","",200,compile_xmin,compile_xmax);
compile_dummy->GetXaxis()->SetRangeUser(compile_xmin,compile_xmax);
compile_dummy->GetYaxis()->SetRangeUser(0.01,1.99);
compile_dummy->SetXTitle("#LT N_{part} #GT");
//compile_dummy->SetTitle("Hadron R_{AA} for p_{T} > 5 GeV");
compile_dummy->SetYTitle("R_{AA}");
compile_dummy->DrawClone();
delete compile_dummy;
prelim_tag.SetTextAlign(23);
prelim_tag.SetTextSize(0.04);
prelim_tag.SetNDC();
prelim_tag.DrawLatex(0.45,0.24,"STAR #bf{#it{Preliminary}}");
prelim_tag.DrawLatex(0.45,0.20,"Isobar #sqrt{s_{NN}}=200 GeV");
prelim_tag.DrawLatex(0.45,0.15,"(h^{+}+h^{-})/2  p_{T} > 5 GeV");
pp_err_buff=sqrt(pp_err_buff*pp_err_buff+3.5*3.5/900);
TBox* pp_errbox=new TBox(compile_xmax-20,1-pp_err_buff,compile_xmax,1+pp_err_buff);
pp_errbox->SetFillColor(15);
pp_errbox->Draw("same");

TGraphErrors** model=hgpythia_ref();
model[0]->SetFillStyle(3006);
model[0]->SetFillColor(kBlue+2);
model[1]->SetFillStyle(3007);
model[1]->SetFillColor(kRed+2);

model[0]->SetMarkerStyle(1);
model[0]->SetMarkerSize(0);
model[0]->SetLineWidth(0);
model[1]->SetMarkerStyle(1);
model[1]->SetMarkerSize(0);
model[1]->SetLineWidth(0);

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
/*
TGraphErrors* phenix_uu_pi=phenix_uu_pion();
phenix_uu_pi->SetMarkerStyle(26);
phenix_uu_pi->SetLineColor(kGreen+3);
phenix_uu_pi->SetMarkerColor(kGreen+3);
phenix_uu_pi->SetMarkerSize(2);
phenix_uu_pi->SetLineWidth(width);
*/
mod_auau->SetLineWidth(width);
integrated_raa[0]->SetLineWidth(width+1);
integrated_raa[1]->SetLineWidth(width+1);
integrated_raa[0]->SetMarkerSize(2);
integrated_raa[1]->SetMarkerSize(2);
pion_cucu->SetLineWidth(width);

TLegend* lg_compile=new TLegend(0.12,0.72,0.3,0.89);
lg_compile->AddEntry(integrated_raa[0],"Ru+Ru");
lg_compile->AddEntry(integrated_raa[1],"Zr+Zr");
lg_compile->AddEntry(pp_errbox,"pp uncertainty");
lg_compile->SetBorderSize(0);
lg_compile->Draw();
sys_err_raa[0]->Draw("s=0.5 same");
sys_err_raa[1]->Draw("s=0.5 same");
integrated_raa[0]->Draw("samep");
integrated_raa[1]->Draw("samep");


TLine* l=new TLine(compile_xmin,1,compile_xmax,1);
l->SetLineStyle(8);
l->Draw("same");

compile_raa->SaveAs(Form("prelim_plots/raa_summary_0_%ibin.pdf",ncent));


TLegend* lg_compare=new TLegend(0.65,0.75,0.86,0.89);
lg_compare->AddEntry(mod_auau,"Au+Au");
lg_compare->AddEntry(mod_dau,"d+Au");
lg_compare->AddEntry(pion_cucu,"Cu+Cu #frac{#pi^{+}+#pi^{-}}{2}");
//lg_compare->AddEntry(mod_auau,"Au+Au 5.1-10 GeV/c");
//lg_compare->AddEntry(mod_dau,"d+Au 5.1-10 GeV/c");
//lg_compare->AddEntry(pion_cucu,"Cu+Cu #frac{#pi^{+}+#pi^{-}}{2} 5-8 GeV/c");
//lg_compare->AddEntry(phenix_uu_pi,"PHENIX U+U 193 GeV #pi^{0}->#gamma#gamma p_{T}>5 GeV/c");

lg_compare->SetBorderSize(0);
lg_compare->Draw();


mod_auau->Draw("samep");
mod_dau->Draw("samep");
//phenix_uu_pi->Draw("samep");
pion_cucu->Draw("samep");

sys_err_raa[0]->Draw("s=0.5 same");
sys_err_raa[1]->Draw("s=0.5 same");
integrated_raa[0]->Draw("samep");
integrated_raa[1]->Draw("samep");

compile_raa->SaveAs(Form("prelim_plots/raa_summary_1_%ibin.pdf",ncent));







TLegend* lg_model=new TLegend(0.3,0.8,0.65,0.89);
lg_model->AddEntry(model[0],"HG-PYTHIA Ru+Ru");
lg_model->AddEntry(model[1],"HG-PYTHIA Zr+Zr");
lg_model->SetBorderSize(0);
lg_model->Draw();
model[0]->SetMarkerColor(kBlue-9);
model[1]->SetMarkerColor(kRed-9);
model[0]->Draw("same e3");
model[1]->Draw("same e3");

sys_err_raa[0]->Draw("s=0.5 same");
sys_err_raa[1]->Draw("s=0.5 same");
integrated_raa[0]->Draw("samep");
integrated_raa[1]->Draw("samep");
compile_raa->SaveAs(Form("prelim_plots/raa_summary_%ibin.pdf",ncent));
//*/
}
