#pragma once

#ifdef MODEL_EXPORTS
#define MODEL_API __declspec(dllexport)
#else
#define MODEL_API __declspec(dllimport)
#endif

#define BEGIN_MODELNAMESPACE namespace Model {
#define END_MODELNAMESPACE };

#define USING_MODELNAMESPACE using namespace Model;

#include "TreeNode.h"
