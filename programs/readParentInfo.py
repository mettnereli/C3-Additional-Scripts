import ROOT
import uproot
import awkward
import numpy as np
import os
import math

def get_root_parent(index, mcparticles):
	 parents = mcparticles.member("parents")
	 if len(parents) == 0:
   	  return index
	 elif len(parents) == 1:
	  return get_root_parent(parents, mcparticles)
	 else:
	  raise Error("this cannot/should not happen")    

if __name__ == '__main__':
 
 h1 = ROOT.TH1D("parents","Parent Hits", 150, 0, 45000)
 h2 = ROOT.TH2D("r_vs_z", "r_vs_z hits", 100, -70, 70, 100, 0, 70)
 x = uproot.open("/eos/uscms/store/user/emettner/C3/geant4/output/BX/C3Sid_100805.root")
 y = x["EVENT"]["MCParticles"].array(library="np")
 siVertexBarrelHits = x["EVENT"]["SiVertexBarrelHits"].array(library="np")
 
 for index, part in enumerate(y[0]):
  parent = get_root_parent(index, part)
  h1.Fill(parent)
 

 for i in siVertexBarrelHits[0]:
  x = i.member("position").member("fCoordinates").member("fX")
  y = i.member("position").member("fCoordinates").member("fY")	
  z = i.member("position").member("fCoordinates").member("fZ")
  h2.Fill(z, math.sqrt(x*x+y*y))

 outFile = ROOT.TFile.Open("parentHist.root", "RECREATE")
 outFile.cd()
 h1.Write()
 h2.SetOption("colz")
 h2.Write()
 outFile.Close()
