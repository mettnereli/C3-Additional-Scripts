#Program to find parent particles of a geant4 C3 Simulation Elias Mettner, Lindsey Gray 
import uproot
import awkward
import numpy as np
import os
import math
import hist

#Recursive parent function
def get_root_parent(index, mcparticles, recurses):
         parents = mcparticles[index]["parents"].tolist()
         if len(parents) == 0:
                  return index, recurses
         elif len(parents) == 1:
                  recurses = recurses + 1
                  return get_root_parent(parents.pop(), mcparticles, recurses)
         else:
                  raise Error("this cannot/should not happen")

def get_first_parent(index, mcparticles):
         parents = mcparticles[index]["parents"].tolist()
         if len(parents) == 0:
                  return index
         elif len(parents) == 1:
                  return parents.pop()
         else:
                  raise Error("this cannot/should not happen")

if __name__ == '__main__':
         #h1 = hist.Hist(hist.axis.Regular(bins=50, start=0, stop=45000, name="parent"))
         #h2 = hist.Hist(hist.axis.Regular(bins=50, start=-70, stop=70, name="z"),
         #               hist.axis.Regular(bins=50, start=0, stop=70, name="r"),
         #               )

	 #pe parent momenta histograms
         #h3 = hist.Hist(hist.axis.Regular(bins=20, start=0, stop=0.5, name="pe"))
         #h4 = hist.Hist(hist.axis.Regular(bins=20, start=0, stop=0.5, name="peX"))
         #h5 = hist.Hist(hist.axis.Regular(bins=20, start=0, stop=0.5, name="peY"))
         #h6 = hist.Hist(hist.axis.Regular(bins=20, start=-100, stop=100, name="peZ"))
         
	 #ps parent momenta histograms
         """
         h7 = hist.Hist(hist.axis.Regular(bins=40, start=-1000, stop=1000, name="psParent"))
         h8 = hist.Hist(hist.axis.Regular(bins=40, start=-1000, stop=1000, name="psXParent"))
         h9 = hist.Hist(hist.axis.Regular(bins=40, start=-1000, stop=1000, name="psYParent"))
         h10 = hist.Hist(hist.axis.Regular(bins=80, start=-25000, stop=25000, name="psZParent"))
         h11 = hist.Hist(hist.axis.Regular(bins=40, start=-1000, stop=1000, name="psHit"))
         h12 = hist.Hist(hist.axis.Regular(bins=40, start=-1000, stop=1000, name="psXHit"))
         h13 = hist.Hist(hist.axis.Regular(bins=40, start=-1000, stop=1000, name="psYHit"))
         h14 = hist.Hist(hist.axis.Regular(bins=80, start=-25000, stop=25000, name="psZHit"))
         """
         h15 = hist.Hist(hist.axis.Regular(bins=10, start=0, stop=10, name="recurses"))
         h16 = hist.Hist(hist.axis.Regular(bins=40, start=-500, stop=500, name="psXFirst"))
         h17 = hist.Hist(hist.axis.Regular(bins=40, start=-500, stop=500, name="psYFirst"))
         h18 = hist.Hist(hist.axis.Regular(bins=80, start=-25000, stop=25000, name="psZFirst"))
         h19 = hist.Hist(hist.axis.Regular(bins=40, start=-500, stop=500, name="psTFirst"))
         h20 = hist.Hist(hist.axis.Regular(bins=40, start=-500, stop=500, name="psXNoParent"))
         h21 = hist.Hist(hist.axis.Regular(bins=40, start=-500, stop=500, name="psYNoParent"))
         h22 = hist.Hist(hist.axis.Regular(bins=80, start=-25000, stop=25000, name="psZNoParent"))
         h23 = hist.Hist(hist.axis.Regular(bins=40, start=-500, stop=500, name="psTNoParent"))
	 #Open file/arrays
         x = awkward.from_parquet("C3Sid_extracted.parquet")
         mcParticles = x["MCParticles"]
         siVertexBarrelHits = x["SiVertexBarrelHits"]

	 #iterate over each file
         for i in range(len(x)):
          print("Reading file " + str(i) + " . . . ")

          #for index in range(len(mcParticles[i])):
                  #parent = get_root_parent(index, mcParticles[i])
                  #h1.fill(parent=parent)

	  #iterate over siVertexBarrelHits
          for index in range(len(siVertexBarrelHits[i])):

                  x = siVertexBarrelHits[i][index]["position"]["fCoordinates"]["fX"]
                  y = siVertexBarrelHits[i][index]["position"]["fCoordinates"]["fY"]
                  z = siVertexBarrelHits[i][index]["position"]["fCoordinates"]["fZ"]
                  #h2.fill(z=z, r=math.sqrt(x*x+y*y))
		
		  #Points at 0 position
                  if x == 0 and y == 0 and z == 0:
                   track = siVertexBarrelHits[i][index]["truth"]["trackID"]
                   calls = 0
                   parent, recurses = get_root_parent(track, mcParticles[i], calls)
                   firstParent = get_first_parent(track, mcParticles[i])

                   """
                   #Get peX and psX of parents
                   peX = mcParticles[i][parent]["pex"]
                   peY = mcParticles[i][parent]["pey"]
                   peZ = mcParticles[i][parent]["pez"]
                   psX = mcParticles[i][parent]["psx"]
                   psY = mcParticles[i][parent]["psy"]
                   psZ = mcParticles[i][parent]["psz"]
                   pe = math.sqrt(peX*peX+peY*peY)
                   ps = math.sqrt(psX*psX+psY*psY)
		   
                   #Get p of hits
                   psXHit = mcParticles[i][track]["psx"]
                   psYHit = mcParticles[i][track]["psy"]
                   psZHit = mcParticles[i][track]["psz"]
                   psHit = math.sqrt(psXHit**2 + psYHit**2)
                   """
                   #Get p of first parent + total recurses
                   psXFirst = mcParticles[i][firstParent]["psx"]
                   psYFirst = mcParticles[i][firstParent]["psy"]
                   psZFirst = mcParticles[i][firstParent]["psz"]
                   psTFirst = math.sqrt(psXFirst**2 + psYFirst**2)
                   
                   if firstParent != track:
                    h16.fill(psXFirst=psXFirst)
                    h17.fill(psYFirst=psYFirst)
                    h18.fill(psZFirst=psZFirst)
                    h19.fill(psTFirst=psTFirst)

                   if firstParent == track:
                    h20.fill(psXNoParent=psXFirst)
                    h21.fill(psYNoParent=psYFirst)
                    h22.fill(psZNoParent=psZFirst)
                    h23.fill(psTNoParent=psTFirst)
                   h15.fill(recurses=recurses)
                   """
                   #Fill
                   h3.fill(pe=pe)
                   h4.fill(peX=peX)
                   h5.fill(peY=peY)
                   h6.fill(peZ=peZ)
                   h7.fill(psParent=ps)
                   h8.fill(psXParent=psX)
                   h9.fill(psYParent=psY)
                   h10.fill(psZParent=psZ)
                   h11.fill(psHit=psHit)
                   h12.fill(psXHit=psXHit)
                   h13.fill(psYHit=psYHit)
                   h14.fill(psZHit=psZHit)
                   """

         print("Writing to file . . . ")
         f = uproot.recreate("firstParentHists.root")
         """
         f["h1"] = h1
         f["h2"] = h2
         f["h3"] = h3
         f["h4"] = h4
         f["h5"] = h5
         f["h6"] = h6
         f["h7"] = h7
         f["h8"] = h8
         f["h9"] = h9
         f["h10"] = h10
         f["h11"] = h11
         f["h12"] = h12
         f["h13"] = h13
         f["h14"] = h14
         """
         f["h15"] = h15
         f["h16"] = h16
         f["h17"] = h17
         f["h18"] = h18
         f["h19"] = h19
         f["h20"] = h20
         f["h21"] = h21
         f["h22"] = h22
         f["h23"] = h23
