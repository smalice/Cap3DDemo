#ifndef __LOGONODE__
#define __LOGONODE__


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SceneNode.h"
 #include <math.h>

class LogoNode: public SceneNode {	
	
	float angle;
	float		Degree;
	float velocity;
public:	

		LogoNode() ;

virtual 
			~LogoNode(void)
		{
		};

protected:
		virtual void localRender();
		virtual void localSimulate();
		virtual void localInit();

};

#endif // __LOGONODE__