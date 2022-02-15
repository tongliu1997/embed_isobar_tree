#include "species_plots.h"


double Interpolate(int size,double* coord,double* wt,double x){
    double max_coord=coord[size-1];
    double min_coord=coord[0];
    if (x>=max_coord) return wt[size-1]; 
    if (x<=min_coord) return wt[0];
    for(int i=0;i<size-1;i++){
	if(x>coord[i+1])continue;
	if(x==coord[i+1])return wt[i+1];
	double dist=1.*(x-coord[i])/(coord[i+1]-coord[i]);
	return dist*wt[i]+(1-dist)*wt[i+1];	
    }
    return -1;
}


TH1F** read_weight(const char* weightname){
//read off weighting between species
double wt[7][60];

FILE* weightfile=fopen(weightname,"r");
//*wt=(double **)malloc(sizeof(double *)*60);
for(int i=0;i<60;i++){
//    (*wt)[i]=(double *)malloc(sizeof(double)*7);
    fscanf(weightfile,"%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\n",&(wt[0][i]),&(wt[1][i]),&(wt[2][i]),&(wt[3][i]),&(wt[4][i]),&(wt[5][i]),&(wt[6][i]));


}
//0th column: center pt
//1st: proton
//2nd: antiproton
//3rd: kplus
//4th: kminus
//5th: piplus
//6th: piminus
//return wt;

TH1F** weights=(TH1F**)malloc(sizeof(TH1F*)*6);


for(int ifile=0;ifile<6;ifile++){
    weights[ifile]=new TH1F(Form("weight_%i",ifile),"",species_plots::obs_bins,species_plots::obs_min,species_plots::obs_max);
    for(int ibin=1;ibin<=species_plots::obs_bins;ibin++){
//	double buff;
//        if(ibin<=30){buff=(wt[2*ibin-2][ifile+1]+wt[2*ibin-1][ifile+1])/2.0;}
//        else{buff=wt[59][ifile+1];}


	double value=Interpolate(60,wt[0],wt[ifile+1],weights[ifile]->GetBinCenter(ibin));

	weights[ifile]->SetBinContent(ibin,value);
	weights[ifile]->SetBinError(ibin,0);
    }   
}
//Need to update this function for better interpolation

cout<<"Weight read into histograms."<<endl;
return weights;

}


TH2F** augment(TH1F** wt1d){
TH2F** augmented=(TH2F**)malloc(sizeof(TH2F*)*6);
for(int ifile=0;ifile<6;ifile++){
    augmented[ifile]=new TH2F(Form("augmented_weight_%i",ifile),"",species_plots::obs_bins,species_plots::obs_min,species_plots::obs_max,species_plots::obs_bins,species_plots::obs_min,species_plots::obs_max);
    for(int ibin=1;ibin<=species_plots::obs_bins;ibin++){
    	for(int jbin=1;jbin<species_plots::obs_bins;jbin++){
	    double entry=wt1d[ifile]->GetBinContent(ibin);
	    augmented[ifile]->SetBinContent(ibin,jbin,entry);
	    augmented[ifile]->SetBinError(ibin,jbin,0);
	}
    }
}

return augmented;
}



void blending(
		const char* weightname="species_weight.txt",
		const string input_key="out-data/hadd_random_trk",
		const string suffix="pt_mixed"
){

//double wt[151][6];
TH1F** wt=read_weight(weightname);



TH2F** wt_2d=augment(wt);
//for(int i=0;i<60;i++){ printf("%f\t%f\t%f\t%f\t%f\t%f\t%f\n",wt[i][0],wt[i][1],wt[i][2],wt[i][3],wt[i][4],wt[i][5],wt[i][6]); }



TCanvas* c1=new TCanvas();
c1->Divide(3,2);
for(int i=0;i<6;i++){
    c1->cd(i+1);
    wt[i]->Draw();
}


std::vector<string> keyword_str={"proton","antiproton","kplus","kminus","piplus","piminus"};
const int nspecies=keyword_str.size();
species_plots* species[nspecies];
for(int i=0;i<nspecies;i++){

    const char* keyword=keyword_str[i].c_str();
    string filename(Form("%s_%s.root",input_key.c_str(),keyword));
    if(suffix!="")filename=Form("%s_%s_%s.root",input_key.c_str(),keyword,suffix.c_str());
   
    if(keyword_str[i]=="piminus_2")
     	species[i]=new species_plots(filename,"piminus_pt_mixed");
    else species[i]=new species_plots(filename,Form("%s_%s",keyword,suffix.c_str()));
    cout<<keyword_str[i]<<endl;

    species[i]->normalize();  
   
}
//species_plots::pt_bins=150;
//species_plots::pt_max=30;
species_plots blended(true,"blended");

for(int i=0;i<species_plots::lumi_bins;i++){
    for(int j=0;j<species_plots::ea_bins;j++){
	for(int k=0;k<species_plots::vz_bins;k++){
	    for(int ifile=0;ifile<nspecies;ifile++){
		species[ifile]->gen_mc_pt[i][j][k]->Multiply(wt[ifile]);;
	    	species[ifile]->match_mc_pt[i][j][k]->Multiply(wt[ifile]);
	    	species[ifile]->reco_pt[i][j][k]->Multiply(wt[ifile]);
		species[ifile]->mc_reco_pt[i][j][k]->Multiply(wt_2d[ifile]);
	    }



/*	    for(int ibin=1;ibin<=species_plots::pt_bins;ibin++){
		double all_mc=0,all_match=0,all_reco=0;
		for(int ifile=0;ifile<nspecies;ifile++){
		if(ibin<=150){    
		    all_mc+=species[ifile]->gen_mc_pt[i][j][k]->GetBinContent(ibin)*wt[ibin][ifile];
		    all_match+=species[ifile]->gen_mc_pt[i][j][k]->GetBinContent(ibin)*wt[ibin][ifile];
		    all_reco+=species[ifile]->reco_pt[i][j][k]->GetBinContent(ibin)*wt[ibin][ifile];
		}}
		blended.gen_mc_pt[i][j][k]->SetBinContent(ibin,all_mc);
		blended.match_mc_pt[i][j][k]->SetBinContent(ibin,all_match);
		blended.reco_pt[i][j][k]->SetBinContent(ibin,all_reco);
      		blended.pt_efficiency[i][j][k]->SetBinContent(ibin,all_reco/all_mc);
		
		for(int jbin=1;jbin<=species_plots::pt_bins;jbin++){
		    double all_resp=0;
		    
		    for(int ifile=0;ifile<nspecies;ifile++){
			all_resp+=species[ifile]->mc_reco_pt[i][j][k]->GetBinContent(ibin,jbin)*wt[ibin][ifile];
		    }
		    blended.mc_reco_pt[i][j][k]->SetBinContent(ibin,jbin,all_resp);
		}
		
	    }
*/

	}
    }
}


for(int ifile=0;ifile<nspecies;ifile++) blended.add(*species[ifile]);



TFile* output = new TFile("isobar_trk_eff_ptmix_blend.root","recreate");

blended.write(output);




output->Close();
return;

} 
