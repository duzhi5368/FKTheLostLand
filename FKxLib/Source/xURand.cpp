/**
*	created:		2013-4-16   5:01
*	filename: 		xURand
*	author:			FreeKnight
*	Copyright (C): 	 FreeKnightServerEngine
*	purpose:		
*/
//------------------------------------------------------------------------
#include "..\Include\xURand.h"
//------------------------------------------------------------------------
float
SeedGen(float min, float max)
{
	unsigned long n = (unsigned long)rand() % 101;
	return min + (float) n * 0.01f * (max - min);
}
//------------------------------------------------------------------------
bool
RandomGen(int probability)
{
	if (probability <= 0)
		return false;
	else if(probability >= 100)
		return true;

	bool arr[100];
    int i;
	for (i = 0; i < probability; i++)
		arr[i] = true;
	for (i = probability; i < 100; i++)
		arr[i] = false;
	int index = rand() % 100;
	return arr[index];
}
//------------------------------------------------------------------------
bool
RandomGen(int totalProbability, int probability)
{
	if (totalProbability < 1 || probability < 1)
		return false;

	int index = rand() % totalProbability;
	return index <= probability ? true : false;
}
//------------------------------------------------------------------------
int
RandomGen(const int probability_arr[], int arr_len, bool bHundredBased/* = true*/)
{
	int prob_sum = 0;
	int i;
	for (i = 0; i < arr_len; i++)
	{
		if (probability_arr[i] < 0)
			return -2;

		prob_sum += probability_arr[i];
	}

	if(prob_sum <= 0)
		return -1;

	if (bHundredBased)
	{
		if (prob_sum > 100)
		{
			return -2;
		}
		else
		{
			prob_sum = 100;
		}
	}

	vector<int> TestArray;
	int index = 0;
	for (i = 0; i < arr_len; i++)
	{
		for (int j = 0; j < probability_arr[i]; j++)
		{
			TestArray.push_back(i);
			index++;
		}
	}
	for (i = index; i < prob_sum; i++)
	{
		TestArray[i] = -1;
	}

	return TestArray[rand() % prob_sum];
}
//------------------------------------------------------------------------
int
RandomGen(const vector<int>& arr, bool bHundredBased)
{
	int prob_sum = 0;
	unsigned int i;
	for (i = 0; i < arr.size(); i++)
	{
		if (arr[i] < 0)
			return -2;

		prob_sum += arr[i];
	}

	if(prob_sum <= 0)
		return -1;//列表总数小于0，无法循环

	if (bHundredBased)
	{
		if (prob_sum > 100)
		{
			return -2;//基数小于列表总合，有些概率永远无法达到。
		}
		else
		{
			prob_sum = 100;
		}
	}

	int randnum = rand() % prob_sum;
	i=0;
	while(randnum >= 0)
	{
		if(i >= arr.size())
			return -2;

		randnum -= arr[i];
		if(randnum <= 0)
			return i;
		i++;
	}

	return -1;
}
//------------------------------------------------------------------------
bool
RandomGen(
		  int result_array[], 
		  const int probability_arr[], 
		  int arr_len, 
		  int sel_num, 
		  bool repeat/* = false*/
		  )
{
	int *pTempArray = new int[arr_len];
	if (NULL == pTempArray)
		return false;

	for (int i = 0; i < arr_len; i++)
	{
		pTempArray[i] = probability_arr[i];
	}

	int result_pos = 0;
	for (int i = 0; i < sel_num; i++)
	{
		int index = RandomGen(pTempArray, arr_len, false);
		if (index < 0)
		{
			delete[] pTempArray;
			pTempArray = NULL;

			return false;
		}

		result_array[result_pos++] = index;
		if (false == repeat)
		{
			pTempArray[index] = 0;
		}
	}

	delete[] pTempArray;
	pTempArray = NULL;
	return true;
}
//------------------------------------------------------------------------