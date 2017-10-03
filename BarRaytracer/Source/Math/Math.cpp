#include"Math.h"

using namespace math;
	

Matrix4x4 Math::MatrixLookAtLH(Vec3 eye, Vec3 at, Vec3 up)
{
	Vec3 zaxis, xaxis, yaxis, cross;
	Normalize(at - eye, zaxis);
	CrossProduct(up, zaxis, cross);
	Normalize(cross, xaxis);
	CrossProduct(zaxis, xaxis, yaxis);
	
	Matrix4x4 mat = { xaxis.x,						yaxis.x,							zaxis.x,							0.0f,
					  xaxis.y,						yaxis.y,							zaxis.y,							0.0f,
					  xaxis.z,						yaxis.z,							zaxis.z,							0.0f,
					  -DotProduct(xaxis, eye),		-DotProduct(yaxis, eye),			-DotProduct(zaxis, eye),			1.0f };

	return mat;
}

Matrix4x4 Math::MatrixOrthoOffCenterLH(float minX, float maxX, float minY, float maxY, float zn, float zf)
{
	Matrix4x4 mat = { 	2/(maxX-minX),				0,							0,					0,
						0,							2/(maxY-minY),				0,					0,
						0,							0,							1/(zf-zn),			0,
						(minX+maxX)/(minX-maxX),	(maxY+minY)/(minY-maxY),	zn/(zn-zf),			1	};
	
	return mat;
}

/*
Matrix4x4 mat = { 1.0f,	0.0f, 0.0f, 0.0f,
					  0.0f, 1.0f, 0.0f, 0.0f,
					  0.0f, 0.0f, 0.0f, 0.0f,
					  0.0f, 0.0f, 0.0f, 0.0f };*/

Matrix4x4 Math::MatrixPerspectiveFovLH(float angle, float aspect, float near, float far)
{
	/*
	xScale     0          0               0
	0        yScale       0               0
	0          0       zf/(zf-zn)         1
	0          0       -zn*zf/(zf-zn)     0
	where:
	yScale = cot(fovY/2)

	xScale = yScale / aspect ratio
	*/

	float yScale = 1.0f / tan(angle/2.0f);
	float xScale = yScale / aspect;
	Matrix4x4 mat = {	xScale,		0.0f,		0.0f,					0.0f,
						0.0f,		yScale,		0.0f,					0.0f,
						0.0f,		0.0f,		far/(far-near),			1.0f,
						0.0f,		0.0f,		-near*far/(far-near),	0.0f	};
	return mat;		  
}

Matrix4x4 Math::MatrixIdentity()
{
	Matrix4x4 mat = { 1.0f,	0.0f, 0.0f, 0.0f,
					  0.0f, 1.0f, 0.0f, 0.0f,
					  0.0f, 0.0f, 1.0f, 0.0f,
					  0.0f, 0.0f, 0.0f, 1.0f };

	return mat;
}

Matrix4x4 Math::MatrixTranslation(float x, float y, float z)
{
	Matrix4x4 mat = { 1.0f,		0.0f,		0.0f,		0.0f,
					  0.0f,		1.0f,		0.0f,		0.0f,
					  0.0f,		0.0f,		1.0f,		0.0f,
					  x,		y,			z,			1.0f };
	return mat;
}

Matrix4x4 Math::MatrixRotationYawPitchRoll(float y, float p, float r)
{
	Matrix4x4 Yaw = MatrixRotationY(y);
	Matrix4x4 Pitch = MatrixRotationX(p);
	Matrix4x4 Roll = MatrixRotationZ(r);
	return Yaw*Pitch*Roll;
}

void Math::ClampTo360(float& angle)
{
	while (angle > 2*3.1415) angle -= 2*3.1415;
	while (angle < 0.0f)	  angle += 2*3.1415;
}


Matrix4x4 Math::MatrixRotationAxis(const Vec3& v, float a)
{
	Matrix4x4 mat = { cos(a) + pow(v.x, 2)*(1 - cos(a)),	v.y*v.x*(1 - cos(a)) - v.z*sin(a),	v.z*v.x*(1 - cos(a)) + v.y*sin(a),		0.0f,
					  v.y*v.x*(1 - cos(a)) + v.z*sin(a),	cos(a) + pow(v.y, 2)*(1 - cos(a)),	v.y*v.z*(1 - cos(a)) - v.x*sin(a),		0.0f,
					  v.z*v.x*(1 - cos(a)) - v.y*sin(a),	v.z*v.y*(1 - cos(a)) + v.x*sin(a),	cos(a) + pow(v.z, 2)*(1 - cos(a)),		0.0f,
					  0.0f,									0.0f,								0.0f,									1.0f };
	return mat;
}



Matrix4x4 Math::MatrixRotationY(float a)
{
	Matrix4x4 mat = { cos(a),	0.0f,	-sin(a),	0.0f,
					  0.0f,		1.0f,	0.0f,		0.0f,
					  sin(a),	0.0f,	cos(a),		0.0f,
					  0.0f,		0.0f,	0.0f,		1.0f };
	return mat;
}

Matrix4x4 Math::MatrixRotationZ(float a)
{
	Matrix4x4 mat = {  cos(a),	sin(a),	0.0f,	0.0f,
					  -sin(a),	cos(a),	0.0f,	0.0f,
					   0.0f,	0.0f,	1.0f,	0.0f,
					   0.0f,	0.0f,	0.0f,	1.0f };
	return mat;
}

Matrix4x4 Math::MatrixRotationX(float a)
{
	Matrix4x4 mat = { 1.0f,		0.0f,		0.0f,		0.0f,
					  0.0f,		cos(a),		sin(a),		0.0f,
					  0.0f,		-sin(a),	cos(a),		0.0f,
					  0.0f,		0.0f,		0.0f,		1.0f };
	return mat;
}

Matrix4x4 Math::MatrixTranspose(const Matrix4x4& m)
{
	Matrix4x4 mat = { m.m[0], m.m[4], m.m[8], m.m[12],
					  m.m[1], m.m[5], m.m[9], m.m[13],
					  m.m[2], m.m[6], m.m[10], m.m[14],
					  m.m[3], m.m[7], m.m[11], m.m[15] };

	return mat;
}


//-------------------------	Vec3

float min(float f1, float f2)
{
	return f1 <= f2 ? f1 : f2;
}

float max(float f1, float f2)
{
	return f1 >= f2 ? f1 : f2;
}

Vec3 Math::Reflect(const Vec3& v, const Vec3& normal)
{
	return v - normal * 2*DotProduct(v, normal);
}

float Math::Clamp(float minf, float maxf, float f)
{
	return max(min(maxf, f), minf);
}

float Math::Saturate(float f)
{
	return Clamp(0.0f, 1.0f, f);
}

void Math::Normalize(const Vec3& v, Vec3& out)
{
	float l = v.Length();
	out.x = v.x / l;
	out.y = v.y / l;
	out.z = v.z / l;
}

Vec3 Math::Normalize(const Vec3& v)
{
	Vec3 out;
	float l = v.Length();
	out.x = v.x / l;
	out.y = v.y / l;
	out.z = v.z / l;

	return out;
}

float Math::DotProduct(const Vec3& v, const Vec3& v2)
{
	return v.x*v2.x + v.y*v2.y + v.z*v2.z;
}

float Math::GetCos(const Vec3& v, const Vec3& v2)
{
	return DotProduct(v, v2) / (v.Length() * v2.Length());
}

float Math::GetAngleBetween(const Vec3& v, const Vec3& v2)
{
	return acos(GetCos(v, v2));
}

void Math::ProjectAonB(const Vec3& a, const Vec3& b, Vec3& out)
{
	out = b * (DotProduct(a, b) / DotProduct(b, b));
}

void Math::CrossProduct(const Vec3& v, const Vec3& v2, Vec3& out)
{
	out.x = v.y*v2.z - v.z*v2.y;
	out.y = v.z*v2.x - v.x*v2.z;
	out.z = v.x*v2.y - v.y*v2.x;
}

//-------------------------	Vec2

void Math::Normalize(const Vec2& v, Vec2& out)
{
	float l = v.Length();
	out.x = v.x / l;
	out.y = v.y / l;
}

float Math::DotProduct(const Vec2& v, const Vec2& v2)
{
	Vec2 tmp; Normalize(v, tmp);
	Vec2 tmpV; Normalize(v2, tmpV);

	return tmp.x*tmpV.x + tmp.y*tmpV.y;
}

float Math::GetCos(const Vec2& v, const Vec2& v2)
{
	return DotProduct(v, v2) / (v.Length() * v2.Length());
}

void Math::ProjectAonB(const Vec2& a, const Vec2& b, Vec2& out)
{
	out = b * (DotProduct(a, b) / DotProduct(b, b));
}