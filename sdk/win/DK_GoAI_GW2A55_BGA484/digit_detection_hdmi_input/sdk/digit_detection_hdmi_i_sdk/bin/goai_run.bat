@echo off

echo.
echo ----------------------------------------------------------------------------------
echo          COPYRIGHT (C) 2014-2021 GOWIN SEMICONDUCTOR TECHNOLOGY CO.,LTD.
echo                             ALL RIGHTS RESERVED.
echo ----------------------------------------------------------------------------------
echo.

echo.
echo GOAI DIGIT_DETECTION BEGINNING...

call digit_detection.exe --device GW2A55C --tflite_model_file C:\Users\liukai\Desktop\digit_detection_hdmi_i_sdk\data\tf_model\digit_detection.tflite --gowin_eda_path D:\Gowin\Gowin_V1.9.7.02Beta --keil_path D:\Keil_v5 --training_type keras

echo.
echo GOAI DIGIT_DETECTION BUILD DONE!

pause