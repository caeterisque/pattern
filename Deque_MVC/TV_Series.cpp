#include "stdafx.h"
#include "TV_Series.h"

void Season::Accept(KSeriesVisitor& v) {
	v.Visit(*this);
}
void Episods::Accept(KSeriesVisitor & v) {
	v.Visit(*this);
 }