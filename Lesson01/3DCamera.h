// 3DCamera.h: interface for the C3DCamera class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_3DCAMERA_H__INCLUDED_)
#define AFX_3DCAMERA_H__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class C3DCamera
{
public:
	C3DCamera();
	C3DCamera(W_Vektor3D<float> Position, W_Vektor3D<float> Target, float Bank, float Lens) : position(Position),
																		target(Target),
																		bank(Bank),
																		lens(Lens) {}
	W_Vektor3D<float>	position;
	W_Vektor3D<float>	target;
	float	bank, lens;
};

#endif // !defined(AFX_3DCAMERA_H__INCLUDED_)
