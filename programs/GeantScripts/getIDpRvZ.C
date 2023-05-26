

void getIDpRvZ() {
TH1D *h_p,*h_pT, *h_pdgID_1, *h_pdgID_2,*h_pdgID_3,*h_pdgID_4, *h_eta;
TH1D *h_pdgID_1_w0, *h_pdgID_2_w0, *h_pdgID_3_w0, *h_pdgID_4_w0;
TH2D *h_hits_r_vs_z, *h_hits_no0;
h_p = new TH1D("h_p","h_p",100,0,250);
h_pT = new TH1D("h_pT","h_pT",100,0,250);
h_pdgID_1 = new TH1D("h_pdgID_1","h_pdgID_1",30,0,30);
h_pdgID_2 = new TH1D("h_pdgID_2","h_pdgID_2",100,200,350);
h_pdgID_3 = new TH1D("h_pdgID_3","h_pdgID_3",300,2200, 2250);
h_pdgID_4 = new TH1D("h_pdgID_4","h_pdgID_4",250,3100, 3350);
h_eta = new TH1D("h_eta","h_eta",50,-4,4);

h_hits_r_vs_z = new TH2D("h_hits_r_vs_z","SiD Detector Layers Visualization",100,-90,90,50,0,70);
h_hits_r_vs_z->SetXTitle("z [mm]");
h_hits_r_vs_z->SetYTitle("radius [mm]");
h_hits_no0 = new TH2D("h_hits_r_vs_z","h_hits_r_vs_z",100,-90,90,50,0,70);
h_hits_no0->SetXTitle("z [mm]");
h_hits_no0->SetYTitle("radius [mm]");


double x_position,y_position,z_position,r_position;
const int nfiles=50;
int totalSize = 0;
for(int ifile=1;ifile<=nfiles;ifile++)
{
	
//cout << "====================================================================== Seed:" << seed[ifile] << " ======================================================================" << endl;
std::ostringstream oss;
oss << "/eos/uscms/store/user/emettner/C3/geant4/output/HepMC/start2GeV/process4/C3SiD_Hadron_" << ifile << ".root";
std::string file_name = oss.str();
cout << file_name << endl;
char char_array[200];
strcpy(char_array, file_name.c_str());
TFile *f1 = new TFile(char_array);
TTree *tree=(TTree*)(f1->Get("EVENT"));
Int_t nentries =(Int_t)(tree-> GetEntries());
cout << "nentries = " << nentries << endl;
TTreeFormula pdgID("pdgID","SiVertexBarrelHits.truth.pdgID",tree);
TTreeFormula X_position("X_position","SiVertexBarrelHits.position.X()",tree);
TTreeFormula Y_position("Y_position","SiVertexBarrelHits.position.Y()",tree);
TTreeFormula Z_position("Z_position","SiVertexBarrelHits.position.Z()",tree);
TTreeFormula R_position("R_position","SiVertexBarrelHits.position.R()",tree);
TTreeFormula Rho("pX","SiVertexBarrelHits.momentum.Rho()",tree);
TTreeFormula Mag2("pY","SiVertexBarrelHits.momentum.Mag2()",tree);
TTreeFormula Eta("eta","SiVertexBarrelHits.position.Eta()",tree);
 for(int i=0; i<nentries; i++)
 {
    //tree -> GetEntry(i);
     tree->LoadTree(i);
	
	 const auto size = X_position.GetNdata();
	 totalSize = totalSize + size;
	 pdgID.GetNdata();
         X_position.GetNdata();
         Y_position.GetNdata();
         Z_position.GetNdata();
         R_position.GetNdata();	
         Rho.GetNdata();
         Mag2.GetNdata();
         Eta.GetNdata();
	 cout << " size = " << size << endl;
	
	 for(int j=0;j<size;j++)
	 {
     auto x = X_position.EvalInstance(j);
     auto y = Y_position.EvalInstance(j);
     auto z = Z_position.EvalInstance(j);
     auto r = R_position.EvalInstance(j);
     auto pdg = pdgID.EvalInstance(j);
     auto pdgAbs = abs(pdg);	
     auto p = Mag2.EvalInstance(j);
     auto pT = Rho.EvalInstance(j);
     auto eta = Eta.EvalInstance(j);	
     h_hits_r_vs_z -> Fill(z,sqrt(x*x+y*y));
     h_p -> Fill(p);
     h_pT -> Fill(pT);
    if (x != 0 && y != 0 && z != 0) {
     h_eta -> Fill(eta);	
     h_pdgID_1 -> Fill(pdgAbs);
     h_pdgID_2 -> Fill(pdgAbs);
     h_pdgID_3 -> Fill(pdgAbs);
     h_pdgID_4 -> Fill(pdgAbs);
     h_hits_no0 -> Fill(z, sqrt(x*x+y*y));
		}
	 }
	
	
	
  }
 }
TFile f("/eos/uscms/store/user/emettner/C3/geant4/output/HepMC/start2GeV/process4/gamma-gamma_geant.root", "recreate");
f.WriteObject(h_hits_r_vs_z, "r_vs_z");
f.WriteObject(h_p, "p");
f.WriteObject(h_pT, "pT");

f.WriteObject(h_pdgID_1, "pdgID_1");
f.WriteObject(h_pdgID_2, "pdgID_2");
f.WriteObject(h_pdgID_3, "pdgID_3");
f.WriteObject(h_pdgID_4, "pdgID_4");
/*
f.WriteObject(h_pdgID_1_w0, "pdgID_1");
f.WriteObject(h_pdgID_2_w0, "pdgID_2");
f.WriteObject(h_pdgID_3_w0, "pdgID_3");
f.WriteObject(h_pdgID_4_w0, "pdgID_4");
*/
f.WriteObject(h_eta, "eta");
f.WriteObject(h_hits_no0, "occupancy");
}
