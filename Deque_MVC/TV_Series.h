#pragma once
#include "KSeriesVisitor.h"
#include <iostream>

class KSeriesVisitor;

using namespace std;
// Иерархия обектов
class TV_series {
public:
	TV_series() {}
	virtual void Accept(KSeriesVisitor&) = 0;
	virtual ~TV_series() { }
};
//-------------------------------------------------------------------------
class Season : public TV_series {
private:
	unsigned int number_of_seasons;
public:
	Season() : number_of_seasons(0) {}

	Season(size_t num1) : number_of_seasons(num1) {}
	void Accept(KSeriesVisitor& v);
	void SetSeas(int a) {
		number_of_seasons = a;
	}
	unsigned int GetSeas() {
		return number_of_seasons;
	}

};
//-------------------------------------------------------------------------

class Episods : public TV_series {
private:
	int number_of_episodes;

public:
	Episods(int num1) :number_of_episodes(num1) {}
	Episods() : number_of_episodes(0) {}

	unsigned int GetEpisods() {
		return number_of_episodes;
	}
	void SetEp(int a) {
		number_of_episodes = a;
	}
	void Accept(KSeriesVisitor& v);
};


