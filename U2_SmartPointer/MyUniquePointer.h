#pragma once
#include <iostream>
#include "MyUniquePointer.h"
//unique pointer ist ein wrapper von einem pointer der sich für die memorie mangment geschichten kümmert

/*
Problem beim UniquePointer sind die standard implementierung des Kompilers der rule of three:
Kopy konstruktor -> wenn der pointer ein scope verlässt wird er gelöscht, exisitert aber eine kopie vom pointer so wird der
Destruktor beim orginalen pointer aufgerufen und bei der kopie das auf dem selben speicherplatz pointet
und das führt zu einen undefined behavior

Assignment Operation -> UniquePointer1 = UniquePointer2 -> das problem hier ist das der originale Pointer der in UnqiuePointer1
vorhanden war, verloren geht.

*/
namespace thebettersmartpointer
{
	template <typename T>
	class MyUniquePointer
	{
	private:
		T* data;
	public:
		//Die vom compiler generierten copy constructor und copy assigment löschen um die probleme zu vermeiden die oben erwähnt worden sind
		MyUniquePointer(MyUniquePointer const&) = delete;
		MyUniquePointer& operator=(MyUniquePointer const&) = delete;
		constexpr MyUniquePointer() {} ;
		constexpr MyUniquePointer(std::nullptr_t) {} ;

		//move constructor
		MyUniquePointer(MyUniquePointer&& p)
		{
			if (this != &p)
			{
				if (data != nullptr)
				{
					delete data;
				}
				this->data = p.data;
				p.data = nullptr;
			}
		}

		//move assigment operator
		MyUniquePointer operator = (MyUniquePointer&& p)
		{
			if (this != p)
			{
				if (data != nullptr)
				{
					delete data;
				}
				this->data = p.data;
				p.data = nullptr;
			}
			return *this;
		}

		//Explicit constructor -> um zu verhindern, dass der compiler falsch castet
		explicit MyUniquePointer(T* data)
		{
			this->data = data;
		}

		//destruktor
		~MyUniquePointer()
		{
			delete data;
		}

		//Operatorüberladung
		T* operator->() const
		{
			return data;
		}

		T& operator*() const
		{
			return *data;
		}

		explicit operator bool() const
		{
			if (data != nullptr)
			{
				return true;
			}
			else
				return false;
		}
		//----//

		T* get() const
		{
			return data;

		}

		//nimmt die ownership vom gewrappten objekt weg und returned diesen und der aktuelle pointer wird null
		T* release()
		{			
			
			T* data2 = nullptr;
			std::swap(data2, data);
			return data2;

		}

		void reset()
		{
			if (this->data != nullptr)
			{
				delete this->data;
				data=nullptr;

			}
				
		}

		bool operator==(const MyUniquePointer<T>& other) const
		{
			return data == other.data;
		}

		bool operator!=(const MyUniquePointer<T>& other) const
		{
			return !(*this == other);
		}

		void swap(MyUniquePointer& data2)
		{
			if (*this != data2)
			{
				T* tmp = data2.data;
				data2.data = this->data;
				data = tmp;
			}

		}
	};
}
