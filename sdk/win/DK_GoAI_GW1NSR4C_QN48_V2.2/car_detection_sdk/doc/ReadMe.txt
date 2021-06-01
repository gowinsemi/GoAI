===============================================================================================================================================
                                       Copyright (C) 2014-2021 Gowin Semiconductor Technology Co.,Ltd
                                                           All Rights Reserved
===============================================================================================================================================
                                                          GoAI:car_detection SDK
===============================================================================================================================================
VERSION
    GoAI2.0
===============================================================================================================================================
FUNCTION
    Recognize car and no car.
    LED2 is GoAI running indicator and System running indicator.
===============================================================================================================================================
RESULT
1. Input image data from camera.
2. Power on, LED2 will be blinked a moment.
3. If car, LED2 is on; If no car, LED2 is off. 
===============================================================================================================================================
HOW TO RUN
1. Open "car_detection_sdk\bin\goai_run.bat";
2. Change parameters in "goai_run.bat" and store;
    1) --tflite_model_file        : specify the full path of car_detection tflite model ("car_detection_sdk\data\tf_model\car_detection.tflite")
    2) --programmer_cli_path      : specify the full path of Gowin Programmer (For example, "Gowin_V1.9.7.05Beta\Programmer\bin")
    3) --gmd_cli_path             : specify the full path of Gcc (For example, "C:\GMD\toolchain\ARM_toolchain\bin")
    4) --training_type            : specify the tflite model training type (tf or keras)
    5) --device                   : specify the device type (default is GW1NSR4C)
3. Double click "goai_run.bat" and run car_detection SDK.
===============================================================================================================================================
OPERATING SYSTEM
1. Windows 7/10.
2. MacOS.
3. Linux.
===============================================================================================================================================
DEVELOPMENT KITS
1. 1x DK-GoAI-GW1NSR4C-QN48 V2.2 board
    GW1NSR-4C
    GW1NSR-LV4CQN48PC7/I6
2. 1x USB wire
3. 1x Camera
===============================================================================================================================================
SDK STRUCTURE
\car_detection_sdk
    \bin                            --> Executable file
        \goai_run.bat               --> Run automatically
        \car_detection.exe          --> Execute car_detection SDK
    \data                           --> Input, output, model, empu_m3 and fpga design
        \empu_m3                    --> M3 c-code design
            \empu_m3                --> M3 libaray
            \go_ai                  --> GoAI library
        \fpga                       --> FPGA fs file and posp file
            \car_detection.fs       --> FPGA fs file
        \output                     --> Output weight/bias/output_multiplier/output_shift bin and bitstream and mcu bin
        \tf_model                   --> Model tflite
    \doc                            --> Documents
        \ReadMe.txt                 --> Read me file
    \plugins                        --> Plugins
        \flatc                      --> Flatc tool
            \flatc.exe              --> Convert tflite
            \schema.fbs             --> Schema file for flatc
===============================================================================================================================================
CAR_DETCTION SOFTWARE DESIGN
1. Memory settings
    1) Flash
        start             size
        0x0               0x8000 (32KB)
    2) Sram
        start             size
        0x20000000        0x1000 (4KB)
2. Compile tool : GMD V1.1
===============================================================================================================================================
CAR_DETECTION HARDWARE DESIGN
1. Cortex-M3 Core
    1) Instruction memory is 32KB
    2) Data memory is 4KB
    3) Frequency is 40MHz
2. Peripherals
    1) GPIO
    2) I2C
    3) AHB Master Extension
3. Synthesis tool : GowinSynthesis V1.9.7.05Beta
4. PnR tool : Gowin_V1.9.7.05Beta
===============================================================================================================================================
MODEL PARAMETERS
    DEPTHWISE             : DepthwiseConv2D layer's flag, 1 is DepthwiseConv2D layer, 0 is not DepthwiseConv2D layer.
    IN_OFFSET             : Input offset, "quantization"'s "zero_point" in each layer's input tensor.
    WT_OFFSET             : Weight offset, "quantization"'s "zero_point" in each layer's weight tensor.
    OUT_OFFSET            : Output offset, "quantization"'s "zero_point" in each layer's output tensor.
    OUT_MULTIPLIER        : Mantissa of "quantization"'s "scale".
    OUT_SHIFT             : Exponent of "quantization"'s "scale".
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