===============================================================================================================================================
                                       Copyright (C) 2014-2021 Gowin Semiconductor Technology Co.,Ltd
                                                           All Rights Reserved
===============================================================================================================================================
                                                          GoAI:magic_wand SDK
===============================================================================================================================================
VERSION
    GoAI 2.0 magic_wand.
===============================================================================================================================================
FUNCTION
    Recognize three movements : wing, ring and slope.
===============================================================================================================================================
RESULT
1. LED2 blinks one time : wing.
2. LED2 blinks two times : ring.
3. LED2 blinks three times : slope.
===============================================================================================================================================
HOW TO RUN
1. Open "magic_wand_sdk\bin\goai_run.bat";
2. Change parameters in "goai_run.bat" and store;
    1) --device            : specify the device type (default is GW1NSR4C)
    2) --tflite_model_file : specify the full path of magic_wand tflite model (For example, "magic_wand_sdk\data\tf_model\magic_wand.tflite")
    3) --gowin_eda_path    : specify the full path of Gowin IDE (For example, "Gowin_V1.9.7.01Beta")
    4) --keil_path         : specify the full path of Keil IDE (For example, "ARM Keil MDK V5.26")
3. Double click "goai_run.bat" and run magic_wand sdk.
===============================================================================================================================================
OPERATING SYSTEM
1. Windows 7/10.
===============================================================================================================================================
DEVELOPMENT KITS
1. DK-GoAI-Embedded-GW1NSR4C-QN48P-V2.2
    GW1NSR-4C
    GW1NSR-LV4CQN48PC7/I6
2. USB wire
3. Power adapter
===============================================================================================================================================
INTEGRATED DEVELOPMENT ENVIRONMENT
1. RTL-code design : Gowin_V1.9.7.01 Beta and higher.
2. Synthesis tool  : GowinSynthesis V1.9.7.01 Beta and higher.
3. C-code design   : ARM Keil MDK V5.26 and higher
4. Python 3.4
===============================================================================================================================================
STRUCTURE
\magic_wand_sdk
    \bin                        --> Executable file
    \data                       --> Input, output, model, empu_m3 and fpga design
        \empu_m3                --> M3 c-code design
            \empu_m3            --> M3 libaray
            \go_ai              --> GoAI library
        \fpga                   --> FPGA fs file
            \magic_wand.fs      --> FPGA fs file
        \output                 --> Output bitstream
        \tf_model               --> Model tflite
    \doc                        --> Documents
        \README.md              --> Read me file
    \plugins                    --> Plugins
        \flatc                  --> Flatc tool
            \flatc.exe          --> Convert tflite
            \schema.fbs         --> Schema file for flatc
===============================================================================================================================================
MAGIC_WAND SOFTWARE DESIGN
1. Memory settings
    1) IROM1
        start             size
        0x0               0x8000 (32KB)
    2) IRAM1
        start             size
        0x20000000        0x4000 (16KB)
===============================================================================================================================================
MAGIC_WAND HARDWARE DESIGN
1. Cortex-M3 Core
    1) Debug
    2) Frequency is 60MHz
    3) Flash is 32KB
    4) SRAM is 16KB
2. Peripherals
    1) GPIO
    2) I2C
    3) UART0
3. Synthesis tool : GowinSynthesis
===============================================================================================================================================
MODEL STRUCTURE
       input
         | (1 x 128 x 3 x 1)
       Conv2D
         | (1 x 128 x3 x8)
      MaxPool2D
         | (1 x42 x 1 x 8)
       Conv2D
         | (1 x 42 x 1 x 16)
      MaxPool2D
         | (1 x 14 x 1 x 16)
      Reshape
         | (1 x 224)
    FullyConnected
         | (1 x 16)
    FullyConnected
         | (1 x 4)
      Softmax
         | (1 x 4)
       output
===============================================================================================================================================