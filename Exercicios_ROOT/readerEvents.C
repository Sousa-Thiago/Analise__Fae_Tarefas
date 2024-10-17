#define readerEvents_cxx
#include "readerEvents.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void readerEvents::Loop()
{
//   In a ROOT session, you can do:
//      root> .L readerEvents.C
//      root> readerEvents t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch

    
   if (fChain == 0) return;
    TH1F *histo1 = new TH1F("histo1", "Histograma numero de Eletrons", 11, 0, 10);
    TH1F *histo2 = new TH1F("histo2", "Histograma numero de Muons", 11, 0, 10);

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
       // cout << "test" << endl;

       histo1->Fill(nElectron);
       histo2->Fill(nMuon);
}
    
TCanvas *canvas1 = new TCanvas("canvas1", "Histograma numero de Eletrons", 800, 600);
    histo1->Draw(); 
    canvas1->Print("histograma_muon.pdf");

    TCanvas *canvas2 = new TCanvas("canvas2", "Histograma numero de Muons", 800, 600);
    histo2->Draw();
    canvas2->Print("histograma_eletron.pdf");

}







    

