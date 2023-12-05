void raw_rcp(){
const string system[2]={"ru","zr"};
TH1F* rcp[2];

int colors[2]={1,2};
TLegend* lg=new TLegend();
for(int i=0;i<2;i++){
  TFile* input=new TFile(Form("outhist_%s_2_3_5bin.root",system[i].c_str()));
  rcp[i]=(TH1F*)input->Get(Form("%s_raw_spec_10_20",system[i].c_str()));
  TH1F* peri=(TH1F*)input->Get(Form("%s_raw_spec_60_80",system[i].c_str()));
  TH1F* ncoll=(TH1F*)input->Get(Form("%s_ncoll",system[i].c_str()));

  float factor=ncoll->GetBinContent(1)/ncoll->GetBinContent(4);
  rcp[i]->Divide(peri);
  rcp[i]->Scale(factor);
  rcp[i]->SetLineWidth(2);
  rcp[i]->SetLineColor(colors[i]);
  lg->AddEntry(rcp[i],system[i].c_str());
  rcp[i]->Draw("same");
}
lg->Draw();
}
