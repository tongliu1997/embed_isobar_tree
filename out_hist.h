#include "embed_species.h"


class out_hist{

public:
    std::vector<int> cent_bins;
    TH1D** unfold_spec;
    TH1D** raw_spec;
    TH1D* hist_nbin;
    TH1D* hist_npart;
    string msys;
public:
    out_hist(const string file_name,std::vector<int> bins,const string system,const string embed_key);
    
    virtual ~out_hist();

    void set_name(const string name);



    void clear_error();
    void add_error(out_hist &variation);
    void add_error(out_hist *variation);
    void add_error(double frac);
    void add_smear(const string filename,const string key);

    double npart(int ibin);
    double npart_err(int ibin);
    double nbin(int ibin);
    double nbin_err(int ibin);
    double ncoll(int ibin){return nbin(ibin);};
    double ncoll_err(int ibin){return nbin_err(ibin);};

    void Write(const string filename);

};

out_hist::out_hist(
	const string file_name,
	std::vector<int> bins={0,10,20,40,60,80},
	const string system="ru",
	const string embed_key=""

){
    cent_bins=bins;
    msys=system;
//    cout<<"Starting reading"<<endl;
    TFile* inputfile=new TFile(file_name.c_str());
    const int ncent=bins.size()-1;
    unfold_spec=(TH1D**)malloc(sizeof(TH1D*)*ncent);
    raw_spec=(TH1D**)malloc(sizeof(TH1D*)*ncent);

    for(int i=0;i<ncent;i++){
	unfold_spec[i]=(TH1D*)inputfile->Get(Form("%s%s_unfolded_spec_%i_%i",system.c_str(),embed_key.c_str(),bins[i],bins[i+1]));
	raw_spec[i]=(TH1D*)inputfile->Get(Form("%s%s_raw_spec_%i_%i",system.c_str(),embed_key.c_str(),bins[i],bins[i+1]));
    }
    hist_nbin=(TH1D*)inputfile->Get(Form("%s%s_ncoll",system.c_str(),embed_key.c_str()));
    hist_npart=(TH1D*)inputfile->Get(Form("%s%s_npart",system.c_str(),embed_key.c_str()));
//*/
};


out_hist::~out_hist(){
    
    for(int i=0;i<cent_bins.size()-1;i++){
	delete unfold_spec[i];
	delete raw_spec[i];
    }
    delete hist_nbin;
    delete hist_npart;

    delete unfold_spec;
    delete raw_spec;

    return;
}



void out_hist::set_name(const string name){
    for(int i=0;i<cent_bins.size()-1;i++){
	unfold_spec[i]->SetName(Form("%s%s_unfolded_spec_%i_%i",msys.c_str(),name.c_str(),cent_bins[i],cent_bins[i+1]));
	raw_spec[i]->SetName(Form("%s%s_raw_spec_%i_%i",msys.c_str(),name.c_str(),cent_bins[i],cent_bins[i+1]));
	
    }
    hist_nbin->SetName(Form("%s%s_ncoll",msys.c_str(),name.c_str()));
    hist_npart->SetName(Form("%s%s_npart",msys.c_str(),name.c_str()));

    return;
}



void out_hist::clear_error(){
    int nxbins=unfold_spec[0]->GetNbinsX();
    for(int i=0;i<cent_bins.size()-1;i++){
 	for(int ibin=1;ibin<=nxbins;ibin++){
	    unfold_spec[i]->SetBinError(ibin,0);
//	    raw_spec[i]->SetBinError(ibin,0);
	}
    }
    return;
}



void out_hist::add_error(out_hist &variation){
    int nxbins=unfold_spec[0]->GetNbinsX();
    for(int i=0;i<cent_bins.size()-1;i++){
 	for(int ibin=1;ibin<=nxbins;ibin++){

	    double vari_error=variation.unfold_spec[i]->GetBinContent(ibin);
	    vari_error-=unfold_spec[i]->GetBinContent(ibin);
//	    cout<<i<<"\t"<<unfold_spec[i]->GetBinCenter(ibin)<<"\t"<<vari_error/unfold_spec[i]->GetBinContent(ibin)<<endl;
	    vari_error=vari_error*vari_error;
	    double nomi_error=unfold_spec[i]->GetBinError(ibin);
	    vari_error+=nomi_error*nomi_error;
	
	    unfold_spec[i]->SetBinError(ibin,sqrt(vari_error));
	}
    }
    return;
}

void out_hist::add_error(out_hist *variation){
    add_error(*variation);
    return;
}
void out_hist::add_error(double frac){
    int nxbins=unfold_spec[0]->GetNbinsX();
    for(int i=0;i<cent_bins.size()-1;i++){
	for(int ibin=1;ibin<=nxbins;ibin++){
	    double vari_error=unfold_spec[i]->GetBinContent(ibin)*frac;
	    vari_error=vari_error*vari_error;
	    
	    double nomi_error=unfold_spec[i]->GetBinError(ibin);
	    vari_error+=nomi_error*nomi_error;
	
	    unfold_spec[i]->SetBinError(ibin,sqrt(vari_error));
	}
    }
}

void out_hist::add_smear(
const string filename="isobar_trk_eff_ptmix_blend.root",
const string key="blended"
){
    int ncentbins=cent_bins.size()-1;
    species_plots species(filename,key,key,"pt");
    const int stack_dim=1;
    vector<int> stack_bin;
    for(int i=ncentbins;i>=0;i--){
	stack_bin.push_back(17-cent_bins[i]/5);
	cout<<17-cent_bins[i]/5<<endl;
    }
  
    TH2F** devs=dev_stack(species,stack_dim,stack_bin);
    
    int nxbins=unfold_spec[0]->GetNbinsX();
//    TCanvas* c1=new TCanvas();
//    c1->Divide(3,2);
    for(int i=0;i<ncentbins;i++){
	TProfile* pf=devs[ncentbins-1-i]->ProfileX(Form("dev_profile_%i",i),1,-1,"s");
	TProfile* pf_rebin=(TProfile*)pf->Rebin(nbins,"pf_rebin",xbins);
//	c1->cd(i+1);
//	pf_rebin->Draw();
	for(int ibin=1;ibin<=nxbins;ibin++){
    	   double nominal_error=unfold_spec[i]->GetBinError(ibin)/unfold_spec[i]->GetBinContent(ibin);
	   double smear=pf_rebin->GetBinError(ibin);
//	   cout<<unfold_spec[i]->GetBinCenter(ibin)<<"\t"<<smear<<"\t"<<nominal_error<<endl;
	   double error=TMath::Sqrt(nominal_error*nominal_error+smear*smear);
	   error*=unfold_spec[i]->GetBinContent(ibin);

	   unfold_spec[i]->SetBinError(ibin,error);
	}
    }
    return;

}

double out_hist::npart(int ibin){
    int ncent=hist_npart->GetNbinsX();
    return hist_npart->GetBinContent(ncent-ibin);
}

double out_hist::npart_err(int ibin){
    int ncent=hist_npart->GetNbinsX();
    return hist_npart->GetBinError(ncent-ibin);
}


double out_hist::nbin(int ibin){
    int ncent=hist_nbin->GetNbinsX();
    return hist_nbin->GetBinContent(ncent-ibin);
}

double out_hist::nbin_err(int ibin){
    int ncent=hist_nbin->GetNbinsX();
    return hist_nbin->GetBinError(ncent-ibin);
}

void out_hist::Write(const string filename){
    TFile* file=new TFile(filename.c_str(),"recreate");
    
    for(int i=0;i<cent_bins.size()-1;i++){
	unfold_spec[i]->Write();
	raw_spec[i]->Write();
    }
    hist_nbin->Write();
    hist_npart->Write();


   return; 
}
