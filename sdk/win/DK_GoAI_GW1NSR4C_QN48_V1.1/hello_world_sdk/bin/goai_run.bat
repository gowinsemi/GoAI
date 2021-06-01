@echo off

echo.
echo ----------------------------------------------------------------------------------
echo          COPYRIGHT (C) 2014-2021 GOWIN SEMICONDUCTOR TECHNOLOGY CO.,LTD.
echo                             ALL RIGHTS RESERVED.
echo ----------------------------------------------------------------------------------
echo.

call hello_world.exe --device GW1NSR4C --tflite_model_file F:\hello_world_sdk\data\tf_model\helloworld.tflite --programmer_cli_path D:\Gowin\Gowin_V1.9.7.05Beta\Programmer\bin --gmd_cli_path C:\GMD\toolchain\ARM_toolchain\bin --training_type tf

pause