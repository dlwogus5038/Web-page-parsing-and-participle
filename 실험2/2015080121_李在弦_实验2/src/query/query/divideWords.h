#ifndef DIVIDEWORDS_H
#define DIVIDEWORDS_H

#include "My_CharStringLink.h"
#include "AVL.h"

#include <string>

My_CharStringLink* divideWords(My_AVL* &MAVL, std::string inputPath 
	, std::string outputPath , int* &checkLabelNum , int maxDicNum);


#endif DIVIDEWORDS_H