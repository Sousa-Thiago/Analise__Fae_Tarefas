#include <RooRealVar.h>
#include <RooCBShape.h>
#include <RooDataSet.h>
#include <RooPlot.h>
#include <TCanvas.h>
#include <TStyle.h>
#include "TH1F.h"

void exercicio4_1() {
    // Definir a variável independente (x)
    RooRealVar x("x", "x", -10, 10);

    // Parâmetros da Crystal Ball
    RooRealVar mean("mean", "Mean", 0, -10, 10);
    RooRealVar sigma("sigma", "Sigma", 1, 0.1, 5);
    RooRealVar alpha("alpha", "Alpha", 1.5, 0.1, 5);
    RooRealVar n("n", "n", 2, 0.1, 10);

    // Criando função Crystal Ball
    RooCBShape crystalBall("crystalBall", "Crystal Ball PDF", x, mean, sigma, alpha, n);

    // Gerar uma amostra de 10.000 dados
    RooDataSet* data = crystalBall.generate(x, 10000);

    // Ajustar a PDF aos dados
    crystalBall.fitTo(*data);

    // Criar um frame para plotar a variável x
    RooPlot* xframe = x.frame();
    
    // Adicionar os dados e a função ajustada no gráfico
    data->plotOn(xframe);
    crystalBall.plotOn(xframe);
    crystalBall.paramOn(xframe, RooFit::Layout(0.1, 0.95, 0.9));

    TCanvas* c1 = new TCanvas("c1", "Ajuste Crystal Ball", 800, 600);
    xframe->Draw();

    // Caixa de informações estatísticas
    gStyle->SetOptStat(222112211);
    // gStyle->SetOptFit(1111);
    c1->SaveAs("crystalBall_roofit.pdf");
    
}
