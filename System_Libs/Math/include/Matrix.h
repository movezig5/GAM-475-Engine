//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2018
// Gam 475
//----------------------------------------------------------------------------- 

#ifndef ENGINE_MATH_MATRIX_H
#define ENGINE_MATH_MATRIX_H

#include "Vect.h"

class Matrix : public Align16
{
public:

	enum SpecialType
	{
		Zero,
		Identity
	};

	enum RotType
	{
		Rot_X,
		Rot_Y,
		Rot_Z
	};

	enum TransType
	{
		Trans
	};

	enum ScaleType
	{
		Scale
	};

	enum RotAxisAngleType
	{
		RotAxisAngle
	};

	enum RotOrientType
	{
		RotOrient,
		RotInverseOrient
	};

	enum RowType
	{
		Row_0,
		Row_1,
		Row_2,
		Row_3
	};


public:

	// Big 4
	Matrix();
	const Matrix &operator = (const Matrix &A);
	Matrix(const Matrix &tM);
	~Matrix();

	// Constructors
	Matrix(const Vect &tV0, const Vect &tV1, const Vect &tV2, const Vect &tV3);
	Matrix(const RotType type, const float angle);

	Matrix(const TransType type, const float tx, const float ty, const float tz);
	Matrix(const TransType type, const Vect &vTrans);

	Matrix(const ScaleType type, const float sx, const float sy, const float sz);
	Matrix(const ScaleType type, const Vect &vScale);

	explicit Matrix(const SpecialType type);

	// Set 
	void set(const Vect &V0, const Vect &V1, const Vect &V2, const Vect &V3);
	void set(const RotType type, const float angle);
	void set(const RotAxisAngleType, const Vect &vAxis, const float angle_radians);
	void set(const RotOrientType, const Vect &dof, const Vect &up);

	void set(const TransType type, const float tx, const float ty, const float tz);
	void set(const TransType type, const Vect &vTrans);

	void set(const ScaleType type, const float sx, const float sy, const float sz);
	void set(const ScaleType type, const Vect &vScale);

	void set(const SpecialType type);
	void set(const RowType type, const Vect &V);
	void set(Vect &axis, float angle);

	// Get
	Vect get(const RowType type) const;

	// Matrix functions
	const float det() const;
	Matrix &T(void);
	const Matrix getT(void)const;
	const Matrix getInv(void) const;
	Matrix &inv(void);

	// comparison
	bool isEqual(const Matrix &A, const float epsilon = MATH_TOLERANCE) const;
	bool isIdentity(const float epsilon = MATH_TOLERANCE) const;

	// bracket operators	
	float &operator[] (const enum m0_enum);
	float &operator[] (const enum m1_enum);
	float &operator[] (const enum m2_enum);
	float &operator[] (const enum m3_enum);
	float &operator[] (const enum m4_enum);
	float &operator[] (const enum m5_enum);
	float &operator[] (const enum m6_enum);
	float &operator[] (const enum m7_enum);
	float &operator[] (const enum m8_enum);
	float &operator[] (const enum m9_enum);
	float &operator[] (const enum m10_enum);
	float &operator[] (const enum m11_enum);
	float &operator[] (const enum m12_enum);
	float &operator[] (const enum m13_enum);
	float &operator[] (const enum m14_enum);
	float &operator[] (const enum m15_enum);
	const float operator[] (const enum m0_enum) const;
	const float operator[] (const enum m1_enum) const;
	const float operator[] (const enum m2_enum) const;
	const float operator[] (const enum m3_enum) const;
	const float operator[] (const enum m4_enum) const;
	const float operator[] (const enum m5_enum) const;
	const float operator[] (const enum m6_enum) const;
	const float operator[] (const enum m7_enum) const;
	const float operator[] (const enum m8_enum) const;
	const float operator[] (const enum m9_enum) const;
	const float operator[] (const enum m10_enum) const;
	const float operator[] (const enum m11_enum) const;
	const float operator[] (const enum m12_enum) const;
	const float operator[] (const enum m13_enum) const;
	const float operator[] (const enum m14_enum) const;
	const float operator[] (const enum m15_enum) const;

	// accessor	
	float &m0();
	float &m1();
	float &m2();
	float &m3();
	float &m4();
	float &m5();
	float &m6();
	float &m7();
	float &m8();
	float &m9();
	float &m10();
	float &m11();
	float &m12();
	float &m13();
	float &m14();
	float &m15();

	const float m0() const;
	const float m1() const;
	const float m2() const;
	const float m3() const;
	const float m4() const;
	const float m5() const;
	const float m6() const;
	const float m7() const;
	const float m8() const;
	const float m9() const;
	const float m10() const;
	const float m11() const;
	const float m12() const;
	const float m13() const;
	const float m14() const;
	const float m15() const;

	// add/sub operators
	Matrix operator + (void) const { return Matrix(*this); };
	Matrix operator + (const Matrix &A) const;
	void operator += (const Matrix &A);
	Matrix operator - (void) const;
	Matrix operator - (const Matrix &A) const;
	void operator -= (const Matrix &A);

	// Multiply
	Matrix operator * (const float s) const;
	friend Matrix operator *(const float scale, const Matrix &A);
	void operator *= (const float scale);
	Matrix operator * (const Matrix &A) const;
	void  operator *= (const Matrix &A);

private:
	const Matrix getAdj(void) const;
	void setRotOrient(const Vect &vect_dof, const Vect &vect_vup);
	void setRotInvOrient(const Vect &vect_dof, const Vect &vect_vup);

	union
	{
		struct
		{
			Vect _v0;
			Vect _v1;
			Vect _v2;
			Vect _v3;
		};

		struct
		{
			float _m0;
			float _m1;
			float _m2;
			float _m3;
			float _m4;
			float _m5;
			float _m6;
			float _m7;
			float _m8;
			float _m9;
			float _m10;
			float _m11;
			float _m12;
			float _m13;
			float _m14;
			float _m15;
		};
	};
};

#endif

// ---  End of File ---------------
