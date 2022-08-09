import argparse

parser = argparse.ArgumentParser(description='A program to place a specific cut on GPig Output pairs.dat files. format: ./run_cut.py cut file_input file_output')
parser.add_argument("cut", help="The cut on the data in GeV (float), removes all events <= the cut. THIS CUT IS IN GEV, NOT MEV, USE DECIMALS FOR MEV", type=float)
parser.add_argument("file_input", help="The input GPig file (pairs.dat)")
parser.add_argument("file_output", help="The output GPig file (other pairs.dat)")

args = parser.parse_args()

cut = args.cut
fileName = args.file_input
newFile = args.file_output

totalLines = 0
afterLines = 0
f = open(fileName, 'r')
nF = open(newFile, 'w')
for line in f.readlines():
    totalLines += 1
    vars = line.split(' ')
    if (abs(float(vars[0])) <= cut): continue;
    afterLines += 1
    nF.write(line)
f.close()
nF.close()

print("Total Events: " + str(totalLines) + "\nAfter Cut: " + str(afterLines))
