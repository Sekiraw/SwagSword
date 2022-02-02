#pragma once
#include "Singleton.hpp"

class Testclass : public CSingleton<Testclass>
{
public:
	bool testfunctioncall();
};