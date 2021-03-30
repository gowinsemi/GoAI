import json
import math
import subprocess
import os

'''Generate JSON file'''
def gen_json_file(mode_path):
  CWD = os.getcwd()
  CWD = CWD.replace('\\','/')
  flatc_command = CWD+'/../plugins/flatc/flatc.exe ' + ' --json --strict-json --raw-binary ' + CWD+'/../plugins/flatc/schema.fbs ' + ' -- '+mode_path
  # if 'work' is not exist, will build a new 'work'.
  if(os.path.exists('../data/work')==False):
    os.mkdir('../data/work')
  sh_proc = subprocess.Popen(flatc_command, cwd=r"../data/work", shell=True)
  stdout, stderr = sh_proc.communicate()


'''Generate tf model parameters header file and bin file'''
def gen_tf_model_params_file():
  with open('../data/work/car_detection.json', 'r') as fp:
    jsonObj = json.load(fp)             # Load JSON objects.

  # First Level Useful Keys for TFLite Flatbuffers JSON
  OP_CODES  = 'operator_codes'          # key 'operator_codes'
  SUBGRAPHS = 'subgraphs'               # key 'subgraphs'
  BUFFERS   = 'buffers'                 # key 'buffers'
  
  # parameters in DepthwiseConv2D/Conv2D/AreragePooling2D
  DEPTHWISE_list = []                   # Flag of DepthwiseConv2D layer. 1 is DepthwiseConv2D; 0 is not DepthwiseConv2D.
  CONV_PADDING_H_list = []              # DepthwiseConv2D/Conv2D padding height.
  CONV_PADDING_W_list = []              # DepthwiseConv2D/Conv2D padding width.
  CONV_STRIDE_H_list = []               # DepthwiseConv2D/Conv2D stride height.
  CONV_STRIDE_W_list = []               # DepthwiseConv2D/Conv2D stride width.
  DILATION_FACTOR_H_list = []           # DepthwiseConv2D/Conv2D dilations height.
  DILATION_FACTOR_W_list = []           # DepthwiseConv2D/Conv2D dilations width.
  DEPTH_MULTIPLIER_list = []            # DepthwiseConv2D depth multiplier in DepthwiseConv2D layer
  OUT_ACTIVATION_MIN_list = []          # This is hard coded -128 for int8 type tensors
  OUT_ACTIVATION_MAX_list = []          # This is hard coded 127 for int8 type tensors
  IN_OFFSET_list = []                   # Input offset. Input tensor's zero_point.
  WT_OFFSET_list = []                   # Weight offset. Weight tensor's zero_point.
  OUT_OFFSET_list = []                  # Output offset. Output tensor's zero_point.
  OUT_MULTIPLIER_OFFSET_list = []       # Output multiplier offset.
  OUT_SHIFT_OFFSET_list = []            # Output shift offset.
  BATCH_list = []                       # Data batches input into convolution.
  CONV_IN_CH_list = []                  # DepthwiseConv2D/Conv2D input tensor's channels.
  CONV_IN_DIM_H_list = []               # DepthwiseConv2D/Conv2D input tensor's dimension height.
  CONV_IN_DIM_W_list = []               # DepthwiseConv2D/Conv2D input tensor's dimension width.
  CONV_OUT_CH_list = []                 # DepthwiseConv2D/Conv2D output tensor's channels.
  CONV_OUT_DIM_H_list = []              # DepthwiseConv2D/Conv2D output dimension height.
  CONV_OUT_DIM_W_list = []              # DepthwiseConv2D/Conv2D output dimension width.
  CONV_KER_CH_list = []                 # DepthwiseConv2D/Conv2D filter/kernel/weight tensor's channels.
  CONV_KER_DIM_H_list = []              # DepthwiseConv2D/Conv2D filter/kernel/weight tensor's dimension height.
  CONV_KER_DIM_W_list = []              # DepthwiseConv2D/Conv2D filter/kernel/weight tensor's dimension height.
  POOL_EN_list = []                     # Flag of AveragePool2D layer. 1 is AveragePool2D; 0 is not AveragePool2D.
  POOL_MODE_list = []                   # Mode of AveragePool2D layer. 1 is AveragePool2D; 0 is not AveragePool2D.
  POOL_IN_CH_list = []                  # AveragePool2D input tensor's channels.
  POOL_IN_DIM_H_list = []               # AveragePool2D input tensor's dimension height.
  POOL_IN_DIM_W_list = []               # AveragePool2D input tensor's dimension width.
  POOL_OUT_CH_list = []                 # AveragePool2D output tensor's channels.
  POOL_OUT_DIM_H_list = []              # AveragePool2D output tensor's dimension height.
  POOL_OUT_DIM_W_list = []              # AveragePool2D output tensor's dimension width.
  POOL_KER_DIM_H_list = []              # AveragePool2D filter/kernel/weight tensor's dimension height.
  POOL_KER_DIM_W_list = []              # AveragePool2D filter/kernel/weight tensor's dimension width.
  POOL_PADDING_H_list = []              # AveragePool2D padding height.
  POOL_PADDING_W_list = []              # AveragePool2D padding width.
  POOL_STRIDE_H_list = []               # AveragePool2D stride height.
  POOL_STRIDE_W_list = []               # AveragePool2D stride width.
  
  # car_detection parameters file and weight/bias binary file.
  # if 'output' is not exist, will build a new 'output'.
  if(os.path.exists('../data/output')==False):
    os.mkdir('../data/output')
  wb_fp = open('../data/output/car_detection_wb.bin', 'wb')
  cp_fp = open('../data/empu_m1/go_ai/tflite_car_detection_parameters.h', 'w')
  
  # parse car_detection JSON file and provision parameters/weights/bias
  # opcode_index : 
  #                1    = Conv2D;
  #                2    = DepthwiseConv2D;
  #                3    = Reshape;
  #                4    = Softmax;
  #                none = AveragePool2D.
  for sgidx in jsonObj[SUBGRAPHS]:
    for opidx in sgidx['operators']:
      if (opidx.get('opcode_index', 0) == 1):
        # -------------------------------------- Conv2D ------------------------------ #
        ''' variables '''
        input_tensor = sgidx['tensors'][opidx['inputs'][0]]
        filter_tensor = sgidx['tensors'][opidx['inputs'][1]]
        bias_tensor = sgidx['tensors'][opidx['inputs'][2]]
        output_tensor = sgidx['tensors'][opidx['outputs'][0]]
        
        filter_scale_list = []
        multiplier_list = []                                                       # 32-bit output_multiplier
        shift_list = []                                                            # 32-bit output_shift
        multiplier_buf = []                                                        # 8-bit output_multiplier
        shift_buf = []                                                             # 8-bit output_shift
        
        ''' calculate '''
        # padding height/width
        # shape[1] = height
        # shape[2] = width
        # padding height
        padding_h = int((input_tensor['shape'][1] + opidx['builtin_options']['stride_h'] - 1)/opidx['builtin_options']['stride_h'])
        padding_h = int((padding_h - 1) * opidx['builtin_options']['stride_h'] + filter_tensor['shape'][1] - input_tensor['shape'][1])
        if (padding_h > 0):
          padding_h = padding_h
        else:
          padding_h = 0
        # padding width
        padding_w = int((input_tensor['shape'][2] + opidx['builtin_options']['stride_w'] - 1)/opidx['builtin_options']['stride_w'])
        padding_w = int((padding_w - 1) * opidx['builtin_options']['stride_w'] + filter_tensor['shape'][2] - input_tensor['shape'][2])
        if (padding_w > 0):
          padding_w = padding_w
        else:
          padding_w = 0
        # input/filter/output scale
        input_scale = input_tensor['quantization']['scale'][0]                      # input tensor's scale
        for filter_scale in filter_tensor['quantization']['scale']:                 # filter tensor's scale
          filter_scale_list.append(filter_scale)
        output_scale = output_tensor['quantization']['scale'][0]                    # output tensor's scale
        for filter_scale in filter_scale_list:
          multiplier, shift = math.frexp((input_scale*filter_scale)/output_scale)
          multiplier_int = int (multiplier * (1<<31))
          multiplier_list.append(multiplier_int)
          shift_list.append(shift)
        
        ''' parameters '''
        #conv2d parameters
        CONV_PADDING_H_list.append(int(padding_h/2))
        CONV_PADDING_W_list.append(int(padding_w/2))
        CONV_STRIDE_H_list.append(opidx['builtin_options']['stride_h'])
        CONV_STRIDE_W_list.append(opidx['builtin_options']['stride_w'])
        DILATION_FACTOR_H_list.append(1)
        DILATION_FACTOR_W_list.append(1)
        DEPTH_MULTIPLIER_list.append(1)
        OUT_ACTIVATION_MIN_list.append(-128)                                         # int8 -128
        OUT_ACTIVATION_MAX_list.append(127)                                          # int8 127
        IN_OFFSET_list.append(-input_tensor['quantization']['zero_point'][0])
        WT_OFFSET_list.append(-filter_tensor['quantization']['zero_point'][0])       # TODO : an array but all zero.
        OUT_OFFSET_list.append(output_tensor['quantization']['zero_point'][0])
        OUT_MULTIPLIER_OFFSET_list.append(len(multiplier_list) * 4)
        OUT_SHIFT_OFFSET_list.append(len(shift_list) * 4)
        BATCH_list.append(1)
        CONV_IN_DIM_H_list.append(input_tensor['shape'][1])
        CONV_IN_DIM_W_list.append(input_tensor['shape'][2])
        CONV_IN_CH_list.append(input_tensor['shape'][3])
        CONV_OUT_DIM_H_list.append(output_tensor['shape'][1])
        CONV_OUT_DIM_W_list.append(output_tensor['shape'][2])
        CONV_OUT_CH_list.append(output_tensor['shape'][3])
        CONV_KER_DIM_H_list.append(filter_tensor['shape'][1])
        CONV_KER_DIM_W_list.append(filter_tensor['shape'][2])
        CONV_KER_CH_list.append(filter_tensor['shape'][0])                          # Conv2D filter shape[0].
        # average_pool2d parameters
        POOL_EN_list.append(0)
        POOL_MODE_list.append(0)
        POOL_OUT_DIM_H_list.append(0)
        POOL_OUT_DIM_W_list.append(0)
        POOL_OUT_CH_list.append(0)
        POOL_IN_DIM_H_list.append(0)
        POOL_IN_DIM_W_list.append(0)
        POOL_IN_CH_list.append(0)
        POOL_KER_DIM_H_list.append(0)
        POOL_KER_DIM_W_list.append(0)
        POOL_PADDING_H_list.append(0)
        POOL_PADDING_W_list.append(0)
        POOL_STRIDE_H_list.append(0)
        POOL_STRIDE_W_list.append(0)
        # depthwise_conv2d flag
        DEPTHWISE_list.append(0)
        # output_multiplier/output_shift
        for mulitiplier in multiplier_list:                                           # write to binary as 8-bits
          multiplier_buf.append(mulitiplier&0x000000ff)
          multiplier_buf.append((mulitiplier>>8)&0x000000ff)
          multiplier_buf.append((mulitiplier>>16)&0x000000ff)
          multiplier_buf.append((mulitiplier>>24)&0x000000ff)
        for shift in shift_list:
          shift_buf.append(shift&0x000000ff)
          shift_buf.append((shift>>8)&0x000000ff)
          shift_buf.append((shift>>16)&0x000000ff)
          shift_buf.append((shift>>24)&0x000000ff)
        # weight/bias
        weight_buf = jsonObj[BUFFERS][filter_tensor['buffer']]['data']                # weight
        bias_buf = jsonObj[BUFFERS][bias_tensor['buffer']]['data']                    # bias
        #
        w_batch = sgidx['tensors'][opidx['inputs'][1]]['shape'][0]
        w_kernel = sgidx['tensors'][opidx['inputs'][1]]['shape'][1] * sgidx['tensors'][opidx['inputs'][1]]['shape'][2]
        w_channel = sgidx['tensors'][opidx['inputs'][1]]['shape'][3]        
        #
        wb_rearrange_buf = []
        #
        for btidx in range (w_batch):
          for mlidx in range (4):
            wb_rearrange_buf.append(multiplier_buf[(btidx * 4) + mlidx])

          for shidx in range (4):
            wb_rearrange_buf.append(shift_buf[(btidx * 4) + shidx])            
        
          for bsidx in range (4):
            wb_rearrange_buf.append(bias_buf[(btidx * 4) + bsidx])          

          for kridx in range (w_kernel):
            for chidx in range (w_channel):
              wb_rearrange_buf.append(weight_buf[(btidx*w_kernel*w_channel) + (kridx*w_channel) + chidx])
        #
        wb_fp.write(bytearray(wb_rearrange_buf))
        
      elif (opidx.get('opcode_index', 0) == 2):
        # --------------------------------------- DepthwiseConv2D -------------------------------- #
        ''' variables '''
        input_tensor = sgidx['tensors'][opidx['inputs'][0]]
        filter_tensor = sgidx['tensors'][opidx['inputs'][1]]
        bias_tensor = sgidx['tensors'][opidx['inputs'][2]]
        output_tensor = sgidx['tensors'][opidx['outputs'][0]]
        
        filter_scale_list = []
        multiplier_list = []                                                       # 32-bit output_multiplier
        shift_list = []                                                            # 32-bit output_shift
        multiplier_buf = []                                                        # 8-bit output_multiplier
        shift_buf = []                                                             # 8-bit output_shift
        
        ''' calculate '''
        # padding height/width
        # shape[1] = height
        # shape[2] = width
        # padding height
        padding_h = int((input_tensor['shape'][1] + opidx['builtin_options']['stride_h'] - 1)/opidx['builtin_options']['stride_h'])
        padding_h = int((padding_h - 1) * opidx['builtin_options']['stride_h'] + filter_tensor['shape'][1] - input_tensor['shape'][1])
        if (padding_h > 0):
          padding_h = padding_h
        else:
          padding_h = 0
        # padding width
        padding_w = int((input_tensor['shape'][2] + opidx['builtin_options']['stride_w'] - 1)/opidx['builtin_options']['stride_w'])
        padding_w = int((padding_w - 1) * opidx['builtin_options']['stride_w'] + filter_tensor['shape'][2] - input_tensor['shape'][2])
        if (padding_w > 0):
          padding_w = padding_w
        else:
          padding_w = 0
        # input/filter/output scale
        input_scale = input_tensor['quantization']['scale'][0]                      # input tensor's scale
        for filter_scale in filter_tensor['quantization']['scale']:                 # filter tensor's scale
          filter_scale_list.append(filter_scale)
        output_scale = output_tensor['quantization']['scale'][0]                    # output tensor's scale
        for filter_scale in filter_scale_list:
          multiplier, shift = math.frexp((input_scale*filter_scale)/output_scale)
          multiplier_int = int (multiplier * (1<<31))
          multiplier_list.append(multiplier_int)
          shift_list.append(shift)
        
        ''' parameters '''
        #depthwise_conv2d parameters
        DEPTHWISE_list.append(1)                                                     #1 : DepthwiseConv2D.
        CONV_PADDING_H_list.append(int(padding_h/2))
        CONV_PADDING_W_list.append(int(padding_w/2))
        CONV_STRIDE_H_list.append(opidx['builtin_options']['stride_h'])
        CONV_STRIDE_W_list.append(opidx['builtin_options']['stride_w'])
        DILATION_FACTOR_H_list.append(1)
        DILATION_FACTOR_W_list.append(1)
        DEPTH_MULTIPLIER_list.append(opidx['builtin_options']['depth_multiplier'])
        OUT_ACTIVATION_MIN_list.append(-128)                                         # int8 -128
        OUT_ACTIVATION_MAX_list.append(127)                                          # int8 127
        IN_OFFSET_list.append(-input_tensor['quantization']['zero_point'][0])
        WT_OFFSET_list.append(-filter_tensor['quantization']['zero_point'][0])       # TODO : an array but all zero.
        OUT_OFFSET_list.append(output_tensor['quantization']['zero_point'][0])
        OUT_MULTIPLIER_OFFSET_list.append(len(multiplier_list) * 4)
        OUT_SHIFT_OFFSET_list.append(len(shift_list) * 4)
        BATCH_list.append(1)
        CONV_IN_DIM_H_list.append(input_tensor['shape'][1])
        CONV_IN_DIM_W_list.append(input_tensor['shape'][2])
        CONV_IN_CH_list.append(input_tensor['shape'][3])
        CONV_OUT_DIM_H_list.append(output_tensor['shape'][1])
        CONV_OUT_DIM_W_list.append(output_tensor['shape'][2])
        CONV_OUT_CH_list.append(output_tensor['shape'][3])
        CONV_KER_DIM_H_list.append(filter_tensor['shape'][1])
        CONV_KER_DIM_W_list.append(filter_tensor['shape'][2])
        CONV_KER_CH_list.append(filter_tensor['shape'][3])
        # average_pool2d parameters
        POOL_EN_list.append(0)
        POOL_MODE_list.append(0)
        POOL_OUT_DIM_H_list.append(0)
        POOL_OUT_DIM_W_list.append(0)
        POOL_OUT_CH_list.append(0)
        POOL_IN_DIM_H_list.append(0)
        POOL_IN_DIM_W_list.append(0)
        POOL_IN_CH_list.append(0)
        POOL_KER_DIM_H_list.append(0)
        POOL_KER_DIM_W_list.append(0)
        POOL_PADDING_H_list.append(0)
        POOL_PADDING_W_list.append(0)
        POOL_STRIDE_H_list.append(0)
        POOL_STRIDE_W_list.append(0)
        # output_multiplier/output_shift
        for mulitiplier in multiplier_list:                                           # write to binary as 8-bits
          multiplier_buf.append(mulitiplier&0x000000ff)
          multiplier_buf.append((mulitiplier>>8)&0x000000ff)
          multiplier_buf.append((mulitiplier>>16)&0x000000ff)
          multiplier_buf.append((mulitiplier>>24)&0x000000ff)
        for shift in shift_list:
          shift_buf.append(shift&0x000000ff)
          shift_buf.append((shift>>8)&0x000000ff)
          shift_buf.append((shift>>16)&0x000000ff)
          shift_buf.append((shift>>24)&0x000000ff)
        # weight/bias
        weight_buf = jsonObj[BUFFERS][filter_tensor['buffer']]['data']                # weight
        bias_buf = jsonObj[BUFFERS][bias_tensor['buffer']]['data']                    # bias
        #
        w_batch = sgidx['tensors'][opidx['inputs'][1]]['shape'][0]
        w_kernel  = sgidx['tensors'][opidx['inputs'][1]]['shape'][1] * sgidx['tensors'][opidx['inputs'][1]]['shape'][2]
        w_channel = sgidx['tensors'][opidx['inputs'][1]]['shape'][3]        
        #
        wb_rearrange_buf = []
        #
        for btidx in range (w_batch):
          for chidx in range (w_channel):
            for mlidx in range (4):
              wb_rearrange_buf.append(multiplier_buf[(chidx * 4) + mlidx])

            for shidx in range (4):
              wb_rearrange_buf.append(shift_buf[(chidx * 4) + shidx])        
          
            for bsidx in range (4):
              wb_rearrange_buf.append(bias_buf[(chidx * 4) + bsidx])          

            for kridx in range (w_kernel):            
              wb_rearrange_buf.append(weight_buf[(btidx*w_kernel*w_channel) + (kridx*w_channel) + chidx])
        #
        wb_fp.write(bytearray(wb_rearrange_buf))
        
      elif (opidx.get('opcode_index', 0) == 3):
        # ----------------------------------------- Reshape ------------------------------------- #
        # TODO : 
        print('TODO : INGORE RESHAPE LAYER.')
        
      elif (opidx.get('opcode_index', 0) == 4):
        # ------------------------------------------ Softmax ------------------------------------ #
        # TODO :
        print('TODO : INGORE SOFTMAX LAYER.')
        
      else:
        # ------------------------------------------ AveragePool2D-------------------------------- #
        ''' variables '''
        input_tensor = sgidx['tensors'][opidx['inputs'][0]]
        output_tensor = sgidx['tensors'][opidx['outputs'][0]]
        
        ''' calculate '''
        # padding height/width
        # shape[1] = height
        # shape[2] = width
        # padding height
        padding_h = int((input_tensor['shape'][1] + opidx['builtin_options']['stride_h'] - opidx['builtin_options']['filter_height'])/opidx['builtin_options']['stride_h'])
        padding_h = int((padding_h - 1) * opidx['builtin_options']['stride_h'] + opidx['builtin_options']['filter_height'] - input_tensor['shape'][1])
        if (padding_h > 0):
          padding_h = padding_h
        else:
          padding_h = 0
        # padding width
        padding_w = int((input_tensor['shape'][2] + opidx['builtin_options']['stride_w'] - opidx['builtin_options']['filter_width'])/opidx['builtin_options']['stride_w'])
        padding_w = int((padding_w - 1) * opidx['builtin_options']['stride_w'] + opidx['builtin_options']['filter_width'] - input_tensor['shape'][2])
        if (padding_w > 0):
          padding_w = padding_w
        else:
          padding_w = 0
        ''' parameters '''
        # average_pool2d parameters
        POOL_EN_list.append(1)
        POOL_MODE_list.append(1)
        POOL_IN_DIM_H_list.append(input_tensor['shape'][1])
        POOL_IN_DIM_W_list.append(input_tensor['shape'][2])
        POOL_IN_CH_list.append(input_tensor['shape'][3])
        POOL_OUT_DIM_H_list.append(output_tensor['shape'][1])
        POOL_OUT_DIM_W_list.append(output_tensor['shape'][2])
        POOL_OUT_CH_list.append(output_tensor['shape'][3])
        POOL_KER_DIM_H_list.append(opidx['builtin_options']['filter_height'])
        POOL_KER_DIM_W_list.append(opidx['builtin_options']['filter_width'])
        POOL_PADDING_H_list.append(int(padding_h/2))
        POOL_PADDING_W_list.append(int(padding_w/2))
        POOL_STRIDE_H_list.append(opidx['builtin_options']['stride_h'])
        POOL_STRIDE_W_list.append(opidx['builtin_options']['stride_w'])
        #depthwise_conv2d/conv2d parameters
        DEPTHWISE_list.append(0)
        CONV_PADDING_H_list.append(0)
        CONV_PADDING_W_list.append(0)
        CONV_STRIDE_H_list.append(0)
        CONV_STRIDE_W_list.append(0)
        DILATION_FACTOR_H_list.append(0)
        DILATION_FACTOR_W_list.append(0)
        DEPTH_MULTIPLIER_list.append(0)
        OUT_ACTIVATION_MIN_list.append(0)
        OUT_ACTIVATION_MAX_list.append(0)
        IN_OFFSET_list.append(0)
        WT_OFFSET_list.append(0)
        OUT_OFFSET_list.append(0)
        BATCH_list.append(1)
        OUT_SHIFT_OFFSET_list.append(0)
        OUT_MULTIPLIER_OFFSET_list.append(0)
        CONV_IN_CH_list.append(0)
        CONV_IN_DIM_H_list.append(0)
        CONV_IN_DIM_W_list.append(0)
        CONV_OUT_CH_list.append(0)
        CONV_OUT_DIM_H_list.append(0)
        CONV_OUT_DIM_W_list.append(0)
        CONV_KER_CH_list.append(0)
        CONV_KER_DIM_H_list.append(0)
        CONV_KER_DIM_W_list.append(0)
  
  # Optimize AveragePool2D layer out, delete AveragePool2D parameters.
  peidx = POOL_EN_list.index(1)
  del DEPTHWISE_list[peidx]
  del CONV_PADDING_H_list[peidx]
  del CONV_PADDING_W_list[peidx]
  del CONV_STRIDE_H_list[peidx]
  del CONV_STRIDE_W_list[peidx]
  del DILATION_FACTOR_H_list[peidx]
  del DILATION_FACTOR_W_list[peidx]
  del DEPTH_MULTIPLIER_list[peidx]
  del OUT_ACTIVATION_MIN_list[peidx]
  del OUT_ACTIVATION_MAX_list[peidx]
  del IN_OFFSET_list[peidx]
  del WT_OFFSET_list[peidx]
  del OUT_OFFSET_list[peidx]
  del OUT_MULTIPLIER_OFFSET_list[peidx]
  del OUT_SHIFT_OFFSET_list[peidx]
  del BATCH_list[peidx]
  del CONV_IN_CH_list[peidx]
  del CONV_IN_DIM_H_list[peidx]
  del CONV_IN_DIM_W_list[peidx]
  del CONV_OUT_CH_list[peidx]
  del CONV_OUT_DIM_H_list[peidx]
  del CONV_OUT_DIM_W_list[peidx]
  del CONV_KER_CH_list[peidx]
  del CONV_KER_DIM_H_list[peidx]
  del CONV_KER_DIM_W_list[peidx]

  del POOL_EN_list[peidx-1]
  del POOL_MODE_list[peidx-1]
  del POOL_IN_CH_list[peidx-1]
  del POOL_IN_DIM_H_list[peidx-1]
  del POOL_IN_DIM_W_list[peidx-1]
  del POOL_OUT_DIM_H_list[peidx-1]
  del POOL_OUT_DIM_W_list[peidx-1]
  del POOL_OUT_CH_list[peidx-1]
  del POOL_KER_DIM_H_list[peidx-1]
  del POOL_KER_DIM_W_list[peidx-1]
  del POOL_PADDING_H_list[peidx-1]
  del POOL_PADDING_W_list[peidx-1]
  del POOL_STRIDE_H_list[peidx-1]
  del POOL_STRIDE_W_list[peidx-1]
  
  '''output parameters'''
  # output parameters to header file.
  wr_str = '\n//GowinSemiconductor Technology Co.,Ltd GoAI:Car Detection Demo!\n'
  cp_fp.write(wr_str)
  wr_str = '//Auto Generate Tflite Model Car Detection Parameters Header File!\n'
  cp_fp.write(wr_str)
  wr_str = '\n#ifndef TFLITE_CAR_DETECTION_PARAMETERS_H_\n'
  cp_fp.write(wr_str)
  wr_str = '#define TFLITE_CAR_DETECTION_PARAMETERS_H_\n'
  cp_fp.write(wr_str)
  wr_str = '\n/* Includes ------------------------------------------------*/\n'
  cp_fp.write(wr_str)
  wr_str = '#include <stdint.h>\n'
  cp_fp.write(wr_str)
  wr_str = '\n/* Parameters ------------------------------------------------*/\n'
  cp_fp.write(wr_str)
  wr_str = '//DepthwiseConv2D/Conv2D/AreragePool2D Layers\n'
  cp_fp.write(wr_str)
  wr_str = 'const int STAGES = '+str(len(DEPTHWISE_list))+';\n\n'
  cp_fp.write(wr_str)
  wr_str = 'const uint8_t DEPTHWISE [STAGES] = {'+str(','.join(str(x) for x in DEPTHWISE_list))+'};\n'
  cp_fp.write(wr_str)
  wr_str = 'const uint16_t DILATION_FACTOR_HEIGHT [STAGES] = {'+str(','.join(str(x) for x in DILATION_FACTOR_H_list))+'};\n'
  cp_fp.write(wr_str)
  wr_str = 'const uint16_t DILATION_FACTOR_WIDTH [STAGES] = {'+str(','.join(str(x) for x in DILATION_FACTOR_W_list))+'};\n'
  cp_fp.write(wr_str)
  wr_str = 'const uint16_t DEPTH_MULTIPLIER [STAGES] = {'+str(','.join(str(x) for x in DEPTH_MULTIPLIER_list))+'};\n'
  cp_fp.write(wr_str)
  wr_str = 'const int32_t OUT_ACTIVATION_MIN [STAGES] = {'+str(','.join(str(x) for x in OUT_ACTIVATION_MIN_list))+'};\n'
  cp_fp.write(wr_str)
  wr_str = 'const int32_t OUT_ACTIVATION_MAX [STAGES] = {'+str(','.join(str(x) for x in OUT_ACTIVATION_MAX_list))+'};\n'
  cp_fp.write(wr_str)
  wr_str = 'const int32_t IN_OFFSET [STAGES] = {'+str(','.join(str(x) for x in IN_OFFSET_list))+'};\n'
  cp_fp.write(wr_str)
  wr_str = 'const int32_t WT_OFFSET [STAGES] = {'+str(','.join(str(x) for x in WT_OFFSET_list))+'};\n'
  cp_fp.write(wr_str)
  wr_str = 'const int32_t OUT_OFFSET [STAGES] = {'+str(','.join(str(x) for x in OUT_OFFSET_list))+'};\n'
  cp_fp.write(wr_str)
  wr_str = 'const int32_t OUT_MULTIPLIER_OFFSET [STAGES] = {'+str(','.join(str(x) for x in OUT_MULTIPLIER_OFFSET_list))+'};\n'
  cp_fp.write(wr_str)
  wr_str = 'const int32_t OUT_SHIFT_OFFSET [STAGES] = {'+str(','.join(str(x) for x in OUT_SHIFT_OFFSET_list))+'};\n'
  cp_fp.write(wr_str)
  wr_str = 'const uint16_t BATCH [STAGES] = {'+str(','.join(str(x) for x in BATCH_list))+'};\n'
  cp_fp.write(wr_str)
  wr_str = 'const uint16_t CONV_PADDING_HEIGHT [STAGES] = {'+str(','.join(str(x) for x in CONV_PADDING_H_list))+'};\n'
  cp_fp.write(wr_str)
  wr_str = 'const uint16_t CONV_PADDING_WIDTH [STAGES] = {'+str(','.join(str(x) for x in CONV_PADDING_W_list))+'};\n'
  cp_fp.write(wr_str)
  wr_str = 'const uint16_t CONV_STRIDE_HEIGHT [STAGES] = {'+str(','.join(str(x) for x in CONV_STRIDE_H_list))+'};\n'
  cp_fp.write(wr_str)
  wr_str = 'const uint16_t CONV_STRIDE_WIDTH [STAGES] = {'+str(','.join(str(x) for x in CONV_STRIDE_W_list))+'};\n'
  cp_fp.write(wr_str)
  wr_str = 'const uint16_t CONV_IN_CH [STAGES] = {'+str(','.join(str(x) for x in CONV_IN_CH_list))+'};\n'
  cp_fp.write(wr_str)
  wr_str = 'const uint16_t CONV_IN_DIM_HEIGHT [STAGES] = {'+str(','.join(str(x) for x in CONV_IN_DIM_H_list))+'};\n'
  cp_fp.write(wr_str)
  wr_str = 'const uint16_t CONV_IN_DIM_WIDTH [STAGES] = {'+str(','.join(str(x) for x in CONV_IN_DIM_W_list))+'};\n'
  cp_fp.write(wr_str)
  wr_str = 'const uint16_t CONV_OUT_CH [STAGES] = {'+str(','.join(str(x) for x in CONV_OUT_CH_list))+'};\n'
  cp_fp.write(wr_str)
  wr_str = 'const uint16_t CONV_OUT_DIM_HEIGHT [STAGES] = {'+str(','.join(str(x) for x in CONV_OUT_DIM_H_list))+'};\n'
  cp_fp.write(wr_str)
  wr_str = 'const uint16_t CONV_OUT_DIM_WIDTH [STAGES] = {'+str(','.join(str(x) for x in CONV_OUT_DIM_W_list))+'};\n'
  cp_fp.write(wr_str)
  wr_str = 'const uint16_t CONV_KER_CH [STAGES] = {'+str(','.join(str(x) for x in CONV_KER_CH_list))+'};\n'
  cp_fp.write(wr_str)
  wr_str = 'const uint16_t CONV_KER_DIM_HEIGHT [STAGES] = {'+str(','.join(str(x) for x in CONV_KER_DIM_H_list))+'};\n'
  cp_fp.write(wr_str)
  wr_str = 'const uint16_t CONV_KER_DIM_WIDTH [STAGES] = {'+str(','.join(str(x) for x in CONV_KER_DIM_W_list))+'};\n'
  cp_fp.write(wr_str)
  wr_str = 'const uint8_t POOL_EN [STAGES] = {'+str(','.join(str(x) for x in POOL_EN_list))+'};\n'
  cp_fp.write(wr_str)
  wr_str = 'const uint8_t POOL_MODE [STAGES] = {'+str(','.join(str(x) for x in POOL_MODE_list))+'};\n'      #TODO - POOL MODE `1` for AVG
  cp_fp.write(wr_str)
  wr_str = 'const uint16_t POOL_IN_CH [STAGES] = {'+str(','.join(str(x) for x in POOL_IN_CH_list))+'};\n'
  cp_fp.write(wr_str)
  wr_str = 'const uint16_t POOL_IN_DIM_HEIGHT [STAGES] = {'+str(','.join(str(x) for x in POOL_IN_DIM_H_list))+'};\n'
  cp_fp.write(wr_str)
  wr_str = 'const uint16_t POOL_IN_DIM_WIDTH [STAGES] = {'+str(','.join(str(x) for x in POOL_IN_DIM_W_list))+'};\n'
  cp_fp.write(wr_str)
  wr_str = 'const uint16_t POOL_OUT_CH [STAGES] = {'+str(','.join(str(x) for x in POOL_OUT_CH_list))+'};\n'
  cp_fp.write(wr_str)
  wr_str = 'const uint16_t POOL_OUT_DIM_HEIGHT [STAGES] = {'+str(','.join(str(x) for x in POOL_OUT_DIM_H_list))+'};\n'
  cp_fp.write(wr_str)
  wr_str = 'const uint16_t POOL_OUT_DIM_WIDTH [STAGES] = {'+str(','.join(str(x) for x in POOL_OUT_DIM_W_list))+'};\n'
  cp_fp.write(wr_str)
  wr_str = 'const uint16_t POOL_KER_DIM_HEIGHT [STAGES] = {'+str(','.join(str(x) for x in POOL_KER_DIM_H_list))+'};\n'
  cp_fp.write(wr_str)
  wr_str = 'const uint16_t POOL_KER_DIM_WIDTH [STAGES] = {'+str(','.join(str(x) for x in POOL_KER_DIM_W_list))+'};\n'
  cp_fp.write(wr_str)
  wr_str = 'const uint16_t POOL_PADDING_HEIGHT [STAGES] = {'+str(','.join(str(x) for x in POOL_PADDING_H_list))+'};\n'
  cp_fp.write(wr_str)
  wr_str = 'const uint16_t POOL_PADDING_WIDTH [STAGES] = {'+str(','.join(str(x) for x in POOL_PADDING_W_list))+'};\n'
  cp_fp.write(wr_str)
  wr_str = 'const uint16_t POOL_STRIDE_HEIGHT [STAGES] = {'+str(','.join(str(x) for x in POOL_STRIDE_H_list))+'};\n'
  cp_fp.write(wr_str)
  wr_str = 'const uint16_t POOL_STRIDE_WIDTH [STAGES] = {'+str(','.join(str(x) for x in POOL_STRIDE_W_list))+'};\n'
  cp_fp.write(wr_str)
  wr_str = '\n#endif        /* TFLITE_CAR_DETECTION_PARAMETERS_H_ */\n'
  cp_fp.write(wr_str)
  
  cp_fp.close()
  wb_fp.close()
  
  os.remove('../data/work/car_detection.json')
  os.rmdir('../data/work')


'''Generate keras model parameters header file and bin file'''
def gen_keras_model_params_file():
  with open('../data/work/car_detection.json', 'r') as fp:
    jsonObj = json.load(fp)             # Load JSON objects.

  # First Level Useful Keys for TFLite Flatbuffers JSON
  OP_CODES  = 'operator_codes'          # key 'operator_codes'
  SUBGRAPHS = 'subgraphs'               # key 'subgraphs'
  BUFFERS   = 'buffers'                 # key 'buffers'
  
  # parameters in DepthwiseConv2D/Conv2D/AreragePooling2D
  DEPTHWISE_list = []                   # Flag of DepthwiseConv2D layer. 1 is DepthwiseConv2D; 0 is not DepthwiseConv2D.
  CONV_PADDING_H_list = []              # DepthwiseConv2D/Conv2D padding height.
  CONV_PADDING_W_list = []              # DepthwiseConv2D/Conv2D padding width.
  CONV_STRIDE_H_list = []               # DepthwiseConv2D/Conv2D stride height.
  CONV_STRIDE_W_list = []               # DepthwiseConv2D/Conv2D stride width.
  DILATION_FACTOR_H_list = []           # DepthwiseConv2D/Conv2D dilations height.
  DILATION_FACTOR_W_list = []           # DepthwiseConv2D/Conv2D dilations width.
  DEPTH_MULTIPLIER_list = []            # DepthwiseConv2D depth multiplier in DepthwiseConv2D layer
  OUT_ACTIVATION_MIN_list = []          # This is hard coded -128 for int8 type tensors
  OUT_ACTIVATION_MAX_list = []          # This is hard coded 127 for int8 type tensors
  IN_OFFSET_list = []                   # Input offset. Input tensor's zero_point.
  WT_OFFSET_list = []                   # Weight offset. Weight tensor's zero_point.
  OUT_OFFSET_list = []                  # Output offset. Output tensor's zero_point.
  OUT_MULTIPLIER_OFFSET_list = []       # Output multiplier offset.
  OUT_SHIFT_OFFSET_list = []            # Output shift offset.
  BATCH_list = []                       # Data batches input into convolution.
  CONV_IN_CH_list = []                  # DepthwiseConv2D/Conv2D input tensor's channels.
  CONV_IN_DIM_H_list = []               # DepthwiseConv2D/Conv2D input tensor's dimension height.
  CONV_IN_DIM_W_list = []               # DepthwiseConv2D/Conv2D input tensor's dimension width.
  CONV_OUT_CH_list = []                 # DepthwiseConv2D/Conv2D output tensor's channels.
  CONV_OUT_DIM_H_list = []              # DepthwiseConv2D/Conv2D output dimension height.
  CONV_OUT_DIM_W_list = []              # DepthwiseConv2D/Conv2D output dimension width.
  CONV_KER_CH_list = []                 # DepthwiseConv2D/Conv2D filter/kernel/weight tensor's channels.
  CONV_KER_DIM_H_list = []              # DepthwiseConv2D/Conv2D filter/kernel/weight tensor's dimension height.
  CONV_KER_DIM_W_list = []              # DepthwiseConv2D/Conv2D filter/kernel/weight tensor's dimension height.
  POOL_EN_list = []                     # Flag of AveragePool2D layer. 1 is AveragePool2D; 0 is not AveragePool2D.
  POOL_MODE_list = []                   # Mode of AveragePool2D layer. 1 is AveragePool2D; 0 is not AveragePool2D.
  POOL_IN_CH_list = []                  # AveragePool2D input tensor's channels.
  POOL_IN_DIM_H_list = []               # AveragePool2D input tensor's dimension height.
  POOL_IN_DIM_W_list = []               # AveragePool2D input tensor's dimension width.
  POOL_OUT_CH_list = []                 # AveragePool2D output tensor's channels.
  POOL_OUT_DIM_H_list = []              # AveragePool2D output tensor's dimension height.
  POOL_OUT_DIM_W_list = []              # AveragePool2D output tensor's dimension width.
  POOL_KER_DIM_H_list = []              # AveragePool2D filter/kernel/weight tensor's dimension height.
  POOL_KER_DIM_W_list = []              # AveragePool2D filter/kernel/weight tensor's dimension width.
  POOL_PADDING_H_list = []              # AveragePool2D padding height.
  POOL_PADDING_W_list = []              # AveragePool2D padding width.
  POOL_STRIDE_H_list = []               # AveragePool2D stride height.
  POOL_STRIDE_W_list = []               # AveragePool2D stride width.
  
  # car_detection parameters file and weight/bias binary file.
  # if 'output' is not exist, will build a new 'output'.
  if(os.path.exists('../data/output')==False):
    os.mkdir('../data/output')
  wb_fp = open('../data/output/car_detection_wb.bin', 'wb')
  cp_fp = open('../data/empu_m1/go_ai/tflite_car_detection_parameters.h', 'w')
  
  # parse car_detection JSON file and provision parameters/weights/bias
  # opcode_index : 
  #                1    = Conv2D;
  #                2    = AveragePool2D;
  #                3    = Reshape;
  #                4    = Softmax;
  #                none = DepthwiseConv2D.
  for sgidx in jsonObj[SUBGRAPHS]:
    for opidx in sgidx['operators']:
      if (opidx.get('opcode_index', 0) == 1):
        # -------------------------------------- Conv2D ------------------------------ #
        ''' variables '''
        input_tensor = sgidx['tensors'][opidx['inputs'][0]]
        filter_tensor = sgidx['tensors'][opidx['inputs'][1]]
        bias_tensor = sgidx['tensors'][opidx['inputs'][2]]
        output_tensor = sgidx['tensors'][opidx['outputs'][0]]
        
        filter_scale_list = []
        multiplier_list = []                                                       # 32-bit output_multiplier
        shift_list = []                                                            # 32-bit output_shift
        multiplier_buf = []                                                        # 8-bit output_multiplier
        shift_buf = []                                                             # 8-bit output_shift
        
        ''' calculate '''
        # padding height/width
        # shape[1] = height
        # shape[2] = width
        # padding height
        padding_h = int((input_tensor['shape'][1] + opidx['builtin_options']['stride_h'] - 1)/opidx['builtin_options']['stride_h'])
        padding_h = int((padding_h - 1) * opidx['builtin_options']['stride_h'] + filter_tensor['shape'][1] - input_tensor['shape'][1])
        if (padding_h > 0):
          padding_h = padding_h
        else:
          padding_h = 0
        # padding width
        padding_w = int((input_tensor['shape'][2] + opidx['builtin_options']['stride_w'] - 1)/opidx['builtin_options']['stride_w'])
        padding_w = int((padding_w - 1) * opidx['builtin_options']['stride_w'] + filter_tensor['shape'][2] - input_tensor['shape'][2])
        if (padding_w > 0):
          padding_w = padding_w
        else:
          padding_w = 0
        # input/filter/output scale
        input_scale = input_tensor['quantization']['scale'][0]                      # input tensor's scale
        for filter_scale in filter_tensor['quantization']['scale']:                 # filter tensor's scale
          filter_scale_list.append(filter_scale)
        output_scale = output_tensor['quantization']['scale'][0]                    # output tensor's scale
        for filter_scale in filter_scale_list:
          multiplier, shift = math.frexp((input_scale*filter_scale)/output_scale)
          multiplier_int = int (multiplier * (1<<31))
          multiplier_list.append(multiplier_int)
          shift_list.append(shift)
        
        ''' parameters '''
        #conv2d parameters
        CONV_PADDING_H_list.append(int(padding_h/2))
        CONV_PADDING_W_list.append(int(padding_w/2))
        CONV_STRIDE_H_list.append(opidx['builtin_options']['stride_h'])
        CONV_STRIDE_W_list.append(opidx['builtin_options']['stride_w'])
        DILATION_FACTOR_H_list.append(1)
        DILATION_FACTOR_W_list.append(1)
        DEPTH_MULTIPLIER_list.append(1)
        OUT_ACTIVATION_MIN_list.append(-128)                                         # int8 -128
        OUT_ACTIVATION_MAX_list.append(127)                                          # int8 127
        IN_OFFSET_list.append(-input_tensor['quantization']['zero_point'][0])
        WT_OFFSET_list.append(-filter_tensor['quantization']['zero_point'][0])       # TODO : an array but all zero.
        OUT_OFFSET_list.append(output_tensor['quantization']['zero_point'][0])
        OUT_MULTIPLIER_OFFSET_list.append(len(multiplier_list) * 4)
        OUT_SHIFT_OFFSET_list.append(len(shift_list) * 4)
        BATCH_list.append(1)
        CONV_IN_DIM_H_list.append(input_tensor['shape'][1])
        CONV_IN_DIM_W_list.append(input_tensor['shape'][2])
        CONV_IN_CH_list.append(input_tensor['shape'][3])
        CONV_OUT_DIM_H_list.append(output_tensor['shape'][1])
        CONV_OUT_DIM_W_list.append(output_tensor['shape'][2])
        CONV_OUT_CH_list.append(output_tensor['shape'][3])
        CONV_KER_DIM_H_list.append(filter_tensor['shape'][1])
        CONV_KER_DIM_W_list.append(filter_tensor['shape'][2])
        CONV_KER_CH_list.append(filter_tensor['shape'][0])                          # Conv2D filter shape[0].
        # average_pool2d parameters
        POOL_EN_list.append(0)
        POOL_MODE_list.append(0)
        POOL_OUT_DIM_H_list.append(0)
        POOL_OUT_DIM_W_list.append(0)
        POOL_OUT_CH_list.append(0)
        POOL_IN_DIM_H_list.append(0)
        POOL_IN_DIM_W_list.append(0)
        POOL_IN_CH_list.append(0)
        POOL_KER_DIM_H_list.append(0)
        POOL_KER_DIM_W_list.append(0)
        POOL_PADDING_H_list.append(0)
        POOL_PADDING_W_list.append(0)
        POOL_STRIDE_H_list.append(0)
        POOL_STRIDE_W_list.append(0)
        # depthwise_conv2d flag
        DEPTHWISE_list.append(0)
        # output_multiplier/output_shift
        for mulitiplier in multiplier_list:                                           # write to binary as 8-bits
          multiplier_buf.append(mulitiplier&0x000000ff)
          multiplier_buf.append((mulitiplier>>8)&0x000000ff)
          multiplier_buf.append((mulitiplier>>16)&0x000000ff)
          multiplier_buf.append((mulitiplier>>24)&0x000000ff)
        for shift in shift_list:
          shift_buf.append(shift&0x000000ff)
          shift_buf.append((shift>>8)&0x000000ff)
          shift_buf.append((shift>>16)&0x000000ff)
          shift_buf.append((shift>>24)&0x000000ff)
        # weight/bias
        weight_buf = jsonObj[BUFFERS][filter_tensor['buffer']]['data']                # weight
        bias_buf = jsonObj[BUFFERS][bias_tensor['buffer']]['data']                    # bias
        #
        w_batch = sgidx['tensors'][opidx['inputs'][1]]['shape'][0]
        w_kernel = sgidx['tensors'][opidx['inputs'][1]]['shape'][1] * sgidx['tensors'][opidx['inputs'][1]]['shape'][2]
        w_channel = sgidx['tensors'][opidx['inputs'][1]]['shape'][3]        
        #
        wb_rearrange_buf = []
        #
        for btidx in range (w_batch):
          for mlidx in range (4):
            wb_rearrange_buf.append(multiplier_buf[(btidx * 4) + mlidx])

          for shidx in range (4):
            wb_rearrange_buf.append(shift_buf[(btidx * 4) + shidx])            
        
          for bsidx in range (4):
            wb_rearrange_buf.append(bias_buf[(btidx * 4) + bsidx])          

          for kridx in range (w_kernel):
            for chidx in range (w_channel):
              wb_rearrange_buf.append(weight_buf[(btidx*w_kernel*w_channel) + (kridx*w_channel) + chidx])
        #
        wb_fp.write(bytearray(wb_rearrange_buf))
        
      elif (opidx.get('opcode_index', 0) == 2):
        # ------------------------------------------ AveragePool2D-------------------------------- #
        ''' variables '''
        input_tensor = sgidx['tensors'][opidx['inputs'][0]]
        output_tensor = sgidx['tensors'][opidx['outputs'][0]]
        
        ''' calculate '''
        # padding height/width
        # shape[1] = height
        # shape[2] = width
        # padding height
        padding_h = int((input_tensor['shape'][1] + opidx['builtin_options']['stride_h'] - opidx['builtin_options']['filter_height'])/opidx['builtin_options']['stride_h'])
        padding_h = int((padding_h - 1) * opidx['builtin_options']['stride_h'] + opidx['builtin_options']['filter_height'] - input_tensor['shape'][1])
        if (padding_h > 0):
          padding_h = padding_h
        else:
          padding_h = 0
        # padding width
        padding_w = int((input_tensor['shape'][2] + opidx['builtin_options']['stride_w'] - opidx['builtin_options']['filter_width'])/opidx['builtin_options']['stride_w'])
        padding_w = int((padding_w - 1) * opidx['builtin_options']['stride_w'] + opidx['builtin_options']['filter_width'] - input_tensor['shape'][2])
        if (padding_w > 0):
          padding_w = padding_w
        else:
          padding_w = 0
        ''' parameters '''
        # average_pool2d parameters
        POOL_EN_list.append(1)
        POOL_MODE_list.append(1)
        POOL_IN_DIM_H_list.append(input_tensor['shape'][1])
        POOL_IN_DIM_W_list.append(input_tensor['shape'][2])
        POOL_IN_CH_list.append(input_tensor['shape'][3])
        POOL_OUT_DIM_H_list.append(output_tensor['shape'][1])
        POOL_OUT_DIM_W_list.append(output_tensor['shape'][2])
        POOL_OUT_CH_list.append(output_tensor['shape'][3])
        POOL_KER_DIM_H_list.append(opidx['builtin_options']['filter_height'])
        POOL_KER_DIM_W_list.append(opidx['builtin_options']['filter_width'])
        POOL_PADDING_H_list.append(int(padding_h/2))
        POOL_PADDING_W_list.append(int(padding_w/2))
        POOL_STRIDE_H_list.append(opidx['builtin_options']['stride_h'])
        POOL_STRIDE_W_list.append(opidx['builtin_options']['stride_w'])
        #depthwise_conv2d/conv2d parameters
        DEPTHWISE_list.append(0)
        CONV_PADDING_H_list.append(0)
        CONV_PADDING_W_list.append(0)
        CONV_STRIDE_H_list.append(0)
        CONV_STRIDE_W_list.append(0)
        DILATION_FACTOR_H_list.append(0)
        DILATION_FACTOR_W_list.append(0)
        DEPTH_MULTIPLIER_list.append(0)
        OUT_ACTIVATION_MIN_list.append(0)
        OUT_ACTIVATION_MAX_list.append(0)
        IN_OFFSET_list.append(0)
        WT_OFFSET_list.append(0)
        OUT_OFFSET_list.append(0)
        BATCH_list.append(1)
        OUT_SHIFT_OFFSET_list.append(0)
        OUT_MULTIPLIER_OFFSET_list.append(0)
        CONV_IN_CH_list.append(0)
        CONV_IN_DIM_H_list.append(0)
        CONV_IN_DIM_W_list.append(0)
        CONV_OUT_CH_list.append(0)
        CONV_OUT_DIM_H_list.append(0)
        CONV_OUT_DIM_W_list.append(0)
        CONV_KER_CH_list.append(0)
        CONV_KER_DIM_H_list.append(0)
        CONV_KER_DIM_W_list.append(0)
        
      elif (opidx.get('opcode_index', 0) == 3):
        # ----------------------------------------- Reshape ------------------------------------- #
        # TODO : 
        print('TODO : INGORE RESHAPE LAYER.')
        
      elif (opidx.get('opcode_index', 0) == 4):
        # ------------------------------------------ Softmax ------------------------------------ #
        # TODO :
        print('TODO : INGORE SOFTMAX LAYER.')
        
      else:
        # --------------------------------------- DepthwiseConv2D -------------------------------- #
        ''' variables '''
        input_tensor = sgidx['tensors'][opidx['inputs'][0]]
        filter_tensor = sgidx['tensors'][opidx['inputs'][1]]
        bias_tensor = sgidx['tensors'][opidx['inputs'][2]]
        output_tensor = sgidx['tensors'][opidx['outputs'][0]]
        
        filter_scale_list = []
        multiplier_list = []                                                       # 32-bit output_multiplier
        shift_list = []                                                            # 32-bit output_shift
        multiplier_buf = []                                                        # 8-bit output_multiplier
        shift_buf = []                                                             # 8-bit output_shift
        
        ''' calculate '''
        # padding height/width
        # shape[1] = height
        # shape[2] = width
        # padding height
        padding_h = int((input_tensor['shape'][1] + opidx['builtin_options']['stride_h'] - 1)/opidx['builtin_options']['stride_h'])
        padding_h = int((padding_h - 1) * opidx['builtin_options']['stride_h'] + filter_tensor['shape'][1] - input_tensor['shape'][1])
        if (padding_h > 0):
          padding_h = padding_h
        else:
          padding_h = 0
        # padding width
        padding_w = int((input_tensor['shape'][2] + opidx['builtin_options']['stride_w'] - 1)/opidx['builtin_options']['stride_w'])
        padding_w = int((padding_w - 1) * opidx['builtin_options']['stride_w'] + filter_tensor['shape'][2] - input_tensor['shape'][2])
        if (padding_w > 0):
          padding_w = padding_w
        else:
          padding_w = 0
        # input/filter/output scale
        input_scale = input_tensor['quantization']['scale'][0]                      # input tensor's scale
        for filter_scale in filter_tensor['quantization']['scale']:                 # filter tensor's scale
          filter_scale_list.append(filter_scale)
        output_scale = output_tensor['quantization']['scale'][0]                    # output tensor's scale
        for filter_scale in filter_scale_list:
          multiplier, shift = math.frexp((input_scale*filter_scale)/output_scale)
          multiplier_int = int (multiplier * (1<<31))
          multiplier_list.append(multiplier_int)
          shift_list.append(shift)
        
        ''' parameters '''
        #depthwise_conv2d parameters
        DEPTHWISE_list.append(1)                                                     #1 : DepthwiseConv2D.
        CONV_PADDING_H_list.append(int(padding_h/2))
        CONV_PADDING_W_list.append(int(padding_w/2))
        CONV_STRIDE_H_list.append(opidx['builtin_options']['stride_h'])
        CONV_STRIDE_W_list.append(opidx['builtin_options']['stride_w'])
        DILATION_FACTOR_H_list.append(1)
        DILATION_FACTOR_W_list.append(1)
        DEPTH_MULTIPLIER_list.append(opidx['builtin_options']['depth_multiplier'])
        OUT_ACTIVATION_MIN_list.append(-128)                                         # int8 -128
        OUT_ACTIVATION_MAX_list.append(127)                                          # int8 127
        IN_OFFSET_list.append(-input_tensor['quantization']['zero_point'][0])
        WT_OFFSET_list.append(-filter_tensor['quantization']['zero_point'][0])       # TODO : an array but all zero.
        OUT_OFFSET_list.append(output_tensor['quantization']['zero_point'][0])
        OUT_MULTIPLIER_OFFSET_list.append(len(multiplier_list) * 4)
        OUT_SHIFT_OFFSET_list.append(len(shift_list) * 4)
        BATCH_list.append(1)
        CONV_IN_DIM_H_list.append(input_tensor['shape'][1])
        CONV_IN_DIM_W_list.append(input_tensor['shape'][2])
        CONV_IN_CH_list.append(input_tensor['shape'][3])
        CONV_OUT_DIM_H_list.append(output_tensor['shape'][1])
        CONV_OUT_DIM_W_list.append(output_tensor['shape'][2])
        CONV_OUT_CH_list.append(output_tensor['shape'][3])
        CONV_KER_DIM_H_list.append(filter_tensor['shape'][1])
        CONV_KER_DIM_W_list.append(filter_tensor['shape'][2])
        CONV_KER_CH_list.append(filter_tensor['shape'][3])
        # average_pool2d parameters
        POOL_EN_list.append(0)
        POOL_MODE_list.append(0)
        POOL_OUT_DIM_H_list.append(0)
        POOL_OUT_DIM_W_list.append(0)
        POOL_OUT_CH_list.append(0)
        POOL_IN_DIM_H_list.append(0)
        POOL_IN_DIM_W_list.append(0)
        POOL_IN_CH_list.append(0)
        POOL_KER_DIM_H_list.append(0)
        POOL_KER_DIM_W_list.append(0)
        POOL_PADDING_H_list.append(0)
        POOL_PADDING_W_list.append(0)
        POOL_STRIDE_H_list.append(0)
        POOL_STRIDE_W_list.append(0)
        # output_multiplier/output_shift
        for mulitiplier in multiplier_list:                                           # write to binary as 8-bits
          multiplier_buf.append(mulitiplier&0x000000ff)
          multiplier_buf.append((mulitiplier>>8)&0x000000ff)
          multiplier_buf.append((mulitiplier>>16)&0x000000ff)
          multiplier_buf.append((mulitiplier>>24)&0x000000ff)
        for shift in shift_list:
          shift_buf.append(shift&0x000000ff)
          shift_buf.append((shift>>8)&0x000000ff)
          shift_buf.append((shift>>16)&0x000000ff)
          shift_buf.append((shift>>24)&0x000000ff)
        # weight/bias
        weight_buf = jsonObj[BUFFERS][filter_tensor['buffer']]['data']                # weight
        bias_buf = jsonObj[BUFFERS][bias_tensor['buffer']]['data']                    # bias
        #
        w_batch = sgidx['tensors'][opidx['inputs'][1]]['shape'][0]
        w_kernel  = sgidx['tensors'][opidx['inputs'][1]]['shape'][1] * sgidx['tensors'][opidx['inputs'][1]]['shape'][2]
        w_channel = sgidx['tensors'][opidx['inputs'][1]]['shape'][3]        
        #
        wb_rearrange_buf = []
        #
        for btidx in range (w_batch):
          for chidx in range (w_channel):
            for mlidx in range (4):
              wb_rearrange_buf.append(multiplier_buf[(chidx * 4) + mlidx])

            for shidx in range (4):
              wb_rearrange_buf.append(shift_buf[(chidx * 4) + shidx])        
          
            for bsidx in range (4):
              wb_rearrange_buf.append(bias_buf[(chidx * 4) + bsidx])          

            for kridx in range (w_kernel):            
              wb_rearrange_buf.append(weight_buf[(btidx*w_kernel*w_channel) + (kridx*w_channel) + chidx])
        #
        wb_fp.write(bytearray(wb_rearrange_buf))
        
  
  # Optimize AveragePool2D layer out, delete AveragePool2D parameters.
  peidx = POOL_EN_list.index(1)
  del DEPTHWISE_list[peidx]
  del CONV_PADDING_H_list[peidx]
  del CONV_PADDING_W_list[peidx]
  del CONV_STRIDE_H_list[peidx]
  del CONV_STRIDE_W_list[peidx]
  del DILATION_FACTOR_H_list[peidx]
  del DILATION_FACTOR_W_list[peidx]
  del DEPTH_MULTIPLIER_list[peidx]
  del OUT_ACTIVATION_MIN_list[peidx]
  del OUT_ACTIVATION_MAX_list[peidx]
  del IN_OFFSET_list[peidx]
  del WT_OFFSET_list[peidx]
  del OUT_OFFSET_list[peidx]
  del OUT_MULTIPLIER_OFFSET_list[peidx]
  del OUT_SHIFT_OFFSET_list[peidx]
  del BATCH_list[peidx]
  del CONV_IN_CH_list[peidx]
  del CONV_IN_DIM_H_list[peidx]
  del CONV_IN_DIM_W_list[peidx]
  del CONV_OUT_CH_list[peidx]
  del CONV_OUT_DIM_H_list[peidx]
  del CONV_OUT_DIM_W_list[peidx]
  del CONV_KER_CH_list[peidx]
  del CONV_KER_DIM_H_list[peidx]
  del CONV_KER_DIM_W_list[peidx]

  del POOL_EN_list[peidx-1]
  del POOL_MODE_list[peidx-1]
  del POOL_IN_CH_list[peidx-1]
  del POOL_IN_DIM_H_list[peidx-1]
  del POOL_IN_DIM_W_list[peidx-1]
  del POOL_OUT_DIM_H_list[peidx-1]
  del POOL_OUT_DIM_W_list[peidx-1]
  del POOL_OUT_CH_list[peidx-1]
  del POOL_KER_DIM_H_list[peidx-1]
  del POOL_KER_DIM_W_list[peidx-1]
  del POOL_PADDING_H_list[peidx-1]
  del POOL_PADDING_W_list[peidx-1]
  del POOL_STRIDE_H_list[peidx-1]
  del POOL_STRIDE_W_list[peidx-1]
  
  '''output parameters'''
  # output parameters to header file.
  wr_str = '\n//GowinSemiconductor Technology Co.,Ltd GoAI:Car Detection Demo!\n'
  cp_fp.write(wr_str)
  wr_str = '//Auto Generate Tflite Model Car Detection Parameters Header File!\n'
  cp_fp.write(wr_str)
  wr_str = '\n#ifndef TFLITE_CAR_DETECTION_PARAMETERS_H_\n'
  cp_fp.write(wr_str)
  wr_str = '#define TFLITE_CAR_DETECTION_PARAMETERS_H_\n'
  cp_fp.write(wr_str)
  wr_str = '\n/* Includes ------------------------------------------------*/\n'
  cp_fp.write(wr_str)
  wr_str = '#include <stdint.h>\n'
  cp_fp.write(wr_str)
  wr_str = '\n/* Parameters ------------------------------------------------*/\n'
  cp_fp.write(wr_str)
  wr_str = '//DepthwiseConv2D/Conv2D/AreragePool2D Layers\n'
  cp_fp.write(wr_str)
  wr_str = 'const int STAGES = '+str(len(DEPTHWISE_list))+';\n\n'
  cp_fp.write(wr_str)
  wr_str = 'const uint8_t DEPTHWISE [STAGES] = {'+str(','.join(str(x) for x in DEPTHWISE_list))+'};\n'
  cp_fp.write(wr_str)
  wr_str = 'const uint16_t DILATION_FACTOR_HEIGHT [STAGES] = {'+str(','.join(str(x) for x in DILATION_FACTOR_H_list))+'};\n'
  cp_fp.write(wr_str)
  wr_str = 'const uint16_t DILATION_FACTOR_WIDTH [STAGES] = {'+str(','.join(str(x) for x in DILATION_FACTOR_W_list))+'};\n'
  cp_fp.write(wr_str)
  wr_str = 'const uint16_t DEPTH_MULTIPLIER [STAGES] = {'+str(','.join(str(x) for x in DEPTH_MULTIPLIER_list))+'};\n'
  cp_fp.write(wr_str)
  wr_str = 'const int32_t OUT_ACTIVATION_MIN [STAGES] = {'+str(','.join(str(x) for x in OUT_ACTIVATION_MIN_list))+'};\n'
  cp_fp.write(wr_str)
  wr_str = 'const int32_t OUT_ACTIVATION_MAX [STAGES] = {'+str(','.join(str(x) for x in OUT_ACTIVATION_MAX_list))+'};\n'
  cp_fp.write(wr_str)
  wr_str = 'const int32_t IN_OFFSET [STAGES] = {'+str(','.join(str(x) for x in IN_OFFSET_list))+'};\n'
  cp_fp.write(wr_str)
  wr_str = 'const int32_t WT_OFFSET [STAGES] = {'+str(','.join(str(x) for x in WT_OFFSET_list))+'};\n'
  cp_fp.write(wr_str)
  wr_str = 'const int32_t OUT_OFFSET [STAGES] = {'+str(','.join(str(x) for x in OUT_OFFSET_list))+'};\n'
  cp_fp.write(wr_str)
  wr_str = 'const int32_t OUT_MULTIPLIER_OFFSET [STAGES] = {'+str(','.join(str(x) for x in OUT_MULTIPLIER_OFFSET_list))+'};\n'
  cp_fp.write(wr_str)
  wr_str = 'const int32_t OUT_SHIFT_OFFSET [STAGES] = {'+str(','.join(str(x) for x in OUT_SHIFT_OFFSET_list))+'};\n'
  cp_fp.write(wr_str)
  wr_str = 'const uint16_t BATCH [STAGES] = {'+str(','.join(str(x) for x in BATCH_list))+'};\n'
  cp_fp.write(wr_str)
  wr_str = 'const uint16_t CONV_PADDING_HEIGHT [STAGES] = {'+str(','.join(str(x) for x in CONV_PADDING_H_list))+'};\n'
  cp_fp.write(wr_str)
  wr_str = 'const uint16_t CONV_PADDING_WIDTH [STAGES] = {'+str(','.join(str(x) for x in CONV_PADDING_W_list))+'};\n'
  cp_fp.write(wr_str)
  wr_str = 'const uint16_t CONV_STRIDE_HEIGHT [STAGES] = {'+str(','.join(str(x) for x in CONV_STRIDE_H_list))+'};\n'
  cp_fp.write(wr_str)
  wr_str = 'const uint16_t CONV_STRIDE_WIDTH [STAGES] = {'+str(','.join(str(x) for x in CONV_STRIDE_W_list))+'};\n'
  cp_fp.write(wr_str)
  wr_str = 'const uint16_t CONV_IN_CH [STAGES] = {'+str(','.join(str(x) for x in CONV_IN_CH_list))+'};\n'
  cp_fp.write(wr_str)
  wr_str = 'const uint16_t CONV_IN_DIM_HEIGHT [STAGES] = {'+str(','.join(str(x) for x in CONV_IN_DIM_H_list))+'};\n'
  cp_fp.write(wr_str)
  wr_str = 'const uint16_t CONV_IN_DIM_WIDTH [STAGES] = {'+str(','.join(str(x) for x in CONV_IN_DIM_W_list))+'};\n'
  cp_fp.write(wr_str)
  wr_str = 'const uint16_t CONV_OUT_CH [STAGES] = {'+str(','.join(str(x) for x in CONV_OUT_CH_list))+'};\n'
  cp_fp.write(wr_str)
  wr_str = 'const uint16_t CONV_OUT_DIM_HEIGHT [STAGES] = {'+str(','.join(str(x) for x in CONV_OUT_DIM_H_list))+'};\n'
  cp_fp.write(wr_str)
  wr_str = 'const uint16_t CONV_OUT_DIM_WIDTH [STAGES] = {'+str(','.join(str(x) for x in CONV_OUT_DIM_W_list))+'};\n'
  cp_fp.write(wr_str)
  wr_str = 'const uint16_t CONV_KER_CH [STAGES] = {'+str(','.join(str(x) for x in CONV_KER_CH_list))+'};\n'
  cp_fp.write(wr_str)
  wr_str = 'const uint16_t CONV_KER_DIM_HEIGHT [STAGES] = {'+str(','.join(str(x) for x in CONV_KER_DIM_H_list))+'};\n'
  cp_fp.write(wr_str)
  wr_str = 'const uint16_t CONV_KER_DIM_WIDTH [STAGES] = {'+str(','.join(str(x) for x in CONV_KER_DIM_W_list))+'};\n'
  cp_fp.write(wr_str)
  wr_str = 'const uint8_t POOL_EN [STAGES] = {'+str(','.join(str(x) for x in POOL_EN_list))+'};\n'
  cp_fp.write(wr_str)
  wr_str = 'const uint8_t POOL_MODE [STAGES] = {'+str(','.join(str(x) for x in POOL_MODE_list))+'};\n'      #TODO - POOL MODE `1` for AVG
  cp_fp.write(wr_str)
  wr_str = 'const uint16_t POOL_IN_CH [STAGES] = {'+str(','.join(str(x) for x in POOL_IN_CH_list))+'};\n'
  cp_fp.write(wr_str)
  wr_str = 'const uint16_t POOL_IN_DIM_HEIGHT [STAGES] = {'+str(','.join(str(x) for x in POOL_IN_DIM_H_list))+'};\n'
  cp_fp.write(wr_str)
  wr_str = 'const uint16_t POOL_IN_DIM_WIDTH [STAGES] = {'+str(','.join(str(x) for x in POOL_IN_DIM_W_list))+'};\n'
  cp_fp.write(wr_str)
  wr_str = 'const uint16_t POOL_OUT_CH [STAGES] = {'+str(','.join(str(x) for x in POOL_OUT_CH_list))+'};\n'
  cp_fp.write(wr_str)
  wr_str = 'const uint16_t POOL_OUT_DIM_HEIGHT [STAGES] = {'+str(','.join(str(x) for x in POOL_OUT_DIM_H_list))+'};\n'
  cp_fp.write(wr_str)
  wr_str = 'const uint16_t POOL_OUT_DIM_WIDTH [STAGES] = {'+str(','.join(str(x) for x in POOL_OUT_DIM_W_list))+'};\n'
  cp_fp.write(wr_str)
  wr_str = 'const uint16_t POOL_KER_DIM_HEIGHT [STAGES] = {'+str(','.join(str(x) for x in POOL_KER_DIM_H_list))+'};\n'
  cp_fp.write(wr_str)
  wr_str = 'const uint16_t POOL_KER_DIM_WIDTH [STAGES] = {'+str(','.join(str(x) for x in POOL_KER_DIM_W_list))+'};\n'
  cp_fp.write(wr_str)
  wr_str = 'const uint16_t POOL_PADDING_HEIGHT [STAGES] = {'+str(','.join(str(x) for x in POOL_PADDING_H_list))+'};\n'
  cp_fp.write(wr_str)
  wr_str = 'const uint16_t POOL_PADDING_WIDTH [STAGES] = {'+str(','.join(str(x) for x in POOL_PADDING_W_list))+'};\n'
  cp_fp.write(wr_str)
  wr_str = 'const uint16_t POOL_STRIDE_HEIGHT [STAGES] = {'+str(','.join(str(x) for x in POOL_STRIDE_H_list))+'};\n'
  cp_fp.write(wr_str)
  wr_str = 'const uint16_t POOL_STRIDE_WIDTH [STAGES] = {'+str(','.join(str(x) for x in POOL_STRIDE_W_list))+'};\n'
  cp_fp.write(wr_str)
  wr_str = '\n#endif        /* TFLITE_CAR_DETECTION_PARAMETERS_H_ */\n'
  cp_fp.write(wr_str)
  
  cp_fp.close()
  wb_fp.close()
  
  os.remove('../data/work/car_detection.json')
  os.rmdir('../data/work')