// 3DObject.cpp: implementation of the C3DObject class.
//
//////////////////////////////////////////////////////////////////////

#include <vector>
using namespace std;

#include "w_vektor.h"
#include "w_matrix.h"
#include "3DFace.h"
#include "3DObject.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

C3DObject::C3DObject()
{

}

C3DObject::~C3DObject()
{
	vertices.clear();
	texturePoints.clear();
	faces.clear();
}

void C3DObject::UseTrasform()
{
	int vnum = vertices.size();

	for (int i = 0; i < vnum; i++)
	{
		vertices[i] = vertices[i] * transform;
	}
}
