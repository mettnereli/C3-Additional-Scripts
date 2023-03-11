void pDistributionLayer1() {
TH1D *p_all, *p_electrons, *p_positrons, *p_photons;
p_all = new TH1D("p_all", "p_all",100,0, 5);
p_electrons = new TH1D("p_electrons","p_electrons",100,0,20);
p_positrons = new TH1D("p_positrons","p_positrons",100,0,20);
p_photons = new TH1D("p_photons","p_photons",100,0,5);
TH1D *pT_all, *pT_electrons, *pT_positrons, *pT_photons;
pT_all = new TH1D("pT_all", "pT_all",100,0, 5);
pT_electrons = new TH1D("pT_electrons","pT_electrons",100,0,20);
pT_positrons = new TH1D("pT_positrons","pT_positrons",100,0,20);
pT_photons = new TH1D("pT_photons","pT_photons",100,0,5);

TH1D *p_5pT_all, *p_5pT_electrons, *p_5pT_positrons, *p_5pT_photons;
p_5pT_all = new TH1D("p_5pT_all", "p_5pT_all",100,0, 5);
p_5pT_electrons = new TH1D("p_5pT_electrons","p_5pT_electrons",100,0,20);
p_5pT_positrons = new TH1D("p_5pT_positrons","p_5pT_positrons",100,0,20);
p_5pT_photons = new TH1D("p_5pT_photons","p_5pT_photons",100,0,5);
TH1D *pT_5pT_all, *pT_5pT_electrons, *pT_5pT_positrons, *pT_5pT_photons;
pT_5pT_all = new TH1D("pT_5pT_all", "pT_5pT_all",100,0, 5);
pT_5pT_electrons = new TH1D("pT_5pT_electrons","pT_5pT_electrons",100,0,20);
pT_5pT_positrons = new TH1D("pT_5pT_positrons","pT_5pT_positrons",100,0,20);
pT_5pT_photons = new TH1D("pT_5pT_photons","pT_5pT_photons",100,0,5);

double x_position,y_position,z_position,r_position;
const int nfiles=400;
double seed[nfiles]={100346, 101206, 104117, 111882, 113580, 113647, 114217, 115843, 116030, 121992, 125137, 126525, 126654, 130912, 133872, 135158, 135789, 137488, 140135, 144037, 144155, 144302, 144552, 145413, 148259, 149277, 149643, 149888, 150213, 153794, 156003, 157321, 158533, 158673, 160373, 162398, 164369, 168257, 169687, 175987, 176603, 179816, 180324, 183760, 185869, 197114, 198121, 199375, 201899, 208721, 210933, 212218, 217752, 218366, 223727, 224378, 224735, 224799, 229526, 230499, 230898, 231172, 240742, 242249, 245440, 246593, 250028, 250281, 253317, 254202, 259765, 261450, 265607, 266327, 269406, 269629, 270295, 272116, 275693, 278439, 280300, 283680, 289173, 290325, 291129, 303206, 304756, 305455, 306581, 308864, 312437, 312743, 313450, 313775, 316999, 326842, 329462, 333011, 333207, 334814, 340141, 340903, 340979, 341131, 344795, 344836, 346700, 349677, 350059, 350513, 352229, 358094, 360024, 362072, 364319, 368131, 370348, 371525, 371724, 377461, 379139, 382393, 383541, 386671, 391951, 397883, 398287, 398627, 398785, 401669, 401888, 402247, 402898, 404073, 409817, 410108, 411382, 411916, 411951, 413536, 414907, 415183, 415417, 420287, 422747, 437276, 437492, 438259, 442462, 442842, 443140, 443581, 452804, 458536, 461722, 462812, 465632, 465937, 467250, 467990, 468503, 480905, 482488, 483011, 485000, 485790, 488550, 488898, 489787, 489905, 490112, 491385, 493983, 496015, 498545, 499676, 502949, 506250, 506582, 506740, 508152, 513275, 522514, 522710, 524393, 528430, 529985, 530031, 533245, 542793, 543061, 544726, 545883, 554322, 556858, 560258, 564789, 566723, 566766, 568434, 570008, 570311, 570435, 571918, 573299, 573962, 574060, 574327, 576837, 582112, 591187, 595300, 598145, 600828, 602879, 608407, 611621, 612177, 612840, 613291, 613785, 620350, 621182, 624252, 624408, 626301, 631821, 634538, 635405, 636424, 638357, 638550, 646693, 648278, 652834, 653649, 653861, 654932, 656835, 660365, 663306, 665865, 669279, 675393, 677977, 678612, 685378, 689616, 692112, 694604, 694737, 697237, 697536, 698492, 699846, 704142, 704642, 706148, 708660, 714906, 715396, 717376, 724626, 725399, 726339, 730025, 732114, 735402, 736775, 741089, 747947, 752650, 759921, 759943, 761639, 761936, 762234, 762746, 765421, 766398, 766941, 768299, 776477, 779523, 780305, 784969, 787827, 787995, 789897, 790126, 794098, 795566, 795993, 797236, 805299, 805788, 810118, 812721, 812815, 815879, 817388, 825349, 831928, 835048, 837035, 842565, 844541, 845213, 850748, 852406, 852503, 852911, 853734, 854498, 857442, 860164, 861251, 862122, 866527, 867508, 870350, 873699, 875155, 878544, 879969, 882058, 882165, 886529, 890252, 891450, 893755, 895469, 896638, 898238, 900843, 903199, 904574, 906069, 908201, 908381, 908955, 910419, 912174, 912195, 912979, 913009, 914988, 917739, 918025, 918613, 921156, 921746, 925454, 926051, 930269, 932576, 934051, 934307, 938011, 938269, 939579, 940132, 940575, 940772, 945637, 948066, 949377, 951022, 955409, 959743, 960114, 960379, 961102, 961837, 962714, 963677, 964622, 965032, 966021, 966840, 968834, 970098, 970787, 970903, 973046, 974695, 975198, 976811, 977555, 980417, 981026, 983637, 987142, 991025, 991902, 992757, 994692, 996481, 997676, 997973};
for(int ifile=0;ifile<nfiles;ifile++)
{
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
TTreeFormula pdgID("pdgID","SiVertexBarrelHits.truth.pdgID",tree);
TTreeFormula Mag2("Mag2", "SiVertexBarrelHits.momentum.Mag2()",tree);
TTreeFormula Rho("Rho", "SiVertexBarrelHits.momentum.Rho()",tree);
 for(int i=0; i<nentries; i++)
 {
    //tree -> GetEntry(i);
     tree->LoadTree(i);
	
	 const auto size = X_position.GetNdata();
	 Y_position.GetNdata();
	 Z_position.GetNdata();
	 R_position.GetNdata();
	 pdgID.GetNdata();
	 Mag2.GetNdata();
	 Rho.GetNdata();
	 cout << " size = " << size << endl;
	
	 for(int j=0;j<size;j++)
	 {
         auto x = X_position.EvalInstance(j);
	 auto y = Y_position.EvalInstance(j);
	 auto z = Z_position.EvalInstance(j);
	 auto pdg = pdgID.EvalInstance(j);
	 auto p = Mag2.EvalInstance(j);
	 auto pT = Rho.EvalInstance(j);
	 auto r = R_position.EvalInstance(j);
	if (r>=13 && r<=17) {
	 if (pdg==11) { p_electrons->Fill(p); pT_electrons->Fill(pT); }
	 if (pdg==-11) { p_positrons->Fill(p); pT_positrons->Fill(pT); }
	 if (pdg==22) { p_photons->Fill(p); pT_photons->Fill(pT); }
	 p_all->Fill(p);
	 pT_all->Fill(pT);
	}
	 }	
	
	
	
  }}
 
for(int ifile=0;ifile<nfiles;ifile++)
{
cout << "====================================================================== Seed:" << seed[ifile] << " ======================================================================" << endl;
std::ostringstream oss;
oss << "/eos/user/e/emettner/C3/geant4/output/pTTests/5pT/C3Sid_" << seed[ifile] << "_5pT.root" ;
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
TTreeFormula pdgID("pdgID","SiVertexBarrelHits.truth.pdgID",tree);
TTreeFormula Mag2("Mag2", "SiVertexBarrelHits.momentum.Mag2()",tree);
TTreeFormula Rho("Rho", "SiVertexBarrelHits.momentum.Rho()",tree);
 for(int i=0; i<nentries; i++)
 {
	tree->LoadTree(i);
         const auto size = X_position.GetNdata();
         Y_position.GetNdata();
         Z_position.GetNdata();
         R_position.GetNdata();
	 pdgID.GetNdata();
         Mag2.GetNdata();
         Rho.GetNdata();
         cout << " size = " << size << endl;

	for(int j=0;j<size;j++)
         {
         auto x = X_position.EvalInstance(j);
         auto y = Y_position.EvalInstance(j);
         auto z = Z_position.EvalInstance(j);
         auto pdg = pdgID.EvalInstance(j);
         auto p = Mag2.EvalInstance(j);
         auto pT = Rho.EvalInstance(j);
	 auto r = R_position.EvalInstance(j);        

        if (r>=13 && r<=17) {
         if (pdg==11) { p_5pT_electrons->Fill(p); pT_5pT_electrons->Fill(pT); }
         if (pdg==-11) { p_5pT_positrons->Fill(p); pT_5pT_positrons->Fill(pT); }
         if (pdg==22) { p_5pT_photons->Fill(p); pT_5pT_photons->Fill(pT); }
         p_5pT_all->Fill(p);
         pT_5pT_all->Fill(pT);
        }
		
}
}
}


TCanvas *c1 = new TCanvas("c1","c1");
c1->SetLogy();
c1->Print("p_pT_layer1_all.pdf[");
p_all->Draw();
p_5pT_all->SetLineColor(2);
p_5pT_all->Draw("same");
c1->Print("p_pT_layer1_all.pdf");
c1->Clear();
p_electrons->Draw();
p_5pT_electrons->SetLineColor(2);
p_5pT_electrons->Draw("same");
c1->Print("p_pT_layer1_all.pdf");
c1->Clear();
p_positrons->Draw();
p_5pT_positrons->SetLineColor(2);
p_5pT_positrons->Draw("same");
c1->Print("p_pT_layer1_all.pdf");
c1->Clear();
p_photons->Draw();
p_5pT_photons->SetLineColor(2);
p_5pT_photons->Draw("same");
c1->Print("p_pT_layer1_all.pdf");
c1->Clear();
pT_all->Draw();
pT_5pT_all->SetLineColor(2);
pT_5pT_all->Draw("same");
c1->Print("p_pT_layer1_all.pdf");
c1->Clear();
pT_electrons->Draw();
pT_5pT_electrons->SetLineColor(2);
pT_5pT_electrons->Draw("same");
c1->Print("p_pT_layer1_all.pdf");
c1->Clear();
pT_positrons->Draw();
pT_5pT_positrons->SetLineColor(2);
pT_5pT_positrons->Draw("same");
c1->Print("p_pT_layer1_all.pdf");
c1->Clear();
pT_photons->Draw();
pT_5pT_photons->SetLineColor(2);
pT_5pT_photons->Draw("same");
c1->Print("p_pT_layer1_all.pdf");
c1->Clear();
c1->Print("p_pT_layer1_all.pdf]");
}