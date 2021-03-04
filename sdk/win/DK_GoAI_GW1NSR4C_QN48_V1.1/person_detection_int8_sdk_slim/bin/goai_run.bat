@echo off

echo.
echo ----------------------------------------------------------------------------------
echo          COPYRIGHT (C) 2014-2020 GOWIN SEMICONDUCTOR TECHNOLOGY CO.,LTD.
echo                             ALL RIGHTS RESERVED.
echo ----------------------------------------------------------------------------------
echo.


set tflite_model_file=D:\user-bak\Users\root\Desktop\person_detection_int8_sdk\data\tf_model\person_detection.tflite
set gowin_programmer_path=D:\user-bak\Users\root\Desktop\person_detection_int8_sdk\plugins\programmer
set keil_path=C:/Keil_v5

echo.
echo GOAI PERSON_DETECTION BEGINNING...

call person_detection.exe --device GW1NSR4C --tflite_model_file %tflite_model_file% --gowin_programmer_path %gowin_programmer_path% --keil_path %keil_path%

echo.
echo GOAI PERSON_DETECTION BUILD DONE!

pause