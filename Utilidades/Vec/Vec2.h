#if !defined(_VEC2_H_)
#define _VEC2_H_

#if !defined(CHECK_VALID)
#define CHECK_VALID( _v ) NULL
#endif // #if !define(CHECK_VALID)

#if !defined(Assert)
#define Assert( _exp ) ((void)0)
#endif // #if !defined(Assert)
 
#if defined (__GNUC__) || defined (__clang__)
#define FORCE_INLINE __attribute__((always_inline)) inline
#elif defined (_MSC_VER)
#define FORCE_INLINE __forceinline 
#else
#define FORCE_INLINE inline
#endif

#include <iostream>
#include <cmath>


template <typename T>
class Vec2
{
public:
	T x, y;
	Vec2<T>(void);
    Vec2<T>(T i);
	Vec2<T>(T X, T Y);
	void Init(T ix = 0.f, T iy = 0.f);
	T operator[](int i) const;
	T& operator[](int i);
	inline void Zero();
    Vec2<T> & operator++();
    Vec2<T> operator++(int);
	bool operator==(const Vec2<T>& v) const;
	bool operator!=(const Vec2<T>& v) const;
	FORCE_INLINE Vec2<T>&	operator+=(const Vec2<T> &v);
	FORCE_INLINE Vec2<T>&	operator-=(const Vec2<T> &v);
	FORCE_INLINE Vec2<T>&	operator*=(const Vec2<T> &v);
	FORCE_INLINE Vec2<T>&	operator*=(T s);
	FORCE_INLINE Vec2<T>&	operator/=(const Vec2<T> &v);
	FORCE_INLINE Vec2<T>&	operator/=(T s);
	FORCE_INLINE Vec2<T>&	operator+=(T fl);
	FORCE_INLINE Vec2<T>&	operator-=(T fl);
	//inline std::ostream &   operator<<(std::ostream &os) const;
	inline T	Length() const;
	FORCE_INLINE T LengthSqr(void) const
	{
		CHECK_VALID(*this);
		return (x*x + y*y);
	}
	bool IsZero(T tolerance = 0.01f) const
	{
		return (x > -tolerance && x < tolerance &&
			y > -tolerance && y < tolerance);
	}
	void	NormalizeInPlace();
	FORCE_INLINE T	DistToSqr(const Vec2<T> &vOther) const;
	T	Dot(const Vec2<T>& vOther) const;
	T	Length2D(void) const;
	T	Length2DSqr(void) const;
	Vec2<T>& operator=(const Vec2<T> &vOther);
	Vec2<T>	operator+(const Vec2<T>& v) const;
	Vec2<T>	operator-(const Vec2<T>& v) const;
	Vec2<T>	operator*(const Vec2<T>& v) const;
	Vec2<T>	operator/(const Vec2<T>& v) const;
	Vec2<T>	operator*(T fl) const;
	Vec2<T>	operator/(T fl) const;

    friend std::ostream & operator<<(std::ostream &os, const Vec2<T>& v) 
    {
        return os << v.x << ' ' << v.y;
	}
	
};


template <typename T>
inline void Vec2<T>::Init(T ix, T iy)
{
	x = ix; y = iy;;
	CHECK_VALID(*this);
}

template <typename T>
inline Vec2<T>::Vec2(T X, T Y)
{
	x = X; y = Y;
	CHECK_VALID(*this);
}

template <typename T>
inline Vec2<T>::Vec2(T i)
{
	x = y = i;
	CHECK_VALID(*this);
}

template <typename T>
inline Vec2<T>::Vec2(void)
{
}

template <typename T>
inline void Vec2<T>::Zero()
{
	x = y = 0.f;
}

template <typename T>
inline void Clear(Vec2<T>& a)
{
	a.x = a.y = 0.f;
}

template <typename T>
inline Vec2<T> & Vec2<T>::operator++()
{
    x++;
    y++;
    return *this;
}

template <typename T>
inline Vec2<T> Vec2<T>::operator++(int)
{
    Vec2<T> temp = *this;
    x++;
    y++;
    return temp;
}

template <typename T>
inline Vec2<T>& Vec2<T>::operator=(const Vec2<T> &vOther)
{
	CHECK_VALID(vOther);
	x = vOther.x; y = vOther.y;
	return *this;
}

template <typename T>
inline T& Vec2<T>::operator[](int i)
{
	Assert((i >= 0) && (i < 3));
	return ((T*)this)[i];
}

template <typename T>
inline T Vec2<T>::operator[](int i) const
{
	Assert((i >= 0) && (i < 3));
	return ((T*)this)[i];
}

template <typename T>
inline bool Vec2<T>::operator==(const Vec2<T>& src) const
{
	CHECK_VALID(src);
	CHECK_VALID(*this);
	return (src.x == x) && (src.y == y);
}

template <typename T>
inline bool Vec2<T>::operator!=(const Vec2<T>& src) const
{
	CHECK_VALID(src);
	CHECK_VALID(*this);
	return (src.x != x) || (src.y != y);
}

template <typename T>
FORCE_INLINE void Copy(const Vec2<T>& src, Vec2<T>& dst)
{
	CHECK_VALID(src);
	dst.x = src.x;
	dst.y = src.y;
}

template <typename T>
FORCE_INLINE  Vec2<T>& Vec2<T>::operator+=(const Vec2<T>& v)
{
	CHECK_VALID(*this);
	CHECK_VALID(v);
	x += v.x; y += v.y;
	return *this;
}

template <typename T>
FORCE_INLINE  Vec2<T>& Vec2<T>::operator-=(const Vec2<T>& v)
{
	CHECK_VALID(*this);
	CHECK_VALID(v);
	x -= v.x; y -= v.y;
	return *this;
}

template <typename T>
FORCE_INLINE  Vec2<T>& Vec2<T>::operator*=(T fl)
{
	x *= fl;
	y *= fl;
	CHECK_VALID(*this);
	return *this;
}

template <typename T>
FORCE_INLINE  Vec2<T>& Vec2<T>::operator*=(const Vec2<T>& v)
{
	CHECK_VALID(v);
	x *= v.x;
	y *= v.y;
	CHECK_VALID(*this);
	return *this;
}
 
template <typename T>
FORCE_INLINE Vec2<T>&	Vec2<T>::operator+=(T fl)
{
	x += fl;
	y += fl;
	CHECK_VALID(*this);
	return *this;
}
 
template <typename T>
FORCE_INLINE Vec2<T>&	Vec2<T>::operator-=(T fl)
{
	x -= fl;
	y -= fl;
	CHECK_VALID(*this);
	return *this;
}
 
template <typename T>
FORCE_INLINE  Vec2<T>& Vec2<T>::operator/=(T fl)
{
	Assert(fl != 0.f);
	T oofl = 1.0f / fl;
	x *= oofl;
	y *= oofl;
	CHECK_VALID(*this);
	return *this;
}
 
template <typename T>
FORCE_INLINE  Vec2<T>& Vec2<T>::operator/=(const Vec2<T>& v)
{
	CHECK_VALID(v);
	Assert(v.x != 0.f && v.y != 0.f);
	x /= v.x;
	y /= v.y;
	CHECK_VALID(*this);
	return *this;
}
 
template <typename T>
inline T Vec2<T>::Length(void) const
{
	CHECK_VALID(*this);
 
	T root = 0.f;
 
	T sqsr = x*x + y*y;

	#if defined (__GNUC__) || defined (__clang__)
    __asm__("sqrtss %1, %0" : "=x" (root) : "x" (sqsr));
	#elif defined (_MSC_VER)
	__asm
	{
		sqrtss xmm0, sqsr
		movss root, xmm0
	}
	#elif
	return sqrt(sqsr);
	#endif

	return root;
}
 
template <typename T>
inline T Vec2<T>::Length2DSqr(void) const
{
	return (x*x + y*y);
}
 
template <typename T>
inline Vec2<T> CrossProduct(const Vec2<T>& a, const Vec2<T>& b)
{
	return Vec2<T>(a.x*b.y - a.y*b.x);
}
 
template <typename T>
T Vec2<T>::DistToSqr(const Vec2<T> &vOther) const
{
	Vec2<T> delta;
 
	delta.x = x - vOther.x;
	delta.y = y - vOther.y;
 
	return delta.LengthSqr();
}
 
template <typename T>
inline void Vec2<T>::NormalizeInPlace()
{
	Vec2<T>& v = *this;
 
	T iradius = 1.f / (this->Length() + 1.192092896e-07F); //FLT_EPSILON
 
	v.x *= iradius;
	v.y *= iradius;
    
}
 
template <typename T>
inline Vec2<T> Vec2<T>::operator+(const Vec2<T>& v) const
{
	Vec2<T> res;
	res.x = x + v.x;
	res.y = y + v.y;
	return res;
}
 
template <typename T>
inline Vec2<T> Vec2<T>::operator-(const Vec2<T>& v) const
{
	Vec2<T> res;
	res.x = x - v.x;
	res.y = y - v.y;
	return res;
}
 
template <typename T>
inline Vec2<T> Vec2<T>::operator*(T fl) const
{
	Vec2<T> res;
	res.x = x * fl;
	res.y = y * fl;
	return res;
}
 
template <typename T>
inline Vec2<T> Vec2<T>::operator*(const Vec2<T>& v) const
{
	Vec2<T> res;
	res.x = x * v.x;
	res.y = y * v.y;
	return res;
}
 
template <typename T>
inline Vec2<T> Vec2<T>::operator/(T fl) const
{
	Vec2<T> res;
	res.x = x / fl;
	res.y = y / fl;
	return res;
}
 
template <typename T>
inline Vec2<T> Vec2<T>::operator/(const Vec2<T>& v) const
{
	Vec2<T> res;
	res.x = x / v.x;
	res.y = y / v.y;
	return res;
}

template <typename T>
inline T Vec2<T>::Dot(const Vec2<T>& vOther) const
{
	const Vec2<T>& a = *this;
 
	return(a.x*vOther.x + a.y*vOther.y);
}

#endif //_VEC2_H_