===============================================================================================================================================
                                       Copyright (C) 2014-2021 Gowin Semiconductor Technology Co.,Ltd
                                                           All Rights Reserved
===============================================================================================================================================
                                                          GoAI:micro_speech SDK
===============================================================================================================================================
VERSION
    GoAI2.0
===============================================================================================================================================
FUNCTION
1. Capture raw audio samples.
2. Convert raw audio samples to spectrogram.
3. Recognize 'yes', 'no', 'silence' and 'unknown' audio.
   led2 : silence
   led4 : unknown
   led3 : yes
   led6 : no
===============================================================================================================================================
HOW TO RUN
1. Open "micro_speech_sdk\bin\goai_run.bat";
2. Change parameters in "goai_run.bat" and store;
    1) --device                   : specify the device type (default is GW2A55C)
    2) --tflite_model_file        : specify the full path of micro_speech tflite model (For example, "micro_speech_sdk\data\tf_model\micro_speech.tflite")
    3) --programmer_cli_path      : specify the full path of Gowin Programmer (For example, "Gowin_V1.9.7.05Beta\Programmer\bin")
    4) --gmd_cli_path             : specify the full path of Gcc (For example, "C:\GMD\toolchain\ARM_toolchain\bin")
    5) --training_type            : specify the model training type (tf or keras)
3. Double click "goai_run.bat" and run micro_speech SDK.
===============================================================================================================================================
OPERATING SYSTEM
1. Windows 7/10.
2. MacOS.
3. Linux.
===============================================================================================================================================
DEVELOPMENT KITS
1. 1x DK-GoAI-GW2A55-PG484 V1.0
    GW2A-55C (version C)
    GW2A-LV55PG484C8/I7
2. 1x USB to UART
3. 1x USB wire
===============================================================================================================================================
SDK STRUCTURE
\micro_speech_sdk
    \bin                        --> Executable file
        \goai_run.bat           --> Run automatically
        \micro_speech.exe       --> Execute micro_speech SDK
    \data                       --> Input, output, model, empu_m1 and fpga design
        \empu_m1                --> M1 c-code design
            \empu_m1            --> M1 libaray
            \go_ai              --> GoAI library
        \fpga                   --> FPGA fs file and posp file
            \micro_speech.fs    --> FPGA fs file
            \micro_speech.posp  --> FPGA posp file
        \tf_model               --> Model tflite
        \output                 --> Weight/bias and bitstream
    \doc                        --> Documents
        \ReadMe.txt             --> Read me file
    \plugins                    --> Plugins
        \flatc                  --> Flatc tool
        \merge_bit              --> Merge bit tool
===============================================================================================================================================
MICRO_SPEECH SOFTWARE DESIGN
1. Memory settings
    1) Flash
        start             size
        0x0               0x20000 (128KB)
    2) Sram
        start             size
        0x20000000        0x10000 (64KB)
2. Compile tool : GMD V1.1
===============================================================================================================================================
MICRO_SPEECH HARDWARE DESIGN
1. Cortex-M1 Core
    1) Disable Debug
    2) Frequency is 48MHz
    3) Internal instruction memory is 128KB
    4) Internal data memory is 64KB
    5) Diable OS extension
2. Peripherals
    1) GPIO
    2) UART0
    3) AHB Master [1]
3. Synthesis tool : GowinSynthesis V1.9.7.05Beta
4. PnR tool : Gowin_V1.9.7.05Beta
===============================================================================================================================================
MODEL STRUCTURE
        Reshape_1
           | (1 x 1960)
        Reshape
           | (1 x 49 x 40 x 1)
     DepthwiseConv2D
           | (1 x 25 x 20 x 8)
      FullyConnected
           | (1 x 4)
        Softmax
           | (1 x 4)
      labels_softmax
===============================================================================================================================================
MODEL PARAMETERS
  DepthwiseConv2D parameters :
    DEPTHWISE             : DepthwiseConv2D layer's flag, 1 is DepthwiseConv2D layer, 0 is not DepthwiseConv2D layer.
    IN_OFFSET             : Input offset, "quantization"'s "zero_point" in each layer's input tensor.
    WT_OFFSET             : Weight offset, "quantization"'s "zero_point" in each layer's weight tensor, an array.
    OUT_OFFSET            : Output offset, "quantization"'s "zero_point" in each layer's output tensor.
    OUT_MULTIPLIER        : Mantissa of "quantization"'s "scale", an array.
    OUT_SHIFT             : Exponent of "quantization"'s "scale", an arry.
    OUT_ACTIVATION_MIN    : Size of weight's data type, e.g. int8_t is -128.
    OUT_ACTIVATION_MAX    : Size of weight's data type, e.g. int8_t is 127.
    BATCH                 : Data batches of input into model computing, e.g. if the input data is too more, need to divide data into several batches.
    DILATION_FACTOR_H     : Height of DepthwiseConv2D/Conv2D dilations.
    DILATION_FACTOR_W     : Width of DepthwiseConv2D/Conv2D dilations.
    CONV_PADDING_H        : Height of DepthwiseConv2D/Conv2D padding.
    CONV_PADDING_W        : Width of DepthwiseConv2D/Conv2D padding.
    CONV_STRIDE_H         : Height of DepthwiseConv2D/Conv2D stride length.
    CONV_STRIDE_W         : Width of DepthwiseConv2D/Conv2D stride length.
    CONV_IN_CH            : Input channels of DepthwiseConv2D/Conv2D.
    CONV_IN_DIM_H         : Height of DepthwiseConv2D/Conv2D input tensor.
    CONV_IN_DIM_W         : Width of DepthwiseConv2D/Conv2D input tensor.
    CONV_OUT_CH           : Output channels of DepthwiseConv2D/Conv2D.
    CONV_OUT_DIM_H        : Height of DepthwiseConv2D/Conv2D output tensor.
    CONV_OUT_DIM_W        : Width of DepthwiseConv2D/Conv2D output tensor.
    CONV_KER_CH           : Weight channels of DepthwiseConv2D/Conv2D.
    CONV_KER_DIM_H        : Height of DepthwiseConv2D/Conv2D weight tensor.
    CONV_KER_DIM_W        : Width of DepthwiseConv2D/Conv2D weight tensor.
    POOL_EN               : AveragePool2D layer's flag, 1 is AveragePool2D layer, 0 is not AveragePool2D layer.
    POOL_MODE             : AveragePool2D layer's mode, 1 is AveragePool2D layer, 0 is not AveragePool2D layer.
    POOL_OUT_DIM_H        : Height of AveragePool2D input tensor.
    POOL_OUT_DIM_W        : Width of AveragePool2D input tensor.
    POOL_OUT_CH           : Output channels of AveragePool2D.
    POOL_KER_DIM_H        : Height of AveragePool2D weight tensor.
    POOL_KER_DIM_W        : Width of AveragePool2D weight tensor.
    POOL_KER_CH           : Weight channels of AveragePool2D.
    POOL_PADDING_H        : Height of AveragePool2D padding.
    POOL_PADDING_W        : Width of AveragePool2D padding.
    POOL_STRIDE_H         : Height of AveragePool2D stride length.
    POOL_STRIDE_W         : Width of AveragePool2D stride length.
  FullyConnected parameters :
    INPUT_OFFSET             : Input offset, "quantization"'s "zero_point" in each layer's input tensor.
    FILTER_OFFSET            : Weight offset, "quantization"'s "zero_point" in each layer's weight tensor.
    OUTPUT_OFFSET            : Output offset, "quantization"'s "zero_point" in each layer's output tensor
    OUTPUT_MULITPLIER        : Mantissa of "quantization"'s "scale".
    OUTPUT_SHIFT             : Exponent of "quantization"'s "scale".
    OUTPUT_ACTIVATION_MIN    : Size of weight's data type, e.g. int8_t is -128.
    OUTPUT_ACTIVATION_MAX    : Size of weight's data type, e.g. int8_t is 127.
    FILTER_DIM_COUNT         : Dimension of weight's "shape".
    BATCHES                  : Data batches of input into model computing, e.g. if the input data is too more, need to divide data into several batches.
    OUTPUT_DEPTH             : Weight shape's 1st dimension.
    ACCUM_DEPTH              : Weight shape's 2nd dimension.
    FILTER_VAL               : Weight.
    BIAS_DATA                : Bias.
===============================================================================================================================================