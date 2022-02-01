
#include "events.h"
#include <sstream>
#include <fstream>

#include "TH1D.h"
#include "TH2D.h"
#include "TProfile.h"

using namespace std;
void test_loop(events& dat, string _options) {
    cout << " Running fn \"test_loop\"" << endl;
    istringstream options ( _options );
    int n_options = 0;
    string arg;
//    ioMsgTree msg_tree{false};
    // msg_tree.slurp_file("src/test_loop.cxx");
    while (options >> arg) {
        cout    << " Option " << n_options << ":  " << arg << endl;
        dat.log << " Option " << n_options << ":  " << arg << endl;
        // msg_tree.msg(Form(" Options %i : %s", n_options, arg.c_str()));
        ++n_options;
    }
    // msg_tree.write();

    // Histogram declarations here:
    // TH1D hg {"hg", "a;b;c", 10, 0., 1.};


    // Run loop here:
    while (dat.next()) {
        // cout << " Doing nothing in event " << dat.jentry << endl;
        // dat.log  << " Doing nothing in event " << dat.jentry << endl;
        // hg.Fill( x );
	cout << dat.vz << endl;
    }

    // Write histograms here
    // hg.Write();


    // Wrap-up work here:
    dat.log  << " Done running events" << endl;
    cout     << " Done running events" << endl;
}
