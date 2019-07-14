#if !defined(_VEC3_H_)
#define _VEC3_H_

#if !defined(Assert)
#define Assert( _exp ) ((void)0)
#endif // #if !defined(Assert)

#if !defined(CHECK_VALID)
#define CHECK_VALID( _v)	Assert( (_v).isValid() )
#endif // #if !define(CHECK_VALID)


 
#if defined (__GNUC__) || defined (__clang__)
#define FORCE_INLINE __attribute__((always_inline)) inline
#elif defined (_MSC_VER)
#define FORCE_INLINE __forceinline 
#else
#define FORCE_INLINE inline
#endif

#include <iostream>
#include <cmath>
#include <emmintrin.h>
#include <immintrin.h>

template <typename T>
class Vec3
{
public:
    
	union
	{
		T vecArray[3] __attribute__ ((aligned (16)));
		struct
		{
			T x;
			T y;
			T z;
		} vecStruct;
	} vecUnion;
	
	Vec3<T>(void);
    Vec3<T>(T i);
	Vec3<T>(T X, T Y, T Z);
	void Init(T ix = 0.f, T iy = 0.f, T iz = 0.f);
	T operator[](int i) const;
	T& operator[](int i);
	inline void Zero();
    Vec3<T> & operator++();
    Vec3<T> operator++(int);
	bool operator==(const Vec3<T>& v) const;
	bool operator!=(const Vec3<T>& v) const;
	FORCE_INLINE Vec3<T>&	operator+=(const Vec3<T> &v);
    //FORCE_INLINE Vec3<double>&	operator+=(const Vec3<double> &v);
	FORCE_INLINE Vec3<T>&	operator-=(const Vec3<T> &v);
	FORCE_INLINE Vec3<T>&	operator*=(const Vec3<T> &v);
	FORCE_INLINE Vec3<T>&	operator*=(T s);
	FORCE_INLINE Vec3<T>&	operator/=(const Vec3<T> &v);
	FORCE_INLINE Vec3<T>&	operator/=(T s);
	FORCE_INLINE Vec3<T>&	operator+=(T fl);
	FORCE_INLINE Vec3<T>&	operator-=(T fl);
	FORCE_INLINE bool isValid() const;
	inline T	Length() const;
	FORCE_INLINE T LengthSqr(void) const
	{
		CHECK_VALID(*this);
		return (vecUnion.vecStruct.x*vecUnion.vecStruct.x + vecUnion.vecStruct.y*vecUnion.vecStruct.y + vecUnion.vecStruct.z*vecUnion.vecStruct.z);
	}
	bool IsZero(T tolerance = 0.01f) const
	{
		return (vecUnion.vecStruct.x > -tolerance && vecUnion.vecStruct.x < tolerance &&
			vecUnion.vecStruct.y > -tolerance && vecUnion.vecStruct.y < tolerance &&
			vecUnion.vecStruct.z > -tolerance && vecUnion.vecStruct.z < tolerance);
	}
	void	NormalizeInPlace();
	FORCE_INLINE T	DistToSqr(const Vec3<T> &vOther) const;
	T	Dot(const Vec3<T>& vOther) const;
	T	Length2D(void) const;
	T	Length2DSqr(void) const;
	Vec3<T>& operator=(const Vec3<T> &vOther);
	Vec3<T>	operator+(const Vec3<T>& v) const;
	Vec3<T>	operator-(const Vec3<T>& v) const;
	Vec3<T>	operator*(const Vec3<T>& v) const;
	Vec3<T>	operator/(const Vec3<T>& v) const;
	Vec3<T>	operator*(T fl) const;
	Vec3<T>	operator/(T fl) const;

    friend std::ostream & operator<<(std::ostream &os, const Vec3<T>& v) 
    {
        return os << v.vecUnion.vecStruct.x << ' ' << v.vecUnion.vecStruct.y << ' ' << v.vecUnion.vecStruct.z;
	}
	
};

template <typename T>
inline bool Vec3<T>::isValid() const
{
	return std::isfinite(vecUnion.vecStruct.x) && std::isfinite(vecUnion.vecStruct.y) && std::isfinite(vecUnion.vecStruct.z);
}

template <typename T>
inline void Vec3<T>::Init(T ix, T iy, T iz)
{
	vecUnion.vecStruct.x = ix; 
    vecUnion.vecStruct.y = iy; 
    vecUnion.vecStruct.z = iz;
	CHECK_VALID(*this);
}

template <typename T>
inline Vec3<T>::Vec3(T X, T Y, T Z)
{
	vecUnion.vecStruct.x = X;
    vecUnion.vecStruct.y = Y; 
    vecUnion.vecStruct.z = Z;
	CHECK_VALID(*this);
}

template <typename T>
inline Vec3<T>::Vec3(T i)
{
	vecUnion.vecStruct.x = i; 
    vecUnion.vecStruct.y = i; 
    vecUnion.vecStruct.z = i;
	CHECK_VALID(*this);
}

template <typename T>
inline Vec3<T>::Vec3(void)
{
}

template <typename T>
inline void Vec3<T>::Zero()
{
    vecUnion.vecStruct.x = 0.f;
    vecUnion.vecStruct.y = 0.f; 
    vecUnion.vecStruct.z = 0.f;
}

template <typename T>
inline void Clear(Vec3<T>& a)
{
	a.vecUnion.vecStruct.x = 0.f;
    a.vecUnion.vecStruct.y = 0.f; 
    a.vecUnion.vecStruct.z = 0.f;
}

template <typename T>
inline Vec3<T> & Vec3<T>::operator++()
{
    ++vecUnion.vecStruct.x;
    ++vecUnion.vecStruct.y;
    ++vecUnion.vecStruct.z;
    return *this;
}

template <typename T>
inline Vec3<T> Vec3<T>::operator++(int)
{
    Vec3<T> temp = *this;
    ++vecUnion.vecStruct.x;
    ++vecUnion.vecStruct.y;
    ++vecUnion.vecStruct.z;
    return temp;
}

template <typename T>
inline Vec3<T>& Vec3<T>::operator=(const Vec3<T> &vOther)
{
	CHECK_VALID(vOther);
	vecUnion.vecStruct.x = vOther.x; vecUnion.vecStruct.y = vOther.y; vecUnion.vecStruct.z = vOther.z;
	return *this;
}

template <typename T>
inline T& Vec3<T>::operator[](int i)
{
	Assert((i >= 0) && (i < 3));
	return ((T*)this)[i];
}

template <typename T>
inline T Vec3<T>::operator[](int i) const
{
	Assert((i >= 0) && (i < 3));
	return ((T*)this)[i];
}

template <typename T>
inline bool Vec3<T>::operator==(const Vec3<T>& src) const
{
	CHECK_VALID(src);
	CHECK_VALID(*this);
	return (src.x == vecUnion.vecStruct.x) && (src.y == vecUnion.vecStruct.y) && (src.z == vecUnion.vecStruct.z);
}

template <typename T>
inline bool Vec3<T>::operator!=(const Vec3<T>& src) const
{
	CHECK_VALID(src);
	CHECK_VALID(*this);
	return (src.x != vecUnion.vecStruct.x) && (src.y != vecUnion.vecStruct.y) && (src.z != vecUnion.vecStruct.z);
}

template <typename T>
FORCE_INLINE void Copy(const Vec3<T>& src, Vec3<T>& dst)
{
	CHECK_VALID(src);
	dst.x = src.x;
	dst.y = src.y;
	dst.z = src.z;
}

template <typename T>
FORCE_INLINE  Vec3<T>& Vec3<T>::operator+=(const Vec3<T>& v)
{
	std::cout << " + NORMAL " << std::endl;
	CHECK_VALID(*this);
	CHECK_VALID(v);
	vecUnion.vecStruct.x += v.vecUnion.vecStruct.x; vecUnion.vecStruct.y += v.vecUnion.vecStruct.y; vecUnion.vecStruct.z += v.vecUnion.vecStruct.z;
	return *this;
}

//SIMD DOUBLE
template <>
FORCE_INLINE  Vec3<double>& Vec3<double>::operator+=(const Vec3<double>& v)
{
	std::cout << " + DOUBLE " << std::endl;
	CHECK_VALID(*this);
	CHECK_VALID(v);

	//SIMD 256-bit Instruction 
	__m256d* ptr_a = (__m256d*)vecUnion.vecArray; 
    __m256d* ptr_b = (__m256d*)v.vecUnion.vecArray; 
    _mm256_store_pd(vecUnion.vecArray, _mm256_add_pd(*ptr_a, *ptr_b));
	//vecUnion.vecStruct.x += v.vecUnion.vecStruct.x; vecUnion.vecStruct.y += v.vecUnion.vecStruct.y; vecUnion.vecStruct.z += v.vecUnion.vecStruct.z;
	return *this;
}

//SIMD FLOAT
template <>
FORCE_INLINE  Vec3<float>& Vec3<float>::operator+=(const Vec3<float>& v)
{
	std::cout << " + FLOAT " << std::endl;
	CHECK_VALID(*this);
	CHECK_VALID(v);

	//SIMD 256-bit Instruction 
	__m128* ptr_a = (__m128*)vecUnion.vecArray; 
    __m128* ptr_b = (__m128*)v.vecUnion.vecArray; 
    _mm_store_ps(vecUnion.vecArray, _mm_add_ps(*ptr_a, *ptr_b));
	//vecUnion.vecStruct.x += v.vecUnion.vecStruct.x; vecUnion.vecStruct.y += v.vecUnion.vecStruct.y; vecUnion.vecStruct.z += v.vecUnion.vecStruct.z;
	return *this;
}

template <typename T>
FORCE_INLINE  Vec3<T>& Vec3<T>::operator-=(const Vec3<T>& v)
{
	CHECK_VALID(*this);
	CHECK_VALID(v);
	vecUnion.vecStruct.x -= v.vecUnion.vecStruct.x; vecUnion.vecStruct.y -= v.vecUnion.vecStruct.y; vecUnion.vecStruct.z -= v.vecUnion.vecStruct.z;
	return *this;
}

template <typename T>
FORCE_INLINE  Vec3<T>& Vec3<T>::operator*=(T fl)
{
	vecUnion.vecStruct.x *= fl;
	vecUnion.vecStruct.y *= fl;
	vecUnion.vecStruct.z *= fl;
	CHECK_VALID(*this);
	return *this;
}

template <typename T>
FORCE_INLINE  Vec3<T>& Vec3<T>::operator*=(const Vec3<T>& v)
{
	CHECK_VALID(v);
	vecUnion.vecStruct.x *= v.vecUnion.vecStruct.x;
	vecUnion.vecStruct.y *= v.vecUnion.vecStruct.y;
	vecUnion.vecStruct.z *= v.vecUnion.vecStruct.z;
	CHECK_VALID(*this);
	return *this;
}
 
template <typename T>
FORCE_INLINE Vec3<T>&	Vec3<T>::operator+=(T fl)
{
	vecUnion.vecStruct.x += fl;
	vecUnion.vecStruct.y += fl;
	vecUnion.vecStruct.z += fl;
	CHECK_VALID(*this);
	return *this;
}
 
template <typename T>
FORCE_INLINE Vec3<T>&	Vec3<T>::operator-=(T fl)
{
	vecUnion.vecStruct.x -= fl;
	vecUnion.vecStruct.y -= fl;
	vecUnion.vecStruct.z -= fl;
	CHECK_VALID(*this);
	return *this;
}
 
template <typename T>
FORCE_INLINE  Vec3<T>& Vec3<T>::operator/=(T fl)
{
	Assert(fl != 0.f);
	T oofl = 1.0f / fl;
	vecUnion.vecStruct.x *= oofl;
	vecUnion.vecStruct.y *= oofl;
	vecUnion.vecStruct.z *= oofl;
	CHECK_VALID(*this);
	return *this;
}
 
template <typename T>
FORCE_INLINE  Vec3<T>& Vec3<T>::operator/=(const Vec3<T>& v)
{
	CHECK_VALID(v);
	Assert(v.x != 0.f && v.y != 0.f && v.z != 0.f);
	vecUnion.vecStruct.x /= v.vecUnion.vecStruct.x;
	vecUnion.vecStruct.y /= v.vecUnion.vecStruct.y;
	vecUnion.vecStruct.z /= v.vecUnion.vecStruct.z;
	CHECK_VALID(*this);
	return *this;
}
 
template <typename T>
inline T Vec3<T>::Length(void) const
{
	CHECK_VALID(*this);
 
	T root = 0.f;
 
	T sqsr = vecUnion.vecStruct.x*vecUnion.vecStruct.x + vecUnion.vecStruct.y*vecUnion.vecStruct.y + vecUnion.vecStruct.z*vecUnion.vecStruct.z;

	#if defined (__GNUC__) || defined (__clang__)
    __asm__("sqrtss %1, %0" : "=x" (root) : "x" (sqsr));
	#elif defined (_MSC_VER)
	__asm
	{
		sqrtss xmm0, sqsr
		movss root, xmm0
	}
	#else
	return sqrt(sqsr);
	#endif

	return root;
}
 
template <typename T>
inline T Vec3<T>::Length2D(void) const
{
	CHECK_VALID(*this);
 
	T root = 0.f;
 
	T sqst = vecUnion.vecStruct.x*vecUnion.vecStruct.x + vecUnion.vecStruct.y*vecUnion.vecStruct.y;

	#if defined (__GNUC__) || defined (__clang__)
	__asm__("sqrtss %1, %0" : "=x" (root) : "x" (sqst));
	#elif defined (_MSC_VER)
	__asm
	{
		sqrtss xmm0, sqst
		movss root, xmm0
	}
	#else
	return sqrt(sqsr);
	#endif
 
	return root;
}
 
template <typename T>
inline T Vec3<T>::Length2DSqr(void) const
{
	return (vecUnion.vecStruct.x*vecUnion.vecStruct.x + vecUnion.vecStruct.y*vecUnion.vecStruct.y);
}
 
template <typename T>
inline Vec3<T> CrossProduct(const Vec3<T>& a, const Vec3<T>& b)
{
	return Vec3<T>(a.vecUnion.vecStruct.y*b.vecUnion.vecStruct.z - a.vecUnion.vecStruct.z*b.vecUnion.vecStruct.y, a.vecUnion.vecStruct.z*b.vecUnion.vecStruct.x - a.vecUnion.vecStruct.x*b.vecUnion.vecStruct.z, a.vecUnion.vecStruct.x*b.vecUnion.vecStruct.y - a.vecUnion.vecStruct.y*b.vecUnion.vecStruct.x);
}
 
template <typename T>
T Vec3<T>::DistToSqr(const Vec3<T> &vOther) const
{
	Vec3<T> delta;
 
	delta.vecUnion.vecStruct.x = vecUnion.vecStruct.x - vOther.vecUnion.vecStruct.x;
	delta.vecUnion.vecStruct.y = vecUnion.vecStruct.y - vOther.vecUnion.vecStruct.y;
	delta.vecUnion.vecStruct.z = vecUnion.vecStruct.z - vOther.vecUnion.vecStruct.z;
 
	return delta.LengthSqr();
}
 
template <typename T>
inline void Vec3<T>::NormalizeInPlace()
{
	Vec3<T>& v = *this;
 
	T iradius = 1.f / (this->Length() + 1.192092896e-07F); //FLT_EPSILON
 
	v.vecUnion.vecStruct.x *= iradius;
	v.vecUnion.vecStruct.y *= iradius;
	v.vecUnion.vecStruct.z *= iradius;
    
}
 
template <typename T>
inline Vec3<T> Vec3<T>::operator+(const Vec3<T>& v) const
{
	Vec3<T> res;
	res.vecUnion.vecStruct.x = vecUnion.vecStruct.x + v.vecUnion.vecStruct.x;
	res.vecUnion.vecStruct.y = vecUnion.vecStruct.y + v.vecUnion.vecStruct.y;
	res.vecUnion.vecStruct.z = vecUnion.vecStruct.z + v.vecUnion.vecStruct.z;
	return res;
}
 
template <typename T>
inline Vec3<T> Vec3<T>::operator-(const Vec3<T>& v) const
{
	Vec3<T> res;
	res.vecUnion.vecStruct.x = vecUnion.vecStruct.x - v.vecUnion.vecStruct.x;
	res.vecUnion.vecStruct.y = vecUnion.vecStruct.y - v.vecUnion.vecStruct.y;
	res.vecUnion.vecStruct.z = vecUnion.vecStruct.z - v.vecUnion.vecStruct.z;
	return res;
}
 
template <typename T>
inline Vec3<T> Vec3<T>::operator*(T fl) const
{
	Vec3<T> res;
	res.vecUnion.vecStruct.x = vecUnion.vecStruct.x * fl;
	res.vecUnion.vecStruct.y = vecUnion.vecStruct.y * fl;
	res.vecUnion.vecStruct.z = vecUnion.vecStruct.z * fl;
	return res;
}
 
template <typename T>
inline Vec3<T> Vec3<T>::operator*(const Vec3<T>& v) const
{
	Vec3<T> res;
	res.vecUnion.vecStruct.x = vecUnion.vecStruct.x * v.vecUnion.vecStruct.x;
	res.vecUnion.vecStruct.y = vecUnion.vecStruct.y * v.vecUnion.vecStruct.y;
	res.vecUnion.vecStruct.z = vecUnion.vecStruct.z * v.vecUnion.vecStruct.z;
	return res;
}
 
template <typename T>
inline Vec3<T> Vec3<T>::operator/(T fl) const
{
	Vec3<T> res;
	res.vecUnion.vecStruct.x = vecUnion.vecStruct.x / fl;
	res.vecUnion.vecStruct.y = vecUnion.vecStruct.y / fl;
	res.vecUnion.vecStruct.z = vecUnion.vecStruct.z / fl;
	return res;
}
 
template <typename T>
inline Vec3<T> Vec3<T>::operator/(const Vec3<T>& v) const
{
	Vec3<T> res;
	res.vecUnion.vecStruct.x = vecUnion.vecStruct.x / v.vecUnion.vecStruct.x;
	res.vecUnion.vecStruct.y = vecUnion.vecStruct.y / v.vecUnion.vecStruct.y;
	res.vecUnion.vecStruct.z = vecUnion.vecStruct.z / v.vecUnion.vecStruct.z;
	return res;
}

template <typename T>
inline T Vec3<T>::Dot(const Vec3<T>& vOther) const
{
	const Vec3<T>& a = *this;
 
	return(a.vecUnion.vecStruct.x*vOther.vecUnion.vecStruct.x + a.vecUnion.vecStruct.y*vOther.vecUnion.vecStruct.y + a.vecUnion.vecStruct.z*vOther.vecUnion.vecStruct.z);
}

#endif //_VEC3_H_

