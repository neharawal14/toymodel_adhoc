 #include "TRandom.h"
#include "TAxis.h"
// for 1000 pts 
   void tmp_hist(){

   gROOT->SetBatch(kTRUE);
   Double_t sigma_st = .0001;
   Double_t sigma1 = .01; 
   Double_t a;
   TRandom3 *random_number = new TRandom3();


// defining pT values

   //Double_t par[7] = {.00114,.00057,.000285,.0001425,.000114,.000076,.000057};
      Double_t par = .000114;
  // Double_t pT[7] = {5,10,20,40,50,75,100};
   Double_t pT = 50;

   TGraph *gr1, *gr2, *gr_corrected, *gr_corrected_a;
   TGraph *sigma_a, *sigma_a_fit;
   TGraphErrors *gain_plot, *gain_plot_a;
   //TCanvas *pT_plots, *pT_plots_fit;
   Int_t number_loop;

// "/home/neha/Documents/work/adhoc_toy_model_study_latest/plots_test/scattered_plot/pt_50.pdf"
// To save pdf for scattered plots
   
   Double_t slope_fit,intercept_fit;

   /* Double_t pt_range[7] = {.007,.013,.028,0.065,0.065,.08,.12};
    Double_t number[7] = {100,100,100,100,100,100,100};
    Double_t pt_range_before_below[7] = {.01,.025,.038,0.08,0.095,.15,.18};
    Double_t pt_range_before_above[7] = {.01,.025,.038,0.08,0.09,.15,.18};*/

 
   Double_t slope_fit_a,intercept_fit_a;
   TCanvas *parabolic_graphs;
   TGraph *gr;

  
   a = par;
   TH2F *hist_plot = new TH2F("hist_plot", "2-D Hist ",100, -.02, .02, 100, -.15, .15);

   Double_t slopevalue[5000], slopeerr[5000], interceptvalue[5000],intercepterr[5000],d0value[5000], d0err[5000],diff_slope[5000];
   Double_t pT_graph[5000],pT_slope[5000],pT_corrected[5000],new_dpT[5000],new_da[5000];
   number_loop =0;
// for tossing toys for a single pT
   for(Int_t k =0; k<5000;k++){
   
 
    Double_t y[14];// = {4.4,7.3,10.2,23,32,40,50,60,70,80,90,100,110};
    Double_t x[14] = {2.9,6.8,10.9,16.0,25.5,33.9,41.9,49.8,60.8,69.2,78.0,86.8,96.5,108.0};
    for (Int_t i=0;i<14;i++) {
 // getting random points      
     y[i] = a*x[i]*x[i] + random_number->Gaus(0,sigma1);
    }

   
// fitting random points in a graph and obtaining fit parameters
   parabolic_graphs = new TCanvas("parabolic_graphs","fit"); //,200,10,700,500);
   parabolic_graphs->cd();
 
   gr = new TGraph(14,x,y);
  // TGraph *gr = new TGraph(n,x,y);
   gr->SetLineColor(2);
   gr->SetLineWidth(4);
   gr->SetMarkerColor(4);
   gr->SetMarkerStyle(21);
   gr->SetTitle("parabolic_fit");
   gr->GetXaxis()->SetTitle("x");
   gr->GetYaxis()->SetTitle("y");
   gr->Draw("AP*");

    TF1 *line0 = new TF1("line0","[2]*x*x+[1]*x+[0]",0,150);
    line0->SetParameter(2,a);
    line0->SetParameter(1,0.0);
    line0->SetParameter(0,0.0);
    gr->Fit("line0");
    gr->Paint("|>");

    //TString parabola_name = plots_parabola[k];

    gStyle->SetOptFit();
   // parabolic_graphs[k]->SaveAs(parabola_name);

    slopevalue[k] = line0->GetParameter(2);
    slopeerr[k] = line0->GetParError(2);
    interceptvalue[k] = line0->GetParameter(1);
    intercepterr[k] = line0->GetParError(1);
    d0value[k] = line0->GetParameter(0);
    d0err[k] = line0->GetParError(0);
    diff_slope[k] = (slopevalue[k] - a)/a;
  
    pT_graph[k] = (0.0057/slopevalue[k]);
    pT_slope[k] = -((pT_graph[k] - pT)/pT);
    number_loop++;

    hist_plot->Fill(d0value[k],pT_slope[k]);
   }
   cout<<"number times loop  "<<number_loop<<endl;
   cout<<"pT  "<<"a  "<<"a from graph   "<<" pt from graph "<<"#Delta a/a   "<<"#Delta pT/pT  "<<" loop number  "<<endl; 
   Int_t i;
  // for(i = 0;i<5000;i++){
  //  cout<<pT[pt_loop]<<"  "<<par[pt_loop]<<"  "<<slopevalue[i]<<"  "<<pT_graph[i]<<"  "<<diff_slope[i]<<"  "<<pT_slope[i]<<"  "<<pt_loop<<endl;
  // }
   
   
// scattered plots gr1 and gr2 
   gr1= new TGraph(5000,d0value,diff_slope);
   gr2= new TGraph(5000,d0value,pT_slope);


  

   TCanvas *pT_plots = new TCanvas("pT_plots","scattered plot pt",1000,1000);

   pT_plots->cd();
   gr2->SetMarkerColor(kBlue);
   gr2->SetMarkerSize(.2);
   gr2->SetMarkerStyle(20);
   gr2->SetLineColor(kBlue);
  // gr2[0]->SetName("g1");
   gr2->GetXaxis()->SetRangeUser(-.02, .02);
   gr2->GetYaxis()->SetRangeUser(-.15, .15);

   gr2->GetXaxis()->SetTitle("d0 (cm)");
   gr2->GetYaxis()->SetTitle(" #frac{#Delta p_{T}}{p_{T}}");
   //gr->GetYaxis()->SetRangeUser(0,.3);
   gr2->SetTitle(" #frac{#Delta p_{T}}{p_{T}} vs d0");
   gr2->Draw("AP");
   pT_plots->SaveAs("pt_tmp_50.pdf");
 
  TCanvas *pT_plots_fit  = new TCanvas("pT_plots_fit","scattered plot pt",1000,1000);

  pT_plots_fit->cd();

 
 TF1 *line_fit= new TF1("line_fit","[1]*x+[0]",-10,10);
  line_fit->SetParameter(0,0);
  line_fit->SetParameter(1,1.0);
  line_fit->SetParName(0,"intercept");  
  line_fit->SetParName(1,"slope");  
  gr2->Fit("line_fit");
  gr2->Draw("AP");
  pT_plots_fit->SaveAs("pt_tmp_50_fit.pdf");

 TCanvas *a_plots = new TCanvas("a_plots","scattered plot a",1000,1000);

   a_plots->cd();
   gr1->SetMarkerColor(kBlue);
   gr1->SetMarkerSize(.2);
   gr1->SetMarkerStyle(20);
   gr1->SetLineColor(kBlue);
  // gr2[0]->SetName("g1");
   gr1->GetXaxis()->SetRangeUser(-.02, .02);
   gr1->GetYaxis()->SetRangeUser(-.15, .15);

   gr1->GetXaxis()->SetTitle("d0 (cm)");
   gr1->GetYaxis()->SetTitle(" #frac{#Delta p_{T}}{p_{T}}");
   //gr->GetYaxis()->SetRangeUser(0,.3);
   gr1->SetTitle(" #frac{#Delta p_{T}}{p_{T}} vs d0");
   gr1->Draw("AP");
   a_plots->SaveAs("pt_tmp_50.pdf");
 
  TCanvas *a_plots_fit  = new TCanvas("a_plots_fit","scattered plot a",1000,1000);

  a_plots_fit->cd();

 
  TF1 *line_fit_a= new TF1("line_fit_a","[1]*x+[0]",-10,10);
  line_fit_a->SetParameter(0,0);
  line_fit_a->SetParameter(1,1.0);
  line_fit_a->SetParName(0,"intercept");  
  line_fit_a->SetParName(1,"slope");  
  gr1->Fit("line_fit_a");
  gr1->Draw("AP");
  a_plots_fit->SaveAs("a_tmp_50_fit.pdf");

 TCanvas *hist = new TCanvas("hist","scattered plot 2d hist",900,900);
   hist->cd();
 /*TF1 * hist_fit = new TF1("hist_fit","[1]*x+[0]",-10,10);
  hist_fit->SetParameter(0,0);
  hist_fit->SetParameter(1,1.0);
  hist_fit->SetParName(0,"intercept");  
  hist_fit->SetParName(1,"slope"); */
  hist_plot->GetXaxis()->SetRangeUser(-.02, .02);
  hist_plot->GetYaxis()->SetRangeUser(-.15, .15);

  hist_plot->GetXaxis()->SetTitle("d0 (cm)");
  hist_plot->GetYaxis()->SetTitle(" #frac{#Delta p_{T}}{p_{T}}");

  hist_plot->Draw("COL");
  //h_2d->Fit("hist_fit");
  
   hist->SaveAs("hist_tmp.pdf");
}

 
 

  