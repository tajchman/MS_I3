#! /usr/bin/env python3

import subprocess, os, argparse, glob, sys

versions = [
    "exemple_seq",
    "exemple_par"
]

parser = argparse.ArgumentParser()
parser.add_argument('-n', type=int, default=2000)
parser.add_argument('-t', '--threads', type=int, default=5)
args = parser.parse_args()

err = 0
for v in versions:
    print("\n___________________________") 
    print(v, '\n') 

    cmd = [os.path.join("install", v),
            "-n", str(args.n)]
    if not v == "exemple_seq":
       cmd += [ "--threads", str(args.threads)]
    
    print(' '.join(cmd))
    subprocess.call(cmd)
