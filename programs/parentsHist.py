#Correct method to access parentage info using awkward array, parquet file
import uproot
import awkward
import numpy as np
import os
import math
import hist

def get_root_parent(index, mcparticles):
         parents = mcparticles[index]["parents"].tolist()
         if len(parents) == 0:
                  return index
         elif len(parents) == 1:
                  return get_root_parent(parents.pop(), mcparticles)
         else:
                  raise Error("this cannot/should not happen")

if __name__ == '__main__':
         h1 = hist.Hist(hist.axis.Regular(bins=200, start=0, stop=45000, name="parent"))
         h2 = hist.Hist(hist.axis.Regular(bins=100, start=-70, stop=70, name="z"),
                        hist.axis.Regular(bins=100, start=0, stop=70, name="r"),
                        )
         h3 = hist.Hist(hist.axis.Regular(bins=50, start=0, stop=5, name="p"))
         x = awkward.from_parquet("C3Sid_extracted.parquet")
         mcParticles = x["MCParticles"]
         siVertexBarrelHits = x["SiVertexBarrelHits"]
         for i in range(len(x)):
          print("Reading file " + str(i) + " . . . ")
          for index in range(len(mcParticles[i])):
                  parent = get_root_parent(index, mcParticles[i])
                  h1.fill(parent=parent)
          for index in range(len(siVertexBarrelHits[i])):
                  x = siVertexBarrelHits[i][index]["position"]["fCoordinates"]["fX"]
                  y = siVertexBarrelHits[i][index]["position"]["fCoordinates"]["fY"]
                  z = siVertexBarrelHits[i][index]["position"]["fCoordinates"]["fZ"]
                  h2.fill(z=z, r=math.sqrt(x*x+y*y))
                  if x == 0 and y == 0 and z == 0:
                   track = siVertexBarrelHits[i][index]["truth"]["trackID"]
                   parent = get_root_parent(track, mcParticles[i])
                   pX = mcParticles[i][parent]["pex"]
                   pY = mcParticles[i][parent]["pey"]
                   pZ = mcParticles[i][parent]["pez"]
                   p = math.sqrt(pX*pX+pY*pY+pZ*pZ)
                   h3.fill(p=p)
         print("Writing to file . . . ")
         f = uproot.recreate("parentPHists.root")
         f["h1"] = h1
         f["h2"] = h2
         f["h3"] = h3
