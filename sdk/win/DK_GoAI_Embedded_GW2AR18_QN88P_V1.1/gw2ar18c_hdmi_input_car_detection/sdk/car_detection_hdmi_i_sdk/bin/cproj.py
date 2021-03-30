import os
import subprocess

#Path for Keil
def keil_compile(KEIL_PATH):
  #C/C++ Project Path
  PROJ_PATH = '../data/empu_m1'

  CC_SRC = [  './go_ai/helper.c',
              './go_ai/command_responder.c',
              './go_ai/bring_up.c',
              './go_ai/main.c',
              './empu_m1/system/system_GOWIN_M1.c',
              './empu_m1/peripheral/source/GOWIN_M1_gpio.c']

  #Path for S source files (relative to PROJ_PATH)
  ASM_SRC = [ './empu_m1/startup/startup_GOWIN_M1.s']

  #Path for Scatter file used for linking (relative to PROJ_PATH)
  LINK_SCT = './empu_m1/sct/empu_m1.sct'

  #Include folders/directories for C files (relative to PROJ_PATH)
  ARMCC_INC = [ './empu_m1/core',
                './empu_m1/peripheral/include',
                './empu_m1/system', 
                './go_ai']

  #Include folders/directories for S files (relative to PROJ_PATH)
  ARMASM_INC = [  './empu_m1/startup']

  #Construct path for ARM CC binaries
  ARMCC = KEIL_PATH+"/ARM/ARMCC/bin/armcc.exe"
  ARMASM = KEIL_PATH+"/ARM/ARMCC/bin/armasm.exe"
  ARMLINK = KEIL_PATH+"/ARM/ARMCC/bin/armlink.exe"
  ARMELF = KEIL_PATH+"/ARM/ARMCC/bin/fromelf.exe"

  AXF_FILE = 'empu_m1.axf'
  BIN_FILE = 'empu_m1.bin'

  #Create list of object files
  C_OBJ_FILES = [os.path.splitext(csrc)[0]+'.o' for csrc in CC_SRC]
  S_OBJ_FILES = [os.path.splitext(ssrc)[0]+'.o' for ssrc in ASM_SRC]

  #Command line options for armcc.exe
  ARMCC_OPT = [ '--c99', 
                '-c', 
                '--cpu Cortex-M1', 
                '--li', 
                '-g', 
                '-O0', 
                '--apcs=interwork', 
                '--split_sections']
                
  #Add '-I ' to include path
  ARMCC_INC_I = ['-I '+item for item in ARMCC_INC]

  #Command line options for armasm.exe
  ARMASM_OPT = [  '--cpu Cortex-M1',
                  '--li', 
                  '-g', 
                  '--apcs=interwork']

  #Add '-I ' to include path          
  ARMASM_INC_I = ['-I '+item for item in ARMASM_INC]

  #Command line options for armlink.exe
  ARMLINK_OPT = [ '--cpu Cortex-M1', 
                  '--strict']

  #Add '--scatter ' to scatter file path
  ARMLINK_SCT = '--scatter '+LINK_SCT
  
  #Path for Inference library used for linking
  ARMLINK_LIB = './go_ai/goai.lib'
  
  #Compile S files
  sdict = dict(zip(ASM_SRC, S_OBJ_FILES))
  for ssrc, sobj in sdict.items():
    cmd_str = ARMASM + ' ' + ' '.join([str(v) for v in ARMASM_OPT]) + ' ' + ' '.join([str(v) for v in ARMASM_INC_I]) + ' ' + ssrc + ' -o ' + sobj
    subprocess.call(cmd_str, cwd=PROJ_PATH, shell=True)

  #Compile C files
  cdict = dict(zip(CC_SRC, C_OBJ_FILES))
  for csrc, cobj in cdict.items():
    cmd_str = ARMCC + ' ' + ' '.join([str(v) for v in ARMCC_OPT]) + ' ' + ' '.join([str(v) for v in ARMCC_INC_I]) + ' ' + csrc + ' -o ' + cobj
    subprocess.call(cmd_str, cwd=PROJ_PATH, shell=True)
    
  #Link object and create .axf
  cmd_str = ARMLINK + ' ' + ' '.join([str(v) for v in ARMLINK_OPT]) + ' ' + ARMLINK_SCT + ' ' + ARMLINK_LIB + ' ' + ' '.join([str(v) for v in S_OBJ_FILES]) + ' ' + ' '.join([str(v) for v in C_OBJ_FILES]) + ' -o ' + AXF_FILE 
  subprocess.call(cmd_str, cwd=PROJ_PATH, shell=True)

  #Create binary file from .axf
  cmd_str = ARMELF + ' --bin -o ' + BIN_FILE + ' ' + AXF_FILE
  subprocess.call(cmd_str, cwd=PROJ_PATH, shell=True)
  
  #Clean up intermediate/generated files
  ##Remove object file created from S files
  for sobj in S_OBJ_FILES:
    os.remove(PROJ_PATH+'/'+sobj)
  ##Remove object file created from S files
  for cobj in C_OBJ_FILES:
    os.remove(PROJ_PATH+'/'+cobj) 
  ##Remove .axf file
  os.remove(PROJ_PATH+'/'+AXF_FILE)  
  # if 'output' is not exist, will build a new 'output'.
  if(os.path.exists('../data/output')==False):
    os.mkdir('../data/output')
  ##Move .bin file
  os.replace(PROJ_PATH+'/'+BIN_FILE, '../plugins/merge_bit/'+BIN_FILE)