@echo off

echo.
echo ----------------------------------------------------------------------------------
echo          COPYRIGHT (C) 2014-2021 GOWIN SEMICONDUCTOR TECHNOLOGY CO.,LTD.
echo                             ALL RIGHTS RESERVED.
echo ----------------------------------------------------------------------------------
echo.


set tflite_model_file=C:\Users\liukai\Desktop\digit_detection_hdmi_i_sdk\data\tf_model\digit_detection.tflite
set programmer_path=C:\Users\liukai\Desktop\digit_detection_hdmi_i_sdk\plugins\programmer
set keil_path=D:\Keil_v5

echo.
echo GOAI DIGIT_DETECTION_HDMI_I BEGINNING...

call digit_detection.exe --device GW2AR18C --tflite_model_file %tflite_model_file% --programmer_path %programmer_path% --keil_path %keil_path% --training_type keras

echo.
echo GOAI DIGIT_DETECTION_HDMI_I BUILD DONE!

pause