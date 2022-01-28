#include "species_plots.h"

void counts(
const string key_str="proton",
const string input_key="out-data/hadd_random_trk"
){

const string lowpt_filename(Form("%s_%s.root",input_key.c_str(),key_str.c_str()));
const string highpt_filename(Form("%s_%s_highpt.root",input_key.c_str(),key_str.c_str()));
cout<<lowpt_filename<<"\t"<<highpt_filename<<endl;


species_plots lowpt(lowpt_filename,"",key_str);
cout<<"High pt file name is "<<highpt_filename<<endl;
species_plots highpt(highpt_filename,"",Form("%s_highpt",key_str.c_str()));

int lowpt_count=0,highpt_count=0;


for(int i=0;i<species_plots::lumi_bins;i++){
    for(int j=0;j<species_plots::ea_bins;j++){
        for(int k=0;k<species_plots::vz_bins;k++){
	    lowpt_count+=lowpt.gen_mc_pt[i][j][k]->GetEntries();
	    highpt_count+=highpt.gen_mc_pt[i][j][k]->GetEntries();
	    
	}
    }
}

cout<<lowpt_count<<"\t"<<highpt_count<<endl;
cout<<1.*lowpt_count/highpt_count<<endl;
}
