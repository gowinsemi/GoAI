@echo off

echo.
echo ----------------------------------------------------------------------------------
echo          COPYRIGHT (C) 2014-2020 GOWIN SEMICONDUCTOR TECHNOLOGY CO.,LTD.
echo                             ALL RIGHTS RESERVED.
echo ----------------------------------------------------------------------------------
echo.


set tflite_model_file=D:\user-bak\Users\root\Desktop\car_detection_sdk\data\tf_model\car_detection.tflite
set gowin_programmer_path=D:\user-bak\Users\root\Desktop\car_detection_sdk\plugins\programmer
set keil_path=C:/Keil_v5

echo.
echo GOAI CAR_DETECTION BEGINNING...

call car_detection.exe --device GW1NSR4C --tflite_model_file %tflite_model_file% --gowin_programmer_path %gowin_programmer_path% --keil_path %keil_path%

echo.
echo GOAI CAR_DETECTION BUILD DONE!

pause