#include "w_vektor.h"
#include "w_matrix.h"

W_Matrix::W_Matrix()
{
	//identity matrix
	C[0][0] = 1;
	C[1][1] = 1;
	C[2][2] = 1;
}

W_Matrix::W_Matrix( const W_Vektor3D<float>& c0, const W_Vektor3D<float>& c1, const W_Vektor3D<float>& c2 )
{
	C[0] = c0;
	C[1] = c1;
	C[2] = c2;
}

W_Vektor3D<float>& W_Matrix::operator [] ( long i )
{
	return C[i];
}

//compare
const bool W_Matrix::operator == ( const W_Matrix& m ) const
{
	return C[0]==m.C[0] && C[1]==m.C[1] && C[2]==m.C[2];
}

const bool W_Matrix::operator != ( const W_Matrix& m ) const
{
	return !(m == *this);
}

//assign
const W_Matrix& W_Matrix::operator = ( const W_Matrix& m )
{
	C[0] = m.C[0];
	C[1] = m.C[1];
	C[2] = m.C[2];
	return *this;
}

//increment
const W_Matrix& W_Matrix::operator +=( const W_Matrix& m )
{
	C[0] += m.C[0];
	C[1] += m.C[1];
	C[2] += m.C[2];
	return *this;
}

//decrement
const W_Matrix& W_Matrix::operator -=( const W_Matrix& m ) 
{
	C[0] -= m.C[0];
	C[1] -= m.C[1];
	C[2] -= m.C[2];
	return *this;
}

//self-multiply by a scalar
const W_Matrix& W_Matrix::operator *= ( float& s )
{
	C[0] *= s;
	C[1] *= s;
	C[2] *= s;
	return *this;
}

//self-multiply by a matrix
const W_Matrix& W_Matrix::operator *= ( const W_Matrix& m )
{
	//NOTE: don't change the columns
	//in the middle of the operation
	W_Matrix temp = (*this);
	C[0] = temp * m.C[0];
	C[1] = temp * m.C[1];
	C[2] = temp * m.C[2];
	return *this;
}

//add
const W_Matrix W_Matrix::operator + ( const W_Matrix& m ) const
{
	return W_Matrix( C[0] + m.C[0], C[1] + m.C[1], C[2] + m.C[2] );
}

//subtract
const W_Matrix W_Matrix::operator - ( const W_Matrix& m ) const
{
	return W_Matrix( C[0] - m.C[0], C[1] - m.C[1], C[2] - m.C[2] );
}

//post-multiply by a scalar
const W_Matrix W_Matrix::operator * ( float& s ) const
{
	return W_Matrix( C[0]*s, C[1]*s, C[2]*s );
}

//post-multiply by a vector
const W_Vektor3D<float> W_Matrix::operator * ( const W_Vektor3D<float>& v ) const
{
	return( C[0]*v[0] + C[1]*v[1] + C[2]*v[2] );
}

	//post-multiply by a matrix
const W_Matrix W_Matrix::operator * ( const W_Matrix& m ) const
{
	return W_Matrix( (*this) * m.C[0], (*this) * m.C[1], (*this) * m.C[2] );
}

//transpose
W_Matrix W_Matrix::transpose() const
{
	//turn columns on their side
	return W_Matrix( W_Vektor3D<float>( C[0][0], C[1][0], C[2][0] ), //column 0
		W_Vektor3D<float>( C[0][1], C[1][1], C[2][1] ), //column 1
		W_Vektor3D<float>( C[0][2], C[1][2], C[2][2] ) //column 2
		);
}

//scalar determinant
float W_Matrix::determinant() const
{
	//Lang, "Linear Algebra", p. 143
	return C[0].Dot( C[1].CrossProd(C[2]) );
}
