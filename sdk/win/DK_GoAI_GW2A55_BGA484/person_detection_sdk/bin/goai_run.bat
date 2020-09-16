@echo off

echo.
echo ----------------------------------------------------------------------------------
echo          COPYRIGHT (C) 2014-2020 GOWIN SEMICONDUCTOR TECHNOLOGY CO.,LTD.
echo                             ALL RIGHTS RESERVED.
echo ----------------------------------------------------------------------------------
echo.

call person_detection.exe --device GW2A55C --tflite_model_file D:\user-bak\Users\root\Desktop\person_detection_sdk\data\tf_model\person_detection.tflite --gowin_eda_path D:/Gowin/Gowin_V1.9.6.02Beta --keil_path C:/Keil_v5

echo.
echo GOAI PERSON_DETECTION BUILD DONE!

pause