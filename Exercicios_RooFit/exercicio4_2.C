#include <RooRealVar.h>
#include <RooExponential.h>
#include <RooDataSet.h>
#include <RooPlot.h>
#include <TCanvas.h>
#include <TStyle.h>

void exercicio4_2() {
    // Definir variável x em um intervalo de 0 a 10
    RooRealVar x("x", "x", 0, 10);
    
    // Definir o parâmetro lambda com valor inicial de 1
    RooRealVar lambda("lambda", "Decay constant", -1, -2, -0.1);
    
    // Definir a função exponencial
    RooExponential expo("expo", "Exponential PDF", x, lambda);
    
    // Gerar 1500 eventos simulados a partir da distribuição exponencial
    RooDataSet* data = expo.generate(x, 1500);

    // Ajusta lambda e o número de eventos
    RooFitResult* fitResult = expo.fitTo(*data, RooFit::Save(), RooFit::Extended());

    // Criar um frame para plotar a variável x
    RooPlot* xframe = x.frame();
    
    // Plotar os dados e a função ajustada
    data->plotOn(xframe);
    expo.plotOn(xframe);
    expo.paramOn(xframe, RooFit::Layout(0.1, 0.95, 0.9));
    
    TCanvas* c1 = new TCanvas("c1", "Ajuste Exponencial", 800, 600);
    xframe->Draw();
    gStyle->SetOptStat(222112211);
    double chi2 = xframe->chiSquare();   
    TLegend *leg = new TLegend(0.1, 0.3, 0.9, 0.9);
    leg->SetTextSize(0.05);
    leg->SetBorderSize(0);
    leg->SetFillStyle(0);
    leg->AddEntry((TObject*)0, Form("#chi^{2}/ndf = %.2f", chi2), "");
    leg->Draw();

    c1->SaveAs("exercicio4_2.pdf");
    

    fitResult->Print("v");

    // Mostrar os valores ajustados de lambda e do número total de eventos
    std::cout << "Lambda ajustado: " << lambda.getVal() << std::endl;
    // std::cout << "Número total de eventos ajustados: " << fitResult->Ndf() << std::endl;
}
