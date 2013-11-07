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

		//�õ�һ��������
        static CVector2D &GetZero()
        {
            static CVector2D zero(0, 0);
            return zero;
        }
		//�õ������ĳ���
        double GetLength(void) const
        {
            double length_square = 0.0;
            length_square += x * x;
            length_square += y * y;

            if (length_square == 0.0)
                return double(0.0);
            return sqrt(length_square);
        }
		//�õ��������ȵ�ƽ��
        double GetLengthSquare(void) const
        {
            double length_square = 0.0f;
            length_square += x * x;
            length_square += y * y;
            return length_square;
        }
		//��øõ��v��֮��ľ���
        double Distance(const CVector2D &v) const
        {
            double length_square = 0.0f;
            length_square += (x - v.x) * (x - v.x);
            length_square += (y - v.y) * (y - v.y);

            if (length_square == 0.0)
                return 0.0;
            return sqrt(length_square);
        }
		//��øõ��v��֮��ľ����ƽ��
        double DistanceSquare(const CVector2D &v) const
        {
            double length_square = 0.0f;
            length_square += (x - v.x) * (x - v.x);
            length_square += (y - v.y) * (y - v.y);
            return length_square;
        }
		//��������λ�������������ı�
        CVector2D &Normalize(void)
        {
            *this /= this->GetLength();
            return *this;
        }
		//��������ĵ�λ�����������������ı�
        CVector2D GetUnit(void) const
        {
            CVector2D retval(*this);
            retval.Normalize();
            return retval;
        }
		//������ֵ
        CVector2D &operator=(const CVector2D &v)       // assignment
        {
            this->x = v.x;
            this->y = v.y;
            return *this;
        }
		//����+=
        CVector2D &operator+= (const CVector2D &v)
        {
            this->x += v.x;
            this->y += v.y;
            return *this;
        }
		//����-=
        CVector2D &operator-= (const CVector2D &v)
        {
            this->x -= v.x;
            this->y -= v.y;
            return *this;
        }
		//����*=
        CVector2D &operator*= (double k)
        {
            this->x *= k;
            this->y *= k;
            return *this;
        }
		//����/=
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
		//�����ӷ�
        CVector2D operator+(const CVector2D &v) const
        {
            CVector2D retval;
            retval.x = x + v.x;
            retval.y = y + v.y;
            return retval;
        }
		//��������
        CVector2D operator-(const CVector2D &v) const
        {
            CVector2D retval;
            retval.x = x - v.x;
            retval.y = y - v.y;
            return retval;
        }
		//��������ֵ�˷�
        CVector2D operator*(double k) const
        {
            CVector2D retval;
            retval.x = x * k;
            retval.y = y * k;
            return retval;
        }
		//��������ֵ����
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
		//����ȡ��
        CVector2D operator-() const
        {
            CVector2D retval;
            retval.x = -x;
            retval.y = -y;
            return retval;
        }
		//�������
        double operator^(const CVector2D &v) const
        {
            return (this->x * v.y - this->y * v.x);
        }
		//�������
        double operator*(const CVector2D &v) const  // dot product
        {
            double retval = 0.0f;
            retval += x * v.x;
            retval += y * v.y;
            return retval;
        }
		//�ж������Ƿ����
        bool operator==(const CVector2D &v) const
        {
            if(x != v.x || y != v.y)
                return false;
            return true;
        }
		//�ж������Ƿ����
        bool operator!=(const CVector2D &v) const
        {
            if(x != v.x || y != v.y)
                return true;
            return false;
        }
		//[]ȡֵ
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
		//[]ȡx,yֵ�����޸�
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
		//()ȡֵ
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
		//()ȡx��y�������޸�
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
	Ϊ���ڸ���������ʱ���Խ���һ������Χ�������������ֵ���㵼�µĴ���
	������ֵ����������ȡ�Ϊ0����С�ж�ʱ������ʹ���ݲ������Ҫʹ�þ����жϡ�
	���粻Ҫʹ��if(a==0),��Ӧ��ʹ��if(tolerance1.isZero(a))
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
		//�ж�������ֵ���
        inline bool AreEqual(double a, double b) const
        {
            return abs(a - b) < ToleranceValue;
        }
		//�ж�һ����ֵ�Ƿ�Ϊ0
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
		//�ж����������Ƿ����
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
		//�ж����������Ƿ�ƽ��
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
//ʹ�ö�ά����CVector2Dʱ�����ɼ�дΪvec2

#define Tolerance CTolerance(1.0e-10)
#define Tolerance2 CTolerance(5.0f)   // ��Ϊ����ݲ���Ϊ���ж���ͼ������ѡ���ƶ�����β��������Խϴ�Ϊ�˷���ѡ���������

extern vec2 operator*(double k, const vec2 &v);
extern bool operator < (double value, const Math::CTolerance& tolerance);
extern bool operator <= (double value, const Math::CTolerance& tolerance);
extern bool operator > (double value, const Math::CTolerance& tolerance);
extern bool operator >= (double value, const Math::CTolerance& tolerance);