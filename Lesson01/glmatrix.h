#ifndef __GLMATRIX__
#define __GLMATRIX__

#include "w_vektor.h"

class GLMatrix {

		float mat[16];
		
	public:
		
		GLMatrix();
		GLMatrix(unsigned int target); //loads target matrix from opengl
		GLMatrix(const GLMatrix& src);
		//GLMatrix(const Vektor3D<float>& c0,const Vektor3D<float>& c1,const Vektor3D<float>& c2);

		//float Element(int i,int j);
		void loadIdentity(); // Loads the identity matrix into this.

		void multMatrix() const; // Multiplies current OpenGL Matrix with this.
		void loadMatrix() const; // Replaces current OpenGL Matrix with this.
		void getMatrix(); // Recieves current Modelview Matrix from OpenGL.
		void getMatrix(unsigned int target); // Recieves matrix with OpenGL's target matrix.

		void translate(const W_Vektor3D<float> &vec);
		void translate(float x, float y, float z);
		void translate(const W_Point3D<float> &p);
		void translate(float *coord);
		
		void scale(const W_Vektor3D<float> &vec);
		void scale(float x, float y, float z);
		void scale(const W_Point3D<float> &p);
		void scale(float *factor);
		
		void rotate(float angle, const W_Vektor3D<float> &vec);
		void rotate(float angle, const W_Point3D<float> &p);
		void rotate(float angle, float x, float y, float z);
		void rotate(float angle, float *axis);

		GLMatrix operator*(const GLMatrix& src) const;
		GLMatrix &operator*=(const GLMatrix& src);
		/*const Vektor3D<float> operator * (const Vektor3D<float>& v) const;
		inline friend const Vektor3D<float> operator * (const Vektor3D<float>& v, const GLMatrix& src)
		{
			return Vektor3D<float>(Vektor3D<float>(src.mat[0], src.mat[1], src.mat[2]).Dot(v), 
				Vektor3D<float>(src.mat[4], src.mat[5], src.mat[6]).Dot(v),
				Vektor3D<float>(src.mat[8], src.mat[9], src.mat[10]).Dot(v));
		};*/

		const bool operator == (const GLMatrix& m) const;
		const bool operator != (const GLMatrix& m) const;

		const GLMatrix& operator = (const GLMatrix& m);

		float& operator[](int i)
		{ return mat[i]; }
		const float& operator[](int i) const
		{ return mat[i]; }

		float determinant() const;
		GLMatrix getInverted() const;
		GLMatrix& invert();
		
		virtual 
		~GLMatrix(void);

};
#endif // __GLMATRIX__