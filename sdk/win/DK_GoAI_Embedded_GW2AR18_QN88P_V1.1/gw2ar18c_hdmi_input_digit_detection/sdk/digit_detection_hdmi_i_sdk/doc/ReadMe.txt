===============================================================================================================================================
                                       Copyright (C) 2014-2021 Gowin Semiconductor Technology Co.,Ltd
                                                           All Rights Reserved
===============================================================================================================================================
                                                    GoAI:digit_detection_hdmi_i SDK
===============================================================================================================================================
VERSION
    GoAI 2.0
===============================================================================================================================================
FUNCTION
    Recognize digit '0' ~ '9'.
    LED2,LED3,LED4,LED5,LED11 and LED12 are GoAI running indicator and system running indicator.
    HDMI output hdmi rx image and character 'Zero' ~ 'Nine' on screen.
===============================================================================================================================================
RESULT
1. Input image data from hdmi rx device.
2. Screen displays 'Zero' ~ 'Nine' through HDMI wire.
3. LED2,LED3,LED4,LED5,LED11 and LED12 are blinking to indicate each loop.
===============================================================================================================================================
HOW TO RUN
1. Open "digit_detection_hdmi_i_sdk\bin\goai_run.bat";
2. Change parameters in "goai_run.bat" and store;
    1) tflite_model_file        : specify the full path of digit_detection tflite model ("digit_detection_hdmi_i_sdk\data\tf_model\digit_detection.tflite")
    2) programmer_path          : specify the full path of Gowin Programmer ("digit_detection_hdmi_i_sdk\plugins\programmer")
    3) keil_path                : specify the full path of Keil IDE (For example, "ARM Keil MDK V5.26")
    4）training_type            : specify tflite model training type (tf or keras)
3. Double click "goai_run.bat" and run digit_detection_hdmi_i SDK.
===============================================================================================================================================
OPERATING SYSTEM
1. Windows 7/10.
===============================================================================================================================================
DEVELOPMENT KITS
1. 1x DK-GoAI-GW2AR18_QN88P_V1.1
    GW2AR-18C (version C)
    GW2AR-LV18QN88PC8/I7
2. 1x USB wire
3. 1x HMDI rx device
4. 2x HMDI wire
5. Screen with HDMI interface
===============================================================================================================================================
INTEGRATED DEVELOPMENT ENVIRONMENT
1. RTL-code design : Gowin_V1.9.7.02Beta and higher
2. Synthesis tool  : GowinSynthesis V1.9.7.02Beta and higher
3. C-code design   : ARM Keil MDK V5.26 and higher
4. Python 3.4
===============================================================================================================================================
SDK STRUCTURE
\digit_detection_hdmi_i_sdk
    \bin                            --> Executable file
        \goai_run.bat               --> Run automatically
        \digit_detection.exe        --> Execute digit_detection_hdmi_i SDK
    \data                           --> Input, output, model, empu_m1 and fpga design
        \empu_m1                    --> M1 c-code design
            \empu_m1                --> M1 libaray
            \go_ai                  --> GoAI library
        \fpga                       --> FPGA fs file and posp file
            \digit_detection.fs     --> FPGA fs file
            \digit_detection.posp   --> FPGA posp file
        \output                     --> Output weight/bias/output_multiplier/output_shift bin and bitstream fs/bin and mcu bin
        \tf_model                   --> Model tflite
    \doc                            --> Documents
        \ReadMe.txt                 --> Read me file
    \plugins                        --> Plugins
        \flatc                      --> Flatc tool
            \flatc.exe              --> Convert tflite
            \schema.fbs             --> Schema file for flatc
        \programmer                 --> Gowin Programmer
        \merge_bit                  --> Merge fs file and bin file
===============================================================================================================================================
DIGIT_DETCTION SOFTWARE DESIGN
1. Memory settings
    1) IROM1
        start             size
        0x0               0x2000 (8KB)
    2) IRAM1
        start             size
        0x20000000        0x2000 (8KB)
===============================================================================================================================================
DIGIT_DETECTION HARDWARE DESIGN
1. Cortex-M1 Core
    1) Internal instruction memory is 8KB (ITCM)
    2) Internal data memory is 8KB (DTCM)
    3) Interrupt number is 32
    4) Disable OS Extension
    5) Disable debug
    6) Disable ITCM initialization
2. Peripherals
    1) GPIO
    2) AHB Master Extension
3. Synthesis tool : GowinSynthesis V1.9.7.02
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