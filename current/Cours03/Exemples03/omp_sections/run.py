#! /usr/bin/env python

from __future__ import print_function
import subprocess, os, argparse, glob, sys

pyversion = sys.version_info[0]
def mydecode(b):
    return b.decode('utf8')
    
versions = [
    "fib_seq",
    "fib_sections"
]

parser = argparse.ArgumentParser()
parser.add_argument('-n', type=int, default=48)
parser.add_argument('-l', '--levels', type=int, default=6)
args = parser.parse_args()

t = {}
err = 0
for v in versions:
    e = os.environ.copy()
    
    print("\n___________________________", file=sys.stderr) 
    print(v, file=sys.stderr) 

    cmd = [ 
           os.path.join("install", v),
            "--n", str(args.n)
          ]
    if v == 'fib_sections':
      cmd += [
           '--l', str(args.levels)
      ]                        

    s = mydecode(subprocess.check_output(cmd, stderr=subprocess.STDOUT, env=e))
    print(s, end='', file=sys.stderr)
    r0 = s.find('CPU time : ')
    r1 = s.find(' s', r0)
    t[v] = float(s[r0 + 11:r1])
  
print ("\n speedup = {:.2f}\n".format(t['fib_seq']/t['fib_sections']), file=sys.stderr)
