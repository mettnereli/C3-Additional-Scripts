//Draws lines from the origin to roughly estimat pT of each particle at 0. Not needed anymore

void pTTester() {
TH1D *h_hits_X, *h_hits_Y,*h_hits_Z, *h_hits_r;
TH2D *h_hits_r_vs_z, *electron_hits_r_vs_z, *positron_hits_r_vs_z, *photon_hits_r_vs_z;
h_hits_X = new TH1D("h_hits_X","h_hits_X",40,-70,70);
h_hits_Y = new TH1D("h_hits_Y","h_hits_Y",40,-70,70);
h_hits_Z = new TH1D("h_hits_Z","h_hits_Z",40,-70,70);
h_hits_r = new TH1D("h_hits_r","h_hits_r",20,0,70);
h_hits_r_vs_z = new TH2D("h_hits_r_vs_z","h_hits_r_vs_z",40,-70,70,20,0,70);
electron_hits_r_vs_z = new TH2D("electron_hits_r_vs_z","electron_hits_r_vs_z",40,-70,70,20,0,70);
positron_hits_r_vs_z = new TH2D("positron_hits_r_vs_z","positron_hits_r_vs_z",40,-70,70,20,0,70);
photon_hits_r_vs_z = new TH2D("photon_hits_r_vs_z","photon_hits_r_vs_z",40,-70,70,20,0,70);
double x_position,y_position,z_position,r_position;
const int nfiles=2;
int totalSize = 0;
for(int ifile=0;ifile<nfiles;ifile++)
{
int N1=0,N2=0,N3=0,N4=0,N5=0;
	
cout << "====================================================================== Seed:" << seed[ifile] << " ======================================================================" << endl;
std::ostringstream oss;
oss << "/eos/user/e/emettner/C3/geant4/output/cutTests/0/C3Sid_" << seed[ifile] << "_0.root" ;
std::string file_name = oss.str();
cout << file_name << endl;
char char_array[200];
strcpy(char_array, file_name.c_str());
TFile *f1 = new TFile(char_array);
TTree *tree=(TTree*)(f1->Get("EVENT"));
Int_t nentries =(Int_t)(tree-> GetEntries());
cout << "nentries = " << nentries << endl;
TTreeFormula X_position("X_position","SiVertexBarrelHits.position.X()",tree);
TTreeFormula Y_position("Y_position","SiVertexBarrelHits.position.Y()",tree);
TTreeFormula Z_position("Z_position","SiVertexBarrelHits.position.Z()",tree);
TTreeFormula R_position("R_position","SiVertexBarrelHits.position.Rho()",tree);
TTreeFormula cellID("cellID","SiVertexBarrelHits.cellID",tree);
TTreeFormula pdgID("pdgID","SiVertexBarrelHits.truth.pdgID",tree);
TTreeFormula Rho("Rho","SiVertexBarrelHits.momentum.Rho()",tree);
TTreeFormula Z_momentum("Z_momentum","SiVertexBarrelHits.momentum.Z()",tree);
gStyle->SetOptStat(0);
h_hits_r_vs_z->Draw("colz same");
 for(int i=0; i<nentries; i++)
 {
    //tree -> GetEntry(i);
     tree->LoadTree(i);
	
	 const auto size = X_position.GetNdata();
	 totalSize = totalSize + size;
	 Y_position.GetNdata();
	 Z_position.GetNdata();
	 R_position.GetNdata();
	 cellID.GetNdata();
	 pdgID.GetNdata();
	 Rho.GetNdata();
	 Z_momentum.GetNdata();
	
	 for(int j=0;j<size;j++)
	 {
     auto x = X_position.EvalInstance(j);
     auto y = Y_position.EvalInstance(j);
     auto z = Z_position.EvalInstance(j);
     auto r = R_position.EvalInstance(j);
     auto ID = cellID.EvalInstance(j);
     auto pdg = pdgID.EvalInstance(j);	
     auto pT = Rho.EvalInstance(j);
     auto pZ = Z_momentum.EvalInstance(j);
     auto angle = pT/pZ;
     auto X = 70*cos(angle);
     auto Y = 70*sin(angle);

	if (x!=0 && y!=0 && z!=0) {
	h_hits_r_vs_z->Fill(z, sqrt(x*x+y*y));
	} 
	if (x==0 && y==0 && z==0) {
        cout << pT << " " << pZ << " " << angle << endl;
	TLine *L = new TLine(0.,0.,X,Y);
	L->SetLineColor(5);
	L->Draw();
	}
		
		
	 }
	
	
	
  }
 }
}
