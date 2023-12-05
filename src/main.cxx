
#include "events.h"
#include <sstream>
#include <fstream>
#include "TFile.h"
// #include <algorithm>
using namespace std;



int main(int nargs, char** argv) {
    /*
     * arguments:
     *   1: number of events
     *   2: input root file list name
     *   3: which program to run
     *   4: output base-name
     *   5: collision system (Ru/Zr/Mix)
     *   6: optional input
     */

    int n_events          {  (nargs>1) ? atoi(argv[1]) : 100 };
    string inp_list       {  (nargs>2) ? argv[2] : "in-lists/list_test.list" };
    string which_loop     {  (nargs>3) ? argv[3] : "eff_phi" };
    string o_name_tag     {  (nargs>4) ? argv[4] : "eff_phi" };
    string which_system   {  (nargs>5) ? argv[5] : "Ru" };
    ostringstream collect;
    for (int i{6};i<nargs;++i) {
//    for (int i{5};i<nargs;++i) {
        string arg {argv[i]};
        collect << arg << " ";
    }

    ofstream log;
    log.open((o_name_tag + ".log").c_str());
    log << "Starting output."  << endl
        << "Command line input:" << endl;
    for (int i{0}; i<nargs; ++i) log << "arg("<<i<<")  " << argv[i] << endl;
    log << endl << endl;

    events my_events{log, n_events, inp_list};
    if(which_system == "Ru") my_events.set_system(events::Ru);
    else if(which_system == "Zr") my_events.set_system(events::Zr);
    else if(which_system == "Mix") my_events.set_system(events::Mix);
    else{cout<<"System setup not recognized."<<endl; return -1;}
   
    
    TFile fout  { (o_name_tag+".root").c_str(), "recreate" };

    // run the loop
    cout << " Looking for function: " << which_loop << endl;
    if (which_loop == "empty-loop") {
        // TAG: empty-loop
   } else if (which_loop == "eff_phi") {
        eff_phi(my_events, collect.str());
   } else if (which_loop == "random_trk") {
        random_trk(my_events, collect.str());
   } else if (which_loop == "test_loop") {
        test_loop(my_events, collect.str());
    } else {
        cout << " -  Fatal error: couldn't find loop \"" << which_loop << "\"" << endl
            << "     ->  Terminating program." << endl;
    }
    fout.Close();
    log.close();
};
