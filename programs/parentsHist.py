#Program to find parent particles of a geant4 C3 Simulation Elias Mettner, Lindsey Gray 
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
         #h2 = hist.Hist(hist.axis.Regular(bins=50, start=-70, stop=70, name="z"),
         #               hist.axis.Regular(bins=50, start=0, stop=70, name="r"),
         #               )

	 #pe momenta histograms
         h3 = hist.Hist(hist.axis.Regular(bins=40, start=0, stop=0.5, name="pe"))
         h4 = hist.Hist(hist.axis.Regular(bins=40, start=0, stop=0.5, name="peX"))
         h5 = hist.Hist(hist.axis.Regular(bins=40, start=0, stop=0.5, name="peY"))
         h6 = hist.Hist(hist.axis.Regular(bins=40, start=0, stop=0.5, name="peZ"))
         
	 #ps momenta histograms
         h7 = hist.Hist(hist.axis.Regular(bins=40, start=0, stop=0.5, name="ps"))
         h8 = hist.Hist(hist.axis.Regular(bins=40, start=0, stop=0.5, name="psX"))
         h9 = hist.Hist(hist.axis.Regular(bins=40, start=0, stop=0.5, name="psY"))
         h10 = hist.Hist(hist.axis.Regular(bins=40, start=0, stop=0.5, name="psZ"))

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
                   parent = get_root_parent(track, mcParticles[i])

		   #Get peX and psX of parents
                   peX = mcParticles[i][parent]["pex"]
                   peY = mcParticles[i][parent]["pey"]
                   peZ = mcParticles[i][parent]["pez"]
                   psX = mcParticles[i][parent]["psx"]
                   psY = mcParticles[i][parent]["psy"]
                   psZ = mcParticles[i][parent]["psz"]
                   pe = math.sqrt(peX*peX+peY*peY+peZ*peZ)
                   ps = math.sqrt(psX*psX+psY*psY+psZ*psZ)

		   #Fill
                   h3.fill(pe=pe)
                   h4.fill(peX=peX)
                   h5.fill(peY=peY)
                   h6.fill(peZ=peZ)
                   h7.fill(ps=ps)
                   h8.fill(psX=psX)
                   h9.fill(psY=psY)
                   h10.fill(psZ=psZ)


         print("Writing to file . . . ")
         f = uproot.recreate("parentPHists.root")
         #f["h1"] = h1
         #f["h2"] = h2
         f["h3"] = h3
         f["h4"] = h4
         f["h5"] = h5
         f["h6"] = h6
         f["h7"] = h7
         f["h8"] = h8
         f["h9"] = h9
         f["h10"] = h10
