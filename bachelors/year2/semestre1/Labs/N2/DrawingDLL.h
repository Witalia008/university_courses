#ifndef DRAWINGDLL_EXPORTS
#define DRAWINGDLL_API __declspec(dllexport)
#else
#define DRAWINGDLL_API __declspec(dllimport)
#endif

#include <Windows.h>
extern "C" {
DRAWINGDLL_API void drawCircle(HDC, int, int, int);
}