#include "../pp_reference/hist_pp.h"
#include "out_hist.h"
void outhist_plot(
const char* ru_name="outhist_ru_2_3.root",
const char* zr_name="outhist_zr_2_3.root",
std::vector<int> bins={0,10,20,30,50,70}
){
const int ncent=bins.size()-1;

double marker_size=1;
double line_width=2;
out_hist* nominal[2];


nominal[0]=new out_hist(ru_name,bins,"ru","");
nominal[1]=new out_hist(zr_name,bins,"zr","");


double npart[2][ncent],npart_err[2][ncent],ncoll[2][ncent],ncoll_err[2][ncent];

for(int isys=0;isys<2;isys++){

    for(int i=0;i<ncent;i++){
	npart[isys][i]=nominal[isys]->npart(i); 
	npart_err[isys][i]=nominal[isys]->npart_err(i); 
	ncoll[isys][i]=nominal[isys]->ncoll(i); 
	ncoll_err[isys][i]=nominal[isys]->ncoll_err(i); 
	
    }
}

int markers[20]={20,21,22,23,29,33,34,37,39,43,45,46,47,48,49,33,34,2,3,5};
TH1D* pp_hist=hist_pp(true);
pp_hist->SetName("pp_hist_witherr");
TH1D* pp_hist_noerr=hist_pp(false);
pp_hist_noerr->SetName("pp_hist_noerr");

pp_hist->Scale(5./7.);
pp_hist_noerr->Scale(5./7.);

gStyle->SetPalette(1);
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
    	raw_copy[i]->Draw("same PLC PLM PMC");
    	if(isys)lg->AddEntry(raw_copy[i],i?Form("%i%%-%i%% / 5^%i",bins[i],bins[i+1],i):"0%-10%");
    }
    if(isys){lg->SetBorderSize(0);lg->Draw();}
}

c[0]->SaveAs("prelim_plots/RawSpec.png");


c[1]=new TCanvas("c1","",1200,600);
c[1]->Divide(2,1,0.0);
double unfold_ymin[2],unfold_ymax[2];
for(int isys=0;isys<2;isys++){
    unfold_ymax[isys]=nominal[isys]->unfold_spec[0]->GetBinContent(4)*5;
    unfold_ymin[isys]=nominal[isys]->unfold_spec[ncent-1]->GetBinContent(nbins-3)/pow(5,ncent-1)/2;
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
    	unfold_copy[i]->Draw("same p0 PLC PLM PMC");
    	lg_unfold->AddEntry(unfold_copy[i],i?Form("%i%%-%i%% / 5^%i",bins[i],bins[i+1],i):"0%-10%");
    }
  if(isys){lg_unfold->SetBorderSize(0);lg_unfold->Draw();}
}

c[1]->SaveAs("prelim_plots/UnfoldSpec.png");


// Raa
c[2]=new TCanvas("c2","",1200,600);
c[2]->Divide(2,1,0);
for(int isys=0;isys<2;isys++){
    string sys=isys?"Zr":"Ru";
    c[2]->cd(isys+1);  
    if(isys==0){gPad->SetRightMargin(0.02); gPad->SetLeftMargin(0.15);}
    else{gPad->SetLeftMargin(0.02);gPad->SetRightMargin(0.05);}
    TLegend* lg_raa=new TLegend(0.18,0.13,0.5,0.35);
    TH1D* unfold_raa[ncent];
    TGraphErrors* raa_sys[ncent];
    double xcent[nbins-8];
    double xerr[nbins-8];
    for(int i=4;i<=nbins-5;i++){
	xcent[i-4]=nominal[isys]->unfold_spec[0]->GetBinCenter(i);
	xerr[i-4]=0;
    }
    TH1D* pp_err=(TH1D*)pp_hist_noerr->Clone();
    pp_err->SetName("pp_errorbar");
    pp_err->Divide(pp_hist);
    pp_err->GetXaxis()->SetRangeUser(0.4,10);
    pp_err->GetYaxis()->SetRangeUser(0.01,1.49);

    pp_err->SetTitle(Form("%s+%s R_{AA}",sys.c_str(),sys.c_str()));
    pp_err->SetFillColorAlpha(15,0.5);
    pp_err->SetXTitle("p_{T} (GeV/c)");
    pp_err->GetXaxis()->SetLabelSize(0.04);
    pp_err->GetXaxis()->SetTitleSize(0.04);
    if(isys==0)pp_err->SetYTitle("R_{AA}");
    else{
	pp_err->GetYaxis()->SetLabelSize(0);	 
	pp_err->GetYaxis()->SetLabelOffset(100);	 
    }
    pp_err->Draw("same e3");  

    
    lg_raa->AddEntry(pp_err,"pp uncertainty");

    for(int i=0;i<ncent;i++){

	double ycent[nbins-8],yerr[nbins-8];
    	unfold_raa[i]=(TH1D*)nominal[isys]->unfold_spec[i]->Clone();
//    	unfold_raa[i]=(TH1D*)raw_spec[isys][i]->Clone();

    	unfold_raa[i]->SetName(Form("%s_raa_%i_%i",sys.c_str(),bins[i],bins[i+1]));
	cout<<sys<<" Ncoll= "<<ncoll[isys][i]<<endl; 
   	unfold_raa[i]->Scale(1.0/ncoll[isys][i]);
    	unfold_raa[i]->SetTitle(Form("%s+%s R_{AA}",sys.c_str(),sys.c_str()));
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
	   yerr[j-4]=unfold_raa[i]->GetBinError(j)/2;

	}
	raa_sys[i]=new TGraphErrors(nbins-8,xcent,ycent,xerr,yerr);
	unfold_raa[i]->SetXTitle("p_{T} (GeV/c)");
    	unfold_raa[i]->SetYTitle("R_{AA}");
    	unfold_raa[i]->SetLineWidth(line_width);
	unfold_raa[i]->SetMarkerSize(marker_size);
	unfold_raa[i]->SetMarkerStyle(markers[i]);

    	unfold_raa[i]->Draw("same e PLC PLM PMC");
	raa_sys[i]->SetMarkerSize(marker_size);
//	raa_sys[i]->DrawClone("same |> PLC PFC");
    	lg_raa->AddEntry(unfold_raa[i],Form("%i%%-%i%%",bins[i],bins[i+1]));
    }

    if(isys){lg_raa->SetBorderSize(0);lg_raa->Draw();}
}
c[2]->SaveAs("prelim_plots/Raa.png");
//Rcp
c[3]=new TCanvas("c3","",1200,600);
c[3]->Divide(2,1,0);
for(int isys=0;isys<2;isys++){
    string sys=isys?"Zr":"Ru";
    c[3]->cd(isys+1);
    if(isys==0){gPad->SetRightMargin(0.02); gPad->SetLeftMargin(0.15);}
    else{gPad->SetLeftMargin(0.02);gPad->SetRightMargin(0.1);}
    TLegend* lg_rcp=new TLegend(0.15,0.1,0.4,0.3);
    TH1D* unfold_rcp[ncent-1];
    for(int i=0;i<ncent-1;i++){

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
    	unfold_rcp[i]->Draw("same PLC PLM PMC");
    	lg_rcp->AddEntry(unfold_rcp[i],Form("%i%%-%i%%",bins[i],bins[i+1]));

    }
    if(isys==1){lg_rcp->SetBorderSize(0);lg_rcp->Draw();}


//    c[isys]->SaveAs(Form("prelim_plots/%s_raw_spec.png",sys.c_str()));
//    c[isys+2]->SaveAs(Form("prelim_plots/%s_unfold_spec.png",sys.c_str()));
//    c[isys+4]->SaveAs(Form("prelim_plots/%s_raa.png",sys.c_str()));
//    c[isys+6]->SaveAs(Form("prelim_plots/%s_rcp.png",sys.c_str()));
    }

double raa_5GeV[2][ncent],raa_err_5GeV[2][ncent];
double raa_xbins[4]={0,5.1,10,30};
double pp_buff=0,pp_err_buff=0;
for(int i=1;i<=nbins;i++){
    if(pp_hist->GetBinCenter(i)<5.1 || pp_hist->GetBinCenter(i)>10)continue;
//    cout<<pp_hist->GetBinCenter(i)<<endl;
     pp_buff+=(pp_hist->GetBinContent(i)*pp_hist->GetBinWidth(i));	    
     pp_err_buff+=pow(pp_hist->GetBinError(i)*pp_hist->GetBinWidth(i),2);	    

}

cout<<"pp fractional error: "<<sqrt(pp_err_buff)/pp_buff<<endl;


TGraphErrors* integrated_raa[2];

for(int isys=0;isys<2;isys++){
   for(int i=0;i<ncent;i++){
	double isobar_buff=0,isobar_err_buff=0;	
	for(int j=1;j<=nbins;j++){
	    if(nominal[isys]->unfold_spec[i]->GetBinCenter(j)<5.1 || nominal[isys]->unfold_spec[i]->GetBinCenter(j)>10)continue;
	    isobar_buff+=nominal[isys]->unfold_spec[i]->GetBinContent(j)*nominal[isys]->unfold_spec[i]->GetBinWidth(j);
	    isobar_err_buff+=pow(nominal[isys]->unfold_spec[i]->GetBinError(j)*nominal[isys]->unfold_spec[i]->GetBinWidth(j),2);
	    
	}
	isobar_buff/=ncoll[isys][i];
	isobar_err_buff/=pow(ncoll[isys][i],2);
	raa_5GeV[isys][i]=isobar_buff/pp_buff;
	cout<<(isys?"zr\t":"ru\t")<<ncoll[isys][i]<<"\t"<<npart[isys][i]<<"\t"<<raa_5GeV[isys][i]<<endl;


	raa_err_5GeV[isys][i]=sqrt(isobar_err_buff/(isobar_buff*isobar_buff)+pp_err_buff/(pp_buff*pp_buff));
//	raa_err_5GeV[isys][i]=sqrt(isobar_err_buff)/isobar_buff;
	raa_err_5GeV[isys][i]*=raa_5GeV[isys][i];

    }

    integrated_raa[isys]=new TGraphErrors(ncent,npart[isys],raa_5GeV[isys],npart_err[isys],raa_err_5GeV[isys]);
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
    auau_err_5GeV[raabin]=sqrt(err_buff/(raa_buff*raa_buff)+pp_err_buff/(pp_buff*pp_buff));
//    auau_err_5GeV[raabin]=sqrt(err_buff)/raa_buff;
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
//    dau_err_5GeV[i]=sqrt(err_buff)/raa_buff;
   dau_err_5GeV[i]=sqrt(err_buff/(raa_buff*raa_buff)+pp_err_buff/(pp_buff*pp_buff)); 
    dau_err_5GeV[i]*=dau_mod_5GeV[i];
}

TGraphErrors* mod_dau=new TGraphErrors(2,dau_npart,dau_mod_5GeV,dau_npart_err,dau_err_5GeV);

cout<<"d+Au plot created."<<endl;

TH1D* plot_displace=(TH1D*)nominal[0]->unfold_spec[0]->Clone();
for(int i=1;i<=plot_displace->GetNbinsX();i++){
    plot_displace->SetBinContent(i,-0.2);
    plot_displace->SetBinError(i,0);
}

TCanvas* ru_vs_zr=new TCanvas("ru_vs_zr","",600,1000);
TH1D* species_ratio[ncent];
TH1D* nbin_ratio[ncent];
TPad* pads[ncent];
//ru_vs_zr->Divide(1,ncent,0.3,0.01);


for(int i=0;i<ncent;i++){
    ru_vs_zr->cd();
    double ymin=0.93/ncent*(ncent-1-i)+0.06;
    double ymax=0.93/ncent*(ncent-i)+0.06;
    if(i==0)ymax=1; 
    if(i==ncent-1)ymin=0; 
    pads[i]=new TPad(Form("ratio_%i",i),"",0,ymin,1,ymax);
    pads[i]->SetFillColor(0);
    pads[i]->SetBorderMode(0);
    if(i!=0)pads[i]->SetTopMargin(0); else pads[i]->SetTopMargin(0.2);
    if(i!=ncent-1)pads[i]->SetBottomMargin(0);else pads[i]->SetBottomMargin(0.3);
    pads[i]->Draw();
    pads[i]->cd();
    TH1D* plot_dummy=(TH1D*)nominal[0]->unfold_spec[0]->Clone();
    for(int i=1;i<=plot_dummy->GetNbinsX();i++){
    	plot_dummy->SetBinContent(i,0);
    	plot_dummy->SetBinError(i,0);
    }

    plot_dummy->GetXaxis()->SetRangeUser(0,15);
    if(i==0){
	plot_dummy->GetYaxis()->SetRangeUser(0.94,1.06);
    	plot_dummy->GetYaxis()->SetNdivisions(403);
    }
    else if(i==1){
	plot_dummy->GetYaxis()->SetRangeUser(0.86,1.14);
    	plot_dummy->GetYaxis()->SetNdivisions(403);
    }
    else if(i==ncent-1){
	plot_dummy->GetYaxis()->SetRangeUser(0.78,1.34);
    	plot_dummy->GetYaxis()->SetNdivisions(203);
    }
    else{ 
	plot_dummy->GetYaxis()->SetRangeUser(0.76,1.24);
	
    	plot_dummy->GetYaxis()->SetNdivisions(203);
    }
    plot_dummy->GetXaxis()->SetNdivisions(5);
    plot_dummy->Draw();
    plot_dummy->GetYaxis()->SetLabelSize(0.1);


    plot_dummy->SetTitle("");
    if(i==ncent-1){
	plot_dummy->GetXaxis()->SetLabelSize(0.12);
	plot_dummy->SetXTitle("p_{T} (GeV/c)");
	plot_dummy->GetXaxis()->SetTitleSize(0.12);
	plot_dummy->GetXaxis()->SetTitleOffset(1);
    }
    else{
	plot_dummy->GetXaxis()->SetTickLength(0);
    }
    plot_dummy->GetYaxis()->SetLabelSize(0.03/(ymax-ymin));
    plot_dummy->Draw();
    species_ratio[i]=(TH1D*)nominal[0]->unfold_spec[i]->Clone();
    species_ratio[i]->Divide(nominal[1]->unfold_spec[i]);
    nbin_ratio[i]=(TH1D*)species_ratio[i]->Clone();
    nbin_ratio[i]->Scale(ncoll[1][i]/ncoll[0][i]);
//    species_ratio[i]->Add(plot_displace,i);
//    species_ratio[i]->GetXaxis()->SetRangeUser(0,10);
//    species_ratio[i]->GetYaxis()->SetRangeUser(1-0.2*ncent,1.5);
//    species_ratio[i]->GetYaxis()->SetRangeUser(0.83,1.21);
//    if(i==ncent-1){species_ratio[i]->SetXTitle("p_{T}");
//    species_ratio[i]->GetXaxis()->SetLabelSize(0.15);} 
    species_ratio[i]->SetLineWidth(2);
    species_ratio[i]->SetMarkerStyle(markers[0]);
    species_ratio[i]->SetMarkerSize(0.5);
    species_ratio[i]->Draw("same");
    nbin_ratio[i]->SetLineColor(kMagenta+2);
    nbin_ratio[i]->SetBarOffset(0.1);
    nbin_ratio[i]->SetMarkerStyle(markers[1]);
    nbin_ratio[i]->SetMarkerSize(0.5);
    nbin_ratio[i]->SetMarkerColor(kMagenta+2);
    nbin_ratio[i]->SetLineWidth(2);
    nbin_ratio[i]->Draw("same");
    TLine* l=new TLine(0,1,15,1);
    l->SetLineStyle(8);
    l->Draw("same");
    if(i==1){
        TLegend* lg_ratio=new TLegend(0.15,0.77,0.5,0.97);
	lg_ratio->AddEntry(species_ratio[i],"No N_{bin} scaling");
	lg_ratio->SetBorderSize(0);
	lg_ratio->Draw("same");
    }

    if(i==2){
    	TLegend* lg_ratio=new TLegend(0.15,0.75,0.5,0.95);
	lg_ratio->AddEntry(nbin_ratio[i],"With N_{bin} scaling");
	lg_ratio->SetBorderSize(0);
	lg_ratio->Draw("same");
    }
    TLatex* biasLabel = new TLatex(0.15,i==(ncent-1)?0.45:0.15, Form("%i%%-%i%%",bins[i],bins[i+1]));
    biasLabel->SetTextAlign(12);
    biasLabel->SetTextFont(43);
    biasLabel->SetTextSize(24);
    biasLabel->SetNDC();
    biasLabel->Draw("same");
    if(i!=0){
	ru_vs_zr->cd();
	TPad* filler=new TPad(Form("filler_%i",i),"",0.101,ymax-0.002,0.899,ymax+0.002);
	filler->SetFillColor(0);
 	filler->SetBorderMode(0);
	filler->Draw();

   }
}
ru_vs_zr->SaveAs("prelim_plots/ru_vs_zr.png");






TCanvas* compile_raa=new TCanvas("compile_raa","",1000,600);
compile_raa->SetLogx();
compile_raa->Draw();
compile_raa->cd();
double compile_xmin=1;
double compile_xmax=375;
TH1D* compile_dummy=new TH1D("comp_dummy","",200,compile_xmin,compile_xmax);
compile_dummy->GetXaxis()->SetRangeUser(compile_xmin,compile_xmax);
compile_dummy->GetYaxis()->SetRangeUser(0.01,1.49);
compile_dummy->SetXTitle("N_{part}");
compile_dummy->SetTitle("Hadron R_{AA} for p_{T} > 5 GeV");
compile_dummy->Draw();

TGraphErrors** model=hgpythia_ref();
model[0]->SetFillStyle(3006);
model[0]->SetFillColorAlpha(kBlue-9,0.5);
model[1]->SetFillStyle(3007);
model[1]->SetFillColorAlpha(kRed-9,0.5);

model[0]->SetMarkerStyle(1);
model[0]->SetMarkerSize(0);
model[0]->SetLineWidth(0);
model[1]->SetMarkerStyle(1);
model[1]->SetMarkerSize(0);
model[1]->SetLineWidth(0);

TGraphErrors* pion_cucu=cucu_pion();

mod_auau->SetLineColor(42);
mod_auau->SetMarkerColor(42);
mod_auau->GetXaxis()->SetTitle("N_{part}");
mod_auau->GetYaxis()->SetTitle("R_{AA}");
mod_auau->SetTitle("Inclusive hadron R_{AA} for p_{T} > 5 GeV");
mod_auau->SetMarkerStyle(32);
integrated_raa[0]->SetLineColor(kBlue);//Ru
integrated_raa[1]->SetLineColor(kRed);//Zr
integrated_raa[0]->SetMarkerStyle(29);
integrated_raa[1]->SetMarkerStyle(47);
integrated_raa[0]->SetMarkerColor(kBlue);
integrated_raa[1]->SetMarkerColor(kRed);
pion_cucu->SetLineColor(32);
pion_cucu->SetMarkerStyle(46);
pion_cucu->SetMarkerColor(32);

mod_dau->SetLineColor(kYellow+2);
mod_dau->SetMarkerColor(kYellow+2);
mod_dau->SetMarkerStyle(25);
mod_dau->SetMarkerSize(1);

TGraphErrors* phenix_pi=phenix_pion();
phenix_pi->SetMarkerStyle(26);
phenix_pi->SetLineColor(30);
phenix_pi->SetMarkerColor(30);
float width=2;
mod_auau->SetLineWidth(width);
integrated_raa[0]->SetLineWidth(width+1);
integrated_raa[1]->SetLineWidth(width+1);
integrated_raa[0]->SetMarkerSize(2);
integrated_raa[1]->SetMarkerSize(2);
phenix_pi->SetLineWidth(width);
pion_cucu->SetLineWidth(width);

TLegend* lg_compare=new TLegend(0.11,0.11,0.4,0.5);
lg_compare->AddEntry(integrated_raa[0],"STAR Ru+Ru #frac{h^{+}+h^{-}}{2}");
lg_compare->AddEntry(integrated_raa[1],"STAR Zr+Zr #frac{h^{+}+h^{-}}{2}");
lg_compare->AddEntry(mod_auau,"STAR Au+Au #frac{h^{+}+h^{-}}{2}");
lg_compare->AddEntry(mod_dau,"STAR d+Au #frac{h^{+}+h^{-}}{2}");
lg_compare->AddEntry(pion_cucu,"STAR Cu+Cu #frac{#pi^{+}+#pi^{-}}{2}");
lg_compare->AddEntry(phenix_pi,"PHENIX U+U 192 GeV #pi^{0}->#gamma#gamma");
lg_compare->AddEntry(model[0],"HG-PYHTIA Ru");
lg_compare->AddEntry(model[1],"HG-PYHTIA Zr");

lg_compare->SetBorderSize(0);
lg_compare->Draw();


TLine* l=new TLine(compile_xmin,1,compile_xmax,1);
l->SetLineStyle(8);
l->Draw("same");
mod_auau->Draw("samep");
mod_dau->Draw("samep");
model[0]->SetMarkerColor(kBlue-9);
model[1]->SetMarkerColor(kRed-9);
model[0]->Draw("same e3");
model[1]->Draw("same e3");
integrated_raa[0]->Draw("samep");
integrated_raa[1]->Draw("samep");
phenix_pi->Draw("samep");
pion_cucu->Draw("samep");

compile_raa->SaveAs("prelim_plots/raa_summary.png");
//*/
}
