@echo off

echo.
echo ----------------------------------------------------------------------------------
echo          COPYRIGHT (C) 2014-2021 GOWIN SEMICONDUCTOR TECHNOLOGY CO.,LTD.
echo                             ALL RIGHTS RESERVED.
echo ----------------------------------------------------------------------------------
echo.


set tflite_model_file=C:\Users\liukai\Desktop\car_detection_sdk\data\tf_model\car_detection.tflite
set gowin_programmer_path=C:\Users\liukai\Desktop\car_detection_sdk\plugins\programmer
set keil_path=D:/Keil_v5

echo.
echo GOAI CAR_DETECTION BEGINNING...

call car_detection.exe --device GW2AR18C --tflite_model_file %tflite_model_file% --gowin_programmer_path %gowin_programmer_path% --keil_path %keil_path%

echo.
echo GOAI CAR_DETECTION BUILD DONE!

pause