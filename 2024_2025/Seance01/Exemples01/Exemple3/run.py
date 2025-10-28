#! /usr/bin/env python

import subprocess, os, sys, math, argparse

parser = argparse.ArgumentParser()
parser.add_argument('-n', type=int, default=7)
parser.add_argument('--text', action="store_true")
args = parser.parse_args()

graph = False
if not args.text:
  try:
    import matplotlib
    import matplotlib.pyplot as plt
    graph = True
  except:
    pass


n = args.n
x = []
m1 = []
m2 = []
d = []

scriptDir = os.path.dirname(os.path.abspath(__file__))

k = 10
print("              localités temporelles")
print("taille          'bonne'      'mauvaise'   différence")
for i in range(n):
  k *= 10
  x.append(k)
  command = [os.path.join(scriptDir, 'install', 'ex_1_3'), '{}'.format(k)]
  p = subprocess.Popen(command, stdout=subprocess.PIPE)
  out, err = p.communicate()
  s = b"'bonne' loc. temporelle "
  p = out.find(s) + len(s)
  m1.append(float(out[p:].split()[0]))
  s = b"'mauvaise' loc. temporelle "
  p = out.find(s) + len(s)
  m2.append(float(out[p:].split()[0]))
  d.append(100.0*(m2[-1]-m1[-1])/m1[-1])
  print("{:>10d} {:12.3g}    {:12.3g} {:12.3g} ({:+7.1f} %)".format(k, m1[-1], m2[-1], 
                                                               m2[-1]-m1[-1], d[-1]))

if graph:
  plt.figure()

  plt.semilogx(x, d, "ro-")
  plt.axhline(0)
  plt.xlabel('taille vecteur')
  plt.suptitle("différence localités temporelles (en %)")
  plt.title("('mauvaise' localité - 'bonne' localité)")
  plt.savefig('localite_temporelle.pdf') 
  plt.show()
