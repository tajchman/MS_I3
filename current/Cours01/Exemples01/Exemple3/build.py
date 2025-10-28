#! /usr/bin/env python3

import os, subprocess, argparse, platform, sys

parser = argparse.ArgumentParser()
parser.add_argument('-c', '--compiler', choices=['gnu', 'intel', 'msvc'], default='gnu')
parser.add_argument('-m', '--mode', choices=['Debug', 'Release'], default='Release')
parser.add_argument('-v', '--verbose', action='store_true')
parser.add_argument('--tests', action='store_true')
args = parser.parse_args()

base       = os.getcwd()
srcDir     = os.path.join(base, 'src')
buildDir   = os.path.join(base, 'build')
installDir = os.path.join(base, 'install')
if args.mode == 'Debug':
  buildDir = os.path.join(buildDir, 'Debug')
  installDir = os.path.join(installDir, 'Debug')
testDir    = os.path.join(base, 'tests')
for d in [buildDir, testDir]:
  os.makedirs(d, exist_ok=True)

e = os.environ.copy()

p = platform.system()
if p == 'Windows':
  gen = '-GNinja'
  if args.compiler == 'intel':
    e['CC'] = 'icx'
    e['CXX'] = 'icpx'
  else:
    e['CC'] = 'cl.exe'
    e['CXX'] = 'cl.exe'
  compileCmd = ['ninja', 'install']
elif p == 'Linux':
  gen = '-GUnix Makefiles'
  if args.compiler == 'intel':
    e['CC'] = 'icx'
    e['CXX'] = 'icpx'
  else:
    e['CC'] = 'gcc'
    e['CXX'] = 'g++'
  if args.verbose:
    compileCmd = ['make', 'VERBOSE=1', '--no-print-directory', 'install']
  else:
    compileCmd = ['make', '--no-print-directory', 'install']

configureCmd = ['cmake', gen, 
                '-B', buildDir,
                '-S', srcDir,
                '-DCMAKE_INSTALL_PREFIX=' + installDir,
                '-DCMAKE_BUILD_TYPE=' + args.mode,
                '-DTEST_DIR=' + testDir]
testCmd      = ['ctest', '--output-on-failure']

commands = [
  configureCmd,
  compileCmd,
  testCmd
]

for cmd in commands:
  if cmd == testCmd and not args.tests:
    continue
  print('__________________\n', ' '.join(cmd), '\n', file=sys.stderr)
  err = subprocess.call(cmd, cwd=buildDir, env=e)
  if not err==0:
    break 
