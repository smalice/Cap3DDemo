#ifndef __W_MATRIX__
#define __W_MATRIX__

#include "w_vektor.h"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class W_Matrix
{
public:
	W_Vektor3D<float> C[3]; //column vectors
public:
	W_Matrix();
	W_Matrix( const W_Vektor3D<float>& c0, const W_Vektor3D<float>& c1, const W_Vektor3D<float>& c2 );

	W_Vektor3D<float>& operator [] ( long i );
	//compare
	const bool operator == ( const W_Matrix& m ) const;

	const bool operator != ( const W_Matrix& m ) const;

	//assign
	const W_Matrix& operator = ( const W_Matrix& m );

	//increment
	const W_Matrix& operator +=( const W_Matrix& m );

	//decrement
	const W_Matrix& operator -=( const W_Matrix& m );

	//self-multiply by a scalar
	const W_Matrix& operator *= ( float& s );

	//self-multiply by a matrix
	const W_Matrix& operator *= ( const W_Matrix& m );

	//add
	const W_Matrix operator + ( const W_Matrix& m ) const;

	//subtract
	const W_Matrix operator - ( const W_Matrix& m ) const;

	//post-multiply by a scalar
	const W_Matrix operator * ( float& s ) const;

	//pre-multiply by a scalar
	friend inline const W_Matrix operator * ( float& s, const W_Matrix& m )
	{
		return m * s;
	}

	//post-multiply by a vector
	const W_Vektor3D<float> operator * ( const W_Vektor3D<float>& v ) const;

	//pre-multiply by a vector
	inline friend const W_Vektor3D<float> operator * ( const W_Vektor3D<float>& v, const W_Matrix& m )
	{
		return W_Vektor3D<float>( m.C[0].Dot(v), m.C[1].Dot(v), m.C[2].Dot(v) );
	}

	//post-multiply by a matrix
	const W_Matrix operator * ( const W_Matrix& m ) const;

	//transpose
	W_Matrix transpose() const;

	//scalar determinant
	float determinant() const;

	//matrix inverse
	const W_Matrix inverse() const;
};

#endif // !defined(__MATRIX__)
