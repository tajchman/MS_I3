#! /usr/bin/env python3

import os, subprocess, argparse, platform, sys, shutil
from pathlib import Path

plat = platform.system()
if plat == 'Linux' or plat.startswith('CYGWIN') or plat == 'Darwin':
  gen = '-GUnix Makefiles'
elif plat == 'Windows':
  gen = '-GNinja'

def execute(commands, e, buildDir):
  for cmd in commands:
    print('__________________\n', ' '.join(cmd), '\n', file=sys.stderr)
    err = subprocess.call(cmd, env=e, cwd=buildDir)
    if not err==0:
      return False
  return True

def build_communs(a):
  
  srcDir = os.path.join(a.srcDir, 'communs')
  buildDir = os.path.join(a.buildDir, 'communs')
  installDir = os.path.join(a.installDir, 'communs')
  os.makedirs(buildDir, exist_ok=True)
  
  configureCmd = ['cmake', gen, 
                  '-B', buildDir,
                  '-S', srcDir,
                  '-DCMAKE_INSTALL_PREFIX=' + installDir,
                  '-DCMAKE_BUILD_TYPE=' + a.mode.capitalize(),
                  ]
  if a.verbose:
    configureCmd.append('-DCMAKE_VERBOSE_MAKEFILE=ON')
  if a.glew_dir:
    configureCmd.append('-DGLEW_DIR=' + a.glew_dir)

  if a.mode == "profile":
    configureCmd += [
      '-DCMAKE_CXX_FLAGS=-pg',
      '-DCMAKE_EXE_LINKER_FLAGS=-pg',
      '-DCMAKE_SHARED_LINKER_FLAGS=-pg',
      '-DTIMERS=OFF'
    ]
  else:
    configureCmd += [
      '-DTIMERS=ON'
    ]
    
  compileCmd = ['cmake', '--build', buildDir]
  installCmd = ['cmake', '--install', buildDir]
  
  if a.type == 'float':
    configureCmd += ["-DFLOAT=On"]

  return execute([configureCmd, compileCmd, installCmd], a.env, buildDir)

def build_version(a, v):
  
  srcDir = os.path.join(a.srcDir, v[0])
  print('srcDir = ' + srcDir)
  buildDir = os.path.join(a.buildDir, v[0])
  os.makedirs(buildDir, exist_ok=True)
  
  configureCmd = ['cmake', gen, 
                  '-B', buildDir,
                  '-S', srcDir,
                  '-DCMAKE_INSTALL_PREFIX=' + a.installDir,
                  '-DCMAKE_BUILD_TYPE=' + a.mode.capitalize(),
                  '-Dcommuns_DIR=' + os.path.join(a.installDir, 'communs')
                  ]
  
  if a.mode == "profile":
    configureCmd += [
      '-DCMAKE_CXX_FLAGS=-pg',
      '-DCMAKE_EXE_LINKER_FLAGS=-pg',
      '-DCMAKE_SHARED_LINKER_FLAGS=-pg',
      '-DTIMERS=OFF'
    ]
  else:
    configureCmd += [
      '-DTIMERS=ON'
    ]
    
  if a.verbose:
    configureCmd.append('-DCMAKE_VERBOSE_MAKEFILE=ON')
  
  compileCmd = ['cmake', '--build', buildDir, '--parallel', a.parallel]
  installCmd = ['cmake', '--install', buildDir]

  if a.type == 'float':
    configureCmd += ["-DFLOAT=On"]

  return execute([configureCmd, compileCmd, installCmd], a.env, buildDir)

  
parser = argparse.ArgumentParser()
parser.add_argument('-m', '--mode', nargs="*", choices=['debug', 'release', 'profile'], default=['release'])
parser.add_argument('-v', '--verbose', action='store_true')
parser.add_argument('-t', '--type', nargs="*", choices=['float', 'double'], default=['double'])
parser.add_argument('-j', '--parallel', type=int, default=1)
parser.add_argument('--glew', default=None)
args = parser.parse_args()

class A:
  pass

if 'CC' in os.environ:
  cc = os.environ['CC']
else:
  cc = 'gcc'

if 'CXX' in os.environ:
  cxx = os.environ['CXX']
else:
  cxx = 'g++'

for m in args.mode:
  for t in args.type:
      a = A()
      a.env = os.environ.copy()
      a.cc = cc
      a.cxx = cxx      
      base = os.getcwd()
      a.srcDir      = os.path.join(base, 'src')
      a.buildDir    = os.path.join(base, 'build', cc, m, t)
      a.installDir  = os.path.join(base, 'install', cc, m, t)
      a.toolsSrcDir    = os.path.join(base, 'tools', 'src')
      a.toolsBuildDir    = os.path.join(base, 'build', cc, m, 'tools')
      a.toolsInstallDir  = os.path.join(base, 'install', cc, m, t, 'tools')
      a.type = t
      a.mode = m
      a.parallel = str(args.parallel)
      a.verbose = args.verbose
      a.glew_dir = args.glew

      os.makedirs(a.toolsSrcDir, exist_ok=True)
      if not build_communs(a):
        sys.exit(-1)
  
      listCases = [
        [os.path.join("CPU", "serial")],
        [os.path.join("CPU", "openmp")],
        [os.path.join("CPU", "threads")],
        [os.path.join("CPU", "tbb")]
      ]
      for v in listCases:
        if not build_version(a, v):
          sys.exit(-1)
  
