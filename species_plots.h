#pragma once

using namespace std;
/*
 * Read in all the embedding plots from file or generate empty ones
 * Dimensions of plots defined at the bottom
 * 
 * */


class species_plots{

public:
    static const int lumi_bins=1;
    static const int ea_bins=17;
    static const int vz_bins=4;

    static int pt_bins;
    static double pt_min;
    static double pt_max;
    static int ntrk_bins;
    static double ntrk_min;
    static double ntrk_max;

/*    species_plots::pt_bins=90;
    pt_min=0;
    pt_max=18;
    ntrk_bins=10;
    ntrk_min=-0.5;
    ntrk_max=9.5;
*/
public:
    string namestr;
    bool is_new=false;

    TH1F* nmctrk_nontrans[lumi_bins][ea_bins][vz_bins];
    TH2F* mc_reco_pt[lumi_bins][ea_bins][vz_bins];
    TH1F* gen_mc_pt[lumi_bins][ea_bins][vz_bins];
    TH1F* match_mc_pt[lumi_bins][ea_bins][vz_bins];
    TH2F* notrans_mc_reco_pt[lumi_bins][ea_bins][vz_bins];
    TH1F* notrans_gen_mc_pt[lumi_bins][ea_bins][vz_bins];
    TH1F* notrans_match_mc_pt[lumi_bins][ea_bins][vz_bins];
//All histograms with name "notrans" select only tracks that align/anti-align with the random angle we picked. 
//At the minute this is still meaningless, but we'll potentially poke into it later.

    TH1F* reco_pt[lumi_bins][ea_bins][vz_bins];
    TH1F* notrans_reco_pt[lumi_bins][ea_bins][vz_bins];
    TH1F* pt_efficiency[lumi_bins][ea_bins][vz_bins];

    TH1F* ZDCx_distribution;

    species_plots(string inputname_str,string input_keyword="",string name_keyword="");
    species_plots(bool make_new_plots, const string keyword);
    virtual ~species_plots();
    virtual void scale(double factor);
    virtual void add(species_plots c1,double factor=1);

    double n_events();//This returns the SCALED number of events; i.e. if an event is scaled by 3 then it's counted as 3 events.
    virtual void normalize();


    virtual void write(TFile* output);
    virtual void write(const string outname);


};


int species_plots::pt_bins=150;
double species_plots::pt_min=0;
double species_plots::pt_max=30;
int species_plots::ntrk_bins=10;
double species_plots::ntrk_min=-0.5;
double species_plots::ntrk_max=9.5;

species_plots::species_plots(string inputname_str,string input_keyword,string name_keyword){
 /*       pt_bins=90;
        pt_min=0;
    	pt_max=18;
    	ntrk_bins=10;
    	ntrk_min=-0.5;
    	ntrk_max=9.5;
*/
    TFile* inputfile=new TFile(inputname_str.c_str());
//  string inputname_str(inputname);
    string namekey_str=name_keyword;
    if(name_keyword==""){
	if(input_keyword=="")namekey_str=inputname_str;
	else namekey_str=input_keyword;
    }
    const char* inkey=input_keyword.c_str();
    const char* namekey=namekey_str.c_str();
    namestr=namekey_str;
	
    for(int i=0;i<lumi_bins;i++){
        for(int j=0;j<ea_bins;j++){
            for(int k=0;k<vz_bins;k++){
		    
		const string in_token ( (input_keyword=="") ? Form("%i_%i_%i",i,j,k):Form("%i_%i_%i_%s",i,j,k,input_keyword.c_str()) );
		const string name_token ( (namekey_str=="") ? Form("%i_%i_%i",i,j,k):Form("%i_%i_%i_%s",i,j,k,namekey_str.c_str()) ) ;

                mc_reco_pt[i][j][k]=(TH2F*)inputfile->Get(Form("mc_reco_pt_%s",in_token.c_str()));
	 	mc_reco_pt[i][j][k]->SetName(Form("mc_reco_pt_%s",name_token.c_str()));
                gen_mc_pt[i][j][k]=(TH1F*)inputfile->Get(Form("gen_mc_pt_%s",in_token.c_str()));
                gen_mc_pt[i][j][k]->SetName(Form("gen_mc_pt_%s",name_token.c_str()));
                match_mc_pt[i][j][k]=(TH1F*)inputfile->Get(Form("match_mc_pt_%s",in_token.c_str()));
                match_mc_pt[i][j][k]->SetName(Form("match_mc_pt_%s",name_token.c_str()));

                notrans_match_mc_pt[i][j][k]=(TH1F*)inputfile->Get(Form("notrans_match_mc_pt_%s",in_token.c_str()));
                notrans_match_mc_pt[i][j][k]->SetName(Form("notrans_match_mc_pt_%s",name_token.c_str()));
                notrans_mc_reco_pt[i][j][k]=(TH2F*)inputfile->Get(Form("notrans_mc_reco_pt_%s",in_token.c_str()));
                notrans_mc_reco_pt[i][j][k]->SetName(Form("notrans_mc_reco_pt_%s",name_token.c_str()));
                notrans_gen_mc_pt[i][j][k]=(TH1F*)inputfile->Get(Form("notrans_gen_mc_pt_%s",in_token.c_str()));
                notrans_gen_mc_pt[i][j][k]->SetName(Form("notrans_gen_mc_pt_%s",name_token.c_str()));

                nmctrk_nontrans[i][j][k]=(TH1F*)inputfile->Get(Form("nmctrk_nontrans_%s",in_token.c_str()));
                nmctrk_nontrans[i][j][k]->SetName(Form("nmctrk_nontrans_%s",name_token.c_str()));

		
		nmctrk_nontrans[i][j][k]->Sumw2();	
		mc_reco_pt[i][j][k]->Sumw2();	
		gen_mc_pt[i][j][k]->Sumw2();	
		match_mc_pt[i][j][k]->Sumw2();	

		notrans_mc_reco_pt[i][j][k]->Sumw2();	
		notrans_gen_mc_pt[i][j][k]->Sumw2();	
		notrans_match_mc_pt[i][j][k]->Sumw2();	


                reco_pt[i][j][k]=(TH1F*)mc_reco_pt[i][j][k]->ProjectionY();
                notrans_reco_pt[i][j][k]=(TH1F*) notrans_mc_reco_pt[i][j][k]->ProjectionY();

                pt_efficiency[i][j][k]=(TH1F*)reco_pt[i][j][k]->Clone();
                pt_efficiency[i][j][k]->Divide(gen_mc_pt[i][j][k]);
                pt_efficiency[i][j][k]->SetTitle(Form("pt_efficiency_%i_%i_%i",i,j,k));

            }
       	}
    }

    const string zdc_in_token  ( (input_keyword=="") ? "ZDCx_distribution" : Form("ZDCx_distribution_%s",input_keyword.c_str()) );
    const string zdc_name_token ( (namekey_str=="") ? "ZDCx_distribution" : Form("ZDCx_distribution_%s",namekey_str.c_str()) ) ;
//    cout<<zdc_in_token<<endl;
    ZDCx_distribution=(TH1F*)inputfile->Get(zdc_in_token.c_str());
    ZDCx_distribution->SetName(zdc_name_token.c_str());
    ZDCx_distribution->Sumw2();

    if(1){
	int ptx_nbins=mc_reco_pt[0][0][0]->GetNbinsX();
	double ptx_min=mc_reco_pt[0][0][0]->GetXaxis()->GetBinLowEdge(1);
	double ptx_max=mc_reco_pt[0][0][0]->GetXaxis()->GetBinLowEdge(ptx_nbins)+mc_reco_pt[0][0][0]->GetXaxis()->GetBinWidth(ptx_nbins);
	if(ptx_nbins!=pt_bins || ptx_min != pt_min || ptx_max != pt_max )	cout<<"pt binning needs to be changed."<<endl;
	int ntrkx_nbins=nmctrk_nontrans[0][0][0]->GetNbinsX();
	double ntrkx_min=nmctrk_nontrans[0][0][0]->GetXaxis()->GetBinLowEdge(1);
	double ntrkx_max=nmctrk_nontrans[0][0][0]->GetXaxis()->GetBinLowEdge(ntrkx_nbins)+nmctrk_nontrans[0][0][0]->GetXaxis()->GetBinWidth(ntrkx_nbins);
	if(ntrkx_nbins != ntrk_bins || ntrkx_min != ntrk_min || ntrkx_max != ntrk_max) {
	    cout<<"ntrk binning needs to be changed. "<<endl;
	    cout<<ntrkx_nbins<<"\t"<<ntrkx_min<<"\t"<<ntrkx_max<<endl;
	}
    }
}


//This constructor is for when we need to make fresh histograms
//The variable "make_new_plots" is not actually used
//It's put there to differentiate this constructor with the previous one
//
species_plots::species_plots(bool make_new_plots, const string keyword){
    namestr=keyword;
    is_new=true;
    for(int i=0;i<lumi_bins;i++){
    	for(int j=0;j<ea_bins;j++){
            for(int k=0;k<vz_bins;k++){
		mc_reco_pt[i][j][k]=new TH2F(Form("mc_reco_pt_%i_%i_%i_%s",i,j,k,keyword.c_str()),"",pt_bins,pt_min,pt_max,pt_bins,pt_min,pt_max);
		gen_mc_pt[i][j][k]=new TH1F(Form("gen_mc_pt_%i_%i_%i_%s",i,j,k,keyword.c_str()),"",pt_bins,pt_min,pt_max);
		match_mc_pt[i][j][k]=new TH1F(Form("match_mc_pt_%i_%i_%i_%s",i,j,k,keyword.c_str()),"",pt_bins,pt_min,pt_max);
		notrans_match_mc_pt[i][j][k]=new TH1F(Form("notrans_match_mc_pt_%i_%i_%i_%s",i,j,k,keyword.c_str()),"",pt_bins,pt_min,pt_max);

		notrans_mc_reco_pt[i][j][k]=new TH2F(Form("notrans_mc_reco_pt_%i_%i_%i_%s",i,j,k,keyword.c_str()),"",pt_bins,pt_min,pt_max,pt_bins,pt_min,pt_max);
		notrans_gen_mc_pt[i][j][k]=new TH1F(Form("notrans_gen_mc_pt_%i_%i_%i_%s",i,j,k,keyword.c_str()),"",pt_bins,pt_min,pt_max);

	   	nmctrk_nontrans[i][j][k]=new TH1F(Form("nmctrk_nontrans_%i_%i_%i_%s",i,j,k,keyword.c_str()),"",ntrk_bins,ntrk_min,ntrk_max); 


		reco_pt[i][j][k]=new TH1F(Form("reco_pt_%i_%i_%i_%s",i,j,k,keyword.c_str()),"",pt_bins,pt_min,pt_max);
		notrans_reco_pt[i][j][k]=new TH1F(Form("notrans_reco_pt_%i_%i_%i_%s",i,j,k,keyword.c_str()),"",pt_bins,pt_min,pt_max);
		pt_efficiency[i][j][k]=new TH1F(Form("pt_efficiency_%i_%i_%i_%s",i,j,k,keyword.c_str()),"",pt_bins,pt_min,pt_max);
		
            }
       	}
    }
    ZDCx_distribution=new TH1F(Form("ZDCx_distribution_%s",keyword.c_str()),"",lumi_bins*50,0,100000);
    cout<<"Generated new plots."<<endl;	
};

species_plots::~species_plots() {return;};

void species_plots::scale(double factor){
    
    for(int i=0;i<lumi_bins;i++){
	for(int j=0;j<ea_bins;j++){
	    for(int k=0;k<vz_bins;k++){
		nmctrk_nontrans[i][j][k]->Scale(factor);	
		mc_reco_pt[i][j][k]->Scale(factor);	
		gen_mc_pt[i][j][k]->Scale(factor);	
		match_mc_pt[i][j][k]->Scale(factor);	

		notrans_mc_reco_pt[i][j][k]->Scale(factor);	
		notrans_gen_mc_pt[i][j][k]->Scale(factor);	
		notrans_match_mc_pt[i][j][k]->Scale(factor);	

		reco_pt[i][j][k]->Scale(factor);
		notrans_reco_pt[i][j][k]->Scale(factor);
//		pt_efficiency[i][j][k]->Scale(factor);
		
	    }
	}
    }
    ZDCx_distribution->Scale(factor);
}

void species_plots::add(species_plots c1,double factor){
    
    for(int i=0;i<lumi_bins;i++){
	for(int j=0;j<ea_bins;j++){
	    for(int k=0;k<vz_bins;k++){
		nmctrk_nontrans[i][j][k]->Add(c1.nmctrk_nontrans[i][j][k],factor);	
		mc_reco_pt[i][j][k]->Add(c1.mc_reco_pt[i][j][k],factor);	
		gen_mc_pt[i][j][k]->Add(c1.gen_mc_pt[i][j][k],factor);	
		match_mc_pt[i][j][k]->Add(c1.match_mc_pt[i][j][k],factor);	

		notrans_mc_reco_pt[i][j][k]->Add(c1.notrans_mc_reco_pt[i][j][k],factor);	
		notrans_gen_mc_pt[i][j][k]->Add(c1.notrans_gen_mc_pt[i][j][k],factor);	
		notrans_match_mc_pt[i][j][k]->Add(c1.notrans_match_mc_pt[i][j][k],factor);	

		reco_pt[i][j][k]->Add(c1.reco_pt[i][j][k],factor);
		notrans_reco_pt[i][j][k]->Add(c1.notrans_reco_pt[i][j][k],factor);
//		pt_efficiency[i][j][k]->Add(c1.pt_efficiency[i][j][k],factor);

		pt_efficiency[i][j][k]=(TH1F*)reco_pt[i][j][k]->Clone();
		pt_efficiency[i][j][k]->SetName(Form("pt_efficiency_%i_%i_%i_%s",i,j,k,namestr.c_str()));
		pt_efficiency[i][j][k]->SetTitle(Form("pt_efficiency_%i_%i_%i",i,j,k));
		pt_efficiency[i][j][k]->Divide(gen_mc_pt[i][j][k]);
		
		
	    }
	}
    }
    ZDCx_distribution->Add(c1.ZDCx_distribution,factor);
}


double species_plots::n_events(){

    return ZDCx_distribution->Integral();


}


void species_plots::normalize(){
     scale(1.0/n_events());

}

void species_plots::write(TFile* output){
    output->cd();
    for(int i=0;i<lumi_bins;i++){
	for(int j=0;j<ea_bins;j++){
	    for(int k=0;k<vz_bins;k++){
		nmctrk_nontrans[i][j][k]->Write();
		mc_reco_pt[i][j][k]->Write();
		match_mc_pt[i][j][k]->Write();
		gen_mc_pt[i][j][k]->Write();

		notrans_gen_mc_pt[i][j][k]->Write();
		notrans_match_mc_pt[i][j][k]->Write();
		notrans_mc_reco_pt[i][j][k]->Write();
    
		reco_pt[i][j][k]->Write();
		notrans_reco_pt[i][j][k]->Write();
		pt_efficiency[i][j][k]->Write();

	    }
	}
    }
    ZDCx_distribution->Write();
}

void species_plots::write(const string outname){
    TFile* output=new TFile(outname.c_str(),"recreate");
    write(output);
    output->Close();
    cout<<"Wrote class to "<<outname<<endl;

}
