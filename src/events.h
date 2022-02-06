
#ifndef events_h
#define events_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "TObject.h"
#include "TClonesArray.h"

#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include "MemTimeProgression.h"



// template to iterate through TClonesArray members
// (will be used with members that return values with the add_class_lib.py loop)
// will allow iteration such as ` for (auto track : dat.iter_track() ) { /* do stuff */ };
template <class T> struct iterTCA {
    TClonesArray* tca;
    T* ptr;
    iterTCA  (TClonesArray* _tca) : tca{_tca} {};

    int index{0};
    iterTCA begin() {
        iterTCA iter {tca};
        iter.ptr = (T*) tca->UncheckedAt(0);
        return iter;
    };
    iterTCA end() {
        iterTCA iter {tca};
        iter.ptr=(T*)tca->UncheckedAt(tca->GetEntriesFast());
        return iter;
    };
    void operator++() {ptr=(T*)tca->UncheckedAt(++index);};
    T& operator*() {return *ptr;};
    bool operator!=(const iterTCA& rhs) { return ptr!=rhs.ptr;};
};


class events {
   private:
   vector<double> vz_par_;
   vector<double> zdc_par_;
   const double vz_norm=0;
   const double zdc_norm=10300;

   const vector<double> vz_par_zr={300.3, 0.03587, -0.0005492, 0.0002321, 
                        5.868e-06,-2.919e-07, -6.337e-09};
   const vector<double> vz_par_ru={302.0, 0.02703, -0.00178, 0.0002438, 
                        1.185e-05,-3.312e-07, -1.227e-08}; 
   const vector<double> zdc_par_zr={98.412, -1.3917e-04};
   const vector<double> zdc_par_ru={98.113, -1.162e-05};

   const vector<double> weight_par={1.34842, -12.8629, 0.767038, 4.2547, -0.00264771,
                          357.779, 5.10897e-06}; 

public :
   enum System
   {
	Ru=0, Zr, Mix
   };


   System  current_system;




   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain
   long long int nevents;
   ofstream &log;
   MemTimeProgression stats;

//:TAG START:  Array Sizes
// Fixed size dimensions of array or collections stored in the TTree if any.
   static constexpr Int_t kMaxmc_Cjet = 200;
   static constexpr Int_t kMaxCjet = 200;
   static constexpr Int_t kMaxFjet = 200;
   static constexpr Int_t kMaxmc_track = 1000;
   static constexpr Int_t kMaxtrack = 1000;
   static constexpr Int_t kMaxtower = 2000;
//:TAG END: Array Sizes

//:TAG START: Leaf Types
  // Declaration of leaf types
   Int_t           mc_Cjet_;
   UInt_t          mc_Cjet_fUniqueID[kMaxmc_Cjet];   //[mc_Cjet_]
   UInt_t          mc_Cjet_fBits[kMaxmc_Cjet];   //[mc_Cjet_]
   Float_t         mc_Cjet_pt[kMaxmc_Cjet];   //[mc_Cjet_]
   Float_t         mc_Cjet_eta[kMaxmc_Cjet];   //[mc_Cjet_]
   Float_t         mc_Cjet_phi[kMaxmc_Cjet];   //[mc_Cjet_]
   Float_t         mc_Cjet_area[kMaxmc_Cjet];   //[mc_Cjet_]
   vector<short>   mc_Cjet_index_track[kMaxmc_Cjet];
   vector<short>   mc_Cjet_index_tower[kMaxmc_Cjet];
   Float_t         mc_Cjet_rho;
   Float_t         mc_Cjet_rho_sigma;
   Int_t           Cjet_;
   UInt_t          Cjet_fUniqueID[kMaxCjet];   //[Cjet_]
   UInt_t          Cjet_fBits[kMaxCjet];   //[Cjet_]
   Float_t         Cjet_pt[kMaxCjet];   //[Cjet_]
   Float_t         Cjet_eta[kMaxCjet];   //[Cjet_]
   Float_t         Cjet_phi[kMaxCjet];   //[Cjet_]
   Float_t         Cjet_area[kMaxCjet];   //[Cjet_]
   vector<short>   Cjet_index_track[kMaxCjet];
   vector<short>   Cjet_index_tower[kMaxCjet];
   Float_t         Cjet_rho;
   Float_t         Cjet_rho_sigma;
   Int_t           Fjet_;
   UInt_t          Fjet_fUniqueID[kMaxFjet];   //[Fjet_]
   UInt_t          Fjet_fBits[kMaxFjet];   //[Fjet_]
   Float_t         Fjet_pt[kMaxFjet];   //[Fjet_]
   Float_t         Fjet_eta[kMaxFjet];   //[Fjet_]
   Float_t         Fjet_phi[kMaxFjet];   //[Fjet_]
   Float_t         Fjet_area[kMaxFjet];   //[Fjet_]
   vector<short>   Fjet_index_track[kMaxFjet];
   vector<short>   Fjet_index_tower[kMaxFjet];
   Float_t         Fjet_rho;
   Float_t         Fjet_rho_sigma;
 //mupicoEventHeader *mu_event;
   UInt_t          fUniqueID;
   UInt_t          fBits;
   Int_t           runId;
   Int_t           eventId;
   Float_t         ZDCx;
   Float_t         vx;
   Float_t         vy;
   Float_t         vz;
   Int_t           BBC_Ein;
   Int_t           BBC_Eout;
   Int_t           BBC_Win;
   Int_t           BBC_Wout;
   Float_t         vzVpd;
   Float_t         ranking;
   Int_t           ZdcSumAdcEast;
   Int_t           ZdcSumAdcWest;
   Short_t         ZdcSmdEastHorizontal[8];
   Short_t         ZdcSmdEastVertical[8];
   Short_t         ZdcSmdWestHorizontal[8];
   Short_t         ZdcSmdWestVertical[8];
   Short_t         EastBBC[24];
   Short_t         WestBBC[24];
   Short_t         refMult;
   Short_t         pthat_min;
   Short_t         pthat_max;
   Short_t         pthat_bin;
   Int_t           mc_track_;
   UInt_t          mc_track_fUniqueID[kMaxmc_track];   //[mc_track_]
   UInt_t          mc_track_fBits[kMaxmc_track];   //[mc_track_]
   Short_t         mc_track_geantId[kMaxmc_track];   //[mc_track_]
   Short_t         mc_track_id[kMaxmc_track];   //[mc_track_]
   Float_t         mc_track_pt[kMaxmc_track];   //[mc_track_]
   Float_t         mc_track_eta[kMaxmc_track];   //[mc_track_]
   Float_t         mc_track_phi[kMaxmc_track];   //[mc_track_]
   Int_t           track_;
   UInt_t          track_fUniqueID[kMaxtrack];   //[track_]
   UInt_t          track_fBits[kMaxtrack];   //[track_]
   Float_t         track_pt[kMaxtrack];   //[track_]
   Float_t         track_eta[kMaxtrack];   //[track_]
   Float_t         track_phi[kMaxtrack];   //[track_]
   Float_t         track_dcaXY[kMaxtrack];   //[track_]
   Float_t         track_dcaXYZ[kMaxtrack];   //[track_]
   Bool_t          track_TOF_match[kMaxtrack];   //[track_]
   Bool_t          track_BEMC_match[kMaxtrack];   //[track_]
   Short_t         track_towerID[kMaxtrack];   //[track_]
   Float_t         track_towerEt[kMaxtrack];   //[track_]
   Short_t         track_nHitsFit[kMaxtrack];   //[track_]
   Short_t         track_nHitsPoss[kMaxtrack];   //[track_]
   Short_t         track_nHitsDedx[kMaxtrack];   //[track_]
   Bool_t          track_pass_cuts[kMaxtrack];   //[track_]
//Cuts used: nHitsFit 15, dcaXYZ 3
   Int_t           tower_;
   UInt_t          tower_fUniqueID[kMaxtower];   //[tower_]
   UInt_t          tower_fBits[kMaxtower];   //[tower_]
   Float_t         tower_Et[kMaxtower];   //[tower_]
   Float_t         tower_eta[kMaxtower];   //[tower_]
   Float_t         tower_phi[kMaxtower];   //[tower_]
   Float_t         tower_Et_hadroncorr[kMaxtower];   //[tower_]
   Short_t         tower_towerID[kMaxtower];   //[tower_]

//:TAG END: Leaf Types

//:TAG START: Declare Branches
   // List of branches
   TBranch        *b_mc_Cjet_;   //!
   TBranch        *b_mc_Cjet_fUniqueID;   //!
   TBranch        *b_mc_Cjet_fBits;   //!
   TBranch        *b_mc_Cjet_pt;   //!
   TBranch        *b_mc_Cjet_eta;   //!
   TBranch        *b_mc_Cjet_phi;   //!
   TBranch        *b_mc_Cjet_area;   //!
   TBranch        *b_mc_Cjet_index_track;   //!
   TBranch        *b_mc_Cjet_index_tower;   //!
   TBranch        *b_mc_Cjet_rho;   //!
   TBranch        *b_mc_Cjet_rho_sigma;   //!
   TBranch        *b_Cjet_;   //!
   TBranch        *b_Cjet_fUniqueID;   //!
   TBranch        *b_Cjet_fBits;   //!
   TBranch        *b_Cjet_pt;   //!
   TBranch        *b_Cjet_eta;   //!
   TBranch        *b_Cjet_phi;   //!
   TBranch        *b_Cjet_area;   //!
   TBranch        *b_Cjet_index_track;   //!
   TBranch        *b_Cjet_index_tower;   //!
   TBranch        *b_Cjet_rho;   //!
   TBranch        *b_Cjet_rho_sigma;   //!
   TBranch        *b_Fjet_;   //!
   TBranch        *b_Fjet_fUniqueID;   //!
   TBranch        *b_Fjet_fBits;   //!
   TBranch        *b_Fjet_pt;   //!
   TBranch        *b_Fjet_eta;   //!
   TBranch        *b_Fjet_phi;   //!
   TBranch        *b_Fjet_area;   //!
   TBranch        *b_Fjet_index_track;   //!
   TBranch        *b_Fjet_index_tower;   //!
   TBranch        *b_Fjet_rho;   //!
   TBranch        *b_Fjet_rho_sigma;   //!
   TBranch        *b_mu_event_fUniqueID;   //!
   TBranch        *b_mu_event_fBits;   //!
   TBranch        *b_mu_event_runId;   //!
   TBranch        *b_mu_event_eventId;   //!
   TBranch        *b_mu_event_ZDCx;   //!
   TBranch        *b_mu_event_vx;   //!
   TBranch        *b_mu_event_vy;   //!
   TBranch        *b_mu_event_vz;   //!
   TBranch        *b_mu_event_BBC_Ein;   //!
   TBranch        *b_mu_event_BBC_Eout;   //!
   TBranch        *b_mu_event_BBC_Win;   //!
   TBranch        *b_mu_event_BBC_Wout;   //!
   TBranch        *b_mu_event_vzVpd;   //!
   TBranch        *b_mu_event_ranking;   //!
   TBranch        *b_mu_event_ZdcSumAdcEast;   //!
   TBranch        *b_mu_event_ZdcSumAdcWest;   //!
   TBranch        *b_mu_event_ZdcSmdEastHorizontal;   //!
   TBranch        *b_mu_event_ZdcSmdEastVertical;   //!
   TBranch        *b_mu_event_ZdcSmdWestHorizontal;   //!
   TBranch        *b_mu_event_ZdcSmdWestVertical;   //!
   TBranch        *b_mu_event_EastBBC;   //!
   TBranch        *b_mu_event_WestBBC;   //!
   TBranch        *b_mu_event_refMult;   //!
   TBranch        *b_pthat_min;   //!
   TBranch        *b_pthat_max;   //!
   TBranch        *b_pthat_bin;   //!
   TBranch        *b_mc_track_;   //!
   TBranch        *b_mc_track_fUniqueID;   //!
   TBranch        *b_mc_track_fBits;   //!
   TBranch        *b_mc_track_geantId;   //!
   TBranch        *b_mc_track_id;   //!
   TBranch        *b_mc_track_pt;   //!
   TBranch        *b_mc_track_eta;   //!
   TBranch        *b_mc_track_phi;   //!
   TBranch        *b_track_;   //!
   TBranch        *b_track_fUniqueID;   //!
   TBranch        *b_track_fBits;   //!
   TBranch        *b_track_pt;   //!
   TBranch        *b_track_eta;   //!
   TBranch        *b_track_phi;   //!
   TBranch        *b_track_dcaXY;   //!
   TBranch        *b_track_dcaXYZ;   //!
   TBranch        *b_track_TOF_match;   //!
   TBranch        *b_track_BEMC_match;   //!
   TBranch        *b_track_towerID;   //!
   TBranch        *b_track_towerEt;   //!
   TBranch        *b_track_nHitsFit;   //!
   TBranch        *b_track_nHitsPoss;   //!
   TBranch        *b_track_nHitsDedx;   //!
   TBranch        *b_track_pass_cuts;   //!
   TBranch        *b_tower_;   //!
   TBranch        *b_tower_fUniqueID;   //!
   TBranch        *b_tower_fBits;   //!
   TBranch        *b_tower_Et;   //!
   TBranch        *b_tower_eta;   //!
   TBranch        *b_tower_phi;   //!
   TBranch        *b_tower_Et_hadroncorr;   //!
   TBranch        *b_tower_towerID;   //!
//:TAG END: Declare Branches

   map<int,bool*>      	trigger_map;
   bool                	has_trigger(int);
   bool                	has_trigger_all(vector<int>);
   bool                	has_trigger_any(vector<int>);

   void 		set_system(System i=Ru);

// 0 for Ru, 1 for Zr, 2 for mix
   double		refmult_corr();

   events(ofstream& log, int n_events, TString inlist);
   virtual ~events();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);

   // values for running the loop
   bool next();
   Long64_t nentries;
   Long64_t jentry;

   // Make friend functions to fill in the runs
   // i.e. friend void runLoop(events&, string);
   // TAG: start-friend-functions
   friend void eff_phi(events&, string);
   friend void random_trk(events&, string);
   friend void test_loop(events&, string);

};
#endif
