#include <TFile.h>
#include <TTree.h>
#include <TH1F.h>
#include <TCanvas.h>

void maketree() {
    // Abrir o arquivo ROOT
    TFile *file = TFile::Open("051E9D22-4F30-8E49-8477-644E65768282.root");
    
    // Acessar a árvore
    TTree *tree = (TTree*)file->Get("nome_da_ntupla");
    
    // Criar histogramas
    TH1F *histo1 = new TH1F("histo1", "Distribuicao de variavel1", 100, 0, 100);
    TH1F *histo2 = new TH1F("histo2", "Distribuicao de variavel2", 100, 0, 100);
    TH1F *histo3 = new TH1F("histo3", "Distribuicao de variavel3", 100, 0, 100);

    // Preencher os histogramas
    tree->Draw("variavel1 >> histo1");
    tree->Draw("variavel2 >> histo2");
    tree->Draw("variavel3 >> histo3");

    // Desenhar os histogramas
    TCanvas *c1 = new TCanvas("c1", "Histogramas", 800, 600);
    c1->Divide(2, 2);
    c1->cd(1); histo1->Draw();
    c1->cd(2); histo2->Draw();
    c1->cd(3); histo3->Draw();
}
