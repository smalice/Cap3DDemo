#include "LogoNode.h"

LogoNode::LogoNode()
{
}

void LogoNode::localInit()
{
	angle=0.0;
	degree = 0.1f;
	mScale = 0.5f;
	trX = 0.0f;
	trY = 0.0f;
	trZ = 0.0f;
	norm_dir = -1;
	LoadModel("3DFocusGroupLogo2.3ds");
	//LoadTexture("Nude1024.tga");
	//LoadTexture("Water.tga",1);
	//	glBindTexture(GL_TEXTURE_2D, m_textureObjectOne);

	angle=0.0;
	Degree = 0.0f;
}

void LogoNode::localRender()
{
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 1.0f);
	glCallList(MyList);
	glPopMatrix();
}

void LogoNode::localSimulate()
{
		local.rotate(20*this->time_f,0.0,1.0,0.0);
}
