@echo off

echo.
echo ----------------------------------------------------------------------------------
echo          COPYRIGHT (C) 2014-2021 GOWIN SEMICONDUCTOR TECHNOLOGY CO.,LTD.
echo                             ALL RIGHTS RESERVED.
echo ----------------------------------------------------------------------------------
echo.

call person_detection.exe --device GW2A55C --tflite_model_file F:\person_detection_hdmi_i_sdk\data\tf_model\person_detection.tflite --programmer_cli_path D:\Gowin\Gowin_V1.9.7.05Beta\Programmer\bin --gmd_cli_path C:\GMD\toolchain\ARM_toolchain\bin --training_type keras

pause