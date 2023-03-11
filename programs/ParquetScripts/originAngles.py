import uproot
import awkward
import numpy as np
import matplotlib.pyplot as plt
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

	 #Open file/arrays
         x = awkward.from_parquet("C3Sid_extracted.parquet")
         mcParticles = x["MCParticles"]
         siVertexBarrelHits = x["SiVertexBarrelHits"]

         #set up 2D plot space
         #fig = plt.figure()
         #ax = plt.subplot(111)
         #ax.set_ylim([0,70])
         #ax.set_xlim([-70,70])
         #ax.plot([-60,60],[17,17])
         cellID_h = hist.Hist(hist.axis.Regular(bins=100, start=0, stop=100, name="cellID"))
         e_hist = hist.Hist(hist.axis.Regular(bins=30, start=-1, stop=1, name="energyDeposit"))
	 #iterate over each file
         for i in range(len(x)):
          print("Reading file " + str(i) + " . . . ")

	  #iterate over siVertexBarrelHits
          for index in range(len(siVertexBarrelHits[i])):

                  x = siVertexBarrelHits[i][index]["position"]["fCoordinates"]["fX"]
                  y = siVertexBarrelHits[i][index]["position"]["fCoordinates"]["fY"]
                  z = siVertexBarrelHits[i][index]["position"]["fCoordinates"]["fZ"]

		  #Points at 0 position
                  if x == 0 and y == 0 and z == 0:

                   track = siVertexBarrelHits[i][index]["truth"]["trackID"]
                   #parent = get_root_parent(track, mcParticles[i])
                   cellID = siVertexBarrelHits[i][index]["cellID"]
                   #Get p of hits

                   psXHit = mcParticles[i][track]["psx"]
                   psYHit = mcParticles[i][track]["psy"]
                   psZHit = mcParticles[i][track]["psz"]
                   psTHit = math.sqrt(psXHit**2 + psYHit**2)
                   #pdgID = mcParticles[i][track]["pdgID"]
                   #energyDeposit = siVertexBarrelHits[i][index]["energyDeposit"]
                   #print("Hit: " + str(index) + " " + "EDeposit: " + str(energyDeposit))                   
                   cellID_h.fill(cellID=cellID)          
    
                   #Plot angled lines
                   #if psTHit > 200:
                    #print("pT: " + str(psTHit) + " ID: " + str(pdgID))
                    #xpolar = (math.cos(psTHit/psZHit))
                    #ypolar = (math.sin(psTHit/psZHit))
                    #endy = 70 * ypolar
                    #endx = 70 * xpolar
                    #ax.plot([0,endx], [0, endy])
         #fig.suptitle('r_vs_z position - angle of origin hits > 200 MeV')
         #fig.savefig("originAngledLines.png")
         f = uproot.recreate("cellID_small.root")
         f["cellID_h"] = cellID_h 
