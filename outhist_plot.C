#include "../pp_reference/hist_pp.h"
void outhist_plot(
const char* ru_name="outhist_ru.root",
const char* zr_name="outhist_zr.root"
){

const int bins[6]={0,10,20,40,60,80};

TFile* ru_file=new TFile(ru_name);
TFile* zr_file=new TFile(zr_name);

TH1D* ru_raw_spec[5];
TH1D* zr_raw_spec[5];

TH1D* ru_unfold_spec[5];
TH1D* zr_unfold_spec[5];

TH1D *ru_npart,*ru_ncoll,*zr_npart,*zr_ncoll;

ru_npart=(TH1D*)ru_file->Get("npart");
ru_ncoll=(TH1D*)ru_file->Get("ncoll");
ru_npart->SetName("ru_npart");
ru_ncoll->SetName("ru_ncoll");

zr_npart=(TH1D*)zr_file->Get("npart");
zr_ncoll=(TH1D*)zr_file->Get("ncoll");
zr_npart->SetName("zr_npart");
zr_ncoll->SetName("zr_ncoll");

double npart_ru[5],npart_err_ru[5],ncoll_ru[5],ncoll_err_ru[5];
double npart_zr[5],npart_err_zr[5],ncoll_zr[5],ncoll_err_zr[5];

for(int i=0;i<5;i++){
    npart_ru[i]=ru_npart->GetBinContent(5-i);
    npart_err_ru[i]=ru_npart->GetBinError(5-i);
    ncoll_ru[i]=ru_ncoll->GetBinContent(5-i);
    ncoll_err_ru[i]=ru_ncoll->GetBinError(5-i);
    
    npart_zr[i]=zr_npart->GetBinContent(5-i);
    npart_err_zr[i]=zr_npart->GetBinError(5-i);
    ncoll_zr[i]=zr_ncoll->GetBinContent(5-i);
    ncoll_err_zr[i]=zr_ncoll->GetBinError(5-i);
}

for(int i=0;i<5;i++){
    ru_raw_spec[i]=(TH1D*)ru_file->Get(Form("ru_raw_spec_%i_%i",bins[i],bins[i+1]));
    zr_raw_spec[i]=(TH1D*)zr_file->Get(Form("zr_raw_spec_%i_%i",bins[i],bins[i+1]));
    ru_unfold_spec[i]=(TH1D*)ru_file->Get(Form("ru_unfolded_spec_%i_%i",bins[i],bins[i+1]));
    zr_unfold_spec[i]=(TH1D*)zr_file->Get(Form("zr_unfolded_spec_%i_%i",bins[i],bins[i+1]));
    ru_raw_spec[i]->Scale(1./4);
    zr_raw_spec[i]->Scale(1./4);
    ru_unfold_spec[i]->Scale(1./4);
    zr_unfold_spec[i]->Scale(1./4);
}
TH1D* pp_hist=hist_pp();

TH1D* plot_displace=(TH1D*)ru_unfold_spec[0]->Clone();
for(int i=1;i<=plot_displace->GetNbinsX();i++){
    plot_displace->SetBinContent(i,-0.2);
    plot_displace->SetBinError(i,0);
}

gStyle->SetPalette(kValentine);
gStyle->SetOptStat(0);
//gStyle->SetOptTitle(0);

//Ru+Ru Raw
TCanvas* c1=new TCanvas("c1","",700,600);
c1->SetLogy();
c1->SetLeftMargin(0.15);
double ruraw_ymax=ru_raw_spec[0]->GetBinContent(4)*2;
//int nbins=ru_raw_spec[4]->GetNbinsX();
double ruraw_ymin=ru_raw_spec[4]->GetBinContent(nbins)/1250;
TLegend* lg=new TLegend(0.6,0.6,0.9,0.9);
for(int i=0;i<5;i++){
//    ru_raw_spec[i]->Add(zr_raw_spec[i]);
//    ru_raw_spec[4]->Add(zr_raw_spec[4]);
//    ru_raw_spec[i]->Divide(ru_raw_spec[4]);
    ru_raw_spec[i]->Scale(1.0/pow(5,i));
    
//    ru_raw_spec[i]->Add(plot_displace,i);
    ru_raw_spec[i]->GetXaxis()->SetRangeUser(0,30);
    ru_raw_spec[i]->GetYaxis()->SetRangeUser(ruraw_ymin,ruraw_ymax);
    ru_raw_spec[i]->SetTitle("Ru raw spectrum");
    ru_raw_spec[i]->SetXTitle("p_{T} (GeV/c)");
//    ru_raw_spec[i]->SetYTitle("#frac{1}{N_{ev}} #frac{d^{2} N}{2#pi p_{T} d p_{T} d #eta}");
    ru_raw_spec[i]->SetYTitle("#frac{1}{2#pi p_{T} } #frac{d^{2} N}{d p_{T} d #eta}");
    ru_raw_spec[i]->SetLineWidth(2);
    ru_raw_spec[i]->Draw("same PLC PLM");
    lg->AddEntry(ru_raw_spec[i],i?Form("%i%%-%i%% / %i",bins[i],bins[i+1],(int)pow(5,i)):"0%-10%");
}
lg->Draw();

//Zr+Zr Raw
TCanvas* c2=new TCanvas("c2","",700,600);
c2->SetLogy();
c2->SetLeftMargin(0.15);
double zrraw_ymax=zr_raw_spec[0]->GetBinContent(4)*2;
//int nbins=ru_raw_spec[4]->GetNbinsX();
double zrraw_ymin=zr_raw_spec[4]->GetBinContent(nbins)/1250;
TLegend* lg_zr=new TLegend(0.6,0.6,0.9,0.9);
for(int i=0;i<5;i++){
    zr_raw_spec[i]->Scale(1.0/pow(5,i));
    zr_raw_spec[i]->GetXaxis()->SetRangeUser(0,30);
    zr_raw_spec[i]->GetYaxis()->SetRangeUser(zrraw_ymin,zrraw_ymax);
    zr_raw_spec[i]->SetTitle("Zr raw spectrum");
    zr_raw_spec[i]->SetXTitle("p_{T} (GeV/c)");
//    ru_raw_spec[i]->SetYTitle("#frac{1}{N_{ev}} #frac{d^{2} N}{2#pi p_{T} d p_{T} d #eta}");
    zr_raw_spec[i]->SetYTitle("#frac{1}{2#pi p_{T} }  #frac{d^{2} N}{d p_{T} d #eta}");

    zr_raw_spec[i]->SetLineWidth(2);
    zr_raw_spec[i]->Draw("same PLC PLM");
    lg_zr->AddEntry(zr_raw_spec[i],i?Form("%i%%-%i%% / %i",bins[i],bins[i+1],(int)pow(5,i)):"0%-10%");

}
lg_zr->Draw();

//Ru+Ru unfolded
TCanvas* c3=new TCanvas("c3","",700,600);
c3->SetLogy();
c3->SetLeftMargin(0.15);
double ruunfold_ymax=ru_unfold_spec[0]->GetBinContent(4)*2;
//int nbins=ru_raw_spec[4]->GetNbinsX();
double ruunfold_ymin=ru_unfold_spec[4]->GetBinContent(nbins-3)/1250;
TLegend* lg_ru_unfold=new TLegend(0.6,0.6,0.9,0.9);
TH1D* ru_unfold_copy[5];
for(int i=0;i<5;i++){

    ru_unfold_copy[i]=(TH1D*)ru_unfold_spec[i]->Clone();
    ru_unfold_copy[i]->Scale(1.0/pow(5,i));
    ru_unfold_copy[i]->GetXaxis()->SetRangeUser(0,15);
    ru_unfold_copy[i]->GetYaxis()->SetRangeUser(ruunfold_ymin,ruunfold_ymax);
    ru_unfold_copy[i]->SetTitle("Ru unfolded spectrum");
    ru_unfold_copy[i]->SetXTitle("p_{T} (GeV/c)");
    ru_unfold_copy[i]->SetYTitle("#frac{1}{2#pi p_{T}} #frac{d^{2} N}{d p_{T} d #eta}");
    ru_unfold_copy[i]->SetLineWidth(2);
    ru_unfold_copy[i]->Draw("same PLC PLM");
    lg_ru_unfold->AddEntry(ru_unfold_copy[i],i?Form("%i%%-%i%% / %i",bins[i],bins[i+1],(int)pow(5,i)):"0%-10%");

}
lg_ru_unfold->Draw();

//Zr+Zr unfolded
TCanvas* c4=new TCanvas("c4","",700,600);
c4->SetLogy();
c4->SetLeftMargin(0.15);
double zrunfold_ymax=zr_unfold_spec[0]->GetBinContent(4)*2;
double zrunfold_ymin=zr_unfold_spec[4]->GetBinContent(nbins-3)/1250;
TLegend* lg_zr_unfold=new TLegend(0.6,0.6,0.9,0.9);
TH1D* zr_unfold_copy[5];
for(int i=0;i<5;i++){

    zr_unfold_copy[i]=(TH1D*)zr_unfold_spec[i]->Clone();
    zr_unfold_copy[i]->SetName(Form("zr_unfold_spec_%i_%i",bins[i],bins[i+1]));
    zr_unfold_copy[i]->Scale(1.0/pow(5,i));
    zr_unfold_copy[i]->GetXaxis()->SetRangeUser(0,15);
    zr_unfold_copy[i]->GetYaxis()->SetRangeUser(zrunfold_ymin,zrunfold_ymax);
    zr_unfold_copy[i]->SetTitle("Zr unfolded spectrum");
    zr_unfold_copy[i]->SetXTitle("p_{T} (GeV/c)");
    zr_unfold_copy[i]->SetYTitle("#frac{1}{2#pi p_{T}} #frac{d^{2} N}{d p_{T} d #eta}");
    zr_unfold_copy[i]->SetLineWidth(2);
    zr_unfold_copy[i]->Draw("same PLC PLM");
    lg_zr_unfold->AddEntry(zr_unfold_copy[i],i?Form("%i%%-%i%% / %i",bins[i],bins[i+1],(int)pow(5,i)):"0%-10%");

}
lg_zr_unfold->Draw();

//Ru+Ru Raa
TCanvas* c5=new TCanvas("c5","",700,600);
c5->SetLeftMargin(0.15);
//double zrunfold_ymax=zr_unfold_spec[0]->GetBinContent(4)*2;
//double zrunfold_ymin=zr_unfold_spec[4]->GetBinContent(nbins-3)/1250;
TLegend* lg_ru_raa=new TLegend(0.6,0.6,0.9,0.9);
TH1D* ru_unfold_raa[5];
for(int i=0;i<5;i++){

    ru_unfold_raa[i]=(TH1D*)ru_unfold_spec[i]->Clone();
    ru_unfold_raa[i]->SetName(Form("ru_raa_%i_%i",bins[i],bins[i+1]));
    ru_unfold_raa[i]->Scale(1.0/ncoll_ru[i]);
    ru_unfold_raa[i]->SetTitle("Ru+Ru R_{AA}");
    ru_unfold_raa[i]->Divide(pp_hist);
    ru_unfold_raa[i]->GetXaxis()->SetRangeUser(0.4,10);
    ru_unfold_raa[i]->GetYaxis()->SetRangeUser(0.1,1.2);

    ru_unfold_raa[i]->SetXTitle("p_{T} (GeV/c)");
    ru_unfold_raa[i]->SetYTitle("R_{AA}");
    ru_unfold_raa[i]->SetLineWidth(2);
    ru_unfold_raa[i]->Draw("same PLC PLM");
    lg_ru_raa->AddEntry(ru_unfold_raa[i],Form("%i%%-%i%%",bins[i],bins[i+1]));

}
lg_ru_raa->Draw();


//Zr+Zr Raa
TCanvas* c6=new TCanvas("c6","",700,600);
c6->SetLeftMargin(0.15);
//double zrunfold_ymax=zr_unfold_spec[0]->GetBinContent(4)*2;
//double zrunfold_ymin=zr_unfold_spec[4]->GetBinContent(nbins-3)/1250;
TLegend* lg_zr_raa=new TLegend(0.6,0.6,0.9,0.9);
TH1D* zr_unfold_raa[5];
for(int i=0;i<5;i++){

    zr_unfold_raa[i]=(TH1D*)zr_unfold_spec[i]->Clone();
    zr_unfold_raa[i]->SetName(Form("zr_raa_%i_%i",bins[i],bins[i+1]));
    zr_unfold_raa[i]->Scale(1./ncoll_zr[i]);
    zr_unfold_raa[i]->SetTitle("Zr+Zr R_{AA}");
    zr_unfold_raa[i]->Divide(pp_hist);
    zr_unfold_raa[i]->GetXaxis()->SetRangeUser(0.4,10);
    zr_unfold_raa[i]->GetYaxis()->SetRangeUser(0.1,1.2);

    zr_unfold_raa[i]->SetXTitle("p_{T} (GeV/c)");
    zr_unfold_raa[i]->SetYTitle("R_{AA}");
    zr_unfold_raa[i]->SetLineWidth(2);
    zr_unfold_raa[i]->Draw("same PLC PLM");
    lg_zr_raa->AddEntry(zr_unfold_raa[i],Form("%i%%-%i%%",bins[i],bins[i+1]));

}
lg_zr_raa->Draw();


//Ru+Ru Rcp
TCanvas* c7=new TCanvas("c7","",700,600);
c7->SetLeftMargin(0.15);
//double ruunfold_ymax=ru_unfold_spec[0]->GetBinContent(4)*2;
//double ruunfold_ymin=ru_unfold_spec[4]->GetBinContent(nbins-3)/1250;
TLegend* lg_ru_rcp=new TLegend(0.15,0.1,0.4,0.3);
TH1D* ru_unfold_rcp[4];
for(int i=0;i<4;i++){

    ru_unfold_rcp[i]=(TH1D*)ru_unfold_spec[i]->Clone();
    ru_unfold_rcp[i]->SetName(Form("ru_rcp_%i_%i",bins[i],bins[i+1]));
    ru_unfold_rcp[i]->Scale(ncoll_ru[4]/ncoll_ru[i]);
    ru_unfold_rcp[i]->SetTitle("Ru+Ru R_{CP}");
    ru_unfold_rcp[i]->Divide(ru_unfold_spec[4]);
    ru_unfold_rcp[i]->GetXaxis()->SetRangeUser(0,15);
    ru_unfold_rcp[i]->GetYaxis()->SetRangeUser(0.1,1.2);

    ru_unfold_rcp[i]->SetXTitle("p_{T} (GeV/c)");
    ru_unfold_rcp[i]->SetYTitle("R_{CP}");
    ru_unfold_rcp[i]->SetLineWidth(2);
    ru_unfold_rcp[i]->Draw("same PLC PLM");
    lg_ru_rcp->AddEntry(ru_unfold_rcp[i],Form("%i%%-%i%%",bins[i],bins[i+1]));

}
lg_ru_rcp->Draw();


//Zr+Zr Rcp
TCanvas* c8=new TCanvas("c8","",700,600);
c8->SetLeftMargin(0.15);
//double zrunfold_ymax=zr_unfold_spec[0]->GetBinContent(4)*2;
//double zrunfold_ymin=zr_unfold_spec[4]->GetBinContent(nbins-3)/1250;
TLegend* lg_zr_rcp=new TLegend(0.15,0.1,0.4,0.3);
TH1D* zr_unfold_rcp[4];
for(int i=0;i<4;i++){

    zr_unfold_rcp[i]=(TH1D*)zr_unfold_spec[i]->Clone();
    zr_unfold_rcp[i]->SetName(Form("zr_rcp_%i_%i",bins[i],bins[i+1]));
    zr_unfold_rcp[i]->Scale(ncoll_zr[4]/ncoll_zr[i]);
    zr_unfold_rcp[i]->SetTitle("Zr+Zr R_{CP}");
    zr_unfold_rcp[i]->Divide(zr_unfold_spec[4]);
    zr_unfold_rcp[i]->GetXaxis()->SetRangeUser(0,15);
    zr_unfold_rcp[i]->GetYaxis()->SetRangeUser(0.1,1.2);

    zr_unfold_rcp[i]->SetXTitle("p_{T} (GeV/c)");
    zr_unfold_rcp[i]->SetYTitle("R_{CP}");
    zr_unfold_rcp[i]->SetLineWidth(2);
    zr_unfold_rcp[i]->Draw("same PLC PLM");
    lg_zr_rcp->AddEntry(zr_unfold_rcp[i],Form("%i%%-%i%%",bins[i],bins[i+1]));

}
lg_zr_rcp->Draw();

c1->SaveAs("prelim_plots/Ru_raw_spec.png");
c2->SaveAs("prelim_plots/Zr_raw_spec.png");
c3->SaveAs("prelim_plots/Ru_unfold_spec.png");
c4->SaveAs("prelim_plots/Zr_unfold_spec.png");
c5->SaveAs("prelim_plots/Ru_raa.png");
c6->SaveAs("prelim_plots/Zr_raa.png");
c7->SaveAs("prelim_plots/Ru_rcp.png");
c8->SaveAs("prelim_plots/Zr_rcp.png");


}
