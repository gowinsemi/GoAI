"""Python command line interface for building Gowin GoAI Car Detection demo design"""

import argparse
import sys
import os
import gwutils
import cproj
import tf_model

def dir_path(string):
  if os.path.isdir(string):
    return string
  else:
    raise NotADirectoryError(string)

def file_path(string):
  if os.path.exists(string):
    return string
  else:
    raise FileNotFoundError(string)

def run_main():

  parser = argparse.ArgumentParser(
      description=("Command line tool to build/program Gowin GoAI Car Detection demo design."))

  parser.add_argument(
      "--tflite_model_file",
      "-m",
      type=file_path,
      help="Full filepath of the TensorFlow Lite (FlatBuffers) model.",
      required=True)

  parser.add_argument(
      "--device",
      "-d",
      type=str,
      help="Gowin Device supported on Embedded Vision Board (default:GW2AR18C)",
      choices=['GW2AR18C'],
      default="GW2AR18C")

  parser.add_argument(
      "--training_type",
      "-t",
      type=str,
      help="Tflite model training type (default:tf)",
      choices=['tf', 'keras'],
      default="tf")

  parser.add_argument(
      "--programmer_path",
      "-g",
      type=dir_path,
      help="Full folderpath of Gowin EDA (default:C:/Gowin/Gowin_V1.9.7.02Beta/Programmer)",
      default="C:/Gowin/Gowin_V1.9.7.02Beta/Programmer")

  parser.add_argument(
      "--keil_path",
      "-k",
      type=dir_path,
      help="Full folderpath of Keil IDE (default:C:/Keil_v5)",
      default="C:/Keil_v5")

  flags, _ = parser.parse_known_args(args=sys.argv[1:])

  model_train_type = flags.training_type
  
  if (os.name == 'nt'):
    print('ANALYZE TFLITE MODEL...')
    tf_model.gen_json_file(flags.tflite_model_file)
    print('EXTRACTING INFO FROM TFLITE MODEL...')
    if(model_train_type == 'tf'):
      # tf
      tf_model.gen_tf_model_params_file()
    elif(model_train_type == 'keras'):
      # keras
      tf_model.gen_keras_model_params_file()
    else:
      # default is tf
      tf_model.gen_tf_model_params_file()
    print('BUILDING EMPU M1 C PROJECT...')
    cproj.keil_compile(flags.keil_path)
    print('PROVISIONING FPGA DESIGN...')
    gwutils.run_gw_eda_win()
    print('RUNNING MERGE-BIT...')
    gwutils.run_merge_bit()
    print('RUNNING FS2BIN...')
    gwutils.run_fs2bin()
    print('PROGRAMMING FPGA...')
    gwutils.program_fpga(flags.programmer_path)
  else:
    print('Only Windows OS is supported!')


if __name__ == "__main__":
  run_main()