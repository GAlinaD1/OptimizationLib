#pragma once
#include "stdafx.h"

namespace OptLib
{
	// https://docs.microsoft.com/ru-ru/cpp/parallel/auto-parallelization-and-auto-vectorization?view=msvc-170
	// https://www.intel.com/content/www/us/en/docs/intrinsics-guide/index.html#techs=AVX&cats=Store&ig_expand=6846,6917
	// https://habr.com/ru/company/intel/blog/205552/
	// https://chryswoods.com/vector_c++/immintrin.html

	/// <summary>
	/// An alias for std::array. It is required for the ease of RawPoint construction.
	/// </summary>
	template<size_t dim>
	using Point = std::array<double, dim>;
	/// elementwise addition of vector + vector
	template<size_t dim>
	Point<dim> operator+(const Point<dim>& arr1, const Point<dim>& arr2)
	{
		Point<dim> result{};

		__m256d x;
		__m256d y;

		constexpr size_t rg_size = 256/8 / sizeof(double);
		constexpr size_t itr = dim / rg_size;

		if constexpr (itr > 0)
		{
			for (size_t i = 0; i < itr; i++)
			{
				x = _mm256_loadu_pd(arr1.data() + i * rg_size);
				y = _mm256_loadu_pd(arr2.data() + i * rg_size);

				x = _mm256_add_pd(x, y);

				_mm256_storeu_pd(result.data() + i * rg_size, x);
			}
		}

		if constexpr (dim % rg_size != 0)
		{
			for (int i = itr * rg_size; i < dim; i++)
				result[i] = arr1[i] + arr2[i];
		}
		
	//	std::transform(arr1.begin(), arr1.end(), arr2.begin(), result.begin(), std::plus<> {});
		return result;
	}
	/// elementwise addition of vector + value
	Point<1> operator+ (Point<1>& p, double a )
	{
		p [0] += a;
		return p;
	}
	/// elementwise subtraction of vector - vector
	template<size_t dim>
	Point<dim> operator-(const Point<dim>& arr1, const Point<dim>& arr2)
	{
		Point<dim> result{};

		__m256d x;
		__m256d y;

		constexpr size_t rg_size = 256 / 8 / sizeof(double);

		constexpr size_t itr = dim / rg_size;

		if constexpr (itr > 0)
		{
			for (size_t i = 0; i < itr; i++)
			{
				x = _mm256_loadu_pd(arr1.data() + i * rg_size);
				y = _mm256_loadu_pd(arr2.data() + i * rg_size);

				x = _mm256_sub_pd(x, y);

				_mm256_storeu_pd(result.data() + i * rg_size, x);
			}
		}

		if constexpr (dim % rg_size != 0)
		{
			for (int i = itr * rg_size; i < dim; i++)
				result[i] = arr1[i] - arr2[i];
		}

	//	std::transform(arr1.begin(), arr1.end(), arr2.begin(), result.begin(), std::minus<> {});
		return result;
	}
	/// elementwise division vector / scalar
	template<size_t dim>
	Point<dim> operator/(const Point<dim>& arr, double val)
	{
		Point<dim> result;
		__m256d Val = _mm256_set1_pd(val);
		__m256d x;

		constexpr size_t rg_size = 256 / 8 / sizeof(double);

		constexpr size_t itr = dim / rg_size;

		if constexpr (itr > 0)
		{
			for (size_t i = 0; i < itr; i++)
			{
				x = _mm256_loadu_pd(arr.data() + i * rg_size);

				x = _mm256_div_pd(x, Val);

				_mm256_storeu_pd(result.data() + i * rg_size, x);
			}
		}

		if constexpr (dim % rg_size != 0)
		{
			for (int i = itr * rg_size; i < dim; i++)
				result[i] = arr[i] / val;
		}


	//	for (auto& elem : arr)
	//		elem /= val;
		return result;
	}
	/// elementwise division of vector / vector
	template<size_t dim>
	Point<dim> operator/(const Point<dim>& arr1, const Point<dim>& arr2)
	{
		Point<dim> result{};

		__m256d x;
		__m256d y;

		constexpr size_t rg_size = 256 / 8 / sizeof(double);

		constexpr size_t itr = dim / rg_size;

		if constexpr (itr > 0)
		{
			for (size_t i = 0; i < itr; i++)
			{
				x = _mm256_loadu_pd(arr1.data() + i * rg_size);
				y = _mm256_loadu_pd(arr2.data() + i * rg_size);

				x = _mm256_div_pd(x, y);

				_mm256_storeu_pd(result.data() + i * rg_size, x);
			}
		}

		if constexpr (dim % rg_size != 0)
		{
			for (int i = itr * rg_size; i < dim; i++)
				result[i] = arr1[i] / arr2[i];
		}

//		std::transform(arr1.begin(), arr1.end(),
//			arr2.begin(), result.begin(), [](double x, double y) {return x / y; });
		return result;
	}
	/// elementwise multiplication of vector * vector
	template<size_t dim>
	Point<dim> operator*(const Point<dim>& arr1, const Point<dim>& arr2)
	{
		Point<dim> result{};

		__m256d x;
		__m256d y;

		constexpr size_t rg_size = 256 / 8 / sizeof(double);
		constexpr size_t itr = dim / rg_size;

		if constexpr (itr > 0)
		{
			for (size_t i = 0; i < itr; i++)
			{
				x = _mm256_loadu_pd(arr1.data() + i * rg_size);
				y = _mm256_loadu_pd(arr2.data() + i * rg_size);

				x = _mm256_mul_pd(x, y);

				_mm256_storeu_pd(result.data() + i * rg_size, x);
			}
		}

		if constexpr (dim % rg_size != 0)
		{
			for (int i = itr * rg_size; i < dim; i++)
				result[i] = arr1[i] * arr2[i];
		}

	//	std::transform(arr1.begin(), arr1.end(),
	//		arr2.begin(), result.begin(), [](double x, double y) {return x * y; });

		return result;
	}
	/// elementwise multiplication of vector * scalar
	template<size_t dim>
	Point<dim> operator*(const Point<dim>& arr, double val)
	{
		Point<dim> result;
		__m256d Val = _mm256_set1_pd(val);
		__m256d x;

		constexpr size_t rg_size = 256 / 8 / sizeof(double);

		constexpr size_t itr = dim / rg_size;

		if constexpr (itr > 0)
		{
			for (size_t i = 0; i < itr; i++)
			{
				x = _mm256_loadu_pd(arr.data() + i * rg_size);

				x = _mm256_mul_pd(x, Val);

				_mm256_storeu_pd(result.data() + i * rg_size, x);
			}
		}

		if constexpr (dim % rg_size != 0)
		{
			for (int i = itr * rg_size; i < dim; i++)
				result[i] = arr[i] * val;
		}
		return result;
	}
	template<size_t dim>
	Point<dim> operator*(double val, const Point<dim>& arr)
	{
		return arr * val;
	}
	/// elementwise sqrt bbb
	template<size_t dim>
	Point<dim> sqrt(const Point<dim>& arr)
	{
		Point<dim> result;
		__m256d x;

		constexpr size_t rg_size = 256 / 8 / sizeof(double);

		constexpr size_t itr = dim / rg_size;

		if constexpr (itr > 0)
		{
			for (size_t i = 0; i < itr; i++)
			{
				x = _mm256_loadu_pd(arr.data() + i * rg_size);
				x = _mm256_sqrt_pd(x);

				_mm256_storeu_pd(result.data() + i * rg_size, x);
			}
		}

		if constexpr (dim % rg_size != 0)
		{
			for (int i = itr * rg_size; i < dim; i++)
				result[i] = std::sqrt(arr[i]);
		}

		return result;
	}
	/// elementwise abs
	template<size_t dim>
	Point<dim> abs(const Point<dim>& arr)
	{
		Point<dim> result;
		__m256d x;
		static const __m256d signmask = _mm256_set1_pd(-0.0f); // 0x80000000
		constexpr size_t rg_size = 256 / 8 / sizeof(double);
		constexpr size_t itr = dim / rg_size;

		for (size_t i = 0; i < itr; i++)
		{
			x = _mm256_loadu_pd(arr.data() + i * rg_size);
			x = _mm256_andnot_pd(signmask, x);

			_mm256_storeu_pd(result.data() + i * rg_size, x);
		}

		if constexpr (dim % rg_size != 0)
		{
			for (int i = itr * rg_size; i < dim; i++)
				result[i] = std::abs(arr[i]);
		}
		return result;
	}
	/// scalar product of two vectors
	template <size_t dim>
	double dot_product(const Point<dim>& x, const Point<dim>& y)
	{
		auto z = x * y;

		double s = 0;
		for (int i = 0; i < dim; i++)
			s += z[i];
		return s;
	}
	template<size_t dim>
	std::ostream& operator<< (std::ostream& o, const Point<dim>& output)
	{
		o << "{ " << output[0];
		if constexpr (dim > 1)
		{
			for (int i = 1; i < dim; i++) {


				o << ", " << output[i];
			}
		}
		o << " }";

		return o;
	}

	/// <summary>
	/// Envelope for the Point<dim>
	/// </summary>
	template<size_t dim>
	struct RawPoint
	{
		//	RawPoint() = default;
		//	RawPoint(Point<dim>&& _P) :P{ std::move(_P)} {};
		//	RawPoint(const Point<dim>& _P) :P{ _P } {};

		Point<dim> P;
		double operator[](int i) const { return P[i]; }
		operator Point<dim>() { return P; }
	};
	///// elementwise addition of vector + vector
	//template<size_t dim>
	//RawPoint<dim> operator+(const RawPoint<dim>& arr1, const RawPoint<dim>& arr2)
	//{
	//	return RawPoint<dim>{std::move(arr1.P+arr2.P)};
	//}
	///// elementwise subtraction of vector - vector
	//template<size_t dim>
	//RawPoint<dim> operator-(const RawPoint<dim>& arr1, const RawPoint<dim>& arr2)
	//{
	//	return RawPoint<dim>{std::move(arr1.P-arr2.P)};
	//}
	///// elementwise division vector / scalar
	//template<size_t dim>
	//RawPoint<dim> operator/(RawPoint<dim> arr, double val)
	//{
	//	return RawPoint{ stq::move(arr.P / val) };
	//}
	///// elementwise division of vector / vector
	//template<size_t dim>
	//RawPoint<dim> operator/(const RawPoint<dim>& arr1, const RawPoint<dim>& arr2)
	//{
	//	return RawPoint<dim>{std::move(arr1.P / arr2.P)};
	//}
	///// elementwise multiplication of vector * vector
	//template<size_t dim>
	//RawPoint<dim> operator*(const RawPoint<dim>& arr1, const RawPoint<dim>& arr2)
	//{
	//	return RawPoint<dim>{std::move(arr1.P* arr2.P)};
	//}
	///// elementwise multiplication of vector * scalar
	//template<size_t dim>
	//RawPoint<dim> operator*(RawPoint<dim> arr, double val)
	//{
	//	return RawPoint<dim>{arr.P* val};
	//}
	template<size_t dim>
	std::ostream& operator<<(std::ostream& o, const RawPoint<dim>& r)
	{
		o << r.P; return o;
	}


	/// <summary>
	/// Point with associated Value. Essentially a {Point, Val}-pair with a comparator to sort Points
	/// </summary>
	template<size_t dim>
	struct PointVal : public RawPoint<dim>
	{
		double Val;
		PointVal() = default;
		PointVal(Point<dim>&& _P, double _Val) : RawPoint{ std::move(_P) }, Val{ _Val }{}
		PointVal(const Point<dim>& _P, double _Val) : RawPoint{ _P }, Val{ _Val }{}

		bool operator<(const PointVal& rhs)
		{
			return this->Val < rhs.Val;
		}
	};
	/// elementwise addition of vector + vector
	template<size_t dim>
	PointVal<dim> operator+(const PointVal<dim>& arr1, const PointVal<dim>& arr2)
	{
		return PointVal<dim>{std::move(arr1.P + arr2.P), arr1.Val + arr2.Val};
	}
	/// elementwise addition of vector + value
	PointVal<1> operator+(PointVal<1>& p, double a)
	{
		return PointVal<1>{std::move(p.P + a),p.Val};
	}
	/// elementwise subtraction of vector - vector
	template<size_t dim>
	PointVal<dim> operator-(const PointVal<dim>& arr1, const PointVal<dim>& arr2)
	{
		return PointVal<dim>{std::move(arr1.P - arr2.P), arr1.Val - arr2.Val};
	}
	/// elementwise division vector / scalar
	template<size_t dim>
	PointVal<dim> operator/(PointVal<dim> arr, double val)
	{
		return PointVal<dim>{ std::move(arr.P / val), arr.Val / val };
	}
	/// elementwise multiplication of vector * vector
	template<size_t dim>
	PointVal<dim> operator*(const PointVal<dim>& arr1, const PointVal<dim>& arr2)
	{
		return PointVal<dim>{std::move(arr1.P* arr2.P), arr1.Val* arr2.Val};
	}
	/// elementwise division of vector * vector
	template<size_t dim>
	PointVal<dim> operator/(const PointVal<dim>& arr1, const PointVal<dim>& arr2)
	{
		return PointVal<dim>{std::move(arr1.P/ arr2.P), arr1.Val/ arr2.Val};
	}
	///  elementwise sqrt nnn
	template<size_t dim>
	PointVal<dim> sqrt(const PointVal<dim>& p)
	{
		return PointVal<dim>{ sqrt<dim>(p.P), std::sqrt(p.Val) };
	}
	///  elementwise abs
	template<size_t dim>
	PointVal<dim> abs(const PointVal<dim>& p)
	{
		return PointVal<dim>{ abs<dim>(p.P), std::abs(p.Val) };
	}
	/// <summary>
	/// Distance between two points
	/// </summary>
	/// <param name="p1"></param>
	/// <param name="p2"></param>
	/// <returns></returns>
	template <size_t dim>
	double dist(const PointVal<dim>& p1, const PointVal<dim>& p2)
	{
		double res = 0.0;
		for (int i = 0; i < dim; i++)
			res += (p2[i] - p1[i]) * (p2[i] - p1[i]);

		return std::sqrt(res);
	}
	template<size_t dim>
	std::ostream& operator<<(std::ostream& o, const PointVal<dim>& r)
	{
		o << "{ " << r.P << ' ' << r.Val << " }"; return o;
	}

	/// <summary>
	/// coefficient of variation, mean/variance
	/// </summary>
	/// <typeparam name="point"></typeparam>
	/// <param name="avg"></param>
	/// <param name="disp"></param>
	/// <returns></returns>
	template<typename point>
	point VarCoef(const point& avg, const point& disp)
	{// requires sqrt(vector), abs(vector), vector/vector
		return abs(avg) / sqrt(disp);
	}

	template<size_t count, typename point>
	using SetOfPoints = std::array<point, count>;
	template<size_t count, typename point>
	std::ostream& operator<< (std::ostream& o, const SetOfPoints<count, point>& output)
	{
		o << "{ " << output[0];
		if constexpr (count > 1)
		{
			for (int i = 1; i < count; i++)
				o << "; " << output[i];
		}
		o << " }";

		return o;
	}


	/// <summary>
	/// A set of points of type point with +-*/ operators overloaded for calculation of Mean, Disp, and VarCoef
	/// </summary>
	/// <typeparam name="point"></typeparam>
	template<size_t count, typename point>
	class RawSetOfPoints
	{
	protected:
		SetOfPoints<count, point> ItsSetOfPoints;
	public:
		RawSetOfPoints() = default;
		RawSetOfPoints(SetOfPoints<count, point> && _s) : ItsSetOfPoints{ std::move(_s) } { }
		RawSetOfPoints(const SetOfPoints<count, point>& _s) : ItsSetOfPoints{ _s } { }
		const point& operator[](int i) const { return Points()[i]; }

		const SetOfPoints<count, point>& Points() const { return ItsSetOfPoints; }
		point Mean() const
		{ // requires vector+vector and vector/double
			point result{ Points()[0] };
			for (int i = 1; i < count; i++)
				result = result + Points()[i];
			result = result / (count + 0.0);
			return result;
		}
		std::pair<point, point> Dispersion() const
		{// requires vector+-*vector, vector/double
			point avg{ Mean() };
			point result = (Points()[0] - avg) * (Points()[0] - avg);

			for (int i = 1; i < count; i++)
				result = result + (Points()[i] - avg) * (Points()[i] - avg);

			return { avg, result / (count + 0.0) };
		}

		operator SetOfPoints<count, point>() { return Points(); }
	};
	template<size_t count, typename point>
	std::ostream& operator<< (std::ostream& o, const RawSetOfPoints<count, point>& output)
	{
		o << "{ " << output[0];
		for (int i = 1; i < count; i++)
			o << "; " << output[i];
		o << " }";
		return o;
	}

	/// <summary>
	/// Set of points with associated value. The calss makes PointVal from Point and Val
	/// </summary>
	/// <typeparam name="point"></typeparam>
	/// <typeparam name="pointval"></typeparam>
	template<size_t count, typename point, typename pointval>
	class SetOfPointVal : public RawSetOfPoints<count, pointval>
	{
	protected:
		static SetOfPoints<count, pointval> make_field(SetOfPoints<count, point>&& _s, std::array<double, count>&& FuncVals)
		{
			SetOfPoints<count, pointval> P;
			for (int i = 0; i < count; i++)
				P[i] = pointval{ std::move(_s[i]), FuncVals[i] };
			return P;
		}
	public:
		SetOfPointVal() = default;
		SetOfPointVal(SetOfPoints<count, pointval>&& _s) :
			RawSetOfPoints<count, pointval>{ std::move(_s) } { }
		SetOfPointVal(SetOfPoints<count, point>&& _s, std::array<double, count>&& funcVals) : // transforms points to points with vals
			SetOfPointVal<count, point, pointval>{ std::move(make_field(std::move(_s), std::move(funcVals))) } {}
	};

	/// <summary>
	/// A set of points of type {point with Val} with +-*/ operators overloaded for calculation of Mean, Disp, and VarCoef. The points are sorted according to Val-field.
	/// </summary>
	/// <typeparam name="point"></typeparam>
	template<size_t count, typename point, typename pointval>
	class SetOfPointValsSort : public SetOfPointVal<count, point, pointval>
	{
	private:
		void Sort() { std::sort(ItsSetOfPoints.begin(), ItsSetOfPoints.end()); }

	public:
		SetOfPointValsSort() = default;
			SetOfPointValsSort(SetOfPoints<count, pointval>&& _s) :
				SetOfPointVal<count, point, pointval>{ std::move(_s) } { this->Sort(); }
		SetOfPointValsSort(SetOfPoints<count, point>&& _s, std::array<double, count>&& funcVals) : // transforms points to points with vals
			SetOfPointVal<count, point, pointval>{ std::move(_s), std::move(funcVals) } {this->Sort(); }
	};

	template<size_t dim>
	using SimplexValNoSort = SetOfPointVal<dim + 1, Point<dim>, PointVal<dim>>;

	using Segment = SimplexValNoSort<1>;
	
	template<size_t dim>
	using SimplexValSort = SetOfPointValsSort<dim + 1, Point<dim>, PointVal<dim>>;
} // OptLib
