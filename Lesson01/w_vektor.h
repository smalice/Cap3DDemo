#ifndef __W_VEKTOR__
#define __W_VEKTOR__

#define _USE_MATH_DEFINES
#include <math.h>

#include "w_point.h"

template <class T, int n>
class W_Vektor { 

		W_Point<T,n> top;

	public:
		
		W_Vektor() {};

		W_Vektor(const T* src)
			{
				memcpy(top.pnt,src,n*sizeof(T));
			};

		W_Vektor(W_Point<T,n> &punkt)
		{
			memcpy(top.pnt,punkt.pnt,n*sizeof(T));
		};

		W_Vektor(W_Vektor<T,n> &vek)
		{
			memcpy(top.pnt,vek.top.pnt,n*sizeof(T));
		};

	virtual	~W_Vektor(void) {};
	};


template <class T>
class W_Vektor3D : public W_Vektor<T,3> {		
		

	public:
		W_Point3D<T> top;
		
		W_Vektor3D() 
		{
			top.Set(0,0,0);
		};

		W_Vektor3D(const T* src)
			{
				top.Set(src);
			};

		W_Vektor3D(const T& xx,const T& yy,const T& zz)
			{ 
				top.Set(xx,yy,zz);
			};

		W_Vektor3D(const W_Point3D<T> &punkt)
		{
			top.Set(punkt[0],punkt[1],punkt[2]);
		};

		W_Vektor3D(const W_Vektor3D<T> &vek)
		{
			//memcpy(top.pnt,vek.top.pnt,3*sizeof(T));
			top.Set(vek[0],vek[1],vek[2]);
		};

		W_Vektor3D<T>& operator=(const W_Vektor3D<T> &vek)
		{
			top.Set(vek[0],vek[1],vek[2]);
			return *this;
		};

		void Set(const T& X,const T& Y,const T& Z)
			{
				top.Set(X,Y,Z); 
			};

		void Set(const T* src)
			{
				top.Set(src[0],src[1],src[2]); 
			};

		void SetUV(const T& UU,const T& VV)
			{
				this->top.SetUV(UU,VV);
			};

		T& operator[] (int i)
		{
			return top[i];
		};

		const T& operator[] (int i) const
		{
			return top[i];
		};

		T* Get()
		{
			return &top.pnt[0];
		};

		void GetXYZ(T &xx, T &yy, T &zz)
			{
				top.GetXYZ(xx,yy,zz);
			};

		const bool operator == (const W_Vektor3D<T>& v) const
		{
			return (v[0]==top[0] && v[1]==top[1] && v[2]==top[2]);
		};

		const bool operator != (const W_Vektor3D<T>& v) const
		{
			return !(v==*this);
		};

		T SqrLength() const
			{
				return top[0]*top[0]+top[1]*top[1]+top[2]*top[2];
			};

		T Length() const
			{
				return (T)(sqrt(SqrLength()));
			};

		W_Vektor3D<T> CrossProd(const W_Vektor3D<T> &vek) const //perp to both of vectors
			{
				return W_Vektor3D<T>(top[1]*vek[2]-top[2]*vek[1],
					top[2]*vek[0]-top[0]*vek[2],
					top[0]*vek[1]-top[1]*vek[0]);
			};

		W_Vektor3D<T>& Normalize() //normalise
			{
				return *this /= this->Length();
			};

		void GetNormalized() //normalise
			{
				//top.Set( top[0]/Length() , top[1]/Length() , top[2]/Length() );
				(*this) /= Length();
			};

		const T Dot( const W_Vektor3D<T> &vek) const
			{
				return top[0]*vek[0]+top[1]*vek[1]+top[2]*vek[2];
			};

		int Angle(W_Vektor3D<T> &vek)
			{
				int u;
				float temp=acos( Scalar(vek)/( Length()*vek.Length() ) );
				u=int(temp*180/M_PI);
				return u;
			};

		const W_Vektor3D<T> operator - () const
		{
			return W_Vektor3D<T>(-top[0],-top[1],-top[2]);
		};

		W_Vektor3D<T>& operator+=(const W_Vektor3D<T> &vec)
		{
			top[0]+= vec[0];
			top[1]+= vec[1];
			top[2]+= vec[2];
			return *this;
		};

		W_Vektor3D<T>& operator-=(const W_Vektor3D<T> &vec)
		{
			top[0]-= vec[0];
			top[1]-= vec[1];
			top[2]-= vec[2];
			return *this;
		};

		W_Vektor3D<T>& operator+=(const T& c)
		{
			top[0]+= c;
			top[1]+= c;
			top[2]+= c;
			return *this;
		};

		W_Vektor3D<T>& operator-=(const T& c)
		{
			top[0]-= c;
			top[1]-= c;
			top[2]-= c;
			return *this;
		};

		W_Vektor3D<T>& operator*=(const T& c)
		{
			top[0]*= c;
			top[1]*= c;
			top[2]*= c;
			return *this;
		};

		W_Vektor3D<T>& operator/=(const T& c)
		{
			top[0]/= c;
			top[1]/= c;
			top[2]/= c;
			return *this;
		};

		W_Vektor3D<T> operator+(const W_Vektor3D<T> &vec) const
		{
			W_Vektor3D<T> temp(*this);
			temp += vec;
			return temp;
		};

		W_Vektor3D<T> operator-(const W_Vektor3D<T> &vec) const
		{
			W_Vektor3D<T> temp(*this);
			temp -= vec;
			return temp;
		};

		W_Vektor3D<T> operator+(const T& c) const
		{
			W_Vektor3D<T> temp(*this);
			temp += c;
			return temp;
		};

		W_Vektor3D<T> operator-(const T& c) const
		{
			W_Vektor3D<T> temp(*this);
			temp -= c;
			return temp;
		};

		W_Vektor3D<T> operator*(const T& c) const
		{
			W_Vektor3D<T> temp(*this);
			temp *= c;
			return temp;
		};

		friend inline const W_Vektor3D<T> operator * (const T& c, const W_Vektor3D<T>& v)
		{
			return v*s;
		};

		W_Vektor3D<T> operator/(const T& c) const
		{
			W_Vektor3D<T> temp(*this);
			temp /= c;
			return temp;
		};

	/*	friend inline const Vektor3D<T> operator * (const T& s, const Vektor3D<T>& v)
		{
			return v*s;
		};*/
	};

#endif // __W_VEKTOR__