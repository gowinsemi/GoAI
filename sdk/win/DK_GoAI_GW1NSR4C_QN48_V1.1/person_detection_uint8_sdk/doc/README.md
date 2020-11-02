===============================================================================================================================================
                                       Copyright (C) 2014-2020 Gowin Semiconductor Technology Co.,Ltd
                                                           All Rights Reserved
===============================================================================================================================================
                                                    GoAI:person_detection_uint8 SDK
===============================================================================================================================================
VERSION
    GoAI 2.0
===============================================================================================================================================
FUNCTION
    Recognize person and no person.
===============================================================================================================================================
RESULT
1. Input image data from camera.
2. Led2 on is person, Led2 off is no person.
===============================================================================================================================================
HOW TO RUN
1. Open "person_detection_uint8_sdk\bin\goai_run.bat";
2. Change parameters in "goai_run.bat" and store;
    1) tflite_model_file        : specify the full path of person_detection tflite model ("person_detection_uint8_sdk\data\tf_model\person_detection.tflite")
    2) gowin_programmer_path    : specify the full path of Gowin Programmer ("person_detection_uint8_sdk\plugins\programmer")
    3) keil_path                : specify the full path of Keil IDE (For example, "ARM Keil MDK V5.24")
3. Double click "goai_run.bat" and run person_detection SDK.
===============================================================================================================================================
OPERATING SYSTEM
1. Windows 7/10.
===============================================================================================================================================
DEVELOPMENT KITS
1. DK-GoAI-GW1NSR4C-QN48-V1.1
    GW1NSR-4C
    GW1NSR-LV4CQN48PC7/I6
2. USB wire
3. Camera
===============================================================================================================================================
INTEGRATED DEVELOPMENT ENVIRONMENT
1. RTL-code design : Gowin_V1.9.7Beta and higher.
2. Synthesis tool  : GowinSynthesis V1.9.7Beta and higher.
3. C-code design   : ARM Keil MDK V5.24 and higher
4. Python 3.4
===============================================================================================================================================
SDK STRUCTURE
\person_detection_uint8_sdk
    \bin                            --> Executable file
        \goai_run.bat               --> Run automatically
        \person_detection.exe       --> Execute person_detection SDK
    \data                           --> Input, output, model, empu_m3 and fpga design
        \empu_m3                    --> M3 c-code design
            \empu_m3                --> M3 libaray
            \go_ai                  --> GoAI library
        \fpga                       --> FPGA fs file and posp file
            \person_detection.fs    --> FPGA fs file
        \output                     --> Output weight/bias bin and bitstream and mcu bin
        \tf_model                   --> Model tflite
    \doc                            --> Documents
        \README.md                  --> Read me file
    \plugins                        --> Plugins
        \flatc                      --> Flatc tool
            \flatc.exe              --> Convert tflite
            \schema.fbs             --> Schema file for flatc
        \programmer                 --> Gowin Programmer
===============================================================================================================================================
PERSON_DETCTION SOFTWARE DESIGN
1. Memory settings
    1) IROM1
        start             size
        0x0               0x8000 (32KB)
    2) IRAM1
        start             size
        0x20000000        0x1000 (4KB)
===============================================================================================================================================
PERSON_DETECTION HARDWARE DESIGN
1. Cortex-M3 Core
    1) Instruction memory is 32KB
    2) Data memory is 4KB
2. Peripherals
    1) GPIO
    2) UART0
    3) I2C
    4) AHB Master Extension
3. Synthesis tool : GowinSynthesis
===============================================================================================================================================
MODEL PARAMETERS
    DEPTHWISE             : DepthwiseConv2D layer's flag, 1 is DepthwiseConv2D layer, 0 is not DepthwiseConv2D layer.
    IN_OFFSET             : Input offset, "quantization"'s "zero_point" in each layer's input tensor.
    WT_OFFSET             : Weight offset, "quantization"'s "zero_point" in each layer's weight tensor.
    OUT_OFFSET            : Output offset, "quantization"'s "zero_point" in each layer's output tensor.
    OUT_MULTIPLIER        : Mantissa of "quantization"'s "scale".
    OUT_SHIFT             : Exponent of "quantization"'s "scale".
    OUT_ACTIVATION_MIN    : Size of weight's data type, e.g. uint8_t is 0.
    OUT_ACTIVATION_MAX    : Size of weight's data type, e.g. uint8_t is 255.
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