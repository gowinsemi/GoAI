@echo off

echo.
echo ----------------------------------------------------------------------------------
echo          COPYRIGHT (C) 2014-2021 GOWIN SEMICONDUCTOR TECHNOLOGY CO.,LTD.
echo                             ALL RIGHTS RESERVED.
echo ----------------------------------------------------------------------------------
echo.

call car_detection.exe --device GW2A55C --tflite_model_file F:\car_detection_sdk\data\tf_model\car_detection.tflite --programmer_cli_path D:\Gowin\Gowin_V1.9.7.05Beta\Programmer\bin --gmd_cli_path C:\GMD\toolchain\ARM_toolchain\bin --training_type tf

pause