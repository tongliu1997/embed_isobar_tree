#include "../pp_reference/hist_pp.h"
#include "out_hist.h"



void outhist_systematics(
const string system="zr",
const string nominal_name="outhist_zr_2_3.root",
const string iter_name="outhist_zr_2_3_1iter.root",
const string pion_name="outhist_zr_pion_2_3.root",
const string smear_name="outhist_zr_smear_2_3.root",
const string out_name="systematics_zr_2_3.root",
std::vector<int> bins={0,10,20,40,60,80}

){
//    out_hist nominal_plots(nominal_name);
    out_hist* nominal_plots=new out_hist(nominal_name,bins,system,"");
    out_hist* iter_plots=new out_hist(iter_name,bins,system,"");
    out_hist* pion_plots=new out_hist(pion_name,bins,system,"_pion");
    out_hist* smear_plots=new out_hist(smear_name,bins,system,"_smear");

//    cout<<pion_plots[0].unfold_spec[0]->GetNbinsX()<<endl;
    nominal_plots->set_name("_systematics");
    nominal_plots->clear_error();
    nominal_plots->add_error(iter_plots);
    nominal_plots->add_error(pion_plots);
    nominal_plots->add_error(smear_plots);
//    nominal_plots->add_error(0.05);
    

//    nominal_plots->add_smear();
//    nominal_plots->unfold_spec[0]->Draw();

    nominal_plots->Write(out_name);

    return;

}
