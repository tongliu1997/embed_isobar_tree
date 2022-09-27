void raa_summary_5bin()
{
//=========Macro generated from canvas: compile_raa/
//=========  (Mon Apr  4 20:04:25 2022) by ROOT version 6.22/06
   TCanvas *compile_raa = new TCanvas("compile_raa", "",151,53,1000,800);
   gStyle->SetOptStat(0);
   compile_raa->Range(0.5536662,-0.25,2.798516,2.25);
   compile_raa->SetFillColor(0);
   compile_raa->SetBorderMode(0);
   compile_raa->SetBorderSize(2);
   compile_raa->SetLogx();
   compile_raa->SetFrameBorderMode(0);
   compile_raa->SetFrameBorderMode(0);
   
   TH1D *comp_dummy__1 = new TH1D("comp_dummy__1","",200,6,375);
   comp_dummy__1->SetMinimum(0);
   comp_dummy__1->SetMaximum(2);
   comp_dummy__1->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   comp_dummy__1->SetLineColor(ci);
   comp_dummy__1->GetXaxis()->SetTitle("#LT N_{part} #GT");
   comp_dummy__1->GetXaxis()->SetRange(1,200);
   comp_dummy__1->GetXaxis()->SetLabelFont(42);
   comp_dummy__1->GetXaxis()->SetLabelSize(0.04);
   comp_dummy__1->GetXaxis()->SetTitleSize(0.06);
   comp_dummy__1->GetXaxis()->SetTitleOffset(0.6);
   comp_dummy__1->GetXaxis()->SetTitleFont(42);
   comp_dummy__1->GetYaxis()->SetTitle("R_{AA}");
   comp_dummy__1->GetYaxis()->SetLabelFont(42);
   comp_dummy__1->GetYaxis()->SetLabelSize(0.04);
   comp_dummy__1->GetYaxis()->SetTitleSize(0.06);
   comp_dummy__1->GetYaxis()->SetTitleOffset(0.65);
   comp_dummy__1->GetYaxis()->SetTitleFont(42);
   comp_dummy__1->GetZaxis()->SetLabelFont(42);
   comp_dummy__1->GetZaxis()->SetTitleOffset(1);
   comp_dummy__1->GetZaxis()->SetTitleFont(42);
   comp_dummy__1->Draw("");
   TLatex *   tex = new TLatex(0.45,0.24,"STAR #bf{#it{Preliminary}}");
tex->SetNDC();
   tex->SetTextAlign(23);
   tex->SetTextSize(0.04);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.45,0.2,"#bf{Isobar #sqrt{s_{NN}}=200 GeV}");
tex->SetNDC();
   tex->SetTextAlign(23);
   tex->SetTextSize(0.04);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.45,0.15,"#bf{(h^{+}+h^{-})/2  p_{T} > 5.1 GeV/#it{c}}");
tex->SetNDC();
   tex->SetTextAlign(23);
   tex->SetTextSize(0.04);
   tex->SetLineWidth(2);
   tex->Draw();
   TBox *box = new TBox(355,0.8634033,375,1.136597);
   box->SetFillColor(15);
   box->SetLineColor(15);
   box->Draw();
   
   TLegend *leg = new TLegend(0.12,0.7,0.35,0.85,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("Graph","Ru+Ru","lpf");
   entry->SetFillStyle(1000);

   ci = TColor::GetColor("#0000ff");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(3);

   ci = TColor::GetColor("#0000ff");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(2);
   entry->SetTextFont(42);
   entry=leg->AddEntry("Graph","Zr+Zr","lpf");
   entry->SetFillStyle(1000);

   ci = TColor::GetColor("#ff0000");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(3);

   ci = TColor::GetColor("#ff0000");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(2);
   entry->SetTextFont(42);
   entry=leg->AddEntry("TBox","pp uncertainty","f");
   entry->SetFillColor(15);
   entry->SetFillStyle(1001);
   entry->SetLineColor(15);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
   
   Double_t Graph0_fx1001[5] = {
   157.2265,
   116.3919,
   71.1642,
   32.69326,
   12.56275};
   Double_t Graph0_fy1001[5] = {
   0.4578087,
   0.5453024,
   0.6895866,
   0.8804518,
   0.9024313};
   Double_t Graph0_fex1001[5] = {
   4.716795,
   3.491756,
   2.134926,
   0.9807978,
   0.3768826};
   Double_t Graph0_fey1001[5] = {
   0.02553233,
   0.02895309,
   0.03556974,
   0.04483068,
   0.04607924};
   TGraphErrors *gre = new TGraphErrors(5,Graph0_fx1001,Graph0_fy1001,Graph0_fex1001,Graph0_fey1001);
   gre->SetName("Graph0");
   gre->SetTitle("Graph");

   ci = 1448;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#0000ff");
   gre->SetLineColor(ci);
   gre->SetMarkerSize(0);
   
   TH1F *Graph_Graph01001 = new TH1F("Graph_Graph01001","Graph",100,10.96728,176.919);
   Graph_Graph01001->SetMinimum(0.3806529);
   Graph_Graph01001->SetMaximum(1.000134);
   Graph_Graph01001->SetDirectory(0);
   Graph_Graph01001->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph01001->SetLineColor(ci);
   Graph_Graph01001->GetXaxis()->SetLabelFont(42);
   Graph_Graph01001->GetXaxis()->SetTitleOffset(1);
   Graph_Graph01001->GetXaxis()->SetTitleFont(42);
   Graph_Graph01001->GetYaxis()->SetLabelFont(42);
   Graph_Graph01001->GetYaxis()->SetTitleFont(42);
   Graph_Graph01001->GetZaxis()->SetLabelFont(42);
   Graph_Graph01001->GetZaxis()->SetTitleOffset(1);
   Graph_Graph01001->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph01001);
   
   gre->Draw("s=0.5 ");
   
   Double_t Graph1_fx1002[5] = {
   156.2169,
   114.8801,
   69.05626,
   31.31929,
   11.74879};
   Double_t Graph1_fy1002[5] = {
   0.4565197,
   0.5467488,
   0.6957025,
   0.8937189,
   0.8975997};
   Double_t Graph1_fex1002[5] = {
   4.686508,
   3.446404,
   2.071688,
   0.9395787,
   0.3524638};
   Double_t Graph1_fey1002[5] = {
   0.02540654,
   0.02897733,
   0.03579431,
   0.04547026,
   0.04592883};
   gre = new TGraphErrors(5,Graph1_fx1002,Graph1_fy1002,Graph1_fex1002,Graph1_fey1002);
   gre->SetName("Graph1");
   gre->SetTitle("Graph");

   ci = 1449;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#ff0000");
   gre->SetLineColor(ci);
   gre->SetMarkerSize(0);
   
   TH1F *Graph_Graph11002 = new TH1F("Graph_Graph11002","Graph",100,10.2567,175.8542);
   Graph_Graph11002->SetMinimum(0.3798716);
   Graph_Graph11002->SetMaximum(0.99477);
   Graph_Graph11002->SetDirectory(0);
   Graph_Graph11002->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph11002->SetLineColor(ci);
   Graph_Graph11002->GetXaxis()->SetLabelFont(42);
   Graph_Graph11002->GetXaxis()->SetTitleOffset(1);
   Graph_Graph11002->GetXaxis()->SetTitleFont(42);
   Graph_Graph11002->GetYaxis()->SetLabelFont(42);
   Graph_Graph11002->GetYaxis()->SetTitleFont(42);
   Graph_Graph11002->GetZaxis()->SetLabelFont(42);
   Graph_Graph11002->GetZaxis()->SetTitleOffset(1);
   Graph_Graph11002->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph11002);
   
   gre->Draw("s=0.5 ");
   
   Double_t Graph2_fx1003[5] = {
   157.2265,
   116.3919,
   71.1642,
   32.69326,
   12.56275};
   Double_t Graph2_fy1003[5] = {
   0.4578087,
   0.5453024,
   0.6895866,
   0.8804518,
   0.9024313};
   Double_t Graph2_fex1003[5] = {
   0.5489803,
   0.8433531,
   0.3760035,
   0.1117199,
   0.02881961};
   Double_t Graph2_fey1003[5] = {
   0.002606534,
   0.003682333,
   0.004095138,
   0.006413092,
   0.01051374};
   gre = new TGraphErrors(5,Graph2_fx1003,Graph2_fy1003,Graph2_fex1003,Graph2_fey1003);
   gre->SetName("Graph2");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#0000ff");
   gre->SetLineColor(ci);
   gre->SetLineWidth(3);

   ci = TColor::GetColor("#0000ff");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(21);
   gre->SetMarkerSize(2);
   
   TH1F *Graph_Graph21003 = new TH1F("Graph_Graph21003","Graph",100,11.28054,172.2996);
   Graph_Graph21003->SetMinimum(0.4094279);
   Graph_Graph21003->SetMaximum(0.9587193);
   Graph_Graph21003->SetDirectory(0);
   Graph_Graph21003->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph21003->SetLineColor(ci);
   Graph_Graph21003->GetXaxis()->SetLabelFont(42);
   Graph_Graph21003->GetXaxis()->SetTitleOffset(1);
   Graph_Graph21003->GetXaxis()->SetTitleFont(42);
   Graph_Graph21003->GetYaxis()->SetLabelFont(42);
   Graph_Graph21003->GetYaxis()->SetTitleFont(42);
   Graph_Graph21003->GetZaxis()->SetLabelFont(42);
   Graph_Graph21003->GetZaxis()->SetTitleOffset(1);
   Graph_Graph21003->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph21003);
   
   gre->Draw("p");
   
   Double_t Graph3_fx1004[5] = {
   156.2169,
   114.8801,
   69.05626,
   31.31929,
   11.74879};
   Double_t Graph3_fy1004[5] = {
   0.4565197,
   0.5467488,
   0.6957025,
   0.8937189,
   0.8975997};
   Double_t Graph3_fex1004[5] = {
   0.5343558,
   0.7873273,
   0.346641,
   0.09220326,
   0.04061752};
   Double_t Graph3_fey1004[5] = {
   0.002524438,
   0.003600194,
   0.004041714,
   0.006423558,
   0.009963541};
   gre = new TGraphErrors(5,Graph3_fx1004,Graph3_fy1004,Graph3_fex1004,Graph3_fey1004);
   gre->SetName("Graph3");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#ff0000");
   gre->SetLineColor(ci);
   gre->SetLineWidth(3);

   ci = TColor::GetColor("#ff0000");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(2);
   
   TH1F *Graph_Graph31004 = new TH1F("Graph_Graph31004","Graph",100,10.53736,171.2556);
   Graph_Graph31004->SetMinimum(0.4086385);
   Graph_Graph31004->SetMaximum(0.95292);
   Graph_Graph31004->SetDirectory(0);
   Graph_Graph31004->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph31004->SetLineColor(ci);
   Graph_Graph31004->GetXaxis()->SetLabelFont(42);
   Graph_Graph31004->GetXaxis()->SetTitleOffset(1);
   Graph_Graph31004->GetXaxis()->SetTitleFont(42);
   Graph_Graph31004->GetYaxis()->SetLabelFont(42);
   Graph_Graph31004->GetYaxis()->SetTitleFont(42);
   Graph_Graph31004->GetZaxis()->SetLabelFont(42);
   Graph_Graph31004->GetZaxis()->SetTitleOffset(1);
   Graph_Graph31004->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph31004);
   
   gre->Draw("p");
   TLine *line = new TLine(6,1,375,1);
   line->SetLineStyle(8);
   line->Draw();
      tex = new TLatex(0.3,0.88,"#bf{Data}");
tex->SetNDC();
   tex->SetTextAlign(23);
   tex->SetTextSize(0.04);
   tex->SetLineWidth(2);
   tex->Draw();
   
   leg = new TLegend(0.35,0.7,0.65,0.85,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   entry=leg->AddEntry("Graph","Au+Au","lpf");
   entry->SetFillStyle(1000);
   entry->SetLineColor(12);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(12);
   entry->SetMarkerStyle(32);
   entry->SetMarkerSize(2);
   entry->SetTextFont(42);
   entry=leg->AddEntry("Graph","d+Au","lpf");
   entry->SetFillStyle(1000);

   ci = TColor::GetColor("#993300");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);

   ci = TColor::GetColor("#993300");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(25);
   entry->SetMarkerSize(1.5);
   entry->SetTextFont(42);
   entry=leg->AddEntry("Graph1D_y1","Cu+Cu #frac{#pi^{+}+#pi^{-}}{2}","lpf");
   entry->SetFillStyle(1000);

   ci = TColor::GetColor("#660066");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);

   ci = TColor::GetColor("#660066");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(27);
   entry->SetMarkerSize(1.5);
   entry->SetTextFont(42);
   leg->Draw();
   
   Double_t Graph4_fx1005[6] = {
   352.4,
   234.6,
   166.7,
   115.5,
   62.4,
   20.9};
   Double_t Graph4_fy1005[6] = {
   0.2643765,
   0.3475562,
   0.4197541,
   0.5337658,
   0.7447176,
   1.163125};
   Double_t Graph4_fex1005[6] = {
   3.7,
   8.8,
   9.8,
   9.95,
   9.35,
   5.8};
   Double_t Graph4_fey1005[6] = {
   0.01337267,
   0.02382148,
   0.02670599,
   0.03349907,
   0.04583013,
   0.07332121};
   gre = new TGraphErrors(6,Graph4_fx1005,Graph4_fy1005,Graph4_fex1005,Graph4_fey1005);
   gre->SetName("Graph4");
   gre->SetTitle("Inclusive hadron R_{AA} for p_{T} > 5 GeV");
   gre->SetFillStyle(1000);
   gre->SetLineColor(12);
   gre->SetLineWidth(2);
   gre->SetMarkerColor(12);
   gre->SetMarkerStyle(32);
   gre->SetMarkerSize(2);
   
   TH1F *Graph_Graph41005 = new TH1F("Graph_Graph41005","Inclusive hadron R_{AA} for p_{T} > 5 GeV",100,13.59,390.2);
   Graph_Graph41005->SetMinimum(0.1524596);
   Graph_Graph41005->SetMaximum(1.334991);
   Graph_Graph41005->SetDirectory(0);
   Graph_Graph41005->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph41005->SetLineColor(ci);
   Graph_Graph41005->GetXaxis()->SetTitle("#langle N_{part} #rangle");
   Graph_Graph41005->GetXaxis()->SetLabelFont(42);
   Graph_Graph41005->GetXaxis()->SetTitleOffset(1);
   Graph_Graph41005->GetXaxis()->SetTitleFont(42);
   Graph_Graph41005->GetYaxis()->SetTitle("R_{AA}");
   Graph_Graph41005->GetYaxis()->SetLabelFont(42);
   Graph_Graph41005->GetYaxis()->SetTitleFont(42);
   Graph_Graph41005->GetZaxis()->SetLabelFont(42);
   Graph_Graph41005->GetZaxis()->SetTitleOffset(1);
   Graph_Graph41005->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph41005);
   
   gre->Draw("p");
   
   Double_t Graph5_fx1006[2] = {
   15.7,
   8.31};
   Double_t Graph5_fy1006[2] = {
   1.200521,
   1.283952};
   Double_t Graph5_fex1006[2] = {
   1.2,
   0.37};
   Double_t Graph5_fey1006[2] = {
   0.09333034,
   0.1135719};
   gre = new TGraphErrors(2,Graph5_fx1006,Graph5_fy1006,Graph5_fex1006,Graph5_fey1006);
   gre->SetName("Graph5");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#993300");
   gre->SetLineColor(ci);
   gre->SetLineWidth(2);

   ci = TColor::GetColor("#993300");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(25);
   gre->SetMarkerSize(1.5);
   
   TH1F *Graph_Graph51006 = new TH1F("Graph_Graph51006","Graph",100,7.044,17.796);
   Graph_Graph51006->SetMinimum(1.078157);
   Graph_Graph51006->SetMaximum(1.426558);
   Graph_Graph51006->SetDirectory(0);
   Graph_Graph51006->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph51006->SetLineColor(ci);
   Graph_Graph51006->GetXaxis()->SetLabelFont(42);
   Graph_Graph51006->GetXaxis()->SetTitleOffset(1);
   Graph_Graph51006->GetXaxis()->SetTitleFont(42);
   Graph_Graph51006->GetYaxis()->SetLabelFont(42);
   Graph_Graph51006->GetYaxis()->SetTitleFont(42);
   Graph_Graph51006->GetZaxis()->SetLabelFont(42);
   Graph_Graph51006->GetZaxis()->SetTitleOffset(1);
   Graph_Graph51006->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph51006);
   
   gre->Draw("p");
   
   Double_t Graph1D_y1_fx3001[4] = {
   99,
   74.55,
   45.86,
   21.54};
   Double_t Graph1D_y1_fy3001[4] = {
   0.593156,
   0.724833,
   0.880833,
   1.10749};
   Double_t Graph1D_y1_felx3001[4] = {
   0,
   0,
   0,
   0};
   Double_t Graph1D_y1_fely3001[4] = {
   0.09127237,
   0.1096191,
   0.1291101,
   0.1598927};
   Double_t Graph1D_y1_fehx3001[4] = {
   0,
   0,
   0,
   0};
   Double_t Graph1D_y1_fehy3001[4] = {
   0.09127237,
   0.1096191,
   0.1291101,
   0.1598927};
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(4,Graph1D_y1_fx3001,Graph1D_y1_fy3001,Graph1D_y1_felx3001,Graph1D_y1_fehx3001,Graph1D_y1_fely3001,Graph1D_y1_fehy3001);
   grae->SetName("Graph1D_y1");
   grae->SetTitle("doi:10.17182/hepdata.98965.v1/t6");
   grae->SetFillStyle(1000);

   ci = TColor::GetColor("#660066");
   grae->SetLineColor(ci);
   grae->SetLineWidth(2);

   ci = TColor::GetColor("#660066");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(27);
   grae->SetMarkerSize(1.5);
   
   TH1F *Graph_Graph1D_y13001 = new TH1F("Graph_Graph1D_y13001","doi:10.17182/hepdata.98965.v1/t6",100,13.794,106.746);
   Graph_Graph1D_y13001->SetMinimum(0.4253337);
   Graph_Graph1D_y13001->SetMaximum(1.343933);
   Graph_Graph1D_y13001->SetDirectory(0);
   Graph_Graph1D_y13001->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph1D_y13001->SetLineColor(ci);
   Graph_Graph1D_y13001->GetXaxis()->SetTitle("Number of Participants");
   Graph_Graph1D_y13001->GetXaxis()->SetLabelFont(42);
   Graph_Graph1D_y13001->GetXaxis()->SetTitleOffset(1);
   Graph_Graph1D_y13001->GetXaxis()->SetTitleFont(42);
   Graph_Graph1D_y13001->GetYaxis()->SetTitle("$R_{AA}^{\\pi^{+}+\\pi^{-}}$ (5<$p_{T}$<8 GeV/c)");
   Graph_Graph1D_y13001->GetYaxis()->SetLabelFont(42);
   Graph_Graph1D_y13001->GetYaxis()->SetTitleFont(42);
   Graph_Graph1D_y13001->GetZaxis()->SetLabelFont(42);
   Graph_Graph1D_y13001->GetZaxis()->SetTitleOffset(1);
   Graph_Graph1D_y13001->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_Graph1D_y13001);
   
   grae->Draw("p");
   
   Double_t Graph0_fx1007[5] = {
   157.2265,
   116.3919,
   71.1642,
   32.69326,
   12.56275};
   Double_t Graph0_fy1007[5] = {
   0.4578087,
   0.5453024,
   0.6895866,
   0.8804518,
   0.9024313};
   Double_t Graph0_fex1007[5] = {
   4.716795,
   3.491756,
   2.134926,
   0.9807978,
   0.3768826};
   Double_t Graph0_fey1007[5] = {
   0.02553233,
   0.02895309,
   0.03556974,
   0.04483068,
   0.04607924};
   gre = new TGraphErrors(5,Graph0_fx1007,Graph0_fy1007,Graph0_fex1007,Graph0_fey1007);
   gre->SetName("Graph0");
   gre->SetTitle("Graph");

   ci = 1448;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#0000ff");
   gre->SetLineColor(ci);
   gre->SetMarkerSize(0);
   
   TH1F *Graph_Graph_Graph010011007 = new TH1F("Graph_Graph_Graph010011007","Graph",100,10.96728,176.919);
   Graph_Graph_Graph010011007->SetMinimum(0.3806529);
   Graph_Graph_Graph010011007->SetMaximum(1.000134);
   Graph_Graph_Graph010011007->SetDirectory(0);
   Graph_Graph_Graph010011007->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph_Graph010011007->SetLineColor(ci);
   Graph_Graph_Graph010011007->GetXaxis()->SetLabelFont(42);
   Graph_Graph_Graph010011007->GetXaxis()->SetTitleOffset(1);
   Graph_Graph_Graph010011007->GetXaxis()->SetTitleFont(42);
   Graph_Graph_Graph010011007->GetYaxis()->SetLabelFont(42);
   Graph_Graph_Graph010011007->GetYaxis()->SetTitleFont(42);
   Graph_Graph_Graph010011007->GetZaxis()->SetLabelFont(42);
   Graph_Graph_Graph010011007->GetZaxis()->SetTitleOffset(1);
   Graph_Graph_Graph010011007->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph_Graph010011007);
   
   gre->Draw("s=0.5 ");
   
   Double_t Graph1_fx1008[5] = {
   156.2169,
   114.8801,
   69.05626,
   31.31929,
   11.74879};
   Double_t Graph1_fy1008[5] = {
   0.4565197,
   0.5467488,
   0.6957025,
   0.8937189,
   0.8975997};
   Double_t Graph1_fex1008[5] = {
   4.686508,
   3.446404,
   2.071688,
   0.9395787,
   0.3524638};
   Double_t Graph1_fey1008[5] = {
   0.02540654,
   0.02897733,
   0.03579431,
   0.04547026,
   0.04592883};
   gre = new TGraphErrors(5,Graph1_fx1008,Graph1_fy1008,Graph1_fex1008,Graph1_fey1008);
   gre->SetName("Graph1");
   gre->SetTitle("Graph");

   ci = 1449;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#ff0000");
   gre->SetLineColor(ci);
   gre->SetMarkerSize(0);
   
   TH1F *Graph_Graph_Graph110021008 = new TH1F("Graph_Graph_Graph110021008","Graph",100,10.2567,175.8542);
   Graph_Graph_Graph110021008->SetMinimum(0.3798716);
   Graph_Graph_Graph110021008->SetMaximum(0.99477);
   Graph_Graph_Graph110021008->SetDirectory(0);
   Graph_Graph_Graph110021008->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph_Graph110021008->SetLineColor(ci);
   Graph_Graph_Graph110021008->GetXaxis()->SetLabelFont(42);
   Graph_Graph_Graph110021008->GetXaxis()->SetTitleOffset(1);
   Graph_Graph_Graph110021008->GetXaxis()->SetTitleFont(42);
   Graph_Graph_Graph110021008->GetYaxis()->SetLabelFont(42);
   Graph_Graph_Graph110021008->GetYaxis()->SetTitleFont(42);
   Graph_Graph_Graph110021008->GetZaxis()->SetLabelFont(42);
   Graph_Graph_Graph110021008->GetZaxis()->SetTitleOffset(1);
   Graph_Graph_Graph110021008->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph_Graph110021008);
   
   gre->Draw("s=0.5 ");
   
   Double_t Graph2_fx1009[5] = {
   157.2265,
   116.3919,
   71.1642,
   32.69326,
   12.56275};
   Double_t Graph2_fy1009[5] = {
   0.4578087,
   0.5453024,
   0.6895866,
   0.8804518,
   0.9024313};
   Double_t Graph2_fex1009[5] = {
   0.5489803,
   0.8433531,
   0.3760035,
   0.1117199,
   0.02881961};
   Double_t Graph2_fey1009[5] = {
   0.002606534,
   0.003682333,
   0.004095138,
   0.006413092,
   0.01051374};
   gre = new TGraphErrors(5,Graph2_fx1009,Graph2_fy1009,Graph2_fex1009,Graph2_fey1009);
   gre->SetName("Graph2");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#0000ff");
   gre->SetLineColor(ci);
   gre->SetLineWidth(3);

   ci = TColor::GetColor("#0000ff");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(21);
   gre->SetMarkerSize(2);
   
   TH1F *Graph_Graph_Graph210031009 = new TH1F("Graph_Graph_Graph210031009","Graph",100,11.28054,172.2996);
   Graph_Graph_Graph210031009->SetMinimum(0.4094279);
   Graph_Graph_Graph210031009->SetMaximum(0.9587193);
   Graph_Graph_Graph210031009->SetDirectory(0);
   Graph_Graph_Graph210031009->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph_Graph210031009->SetLineColor(ci);
   Graph_Graph_Graph210031009->GetXaxis()->SetLabelFont(42);
   Graph_Graph_Graph210031009->GetXaxis()->SetTitleOffset(1);
   Graph_Graph_Graph210031009->GetXaxis()->SetTitleFont(42);
   Graph_Graph_Graph210031009->GetYaxis()->SetLabelFont(42);
   Graph_Graph_Graph210031009->GetYaxis()->SetTitleFont(42);
   Graph_Graph_Graph210031009->GetZaxis()->SetLabelFont(42);
   Graph_Graph_Graph210031009->GetZaxis()->SetTitleOffset(1);
   Graph_Graph_Graph210031009->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph_Graph210031009);
   
   gre->Draw("p");
   
   Double_t Graph3_fx1010[5] = {
   156.2169,
   114.8801,
   69.05626,
   31.31929,
   11.74879};
   Double_t Graph3_fy1010[5] = {
   0.4565197,
   0.5467488,
   0.6957025,
   0.8937189,
   0.8975997};
   Double_t Graph3_fex1010[5] = {
   0.5343558,
   0.7873273,
   0.346641,
   0.09220326,
   0.04061752};
   Double_t Graph3_fey1010[5] = {
   0.002524438,
   0.003600194,
   0.004041714,
   0.006423558,
   0.009963541};
   gre = new TGraphErrors(5,Graph3_fx1010,Graph3_fy1010,Graph3_fex1010,Graph3_fey1010);
   gre->SetName("Graph3");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#ff0000");
   gre->SetLineColor(ci);
   gre->SetLineWidth(3);

   ci = TColor::GetColor("#ff0000");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(2);
   
   TH1F *Graph_Graph_Graph310041010 = new TH1F("Graph_Graph_Graph310041010","Graph",100,10.53736,171.2556);
   Graph_Graph_Graph310041010->SetMinimum(0.4086385);
   Graph_Graph_Graph310041010->SetMaximum(0.95292);
   Graph_Graph_Graph310041010->SetDirectory(0);
   Graph_Graph_Graph310041010->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph_Graph310041010->SetLineColor(ci);
   Graph_Graph_Graph310041010->GetXaxis()->SetLabelFont(42);
   Graph_Graph_Graph310041010->GetXaxis()->SetTitleOffset(1);
   Graph_Graph_Graph310041010->GetXaxis()->SetTitleFont(42);
   Graph_Graph_Graph310041010->GetYaxis()->SetLabelFont(42);
   Graph_Graph_Graph310041010->GetYaxis()->SetTitleFont(42);
   Graph_Graph_Graph310041010->GetZaxis()->SetLabelFont(42);
   Graph_Graph_Graph310041010->GetZaxis()->SetTitleOffset(1);
   Graph_Graph_Graph310041010->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph_Graph310041010);
   
   gre->Draw("p");
   
   leg = new TLegend(0.65,0.72,0.89,0.85,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   entry=leg->AddEntry("hgpythia_ru","Ru+Ru","lpf");

   ci = 1446;
   color = new TColor(ci, 0, 0, 1, " ", 0.5);
   entry->SetFillColor(ci);
   entry->SetFillStyle(3002);
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("hgpythia_zr","Zr+Zr","lpf");

   ci = 1447;
   color = new TColor(ci, 1, 0, 0, " ", 0.5);
   entry->SetFillColor(ci);
   entry->SetFillStyle(3001);
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(1);
   entry->SetTextFont(42);
   leg->Draw();
   
   leg = new TLegend(0.35,0.7,0.65,0.85,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   entry=leg->AddEntry("Graph4","Au+Au","lpf");
   entry->SetFillStyle(1000);
   entry->SetLineColor(12);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(12);
   entry->SetMarkerStyle(32);
   entry->SetMarkerSize(2);
   entry->SetTextFont(42);
   entry=leg->AddEntry("Graph5","d+Au","lpf");
   entry->SetFillStyle(1000);

   ci = TColor::GetColor("#993300");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);

   ci = TColor::GetColor("#993300");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(25);
   entry->SetMarkerSize(1.5);
   entry->SetTextFont(42);
   entry=leg->AddEntry("Graph1D_y1","Cu+Cu #frac{#pi^{+}+#pi^{-}}{2}","lpf");
   entry->SetFillStyle(1000);

   ci = TColor::GetColor("#660066");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);

   ci = TColor::GetColor("#660066");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(27);
   entry->SetMarkerSize(1.5);
   entry->SetTextFont(42);
   leg->Draw();
      tex = new TLatex(0.75,0.88,"#bf{HG-PYTHIA}");
tex->SetNDC();
   tex->SetTextAlign(23);
   tex->SetTextSize(0.04);
   tex->SetLineWidth(2);
   tex->Draw();
   
   Double_t hgpythia_ru_fx1011[19] = {
   175.2427,
   159.6462,
   142.1708,
   125.8655,
   111.2041,
   97.27234,
   84.78964,
   73.94191,
   64.21881,
   55.18999,
   47.12489,
   40.15421,
   33.83527,
   28.44579,
   23.2369,
   18.54294,
   15.47547,
   13.28336,
   11.13416};
   Double_t hgpythia_ru_fy1011[19] = {
   1.30318,
   1.159103,
   1.154985,
   1.112905,
   1.148021,
   1.091299,
   1.061937,
   1.173789,
   1.143569,
   1.018301,
   1.078955,
   1.109609,
   1.02587,
   1.077218,
   1.131196,
   0.8090772,
   0.7054669,
   0.5779776,
   0.3225314};
   Double_t hgpythia_ru_fex1011[19] = {
   0.00852851,
   0.01152548,
   0.01227936,
   0.01254537,
   0.01210242,
   0.01132894,
   0.01127849,
   0.01072183,
   0.01030023,
   0.009450195,
   0.009322667,
   0.0087619,
   0.008333907,
   0.008189638,
   0.006837197,
   0.006788287,
   0.008087492,
   0.007021729,
   0.005872791};
   Double_t hgpythia_ru_fey1011[19] = {
   0.1939925,
   0.1728457,
   0.1724555,
   0.1666347,
   0.1721683,
   0.1640839,
   0.1606059,
   0.1779631,
   0.1745626,
   0.1568637,
   0.1682571,
   0.1747013,
   0.165269,
   0.1776716,
   0.1865401,
   0.1477285,
   0.1546157,
   0.1363462,
   0.09383136};
   gre = new TGraphErrors(19,hgpythia_ru_fx1011,hgpythia_ru_fy1011,hgpythia_ru_fex1011,hgpythia_ru_fey1011);
   gre->SetName("hgpythia_ru");
   gre->SetTitle("Graph");

   ci = 1446;
   color = new TColor(ci, 0, 0, 1, " ", 0.5);
   gre->SetFillColor(ci);
   gre->SetFillStyle(3002);
   gre->SetLineWidth(0);
   gre->SetMarkerSize(0);
   
   TH1F *Graph_hgpythia_ru1011 = new TH1F("Graph_hgpythia_ru1011","Graph",100,10.01546,191.6636);
   Graph_hgpythia_ru1011->SetMinimum(0.1018527);
   Graph_hgpythia_ru1011->SetMaximum(1.62402);
   Graph_hgpythia_ru1011->SetDirectory(0);
   Graph_hgpythia_ru1011->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_hgpythia_ru1011->SetLineColor(ci);
   Graph_hgpythia_ru1011->GetXaxis()->SetTitle("N_{part}");
   Graph_hgpythia_ru1011->GetXaxis()->SetLabelFont(42);
   Graph_hgpythia_ru1011->GetXaxis()->SetTitleOffset(1);
   Graph_hgpythia_ru1011->GetXaxis()->SetTitleFont(42);
   Graph_hgpythia_ru1011->GetYaxis()->SetLabelFont(42);
   Graph_hgpythia_ru1011->GetYaxis()->SetTitleFont(42);
   Graph_hgpythia_ru1011->GetZaxis()->SetLabelFont(42);
   Graph_hgpythia_ru1011->GetZaxis()->SetTitleOffset(1);
   Graph_hgpythia_ru1011->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_hgpythia_ru1011);
   
   gre->Draw(" e3");
   
   Double_t hgpythia_zr_fx1012[19] = {
   173.6628,
   158.3702,
   141.1846,
   124.8522,
   109.8999,
   96.12094,
   83.92842,
   73.14074,
   62.97487,
   53.64995,
   46.02687,
   38.94453,
   32.84024,
   27.70783,
   23.10661,
   19.03523,
   15.83991,
   13.5806,
   11.37644};
   Double_t hgpythia_zr_fy1012[19] = {
   1.279048,
   1.177075,
   1.12652,
   1.130577,
   1.105918,
   1.111763,
   1.095066,
   1.13798,
   1.161858,
   1.094953,
   1.074208,
   0.9809098,
   1.034031,
   0.8360941,
   0.7843418,
   0.9061802,
   0.5947251,
   0.3458308,
   0.3673649};
   Double_t hgpythia_zr_fex1012[19] = {
   0.008592975,
   0.0115045,
   0.01237506,
   0.01254476,
   0.01213283,
   0.01172738,
   0.01146725,
   0.01100329,
   0.01006364,
   0.009734659,
   0.009893645,
   0.008486615,
   0.009281129,
   0.007961729,
   0.008215356,
   0.006892849,
   0.008172025,
   0.007037186,
   0.005864142};
   Double_t hgpythia_zr_fey1012[19] = {
   0.1904978,
   0.1755975,
   0.1683721,
   0.1693721,
   0.166083,
   0.167488,
   0.1658383,
   0.1730404,
   0.1773046,
   0.169099,
   0.1690338,
   0.1554626,
   0.1703193,
   0.1411756,
   0.1424081,
   0.1608116,
   0.1364437,
   0.09341366,
   0.09909206};
   gre = new TGraphErrors(19,hgpythia_zr_fx1012,hgpythia_zr_fy1012,hgpythia_zr_fex1012,hgpythia_zr_fey1012);
   gre->SetName("hgpythia_zr");
   gre->SetTitle("Graph");

   ci = 1447;
   color = new TColor(ci, 1, 0, 0, " ", 0.5);
   gre->SetFillColor(ci);
   gre->SetFillStyle(3001);
   gre->SetLineWidth(0);
   gre->SetMarkerSize(0);
   
   TH1F *Graph_hgpythia_zr1012 = new TH1F("Graph_hgpythia_zr1012","Graph",100,10.23352,189.9015);
   Graph_hgpythia_zr1012->SetMinimum(0.1307043);
   Graph_hgpythia_zr1012->SetMaximum(1.591259);
   Graph_hgpythia_zr1012->SetDirectory(0);
   Graph_hgpythia_zr1012->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_hgpythia_zr1012->SetLineColor(ci);
   Graph_hgpythia_zr1012->GetXaxis()->SetTitle("N_{part}");
   Graph_hgpythia_zr1012->GetXaxis()->SetLabelFont(42);
   Graph_hgpythia_zr1012->GetXaxis()->SetTitleOffset(1);
   Graph_hgpythia_zr1012->GetXaxis()->SetTitleFont(42);
   Graph_hgpythia_zr1012->GetYaxis()->SetLabelFont(42);
   Graph_hgpythia_zr1012->GetYaxis()->SetTitleFont(42);
   Graph_hgpythia_zr1012->GetZaxis()->SetLabelFont(42);
   Graph_hgpythia_zr1012->GetZaxis()->SetTitleOffset(1);
   Graph_hgpythia_zr1012->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_hgpythia_zr1012);
   
   gre->Draw(" e3");
   
   Double_t Graph0_fx1013[5] = {
   157.2265,
   116.3919,
   71.1642,
   32.69326,
   12.56275};
   Double_t Graph0_fy1013[5] = {
   0.4578087,
   0.5453024,
   0.6895866,
   0.8804518,
   0.9024313};
   Double_t Graph0_fex1013[5] = {
   4.716795,
   3.491756,
   2.134926,
   0.9807978,
   0.3768826};
   Double_t Graph0_fey1013[5] = {
   0.02553233,
   0.02895309,
   0.03556974,
   0.04483068,
   0.04607924};
   gre = new TGraphErrors(5,Graph0_fx1013,Graph0_fy1013,Graph0_fex1013,Graph0_fey1013);
   gre->SetName("Graph0");
   gre->SetTitle("Graph");

   ci = 1448;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#0000ff");
   gre->SetLineColor(ci);
   gre->SetMarkerSize(0);
   
   TH1F *Graph_Graph_Graph_Graph0100110071013 = new TH1F("Graph_Graph_Graph_Graph0100110071013","Graph",100,10.96728,176.919);
   Graph_Graph_Graph_Graph0100110071013->SetMinimum(0.3806529);
   Graph_Graph_Graph_Graph0100110071013->SetMaximum(1.000134);
   Graph_Graph_Graph_Graph0100110071013->SetDirectory(0);
   Graph_Graph_Graph_Graph0100110071013->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph_Graph_Graph0100110071013->SetLineColor(ci);
   Graph_Graph_Graph_Graph0100110071013->GetXaxis()->SetLabelFont(42);
   Graph_Graph_Graph_Graph0100110071013->GetXaxis()->SetTitleOffset(1);
   Graph_Graph_Graph_Graph0100110071013->GetXaxis()->SetTitleFont(42);
   Graph_Graph_Graph_Graph0100110071013->GetYaxis()->SetLabelFont(42);
   Graph_Graph_Graph_Graph0100110071013->GetYaxis()->SetTitleFont(42);
   Graph_Graph_Graph_Graph0100110071013->GetZaxis()->SetLabelFont(42);
   Graph_Graph_Graph_Graph0100110071013->GetZaxis()->SetTitleOffset(1);
   Graph_Graph_Graph_Graph0100110071013->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph_Graph_Graph0100110071013);
   
   gre->Draw("s=0.5 ");
   
   Double_t Graph1_fx1014[5] = {
   156.2169,
   114.8801,
   69.05626,
   31.31929,
   11.74879};
   Double_t Graph1_fy1014[5] = {
   0.4565197,
   0.5467488,
   0.6957025,
   0.8937189,
   0.8975997};
   Double_t Graph1_fex1014[5] = {
   4.686508,
   3.446404,
   2.071688,
   0.9395787,
   0.3524638};
   Double_t Graph1_fey1014[5] = {
   0.02540654,
   0.02897733,
   0.03579431,
   0.04547026,
   0.04592883};
   gre = new TGraphErrors(5,Graph1_fx1014,Graph1_fy1014,Graph1_fex1014,Graph1_fey1014);
   gre->SetName("Graph1");
   gre->SetTitle("Graph");

   ci = 1449;
   color = new TColor(ci, 1, 1, 1, " ", 0);
   gre->SetFillColor(ci);
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#ff0000");
   gre->SetLineColor(ci);
   gre->SetMarkerSize(0);
   
   TH1F *Graph_Graph_Graph_Graph1100210081014 = new TH1F("Graph_Graph_Graph_Graph1100210081014","Graph",100,10.2567,175.8542);
   Graph_Graph_Graph_Graph1100210081014->SetMinimum(0.3798716);
   Graph_Graph_Graph_Graph1100210081014->SetMaximum(0.99477);
   Graph_Graph_Graph_Graph1100210081014->SetDirectory(0);
   Graph_Graph_Graph_Graph1100210081014->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph_Graph_Graph1100210081014->SetLineColor(ci);
   Graph_Graph_Graph_Graph1100210081014->GetXaxis()->SetLabelFont(42);
   Graph_Graph_Graph_Graph1100210081014->GetXaxis()->SetTitleOffset(1);
   Graph_Graph_Graph_Graph1100210081014->GetXaxis()->SetTitleFont(42);
   Graph_Graph_Graph_Graph1100210081014->GetYaxis()->SetLabelFont(42);
   Graph_Graph_Graph_Graph1100210081014->GetYaxis()->SetTitleFont(42);
   Graph_Graph_Graph_Graph1100210081014->GetZaxis()->SetLabelFont(42);
   Graph_Graph_Graph_Graph1100210081014->GetZaxis()->SetTitleOffset(1);
   Graph_Graph_Graph_Graph1100210081014->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph_Graph_Graph1100210081014);
   
   gre->Draw("s=0.5 ");
   
   Double_t Graph2_fx1015[5] = {
   157.2265,
   116.3919,
   71.1642,
   32.69326,
   12.56275};
   Double_t Graph2_fy1015[5] = {
   0.4578087,
   0.5453024,
   0.6895866,
   0.8804518,
   0.9024313};
   Double_t Graph2_fex1015[5] = {
   0.5489803,
   0.8433531,
   0.3760035,
   0.1117199,
   0.02881961};
   Double_t Graph2_fey1015[5] = {
   0.002606534,
   0.003682333,
   0.004095138,
   0.006413092,
   0.01051374};
   gre = new TGraphErrors(5,Graph2_fx1015,Graph2_fy1015,Graph2_fex1015,Graph2_fey1015);
   gre->SetName("Graph2");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#0000ff");
   gre->SetLineColor(ci);
   gre->SetLineWidth(3);

   ci = TColor::GetColor("#0000ff");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(21);
   gre->SetMarkerSize(2);
   
   TH1F *Graph_Graph_Graph_Graph2100310091015 = new TH1F("Graph_Graph_Graph_Graph2100310091015","Graph",100,11.28054,172.2996);
   Graph_Graph_Graph_Graph2100310091015->SetMinimum(0.4094279);
   Graph_Graph_Graph_Graph2100310091015->SetMaximum(0.9587193);
   Graph_Graph_Graph_Graph2100310091015->SetDirectory(0);
   Graph_Graph_Graph_Graph2100310091015->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph_Graph_Graph2100310091015->SetLineColor(ci);
   Graph_Graph_Graph_Graph2100310091015->GetXaxis()->SetLabelFont(42);
   Graph_Graph_Graph_Graph2100310091015->GetXaxis()->SetTitleOffset(1);
   Graph_Graph_Graph_Graph2100310091015->GetXaxis()->SetTitleFont(42);
   Graph_Graph_Graph_Graph2100310091015->GetYaxis()->SetLabelFont(42);
   Graph_Graph_Graph_Graph2100310091015->GetYaxis()->SetTitleFont(42);
   Graph_Graph_Graph_Graph2100310091015->GetZaxis()->SetLabelFont(42);
   Graph_Graph_Graph_Graph2100310091015->GetZaxis()->SetTitleOffset(1);
   Graph_Graph_Graph_Graph2100310091015->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph_Graph_Graph2100310091015);
   
   gre->Draw("p");
   
   Double_t Graph3_fx1016[5] = {
   156.2169,
   114.8801,
   69.05626,
   31.31929,
   11.74879};
   Double_t Graph3_fy1016[5] = {
   0.4565197,
   0.5467488,
   0.6957025,
   0.8937189,
   0.8975997};
   Double_t Graph3_fex1016[5] = {
   0.5343558,
   0.7873273,
   0.346641,
   0.09220326,
   0.04061752};
   Double_t Graph3_fey1016[5] = {
   0.002524438,
   0.003600194,
   0.004041714,
   0.006423558,
   0.009963541};
   gre = new TGraphErrors(5,Graph3_fx1016,Graph3_fy1016,Graph3_fex1016,Graph3_fey1016);
   gre->SetName("Graph3");
   gre->SetTitle("Graph");
   gre->SetFillStyle(1000);

   ci = TColor::GetColor("#ff0000");
   gre->SetLineColor(ci);
   gre->SetLineWidth(3);

   ci = TColor::GetColor("#ff0000");
   gre->SetMarkerColor(ci);
   gre->SetMarkerStyle(20);
   gre->SetMarkerSize(2);
   
   TH1F *Graph_Graph_Graph_Graph3100410101016 = new TH1F("Graph_Graph_Graph_Graph3100410101016","Graph",100,10.53736,171.2556);
   Graph_Graph_Graph_Graph3100410101016->SetMinimum(0.4086385);
   Graph_Graph_Graph_Graph3100410101016->SetMaximum(0.95292);
   Graph_Graph_Graph_Graph3100410101016->SetDirectory(0);
   Graph_Graph_Graph_Graph3100410101016->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_Graph_Graph_Graph3100410101016->SetLineColor(ci);
   Graph_Graph_Graph_Graph3100410101016->GetXaxis()->SetLabelFont(42);
   Graph_Graph_Graph_Graph3100410101016->GetXaxis()->SetTitleOffset(1);
   Graph_Graph_Graph_Graph3100410101016->GetXaxis()->SetTitleFont(42);
   Graph_Graph_Graph_Graph3100410101016->GetYaxis()->SetLabelFont(42);
   Graph_Graph_Graph_Graph3100410101016->GetYaxis()->SetTitleFont(42);
   Graph_Graph_Graph_Graph3100410101016->GetZaxis()->SetLabelFont(42);
   Graph_Graph_Graph_Graph3100410101016->GetZaxis()->SetTitleOffset(1);
   Graph_Graph_Graph_Graph3100410101016->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph_Graph_Graph3100410101016);
   
   gre->Draw("p");
   compile_raa->Modified();
   compile_raa->cd();
   compile_raa->SetSelected(compile_raa);
}
