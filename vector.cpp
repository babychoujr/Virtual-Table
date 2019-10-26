#include <iostream>
#include <initializer_list>
#include <string.h>
#include <algorithm>
using namespace std;

template 
	<typename T>
class Vector{
private:
	int sz; // the number of elements in this Vector
	T* buf; // the base of the array of Ts
public:
	Vector(int n){
		sz = n;
		buf = new T[n];
	}
	
	Vector(initializer_list<T> L){
		sz = L.size();
		buf = new T[sz];
		int i = 0;
		for(T item:L){
			buf[i] = item;
			i+= 1; 
		}
	}
	
	~Vector(){
		delete[] buf;
	}
	
	Vector(const Vector & v){
		sz = v.sz;
		if(sz == 0){
			buf = nullptr;
		}
		buf = new T[sz];
		for(int i = 0; i < sz; i++){
			buf[i] = v.buf[i];
		}
	}
	
	int size() const{
		return sz;
	}
	
	T & operator [] (const int i){
		if(i < 0 || i >= sz){
			throw i;
		}
		else{
			return buf[i];
		}
	}

	T operator * (const Vector & v)const{
		if(v.sz == 0 || sz == 0){
			return 0;
		}
		int dot_product = 0;
		int length = min(sz, v.sz);
		for(int i = 0; i < length; i++){
			dot_product += v.buf[i] * buf[i];
		}
		return dot_product;
	}

	Vector operator + (const Vector & v)const{
		if(v.sz >= sz){
			Vector<T> v1(v.sz);
			for(int i = 0; i < v.sz; i++){
				v1.buf[i] = v.buf[i];
			}
			for(int i = 0; i < sz; i++){
				v1.buf[i] += buf[i];
			}
			return v1;
		}
		else{
			Vector<T> v1(sz);
			for(int i = 0; i < sz; i++){
				v1.buf[i] = buf[i];
			}
			for(int i = 0; i < v.sz; i++){
				v1.buf[i] += v.buf[i];
			}
			return v1;
		}
	}

	const Vector & operator = (const Vector & v){
		if(this != &v){
			delete[] buf;
			sz = v.sz;
			buf = new T[sz];
			for(int i = 0; i < sz; i++){
				buf[i] = v.buf[i];
			}
		}
		return *this;
	}
	
	bool operator == (const Vector & v) const{
		if(v.sz != sz){
			return false;
		}
		for(int i = 0; i < sz; i++){
			if(buf[i] != v.buf[i]){
				return false;
			}
		}
		return true;
	}

	bool operator != (const Vector & v) const{
		if(v.sz != sz){
			return true;
		}
		for(int i = 0; i < sz; i++){
			if(buf[i] != v.buf[i]){
				return true;
			}
		}
		return false;
	}

	friend Vector operator *(const int n, const Vector & v){
		Vector<T> result_v(v.sz);
		result_v.sz = v.sz;
		for(int i = 0; i < result_v.sz; i++){
			result_v[i] = v.buf[i] * n;
		}
		return result_v;
	}

	friend Vector operator +(const int n, const Vector & v){
		Vector<T> result_v(v.sz);
		result_v.sz = v.sz;	
		for(int i = 0; i < result_v.sz; i++){
			result_v[i] = v.buf[i]+ n;
		}
		return result_v;
	}

	friend ostream& operator << (ostream & o, const Vector & v){
		o << "(";
		for(int i = 0; i < v.sz; ++i){
			o << v.buf[i];
			if(i != v.sz -1){
				o << ", ";
			}
		}
		o << ")\n";
		return o;
	}
		
};
