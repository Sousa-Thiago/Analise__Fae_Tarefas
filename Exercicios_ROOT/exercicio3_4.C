void exercicio3_4() {
    // Abrindo o arquivo
    TFile *file = TFile::Open("tree.root");
    TTree *tree = (TTree*)file->Get("tree1");

    // Variáveis
    float ebeam, px, py, pz;
    tree->SetBranchAddress("ebeam", &ebeam);
    tree->SetBranchAddress("px", &px);
    tree->SetBranchAddress("py", &py);
    tree->SetBranchAddress("pz", &pz);

    // Cálcula da média da energia do feixe
    double totalEnergy = 0;
    Long64_t nEntries = tree->GetEntries();

    // Loop do cálculo da média
    for (Long64_t i = 0; i < nEntries; i++) {
        tree->GetEntry(i);
        totalEnergy += ebeam; // Soma a energia do feixe
    }

    // Vereficar se a média é > 0 
    if (nEntries > 0) {
        double meanEnergy = totalEnergy / nEntries; // Média
        double lowerCut = meanEnergy - 0.2;
        double upperCut = meanEnergy + 0.2;

        // Criando os cortes
        TCut cut = Form("ebeam < %f || ebeam > %f", upperCut, lowerCut);

        // Montando o histograma
        TH1F *histogram = new TH1F("h_total_momentum", "Total Momentum Distribution", 200, 130, 160); 

        // Preenchendo o histograma TTree::Draw
        tree->Draw("TMath::Sqrt(px*px + py*py + pz*pz)>>h_total_momentum", cut);

        // Criar um canvas para desenhar o histograma
        TCanvas *c2 = new TCanvas("c2", "Total Momentum Distribution", 800, 600);
        histogram->Draw();

        // Salvar em arquivo PDF
        c2->SaveAs("exercício_4.pdf");
    }
    // Fechar o arquivo
    file->Close(); 
}