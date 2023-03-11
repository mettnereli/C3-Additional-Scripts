import awkward
import uproot
import glob
from rich.progress import track
import multiprocessing
import concurrent.futures
import pathlib

def extract_file(c3FileName, keep):
    c3File = uproot.open(c3FileName)
    
    tree = c3File["EVENT"]

    json_branches = {}

    for branchName in tree.keys():
        if branchName not in keep:
            continue
        branch = tree[branchName]

        dataProduct = branch.arrays(library="np")[branchName][0]
        out = []
        for thing in dataProduct:
            out.append(thing.tojson())

        json_branches[branchName] = out


    c3OutName = c3FileName.split(".root")[0]
    c3OutName = f"{c3OutName}_extracted.parquet"
    awkward.to_parquet(awkward.Array([json_branches]), c3OutName)
    return c3OutName


if __name__ == '__main__':

    nWorkers = multiprocessing.cpu_count()
    files = glob.glob("./C3Si*.root")
    keep = ["MCParticles", "SiVertexBarrelHits"]
    
    outNames = []
    with concurrent.futures.ProcessPoolExecutor(max_workers=nWorkers) as executor:
        outNameFtrs = [executor.submit(extract_file, fname, keep) for fname in files]
        for outNameFtr in track(concurrent.futures.as_completed(outNameFtrs), description="Extracting GEANT info...", total=len(outNameFtrs)):
            outNames.append(outNameFtr.result())

    out_array = None
    for outName in track(outNames, "concatenating..."):
        temp = awkward.from_parquet(outName)
        if out_array is None:
            out_array = temp
        else:
            out_array = awkward.concatenate([out_array, temp])
        pathlib.Path(outName).unlink()

    awkward.to_parquet(out_array, "C3Sid_extracted.parquet")
