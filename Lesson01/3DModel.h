// 3DModel.h: interface for the C3DModel class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_3DMODEL_H__INCLUDED_)
#define AFX_3DMODEL_H__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
using namespace std;

#include "w_vektor.h"
#include "w_matrix.h"
#include "3dCamera.h"
#include "3dsFileLoader.h"

class C3DObject;

class C3DModel : public C3dsFileLoader
{
	int iter;
public:
	enum	{NoObjects = -1};
	C3DModel() : C3dsFileLoader(), mObjectsCount(NoObjects), mStillOpen(false) {}
	bool	NewObject();
	bool	EndObject();
	bool	IsObjectWriting() const {return mStillOpen;}
	bool	AddVertex(float x, float y, float z);
	bool	AddFace(int A, int B, int C);
	bool	AddTexturePoint(float u, float v);
	bool	AddCamera(C3DCamera Camera);
	bool	SetMatrix(W_Matrix Mtx);
	bool	SetTranslation(float x, float y, float z);
	int		GetObjNumber() const {return (mObjectsCount + 1);}
	C3DObject *GetObjectW(int ObjectNumber) const {return mObjects[ObjectNumber];}
private:
	int		mObjectsCount;	// Objects counter
	bool	mStillOpen;		// If true an object creating session was opened but still not closed
	vector	<C3DObject*> mObjects;
	vector	<C3DCamera> mCameras;
protected:
	void		User3dVert(float x, float y, float z);
	void		User3dFace(unsigned short A, unsigned short B, unsigned short C, unsigned short Flags);
	void		UserCamera(float px, float py, float pz,
								   float tx, float ty, float tz,
								   float Bank, float Lens);
	void		UserMapVertex(float U, float V);
	void		UserTransformMatrix(const Transform3dsMatrix &Transform, const Translate3dsMatrix &Translate);
	void		UserChunkObj();
	void		UserEndOfFile();
};

#endif // !defined(AFX_3DMODEL_H__INCLUDED_)
