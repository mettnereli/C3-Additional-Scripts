#Program to find parent particles of a geant4 C3 Simulation Elias Mettner, Lindsey Gray 
import ROOT
import uproot
import awkward
import numpy as np
import os
import math
import hist

#Recursive parent function
def get_root_parent(index, mcparticles):
         parents = mcparticles[index]["parents"].tolist()
         if len(parents) == 0:
                  return index
         elif len(parents) == 1:
                  return get_root_parent(parents.pop(), mcparticles)
         else:
                  raise Error("this cannot/should not happen")

if __name__ == '__main__':
         #h1 = hist.Hist(hist.axis.Regular(bins=50, start=0, stop=45000, name="parent"))
         h2 = hist.Hist(hist.axis.Regular(bins=50, start=-70, stop=70, name="z"),
                        hist.axis.Regular(bins=50, start=0, stop=70, name="r"),
                        )
         newh2 = ROOT.TH2D("h2", "r_vs_z", 50, -70, 70, 50, 0, 70);
	 #pe parent momenta histograms
         #h3 = hist.Hist(hist.axis.Regular(bins=20, start=0, stop=0.5, name="pe"))
         #h4 = hist.Hist(hist.axis.Regular(bins=20, start=0, stop=0.5, name="peX"))
         #h5 = hist.Hist(hist.axis.Regular(bins=20, start=0, stop=0.5, name="peY"))
         #h6 = hist.Hist(hist.axis.Regular(bins=20, start=-100, stop=100, name="peZ"))
         
	 #ps parent momenta histograms
         #h7 = hist.Hist(hist.axis.Regular(bins=40, start=-1000, stop=1000, name="psTParent"))
         #h8 = hist.Hist(hist.axis.Regular(bins=40, start=-1000, stop=1000, name="psXParent"))
         #h9 = hist.Hist(hist.axis.Regular(bins=40, start=-1000, stop=1000, name="psYParent"))
         #h10 = hist.Hist(hist.axis.Regular(bins=80, start=-25000, stop=25000, name="psZParent"))
         h11 = hist.Hist(hist.axis.Regular(bins=40, start=-1000, stop=1000, name="psTHit"))
         h12 = hist.Hist(hist.axis.Regular(bins=40, start=-1000, stop=1000, name="psXHit"))
         h13 = hist.Hist(hist.axis.Regular(bins=40, start=-1000, stop=1000, name="psYHit"))
         h14 = hist.Hist(hist.axis.Regular(bins=80, start=-25000, stop=25000, name="psZHit"))

	 #Open file/arrays
         x = awkward.from_parquet("C3Sid_extracted.parquet")
         mcParticles = x["MCParticles"]
         siVertexBarrelHits = x["SiVertexBarrelHits"]

	 #iterate over each file
         for i in range(len(x)):
          print("Reading file " + str(i) + " . . . ")
          newh2.Draw("colz same")
	  #iterate over siVertexBarrelHits
          for index in range(len(siVertexBarrelHits[i])):

                  x = siVertexBarrelHits[i][index]["position"]["fCoordinates"]["fX"]
                  y = siVertexBarrelHits[i][index]["position"]["fCoordinates"]["fY"]
                  z = siVertexBarrelHits[i][index]["position"]["fCoordinates"]["fZ"]
                  r = math.sqrt(x**2 + y**2)
		  #Points away from 0 position
                  if x == 0 and y == 0 and z == 0:
                   track = siVertexBarrelHits[i][index]["truth"]["trackID"]
                   parent = get_root_parent(track, mcParticles[i])
		   #Get peX and psX of parents
                   #peX = mcParticles[i][parent]["pex"]
                   #peY = mcParticles[i][parent]["pey"]
                   #peZ = mcParticles[i][parent]["pez"]
                   #psX = mcParticles[i][parent]["psx"]
                   #psY = mcParticles[i][parent]["psy"]
                   #psZ = mcParticles[i][parent]["psz"]
                   #peT = math.sqrt(peX*peX+peY*peY)
                   #psT = math.sqrt(psX*psX+psY*psY)
                   newh2.Fill(z, r)
                   #Get p of hits
                   psXHit = mcParticles[i][track]["psx"]
                   psYHit = mcParticles[i][track]["psy"]
                   psZHit = mcParticles[i][track]["psz"]
                   psTHit = math.sqrt(psXHit**2 + psYHit**2)
                   if psTHit > 50 or psTHit < 50:
                    xpolar = 70*(math.cos(psTHit/psZHit))
                    ypolar = 70*(math.sin(psTHit/psZHit))
                    L = ROOT.TLine(0.,0.,xpolar,ypolar)
                    L.SetLineColor(5)
                    L.Draw()
                   #Fill
                   h2.fill(z=z, r=(math.sqrt(x**2 + y**2)))
                   #h3.fill(pe=pe)
                   #h4.fill(peX=peX)
                   #h5.fill(peY=peY)
                   #h6.fill(peZ=peZ)
                   #h7.fill(psTParent=psT)
                   #h8.fill(psXParent=psX)
                   #h9.fill(psYParent=psY)
                   #h10.fill(psZParent=psZ)
                   h11.fill(psTHit=psTHit)
                   h12.fill(psXHit=psXHit)
                   h13.fill(psYHit=psYHit)
                   h14.fill(psZHit=psZHit)


         print("Writing to file . . . ")
         c1.Print("hist_r_vs_z.png")
         #f = uproot.recreate("nonParent_angle1.root")
         #f["h2"] = newh2
         #f["h3"] = h3
         #f["h4"] = h4
         #f["h5"] = h5
         #f["h6"] = h6
         #f["h7"] = h7
         #f["h8"] = h8
         #f["h9"] = h9
         #f["h10"] = h10
         #f["h11"] = h11
         #f["h12"] = h12
         #f["h13"] = h13
         #f["h14"] = h14
