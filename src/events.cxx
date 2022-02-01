
#define events_cxx
#include "events.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

using namespace std;


events::events(ofstream& _log, int _n_events, TString inp_file) :
    nevents{_n_events},
    log {_log}, 
    stats {1000},
    jentry {-1}
{
    TChain* tree  = new TChain("events");
    if (inp_file.EndsWith(".root")) {
            cout << " Adding input file: " << inp_file << endl;
        tree->Add(inp_file.Data());
    } else if (inp_file.EndsWith(".list")) {
        string line;
        ifstream list;
        list.open(inp_file.Data());
        while (getline(list, line)){
            cout << " Adding input file: " << line << endl;
            tree->Add(line.c_str());
        }
        list.close();
    }
    /* cout << " has " << tree->GetEntries() << " in tree" << endl; */
    /* cout << " has " << tree->GetEntriesFast() << " in tree" << endl; */
    Init(tree);

    //Set the trigger map

    nentries = tree->GetEntries();
    if (nevents == -1) nevents = nentries;
    cout<<"nentries = "<<nentries<<endl;


}
events::~events()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t events::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t events::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void events::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   //:TAG START: Set Branches
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("mc_Cjet", &mc_Cjet_, &b_mc_Cjet_);
   fChain->SetBranchAddress("mc_Cjet.fUniqueID", mc_Cjet_fUniqueID, &b_mc_Cjet_fUniqueID);
   fChain->SetBranchAddress("mc_Cjet.fBits", mc_Cjet_fBits, &b_mc_Cjet_fBits);
   fChain->SetBranchAddress("mc_Cjet.pt", mc_Cjet_pt, &b_mc_Cjet_pt);
   fChain->SetBranchAddress("mc_Cjet.eta", mc_Cjet_eta, &b_mc_Cjet_eta);
   fChain->SetBranchAddress("mc_Cjet.phi", mc_Cjet_phi, &b_mc_Cjet_phi);
   fChain->SetBranchAddress("mc_Cjet.area", mc_Cjet_area, &b_mc_Cjet_area);
   fChain->SetBranchAddress("mc_Cjet.index_track", mc_Cjet_index_track, &b_mc_Cjet_index_track);
   fChain->SetBranchAddress("mc_Cjet.index_tower", mc_Cjet_index_tower, &b_mc_Cjet_index_tower);
   fChain->SetBranchAddress("mc_Cjet_rho", &mc_Cjet_rho, &b_mc_Cjet_rho);
   fChain->SetBranchAddress("mc_Cjet_rho_sigma", &mc_Cjet_rho_sigma, &b_mc_Cjet_rho_sigma);
   fChain->SetBranchAddress("Cjet", &Cjet_, &b_Cjet_);
   fChain->SetBranchAddress("Cjet.fUniqueID", Cjet_fUniqueID, &b_Cjet_fUniqueID);
   fChain->SetBranchAddress("Cjet.fBits", Cjet_fBits, &b_Cjet_fBits);
   fChain->SetBranchAddress("Cjet.pt", Cjet_pt, &b_Cjet_pt);
   fChain->SetBranchAddress("Cjet.eta", Cjet_eta, &b_Cjet_eta);
   fChain->SetBranchAddress("Cjet.phi", Cjet_phi, &b_Cjet_phi);
   fChain->SetBranchAddress("Cjet.area", Cjet_area, &b_Cjet_area);
   fChain->SetBranchAddress("Cjet.index_track", Cjet_index_track, &b_Cjet_index_track);
   fChain->SetBranchAddress("Cjet.index_tower", Cjet_index_tower, &b_Cjet_index_tower);
   fChain->SetBranchAddress("Cjet_rho", &Cjet_rho, &b_Cjet_rho);
   fChain->SetBranchAddress("Cjet_rho_sigma", &Cjet_rho_sigma, &b_Cjet_rho_sigma);
   fChain->SetBranchAddress("Fjet", &Fjet_, &b_Fjet_);
   fChain->SetBranchAddress("Fjet.fUniqueID", Fjet_fUniqueID, &b_Fjet_fUniqueID);
   fChain->SetBranchAddress("Fjet.fBits", Fjet_fBits, &b_Fjet_fBits);
   fChain->SetBranchAddress("Fjet.pt", Fjet_pt, &b_Fjet_pt);
   fChain->SetBranchAddress("Fjet.eta", Fjet_eta, &b_Fjet_eta);
   fChain->SetBranchAddress("Fjet.phi", Fjet_phi, &b_Fjet_phi);
   fChain->SetBranchAddress("Fjet.area", Fjet_area, &b_Fjet_area);
   fChain->SetBranchAddress("Fjet.index_track", Fjet_index_track, &b_Fjet_index_track);
   fChain->SetBranchAddress("Fjet.index_tower", Fjet_index_tower, &b_Fjet_index_tower);
   fChain->SetBranchAddress("Fjet_rho", &Fjet_rho, &b_Fjet_rho);
   fChain->SetBranchAddress("Fjet_rho_sigma", &Fjet_rho_sigma, &b_Fjet_rho_sigma);
   fChain->SetBranchAddress("fUniqueID", &fUniqueID, &b_mu_event_fUniqueID);
   fChain->SetBranchAddress("fBits", &fBits, &b_mu_event_fBits);
   fChain->SetBranchAddress("runId", &runId, &b_mu_event_runId);
   fChain->SetBranchAddress("eventId", &eventId, &b_mu_event_eventId);
   fChain->SetBranchAddress("ZDCx", &ZDCx, &b_mu_event_ZDCx);
   fChain->SetBranchAddress("vx", &vx, &b_mu_event_vx);
   fChain->SetBranchAddress("vy", &vy, &b_mu_event_vy);
   fChain->SetBranchAddress("vz", &vz, &b_mu_event_vz);
   fChain->SetBranchAddress("BBC_Ein", &BBC_Ein, &b_mu_event_BBC_Ein);
   fChain->SetBranchAddress("BBC_Eout", &BBC_Eout, &b_mu_event_BBC_Eout);
   fChain->SetBranchAddress("BBC_Win", &BBC_Win, &b_mu_event_BBC_Win);
   fChain->SetBranchAddress("BBC_Wout", &BBC_Wout, &b_mu_event_BBC_Wout);
   fChain->SetBranchAddress("vzVpd", &vzVpd, &b_mu_event_vzVpd);
   fChain->SetBranchAddress("ranking", &ranking, &b_mu_event_ranking);
   fChain->SetBranchAddress("ZdcSumAdcEast", &ZdcSumAdcEast, &b_mu_event_ZdcSumAdcEast);
   fChain->SetBranchAddress("ZdcSumAdcWest", &ZdcSumAdcWest, &b_mu_event_ZdcSumAdcWest);
   fChain->SetBranchAddress("ZdcSmdEastHorizontal[8]", ZdcSmdEastHorizontal, &b_mu_event_ZdcSmdEastHorizontal);
   fChain->SetBranchAddress("ZdcSmdEastVertical[8]", ZdcSmdEastVertical, &b_mu_event_ZdcSmdEastVertical);
   fChain->SetBranchAddress("ZdcSmdWestHorizontal[8]", ZdcSmdWestHorizontal, &b_mu_event_ZdcSmdWestHorizontal);
   fChain->SetBranchAddress("ZdcSmdWestVertical[8]", ZdcSmdWestVertical, &b_mu_event_ZdcSmdWestVertical);
   fChain->SetBranchAddress("EastBBC[24]", EastBBC, &b_mu_event_EastBBC);
   fChain->SetBranchAddress("WestBBC[24]", WestBBC, &b_mu_event_WestBBC);
   fChain->SetBranchAddress("refMult", &refMult, &b_mu_event_refMult);
   fChain->SetBranchAddress("pthat_min", &pthat_min, &b_pthat_min);
   fChain->SetBranchAddress("pthat_max", &pthat_max, &b_pthat_max);
   fChain->SetBranchAddress("pthat_bin", &pthat_bin, &b_pthat_bin);
   fChain->SetBranchAddress("mc_track", &mc_track_, &b_mc_track_);
   fChain->SetBranchAddress("mc_track.fUniqueID", mc_track_fUniqueID, &b_mc_track_fUniqueID);
   fChain->SetBranchAddress("mc_track.fBits", mc_track_fBits, &b_mc_track_fBits);
   fChain->SetBranchAddress("mc_track.geantId", mc_track_geantId, &b_mc_track_geantId);
   fChain->SetBranchAddress("mc_track.id", mc_track_id, &b_mc_track_id);
   fChain->SetBranchAddress("mc_track.pt", mc_track_pt, &b_mc_track_pt);
   fChain->SetBranchAddress("mc_track.eta", mc_track_eta, &b_mc_track_eta);
   fChain->SetBranchAddress("mc_track.phi", mc_track_phi, &b_mc_track_phi);
   fChain->SetBranchAddress("track", &track_, &b_track_);
   fChain->SetBranchAddress("track.fUniqueID", track_fUniqueID, &b_track_fUniqueID);
   fChain->SetBranchAddress("track.fBits", track_fBits, &b_track_fBits);
   fChain->SetBranchAddress("track.pt", track_pt, &b_track_pt);
   fChain->SetBranchAddress("track.eta", track_eta, &b_track_eta);
   fChain->SetBranchAddress("track.phi", track_phi, &b_track_phi);
   fChain->SetBranchAddress("track.dcaXY", track_dcaXY, &b_track_dcaXY);
   fChain->SetBranchAddress("track.dcaXYZ", track_dcaXYZ, &b_track_dcaXYZ);
   fChain->SetBranchAddress("track.TOF_match", track_TOF_match, &b_track_TOF_match);
   fChain->SetBranchAddress("track.BEMC_match", track_BEMC_match, &b_track_BEMC_match);
   fChain->SetBranchAddress("track.towerID", track_towerID, &b_track_towerID);
   fChain->SetBranchAddress("track.towerEt", track_towerEt, &b_track_towerEt);
   fChain->SetBranchAddress("track.nHitsFit", track_nHitsFit, &b_track_nHitsFit);
   fChain->SetBranchAddress("track.nHitsPoss", track_nHitsPoss, &b_track_nHitsPoss);
   fChain->SetBranchAddress("track.nHitsDedx", track_nHitsDedx, &b_track_nHitsDedx);
   fChain->SetBranchAddress("track.pass_cuts", track_pass_cuts, &b_track_pass_cuts);
   fChain->SetBranchAddress("tower", &tower_, &b_tower_);
   fChain->SetBranchAddress("tower.fUniqueID", tower_fUniqueID, &b_tower_fUniqueID);
   fChain->SetBranchAddress("tower.fBits", tower_fBits, &b_tower_fBits);
   fChain->SetBranchAddress("tower.Et", tower_Et, &b_tower_Et);
   fChain->SetBranchAddress("tower.eta", tower_eta, &b_tower_eta);
   fChain->SetBranchAddress("tower.phi", tower_phi, &b_tower_phi);
   fChain->SetBranchAddress("tower.Et_hadroncorr", tower_Et_hadroncorr, &b_tower_Et_hadroncorr);
   fChain->SetBranchAddress("tower.towerID", tower_towerID, &b_tower_towerID);
   //:TAG END: Set Branches
   Notify();
}

Bool_t events::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void events::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t events::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}

bool events::next() {
    jentry++;
    if (jentry >= nevents) {
        stats.set_get_stats();
        log  << " Final stats: " << stats.stats << endl; 
        return false;
    }
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) {
        cout << " Breaking out of loop at jentry on failure to read ientry: " << jentry << endl;
        stats.set_get_stats();
        log  << " Final stats: " << stats.stats << endl; 
        return false;
    }
    fChain->GetEntry(jentry);
    if (stats.call()) log << stats.stats << endl;
    return true;
}

//:TAG START: Coda Functions
//:TAG END: Coda Functions


// warning, below function will seg-fault if trigger is not in map
bool  events::has_trigger(int i_trig) { return *(trigger_map[i_trig]); };
bool  events::has_trigger_all(vector<int> triggers) { 
    for (auto T : triggers)  if (! *(trigger_map[T])) return false;
    return true;
};
bool  events::has_trigger_any(vector<int> triggers) { 
    for (auto T : triggers)  if (*(trigger_map[T])) return true;
    return false;
};

void events::set_system(System i){

    cout<<"System set to be "<<i<<endl;
    vz_par_.clear();
    zdc_par_.clear();
    switch(i){
    case Ru:
	vz_par_=vz_par_ru;
  	zdc_par_=zdc_par_ru;
	break;
    case Zr:
	vz_par_=vz_par_zr;
 	zdc_par_=zdc_par_zr;
	break;
    case Mix:
	for(int i=0;i<vz_par_zr.size();i++){
	    double buff=(vz_par_zr[i]+vz_par_ru[i])/2.0;
	    vz_par_.push_back(buff);
	}
	for(int i=0;i<zdc_par_zr.size();i++){
	    double buff=(zdc_par_zr[i]+zdc_par_ru[i])/2.0;
	    zdc_par_.push_back(buff);
	}
	
    }
    current_system=i;

}


double events::refmult_corr(){

//  int _mult= (mult == -1)? refMult : mult;
  int _mult=  refMult;
  double zdc_standard = zdc_par_[0] + zdc_par_[1] * zdc_norm /1000.0;
  double zdc_scale = zdc_par_[0] + zdc_par_[1] * ZDCx / 1000.0;

  double vz_standard = 0;
  double vz_scale = 0;
  
  for(int i=0;i<vz_par_.size();i++){
    vz_standard += vz_par_[i]*pow(vz_norm,i);
    vz_scale += vz_par_[i]*pow(vz,i);
  }
  double zdc_correction=zdc_standard/zdc_scale;
  double vz_correction=1.0;
  if(vz_scale > 0 ) vz_correction = vz_standard / vz_scale ;

//  cout<<_mult<<"\t"<<vz_correction<<"\t"<<ZDCx<<"\t"<<zdc_correction<<endl;

  double corrected = _mult * vz_correction * zdc_correction;
  return corrected;

}

