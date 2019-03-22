/**
* @file		BaseManager.h
* @brief	マネージャの基底となるクラス
* @author	小山智也
* @date		2019/03/19
*/
#pragma once

#include "../Windows/Windows.h"

class Systems;
class Interface {

public:
	Interface(Systems* systems) { _systems = systems; }
	virtual ~Interface() {}

	Systems* GetSystems() { return _systems; }

	virtual HRESULT Init() = 0;
	virtual void Uninit() {}
	virtual void Update() {}
	virtual void Draw()   {}

protected:
	Systems* _systems;
};


template<class Child>
class BaseManager : public Interface
{

public:
	BaseManager(Systems* systems) : Interface(systems) {}
	virtual ~BaseManager(void) { obj_.clear(); }


protected:
	virtual void Add(Child* obj)
	{
		obj_.emplace_back(obj);
	}

	void RemovePtr(Child* obj)
	{
		RemoveVectorPtr(obj_, obj);
	}

	void Remove(Child* obj)
	{
		RemoveVector(obj_, obj);
	}

	std::vector<Child*> obj_;
};