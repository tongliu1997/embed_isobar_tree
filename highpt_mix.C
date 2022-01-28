#include "species_plots.h"

void highpt_mix(
const string key_str="proton",
const string input_key="out-data/hadd_random_trk"
){



const string lowpt_filename(Form("%s_%s.root",input_key.c_str(),key_str.c_str()));
const string highpt_filename(Form("%s_%s_highpt.root",input_key.c_str(),key_str.c_str()));
cout<<lowpt_filename<<"\t"<<highpt_filename<<endl;


species_plots lowpt(lowpt_filename,"",key_str);
//species_plots lowpt(lowpt_filename);
cout<<"High pt file name is "<<highpt_filename<<endl;
species_plots highpt(highpt_filename,"",Form("%s_highpt",key_str.c_str()));
//species_plots highpt(highpt_filename);

species_plots mixed(true,Form("%s_pt_mixed",key_str.c_str()));

//double scale_factor=100/6;
//if(key_str=="piplus" || key_str=="piminus") scale_factor=500/6;


cout<<2.2*lowpt.ZDCx_distribution->Integral()/highpt.ZDCx_distribution->GetEntries()<<endl;

double high_trks=0,low_trks=0;
for(int i=0;i<species_plots::lumi_bins;i++){
    for(int j=0;j<species_plots::ea_bins;j++){
	for(int k=0;k<species_plots::vz_bins;k++){
//	    cout<<i<<"\t"<<j<<"\t"<<k<<endl;
	    high_trks+=highpt.gen_mc_pt[i][j][k]->GetEntries();
	    low_trks+=lowpt.gen_mc_pt[i][j][k]->GetEntries();
	}
    }
}

cout<<low_trks<<"\t"<<high_trks<<endl;
//double scale_factor=75.0/24.0*(low_trks-high_trks)/high_trks-1;
double scale_factor=75.0/24.0*low_trks/high_trks;
cout<<scale_factor<<endl;


mixed.add(lowpt);
mixed.add(highpt,scale_factor);

mixed.write(Form("out-data/hadd_random_trk_%s_pt_mixed.root",key_str.c_str()));


}
