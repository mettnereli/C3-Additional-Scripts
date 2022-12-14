

void getID() {
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
const int nfiles=400;
int totalSize = 0;
double seed[nfiles]={100346, 101206, 104117, 111882, 113580, 113647, 114217, 115843, 116030, 121992, 125137, 126525, 126654, 130912, 133872, 135158, 135789, 137488, 140135, 144037, 144155, 144302, 144552, 145413, 148259, 149277, 149643, 149888, 150213, 153794, 156003, 157321, 158533, 158673, 160373, 162398, 164369, 168257, 169687, 175987, 176603, 179816, 180324, 183760, 185869, 197114, 198121, 199375, 201899, 208721, 210933, 212218, 217752, 218366, 223727, 224378, 224735, 224799, 229526, 230499, 230898, 231172, 240742, 242249, 245440, 246593, 250028, 250281, 253317, 254202, 259765, 261450, 265607, 266327, 269406, 269629, 270295, 272116, 275693, 278439, 280300, 283680, 289173, 290325, 291129, 303206, 304756, 305455, 306581, 308864, 312437, 312743, 313450, 313775, 316999, 326842, 329462, 333011, 333207, 334814, 340141, 340903, 340979, 341131, 344795, 344836, 346700, 349677, 350059, 350513, 352229, 358094, 360024, 362072, 364319, 368131, 370348, 371525, 371724, 377461, 379139, 382393, 383541, 386671, 391951, 397883, 398287, 398627, 398785, 401669, 401888, 402247, 402898, 404073, 409817, 410108, 411382, 411916, 411951, 413536, 414907, 415183, 415417, 420287, 422747, 437276, 437492, 438259, 442462, 442842, 443140, 443581, 452804, 458536, 461722, 462812, 465632, 465937, 467250, 467990, 468503, 480905, 482488, 483011, 485000, 485790, 488550, 488898, 489787, 489905, 490112, 491385, 493983, 496015, 498545, 499676, 502949, 506250, 506582, 506740, 508152, 513275, 522514, 522710, 524393, 528430, 529985, 530031, 533245, 542793, 543061, 544726, 545883, 554322, 556858, 560258, 564789, 566723, 566766, 568434, 570008, 570311, 570435, 571918, 573299, 573962, 574060, 574327, 576837, 582112, 591187, 595300, 598145, 600828, 602879, 608407, 611621, 612177, 612840, 613291, 613785, 620350, 621182, 624252, 624408, 626301, 631821, 634538, 635405, 636424, 638357, 638550, 646693, 648278, 652834, 653649, 653861, 654932, 656835, 660365, 663306, 665865, 669279, 675393, 677977, 678612, 685378, 689616, 692112, 694604, 694737, 697237, 697536, 698492, 699846, 704142, 704642, 706148, 708660, 714906, 715396, 717376, 724626, 725399, 726339, 730025, 732114, 735402, 736775, 741089, 747947, 752650, 759921, 759943, 761639, 761936, 762234, 762746, 765421, 766398, 766941, 768299, 776477, 779523, 780305, 784969, 787827, 787995, 789897, 790126, 794098, 795566, 795993, 797236, 805299, 805788, 810118, 812721, 812815, 815879, 817388, 825349, 831928, 835048, 837035, 842565, 844541, 845213, 850748, 852406, 852503, 852911, 853734, 854498, 857442, 860164, 861251, 862122, 866527, 867508, 870350, 873699, 875155, 878544, 879969, 882058, 882165, 886529, 890252, 891450, 893755, 895469, 896638, 898238, 900843, 903199, 904574, 906069, 908201, 908381, 908955, 910419, 912174, 912195, 912979, 913009, 914988, 917739, 918025, 918613, 921156, 921746, 925454, 926051, 930269, 932576, 934051, 934307, 938011, 938269, 939579, 940132, 940575, 940772, 945637, 948066, 949377, 951022, 955409, 959743, 960114, 960379, 961102, 961837, 962714, 963677, 964622, 965032, 966021, 966840, 968834, 970098, 970787, 970903, 973046, 974695, 975198, 976811, 977555, 980417, 981026, 983637, 987142, 991025, 991902, 992757, 994692, 996481, 997676, 997973};
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
	
	 cout << " size = " << size << endl;
	
	 for(int j=0;j<size;j++)
	 {
     auto x = X_position.EvalInstance(j);
     auto y = Y_position.EvalInstance(j);
     auto z = Z_position.EvalInstance(j);
     auto r = R_position.EvalInstance(j);
     auto ID = cellID.EvalInstance(j);
     auto pdg = pdgID.EvalInstance(j);	
	
	
	 //cout << " x = " << x << " y = " << y <<  " r = " << r <<  "   " << sqrt(x*x+y*y) << " z = " << z << " cell ID " << ID << endl;
	
	
	 if (r>=13 && r<=17)   N1++;
	 if (r>=21 && r<=25)   N2++;
	 if (r>=34 && r<=38)   N3++;
	 if (r>=46.6 && r<=50.6) N4++;
	 if (r>=59 && r<=63) N5++;
	
	 if (pdg==11) { electron_hits_r_vs_z->Fill(z, sqrt(x*x+y*y)); }
	 if (pdg==-11) { positron_hits_r_vs_z ->Fill(z, sqrt(x*x+y*y)); }
         if (pdg==22) { photon_hits_r_vs_z ->Fill(z, sqrt(x*x+y*y)); }
	
	 
	 h_hits_X -> Fill(x);
     h_hits_Y -> Fill(y);
     h_hits_Z -> Fill(z);
     h_hits_r -> Fill(sqrt(x*x+y*y));
     h_hits_r_vs_z -> Fill(z,sqrt(x*x+y*y));
	 	
		
		
	 }
	
	
	
  }
 }
TCanvas *c1 = new TCanvas ("c1", "c1");
c1->cd();
h_hits_r_vs_z->Draw("colz");
TCanvas *c2 = new TCanvas ("c2", "c2");
c2->cd();
electron_hits_r_vs_z->Draw("colz");
TCanvas *c3 = new TCanvas ("c3", "c3");
c3->cd();
positron_hits_r_vs_z->Draw("colz");
TCanvas *c4 = new TCanvas ("c4", "c4");
c4->cd();
photon_hits_r_vs_z->Draw("colz");
}
