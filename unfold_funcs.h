
#include "embed_species.h"
double ncoll_bins[2][16]=
 {{388.45,322.59,257.34,204.98,162.96,128.2,100.69,78.46,59.99,45.45,33.98,24.73,18.06,13.14,9.33,6.66},{385.5,317.43,250.94,197.64,155.94,122.24,94.42,72.08,54.75,41.22,30.70,22.81,16.77,12.01,8.36,5.84}};

double ncoll_err[2][16]=
{{9.7825,4.8359,3.2789,2.3979,1.9251,1.3474,1.1076,0.7347,0.5115,0.3755,0.2409,0.1828,0.1214,0.0899,0.0448,0.0325},{9.6667,4.5151,3.0232,2.2238,1.6972,1.2782,0.9063,0.6411,0.4737,0.3329,0.2128,0.1234,0.116,0.0739,0.048,0.0431}};

double npart_bins[2][16]={{166.76,147.54,125.67,106.66,90.42,76.07,63.89,53.35,43.87,35.79,28.83,22.72,17.83,13.89,10.57,8.05},{165.93,146.51,124.49,105.17,88.91,74.76,62.17,51.18,41.90,34.01,27.29,21.77,17.14,13.16,9.80,7.32}};
double npart_err[2][16]={{0.10541,0.99967,0.91996,0.763,0.54546,0.4547,0.26448,0.22901,0.17927,0.1103,0.09156,0.06682,0.04334,0.03326,0.02328,0.01562},{0.08702,0.98141,0.88844,0.68516,0.50607,0.38555,0.28025,0.22111,0.13392,0.09793,0.07122,0.06506,0.06675,0.04105,0.02941,0.02726}};

TH2D* truth_augment(TH2F* resp_mtx,TH1D* spec){
    int nbins=spec->GetNbinsX();
    double xmin=spec->GetXaxis()->GetBinLowEdge(1);
    double xmax=spec->GetXaxis()->GetBinLowEdge(nbins)+spec->GetXaxis()->GetBinWidth(nbins);
    TH2D* augmented=new TH2D(Form("%s_augmented",spec->GetName()),"",nbins,xmin,xmax,nbins,xmin,xmax);
    for(int i=1;i<=nbins;i++){
	double mtx_entries=resp_mtx->ProjectionY(Form("slice_%i",i),i,i,"")->Integral();
	double value=spec->GetBinContent(i);
	double error=spec->GetBinError(i);
	if(mtx_entries!=0){
	    value/=mtx_entries;
	    error/=mtx_entries;
	}
	for(int j=1;j<=nbins;j++){
	    augmented->SetBinContent(i,j,value);
	    augmented->SetBinError(i,j,error);
	}
    }    
    return augmented;
}

/*TH2F* column_normalize(TH2F* resp_mtx){
    int nbins=resp_mtx->GetNbinsX();
    int xmin=resp_mtx->GetXaxis()->GetBinLowEdge(1);
    int xmax=resp_mtx->GetXaxis()->GetBinLowEdge(nbins)+resp_mtx->GetXaxis()->GetBinWidth(nbins);
    for(int i=1;i<=nbins;i++){
	double entries=resp_mtx->ProjectionY(Form("slice_"))

    }

}
*/


TH2F* outlier_trim(TH2F* resp){
    TH2F* result=(TH2F*)resp->Clone();
    int nbins=result->GetNbinsX();

    TH1F* MC=(TH1F*)resp->ProjectionX();
    for(int i=1;i<=nbins;i++){
	double MC_truth=MC->GetBinContent(i);
	for(int j=1;j<=nbins;j++){
	    if(result->GetXaxis()->GetBinCenter(j)>20 || result->GetYaxis()->GetBinCenter(i)>20){
		result->SetBinContent(j,i,0);
		result->SetBinError(j,i,0);
		continue;
	    }
	    if(result->GetBinContent(j,i)>MC_truth && result->GetBinError(j,i) >0.9*result->GetBinContent(j,i)){
//	    if(result->GetBinContent(j,i)>MC_truth*0.1 && result->GetBinError(j,i) >MC_truth){
//	    if(1){
//	 	cout<<"outlier_trim::"<<j<<"\t"<<i<<"\t"<<result->GetBinContent(j,i)<<"\t"<<result->GetBinError(j,i)<<endl;
		result->SetBinContent(j,i,0);
		result->SetBinError(j,i,0);
	    }
	}
    }
    return result;

}


TH2F* resp_reweight(TH2F* resp_mtx,TH1D* spec,int iter){

    TH2F* resp_aug=(TH2F*)resp_mtx->Clone();
    TH2D* aug_spec=truth_augment(resp_mtx,spec);
    resp_aug->Multiply(aug_spec);
    
    TH2F* resp_return=outlier_trim(resp_aug);
//    TH2F* resp_return=(TH2F*)resp_aug->Clone();

    resp_return->SetName(Form("%s_iter_%i",resp_mtx->GetName(),iter));
    resp_return->SetTitle(Form("%s_iter_%i",resp_mtx->GetTitle(),iter));
    delete aug_spec;
    delete resp_aug;
    return resp_return;
}


TH1D* spec_unfold(TH1D* raw_spec,TH2F* resp_mtx,int iter){
//Unfolding code, actually manipulating the matrix column-by-column to obtain result

    int nbins=raw_spec->GetNbinsX();
    double xmin=raw_spec->GetXaxis()->GetBinLowEdge(1);
    double xmax=raw_spec->GetXaxis()->GetBinLowEdge(nbins)+raw_spec->GetXaxis()->GetBinWidth(nbins);
    TH1D* unfolded=new TH1D(Form("%s_unfolded_%i",raw_spec->GetName(),iter),"Unfolded spec;p_{T};yield",nbins,xmin,xmax);
//    TH1F* reco_weight_ref=(TH1F*)resp_mtx->ProjectionY();    
    for(int i=1;i<=nbins;i++){
	if(raw_spec->GetBinCenter(i)<0.2)continue;
	TH1D* slice=(TH1D*)resp_mtx->ProjectionX(Form("mtx_%i",i),i,i,"");
	double integral=slice->Integral();
	if(integral==0)continue;
	double weight=1.*raw_spec->GetBinContent(i)/slice->Integral();
//	cout<<raw_spec->GetBinCenter(i)<<"\t"<<integral<<"\t"<<raw_spec->GetBinContent(i)<<"\t"<<weight<<endl;
	unfolded->Add(slice,weight);
    }
    return unfolded;
}

TH1D* spec_correct(TH1D* raw_spec,TH2F* resp_mtx,int iter){
//Correcting the spectrum by measured*matched/reco
    TH1D* corrected=(TH1D*)raw_spec->Clone();
    corrected->SetName(Form("%s_corrected_%i",raw_spec->GetName(),iter));
    TH1D* matched=(TH1D*)resp_mtx->ProjectionX();
    TH1D* reco=(TH1D*)resp_mtx->ProjectionY();
//    cout<<"Iteration "<<i<<" Data"<<endl;
//    cout<<



    matched->Divide(reco);
    corrected->Multiply(matched);
    
    return corrected;
}

TH1F* tracking_efficiency(TH2F* resp_mtx,TH1F* matching_eff){
    TH1F* reco=(TH1F*)resp_mtx->ProjectionY();
    TH1F* match=(TH1F*)resp_mtx->ProjectionX();
    reco->SetTitle(Form("%s_efficiency",resp_mtx->GetName()));
//    TH1F* reco_rebin=(TH1F*)reco->Rebin(nbins,Form("%s_efficiency_rebin",resp_mtx->GetName()),xbins);
//    TH1F* match_rebin=(TH1F*)match->Rebin(nbins,Form("%s_match_rebin",resp_mtx->GetName()),xbins);
    TH1F* reco_rebin=(TH1F*)reco->Clone();
    reco_rebin->SetName(Form("%s_eff_clone",resp_mtx->GetName()));
    TH1F* match_rebin=(TH1F*)match->Clone();
    match_rebin->SetName(Form("%s_match_clone",resp_mtx->GetName()));

    reco_rebin->Divide(match_rebin);
    reco_rebin->Multiply(matching_eff);
    delete reco;
    delete match;
    delete match_rebin;
    return reco_rebin; 
}

