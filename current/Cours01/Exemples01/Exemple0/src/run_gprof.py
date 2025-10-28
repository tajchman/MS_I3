#! /usr/bin/env python

import subprocess, sys

with open('gprof.log', 'w') as fLog:
  subprocess.run(['gprof', '-b', sys.argv[-1]], stdout=fLog)
