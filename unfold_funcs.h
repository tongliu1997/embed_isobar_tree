
#include "embed_species.h"
double ncoll_bins[16]={385,317,232,232,150,150,94,94,56,56,32,32,17,17,9,9};


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

TH2F* resp_reweight(TH2F* resp_mtx,TH1D* spec){

    TH2F* resp_return=(TH2F*)resp_mtx->Clone();
    TH2D* aug_spec=truth_augment(resp_mtx,spec);
    resp_return->Multiply(aug_spec);
    delete aug_spec;
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
    matched->Divide(reco);
    corrected->Multiply(matched);
    return corrected;
}

