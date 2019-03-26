/**
* @file		Define.h
* @brief	�萔�n
* @author	���R�q��
* @date		2019/02/24
*/
#pragma once

#pragma comment(lib, "dxguid.lib")
#include <type_traits>
#include <vector>
#include <array>
#include <fstream>
#include "Vector.h"

using std::string;
using std::ifstream;
using std::wstring;

template<typename Num>
inline Num Hf(Num n) { return (Num)(n * 0.5f); };
template<typename Num>
inline Num Qua(Num origin) { return (Num)(origin * 0.25f); };
template<typename Num>
inline Num Abs(Num origin) { return origin >= 0 ? origin : -origin; };


// ���
template<class Re>
inline bool ReleaseThis(Re& re)
{
	if (re != NULL)
	{
		re->Release();
		re = NULL;
		return true;
	}
	return false;
};

template<class Del>
inline bool DeleteThis(Del& del)
{
	if (del != nullptr)
	{
		delete del;
		del = nullptr;
		return true;
	}
	return false;
};

/* @fn		RemoveVectorPtr
* @brief	vector����erase�A&���̌�delete����
* @param	(obj)		vector
* @param	(_this)		���o���z��
* @return	���������s��		*/
template<class T, class U>
inline bool RemoveVectorPtr(T& obj, U& _this)
{
	for (auto itr = obj.begin(); itr != obj.end();)
	{
		if ((*itr) == _this)
		{
			auto temp = *itr;
			itr = obj.erase(itr);		//�z��폜
			delete temp;
			temp = nullptr;
			break;
		}
		else
		{
			itr++;
		}
	}
	if (_heapchk() != _HEAPOK)
		DebugBreak();

	obj.shrink_to_fit();
	return true;
}

/* @fn		RemoveVector
* @brief	vector����erase�Adelete�͂��Ȃ�
* @param	(obj)		vector
* @param	(_this)		���o���z��
* @return	���������s��		*/
template<class T, class U>
inline bool RemoveVector(T& obj, U& _this)
{
	for (auto itr = obj.begin(); itr != obj.end();)
	{
		if ((*itr) == _this)
		{
			itr = obj.erase(itr);		//�z��폜
			break;
		}
		else
		{
			itr++;
		}
	}

	obj.shrink_to_fit();
	return true;
}

/* @fn		Swap
* @brief	�z�����ւ�����
* @param	(obj1, obj2)	����ւ���l		*/
template<class T>
inline void Swap(T& obj1, T& obj2)
{
	T temp = obj1;
	obj1 = obj2;
	obj2 = temp;
}