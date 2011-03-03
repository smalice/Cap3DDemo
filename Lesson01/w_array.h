#ifndef __W_ARRAY__
#define __W_ARRAY__

template <class T>

class W_Array {

	T *data;
	int max_elem;

public:
	int no_elem;

	W_Array()	
	{
		no_elem=0;
		max_elem=100;
		data =new T[max_elem];
	};
	
	W_Array(int x)
	{
		no_elem=0;
		max_elem=x;
		data =new T[max_elem];
	};

	void NewElem(const T& x)
	{		
	
		if (no_elem<=max_elem)
		{data[no_elem]=x;
		no_elem++;}
	};

	/*const T GetElem(int i)
		{
			if (i<no_elem)
				return	data[i];
		};
*/
	T& operator[] (int i)
		{
			return data[i];
		};

	const T& operator[] (int i) const
		{
			return data[i];
		};

	virtual ~W_Array(void)   {};
	
};
#endif // __W_ARRAY__