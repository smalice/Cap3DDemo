#include "scenenode.h"
#include <windows.h>		// Header File For Windows
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>	
#include "3DObject.h"

SceneNode::SceneNode()
{
}

void SceneNode::Update(double dt)
{
	this->time_f = dt;
	this->localSimulate();
	for (int i=0; i<arr.no_elem; i++)
			arr[i]->Update(dt);
}

void SceneNode::Render()
{
	glPushMatrix();	
		this->local.multMatrix();
		this->localRender();
		for(int i=0; i<arr.no_elem; i++)
			arr[i]->Render();
	glPopMatrix();
}

void SceneNode::Init()
{
	this->localInit();
	for(int i=0; i<arr.no_elem; i++)
		arr[i]->Init();
}

void SceneNode::Add(SceneNode *newchild)
{
	arr.NewElem(newchild);
}

void SceneNode::Add(SceneNode *newchild, GLuint texObj)
{
	arr.NewElem(newchild);
	newchild->m_textureObjectOne = texObj;
}

void SceneNode::LoadModel(string myfile)
{
	ModelloPtr = new C3DModel();
	ModelloPtr->ProcessFile(myfile);
//	cout << "File Loaded" << endl;
	int nobj = ModelloPtr->GetObjNumber();

	for (int i = 0; i < nobj; i++)
	{
		C3DObject *ObjectPtr;
		ObjectPtr = ModelloPtr->GetObjectW(i);
		ObjectPtr->UseTrasform();
	}
		
	///////////////
	MyList = glGenLists(1);
	glNewList(MyList, GL_COMPILE);
	DrawModel();
	glEndList();
}

void SceneNode::DrawModel()
{
	glBindTexture(GL_TEXTURE_2D, m_textureObjectOne);

	int nobj = ModelloPtr->GetObjNumber();

	for (int i = 0; i < nobj; i++)
	{
		C3DObject *ObjectPtr;
		ObjectPtr = ModelloPtr->GetObjectW(i);
		int nfaces = ObjectPtr->faces.size();
		
		for(int face = 0; face < nfaces; face++)
		{
			C3DFace *FacePtr;
			FacePtr = &ObjectPtr->faces[face];
			int A, B, C;
			A = FacePtr->A;
			B = FacePtr->B;
			C = FacePtr->C;

			///////////////////////
			W_Vektor3D<float> a_pro(ObjectPtr->vertices[C][0]-ObjectPtr->vertices[A][0],ObjectPtr->vertices[C][1]-ObjectPtr->vertices[A][1],ObjectPtr->vertices[C][2]-ObjectPtr->vertices[A][2]);
			W_Vektor3D<float> b_pro(ObjectPtr->vertices[C][0]-ObjectPtr->vertices[B][0],ObjectPtr->vertices[C][1]-ObjectPtr->vertices[B][1],ObjectPtr->vertices[C][2]-ObjectPtr->vertices[B][2]);
			W_Vektor3D<float> cros_pro;
			cros_pro = a_pro.CrossProd(b_pro);
			cros_pro.GetNormalized();
			glNormal3f(cros_pro[0]*norm_dir,cros_pro[1]*norm_dir,cros_pro[2]*norm_dir);
			///////////////////

			glBegin(GL_TRIANGLES);
				//glTexCoord2f(ObjectPtr->texturePoints[A][0],ObjectPtr->texturePoints[A][1]);
				glTexCoord2f(ObjectPtr->vertices[A].top.U,ObjectPtr->vertices[A].top.V);
				glVertex3f( trX+ObjectPtr->vertices[A][0]/mScale, trY+ObjectPtr->vertices[A][1]/mScale, trZ+ObjectPtr->vertices[A][2]/mScale);
				//glTexCoord2f(ObjectPtr->texturePoints[B][0],ObjectPtr->texturePoints[B][1]);
				glTexCoord2f(ObjectPtr->vertices[B].top.U,ObjectPtr->vertices[B].top.V);
				glVertex3f( trX+ObjectPtr->vertices[B][0]/mScale, trY+ObjectPtr->vertices[B][1]/mScale, trZ+ObjectPtr->vertices[B][2]/mScale);
				//glTexCoord2f(ObjectPtr->texturePoints[C][0],ObjectPtr->texturePoints[C][1]);
				glTexCoord2f(ObjectPtr->vertices[C].top.U,ObjectPtr->vertices[C].top.V);
				glVertex3f( trX+ObjectPtr->vertices[C][0]/mScale, trY+ObjectPtr->vertices[C][1]/mScale, trZ+ObjectPtr->vertices[C][2]/mScale);
			glEnd();
		}
	}

	

}

void SceneNode::LoadTexture(char * tgafile)
{	
	m_textureOne = new CTargaImage;
	// load texture image data
	m_textureOne->Load(tgafile);
	// bind the texture object
	glBindTexture(GL_TEXTURE_2D, m_textureObjectOne);
	// minimum required to set the min and mag texture filters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// now that the texture object is bound, specify a texture for it
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_textureOne->GetWidth(), m_textureOne->GetHeight(),
				 0, GL_RGB, GL_UNSIGNED_BYTE, m_textureOne->GetImage());
}