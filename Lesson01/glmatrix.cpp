#include "glmatrix.h"
//#include "vektor.h"
 #include <windows.h>		// Header File For Windows
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>	

GLMatrix::GLMatrix()
{
	loadIdentity();
}

GLMatrix::~GLMatrix()
{
}

GLMatrix::GLMatrix(const GLMatrix &src)
{
	memcpy(mat,src.mat,sizeof(mat));
}

GLMatrix::GLMatrix(unsigned int target)
{
	this->getMatrix(target);
}
/*
//vosmojno nado perevernut
GLMatrix::GLMatrix(const Vektor3D<float>& c0,const Vektor3D<float>& c1,const Vektor3D<float>& c2)
{
	for (int i=0;i<4;i++)
	{
		mat[i]=c0[i];
		mat[i+4]=c1[i];
		mat[i+8]=c2[i];
	}
}
*/
void GLMatrix::loadIdentity()
{	
	for (int i=0;i<16;i++)
	{
		mat[i] = (i%5 == 0) ? 1.0f : 0.0f;
	}
}

void GLMatrix::loadMatrix() const
{
	glLoadMatrixf(mat);
}

void GLMatrix::getMatrix()
{
	glGetFloatv(GL_MODELVIEW_MATRIX, mat);
}

void GLMatrix::getMatrix(unsigned int target)
{
	glGetFloatv(target, mat);
}

void GLMatrix::multMatrix() const
{
	glMultMatrixf(mat);
}

void GLMatrix::translate(float x, float y, float z)
{
		glPushMatrix();
		loadMatrix();
		glTranslatef(x,y,z);
		getMatrix(); 
		glPopMatrix();
}

void GLMatrix::translate(const W_Vektor3D<float> &vec)
{
	translate(vec[0],vec[1],vec[2]);
}

void GLMatrix::translate(const W_Point3D<float> &p)
{
	translate(p[0],p[1],p[2]);
}

void GLMatrix::translate(float *coord)
{
	translate(coord[0],coord[1],coord[2]);
}

void GLMatrix::rotate(float angle, float x, float y, float z)
{
		glPushMatrix();
		loadMatrix();
		glRotatef(angle,x,y,z);
		getMatrix(); 
		glPopMatrix();
}

void GLMatrix::rotate(float angle, const W_Vektor3D<float> &vec)
{
	rotate(angle,vec[0],vec[1],vec[2]);
}

void GLMatrix::rotate(float angle, const W_Point3D<float> &p)
{
	rotate(angle,p[0],p[1],p[2]);
}

void GLMatrix::rotate(float angle, float *axis)
{
	rotate(angle,axis[0],axis[1],axis[2]);
}

void GLMatrix::scale(float x, float y, float z)
{
		glPushMatrix();
		loadMatrix();
		glScalef(x,y,z);
		getMatrix(); 
		glPopMatrix();
}

void GLMatrix::scale(const W_Point3D<float> &p)
{
	scale(p[0],p[1],p[2]);
}

void GLMatrix::scale(const W_Vektor3D<float> &vec)
{
	scale(vec[0],vec[1],vec[2]);
}

void GLMatrix::scale(float *factor)
{
	scale(factor[0],factor[1],factor[2]);
}

GLMatrix GLMatrix::operator *(const GLMatrix &src) const
{
	GLMatrix m;
	glPushMatrix();
	this->loadMatrix();
	src.multMatrix();
	m.getMatrix();
	glPopMatrix();
	return m;
}

GLMatrix& GLMatrix::operator *=(const GLMatrix &src)
{
	glPushMatrix();
	this->loadMatrix();
	src.multMatrix();
	this->getMatrix();
	glPopMatrix();
	return *this;
}
/*
const Vektor3D<float> GLMatrix::operator * (const Vektor3D<float>& v) const
{
	return (Vektor3D<float>(mat[0],mat[1],mat[2])*v[0]+
		Vektor3D<float>(mat[4],mat[5],mat[6])*v[1]+
		Vektor3D<float>(mat[8],mat[9],mat[10])*v[2]);
}*/

const bool GLMatrix::operator == (const GLMatrix& m) const
{
	bool svar = true;
	for (int i=0; i<16; i++)
		svar = svar && (mat[i]==m.mat[i]);
	return svar;
}

const bool GLMatrix::operator != (const GLMatrix& m) const
{
	return !(m==*this);
}

const GLMatrix& GLMatrix::operator = (const GLMatrix& m)
{
	for (int i=0; i<16; i++)
		mat[i]=m.mat[i];
	return *this;
}

float GLMatrix::determinant() const
{
	return
		mat[ 3]*mat[ 6]*mat[ 9]*mat[12] - mat[ 2]*mat[ 7]*mat[ 9]*mat[12] -
	mat[ 3]*mat[ 5]*mat[10]*mat[12] + mat[ 1]*mat[ 7]*mat[10]*mat[12] +

	mat[ 2]*mat[ 5]*mat[11]*mat[12] - mat[ 1]*mat[ 6]*mat[11]*mat[12] -
	mat[ 3]*mat[ 6]*mat[ 8]*mat[13] + mat[ 2]*mat[ 7]*mat[ 8]*mat[13] +

	mat[ 3]*mat[ 4]*mat[10]*mat[13] - mat[ 0]*mat[ 7]*mat[10]*mat[13] -
	mat[ 2]*mat[ 4]*mat[11]*mat[13] + mat[ 0]*mat[ 6]*mat[11]*mat[13] +

	mat[ 3]*mat[ 5]*mat[ 8]*mat[14] - mat[ 1]*mat[ 7]*mat[ 8]*mat[14] -
	mat[ 3]*mat[ 4]*mat[ 9]*mat[14] + mat[ 0]*mat[ 7]*mat[ 9]*mat[14] +

	mat[ 1]*mat[ 4]*mat[11]*mat[14] - mat[ 0]*mat[ 5]*mat[11]*mat[14] -
	mat[ 2]*mat[ 5]*mat[ 8]*mat[15] + mat[ 1]*mat[ 6]*mat[ 8]*mat[15] +

	mat[ 2]*mat[ 4]*mat[ 9]*mat[15] - mat[ 0]*mat[ 6]*mat[ 9]*mat[15] -
	mat[ 1]*mat[ 4]*mat[10]*mat[15] + mat[ 0]*mat[ 5]*mat[10]*mat[15];
}

GLMatrix GLMatrix::getInverted() const
{
	GLMatrix m(*this);
	return m.invert();
}

GLMatrix& GLMatrix::invert()
{
	float det = determinant();
	mat[ 0] = (1/det) *( mat[ 6]*mat[11]*mat[13] - mat[ 7]*mat[10]*mat[13] +
			   mat[ 7]*mat[ 9]*mat[14] - mat[ 5]*mat[11]*mat[14] -
			   mat[ 6]*mat[ 9]*mat[15] + mat[ 5]*mat[10]*mat[15] );
  mat[ 1] = (1/det) *( mat[ 3]*mat[10]*mat[13] - mat[ 2]*mat[11]*mat[13] -
			   mat[ 3]*mat[ 9]*mat[14] +	mat[ 1]*mat[11]*mat[14] +
			   mat[ 2]*mat[ 9]*mat[15] - mat[ 1]*mat[10]*mat[15] );
  mat[ 2] = (1/det) *( mat[ 2]*mat[ 7]*mat[13] - mat[ 3]*mat[ 6]*mat[13] +
			   mat[ 3]*mat[ 5]*mat[14] - mat[ 1]*mat[ 7]*mat[14] -
			   mat[ 2]*mat[ 5]*mat[15] + mat[ 1]*mat[ 6]*mat[15] );
  mat[ 3] = (1/det) *( mat[ 3]*mat[ 6]*mat[ 9] - mat[ 2]*mat[ 7]*mat[ 9] -
			   mat[ 3]*mat[ 5]*mat[10] + mat[ 1]*mat[ 7]*mat[10] +
			   mat[ 2]*mat[ 5]*mat[11] - mat[ 1]*mat[ 6]*mat[11] );
  mat[ 4] = (1/det) *( mat[ 7]*mat[10]*mat[12] - mat[ 6]*mat[11]*mat[12] -
			   mat[ 7]*mat[ 8]*mat[14] + mat[ 4]*mat[11]*mat[14] +
			   mat[ 6]*mat[ 8]*mat[15] - mat[ 4]*mat[10]*mat[15] );
  mat[ 5] = (1/det) *( mat[ 2]*mat[11]*mat[12] - mat[ 3]*mat[10]*mat[12] +
			   mat[ 3]*mat[ 8]*mat[14] - mat[ 0]*mat[11]*mat[14] -
			   mat[ 2]*mat[ 8]*mat[15] + mat[ 0]*mat[10]*mat[15] );
  mat[ 6] = (1/det) *( mat[ 3]*mat[ 6]*mat[12] - mat[ 2]*mat[ 7]*mat[12] -
			   mat[ 3]*mat[ 4]*mat[14] + mat[ 0]*mat[ 7]*mat[14] +
			   mat[ 2]*mat[ 4]*mat[15] - mat[ 0]*mat[ 6]*mat[15] );
  mat[ 7] = (1/det) *( mat[ 2]*mat[ 7]*mat[ 8] - mat[ 3]*mat[ 6]*mat[ 8] +
			   mat[ 3]*mat[ 4]*mat[10] - mat[ 0]*mat[ 7]*mat[10] -
			   mat[ 2]*mat[ 4]*mat[11] + mat[ 0]*mat[ 6]*mat[11] );
  mat[ 8] = (1/det) *( mat[ 5]*mat[11]*mat[12] - mat[ 7]*mat[ 9]*mat[12] +
			   mat[ 7]*mat[ 8]*mat[13] - mat[ 4]*mat[11]*mat[13] -
			   mat[ 5]*mat[ 8]*mat[15] + mat[ 4]*mat[ 9]*mat[15] );
  mat[ 9] = (1/det) *( mat[ 3]*mat[ 9]*mat[12] - mat[ 1]*mat[11]*mat[12] -
			   mat[ 3]*mat[ 8]*mat[13] + mat[ 0]*mat[11]*mat[13] +
			   mat[ 1]*mat[ 8]*mat[15] - mat[ 0]*mat[ 9]*mat[15] );
  mat[10] = (1/det) *( mat[ 1]*mat[ 7]*mat[12] - mat[ 3]*mat[ 5]*mat[12] +
			   mat[ 3]*mat[ 4]*mat[13] - mat[ 0]*mat[ 7]*mat[13] -
			   mat[ 1]*mat[ 4]*mat[15] + mat[ 0]*mat[ 5]*mat[15] );
  mat[11] = (1/det) *( mat[ 3]*mat[ 5]*mat[ 8] - mat[ 1]*mat[ 7]*mat[ 8] -
			   mat[ 3]*mat[ 4]*mat[ 9] + mat[ 0]*mat[ 7]*mat[ 9] +
			   mat[ 1]*mat[ 4]*mat[11] - mat[ 0]*mat[ 5]*mat[11] );
  mat[12] = (1/det) *( mat[ 6]*mat[ 9]*mat[12] - mat[ 5]*mat[10]*mat[12] -
			   mat[ 6]*mat[ 8]*mat[13] + mat[ 4]*mat[10]*mat[13] +
			   mat[ 5]*mat[ 8]*mat[14] - mat[ 4]*mat[ 9]*mat[14] );
  mat[13] = (1/det) *( mat[ 1]*mat[10]*mat[12] - mat[ 2]*mat[ 9]*mat[12] +
			   mat[ 2]*mat[ 8]*mat[13] - mat[ 0]*mat[10]*mat[13] -
			   mat[ 1]*mat[ 8]*mat[14] + mat[ 0]*mat[ 9]*mat[14] );
  mat[14] = (1/det) *( mat[ 2]*mat[ 5]*mat[12] - mat[ 1]*mat[ 6]*mat[12] -
			   mat[ 2]*mat[ 4]*mat[13] + mat[ 0]*mat[ 6]*mat[13] +
			   mat[ 1]*mat[ 4]*mat[14] - mat[ 0]*mat[ 5]*mat[14] );
  mat[15] = (1/det) *( mat[ 1]*mat[ 6]*mat[ 8] - mat[ 2]*mat[ 5]*mat[ 8] +
			   mat[ 2]*mat[ 4]*mat[ 9] - mat[ 0]*mat[ 6]*mat[ 9] -
			   mat[ 1]*mat[ 4]*mat[10] + mat[ 0]*mat[ 5]*mat[10] );
  //scale(1/determinant());
  return *this;
}