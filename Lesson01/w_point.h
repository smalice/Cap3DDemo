#ifndef __W_POINT__
#define __W_POINT__

template <class T, int n>
class W_Point { 
		T pnt[n];
	
	public:
		
		W_Point(){};

		W_Point(const T* src)
			{
				memcpy(pnt,src,n*sizeof(T));
			};

		W_Point(const W_Point<T,n> &punkt)
			{
				memcpy(pnt,punkt.pnt,n*sizeof(T));
			};
/*
		Point<T,n> operator+(const T c)
			{
				Point<T,n> temp;
				for (int i=0; i<n; i++)
					temp.pnt[i] = pnt[i] + c;
				return temp;
			};

		Point<T,n> operator*(const T c)
			{
				Point<T,n> temp;
				for (int i=0; i<n; i++)
					temp.pnt[i] = pnt[i] * c;
				return temp;
			};

		Point<T,n>  operator/(const T c)
			{
				Point<T,n>  temp;
				for (int i=0; i<n; i++)
					temp.pnt[i] = T(pnt[i] / c);
				return temp;
			};

		Point<T,n> operator+(const Point<T,n> &p)
		{
			Point<T,n> temp;
			for (int i=0; i<n; i++)
				temp.pnt[i] = pnt[i] + p.pnt[i];
			return temp;
		};

		Point<T,n> operator-(const Point<T,n> &p)
		{
			Point<T,n> temp;
			for (int i=0; i<n; i++)
				temp.pnt[i] = pnt[i] - p.pnt[i];
			return temp;
		};
*/
	virtual 
		~W_Point(void){};
};

template <class T>
class W_Point3D : public W_Point<T,3> {	
		

	public:
		T pnt[3];
		T U;
		T V;

		W_Point3D(){};
		
		W_Point3D(const W_Point3D<T> &punkt) 
			{
				memcpy(pnt,punkt.pnt,3*sizeof(T));
			};

		W_Point3D(const T& xx,const T& yy,const T& zz)
			{
				pnt[0]=xx; pnt[1]=yy; pnt[2]=zz; 
			};

		W_Point3D(const T* src)
			{
				memcpy(pnt,src,3*sizeof(T));
			};

		W_Point3D<T>& operator=(const W_Point3D<T> &punkt)
		{
			memcpy(pnt, punkt.pnt, 3*sizeof(T));
			return *this;
		};

		void Set(const T& xx,const T& yy,const T& zz)
			{
				pnt[0]=xx;
				pnt[1]=yy;
				pnt[2]=zz;
			};

		void SetUV(const T& UU,const T& VV)
			{
				U = UU;
				V = VV;
			};

		void Set(const T* src)
			{
				pnt[0]=src[0];
				pnt[1]=src[1];
				pnt[2]=src[2];
			};

		T& operator[] (int i)
		{
			return pnt[i];
		};

		const T& operator[] (int i) const
		{
			return pnt[i];
		};

		T* Get()
		{
			return &pnt[0];
		};

		void GetXYZ(T &xx, T &yy, T &zz)
			{
				xx = pnt[0];
				yy = pnt[1];
				zz = pnt[2];
			};

		W_Point3D<T>& operator+=(const W_Point3D<T> &punkt)
		{
			pnt[0]+= punkt[0];
			pnt[1]+= punkt[1];
			pnt[2]+= punkt[2];
			return *this;
		};

		W_Point3D<T>& operator-=(const W_Point3D<T> &punkt)
		{
			pnt[0]-= punkt[0];
			pnt[1]-= punkt[1];
			pnt[2]-= punkt[2];
			return *this;
		};

		W_Point3D<T>& operator+=(const T& c)
		{
			pnt[0]+= c;
			pnt[1]+= c;
			pnt[2]+= c;
			return *this;
		};

		W_Point3D<T>& operator-=(const T& c)
		{
			pnt[0]-= punkt[0];
			pnt[1]-= punkt[1];
			pnt[2]-= punkt[2];
			return *this;
		};

		W_Point3D<T>& operator*=(const T& c)
		{
			pnt[0]*= c;
			pnt[1]*= c;
			pnt[2]*= c;
			return *this;
		};

		W_Point3D<T>& operator/=(const T& c)
		{
			pnt[0]/= punkt[0];
			pnt[1]/= punkt[1];
			pnt[2]/= punkt[2];
			return *this;
		};

		W_Point3D<T> operator+(const W_Point3D<T> &punkt) const
		{
			W_Point3D<T> temp(*this);
			temp += punkt;
			return temp;
		};

		W_Point3D<T> operator-(const W_Point3D<T> &punkt) const
		{
			W_Point3D<T> temp(*this);
			temp -= punkt;
			return temp;
		};

		W_Point3D<T> operator+(const T& c) const
			{
				W_Point3D<T> temp(*this);
				temp += c;
				return temp;
			};

		W_Point3D<T> operator-(const T& c) const
			{
				W_Point3D<T> temp(*this);
				temp -= c;
				return temp;
			};

		W_Point3D<T> operator*(const T& c) const
			{
				W_Point3D<T> temp(*this);
				temp *= c;
				return temp;
			};

		W_Point3D<T> operator/(const T& c) const
			{
				W_Point3D<T> temp(*this);
				temp /= c;
				return temp;
			};

		T SqrDistance(const W_Point3D<T>& punkt)
		{
			return pnt[0]*pnt[0]+pnt[1]*pnt[1]+pnt[2]*pnt[2];
		};
	
		T Distance(const W_Point3D<T>& punkt)
		{
			return (T)(sqrt(SqrDistance(punkt)));
		};
};


#endif // __W_POINT__