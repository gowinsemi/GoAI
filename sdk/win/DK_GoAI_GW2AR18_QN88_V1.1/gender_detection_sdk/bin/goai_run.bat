@echo off

echo.
echo ----------------------------------------------------------------------------------
echo          COPYRIGHT (C) 2014-2021 GOWIN SEMICONDUCTOR TECHNOLOGY CO.,LTD.
echo                             ALL RIGHTS RESERVED.
echo ----------------------------------------------------------------------------------
echo.


set tflite_model_file=F:\gender_detection_sdk\data\tf_model\gender_detection.tflite
set programmer_cli_path=D:\Gowin\Gowin_V1.9.7.05Beta\Programmer\bin
set gmd_cli_path=C:\GMD\toolchain\ARM_toolchain\bin

call gender_detection.exe --device GW2AR18C --tflite_model_file %tflite_model_file% --programmer_cli_path %programmer_cli_path% --gmd_cli_path %gmd_cli_path% --training_type keras

pause