void printHadronFiles() {
TFile *f1 = new TFile("/eos/uscms/store/user/emettner/C3/geant4/output/HepMC/start2GeV/process1/gamma-gamma_geant.root");
TFile *f2 = new TFile("/eos/uscms/store/user/emettner/C3/geant4/output/HepMC/start2GeV/process2/gamma-gamma_geant.root");
TFile *f3 = new TFile("/eos/uscms/store/user/emettner/C3/geant4/output/HepMC/start2GeV/process3/gamma-gamma_geant.root");
TFile *f4 = new TFile("/eos/uscms/store/user/emettner/C3/geant4/output/HepMC/start2GeV/process4/gamma-gamma_geant.root");

const char* plots[9] = {"occupancy", "r_vs_z", "p", "pT", "pdgID_1", "pdgID_2", "pdgID_3", "pdgID_4", "eta"};

TH2D * rvzNo01 = (TH2D*)f1->Get("occupancy");
TH2D * rvzNo02 = (TH2D*)f2->Get("occupancy");
TH2D * rvzNo03 = (TH2D*)f3->Get("occupancy");
TH2D * rvzNo04 = (TH2D*)f4->Get("occupancy");
rvzNo01->SetTitle("R_vs_Z Process 1");
rvzNo02->SetTitle("R_vs_Z Process 2");
rvzNo03->SetTitle("R_vs_Z Process 3");
rvzNo04->SetTitle("R_vs_Z Process 4");

TH2D * rvz1 = (TH2D*)f1->Get("r_vs_z");
TH2D * rvz2 = (TH2D*)f2->Get("r_vs_z");
TH2D * rvz3 = (TH2D*)f3->Get("r_vs_z");
TH2D * rvz4 = (TH2D*)f4->Get("r_vs_z");
rvz1->SetTitle("R_vs_z Process 1");
rvz2->SetTitle("R_vs_z Process 2");
rvz3->SetTitle("R_vs_z Process 3");
rvz4->SetTitle("R_vs_z Process 4");

TH1D * p1 = (TH1D*)f1->Get("p");
TH1D * p2 = (TH1D*)f2->Get("p");
TH1D * p3 = (TH1D*)f3->Get("p");
TH1D * p4 = (TH1D*)f4->Get("p");
p1->SetTitle("p Process 1");
p2->SetTitle("p Process 2");
p3->SetTitle("p Process 3");
p4->SetTitle("p Process 4");

TH1D * pT1 = (TH1D*)f1->Get("pT");
TH1D * pT2 = (TH1D*)f2->Get("pT");
TH1D * pT3 = (TH1D*)f3->Get("pT");
TH1D * pT4 = (TH1D*)f4->Get("pT");
pT1->SetTitle("pT Process 1");
pT2->SetTitle("pT Process 2");
pT3->SetTitle("pT Process 3");
pT4->SetTitle("pT Process 4");

TH1D * pdgID1 = (TH1D*)f1->Get("pdgID_1");
TH1D * pdgID2 = (TH1D*)f2->Get("pdgID_1");
TH1D * pdgID3 = (TH1D*)f3->Get("pdgID_1");
TH1D * pdgID4 = (TH1D*)f4->Get("pdgID_1");
pdgID1->SetTitle("pdgID Process 1");
pdgID2->SetTitle("pdgID Process 2");
pdgID3->SetTitle("pdgID Process 3");
pdgID4->SetTitle("pdgID Process 4");

TH1D * eta1 = (TH1D*)f1->Get("eta");
TH1D * eta2 = (TH1D*)f2->Get("eta");
TH1D * eta3 = (TH1D*)f3->Get("eta");
TH1D * eta4 = (TH1D*)f4->Get("eta");
eta1->SetTitle("eta Process 1");
eta2->SetTitle("eta Process 2");
eta3->SetTitle("eta Process 3");
eta4->SetTitle("eta Process 4");



auto c  = new TCanvas("c","", 1500, 1500);
c->Divide(2,2);
c->Print("my_output.pdf[");

c->cd(1);
rvzNo01->Draw("colz");
c->cd(2);
rvzNo02->Draw("colz");
c->cd(3);
rvzNo03->Draw("colz");
c->cd(4);
rvzNo04->Draw("colz");

c->Print("my_output.pdf");
c->Clear();
c->Divide(2,2);

c->cd(1);
rvz1->Draw("colz");
c->cd(2);
rvz2->Draw("colz");
c->cd(3);
rvz3->Draw("colz");
c->cd(4);
rvz4->Draw("colz");

c->Print("my_output.pdf");
c->Clear();

gStyle->SetOptStat(111111);

c->Divide(2,2);
c->cd(1);
p1->Draw();
c->cd(2);
p2->Draw();
c->cd(3);
p3->Draw();
c->cd(4);
p4->Draw();

c->Print("my_output.pdf");
c->Clear();

c->Divide(2,2);
c->cd(1);
pT1->Draw();
c->cd(2);
pT2->Draw();
c->cd(3);
pT3->Draw();
c->cd(4);
pT4->Draw();
c->SetLogy();
c->Print("my_output.pdf");
c->Clear();
c->Divide(2,2);

c->cd(1);
pdgID1->Draw();
c->cd(2);
pdgID2->Draw();
c->cd(3);
pdgID3->Draw();
c->cd(4);
pdgID4->Draw();

c->Print("my_output.pdf");
c->Clear();
c->Divide(2,2);

c->cd(1);
eta1->Draw();
c->cd(2);
eta2->Draw();
c->cd(3);
eta3->Draw();
c->cd(4);
eta4->Draw();

c->Print("my_output.pdf");
c->Print("my_output.pdf]");
c->Close();
}
