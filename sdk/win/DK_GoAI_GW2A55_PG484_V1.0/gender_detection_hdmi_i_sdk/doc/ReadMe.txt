===============================================================================================================================================
                                       Copyright (C) 2014-2021 Gowin Semiconductor Technology Co.,Ltd
                                                           All Rights Reserved
===============================================================================================================================================
                                                    GoAI:gender_detection_hdmi_i SDK
===============================================================================================================================================
VERSION
    GoAI2.0
===============================================================================================================================================
FUNCTION
    Recognize female or male.
===============================================================================================================================================
RESULT
1. Input image data from HDMI input device.
2. Led changed when female or male or unknown.
   1) LED2 : unknown
   2) LED4 : female
   3) LED3 : male
3. HDMI outputs 'FEMALE' or 'MALE' or empty.
4. Serial terminal outputs 'unknown' or 'female' or 'male'.
===============================================================================================================================================
HOW TO RUN
1. Open "gender_detection_hdmi_i_sdk\bin\goai_run.bat";
2. Change parameters in "goai_run.bat" and store;
    1) --device                   : specify the device type (default is GW2A55C)
    2) --tflite_model_file        : specify the full path of gender_detection_hdmi_i tflite model ("gender_detection_hdmi_i_sdk\data\tf_model\gender_detection.tflite")
    3) --programmer_cli_path      : specify the full path of Gowin Programmer (For example, "Gowin_V1.9.7.05Beta\Programmer\bin")
    4) --gmd_cli_path             : specify the full path of Gcc (For example, "C:\GMD\toolchain\ARM_toolchain\bin")
    5) --training_type            : specify tflite model training type (tf or keras)
3. Double click "goai_run.bat" and run gender_detection_hdmi_i SDK.
===============================================================================================================================================
OPERATING SYSTEM
1. Windows 7/10.
2. MacOS.
3. Linux.
===============================================================================================================================================
DEVELOPMENT KITS
1. 1x DK-GoAI-GW2A55-PG484 V1.0 board
    GW2A-55C (version C)
    GW2A-LV55PG484C8/I7
2. 2x Displayers with HDMI Interface
3. 2x HDMI wires
4. 1x USB wire
===============================================================================================================================================
SDK STRUCTURE
\gender_detection_hdmi_i_sdk
    \bin                            --> Executable file
        \goai_run.bat               --> Run automatically
        \gender_detection.exe       --> Execute gender_detection_hdmi_i SDK
    \data                           --> Input, output, model, empu_m1 and fpga design
        \empu_m1                    --> M1 c-code design
            \empu_m1                --> M1 libaray
            \go_ai                  --> GoAI library
        \fpga                       --> FPGA fs file and posp file
            \gender_detection.fs    --> FPGA fs file
            \gender_detection.posp  --> FPGA posp file
        \output                     --> Output weight/bias and bitstream
        \tf_model                   --> Model tflite
    \doc                            --> Documents
        \ReadMe.txt                 --> Read me file
    \plugins                        --> Plugins
        \flatc                      --> Flatc tool
        \merge_bit                  --> Merge bit tool
===============================================================================================================================================
GENDER_DETCTION_HDMI_I SOFTWARE DESIGN
1. Memory settings
    1) Flash
        start             size
        0x0               0x4000 (16KB)
    2) Sram
        start             size
        0x20000000        0x4000 (16KB)
2. Compile tool : GMD V1.1
===============================================================================================================================================
GENDER_DETECTION_HDMI_I HARDWARE DESIGN
1. Cortex-M1 Core
    1) Disable Debug
    2) Frequency is 48MHz
    3) Internal instruction memory is 16KB
    4) Internal data memory is 16KB
    5) Disable OS extension
2. Peripherals
    1) GPIO
    2) UART0
    3) AHB Master [1]
3. Synthesis tool : SynplifyPro
4. PnR tool : Gowin_V1.9.7.05Beta
===============================================================================================================================================
MODEL PARAMETERS
    DEPTHWISE             : DepthwiseConv2D layer's flag, 1 is DepthwiseConv2D layer, 0 is not DepthwiseConv2D layer.
    IN_OFFSET             : Input offset, "quantization"'s "zero_point" in each layer's input tensor.
    WT_OFFSET             : Weight offset, "quantization"'s "zero_point" in each layer's weight tensor.
    OUT_OFFSET            : Output offset, "quantization"'s "zero_point" in each layer's output tensor.
    OUT_MULTIPLIER_OFFSET : Output multiplier offset.
    OUT_SHIFT_OFFSET      : Output shift offset.
    OUT_ACTIVATION_MIN    : Size of weight's data type, e.g. int8_t is -128.
    OUT_ACTIVATION_MAX    : Size of weight's data type, e.g. int8_t is 127.
    BATCH                 : Data batches of input into model computing, e.g. if the input data is too more, need to divide data into several batches.
    DILATION_FACTOR       : Dilations.
    CONV_PADDING          : DepthwiseConv2D/Conv2D padding.
    CONV_STRIDE           : DepthwiseConv2D/Conv2D stride length. 
    CONV_IM_CH            : DepthwiseConv2D/Conv2D input tensor's channels. 
    CONV_IM_DIM           : DepthwiseConv2D/Conv2D input tensor's dimension (height,width).
    CONV_OUT_CH           : DepthwiseConv2D/Conv2D output tensor's channels.
    CONV_OUT_DIM          : DepthwiseConv2D/Conv2D output tensor's dimension (height,width).
    CONV_KER_DIM          : DepthwiseConv2D/Conv2D convolution kernel tensor's dimension (height, width).
    POOL_EN               : AveragePool2D layer's flag, 1 is AveragePool2D layer, 0 is not AveragePool2D layer.
    POOL_OUT_DIM          : AveragePool2D input tensor's dimension (height, width).
    POOL_OUT_CH           : AveragePool2D output tensor's channels.
    POOL_KER_DIM          : AveragePool2D kernel tensor's dimension (height, width).
    POOL_PADDING          : AveragePool2D padding.
    POOL_STRIDE           : AveragePool2D stride length.
===============================================================================================================================================