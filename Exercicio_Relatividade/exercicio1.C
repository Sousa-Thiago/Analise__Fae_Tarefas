#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <TCanvas.h>
#include <TMath.h>

void exercicio1() {
    // Abrindo o dataset .root
    TFile *file = TFile::Open("MC1.root");
    TTree *tree = (TTree*)file->Get("Events");

    // Variáveis utilizadas no trabalho
    float pt1, pt2, eta1, eta2, phi1, phi2;

    // Ligando as variáveis aos ramos
    tree->SetBranchAddress("Tau_pt", &pt1);
    tree->SetBranchAddress("Muon_pt", &pt2);
    tree->SetBranchAddress("Tau_eta", &eta1);
    tree->SetBranchAddress("Muon_eta", &eta2);
    tree->SetBranchAddress("Tau_phi", &phi1);
    tree->SetBranchAddress("Muon_phi", &phi2);

    
    // Plot dos histogramas
    TH1F *h_pt = new TH1F("Leptons_pt", "pT do Tau e Muon", 50, 0, 100);
    h_pt->GetXaxis()->SetTitle("p_{T} (GeV/c)");
    h_pt->GetYaxis()->SetTitle("Events");
    TH1F *h_eta = new TH1F("Leptons_eta", "#eta do Tau e Muon", 50, -3, 3);
    h_eta->GetXaxis()->SetTitle("#eta");
    h_eta->GetYaxis()->SetTitle("Events");
    TH1F *h_phi = new TH1F("Leptons_phi", "#phi do Tau e Muon", 50, -TMath::Pi(), TMath::Pi());
    h_phi->GetXaxis()->SetTitle("#phi");
    h_phi->GetYaxis()->SetTitle("Events");
    TH1F *h_mass = new TH1F("Leptons_mass", "Massa Invariante dos Leptons", 50, 0, 200);
    // h_mass->GetXaxis()->SetTitle("Mass (GeV/c^{2})");
    // h_mass->GetYaxis()->SetTitle("Events");

    Long64_t nentries = tree->GetEntries();
    for (Long64_t i = 0; i < nentries; i++) {
        tree->GetEntry(i);
        
        h_pt->Fill(pt1);
        h_pt->Fill(pt2);
        h_eta->Fill(eta1);
        h_eta->Fill(eta2);
        h_phi->Fill(phi1);
        h_phi->Fill(phi2);

        // Calculando a massa invariante dos dois leptons
        double M2 = 2 * pt1 * pt2 * 
                    (TMath::CosH(eta1 - eta2) - TMath::Cos(phi1 - phi2));
        double M = TMath::Sqrt(M2);
        h_mass->Fill(M);
    }

    TCanvas *c1 = new TCanvas("c1", "Variaveis e Massa Invariante", 800, 600);
    c1->Divide(2, 2);
    c1->cd(1); h_pt->Draw();
    c1->cd(2); h_eta->Draw();
    c1->cd(3); h_phi->Draw();
    c1->cd(4); h_mass->Draw();
    
    c1->SaveAs("distributions_and_invariant_mass_v2.png");

    // Fechando o arquivo
    file->Close();
}
