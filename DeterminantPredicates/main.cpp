#include <iostream>

/*
	Experimenting with Determinant Predicates from Real-Time Collision Detection
	by Christer Ericson, "Chapter 3 A Math and Geometry Primer"
*/

float InCircle2D(float aX, float aY,
	float bX, float bY,
	float cX, float cY,
	float dX, float dY);

class Matrix3x3
{
private:
	float data[9];

public:
	Matrix3x3(float aX, float aY,
		float bX, float bY,
		float cX, float cY)
	{
		data[0] = aX;	data[1] = aY;	data[2] = 1;
		data[3] = bX;	data[4] = bY;	data[5] = 1;
		data[6] = cX;	data[7] = cY;	data[8] = 1;
	}

	Matrix3x3(float m11, float m12, float m13,
		float m21, float m22, float m23,
		float m31, float m32, float m33)
	{
		data[0] = m11;	data[1] = m12;	data[2] = m13;
		data[3] = m21;	data[4] = m22;	data[5] = m23;
		data[6] = m31;	data[7] = m32;	data[8] = m33;
	}

	float Determinate()
	{
		return data[0] * ((data[4] * data[8]) - (data[5] * data[7])) -
			data[3] * ((data[1] * data[8]) - (data[2] * data[7])) +
			data[6] * ((data[1] * data[5]) - (data[2] * data[4]));
	}
};

class Matrix4x4
{
private:
	float data[16];

public:
	Matrix4x4(float aX, float aY, float aZ,
		float bX, float bY, float bZ,
		float cX, float cY, float cZ,
		float dX, float dY, float dZ)
	{
		data[0] = aX;	data[1] = aY;	data[2] = aZ;	data[3] = 1;
		data[4] = bX;	data[5] = bY;	data[6] = bZ;	data[7] = 1;
		data[8] = cX;	data[9] = cY;	data[10] = cZ;	data[11] = 1;
		data[12] = dX;	data[13] = dY;	data[14] = dZ;	data[15] = 1;
	}

	// Method: http://mathcentral.uregina.ca/QQ/database/QQ.09.07/h/rav1.html
	float Determinate()
	{
		Matrix3x3 A(data[5], data[6], data[7],
			data[9], data[10], data[11],
			data[13], data[14], data[15]);

		Matrix3x3 B(data[4], data[6], data[7],
			data[8], data[10], data[11],
			data[12], data[14], data[15]);

		Matrix3x3 C(data[4], data[5], data[7],
			data[8], data[9], data[11],
			data[12], data[13], data[15]);

		Matrix3x3 D(data[4], data[5], data[6],
			data[8], data[9], data[10],
			data[12], data[13], data[14]);

		float answer = 
			(data[0] * A.Determinate()) - (data[1] * B.Determinate()) + (data[2] * C.Determinate()) - (data[3] * D.Determinate());

		return answer;
	}
};

float InCircle2D(float aX, float aY,
	float bX, float bY,
	float cX, float cY,
	float dX, float dY)
{
	float AxAy_Squared = (aX * aX) + (aY * aY);
	float BxBy_Squared = (bX * bX) + (bY * bY);
	float CxCy_Squared = (cX * cX) + (cY * cY);
	float DxDy_Squared = (dX * dX) + (dY * dY);

	Matrix4x4 matrix(aX, aY, AxAy_Squared,
		bX, bY, BxBy_Squared,
		cX, cY, CxCy_Squared,
		dX, dY, DxDy_Squared);

	float answer = matrix.Determinate();

	return answer;
}

int main(int argc, char* argv[])
{
	//					 A        B       C
	Matrix3x3 orient2D(10,10,	 5,5,	4,15);
	float orient2D_Answer = orient2D.Determinate();

	if(orient2D_Answer > 0)
		std::cout << "C lies to the left of the directed line AB" << std::endl;
	else if(orient2D_Answer < 0)
		std::cout << "C lies to the right of the directed line AB" << std::endl;

	//					 A		  B		  C			D
	Matrix4x4 orient3D(1,4,2,	0,1,4,	-1,0,1,	  2,0,4);
	float orient3D_Answer = orient3D.Determinate();

	if (orient3D_Answer > 0)
		std::cout << "D lies below the supporting plane of triangle ABC" << std::endl;
	else if (orient3D_Answer < 0)
		std::cout << "D lies above the supporting plane of triangle ABC" << std::endl;

	//									 A		 B		 C		 D
	float inCircle_Answer = InCircle2D(5,5,		4,5,	4,2,	4.5,3.5);

	if (inCircle_Answer > 0)
		std::cout << "D lies inside the circle through the three points A, B, and C" << std::endl;
	else if (inCircle_Answer < 0)
		std::cout << "D lies outside the circle of the there points A, B and C" << std::endl;
}