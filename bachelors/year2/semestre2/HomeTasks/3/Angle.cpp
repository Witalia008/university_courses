#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <set>
#include <algorithm>
#include <vector>
#include <string>
#include <memory.h>
#include <map>
#define _USE_MATH_DEFINES
#include <math.h>
#include <list>
#include <fstream>
#include <time.h>
#include <iomanip>
#include <queue>
#include <stack>
#include <complex>
#include <limits.h>
#include <cassert>
#include <chrono>
#include <regex>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <unordered_map>
#include <unordered_set>
#include <random>
#include <valarray>
#include <Windows.h>


using namespace std;
using namespace std::chrono;

namespace {
#define клас class
#define захищені protected
#define публічні public
#define цілийТип int
#define дійснийТип double
#define статичний static
#define порожнеча void
#define потікКонсоліДляВводу cin
#define потікКонсоліДляВиводу cout
#define повернути return
#define та >>
#define іЩе <<
#define кінецьРядка endl
#define прогалина " "
#define оператор operator
#define додавання +
#define віднімання -
#define збільшенняНаОдин ++
#define зменшенняНаОдин --
#define порівняння ==
#define присвоєння =
#define я this
#define і ,
#define приятель friend
#define аТакож &&
#define відкриваючаФігурнаДужка {
#define закриваючаФігурнаДужка }
#define відкриваючаКруглаДужка (
#define закриваючаКруглаДужка )
#define відкриваючаКвадратнаДужка [
#define закриваючаКвадратнаДужка ]
#define поМодулю %
#define множення *
#define ділення /
#define наступне :
#define маєНаступне ::
#define кінецьФрази ;
#define головнаФункція main
#define нуль 0
#define один 1
#define два 2
#define три 3
#define чотири 4
#define пьять 5
#define шість 6
#define сім 7
#define вісім 8
#define девьять 9
#define крапка .
#define система system
#define рядок(а) (#а)
#define константа const
#define косинусУМінусПершійСтепені acos
#define отриматиДескриптор GetDC
#define отриматиВікноКонсолі GetConsoleWindow
#define створитиРучку CreatePen
#define посунутисьДо MoveToEx
#define лініяДо LineTo
#define типДескриптор HDC
#define типРучка HPEN
#define вибратиОбьєкт SelectObject
#define товстийТипРучки PS_SOLID
#define білийКолір RGB(255,255,255)
#define синус sin
#define косинус cos
};

константа дійснийТип Пі присвоєння два множення косинусУМінусПершійСтепені відкриваючаКруглаДужка нуль закриваючаКруглаДужка кінецьФрази

клас Кут відкриваючаФігурнаДужка
захищені наступне
цілийТип градуси і хвилини кінецьФрази
порожнеча перевіркаНаКорректність відкриваючаКруглаДужка закриваючаКруглаДужка відкриваючаФігурнаДужка
градуси = відкриваючаКруглаДужка градуси поМодулю 360 додавання 360 закриваючаКруглаДужка поМодулю 360 кінецьФрази
хвилини = відкриваючаКруглаДужка хвилини поМодулю 100 додавання 100 закриваючаКруглаДужка поМодулю 100 кінецьФрази
закриваючаФігурнаДужка
публічні наступне
Кут відкриваючаКруглаДужка закриваючаКруглаДужка відкриваючаФігурнаДужка
градуси присвоєння хвилини присвоєння нуль кінецьФрази
закриваючаФігурнаДужка
Кут відкриваючаКруглаДужка цілийТип ціле закриваючаКруглаДужка відкриваючаФігурнаДужка
градуси присвоєння ціле поМодулю 360 кінецьФрази
перевіркаНаКорректність відкриваючаКруглаДужка закриваючаКруглаДужка кінецьФрази
закриваючаФігурнаДужка
Кут відкриваючаКруглаДужка дійснийТип будьЯкийКут закриваючаКруглаДужка відкриваючаФігурнаДужка
градуси присвоєння цілийТип відкриваючаКруглаДужка будьЯкийКут закриваючаКруглаДужка поМодулю 360 кінецьФрази
хвилини присвоєння цілийТип відкриваючаКруглаДужка будьЯкийКут множення 100 закриваючаКруглаДужка поМодулю 100 кінецьФрази
перевіркаНаКорректність відкриваючаКруглаДужка закриваючаКруглаДужка кінецьФрази
закриваючаФігурнаДужка
порожнеча ввідКута відкриваючаКруглаДужка закриваючаКруглаДужка відкриваючаФігурнаДужка
потікКонсоліДляВводу та градуси та хвилини кінецьФрази
перевіркаНаКорректність відкриваючаКруглаДужка закриваючаКруглаДужка кінецьФрази
закриваючаФігурнаДужка
порожнеча вивідКута відкриваючаКруглаДужка закриваючаКруглаДужка відкриваючаФігурнаДужка
потікКонсоліДляВиводу іЩе градуси іЩе прогалина іЩе хвилини іЩе кінецьРядка кінецьФрази
закриваючаФігурнаДужка
дійснийТип вРадіанах відкриваючаКруглаДужка закриваючаКруглаДужка відкриваючаФігурнаДужка
повернути відкриваючаКруглаДужка градуси додавання хвилини ділення 100.0 закриваючаКруглаДужка ділення 360.0 множення відкриваючаКруглаДужка 2 множення Пі закриваючаКруглаДужка кінецьФрази
закриваючаФігурнаДужка
Кут оператор додавання відкриваючаКруглаДужка Кут інший закриваючаКруглаДужка відкриваючаФігурнаДужка
повернути Кут відкриваючаКруглаДужка відкриваючаКруглаДужка я->вРадіанах відкриваючаКруглаДужка закриваючаКруглаДужка
додавання інший крапка вРадіанах відкриваючаКруглаДужка закриваючаКруглаДужка закриваючаКруглаДужка
ділення відкриваючаКруглаДужка два множення Пі закриваючаКруглаДужка множення 360 закриваючаКруглаДужка кінецьФрази
закриваючаФігурнаДужка
приятель Кут оператор віднімання відкриваючаКруглаДужка Кут і Кут закриваючаКруглаДужка кінецьФрази
Кут оператор збільшенняНаОдин відкриваючаКруглаДужка закриваючаКруглаДужка відкриваючаФігурнаДужка
відкриваючаКруглаДужка градуси закриваючаКруглаДужка збільшенняНаОдин;
перевіркаНаКорректність відкриваючаКруглаДужка закриваючаКруглаДужка кінецьФрази
повернути* я кінецьФрази
закриваючаФігурнаДужка
приятель Кут оператор зменшенняНаОдин відкриваючаКруглаДужка Кут закриваючаКруглаДужка кінецьФрази
Кут оператор присвоєння відкриваючаКруглаДужка Кут інший закриваючаКруглаДужка відкриваючаФігурнаДужка
градуси присвоєння інший крапка градуси кінецьФрази
хвилини присвоєння інший крапка хвилини кінецьФрази
закриваючаФігурнаДужка
Кут оператор порівняння відкриваючаКруглаДужка Кут інший закриваючаКруглаДужка відкриваючаФігурнаДужка
повернути градуси порівняння інший крапка градуси аТакож хвилини порівняння інший крапка хвилини кінецьФрази
закриваючаФігурнаДужка
порожнеча намалювати відкриваючаКруглаДужка закриваючаКруглаДужка відкриваючаФігурнаДужка
типДескриптор дескриптор присвоєння отриматиДескриптор відкриваючаКруглаДужка отриматиВікноКонсолі відкриваючаКруглаДужка закриваючаКруглаДужка закриваючаКруглаДужка кінецьФрази
типРучка ручка присвоєння створитиРучку відкриваючаКруглаДужка товстийТипРучки і один і
білийКолір закриваючаКруглаДужка кінецьФрази
вибратиОбьєкт відкриваючаКруглаДужка дескриптор і ручка закриваючаКруглаДужка кінецьФрази
посунутисьДо відкриваючаКруглаДужка дескриптор і 100 і нуль і нуль закриваючаКруглаДужка кінецьФрази
лініяДо відкриваючаКруглаДужка дескриптор і 100 і 200 закриваючаКруглаДужка кінецьФрази
посунутисьДо відкриваючаКруглаДужка дескриптор і нуль і 100 і нуль закриваючаКруглаДужка кінецьФрази
лініяДо відкриваючаКруглаДужка дескриптор і 200 і 100 закриваючаКруглаДужка кінецьФрази
посунутисьДо відкриваючаКруглаДужка дескриптор і 100 і 100 і нуль закриваючаКруглаДужка кінецьФрази
лініяДо відкриваючаКруглаДужка дескриптор і
100 додавання косинус відкриваючаКруглаДужка вРадіанах відкриваючаКруглаДужка закриваючаКруглаДужка закриваючаКруглаДужка множення 100 і
100 віднімання синус відкриваючаКруглаДужка вРадіанах відкриваючаКруглаДужка закриваючаКруглаДужка закриваючаКруглаДужка множення 100
закриваючаКруглаДужка кінецьФрази

закриваючаФігурнаДужка
закриваючаФігурнаДужка;

Кут оператор віднімання відкриваючаКруглаДужка Кут неЯ і Кут інший закриваючаКруглаДужка відкриваючаФігурнаДужка
повернути Кут відкриваючаКруглаДужка відкриваючаКруглаДужка неЯ крапка вРадіанах відкриваючаКруглаДужка закриваючаКруглаДужка віднімання
інший крапка вРадіанах відкриваючаКруглаДужка закриваючаКруглаДужка закриваючаКруглаДужка ділення відкриваючаКруглаДужка два множення Пі закриваючаКруглаДужка
множення 360 закриваючаКруглаДужка кінецьФрази
закриваючаФігурнаДужка

Кут оператор зменшенняНаОдин відкриваючаКруглаДужка Кут неЯ закриваючаКруглаДужка відкриваючаФігурнаДужка
відкриваючаКруглаДужка неЯ закриваючаКруглаДужка зменшенняНаОдин кінецьФрази
неЯ крапка перевіркаНаКорректність відкриваючаКруглаДужка закриваючаКруглаДужка кінецьФрази
повернути неЯ кінецьФрази
закриваючаФігурнаДужка

клас Сектор наступне публічні Кут відкриваючаФігурнаДужка
захищені наступне
дійснийТип радіус кінецьФрази
публічні наступне
Сектор відкриваючаКруглаДужка закриваючаКруглаДужка
наступне Кут відкриваючаКруглаДужка закриваючаКруглаДужка
відкриваючаФігурнаДужка
радіус присвоєння нуль кінецьФрази
закриваючаФігурнаДужка
Сектор відкриваючаКруглаДужка цілийТип цілеЧисло і дійснийТип радіусНовий закриваючаКруглаДужка
наступне Кут відкриваючаКруглаДужка цілеЧисло закриваючаКруглаДужка
відкриваючаФігурнаДужка
радіус присвоєння радіусНовий кінецьФрази
закриваючаФігурнаДужка
Сектор відкриваючаКруглаДужка дійснийТип будьЯкийКут і дійснийТип радіусНовий закриваючаКруглаДужка
наступне Кут відкриваючаКруглаДужка будьЯкийКут закриваючаКруглаДужка
відкриваючаФігурнаДужка
радіус присвоєння радіусНовий кінецьФрази
закриваючаФігурнаДужка
дійснийТип площа відкриваючаКруглаДужка закриваючаКруглаДужка відкриваючаФігурнаДужка
повернути радіус множення радіус множення Пі множення Кут маєНаступне вРадіанах відкриваючаКруглаДужка закриваючаКруглаДужка ділення
відкриваючаКруглаДужка два множення Пі закриваючаКруглаДужка кінецьФрази
закриваючаФігурнаДужка
закриваючаФігурнаДужка;

цілийТип головнаФункція відкриваючаКруглаДужка закриваючаКруглаДужка відкриваючаФігурнаДужка
статичний Кут оБожеХтоПридумавТакеЗавданняСтворитиСтатичнийОбьєктДаногоТипуЯкщоВТипуНеМожеБутиСтатичнихОбьєктівАТакіМожутьБутиТількиВКласів присвоєння
Кут відкриваючаКруглаДужка 50 закриваючаКруглаДужка і
жахіттяПросто присвоєння Кут відкриваючаКруглаДужка 22.09 закриваючаКруглаДужка кінецьФрази
потікКонсоліДляВиводу іЩе оБожеХтоПридумавТакеЗавданняСтворитиСтатичнийОбьєктДаногоТипуЯкщоВТипуНеМожеБутиСтатичнихОбьєктівАТакіМожутьБутиТількиВКласів.вРадіанах відкриваючаКруглаДужка закриваючаКруглаДужка
іЩе прогалина іЩе жахіттяПросто крапка вРадіанах відкриваючаКруглаДужка закриваючаКруглаДужка іЩе кінецьРядка кінецьФрази
Кут хтоЗнаЧомуЦейОбьєктДинамічнийАле_ присвоєння Кут відкриваючаКруглаДужка закриваючаКруглаДужка кінецьФрази
хтоЗнаЧомуЦейОбьєктДинамічнийАле_ крапка ввідКута відкриваючаКруглаДужка закриваючаКруглаДужка кінецьФрази
хтоЗнаЧомуЦейОбьєктДинамічнийАле_ крапка вивідКута відкриваючаКруглаДужка закриваючаКруглаДужка кінецьФрази
хтоЗнаЧомуЦейОбьєктДинамічнийАле_ крапка намалювати відкриваючаКруглаДужка закриваючаКруглаДужка кінецьФрази
Кут масивКутівДеЗначенняПрисвоюютьсяПриСтворенні відкриваючаКвадратнаДужка два закриваючаКвадратнаДужка присвоєння відкриваючаФігурнаДужка
Кут відкриваючаКруглаДужка 1. закриваючаКруглаДужка і
Кут відкриваючаКруглаДужка 20 закриваючаКруглаДужка
закриваючаФігурнаДужка кінецьФрази
Сектор ващєКльовийСектор присвоєння Сектор відкриваючаКруглаДужка 19.5 і 10 закриваючаКруглаДужка кінецьФрази
потікКонсоліДляВиводу іЩе ващєКльовийСектор крапка площа відкриваючаКруглаДужка закриваючаКруглаДужка іЩе кінецьРядка кінецьФрази
система відкриваючаКруглаДужка рядок(pause) закриваючаКруглаДужка кінецьФрази
повернути нуль кінецьФрази
закриваючаФігурнаДужка