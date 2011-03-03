// 3DObject.h: interface for the C3DObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_3DOBJECT_H__INCLUDED_)
#define AFX_3DOBJECT_H__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "w_vektor.h"
#include "w_matrix.h"
#include "3DFace.h"

class C3DObject
{
public:
	C3DObject();
	~C3DObject();
	void	UseTrasform();
	vector	<W_Vektor3D<float>> vertices;
	vector	<W_Vektor3D<float>> texturePoints;
	vector	<C3DFace> faces;
	W_Matrix	transform;
	float	translate[3];
};

#endif // !defined(AFX_3DOBJECT_H__INCLUDED_)
