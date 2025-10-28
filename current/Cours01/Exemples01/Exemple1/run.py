#! /usr/bin/env python

import subprocess, os, sys, math, argparse, numpy

parser = argparse.ArgumentParser()
parser.add_argument('-k', '--samples', type=int, default=10)
parser.add_argument('-n', '--length', type=int, default=10)
parser.add_argument('-d', '--distance', type=int, default=1)
parser.add_argument('--variation', action="store_true")
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


n = args.length
k = args.samples
d = args.distance

scriptDir = os.path.dirname(os.path.abspath(__file__))
command = [os.path.join(scriptDir, 'install', 'ex_1_1'), 
           '-n', str(n), '-d', str(d)]

m = numpy.zeros((k, n))

for ik in range(k):

    subprocess.call(command)
    with open('results.dat') as f:
        for l in f:
            ll = l.split()
            it = int(ll[0]) - 1
            t = float(ll[1])
            m[ik, it] = t

x = numpy.linspace(1,n, num=n)
y = numpy.mean(m, axis=0)

if graph:
    plt.figure()
    p1 = plt.plot(x, y, "b-o", label="moyenne sur " + str(k) + ' exécutions')
    plt.xlabel('Itération')
    plt.legend()
    plt.title('Temps Itération n')
    outFileName = 'cycles_n_{}.pdf'.format(n)
    plt.savefig(outFileName)
    plt.show()
else:
    print('Temps Itération n')
    for i in range(len(y)):
        print("{:>5d}  {:12.3e}".format(i+1, y[i]))

