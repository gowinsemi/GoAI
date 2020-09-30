@echo off

echo.
echo ----------------------------------------------------------------------------------
echo          COPYRIGHT (C) 2014-2020 GOWIN SEMICONDUCTOR TECHNOLOGY CO.,LTD.
echo                             ALL RIGHTS RESERVED.
echo ----------------------------------------------------------------------------------
echo.

echo.
echo GOAI MICRO_SPEECH BEGINNING...

call micro_speech.exe --device GW2A55C --tflite_model_file C:\projects\AI\GoAI_sdk\sdk\win\DK_GoAI_GW2A55_BGA484\micro_speech_sdk\data\tf_model\micro_speech.tflite --gowin_eda_path C:/Gowin/Gowin_V1.9.6.02Beta --keil_path C:/Keil_v5

echo.
echo GOAI MICRO_SPEECH BUILD DONE!

pause