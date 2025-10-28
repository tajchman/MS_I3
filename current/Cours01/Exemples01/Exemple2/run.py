#! /usr/bin/env python

import subprocess, os, sys, math, argparse
parser = argparse.ArgumentParser()
parser.add_argument('-n', type=int, default=12)
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

scriptDir = os.path.dirname(os.path.abspath(__file__))

k = 1
print('size          by lines   by columns')
for i in range(n):
  k *= 2
  x.append(k)
  command = [os.path.join(scriptDir, 'install', 'ex_1_2'), '-n', str(k)]
  p = subprocess.Popen(command, stdout=subprocess.PIPE)
  out, err = p.communicate()
  p = out.find(b"lignes   ") + 9
  m1.append(float(out[p:].split()[0]))
  p = out.find(b"colonnes ") + 9
  m2.append(float(out[p:].split()[0]))
  print("{:>7d} : {:12.3g} {:12.3g}".format(k, m1[-1], m2[-1]))

if graph:
  plt.figure()

  plt.semilogy(x, m1, "ro-", label="algo. lignes")
  plt.semilogy(x, m2, "bo-", label="algo. colonnes")
  plt.xlabel('taille matrice')
  plt.ylabel('temps CPU (s)')
  plt.legend()

  plt.savefig('matrices.pdf') 
  plt.show()
