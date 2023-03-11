
// Copyright (c) 2023 Jacob R. Green
// All Rights Reserved.

#pragma once

#include <muchcool/rndr.hpp>
#include <muchcool/xgdi.hpp>

#ifdef UXUI_INTERNALS
#define UXUI_PUBLIC public:
#define UXUI_PROTECTED protected:
#define UXUI_INTERNALPROTECTED public:
#define UXUI_INTERNAL public:
#define UXUI_PRIVATE private:
#else
#define UXUI_PUBLIC public:
#define UXUI_PROTECTED protected:
#define UXUI_INTERNALPROTECTED protected:
#define UXUI_INTERNAL private:
#define UXUI_PRIVATE private:
#endif

namespace muchcool::uxui {}