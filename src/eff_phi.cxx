/*
 *Looks like embedding data all have refmult set to zero? Check back that at RCAF.
 *
 */
#include "events.h"
#include <sstream>
#include <fstream>

#include "TH1D.h"
#include "TH2D.h"
#include "TProfile.h"

#include "TRandom3.h"
#include "loc_funcs.h"
#include "common_funcs.h"

#define PI           3.141592653589793116
#define TWO_PI       6.283185307179586232
#define PI_MINUS_ONE 2.141592653589793116
#define PI0MASS2     0.0182196

const int debug_level=0;


const int pt_bin=600;
const double pt_min=0;
const double pt_max=30;

const int ntrk_bin=10;
const double ntrk_min=-0.5;
const double ntrk_max=9.5;

const int phi_bin=96;
const double phi_min=0;
const double phi_max=TWO_PI;


//This function is used to assign an event to a certain bin, whatever the parameter is
//The 0-th entry of "bound" is the lower bound of said parameter
//where the last should be the upper bound
static int define_bin(double param,vector<double> bound){
    int ibin=-1;
    vector<double>::iterator it=bound.begin();
    while( it != bound.end() ){
	if( param < *it ){ return ibin; }
	ibin++;
	it++;
    }
    return -2;
}

using namespace std;
void eff_phi(events& dat, string _options) {
    TH1::SetDefaultSumw2(true);
    TH2::SetDefaultSumw2(true);

    cout << " Running fn \"eff_phi\"" << endl;
    istringstream options ( _options );
    int n_options = 0;
    string arg;
    while (options >> arg) {
        cout    << " Option " << n_options << ":  " << arg << endl;
        dat.log << " Option " << n_options << ":  " << arg << endl;
        // msg_tree.msg(Form(" Options %i : %s", n_options, arg.c_str()));
        ++n_options;
    }

    // Histogram declarations here:
    vector<double> vz_bound={-35,-20,-5,10,25};
//    vector<double> vz_bound={-30,-15,0,15,30};
//    vector<double> ea_bound={0,1,3,5,100};
    vector<double> ea_bound={0,9, 12, 16, 21, 27, 35, 45, 56, 70, 86, 104, 126, 152, 181, 217, 259,10000};


//    vector<double> lumi_bound={0,8000,15000,23000,50000};
    vector<double> lumi_bound={0,100000};

    int lumi_bins=lumi_bound.size()-1;
    int ea_bins=ea_bound.size()-1;
    int vz_bins=vz_bound.size()-1;
    TH1F* nmctrk_nontrans[lumi_bins][ea_bins][vz_bins];
    TH1F* match_mc_phi[lumi_bins][ea_bins][vz_bins];
    TH2F* mc_reco_phi[lumi_bins][ea_bins][vz_bins];
    TH1F* gen_mc_phi[lumi_bins][ea_bins][vz_bins];
    TH1F* notrans_match_mc_phi[lumi_bins][ea_bins][vz_bins];
    TH2F* notrans_mc_reco_phi[lumi_bins][ea_bins][vz_bins];
    TH1F* notrans_gen_mc_phi[lumi_bins][ea_bins][vz_bins];
//
//The "notrans_" tag selects the near & recoil side MC tracks for effeciency study
//
    for(int i=0;i<lumi_bins;i++){
	for(int j=0;j<ea_bins;j++){
	    for(int k=0;k<vz_bins;k++){
		nmctrk_nontrans[i][j][k]=new TH1F(Form("nmctrk_nontrans_%i_%i_%i",i,j,k),"Number of MC tracks in the accepted region",ntrk_bin,ntrk_min,ntrk_max);
		mc_reco_phi[i][j][k]=new TH2F(Form("mc_reco_phi_%i_%i_%i",i,j,k),"MC vs reco pt;MC pt;Reco pt",phi_bin,phi_min,phi_max,phi_bin,phi_min,phi_max);
		match_mc_phi[i][j][k]=new TH1F(Form("match_mc_phi_%i_%i_%i",i,j,k),"Matched MC pt;MC pt;count",phi_bin,phi_min,phi_max);
		gen_mc_phi[i][j][k]=new TH1F(Form("gen_mc_phi_%i_%i_%i",i,j,k),"Generated MC pt;MC pt;count",phi_bin,phi_min,phi_max);
		notrans_mc_reco_phi[i][j][k]=new TH2F(Form("notrans_mc_reco_phi_%i_%i_%i",i,j,k),"MC vs reco pt;MC pt;Reco pt",phi_bin,phi_min,phi_max,phi_bin,phi_min,phi_max);
		notrans_match_mc_phi[i][j][k]=new TH1F(Form("notrans_match_mc_phi_%i_%i_%i",i,j,k),"Matched MC pt;MC pt;count",phi_bin,phi_min,phi_max);
		notrans_gen_mc_phi[i][j][k]=new TH1F(Form("notrans_gen_mc_phi_%i_%i_%i",i,j,k),"Generated MC pt;MC pt;count",phi_bin,phi_min,phi_max);
	    }
	}
    }

    TH1F* mu_phi=new TH1F("mu_phi","MuDst track phi distribution",phi_bin,phi_min,phi_max);
    TH1F* zdc_dist=new TH1F("ZDCx_distribution","ZDCx distribution",lumi_bins*50,lumi_bound[0],lumi_bound[lumi_bins]);
    TRandom3 ran_phi;
    ran_phi.SetSeed(0);

    // Run loop here:
    while (dat.next()) {
	if(debug_level)cout<<"Start working on event"<<endl;
	int ntrack=dat.track_;
	int nmctrk=dat.mc_track_;

	float vz=dat.vz;
	int   ibin_vz=define_bin(vz,vz_bound);

	float zdcx=dat.ZDCx;
	int   ibin_lumi=define_bin(zdcx,lumi_bound);
	zdc_dist->Fill(zdcx);
	if(ibin_vz < 0 ){
	    if(debug_level)
		cout<<"vz="<<vz<<" out of range!"<<endl;
	    continue;
	}
	if(ibin_lumi < 0 ){
	    if(debug_level)
		cout<<"zdcx="<<zdcx<<" out of range!"<<endl;
	    continue;
	}

	float phi_rantrig {(float) ran_phi.Uniform(0,TWO_PI)};

	vector<int> matched_trks={};
// Reco tracks matched to a MC track

 	for (int i=0;i<nmctrk;i++){
	    short mc_trk_id=dat.mc_track_id[i];
	    if(mc_trk_id<0){continue;}
	    matched_trks.push_back(mc_trk_id);
	}
	
	int randmult_embed=0,randmult_noembed=0;
	
	for(int i=0;i<ntrack;i++){
	    vector<int>::iterator it;
	    if(!(dat.track_pass_cuts[i] && (dat.track_nHitsFit[i] > 0.52*dat.track_nHitsPoss[i] )))continue; //
	    it = find(matched_trks.begin(),matched_trks.end(),i);
	    bool is_matched = (it == matched_trks.end()) ? false : true;
	    mu_phi->Fill(dat.track_phi[i]);
//	    if(is_phi_tran(phi_rantrig,dat.track_phi[i])) cout<<"It's transverse."<<phi_rantrig<<"\t"<<dat.track_phi[i]<<endl;	
	    bool is_trans=is_phi_tran(phi_rantrig,dat.track_phi[i]);
	    if( is_trans && dat.track_TOF_match ){
		randmult_embed++;
		if(!is_matched)randmult_noembed++;
	    }	    
	}
//	cout<<randmult<<"\t"<<randmult_embed<<endl;

	double mRefMult_corr=dat.refmult_corr();
	int ibin_ea=define_bin(mRefMult_corr,ea_bound);
//	int ibin_ea=define_bin(randmult_embed,ea_bound);
	
	if(debug_level)cout<<zdcx<<"\t"<<ibin_lumi<<"\t"<<mRefMult_corr<<"\t"<<ibin_ea<<"\t"<<vz<<"\t"<<ibin_vz<<endl;
//	cout<<dat.refMult<<endl;
//	cout<<"ibin_vz="<<ibin_vz<<" zdcx=" << zdcx <<" ibin_lumi="<<ibin_lumi<< " refmult_corr = "<< mRefMult_corr << " ibin_ea="<<ibin_ea<<endl;


	int nmctrack_nontrans=0;
 	if(debug_level) cout<<"Number of MC tracks is "<<nmctrk<<endl;
	for(int i=0;i<nmctrk;i++){
	    short mc_trk_id=dat.mc_track_id[i];
	    float mc_pt=dat.mc_track_pt[i];
	    float mc_phi=dat.mc_track_phi[i]; 
	    gen_mc_phi[ibin_lumi][ibin_ea][ibin_vz]->Fill(mc_phi);
	    bool mc_is_trans=is_phi_tran(phi_rantrig,dat.mc_track_phi[i]);
	    if(debug_level > 2){
		cout<<"Checkpoint 1 mc_phi is "<<mc_phi<<endl;
		if(mc_is_trans)cout<<"Is transverse"<<endl;
		else cout<<"Is not transverse"<<endl;
	    }
	    if(!mc_is_trans) notrans_gen_mc_phi[ibin_lumi][ibin_ea][ibin_vz]->Fill(mc_phi);
	    if(debug_level > 2)cout<<"Checkpoint 2"<<endl;
	    if(mc_trk_id<0)continue;
	    if(!(dat.track_pass_cuts[mc_trk_id] && (dat.track_nHitsFit[mc_trk_id] > 0.52*dat.track_nHitsPoss[mc_trk_id] )))continue;//
//	    TH1F* gen_mc_pt[lumi_bins][ea_bins][vz_bins];
	    float reco_phi=dat.track_phi[mc_trk_id];
	    mc_reco_phi[ibin_lumi][ibin_ea][ibin_vz]->Fill(mc_phi,reco_phi);
	    match_mc_phi[ibin_lumi][ibin_ea][ibin_vz]->Fill(mc_phi);
	    if(!mc_is_trans){
		notrans_mc_reco_phi[ibin_lumi][ibin_ea][ibin_vz]->Fill(mc_phi,reco_phi);
		notrans_match_mc_phi[ibin_lumi][ibin_ea][ibin_vz]->Fill(mc_phi);
		nmctrack_nontrans++;
	    }
	}
	nmctrk_nontrans[ibin_lumi][ibin_ea][ibin_vz]->Fill(nmctrack_nontrans);
    	if(debug_level) cout<<"Finish working on event."<<endl;
    }

    // Write histograms here
    // hg.Write();
    for(int i=0;i<lumi_bins;i++){
	for(int j=0;j<ea_bins;j++){
	    for(int k=0;k<vz_bins;k++){
		nmctrk_nontrans[i][j][k]->Write();
		mc_reco_phi[i][j][k]->Write();
		match_mc_phi[i][j][k]->Write();
		gen_mc_phi[i][j][k]->Write();
		notrans_mc_reco_phi[i][j][k]->Write();
		notrans_match_mc_phi[i][j][k]->Write();
		notrans_gen_mc_phi[i][j][k]->Write();
	    }
	}
    }
    mu_phi->Write();
    zdc_dist->Write();
    // Wrap-up work here:

    dat.log  << " Done running events" << endl;
    cout     << " Done running events" << endl;
}
