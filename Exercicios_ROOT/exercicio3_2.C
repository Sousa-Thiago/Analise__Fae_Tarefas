#include <TGraph.h>
#include <TGraphErrors.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <iostream>

void plotGraphs() {
    // Canvas
    TCanvas *canvas = new TCanvas("canvas", "Graph with Errors", 800, 600);

    // TGraph para os dados
    TGraph *graph = new TGraph("graphdata.txt");
    if (!graph) {
        std::cerr << "Erro ao carregar graphdata.txt" << std::endl;
        return;
    }

    // TGraphErrors para as barras de erros
    TGraphErrors *graphErrors = new TGraphErrors("graphdata_error.txt");
    if (!graphErrors) {
        std::cerr << "Erro ao carregar graphdata_error.txt" << std::endl;
        return;
    }

    // Configurações do plot
    graph->SetMarkerStyle(22); // Estilo do marcador de caixa preta
    graph->SetMarkerColor(kBlack);
    graph->SetTitle("Grafico com Erros;eixo-X;eixo-Y");
    graph->Draw("ALP"); // Desenha os pontos do TGraph com linhas

    // Desenha o gráfico com erro
    graphErrors->SetMarkerStyle(21); // Estilo do marcador de círculo
    graphErrors->SetMarkerColor(kRed);
    graphErrors->Draw("P"); // Desenha os pontos do TGraphErrors

    // Salva o gráfico em PDF
    canvas->Print("exercício_2.pdf");

    // Limpa a memória
    delete canvas;
    delete graph;
    delete graphErrors;
}

void exercicio3_2() {
    plotGraphs();
}