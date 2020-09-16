@echo off

echo.
echo ----------------------------------------------------------------------------------
echo          COPYRIGHT (C) 2014-2020 GOWIN SEMICONDUCTOR TECHNOLOGY CO.,LTD.
echo                             ALL RIGHTS RESERVED.
echo ----------------------------------------------------------------------------------
echo.

call hello_world.exe --device GW2AR18C --tflite_model_file D:\user-bak\Users\root\Desktop\hello_world_sdk\data\tf_model\helloworld.tflite --gowin_eda_path D:/Gowin/Gowin_V1.9.6.02Beta --keil_path C:/Keil_v5

echo.
echo GOAI HELLO_WORLD BUILD DONE!

pause