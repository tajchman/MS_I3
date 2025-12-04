#! /usr/bin/env python

import subprocess, os, argparse, glob, sys

versions = [
    "fib_seq",
    "fib_tasks"
]

parser = argparse.ArgumentParser()
parser.add_argument('-n', type=int, default=48)
parser.add_argument('-t', '--threads', type=int, default=8)
parser.add_argument('-l', '--levels', type=int, default=3)
args = parser.parse_args()

err = 0
for v in versions:
    print("\n___________________________", file=sys.stderr) 
    print(v, file=sys.stderr) 

    cmd = [os.path.join("install", v),
                        "--n", str(args.n),
                        "--threads", str(args.threads),
                        "--levels", str(args.levels)]
    p = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    out = p.stdout.decode('utf8')
    print(out, end='', file=sys.stderr)
    r0 = out.find('CPU time : ')
    r1 = out.find(' s', r0)
    t = float(out[r0 + 11:r1])
    if v == "fib_seq":
        t0 = t
    else:
        print (" speedup = ", int(100*t0/t)/100, file=sys.stderr)
    print ("", file=sys.stderr)
