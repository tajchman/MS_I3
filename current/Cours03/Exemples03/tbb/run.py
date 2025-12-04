#! /usr/bin/env python3

import subprocess, os, argparse, glob, sys

versions = [
    "exemple_seq",
    "exemple_par"
]

parser = argparse.ArgumentParser()
parser.add_argument('-n', type=int, default=2000)
parser.add_argument('-t', '--threads', type=int, default=5)
parser.add_argument('-g', '--grain', type=int, default=100)
args = parser.parse_args()

baseDir = os.getcwd()
e = os.environ.copy()
TBB_LIBPATH = ':' + os.path.join(baseDir, 'local', 'tbb', 'lib') + \
              ':' + os.path.join(baseDir, 'local', 'tbb', 'lib64')
if 'LD_LIBRARY_PATH' in e:
    e['LD_LIBRARY_PATH'] += TBB_LIBPATH
else:
    e['LD_LIBRARY_PATH'] = TBB_LIBPATH

err = 0
for v in versions:
    print("\n___________________________") 

    cmd = [os.path.join("install", v),
            "--n", str(args.n)]
    if not v == "exemple_seq":
       cmd += [ "--threads", str(args.threads)]
    
    print(' '.join(cmd))
    subprocess.call(cmd, env=e)
