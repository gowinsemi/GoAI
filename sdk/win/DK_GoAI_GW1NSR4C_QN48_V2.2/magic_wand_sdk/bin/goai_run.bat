@echo off

echo.
echo ----------------------------------------------------------------------------------
echo          COPYRIGHT (C) 2014-2021 GOWIN SEMICONDUCTOR TECHNOLOGY CO.,LTD.
echo                             ALL RIGHTS RESERVED.
echo ----------------------------------------------------------------------------------
echo.

echo.
echo GOAI MAGIC_WAND BEGINNING...
call magic_wand.exe --device GW1NSR4C --tflite_model_file C:\Users\liukai\Desktop\magic_wand_sdk\data\tf_model\magic_wand.tflite --gowin_eda_path D:/Gowin/Gowin_V1.9.7.01Beta --keil_path D:/Keil_v5

echo.
echo GOAI MAGIC_WAND BUILD DONE!

pause