===============================================================================================================================================
                                       Copyright (C) 2014-2020 Gowin Semiconductor Technology Co.,Ltd
                                                           All Rights Reserved
===============================================================================================================================================
                                                          GoAI:micro_speech SDK
===============================================================================================================================================
VERSION
    GoAI 2.0 micro_speech
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
    1) --device            : specify the device type (default is GW2A55C)
    2) --tflite_model_file : specify the full path of micro_speech tflite model (For example, "micro_speech_sdk\data\tf_model\micro_speech.tflite")
    3) --gowin_eda_path    : specify the full path of Gowin IDE (For example, "Gowin_V1.9.6.02Beta")
    4) --keil_path         : specify the full path of Keil IDE (For example, "ARM Keil MDK V5.24")
3. Double click "goai_run.bat" and run micro_speech SDK.
===============================================================================================================================================
OPERATING SYSTEM
1. Windows 7/10.
===============================================================================================================================================
DEVELOPMENT KITS
1. DK-GoAI-Embedded-GW2A55-PG484
    GW2A-55C
    GW2A-LV55PG484C8/I7
2. USB to Serial mini board
3. USB wire
4. Power adapter
===============================================================================================================================================
INTEGRATED DEVELOPMENT ENVIRONMENT
1. RTL-code design : Gowin_V1.9.6.02 Beta and higher.
2. Synthesis tool  : GowinSynthesis V1.9.6.02 Beta and higher.
3. C-code design   : ARM Keil MDK V5.24 and higher
4. Serial debugging assistant
5. Python 3.7
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
        \output                 --> Output
        \tf_model               --> Model tflite
        \work                   --> Temporary working space
    \doc                        --> Documents
        \README.md              --> Read me file
    \plugins                    --> Plugins
        \flatc                  --> Flatc tool
            \flatc.exe          --> Convert tflite
            \schema.fbs         --> Schema file for flatc
        \merge_bit              --> Merge bit tool
            \make_loc.exe       --> Generate itcm location
            \merge_bit.exe      --> Merge fs file and bin file
===============================================================================================================================================
MICRO_SPEECH SOFTWARE DESIGN
1. Memory settings
    1) IROM1
        start             size
        0x0               0x10000 (64KB)
    2) IRAM1
        start             size
        0x20000000        0x10000 (64KB)
===============================================================================================================================================
MICRO_SPEECH HARDWARE DESIGN
1. Cortex-M1 Core
    1) Disable debug
    2) Frequency is 48MHz
    3) Internal instruction memory is 64KB
    4) Internal data memory is 64KB
    5) No OS extension
2. Peripherals
    1) GPIO
    2) UART0
    3) AHB Master [1]
3. Synthesis tool : GowinSynthesis
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