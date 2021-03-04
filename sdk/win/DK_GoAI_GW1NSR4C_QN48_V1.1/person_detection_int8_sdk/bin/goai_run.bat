@echo off

echo.
echo ----------------------------------------------------------------------------------
echo          COPYRIGHT (C) 2014-2021 GOWIN SEMICONDUCTOR TECHNOLOGY CO.,LTD.
echo                             ALL RIGHTS RESERVED.
echo ----------------------------------------------------------------------------------
echo.


set tflite_model_file=C:/projects/public_GoAI/sdk/win/DK_GoAI_Embedded_GW2AR18_QN88P_V1.1/person_detection_int8_sdk/data/tf_model/person_detection.tflite
set programmer_path=C:/projects/public_GoAI/sdk/win/DK_GoAI_Embedded_GW2AR18_QN88P_V1.1/person_detection_int8_sdk/plugins/programmer
set keil_path=C:/Keil_v5

echo.
echo GOAI PERSON_DETECTION BEGINNING...

call person_detection.exe --device GW1NSR4C --tflite_model_file %tflite_model_file% --programmer_path %programmer_path% --keil_path %keil_path% --training_type keras

echo.
echo GOAI PERSON_DETECTION BUILD DONE!

pause