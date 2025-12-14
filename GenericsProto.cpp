module;

#include <string>
#include <cassert>
#include<iostream>
#include <sstream>


export module Generics;

export template <typename T>

//the purpose of this class is store ANY DATATYPE
//i will use this class to develop a console Applications
class Generics
{
	public:
		Generics(T DefaultValue);
		Generics(int rows, int cols, T DefaultValue);
		Generics(const Generics<T>& Obj);//copy constructor
		virtual ~Generics();//
		//accesors
		int getCols()const;
		int getRows()const;
		T getDefValue()const;
		T getValue(int row, int col)const;
		virtual std::string ShowGrid()const;//can be overidden by another class
		//mutators
		void setValue(int row, int col, T value);
		Generics<T>& operator=(const Generics& ObjRHS);
		Generics<T>& operator++(int);
		bool operator==(const Generics& ObjRHS)const;
		template <typename F>
		friend std::ostream &operator<<(std::ostream &ObjLHS, const Generics<F> &ObjRHS);
	private:
		int _Rows;
		int _Cols;
		T** _grid;//maybe consider a std::vector 
		T _DefaultValue;
		void Alloc();
		void Dealloc();
		void Clone(const Generics<T>& Obj);
	protected:
		//helper methods
		bool IsinGrd(int row, int col)const;
		void Reset(T Value);
		//class constants
		static constexpr int DefaultCols = 300;
		static constexpr int DefaultRows = 300;
};

//=========================================public==========================================================
export template <typename T>
Generics<T>::Generics(T DefaultValue):Generics(DefaultRows, DefaultCols, DefaultValue)
{}

export template <typename T>
Generics<T>::Generics(int rows, int cols, T DefaultValue):_Rows(rows), _Cols(cols), _DefaultValue(DefaultValue)
{
	Alloc();
}

export template <typename T>
Generics<T>::Generics(const Generics<T>& Obj):Generics(Obj.getRows(), Obj.getCols(), getDefValue())
{
	if(this != &Obj)
	{
		//avoid self assignment
		this -> Clone(Obj);//clone the grid
	}
}

export template <typename T>
Generics<T>::~Generics()
{
	Dealloc();
}

export template <typename T>
int Generics<T>::getCols()const
{
	return _Cols;
}

template <typename T>
int Generics<T>::getRows()const
{
	return _Rows;
}

export template <typename T>
T Generics<T>::getValue(int row, int col)const
{
	//safety check
	const bool isIngrid = IsinGrd(row, col);
	assert(isIngrid);
	return _grid[row][col];
}
export template <typename T>
T Generics<T>::getDefValue()const
{
	return _DefaultValue;
}
export template <typename T>
std::string Generics<T>::ShowGrid()const
{
	std::stringstream ssShow;
	//ssShow<<"Data in Container: "<<std::endl;
	for(int k = 0;k<_Rows;k++)
	{
		for(int j = 0;j<_Cols;j++)
		{
			ssShow<<_grid[k][j]<<' ';
		}
		ssShow<<std::endl;
	}
	return ssShow.str();
}

export template <typename F>

std::ostream &operator<<(std::ostream &ObjLHS, const Generics<F> &ObjRHS)
{
	for(int k = 0; k< ObjRHS.getRows();k++)
	{
		for(int j = 0; j<ObjRHS.getCols();j++)
		{
			ObjLHS<<ObjRHS.getValue(k, j)<<' ';
		}
		ObjLHS<<std::endl;
	}
	return ObjLHS;
}
//=====================================================private/protected==========================================

export template <typename T>
void Generics<T>::Alloc()
{
	_grid = new T*[_Rows];
	for(int k = 0; k<_Rows;k++)
	{
		_grid[k] = new T[_Cols];
		for(int j = 0; j<_Cols; j++)
		{
			_grid[k][j] = _DefaultValue;
		}
	}
}

export template <typename T>
void Generics<T>::Dealloc()
{
	for(int k = 0; k< _Rows;k++)
	{
		delete[] _grid[k];
	}
	delete[] _grid;
	_grid = nullptr;//get rid of dangling ptr
}

template <typename T>
bool Generics<T>::IsinGrd(int row, int col)const
{
	return col>=0 && col<_Cols && row>=0 && row<_Rows;
}

export template <typename T>
void Generics<T>::Clone(const Generics<T>& Obj)
{
	assert(this->_Rows == Obj.getRows() && this->_Cols == Obj.getCols());//safety check
	for(int k = 0; k<_Rows; k++)
	{
		for(int j = 0; j< _Cols; j++)
		{
			this->_grid[k][j] = Obj.getValue(k, j);
		}
	}
}

export template <typename T>
void Generics<T>::setValue(int row, int col, T value)
{
	assert(IsinGrd(row, col));
	_grid[row][col] = value;
}
export template <typename T>
Generics<T>& Generics<T>::operator=(const Generics<T>& ObjRHS)
{
	Dealloc();
	//free the memory
	_Rows = ObjRHS.getRows();
	_Cols = ObjRHS.getCols();
	Alloc();
	Clone(ObjRHS);
	return *this;
}
export template <typename T>
bool Generics<T>::operator==(const Generics& ObjRHS)const
{
	if(_Rows != ObjRHS.getRows() || _Cols != ObjRHS.getCols())
		return false;
	if(_DefaultValue != ObjRHS.getDefValue())
		return false;
	for(int k = 0; k<_Rows;k++)
	{
		for(int j = 0;j<_Cols;j++)
		{
			if(!(_grid[k][j] == ObjRHS.getValue(k, j)))//if the opposite is true
			{
				//for some datatypes the == operator may need to be overloaded
				return false;
			}
		}
	}
	return true;//else. all fails
}
export template <typename T>
Generics<T>& Generics<T>::operator++(int)
{
	//for the future -> include a try-catch block
	for(int k = 0;k<_Rows;k++)
	{
		for(int j = 0;j<_Cols;j++)
		{
			//for some datatypes(classes) the ++ operator may need to be overloaded
			_grid[k][j]++;
		}
	}
	return *this;
}
export template <typename T>
void Generics<T>::Reset(T Value)
{
	for(int k = 0;k<_Rows;k++)
	{
		for(int j = 0;j<_Cols;j++)
			_grid[k][j] = Value;
	}
}

