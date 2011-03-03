#ifndef __SCENENODE__
#define __SCENENODE__

#include "w_array.h"
#include "glmatrix.h"
#include "CTargaImage.h"

#include <windows.h>		// Header File For Windows
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>	

#include <string>
using namespace std;

#include "3dModel.h"

class SceneNode {
		W_Array<SceneNode *> arr;	

	protected:
		double time_f; //the time since the last frame

		virtual void localSimulate() {};
		virtual void localRender() {};
		virtual void localInit() {};

		
		CTargaImage *m_textureOne;

	public:
		GLMatrix    local;
		C3DModel	*ModelloPtr;
		GLuint m_textureObjectOne;

		float   angle;
		float	mScale;
		float	degree, d_var;
		float	trX, trY, trZ;
		char	norm_dir;
		GLuint	MyList;

		SceneNode();

		void Render();
		void Update(double dt);
		void Init();
		void LoadModel(string myfile);
		void LoadTexture(char * tgafile);
		void DrawModel();

		void Add(SceneNode *newchild);
		void Add(SceneNode *newchild, GLuint texObj);

		void setGLMatrix(const GLMatrix& m)
		{
			local = m;
		}

		GLMatrix& getGLMatrix()
		{
			return local;
		}

		virtual 
			~SceneNode(void){};

};
#endif // __SCENENODE__