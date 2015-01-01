import argparse
import os.path
import fileinput

parser = argparse.ArgumentParser()
parser.add_argument("name",     type=str,     help="Name of the .beatj beat score")
parser.add_argument("length",   type=int,     help="Length (in seconds) of music file")
parser.add_argument("bpm",      type=int,     help="BPM of the music file, please try to be as accurate as possible with this")

args = parser.parse_args()

# creates a file named args.name + ".beatj" based on command line arguments
def gen_beatscore():
    # set up some easier to read variables
    length = args.length
    bpm = args.bpm
    name = args.name

    # create the file
    nfile = open('beatscore/'+name+".beatj",'a')

    # start writing stuff to file
    nfile.write("// AUTOMATICALLY GENERATED BEATSCORE\n")
    nfile.write("// PLEASE FILL IN ALL APPROPRIATE VALUES OR RISK UNDEFINED BEHAVIOR\n")
    nfile.write("// DOUBLE FORWARD SLASHES ARE COMMENTS, HASHTAGS ARE GAME ARGUMENTS, CHANGE ONLY WHEN APPROPRIATE\n")
    nfile.write("// NOTE: COMMENTS MUST BE THE ENTIRE LINE, IE. NOT LIKE THIS: #BEGIN // BLAH\n")
    nfile.write("// NOTE: GAME ARGUMENTS CANNOT HAVE ANY SPACES, IE. NOT LIKE THIS: #SONG = BLAH\n")
    nfile.write("// NOTE: SUBBEAT DESIGNATIONS CANNOT HAVE ANY SPACES, IE. NOT LIKE THIS: 1 -> C\n")
    nfile.write("// NOTE: MOUSE BEATS CAN BE DESIGNATED BY ADDING A \'m\' BEFORE THE NOTE\n\n")
    nfile.write("#SONG=\n")
    nfile.write("#LENGTH="+str(length)+"\n")
    nfile.write("#BPM="+str(bpm)+"\n\n")
    nfile.write("// begin score section\n")
    nfile.write("#BEGIN\n")

    numbeats = int(float(length) / 60 * bpm) + 1    # floor numbeats
    for i in range(1,numbeats+1):
        nfile.write("BEAT-"+str(i)+"\n")
        for j in range(1,4+1):
            nfile.write("   "+str(j)+"->\n")
    nfile.write("#END\n")

def main():
    # check if specified file name already exists
    if os.path.isfile("beatscore/"+args.name+".beatj"):
        print "Error - beat score file \'" + args.name + ".beatj\' already exists"
        return
    else:
        gen_beatscore()

main()
