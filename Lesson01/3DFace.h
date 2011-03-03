// 3DFace.h: interface for the C3DFace class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_3DFACE_H__INCLUDED_)
#define AFX_3DFACE_H__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class C3DFace
{
public:
	C3DFace();
	C3DFace(int a, int b, int c) : A(a), B(b), C(c) {}
	int A, B, C;
};

#endif // !defined(AFX_3DFACE_H__INCLUDED_)
