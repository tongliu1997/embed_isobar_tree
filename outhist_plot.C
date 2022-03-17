#include "../pp_reference/hist_pp.h"
void outhist_plot(
const char* ru_name="outhist_ru_2_3.root",
const char* zr_name="outhist_zr_2_3.root"
){

const int bins[6]={0,10,20,40,60,80};

TFile* file[2];
file[0]=new TFile(ru_name);
file[1]=new TFile(zr_name);

TH1D* raw_spec[2][5];
TH1D* unfold_spec[2][5];
TH1D *hist_npart[2],*hist_ncoll[2];

double npart[2][5],npart_err[2][5],ncoll[2][5],ncoll_err[2][5];

for(int isys=0;isys<2;isys++){
    string sys=isys?"zr":"ru";
    hist_npart[isys]=(TH1D*)file[isys]->Get("npart");
    hist_ncoll[isys]=(TH1D*)file[isys]->Get("ncoll");
    hist_npart[isys]->SetName(Form("%s_npart",sys.c_str()));
    hist_ncoll[isys]->SetName(Form("%s_ncoll",sys.c_str()));

    for(int i=0;i<5;i++){
    	npart[isys][i]=hist_npart[isys]->GetBinContent(5-i);
    	npart_err[isys][i]=hist_npart[isys]->GetBinError(5-i);
    	ncoll[isys][i]=hist_ncoll[isys]->GetBinContent(5-i);
    	ncoll_err[isys][i]=hist_ncoll[isys]->GetBinError(5-i);

    	raw_spec[isys][i]=(TH1D*)file[isys]->Get(Form("%s_raw_spec_%i_%i",sys.c_str(),bins[i],bins[i+1]));
    	unfold_spec[isys][i]=(TH1D*)file[isys]->Get(Form("%s_unfolded_spec_%i_%i",sys.c_str(),bins[i],bins[i+1]));
    }
}

TH1D* pp_hist=hist_pp();
pp_hist->Scale(5./7.);

gStyle->SetPalette(kValentine);
gStyle->SetOptStat(0);
//gStyle->SetOptTitle(0);

TCanvas* c[8];
for(int isys=0;isys<2;isys++){
    
    string sys=isys?"zr":"ru";

//Raw
    c[isys]=new TCanvas(Form("c_%i",isys),"",700,600);
    c[isys]->SetLogy();
    c[isys]->SetLeftMargin(0.15);
    double raw_ymax=raw_spec[isys][0]->GetBinContent(4)*2;
    double raw_ymin=raw_spec[isys][4]->GetBinContent(nbins)/1250;
    TLegend* lg=new TLegend(0.6,0.6,0.9,0.9);
    TH1D* raw_copy[5];
    for(int i=0;i<5;i++){
	raw_copy[i]=(TH1D*)raw_spec[isys][i]->Clone();
    	raw_copy[i]->Scale(1.0/pow(5,i));
    
    	raw_copy[i]->GetXaxis()->SetRangeUser(0,30);
    	raw_copy[i]->GetYaxis()->SetRangeUser(raw_ymin,raw_ymax);
    	raw_copy[i]->SetTitle(Form("%s raw spectrum",sys.c_str()));
    	raw_copy[i]->SetXTitle("p_{T} (GeV/c)");
     	raw_copy[i]->SetYTitle("#frac{1}{2#pi p_{T} } #frac{d^{2} N}{d p_{T} d #eta}");
    	raw_copy[i]->SetLineWidth(2);
    	raw_copy[i]->Draw("same PLC PLM");
    	lg->AddEntry(raw_copy[i],i?Form("%i%%-%i%% / %i",bins[i],bins[i+1],(int)pow(5,i)):"0%-10%");
    }
    lg->Draw();

//Unfolded
    c[isys+2]=new TCanvas(Form("c_%i",isys+2),"",700,600);
    c[isys+2]->SetLogy();
    c[isys+2]->SetLeftMargin(0.15);
    double unfold_ymax=unfold_spec[isys][0]->GetBinContent(4)*2;
    double unfold_ymin=unfold_spec[isys][4]->GetBinContent(nbins-3)/1250;
    TLegend* lg_unfold=new TLegend(0.6,0.6,0.9,0.9);
    TH1D* unfold_copy[5];
    for(int i=0;i<5;i++){

    	unfold_copy[i]=(TH1D*)unfold_spec[isys][i]->Clone();
    	unfold_copy[i]->Scale(1.0/pow(5,i));
    	unfold_copy[i]->GetXaxis()->SetRangeUser(0,15);
    	unfold_copy[i]->GetYaxis()->SetRangeUser(unfold_ymin,unfold_ymax);
    	unfold_copy[i]->SetTitle(Form("%s unfolded spectrum",sys.c_str()));
    	unfold_copy[i]->SetXTitle("p_{T} (GeV/c)");
    	unfold_copy[i]->SetYTitle("#frac{1}{2#pi p_{T}} #frac{d^{2} N}{d p_{T} d #eta}");
    	unfold_copy[i]->SetLineWidth(2);
    	unfold_copy[i]->Draw("same PLC PLM");
    	lg_unfold->AddEntry(unfold_copy[i],i?Form("%i%%-%i%% / %i",bins[i],bins[i+1],(int)pow(5,i)):"0%-10%");

    }
    lg_unfold->Draw();


// Raa
    c[isys+4]=new TCanvas(Form("c_%i",isys+4),"",700,600);
    c[isys+4]->SetLeftMargin(0.15);
    TLegend* lg_raa=new TLegend(0.6,0.6,0.9,0.9);
    TH1D* unfold_raa[5];
    TGraphErrors* raa_sys[5];
    double xcent[nbins-8];
    double xerr[nbins-8];
    for(int i=4;i<=nbins-5;i++){
	xcent[i-4]=unfold_spec[isys][0]->GetBinCenter(i);
	xerr[i-4]=0;
    }
    for(int i=0;i<5;i++){

	double ycent[nbins-8],yerr[nbins-8];
    	unfold_raa[i]=(TH1D*)unfold_spec[isys][i]->Clone();
//    	unfold_raa[i]=(TH1D*)raw_spec[isys][i]->Clone();

    	unfold_raa[i]->SetName(Form("%s_raa_%i_%i",sys.c_str(),bins[i],bins[i+1]));
	cout<<"Ncoll= "<<ncoll[isys][i]<<endl; 
   	unfold_raa[i]->Scale(1.0/ncoll[isys][i]);
    	unfold_raa[i]->SetTitle(Form("%s+%s R_{AA}",sys.c_str(),sys.c_str()));
    	unfold_raa[i]->Divide(pp_hist);
    	unfold_raa[i]->GetXaxis()->SetRangeUser(0.4,10);
    	unfold_raa[i]->GetYaxis()->SetRangeUser(0.1,1.5);
	for(int j=4;j<=nbins-5;j++){
//	    ycent[j-4]=unfold_spec[isys][i]->GetBinContent(j)/pp_hist->GetBinContent(j-3);
	   ycent[j-4]=unfold_raa[i]->GetBinContent(j);
	   yerr[j-4]=unfold_raa[i]->GetBinError(j)/2;

	}
	raa_sys[i]=new TGraphErrors(nbins-8,xcent,ycent,xerr,yerr);
	unfold_raa[i]->SetXTitle("p_{T} (GeV/c)");
    	unfold_raa[i]->SetYTitle("R_{AA}");
    	unfold_raa[i]->SetLineWidth(2);
    	unfold_raa[i]->Draw("same e PLC PLM");
	raa_sys[i]->SetMarkerSize(2);
//	raa_sys[i]->DrawClone("same |> PLC PFC");
    	lg_raa->AddEntry(unfold_raa[i],Form("%i%%-%i%%",bins[i],bins[i+1]));

    }
    lg_raa->Draw();


// Rcp
    c[isys+6]=new TCanvas(Form("c_%i",isys+6),"",700,600);
    c[isys+6]->SetLeftMargin(0.15);
    TLegend* lg_rcp=new TLegend(0.15,0.1,0.4,0.3);
    TH1D* unfold_rcp[4];
    for(int i=0;i<4;i++){

    	unfold_rcp[i]=(TH1D*)unfold_spec[isys][i]->Clone();
    	unfold_rcp[i]->SetName(Form("%s_rcp_%i_%i",sys.c_str(),bins[i],bins[i+1]));
     	unfold_rcp[i]->Scale(ncoll[isys][4]/ncoll[isys][i]);
     	unfold_rcp[i]->SetTitle(Form("%s+%s R_{CP}",sys.c_str(),sys.c_str()));
    	unfold_rcp[i]->Divide(unfold_spec[isys][4]);
    	unfold_rcp[i]->GetXaxis()->SetRangeUser(0,15);
    	unfold_rcp[i]->GetYaxis()->SetRangeUser(0.1,1.2);
	
    	unfold_rcp[i]->SetXTitle("p_{T} (GeV/c)");
    	unfold_rcp[i]->SetYTitle("R_{CP}");
    	unfold_rcp[i]->SetLineWidth(2);
    	unfold_rcp[i]->Draw("same PLC PLM");
    	lg_rcp->AddEntry(unfold_rcp[i],Form("%i%%-%i%%",bins[i],bins[i+1]));

    }
    lg_rcp->Draw();


    c[isys]->SaveAs(Form("prelim_plots/%s_raw_spec.png",sys.c_str()));
    c[isys+2]->SaveAs(Form("prelim_plots/%s_unfold_spec.png",sys.c_str()));
    c[isys+4]->SaveAs(Form("prelim_plots/%s_raa.png",sys.c_str()));
    c[isys+6]->SaveAs(Form("prelim_plots/%s_rcp.png",sys.c_str()));
    }

double raa_5GeV[2][5],raa_err_5GeV[2][5];
double raa_xbins[4]={0,5.1,10,30};
double pp_buff=0,pp_err_buff=0;
for(int i=1;i<=nbins;i++){
    if(pp_hist->GetBinCenter(i)<5.1 || pp_hist->GetBinCenter(i)>10)continue;
//    cout<<pp_hist->GetBinCenter(i)<<endl;
     pp_buff+=(pp_hist->GetBinContent(i)*pp_hist->GetBinWidth(i));	    
     pp_err_buff+=pow(pp_hist->GetBinError(i)*pp_hist->GetBinWidth(i),2);	    
}



TGraphErrors* integrated_raa[2];

for(int isys=0;isys<2;isys++){
   for(int i=0;i<5;i++){
	double isobar_buff=0,isobar_err_buff=0;	
	for(int j=1;j<=nbins;j++){
	    if(unfold_spec[isys][i]->GetBinCenter(j)<5.1 || unfold_spec[isys][i]->GetBinCenter(j)>10)continue;
	    isobar_buff+=unfold_spec[isys][i]->GetBinContent(j)*unfold_spec[isys][i]->GetBinWidth(j);
	    isobar_err_buff+=pow(unfold_spec[isys][i]->GetBinError(j)*unfold_spec[isys][i]->GetBinWidth(j),2);
	    
	}
	isobar_buff/=ncoll[isys][i];
	isobar_err_buff/=pow(ncoll[isys][i],2);
	raa_5GeV[isys][i]=isobar_buff/pp_buff;
	cout<<(isys?"zr\t":"ru\t")<<npart[isys][i]<<"\t"<<raa_5GeV[isys][i]<<endl;


	raa_err_5GeV[isys][i]=sqrt(isobar_err_buff/(isobar_buff*isobar_buff)+pp_err_buff/(pp_buff*pp_buff));
	raa_err_5GeV[isys][i]*=raa_5GeV[isys][i];

    }

    integrated_raa[isys]=new TGraphErrors(5,npart[isys],raa_5GeV[isys],npart_err[isys],raa_err_5GeV[isys]);
}

TH1D** auau_hist=hist_auau();


double auau_mod_5GeV[6],auau_err_5GeV[6];

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

//    cout<<auau_mod_5GeV[raabin]<<endl;

    auau_err_5GeV[raabin]=sqrt(err_buff/(raa_buff*raa_buff)+pp_err_buff/(pp_buff*pp_buff));
    auau_err_5GeV[raabin]*=auau_mod_5GeV[raabin];

//    cout<<raabin<<"\t"<<auau_npart[raabin]<<"\t"<<auau_npart_err[raabin]<<"\t"<<auau_mod_5GeV[raabin]<<"\t"<<auau_err_5GeV[raabin]<<endl;
    }


TCanvas* c_raa=new TCanvas("c_raa","",900,600);
c_raa->SetLogx();
TGraphErrors* mod_auau=new TGraphErrors(6,auau_npart,auau_mod_5GeV,auau_npart_err,auau_err_5GeV);
mod_auau->SetLineColor(kOrange+2);
mod_auau->GetXaxis()->SetTitle("N_{part}");
mod_auau->GetXaxis()->SetRangeUser(0.1,400);
mod_auau->GetYaxis()->SetTitle("R_{AA}");
mod_auau->SetTitle("Inclusive hadron R_{AA} for 5.1 < p_{T} < 10 GeV");
mod_auau->SetMarkerStyle(22);
integrated_raa[0]->SetLineColor(kBlue);//Ru
integrated_raa[1]->SetLineColor(kRed);//Zr
integrated_raa[0]->SetMarkerStyle(29);
integrated_raa[1]->SetMarkerStyle(29);
integrated_raa[0]->SetMarkerColor(kBlue);
integrated_raa[1]->SetMarkerColor(kRed);
mod_auau->Draw("ap");
integrated_raa[0]->Draw("samep");
integrated_raa[1]->Draw("samep");

TGraphErrors* phenix_pi=phenix_pion();
phenix_pi->SetMarkerStyle(23);
phenix_pi->SetLineColor(kGreen+1);
phenix_pi->Draw("samep");
float width=2;
mod_auau->SetLineWidth(width);
integrated_raa[0]->SetLineWidth(width);
integrated_raa[1]->SetLineWidth(width);
phenix_pi->SetLineWidth(width);

TLegend* lg_compare=new TLegend(0.6,0.6,0.9,0.9);
lg_compare->AddEntry(mod_auau,"STAR Au+Au #frac{h^{+}+h^{-}}{2}");
lg_compare->AddEntry(integrated_raa[0],"STAR Ru+Ru #frac{h^{+}+h^{-}}{2}");
lg_compare->AddEntry(integrated_raa[1],"STAR Zr+Zr #frac{h^{+}+h^{-}}{2}");
lg_compare->AddEntry(phenix_pi,"PHENIX U+U 192 GeV #pi^{0}->#gamma#gamma");
lg_compare->Draw();

TH1D* plot_displace=(TH1D*)unfold_spec[0][0]->Clone();
for(int i=1;i<=plot_displace->GetNbinsX();i++){
    plot_displace->SetBinContent(i,-0.2);
    plot_displace->SetBinError(i,0);
}
TCanvas* ru_vs_zr=new TCanvas("ru_vs_zr","",700,1000);
TH1D* species_ratio[5];
TLegend* lg_ratio=new TLegend(0.6,0.7,0.9,0.9);
for(int i=0;i<5;i++){
    species_ratio[i]=(TH1D*)unfold_spec[0][i]->Clone();
    species_ratio[i]->Divide(unfold_spec[1][i]);
    species_ratio[i]->Add(plot_displace,i);
    species_ratio[i]->GetXaxis()->SetRangeUser(0,20);
    species_ratio[i]->GetYaxis()->SetRangeUser(0,1.5);
    species_ratio[i]->SetXTitle("p_{T}");
    species_ratio[i]->SetTitle("Ru/Zr w/out Nbin scaling");
    species_ratio[i]->Draw("same PLC PLM");
    lg_ratio->AddEntry(species_ratio[i],Form("%i%%_%i%%",bins[i],bins[i+1]));
}



TCanvas* ru_zr_nbin=new TCanvas("ru_zr_nbin","",700,1000);
TH1D* ratio_nbin[5];
for(int i=0;i<5;i++){
    ratio_nbin[i]=(TH1D*)unfold_spec[0][i]->Clone();
    ratio_nbin[i]->Divide(unfold_spec[1][i]);
    ratio_nbin[i]->Scale(ncoll[1][i]/ncoll[0][i]);
    ratio_nbin[i]->Add(plot_displace,i);
    ratio_nbin[i]->GetXaxis()->SetRangeUser(0,20);
    ratio_nbin[i]->GetYaxis()->SetRangeUser(0,1.2);
    ratio_nbin[i]->SetXTitle("p_{T}");
    ratio_nbin[i]->SetTitle("Ru/Zr with Nbin scaling");
    ratio_nbin[i]->Draw("same PLC PLM");
}
ru_vs_zr->SaveAs("prelim_plots/ru_vs_zr.png");
ru_zr_nbin->SaveAs("prelim_plots/ru_vs_zr_nbin.png");

}
