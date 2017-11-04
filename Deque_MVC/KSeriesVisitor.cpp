#pragma once
#include "stdafx.h"
#include "KSeriesVisitor.h"
#include "TV_Series.h"
#include <list>
#include <string>

//--------------------------------------------------

void Sum :: Visit(Season& par) {
	seasons += par.GetSeas();
}

void Sum::Visit(Episods& par) {
	episods += par.GetEpisods();
}
//-------------------------------------------------
void toString::Visit(Season & num) {
	str += ' ';
	str += std::to_string(num.GetSeas());
}

void toString::Visit(Episods & num) {
	str += ' ';
	str += std::to_string(num.GetEpisods());
}
