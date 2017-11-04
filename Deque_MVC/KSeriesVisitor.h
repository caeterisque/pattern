#pragma once
#include "stdafx.h"
#include "Container.h"
#include "TV_Series.h"
#include <string>
#include <iostream>
#include <Windows.h>

using namespace std;


class TV_series;
class Season;
class Episods;
#pragma once
#include <iostream>
#include <string>
#include <vector>

class TV_series;
class Season;
class Release;


// Иерархия посетителей
class KSeriesVisitor {
public:
	KSeriesVisitor() { }

	virtual void Visit(Season&) = 0;
	virtual void Visit(Episods&) = 0;
	virtual ~KSeriesVisitor() { }
};
//---------------------------------------------------------------




class Sum : public KSeriesVisitor {
public:
	Sum() : seasons(0), episods(0) {}

	void Visit(Season & seas);
	void Visit(Episods & ep);


	void DisplaySeas(HWND hwnd) {
		string b12 = to_string(seasons);
		SetWindowText(hwnd, b12.c_str());
	}
	void DisplayEp(HWND hwnd) {
		string b12 = to_string(episods);
		SetWindowText(hwnd, b12.c_str());
	}

	int seasons;
    int episods;

};
//----------------------------------------------
class toString : public KSeriesVisitor {
public:
	toString() : str("") {}

	void Visit(Season & num);

	void Visit(Episods & num);

	void Display();

	string str;

};