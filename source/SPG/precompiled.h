#pragma once

#ifndef PRECOMPILED_H
#define PRECOMPILED_H

#include "crap.h"


#if defined(DEBUG) || defined(_DEBUG)
#define DATA_PATH crap::string256("../../../data/")
#define BINARY_PATH crap::string256("../../../data/binary/")
#else
#define DATAPATH crap::string256("data/")
#define BINARY_PATH crap::string256("data/binary/")
#endif

#endif // PRECOMPILED_H