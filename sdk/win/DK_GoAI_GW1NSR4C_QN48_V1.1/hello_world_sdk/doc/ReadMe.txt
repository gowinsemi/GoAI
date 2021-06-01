===============================================================================================================================================
                                       Copyright (C) 2014-2021 Gowin Semiconductor Technology Co.,Ltd
                                                           All Rights Reserved
===============================================================================================================================================
                                                          GoAI:hello_world SDK
===============================================================================================================================================
VERSION
    GoAI2.0
===============================================================================================================================================
FUNCTION
    y = sin(x).
===============================================================================================================================================
RESULT
1. Light LED2, LED3 as a sinusoid.
2. Print (x,y) on serial terminal.
===============================================================================================================================================
HOW TO RUN
1. Open "hello_world_sdk\bin\goai_run.bat";
2. Change parameters in "goai_run.bat" and store;
    1) --device                   : specify the device type (default is GW1NSR4C)
    2) --tflite_model_file        : specify the full path of hello_word tflite model (For example, "hello_world_sdk\data\tf_model\helloworld.tflite")
    3) --programmer_cli_path      : specify the full path of Gowin Programmer (For example, "Gowin_V1.9.7.05Beta\Programmer\bin")
    4) --gmd_cli_path             : specify the full path of Gcc (For example, "C:\GMD\toolchain\ARM_toolchain\bin")
    5) --training_type            : specify the model training type (tf or keras)
3. Double click "goai_run.bat" and run hello_world sdk.
===============================================================================================================================================
OPERATING SYSTEM
1. Windows 7/10.
===============================================================================================================================================
DEVELOPMENT KITS
1. 1x DK-GoAI-GW1NSR4C-QN48 V1.1 board
    GW1NSR-4C
    GW1NSR-LV4CQN48PC7/I6
2. 1x USB wire
===============================================================================================================================================
STRUCTURE
\hello_world_sdk
    \bin                        --> Executable file
    \data                       --> Input, output, model, empu_m3 and fpga design
        \empu_m3                --> M3 c-code design
            \empu_m3            --> M3 libaray
            \go_ai              --> GoAI library
        \fpga                   --> FPGA fs file
            \hello_word.fs      --> FPGA fs file
        \output                 --> Output bitstream
        \tf_model               --> Model tflite
    \doc                        --> Documents
        \ReadMe.txt             --> Read me file
    \plugins                    --> Plugins
        \flatc                  --> Flatc tool
            \flatc.exe          --> Convert tflite
            \schema.fbs         --> Schema file for flatc
===============================================================================================================================================
HELLO_WORLD SOFTWARE DESIGN
1. Memory settings
    1) Flash
        start             size
        0x0               0x8000 (32KB)
    2) Sram
        start             size
        0x20000000        0x4000 (16KB)
2. Compile tool : GMD V1.1
===============================================================================================================================================
HELLO_WORLD HARDWARE DESIGN
1. Cortex-M3 Core
    1) Debug
    2) Frequency is 80MHz
    3) Flash is 32KB
    4) Sram is 16KB
2. Peripherals
    1) GPIO
3. Synthesis tool : GowinSynthesis V1.9.7.05Beta
4. PnR tool : Gowin_V1.9.7.05Beta
===============================================================================================================================================
MODEL STRUCTURE
       input
         | (1 x 1)
    FullyConnected
         | (1 x 16)
    FullyConnected
         | (1 x 16)
    FullyConnected
         | (1 x 1)
      output
===============================================================================================================================================
MODEL PARAMETERS
    input_offset             : Input offset, "quantization"'s "zero_point" in each layer's input tensor.
    filter_offset            : Weight offset, "quantization"'s "zero_point" in each layer's weight tensor.
    output_offset            : Output offset, "quantization"'s "zero_point" in each layer's output tensor.
    output_multiplier        : Mantissa of "quantization"'s "scale".
    output_shift             : Exponent of "quantization"'s "scale".
    output_activation_min    : Size of weight's data type, e.g. int8_t is -128.
    output_activation_max    : Size of weight's data type, e.g. int8_t is 127.
    filter_dim_count         : Dimension of weight's "shape".
    batches                  : Data batches of input into model computing, e.g. if the input data is too more, need to divide data into several batches.
    output_depth             : Weight shape's 1st dimension.
    accum_depth              : Weight shape's 2nd dimension.
    filter_val               : Weight.
    bias_data                : Bias.
===============================================================================================================================================