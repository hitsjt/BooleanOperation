#pragma once
#include <cmath>
#include <ostream>

#ifdef DEBUG
#include <exception>
#endif

#define DOUBLE_PI           6.28318530717958647692
#define PI                  3.14159265358979323846
#define HALF_PI             1.57079632679489661923

namespace Math
{
    class CVector2D
    {
    public:
        double x, y;
    public:
        CVector2D(void){}
        CVector2D(const CVector2D &v) : x(v.x), y(v.y){}
        CVector2D(double _x, double _y) : x(_x), y(_y){}
        ~CVector2D(void){}

        double Getx() const{return x;}
        void Setx(double value){x = value;}
        double Gety() const{return y;}
        void Sety(double value){y = value;}

		//得到一个零向量
        static CVector2D &GetZero()
        {
            static CVector2D zero(0, 0);
            return zero;
        }
		//得到向量的长度
        double GetLength(void) const
        {
            double length_square = 0.0;
            length_square += x * x;
            length_square += y * y;

            if (length_square == 0.0)
                return double(0.0);
            return sqrt(length_square);
        }
		//得到向量长度的平方
        double GetLengthSquare(void) const
        {
            double length_square = 0.0f;
            length_square += x * x;
            length_square += y * y;
            return length_square;
        }
		//求得该点和v点之间的距离
        double Distance(const CVector2D &v) const
        {
            double length_square = 0.0f;
            length_square += (x - v.x) * (x - v.x);
            length_square += (y - v.y) * (y - v.y);

            if (length_square == 0.0)
                return 0.0;
            return sqrt(length_square);
        }
		//求得该点和v点之间的距离的平方
        double DistanceSquare(const CVector2D &v) const
        {
            double length_square = 0.0f;
            length_square += (x - v.x) * (x - v.x);
            length_square += (y - v.y) * (y - v.y);
            return length_square;
        }
		//将向量单位化，向量发生改变
        CVector2D &Normalize(void)
        {
            *this /= this->GetLength();
            return *this;
        }
		//求得向量的单位化向量，向量本身不改变
        CVector2D GetUnit(void) const
        {
            CVector2D retval(*this);
            retval.Normalize();
            return retval;
        }
		//向量赋值
        CVector2D &operator=(const CVector2D &v)       // assignment
        {
            this->x = v.x;
            this->y = v.y;
            return *this;
        }
		//向量+=
        CVector2D &operator+= (const CVector2D &v)
        {
            this->x += v.x;
            this->y += v.y;
            return *this;
        }
		//向量-=
        CVector2D &operator-= (const CVector2D &v)
        {
            this->x -= v.x;
            this->y -= v.y;
            return *this;
        }
		//向量*=
        CVector2D &operator*= (double k)
        {
            this->x *= k;
            this->y *= k;
            return *this;
        }
		//向量/=
        CVector2D &operator/= (double k)
        {
#ifdef DEBUG
            if (k == 0.0)
                throw std::exception("Divide by Zero");
#endif
            this->x /= k;
            this->y /= k;
            return *this;
        }
		//向量加法
        CVector2D operator+(const CVector2D &v) const
        {
            CVector2D retval;
            retval.x = x + v.x;
            retval.y = y + v.y;
            return retval;
        }
		//向量减法
        CVector2D operator-(const CVector2D &v) const
        {
            CVector2D retval;
            retval.x = x - v.x;
            retval.y = y - v.y;
            return retval;
        }
		//向量与数值乘法
        CVector2D operator*(double k) const
        {
            CVector2D retval;
            retval.x = x * k;
            retval.y = y * k;
            return retval;
        }
		//向量与数值除法
        CVector2D operator/(double k) const
        {
#ifdef DEBUG
            if (k == 0.0)
                throw std::exception("Divide by Zero");
#endif
            CVector2D retval;
            retval.x = x / k;
            retval.y = y / k;
            return retval;
        }
		//向量取反
        CVector2D operator-() const
        {
            CVector2D retval;
            retval.x = -x;
            retval.y = -y;
            return retval;
        }
		//向量叉积
        double operator^(const CVector2D &v) const
        {
            return (this->x * v.y - this->y * v.x);
        }
		//向量点乘
        double operator*(const CVector2D &v) const  // dot product
        {
            double retval = 0.0f;
            retval += x * v.x;
            retval += y * v.y;
            return retval;
        }
		//判断向量是否相等
        bool operator==(const CVector2D &v) const
        {
            if(x != v.x || y != v.y)
                return false;
            return true;
        }
		//判断向量是否不相等
        bool operator!=(const CVector2D &v) const
        {
            if(x != v.x || y != v.y)
                return true;
            return false;
        }
		//[]取值
        const double &operator[](unsigned int index) const
        {
            if (index == 0)
                return x;
            else if (index == 1)
                return y;
            else
            {
#ifdef DEBUG
                throw std::exception("out of data");
#endif
            }
        }
		//[]取x,y值并可修改
        double &operator[](unsigned int index)
        {
            if (index == 0)
                return x;
            else if (index == 1)
                return y;
            else
            {
#ifdef DEBUG
                throw std::exception("out of data");
#endif
            }
        }
		//()取值
        const double &operator()(unsigned int index) const
        {
            if (index == 0)
                return x;
            else if (index == 1)
                return y;
            else
            {
#ifdef DEBUG
                throw std::exception("out of data");
#endif
            }
        }
		//()取x，y并可以修改
        double &operator()(unsigned int index)
        {
            if (index == 0)
                return x;
            else if (index == 1)
                return y;
            else
            {
#ifdef DEBUG
                throw std::exception("out of data");
#endif
            }
        }
    };

	/*
	为了在浮点数运算时可以接受一定的误差范围。避免因绝对数值计算导致的错误。
	在做数值和向量的相等、为0、大小判断时，合理使用容差，尽量不要使用绝对判断。
	例如不要使用if(a==0),而应该使用if(tolerance1.isZero(a))
	*/
    class CTolerance
    {
    public:
        double ToleranceValue;
        double SquareToleranceValue;
    public:
        CTolerance(double tolerance): ToleranceValue(tolerance) {
            SquareToleranceValue = tolerance * tolerance;
        }
		//判断两个数值相等
        inline bool AreEqual(double a, double b) const
        {
            return abs(a - b) < ToleranceValue;
        }
		//判断一个数值是否为0
        inline bool IsZero(double value) const
        {
            return abs(value) < ToleranceValue;
        }

        inline bool AreSquareEqual(double a, double b) const
        {
            return abs(a - b) < SquareToleranceValue;
        }

        inline bool AreSquareZero(double value) const
        {
            return abs(value) < SquareToleranceValue;
        }
		//判断两个向量是否相等
        inline bool AreEqual(const CVector2D & a, const CVector2D & b) const
        {
            if (!AreEqual(a.x, b.x) || !AreEqual(a.y, b.y))
                return false;
            return true;
        }

        inline bool IsZero(const CVector2D & vec) const
        {
            if (!IsZero(vec.x) || !IsZero(vec.y))
                return false;
            return true;
        }

        inline bool ContainsIncludeEnds(double value, double left, double right) const
        {
            return ((value > left - ToleranceValue) && (value < right + ToleranceValue));
        }

        inline bool ContainsExcludeEnds(double value, double left, double right) const
        {
            return ((value > left + ToleranceValue) && (value < right - ToleranceValue));
        }

        inline bool operator==(double value) const
        {
            return IsZero(value);
        }

        inline bool operator < (double value) const
        {
            return value < -ToleranceValue;
        }

        inline bool operator <= (double value) const
        {
            return value < ToleranceValue;
        }

        inline bool operator > (double value) const
        {
            return value > ToleranceValue;
        }

        inline bool operator >= (double value) const
        {
            return value > -ToleranceValue;
        }
		//判断两个向量是否平行
        bool AreParallel(const CVector2D &a, const CVector2D &b) const
        {
#ifdef DEBUG
            if (IsZero(a) || IsZero(b))
                throw std::exception("Cannot judge zero vector parallel");
#endif
            double cosine = a.GetUnit() * b.GetUnit();
            return AreEqual(abs(cosine), 1.0);
        }
    };
}

typedef Math::CVector2D vec2;
//使用二维向量CVector2D时，均可简写为vec2

#define Tolerance CTolerance(1.0e-10)
#define Tolerance2 CTolerance(5.0f)   // 因为这个容差是为了判断在图像区域选择、移动多边形操作，所以较大，为了方便选定到多边形

extern vec2 operator*(double k, const vec2 &v);
extern bool operator < (double value, const Math::CTolerance& tolerance);
extern bool operator <= (double value, const Math::CTolerance& tolerance);
extern bool operator > (double value, const Math::CTolerance& tolerance);
extern bool operator >= (double value, const Math::CTolerance& tolerance);