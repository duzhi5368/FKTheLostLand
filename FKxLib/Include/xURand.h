/**
*	created:		2013-4-16   4:55
*	filename: 		xURand
*	author:			FreeKnight
*	Copyright (C): 	 FreeKnightServerEngine
*	purpose:		
*/
//------------------------------------------------------------------------
#pragma once
//------------------------------------------------------------------------
#include <vector>
using namespace std;
//------------------------------------------------------------------------
extern
float
SeedGen(float min, float max);
//------------------------------------------------------------------------
extern
bool
RandomGen(int probability);
//------------------------------------------------------------------------
extern
bool
RandomGen(int totalProbability, int probability);
//------------------------------------------------------------------------
extern
int
RandomGen(const int probability_arr[], int arr_len, bool bHundredBased = true);
//------------------------------------------------------------------------
extern
int
RandomGen(const vector<int>& arr, bool bHundredBased);
//------------------------------------------------------------------------
extern
bool
RandomGen(
		  int result_array[], 
		  const int probability_arr[], 
		  int arr_len, 
		  int sel_num, 
		  bool repeat = false
		  );
//------------------------------------------------------------------------