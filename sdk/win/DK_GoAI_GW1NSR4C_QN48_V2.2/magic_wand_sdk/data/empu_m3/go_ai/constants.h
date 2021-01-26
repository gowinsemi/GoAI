/*
 * *****************************************************************************************
 *
 * 		Copyright (C) 2014-2020 Gowin Semiconductor Technology Co.,Ltd.
 * 		
 * @file			constants.h
 * @author		Embedded Development Team
 * @version		V1.0.0
 * @date			2020-10-12 09:00:00
 * @brief			constants.
 ******************************************************************************************
 */

#ifndef GOAI_CONSTANTS_H_
#define GOAI_CONSTANTS_H_

/* Definitions ------------------------------------------------------------------------ */
//The expected accelerometer data sample frequency
const float kTargetHz = 25;

// What gestures are supported.
const int kGestureCount = 4;
const int kWingGesture = 0;		//Wing
const int kRingGesture = 1;		//Ring
const int kSlopeGesture = 2;	//Slope
const int kNoGesture = 3;			//Unknown

//These control the sensitivity of the detection algorithm. If you're seeing
//too many false positives or not enough true positives, you can try tweaking
//these thresholds. Often, increasing the size of the training set will give
//more robust results though, so consider retraining if you are seeing poor
//predictions.
//const float kDetectionThreshold = 0.8f;
const float kDetectionThreshold = 0.6f;
const int kPredictionHistoryLength = 5;
const int kPredictionSuppressionDuration = 25;

#endif
