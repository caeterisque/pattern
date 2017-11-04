#include <windows.h>
#include <iostream>
#include <iterator>
#include <fstream>
#include <string>
#include <algorithm>
#include "TV_Series.h"
#include "KSeriesVisitor.h"
#include "Container.h"


using namespace std;

class Series {
public:
	Series() : deq{ new Season(4), new Episods(3), new Season(7) } {}

	~Series() {
		for (auto px : deq)
			delete px;
	}

	void PushBack(TV_series * build) {
		deq.PushBack(build);
	}

	void PopBack() {
		deq.PopBack();
	}

	int GetSumSeas() {
		Sum my_sum;
		for (auto px : deq)
			(*px).Accept(my_sum);
		return my_sum.seasons;
	}

	int GetSumEp() {
		Sum my_sum;
		for (auto px : deq)
			(*px).Accept(my_sum);
		return my_sum.episods;
	}
	string GetString() {
		toString _str;
		for (auto px : deq)
			(*px).Accept(_str);
		return _str.str;
	}

	KVector <TV_series*> deq;
};



class Subject;
template <typename T> class Controller;

//------------------------------------------------------------------------------
class Observer {
public:
	virtual ~Observer() {}
	virtual void Update(Subject * ChangedSubject) = 0;

protected:
	Observer() {}
};

//------------------------------------------------------------------------------
class Subject{
public:
	Subject() {}
	virtual ~Subject() { }

	virtual void Attach(Observer* obs) {
		_Observers.PushBack(obs);
	}

	/*virtual void Notify() {
		for (auto it = _Observers.begin(); it != _Observers.end(); ++it)
			(*it)->Update(this);
	}*/
	virtual void Notify() {
		for (auto it = _Observers.begin(); it != _Observers.end(); ++it)
			(*it)->Update(this);

	}
private:
	KVector <Observer *> _Observers;
};    

//------------------------------------------------------------------------------
template <typename T>
class DataSubject : public Subject
{
public:
	DataSubject() : Subject(), _data(T()) {}

	void ChangeData(T aData){
		_data = aData;
		Notify();
	}

	T const& GetData() const { 
		return _data; 
	}

private:
	T _data;
};
//------------------------------------------------------------------------------
template <>
class DataSubject<Series> : public Subject {
public:
	DataSubject() : Subject(), _data(Series{}) {	}

	void ChangeData(Series aData) {}

	void PushFl(HWND& hEdit) {
		char Buf[20];
		GetWindowText(hEdit, Buf, 20);
		if (Buf[0] == '\0') return ;
		std::string str = "";
		for (int i = 0; i < 10; i++)
			str += Buf[i];
		int Data = stoi(str);
		TV_series* series = new Season(Data);
		_data.PushBack(series);
		Notify();
	}

	void PushRm(HWND& hEdit) {
		char Buf[20];
		GetWindowText(hEdit, Buf, 20);
		if (Buf[0] == '\0') return ;
		std::string str = "";
		for (int i = 0; i < 10; i++)
			str += Buf[i];
		int Data = stoi(str);
		TV_series* series = new Episods(Data);
		_data.PushBack(series);
		Notify();
	}

	void PopEl(HWND* hwnd) {
		_data.PopBack();
		Notify();
	}

	void GetSumSeas(HWND* hwnd) {
		Sum s;
		for (auto px : _data.deq)
			(*px).Accept(s);
		s.DisplaySeas(*hwnd);
	}
	void GetSumEp(HWND* hwnd) {
		Sum s;
		for (auto px : _data.deq)
			(*px).Accept(s);
		s.DisplayEp(*hwnd);
	}
	string  GetData() {
		return _data.GetString();
	}

private:
	Series _data;
 
};

template <typename T>
class DataObserver : public Observer{
public:
	DataObserver(DataSubject<T> * aSubject, HWND * aEdit) : _subject(aSubject), _edit(aEdit){
		_subject->Attach(this);
	}

	virtual ~DataObserver() {}

	virtual void Update(Subject * ChangedSubject){
		std::string str = std::to_string(_subject->GetData());
		const char*  wch = str.c_str();
		SetWindowText(*_edit, wch);
	}

private:
	DataSubject<T> * _subject;
	HWND * _edit;
};


template <>
class DataObserver<Series> : public Observer {
public:
	DataObserver(DataSubject<Series> * aSubject, HWND * aEdit) : _subject(aSubject), _edit(aEdit) {
		_subject->Attach(this);
	}

	virtual ~DataObserver() {}

	virtual void Update(Subject * ChangedSubject) {
			string str = _subject->GetData();
			std::string wstr = std::string(str.begin(), str.end());
			const char*  wch = wstr.c_str();
			SetWindowText(*_edit, wch);
	}

private:
	DataSubject<Series> * _subject;
	HWND * _edit;
};

//------------------------------------------------------------------------------


template <typename T>
class ObserverForUser : public Observer {
public:
	ObserverForUser(DataSubject<T> * aSubject, HWND * aEdit, Controller<T> * aCtrl)
		: _subject(aSubject), _edit(aEdit), _ctrl(aCtrl) {
		_subject->Attach(this);
	}
	virtual ~ObserverForUser() {}

	virtual void Update(Subject * ChangedSubject) {
		if (ChangedSubject == _subject) {
			std::string str = std::to_string(_subject->GetData());
			const char*  wch = str.c_str();
			SetWindowText(*_edit, wch);
		}
	}

	virtual void SendNewData() {
		char Buf[20];
		GetWindowText(*_edit, Buf, 20);
		std::string str = "";
		for (int i = 0; i < 10; i++)
			str += Buf[i];
		double Data = stoi(str);
		_ctrl->ChangeData(Data);
	}

private:
	DataSubject<T> * _subject;
	HWND * _edit;
	Controller<T> * _ctrl;
};

template <>
class ObserverForUser<Series> : public Observer {
public:
	ObserverForUser(DataSubject<Series> * aSubject, HWND * aEdit, Controller<Series> * aCtrl)
		: _subject(aSubject), _edit(aEdit), _ctrl(aCtrl) {
		_subject->Attach(this);
	}
	virtual ~ObserverForUser() {}

	virtual void Update(Subject * ChangedSubject) {
			string str = _subject->GetData();
			std::string wstr = std::string(str.begin(), str.end());
			const char*  wch = wstr.c_str();
			SetWindowText(*_edit, wch);
	}

private:
	DataSubject<Series> * _subject;
	HWND * _edit;
	Controller<Series> * _ctrl;
};



template <typename T>
class Controller{
public:
	Controller(DataSubject<T> * aSubject) : _subject(aSubject) {}
	virtual ~Controller() {}
	virtual void ChangeData(T const& aDate){
		_subject->ChangeData(aDate);
	}

private:
	DataSubject<T> * _subject;

};

   

