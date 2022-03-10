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

for(int i=0;i<5;i++){
    ru_raw_spec[i]=(TH1D*)ru_file->Get(Form("ru_raw_spec_%i_%i",bins[i],bins[i+1]));
    zr_raw_spec[i]=(TH1D*)zr_file->Get(Form("zr_raw_spec_%i_%i",bins[i],bins[i+1]));
    ru_unfold_spec[i]=(TH1D*)ru_file->Get(Form("ru_unfolded_spec_%i_%i",bins[i],bins[i+1]));
    zr_unfold_spec[i]=(TH1D*)zr_file->Get(Form("zr_unfolded_spec_%i_%i",bins[i],bins[i+1]));
}

TCanvas* c1=new TCanvas("c1","",600,600);
gStyle->SetPalette(kValentine);
gStyle->SetOptStat(0);
gStyle->SetOptTitle(0);
c1->SetLogy();
TH1D* plot_displace=(TH1D*)ru_unfold_spec[0]->Clone();
for(int i=1;i<=plot_displace->GetNbinsX();i++){
    plot_displace->SetBinContent(i,-0.2);
    plot_displace->SetBinError(i,0);
}
TLegend* lg=new TLegend();
for(int i=0;i<1;i++){
//    ru_raw_spec[i]->Add(zr_raw_spec[i]);
//    ru_raw_spec[4]->Add(zr_raw_spec[4]);
    ru_raw_spec[i]->Divide(ru_raw_spec[4]);
//    zr_raw_spec[i]->Scale(1.0/pow(5,i));
    ru_raw_spec[i]->Add(plot_displace,i);
    ru_raw_spec[i]->GetXaxis()->SetRangeUser(0,30);
    ru_raw_spec[i]->SetLineWidth(2);

    ru_raw_spec[i]->Draw("same PLC PLM");
    lg->AddEntry(ru_raw_spec[i],Form("%i%%_%i%%",bins[i],bins[i+1]));

}
lg->Draw();

}
