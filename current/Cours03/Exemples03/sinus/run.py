#! /usr/bin/env python3

from __future__ import print_function
import subprocess, os, argparse, glob, sys
def mydecode(b):
    return b.decode('utf8')

versions = [
    "seq",
    "omp_fine_grain",
    "omp_coarse_grain",
    "omp_fine_grain dynamic",
    "omp_adaptatif_run1",
    "omp_adaptatif_run2",
    "omp_adaptatif_run3",
    "omp_tasks",
    "tbb"
]

parser = argparse.ArgumentParser()
parser.add_argument('-t', '--threads', type=int, default=5)
parser.add_argument('-n', type=int, default=2000)
parser.add_argument('-chunk', type=int, default=0)
parser.add_argument('-tasks', type=int, default=100)
args = parser.parse_args()

for f in glob.glob('load*'):
  os.remove(f)

err = 0
for v in versions:
    e = os.environ.copy()
    e['OMP_NUM_THREADS'] = str(args.threads)
    compl = ''
    v = "sinus_" + v
    vv = v
    print("\n___________________________", file=sys.stderr) 
    if "adapt" in v:
        compl = '(' + v[-4:] + ')'
        vv = v[:-5]
    if "dynamic" in v:
        vv = v[:-8]
    cmd = [os.path.join("install", vv)]
    if not v == 'sinus_seq' and not v == 'sinus_tbb':
        cmd += ["-threads", str(args.threads)]
    if "dynamic" in v:
        cmd += ['-chunk', str(args.chunk)]
    if "task" in v:
        cmd += ['-tasks', str(args.tasks)]
    cmd += ['-n', str(args.n)]
    print(' '.join(cmd), compl, file=sys.stderr)
    s = mydecode(subprocess.check_output(cmd, stderr=subprocess.STDOUT, env=e))
    print(s, end='', file=sys.stderr)
    r0 = s.find('temps calcul : ')
    r1 = s.find(' s', r0)
    print(s[r0:r1+2], end='', file=sys.stderr)
    t = float(s[r0 + 15:r1])
    if v == "sinus_seq":
        t0 = t
        print(file=sys.stderr)
    else:
        print ("\n speedup = {:.2f}\n".format(t0/t), file=sys.stderr)
