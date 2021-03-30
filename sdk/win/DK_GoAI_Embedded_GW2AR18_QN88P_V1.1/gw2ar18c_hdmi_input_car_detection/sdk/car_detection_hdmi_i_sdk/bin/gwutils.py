import subprocess
import os
import shutil
import time
import stat

# copy fs and posp file to merge_bit tool
def run_gw_eda_win(): 
  if(os.path.exists('../plugins/merge_bit/car_detection.fs')):
    os.chmod('../plugins/merge_bit/car_detection.fs',stat.S_IWRITE)
    os.remove('../plugins/merge_bit/car_detection.fs')
  shutil.copyfile('../data/fpga/car_detection.fs', '../plugins/merge_bit/car_detection.fs')
  shutil.copyfile('../data/fpga/car_detection.posp', '../plugins/merge_bit/car_detection.posp')

# merge fs file and bin file
def run_merge_bit():
  cmd = 'make_loc.exe -i car_detection.posp -s 8 -t gowin_syn'
  sh_proc = subprocess.Popen(cmd, cwd=r"../plugins/merge_bit", shell=True)
  stdout, stderr = sh_proc.communicate()  
  cmd = 'merge_bit.exe empu_m1.bin itcm.loc car_detection.fs'
  sh_proc = subprocess.Popen(cmd, cwd=r"../plugins/merge_bit", shell=True)
  stdout, stderr = sh_proc.communicate()
  if(os.path.exists('../data/output/car_detection.fs')):
    os.chmod('../data/output/car_detection.fs',stat.S_IWRITE)
    os.remove('../data/output/car_detection.fs')
  os.replace('../plugins/merge_bit/new_car_detection.fs', '../data/output/car_detection.fs')
  os.remove('../plugins/merge_bit/empu_m1.bin')
  if(os.path.exists('../plugins/merge_bit/car_detection.fs')):
    os.chmod('../plugins/merge_bit/car_detection.fs',stat.S_IWRITE) #fs file is only read.
    os.remove('../plugins/merge_bit/car_detection.fs')
  os.remove('../plugins/merge_bit/car_detection.posp')
  os.remove('../plugins/merge_bit/itcm.loc')

# convert fs file to bin file
def run_fs2bin():
  if(os.path.exists('../data/output/car_detection.bin')):
    os.chmod('../data/output/car_detection.bin',stat.S_IWRITE)
    os.remove('../data/output/car_detection.bin')
  
  with open('../data/output/car_detection.bin', 'wb') as fout:
    with open('../data/output/car_detection.fs') as fin:
      for line in fin:
        if '//' in line:
          continue
        line = line.strip()
        for i in range(0, len(line), 8):
          _b = int(line[i: i+8], 2)
          fout.write(bytes([_b]) )
  fout.close()
  fin.close()

  if(os.path.exists('../data/output/car_detection.fs')):
    os.chmod('../data/output/car_detection.fs',stat.S_IWRITE)
    os.remove('../data/output/car_detection.fs')

# dowload
def program_fpga(programmer_path):
  CWD = os.getcwd()
  CWD = CWD.replace('\\','/')
  #1nd : DK-GoAI-GW2AR18C_QN88P V1.1 downloads bit bin file
  cmd = programmer_path+'/bin/programmer_cli.exe -d GW2AR-18C -r 42 --spiaddr 0x000000 -m '+CWD+'/../data/output/car_detection.bin'
  print (cmd)
  sh_proc = subprocess.Popen(cmd, cwd=r"../data/output", shell=True)
  stdout, stderr = sh_proc.communicate()
  time.sleep(3)
  #2rd : DK-GoAI-GW2AR18C_QN88P V1.1 downloads wb bin file
  cmd = programmer_path+'/bin/programmer_cli.exe -d GW2AR-18C -r 42 --spiaddr 0x700000 -m '+CWD+'/../data/output/car_detection_wb.bin'
  print (cmd)
  sh_proc = subprocess.Popen(cmd, cwd=r"../data/output", shell=True)
  stdout, stderr = sh_proc.communicate()