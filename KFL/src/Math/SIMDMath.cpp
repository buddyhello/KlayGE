/**
 * @file SIMDMath.cpp
 * @author Minmin Gong
 *
 * @section DESCRIPTION
 *
 * This source file is part of KFL, a subproject of KlayGE
 * For the latest info, see http://www.klayge.org
 *
 * @section LICENSE
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published
 * by the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * You may alternatively use this source under the terms of
 * the KlayGE Proprietary License (KPL). You can obtained such a license
 * from http://www.klayge.org/licensing/.
 */

#include <KFL/KFL.hpp>
#include <KFL/SIMDMath.hpp>

#pragma warning(disable: 4100) // Will be removed after all functions are implemented

namespace KlayGE
{
	namespace SIMDMathLib
	{
		// General Vector
		///////////////////////////////////////////////////////////////////////////////
		SIMDVectorF4 Add(SIMDVectorF4 const & lhs, SIMDVectorF4 const & rhs)
		{
			SIMDVectorF4 ret;
#if defined(SIMD_MATH_SSE)
			UNREF_PARAM(lhs);
			UNREF_PARAM(rhs);
			// TODO
#else
			for (int i = 0; i < 4; ++ i)
			{
				ret.Vec()[i] = lhs.Vec()[i] + rhs.Vec()[i];
			}
#endif
			return ret;
		}

		SIMDVectorF4 Substract(SIMDVectorF4 const & lhs, SIMDVectorF4 const & rhs)
		{
			SIMDVectorF4 ret;
#if defined(SIMD_MATH_SSE)
			UNREF_PARAM(lhs);
			UNREF_PARAM(rhs);
			// TODO
#else
			for (int i = 0; i < 4; ++ i)
			{
				ret.Vec()[i] = lhs.Vec()[i] - rhs.Vec()[i];
			}
#endif
			return ret;
		}

		SIMDVectorF4 Multiply(SIMDVectorF4 const & lhs, SIMDVectorF4 const & rhs)
		{
			SIMDVectorF4 ret;
#if defined(SIMD_MATH_SSE)
			UNREF_PARAM(lhs);
			UNREF_PARAM(rhs);
			// TODO
#else
			for (int i = 0; i < 4; ++ i)
			{
				ret.Vec()[i] = lhs.Vec()[i] * rhs.Vec()[i];
			}
#endif
			return ret;
		}

		SIMDVectorF4 Divide(SIMDVectorF4 const & lhs, SIMDVectorF4 const & rhs)
		{
			SIMDVectorF4 ret;
#if defined(SIMD_MATH_SSE)
			UNREF_PARAM(lhs);
			UNREF_PARAM(rhs);
			// TODO
#else
			for (int i = 0; i < 4; ++ i)
			{
				ret.Vec()[i] = lhs.Vec()[i] / rhs.Vec()[i];
			}
#endif
			return ret;
		}

		SIMDVectorF4 Negative(SIMDVectorF4 const & rhs)
		{
			SIMDVectorF4 ret;
#if defined(SIMD_MATH_SSE)
			UNREF_PARAM(rhs);
			// TODO
#else
			for (int i = 0; i < 4; ++ i)
			{
				ret.Vec()[i] = -rhs.Vec()[i];
			}
#endif
			return ret;
		}

		SIMDVectorF4 BaryCentric(SIMDVectorF4 const & v1, SIMDVectorF4 const & v2, SIMDVectorF4 const & v3,
			float f, float g)
		{
			return (1 - f - g) * v1 + f * v2 + g * v3;
		}

		SIMDVectorF4 CatmullRom(SIMDVectorF4 const & v0, SIMDVectorF4 const & v1,
			SIMDVectorF4 const & v2, SIMDVectorF4 const & v3, float s)
		{
			float const s2 = s * s;
			float const s3 = s2 * s;
			return ((-s3 + 2 * s2 - s) * v0 + (3 * s3 - 5 * s2 + 2) * v1
				+ (-3 * s3 + 4 * s2 + s) * v2 + (s3 - s2) * v3) * 0.5f;
		}

		SIMDVectorF4 CubicBezier(SIMDVectorF4 const & v0, SIMDVectorF4 const & v1,
			SIMDVectorF4 const & v2, SIMDVectorF4 const & v3, float s)
		{
			// From http://en.wikipedia.org/wiki/B%C3%A9zier_curve

			float const s2 = s * s;
			float const s3 = s2 * s;
			return ((-s3 + 3 * s2 - 3 * s + 1) * v0 + (3 * s3 - 6 * s2 + 3 * s) * v1
				+ (-3 * s3 + 3 * s2) * v2 + s3 * v3);
		}

		SIMDVectorF4 CubicBSpline(SIMDVectorF4 const & v0, SIMDVectorF4 const & v1,
			SIMDVectorF4 const & v2, SIMDVectorF4 const & v3, float s)
		{
			// From http://en.wikipedia.org/wiki/B-spline

			float const s2 = s * s;
			float const s3 = s2 * s;
			return ((-s3 + 3 * s2 - 3 * s + 1) * v0 + (3 * s3 - 6 * s2 + 4) * v1
				+ (-3 * s3 + 3 * s2 + 3 * s + 1) * v2 + s3 * v3) / 6;
		}

		SIMDVectorF4 Hermite(SIMDVectorF4 const & v1, SIMDVectorF4 const & t1,
			SIMDVectorF4 const & v2, SIMDVectorF4 const & t2, float s)
		{
			float const s2 = s * s;
			float const s3 = s2 * s;
			float const h1 = 2 * s3 - 3 * s2 + 1;
			float const h2 = s3 - 2 * s2 + s;
			float const h3 = -2 * s3 + 3 * s2;
			float const h4 = s3 - s2;
			return h1 * v1 + h2 * t1 + h3 * v2 + h4 * t2;
		}

		SIMDVectorF4 Lerp(SIMDVectorF4 const & lhs, SIMDVectorF4 const & rhs, float s)
		{
			return lhs + (rhs - lhs) * s;
		}

		SIMDVectorF4 Abs(SIMDVectorF4 const & x)
		{
			SIMDVectorF4 ret;
#if defined(SIMD_MATH_SSE)
			// TODO
#else
			for (int i = 0; i < 4; ++ i)
			{
				ret.Vec()[i] = MathLib::abs(x.Vec()[i]);
			}
#endif
			return ret;
		}

		SIMDVectorF4 Sgn(SIMDVectorF4 const & x)
		{
			SIMDVectorF4 ret;
#if defined(SIMD_MATH_SSE)
			// TODO
#else
			for (int i = 0; i < 4; ++ i)
			{
				ret.Vec()[i] = MathLib::sgn(x.Vec()[i]);
			}
#endif
			return ret;
		}

		SIMDVectorF4 Sqr(SIMDVectorF4 const & x)
		{
			return x * x;
		}

		SIMDVectorF4 Cube(SIMDVectorF4 const & x)
		{
			return Sqr(x) * x;
		}

		SIMDVectorF4 LoadVector1(float v)
		{
			SIMDVectorF4 ret;
#if defined(SIMD_MATH_SSE)
			ret.Vec() = _mm_load_ss(&v);
#else
			ret.Vec()[0] = v;
			for (int i = 1; i < 4; ++ i)
			{
				ret.Vec()[i] = 0;
			}
#endif
			return ret;
		}

		SIMDVectorF4 LoadVector2(float2 const & v)
		{
			return LoadVector2(&v[0]);
		}

		SIMDVectorF4 LoadVector3(float3 const & v)
		{
			return LoadVector3(&v[0]);
		}

		SIMDVectorF4 LoadVector4(float4 const & v)
		{
			return LoadVector4(&v[0]);
		}

		SIMDVectorF4 LoadVector2(float const * v)
		{
			SIMDVectorF4 ret;
#if defined(SIMD_MATH_SSE)
			__m128 x = _mm_load_ss(&v[0]);
			__m128 y = _mm_load_ss(&v[1]);
			ret.Vec() = _mm_unpacklo_ps(x, y);
#else
			for (int i = 0; i < 2; ++ i)
			{
				ret.Vec()[i] = v[i];
			}
			for (int i = 2; i < 4; ++ i)
			{
				ret.Vec()[i] = 0;
			}
#endif
			return ret;
		}

		SIMDVectorF4 LoadVector3(float const * v)
		{
			SIMDVectorF4 ret;
#if defined(SIMD_MATH_SSE)
			__m128 x = _mm_load_ss(&v[0]);
			__m128 y = _mm_load_ss(&v[1]);
			__m128 z = _mm_load_ss(&v[2]);
			__m128 xy = _mm_unpacklo_ps(x, y);
			ret.Vec() = _mm_movelh_ps(xy, z);
#else
			for (int i = 0; i < 3; ++ i)
			{
				ret.Vec()[i] = v[i];
			}
			for (int i = 3; i < 4; ++ i)
			{
				ret.Vec()[i] = 0;
			}
#endif
			return ret;
		}

		SIMDVectorF4 LoadVector4(float const * v)
		{
			SIMDVectorF4 ret;
#if defined(SIMD_MATH_SSE)
			ret.Vec() = _mm_load_ps(&v[0]);
#else
			for (int i = 0; i < 4; ++i)
			{
				ret.Vec()[i] = v[i];
			}
#endif
			return ret;
		}

		void StoreVector1(float& fs, SIMDVectorF4 const & v)
		{
#if defined(SIMD_MATH_SSE)
			_mm_store_ss(&fs, v.Vec());
#else
			fs = v.Vec()[0];
#endif
		}

		void StoreVector2(float2& fs, SIMDVectorF4 const & v)
		{
#if defined(SIMD_MATH_SSE)
			__m128 x = v.Vec();
			__m128 y = _mm_shuffle_ps(x, x, _MM_SHUFFLE(1, 1, 1, 1));
			_mm_store_ss(&fs[0], x);
			_mm_store_ss(&fs[1], y);
#else
			for (int i = 0; i < 2; ++ i)
			{
				fs[i] = v.Vec()[i];
			}
#endif
		}

		void StoreVector3(float3& fs, SIMDVectorF4 const & v)
		{
#if defined(SIMD_MATH_SSE)
			__m128 x = v.Vec();
			__m128 y = _mm_shuffle_ps(x, x, _MM_SHUFFLE(1, 1, 1, 1));
			__m128 z = _mm_shuffle_ps(x, x, _MM_SHUFFLE(2, 2, 2, 2));
			_mm_store_ss(&fs[0], x);
			_mm_store_ss(&fs[1], y);
			_mm_store_ss(&fs[2], z);
#else
			for (int i = 0; i < 3; ++ i)
			{
				fs[i] = v.Vec()[i];
			}
#endif
		}

		void StoreVector4(float4& fs, SIMDVectorF4 const & v)
		{
#if defined(SIMD_MATH_SSE)
			_mm_store_ps(&fs[0], v.Vec());
#else
			for (int i = 0; i < 4; ++ i)
			{
				fs[i] = v.Vec()[i];
			}
#endif
		}

		SIMDVectorF4 SetVector(float x, float y, float z, float w)
		{
			SIMDVectorF4 ret;
#if defined(SIMD_MATH_SSE)
			ret.Vec() = _mm_set_ps(x, y, z, w);
#else
			ret.Vec()[0] = x;
			ret.Vec()[1] = y;
			ret.Vec()[2] = z;
			ret.Vec()[3] = w;
#endif
			return ret;
		}

		SIMDVectorF4 SetVector(float v)
		{
			SIMDVectorF4 ret;
#if defined(SIMD_MATH_SSE)
			ret.Vec() = _mm_set_ps1(v);
#else
			ret.Vec()[0] = v;
			ret.Vec()[1] = v;
			ret.Vec()[2] = v;
			ret.Vec()[3] = v;
#endif
			return ret;
		}

		float GetX(SIMDVectorF4 const & rhs)
		{
#if defined(SIMD_MATH_SSE)
			return _mm_cvtss_f32(rhs.Vec());
#else
			return GetByIndex(rhs, 0);
#endif
		}

		float GetY(SIMDVectorF4 const & rhs)
		{
#if defined(SIMD_MATH_SSE)
			__m128 tmp = _mm_shuffle_ps(rhs.Vec(), rhs.Vec(), _MM_SHUFFLE(1, 1, 1, 1));
			return _mm_cvtss_f32(tmp);
#else
			return GetByIndex(rhs, 1);
#endif
		}

		float GetZ(SIMDVectorF4 const & rhs)
		{
#if defined(SIMD_MATH_SSE)
			__m128 tmp = _mm_shuffle_ps(rhs.Vec(), rhs.Vec(), _MM_SHUFFLE(2, 2, 2, 2));
			return _mm_cvtss_f32(tmp);
#else
			return GetByIndex(rhs, 2);
#endif
		}

		float GetW(SIMDVectorF4 const & rhs)
		{
#if defined(SIMD_MATH_SSE)
			__m128 tmp = _mm_shuffle_ps(rhs.Vec(), rhs.Vec(), _MM_SHUFFLE(3, 3, 3, 3));
			return _mm_cvtss_f32(tmp);
#else
			return GetByIndex(rhs, 3);
#endif
		}

		float GetByIndex(SIMDVectorF4 const & rhs, size_t index)
		{
#if defined(SIMD_MATH_SSE)
			return rhs.Vec().m128_f32[index];
#else
			return rhs.Vec()[index];
#endif
		}

		SIMDVectorF4 SetX(SIMDVectorF4 const & rhs, float v)
		{
#if defined(SIMD_MATH_SSE)
			SIMDVectorF4 ret;
			ret.Vec() = _mm_move_ss(rhs.Vec(), _mm_set_ss(v));
			return ret;
#else
			return SetByIndex(rhs, v, 0);
#endif
		}

		SIMDVectorF4 SetY(SIMDVectorF4 const & rhs, float v)
		{
#if defined(SIMD_MATH_SSE)
			SIMDVectorF4 ret;
			__m128 yxzw = _mm_shuffle_ps(rhs.Vec(), rhs.Vec(), _MM_SHUFFLE(3, 2, 0, 1));
			yxzw = _mm_move_ss(yxzw, _mm_set_ss(v));
			ret.Vec() = _mm_shuffle_ps(yxzw, yxzw, _MM_SHUFFLE(3, 2, 0, 1));
			return ret;
#else
			return SetByIndex(rhs, v, 1);
#endif
		}

		SIMDVectorF4 SetZ(SIMDVectorF4 const & rhs, float v)
		{
#if defined(SIMD_MATH_SSE)
			SIMDVectorF4 ret;
			__m128 zyxw = _mm_shuffle_ps(rhs.Vec(), rhs.Vec(), _MM_SHUFFLE(3, 0, 1, 2));
			zyxw = _mm_move_ss(zyxw, _mm_set_ss(v));
			ret.Vec() = _mm_shuffle_ps(zyxw, zyxw, _MM_SHUFFLE(3, 0, 1, 2));
			return ret;
#else
			return SetByIndex(rhs, v, 2);
#endif
		}

		SIMDVectorF4 SetW(SIMDVectorF4 const & rhs, float v)
		{
#if defined(SIMD_MATH_SSE)
			SIMDVectorF4 ret;
			__m128 wyzx = _mm_shuffle_ps(rhs.Vec(), rhs.Vec(), _MM_SHUFFLE(0, 2, 1, 3));
			wyzx = _mm_move_ss(wyzx, _mm_set_ss(v));
			ret.Vec() = _mm_shuffle_ps(wyzx, wyzx, _MM_SHUFFLE(0, 2, 1, 3));
			return ret;
#else
			return SetByIndex(rhs, v, 3);
#endif
		}

		SIMDVectorF4 SetByIndex(SIMDVectorF4 const & rhs, float v, size_t index)
		{
			SIMDVectorF4 ret = rhs;
#if defined(SIMD_MATH_SSE)
			ret.Vec().m128_f32[index] = v;
#else
			ret.Vec()[index] = v;
#endif
			return ret;
		}

		SIMDVectorF4 Maximize(SIMDVectorF4 const & lhs, SIMDVectorF4 const & rhs)
		{
			SIMDVectorF4 ret;
#if defined(SIMD_MATH_SSE)
			// TODO
#else
			for (int i = 0; i < 4; ++ i)
			{
				ret.Vec()[i] = std::max(lhs.Vec()[i], rhs.Vec()[i]);
			}
#endif
			return ret;
		}

		SIMDVectorF4 Minimize(SIMDVectorF4 const & lhs, SIMDVectorF4 const & rhs)
		{
			SIMDVectorF4 ret;
#if defined(SIMD_MATH_SSE)
			// TODO
#else
			for (int i = 0; i < 4; ++ i)
			{
				ret.Vec()[i] = std::min(lhs.Vec()[i], rhs.Vec()[i]);
			}
#endif
			return ret;
		}

		SIMDVectorF4 Reflect(SIMDVectorF4 const & incident, SIMDVectorF4 const & normal)
		{
			return incident - 2 * DotVector3(incident, normal) * normal;
		}

		SIMDVectorF4 Refract(SIMDVectorF4 const & incident, SIMDVectorF4 const & normal, float refraction_index)
		{
			float t = GetX(DotVector3(incident, normal));
			float r = 1 - refraction_index * refraction_index * (1 - t * t);

			if (r < 0)
			{
				// Total internal reflection
				return SIMDVectorF4::Zero();
			}
			else
			{
				float s = refraction_index * t + sqrt(abs(r));
				return refraction_index * incident - s * normal;
			}
		}

		// 2D Vector
		///////////////////////////////////////////////////////////////////////////////
		SIMDVectorF4 CrossVector2(SIMDVectorF4 const & lhs, SIMDVectorF4 const & rhs)
		{
			SIMDVectorF4 ret;
#if defined(SIMD_MATH_SSE)
			// TODO
#else
			ret = SetVector(GetX(lhs) * GetY(rhs) - GetY(lhs) * GetX(rhs));
#endif
			return ret;
		}

		SIMDVectorF4 DotVector2(SIMDVectorF4 const & lhs, SIMDVectorF4 const & rhs)
		{
			SIMDVectorF4 ret;
#if defined(SIMD_MATH_SSE)
			// TODO
#else
			ret = SetVector(GetX(lhs) * GetX(rhs) + GetY(lhs) * GetY(rhs));
#endif
			return ret;
		}

		SIMDVectorF4 LengthSqVector2(SIMDVectorF4 const & rhs)
		{
			SIMDVectorF4 ret;
#if defined(SIMD_MATH_SSE)
			// TODO
#else
			ret = DotVector2(rhs, rhs);
#endif
			return ret;
		}

		SIMDVectorF4 LengthVector2(SIMDVectorF4 const & rhs)
		{
			SIMDVectorF4 ret;
#if defined(SIMD_MATH_SSE)
			// TODO
#else
			ret = SetVector(sqrt(GetX(LengthSqVector2(rhs))));
#endif
			return ret;
		}

		SIMDVectorF4 NormalizeVector2(SIMDVectorF4 const & rhs)
		{
			SIMDVectorF4 ret;
#if defined(SIMD_MATH_SSE)
			// TODO
#else
			ret = rhs * MathLib::recip_sqrt(GetX(LengthSqVector2(rhs)));
#endif
			return ret;
		}

		SIMDVectorF4 TransformCoordVector2(SIMDVectorF4 const & v, SIMDMatrixF4 const & mat)
		{
			SIMDVectorF4 ret;
#if defined(SIMD_MATH_SSE)
			// TODO
#else
			SIMDVectorF4 temp;
			for (int i = 0; i < 4; ++ i)
			{
				temp.Vec()[i] = GetX(v) * mat(0, i) + GetY(v) * mat(1, i) + mat(3, i);
			}
			if (MathLib::equal(GetW(temp), 0.0f))
			{
				ret = SIMDVectorF4::Zero();
			}
			else
			{
				for (int i = 0; i < 2; ++ i)
				{
					ret.Vec()[i] = temp.Vec()[i] / GetW(temp);
				}
				for (int i = 2; i < 4; ++ i)
				{
					ret.Vec()[i] = 0;
				}
			}
#endif
			return ret;
		}

		SIMDVectorF4 TransformNormalVector2(SIMDVectorF4 const & v, SIMDMatrixF4 const & mat)
		{
			SIMDVectorF4 ret;
#if defined(SIMD_MATH_SSE)
			// TODO
#else
			for (int i = 0; i < 2; ++ i)
			{
				ret.Vec()[i] = GetX(v) * mat(0, i) + GetY(v) * mat(1, i);
			}
			for (int i = 2; i < 4; ++ i)
			{
				ret.Vec()[i] = 0;
			}
#endif
			return ret;
		}

		// 3D Vector
		///////////////////////////////////////////////////////////////////////////////
		SIMDVectorF4 Angle(SIMDVectorF4 const & lhs, SIMDVectorF4 const & rhs)
		{
			return SetVector(MathLib::acos(GetX(DotVector3(lhs, rhs) / (LengthVector3(lhs) * LengthVector3(rhs)))));
		}

		SIMDVectorF4 CrossVector3(SIMDVectorF4 const & lhs, SIMDVectorF4 const & rhs)
		{
			SIMDVectorF4 ret;
#if defined(SIMD_MATH_SSE)
			// TODO
#else
			ret = SetVector(GetY(lhs) * GetZ(rhs) - GetZ(lhs) * GetY(rhs),
				GetZ(lhs) * GetX(rhs) - GetX(lhs) * GetZ(rhs),
				GetX(lhs) * GetY(rhs) - GetY(lhs) * GetX(rhs),
				0.0f);
#endif
			return ret;
		}

		SIMDVectorF4 DotVector3(SIMDVectorF4 const & lhs, SIMDVectorF4 const & rhs)
		{
			SIMDVectorF4 ret;
#if defined(SIMD_MATH_SSE)
			// TODO
#else
			ret = SetVector(GetX(lhs) * GetX(rhs) + GetY(lhs) * GetY(rhs)
				+ GetZ(lhs) * GetZ(rhs));
#endif
			return ret;
		}

		SIMDVectorF4 LengthSqVector3(SIMDVectorF4 const & rhs)
		{
			SIMDVectorF4 ret;
#if defined(SIMD_MATH_SSE)
			// TODO
#else
			ret = DotVector3(rhs, rhs);
#endif
			return ret;
		}

		SIMDVectorF4 LengthVector3(SIMDVectorF4 const & rhs)
		{
			SIMDVectorF4 ret;
#if defined(SIMD_MATH_SSE)
			// TODO
#else
			ret = SetVector(sqrt(GetX(LengthSqVector3(rhs))));
#endif
			return ret;
		}

		SIMDVectorF4 NormalizeVector3(SIMDVectorF4 const & rhs)
		{
			SIMDVectorF4 ret;
#if defined(SIMD_MATH_SSE)
			// TODO
#else
			ret = rhs * MathLib::recip_sqrt(GetX(LengthSqVector3(rhs)));
#endif
			return ret;
		}

		SIMDVectorF4 TransformCoordVector3(SIMDVectorF4 const & v, SIMDMatrixF4 const & mat)
		{
			SIMDVectorF4 ret;
#if defined(SIMD_MATH_SSE)
			// TODO
#else
			SIMDVectorF4 temp;
			for (int i = 0; i < 4; ++ i)
			{
				temp.Vec()[i] = GetX(v) * mat(0, i) + GetY(v) * mat(1, i)
					+ GetZ(v) * mat(2, i) + mat(3, i);
			}
			if (MathLib::equal(GetW(temp), 0.0f))
			{
				ret = SIMDVectorF4::Zero();
			}
			else
			{
				for (int i = 0; i < 3; ++ i)
				{
					ret.Vec()[i] = temp.Vec()[i] / GetW(temp);
				}
				for (int i = 3; i < 4; ++ i)
				{
					ret.Vec()[i] = 0;
				}
			}
#endif
			return ret;
		}

		SIMDVectorF4 TransformNormalVector3(SIMDVectorF4 const & v, SIMDMatrixF4 const & mat)
		{
			SIMDVectorF4 ret;
#if defined(SIMD_MATH_SSE)
			// TODO
#else
			for (int i = 0; i < 3; ++ i)
			{
				ret.Vec()[i] = GetX(v) * mat(0, i) + GetY(v) * mat(1, i)
					+ GetZ(v) * mat(2, i);
			}
			for (int i = 3; i < 4; ++ i)
			{
				ret.Vec()[i] = 0;
			}
#endif
			return ret;
		}

		SIMDVectorF4 TransformQuat(SIMDVectorF4 const & v, SIMDVectorF4 const & quat)
		{
			SIMDVectorF4 ret;
#if defined(SIMD_MATH_SSE)
			// TODO
#else
			ret = v + CrossVector3(quat, CrossVector3(quat, v) + GetW(quat) * v) * 2;
#endif
			return ret;
		}

		SIMDVectorF4 Project(SIMDVectorF4 const & vec,
			SIMDMatrixF4 const & world, SIMDMatrixF4 const & view, SIMDMatrixF4 const & proj,
			int const viewport[4], float near_plane, float far_plane)
		{
			SIMDVectorF4 ret;
#if defined(SIMD_MATH_SSE)
			// TODO
#else
			SIMDVectorF4 temp(TransformVector4(vec, world));
			temp = TransformVector4(temp, view);
			temp = TransformVector4(temp, proj);
			temp /= GetW(temp);

			ret.Vec()[0] = (GetX(temp) + 1) * viewport[2] / 2 + viewport[0];
			ret.Vec()[1] = (-GetY(temp) + 1) * viewport[3] / 2 + viewport[1];
			ret.Vec()[2] = GetZ(temp) * (far_plane - near_plane) + near_plane;
			ret.Vec()[3] = 1.0f;
#endif
			return ret;
		}

		SIMDVectorF4 Unproject(SIMDVectorF4 const & win_vec, float clip_w,
			SIMDMatrixF4 const & world, SIMDMatrixF4 const & view, SIMDMatrixF4 const & proj,
			int const viewport[4], float near_plane, float far_plane)
		{
			SIMDVectorF4 ret;
#if defined(SIMD_MATH_SSE)
			// TODO
#else
			SIMDVectorF4 temp;
			temp.Vec()[0] = 2 * (GetX(win_vec) - viewport[0]) / viewport[2] - 1;
			temp.Vec()[1] = -(2 * (GetY(win_vec) - viewport[1]) / viewport[3] - 1);
			temp.Vec()[2] = (GetZ(win_vec) - near_plane) / (far_plane - near_plane);
			temp.Vec()[3] = clip_w;

			SIMDMatrixF4 mat(Inverse(world * view * proj));
			temp = TransformVector4(temp, mat);

			ret = SetVector(GetX(temp), GetY(temp), GetZ(temp), 0.0f) / GetW(temp);
#endif
			return ret;
		}

		// 4D Vector
		///////////////////////////////////////////////////////////////////////////////
		SIMDVectorF4 CrossVector4(SIMDVectorF4 const & v1, SIMDVectorF4 const & v2, SIMDVectorF4 const & v3)
		{
			SIMDVectorF4 ret;
#if defined(SIMD_MATH_SSE)
			// TODO
#else
			float const A = (GetX(v2) * GetY(v3)) - (GetY(v2) * GetX(v3));
			float const B = (GetX(v2) * GetZ(v3)) - (GetZ(v2) * GetX(v3));
			float const C = (GetX(v2) * GetW(v3)) - (GetW(v2) * GetX(v3));
			float const D = (GetY(v2) * GetZ(v3)) - (GetZ(v2) * GetY(v3));
			float const E = (GetY(v2) * GetW(v3)) - (GetW(v2) * GetY(v3));
			float const F = (GetZ(v2) * GetW(v3)) - (GetW(v2) * GetZ(v3));

			ret = SetVector((GetY(v1) * F) - (GetZ(v1) * E) + (GetW(v1) * D),
				-(GetX(v1) * F) + (GetZ(v1) * C) - (GetW(v1) * B),
				(GetX(v1) * E) - (GetY(v1) * C) + (GetW(v1) * A),
				-(GetX(v1) * D) + (GetY(v1) * B) - (GetZ(v1) * A));
#endif
			return ret;
		}

		SIMDVectorF4 DotVector4(SIMDVectorF4 const & lhs, SIMDVectorF4 const & rhs)
		{
			SIMDVectorF4 ret;
#if defined(SIMD_MATH_SSE)
			// TODO
#else
			ret = SetVector(GetX(lhs) * GetX(rhs) + GetY(lhs) * GetY(rhs)
				+ GetZ(lhs) * GetZ(rhs) + GetW(lhs) * GetW(rhs));
#endif
			return ret;
		}

		SIMDVectorF4 LengthSqVector4(SIMDVectorF4 const & rhs)
		{
			SIMDVectorF4 ret;
#if defined(SIMD_MATH_SSE)
			// TODO
#else
			ret = DotVector4(rhs, rhs);
#endif
			return ret;
		}

		SIMDVectorF4 LengthVector4(SIMDVectorF4 const & rhs)
		{
			SIMDVectorF4 ret;
#if defined(SIMD_MATH_SSE)
			// TODO
#else
			ret = SetVector(sqrt(GetX(LengthSqVector4(rhs))));
#endif
			return ret;
		}

		SIMDVectorF4 NormalizeVector4(SIMDVectorF4 const & rhs)
		{
			SIMDVectorF4 ret;
#if defined(SIMD_MATH_SSE)
			// TODO
#else
			ret = rhs * MathLib::recip_sqrt(GetX(LengthSqVector4(rhs)));
#endif
			return ret;
		}

		SIMDVectorF4 TransformVector4(SIMDVectorF4 const & v, SIMDMatrixF4 const & mat)
		{
			SIMDVectorF4 ret;
#if defined(SIMD_MATH_SSE)
			// TODO
#else
			for (int i = 0; i < 4; ++ i)
			{
				ret.Vec()[i] = GetX(v) * mat(0, i) + GetY(v) * mat(1, i)
					+ GetZ(v) * mat(2, i) + GetW(v) * mat(3, i);
			}
#endif
			return ret;
		}

		// 4D Matrix
		///////////////////////////////////////////////////////////////////////////////
		SIMDMatrixF4 Add(SIMDMatrixF4 const & lhs, SIMDMatrixF4 const & rhs)
		{
			return SIMDMatrixF4(Add(lhs.Row(0), rhs.Row(0)),
				Add(lhs.Row(1), rhs.Row(1)),
				Add(lhs.Row(2), rhs.Row(2)),
				Add(lhs.Row(3), rhs.Row(3)));
		}

		SIMDMatrixF4 Substract(SIMDMatrixF4 const & lhs, SIMDMatrixF4 const & rhs)
		{
			return SIMDMatrixF4(Substract(lhs.Row(0), rhs.Row(0)),
				Substract(lhs.Row(1), rhs.Row(1)),
				Substract(lhs.Row(2), rhs.Row(2)),
				Substract(lhs.Row(3), rhs.Row(3)));
		}

		SIMDMatrixF4 Multiply(SIMDMatrixF4 const & lhs, SIMDMatrixF4 const & rhs)
		{
#if defined(SIMD_MATH_SSE)
			UNREF_PARAM(lhs);
			// TODO
			return rhs;
#else
			SIMDMatrixF4 const tmp = Transpose(rhs);

			V4TYPE const & l0 = lhs.Row(0).Vec();
			V4TYPE const & l1 = lhs.Row(1).Vec();
			V4TYPE const & l2 = lhs.Row(2).Vec();
			V4TYPE const & l3 = lhs.Row(3).Vec();

			V4TYPE const & t0 = tmp.Row(0).Vec();
			V4TYPE const & t1 = tmp.Row(1).Vec();
			V4TYPE const & t2 = tmp.Row(2).Vec();
			V4TYPE const & t3 = tmp.Row(3).Vec();

			return SIMDMatrixF4(
				l0[0] * t0[0] + l0[1] * t0[1] + l0[2] * t0[2] + l0[3] * t0[3],
				l0[0] * t1[0] + l0[1] * t1[1] + l0[2] * t1[2] + l0[3] * t1[3],
				l0[0] * t2[0] + l0[1] * t2[1] + l0[2] * t2[2] + l0[3] * t2[3],
				l0[0] * t3[0] + l0[1] * t3[1] + l0[2] * t3[2] + l0[3] * t3[3],

				l1[0] * t0[0] + l1[1] * t0[1] + l1[2] * t0[2] + l1[3] * t0[3],
				l1[0] * t1[0] + l1[1] * t1[1] + l1[2] * t1[2] + l1[3] * t1[3],
				l1[0] * t2[0] + l1[1] * t2[1] + l1[2] * t2[2] + l1[3] * t2[3],
				l1[0] * t3[0] + l1[1] * t3[1] + l1[2] * t3[2] + l1[3] * t3[3],

				l2[0] * t0[0] + l2[1] * t0[1] + l2[2] * t0[2] + l2[3] * t0[3],
				l2[0] * t1[0] + l2[1] * t1[1] + l2[2] * t1[2] + l2[3] * t1[3],
				l2[0] * t2[0] + l2[1] * t2[1] + l2[2] * t2[2] + l2[3] * t2[3],
				l2[0] * t3[0] + l2[1] * t3[1] + l2[2] * t3[2] + l2[3] * t3[3],

				l3[0] * t0[0] + l3[1] * t0[1] + l3[2] * t0[2] + l3[3] * t0[3],
				l3[0] * t1[0] + l3[1] * t1[1] + l3[2] * t1[2] + l3[3] * t1[3],
				l3[0] * t2[0] + l3[1] * t2[1] + l3[2] * t2[2] + l3[3] * t2[3],
				l3[0] * t3[0] + l3[1] * t3[1] + l3[2] * t3[2] + l3[3] * t3[3]);
#endif
		}

		SIMDMatrixF4 Multiply(SIMDMatrixF4 const & lhs, float rhs)
		{
			SIMDVectorF4 r = SetVector(rhs, rhs, rhs, rhs);
			return SIMDMatrixF4(Multiply(lhs.Row(0), r),
				Multiply(lhs.Row(1), r),
				Multiply(lhs.Row(2), r),
				Multiply(lhs.Row(3), r));
		}

		SIMDMatrixF4 Negative(SIMDMatrixF4 const & rhs)
		{
			return SIMDMatrixF4(Negative(rhs.Row(0)),
				Negative(rhs.Row(1)),
				Negative(rhs.Row(2)),
				Negative(rhs.Row(3)));
		}

		SIMDMatrixF4 Inverse(SIMDMatrixF4 const & rhs)
		{
			SIMDMatrixF4 ret;
#if defined(SIMD_MATH_SSE)
			// TODO
#else
			float const _2132_2231 = rhs(1, 0) * rhs(2, 1) - rhs(1, 1) * rhs(2, 0);
			float const _2133_2331 = rhs(1, 0) * rhs(2, 2) - rhs(1, 2) * rhs(2, 0);
			float const _2134_2431 = rhs(1, 0) * rhs(2, 3) - rhs(1, 3) * rhs(2, 0);
			float const _2142_2241 = rhs(1, 0) * rhs(3, 1) - rhs(1, 1) * rhs(3, 0);
			float const _2143_2341 = rhs(1, 0) * rhs(3, 2) - rhs(1, 2) * rhs(3, 0);
			float const _2144_2441 = rhs(1, 0) * rhs(3, 3) - rhs(1, 3) * rhs(3, 0);
			float const _2233_2332 = rhs(1, 1) * rhs(2, 2) - rhs(1, 2) * rhs(2, 1);
			float const _2234_2432 = rhs(1, 1) * rhs(2, 3) - rhs(1, 3) * rhs(2, 1);
			float const _2243_2342 = rhs(1, 1) * rhs(3, 2) - rhs(1, 2) * rhs(3, 1);
			float const _2244_2442 = rhs(1, 1) * rhs(3, 3) - rhs(1, 3) * rhs(3, 1);
			float const _2334_2433 = rhs(1, 2) * rhs(2, 3) - rhs(1, 3) * rhs(2, 2);
			float const _2344_2443 = rhs(1, 2) * rhs(3, 3) - rhs(1, 3) * rhs(3, 2);
			float const _3142_3241 = rhs(2, 0) * rhs(3, 1) - rhs(2, 1) * rhs(3, 0);
			float const _3143_3341 = rhs(2, 0) * rhs(3, 2) - rhs(2, 2) * rhs(3, 0);
			float const _3144_3441 = rhs(2, 0) * rhs(3, 3) - rhs(2, 3) * rhs(3, 0);
			float const _3243_3342 = rhs(2, 1) * rhs(3, 2) - rhs(2, 2) * rhs(3, 1);
			float const _3244_3442 = rhs(2, 1) * rhs(3, 3) - rhs(2, 3) * rhs(3, 1);
			float const _3344_3443 = rhs(2, 2) * rhs(3, 3) - rhs(2, 3) * rhs(3, 2);

			float const det = Determinant(rhs);
			if (MathLib::equal(det, 0.0f))
			{
				ret = rhs;
			}
			else
			{
				float const inv_det = 1.0f / det;

				ret = SIMDMatrixF4(
					+inv_det * (rhs(1, 1) * _3344_3443 - rhs(1, 2) * _3244_3442 + rhs(1, 3) * _3243_3342),
					-inv_det * (rhs(0, 1) * _3344_3443 - rhs(0, 2) * _3244_3442 + rhs(0, 3) * _3243_3342),
					+inv_det * (rhs(0, 1) * _2344_2443 - rhs(0, 2) * _2244_2442 + rhs(0, 3) * _2243_2342),
					-inv_det * (rhs(0, 1) * _2334_2433 - rhs(0, 2) * _2234_2432 + rhs(0, 3) * _2233_2332),

					-inv_det * (rhs(1, 0) * _3344_3443 - rhs(1, 2) * _3144_3441 + rhs(1, 3) * _3143_3341),
					+inv_det * (rhs(0, 0) * _3344_3443 - rhs(0, 2) * _3144_3441 + rhs(0, 3) * _3143_3341),
					-inv_det * (rhs(0, 0) * _2344_2443 - rhs(0, 2) * _2144_2441 + rhs(0, 3) * _2143_2341),
					+inv_det * (rhs(0, 0) * _2334_2433 - rhs(0, 2) * _2134_2431 + rhs(0, 3) * _2133_2331),

					+inv_det * (rhs(1, 0) * _3244_3442 - rhs(1, 1) * _3144_3441 + rhs(1, 3) * _3142_3241),
					-inv_det * (rhs(0, 0) * _3244_3442 - rhs(0, 1) * _3144_3441 + rhs(0, 3) * _3142_3241),
					+inv_det * (rhs(0, 0) * _2244_2442 - rhs(0, 1) * _2144_2441 + rhs(0, 3) * _2142_2241),
					-inv_det * (rhs(0, 0) * _2234_2432 - rhs(0, 1) * _2134_2431 + rhs(0, 3) * _2132_2231),

					-inv_det * (rhs(1, 0) * _3243_3342 - rhs(1, 1) * _3143_3341 + rhs(1, 2) * _3142_3241),
					+inv_det * (rhs(0, 0) * _3243_3342 - rhs(0, 1) * _3143_3341 + rhs(0, 2) * _3142_3241),
					-inv_det * (rhs(0, 0) * _2243_2342 - rhs(0, 1) * _2143_2341 + rhs(0, 2) * _2142_2241),
					+inv_det * (rhs(0, 0) * _2233_2332 - rhs(0, 1) * _2133_2331 + rhs(0, 2) * _2132_2231));
			}
#endif
			return ret;
		}

		SIMDMatrixF4 LookAtLH(SIMDVectorF4 const & eye, SIMDVectorF4 const & at)
		{
			return LookAtLH(eye, at, SetVector(0, 1, 0, 0));
		}

		SIMDMatrixF4 LookAtLH(SIMDVectorF4 const & eye, SIMDVectorF4 const & at,
			SIMDVectorF4 const & up)
		{
			SIMDMatrixF4 ret;
#if defined(SIMD_MATH_SSE)
			// TODO
#else
			SIMDVectorF4 z_axis = NormalizeVector3(at - eye);
			SIMDVectorF4 x_axis = NormalizeVector3(CrossVector3(up, z_axis));
			SIMDVectorF4 y_axis = CrossVector3(z_axis, x_axis);

			ret = SIMDMatrixF4(
				GetX(x_axis), GetX(y_axis), GetX(z_axis), 0,
				GetY(x_axis), GetY(y_axis), GetY(z_axis), 0,
				GetZ(x_axis), GetZ(y_axis), GetZ(z_axis), 0,
				-GetX(DotVector3(x_axis, eye)), -GetX(DotVector3(y_axis, eye)), -GetX(DotVector3(z_axis, eye)), 1);
#endif
			return ret;
		}

		SIMDMatrixF4 LookAtRH(SIMDVectorF4 const & eye, SIMDVectorF4 const & at)
		{
			return LookAtRH(eye, at, SetVector(0, 1, 0, 0));
		}

		SIMDMatrixF4 LookAtRH(SIMDVectorF4 const & eye, SIMDVectorF4 const & at,
			SIMDVectorF4 const & up)
		{
			SIMDMatrixF4 ret;
#if defined(SIMD_MATH_SSE)
			// TODO
#else
			SIMDVectorF4 z_axis = NormalizeVector3(eye - at);
			SIMDVectorF4 x_axis = NormalizeVector3(CrossVector3(up, z_axis));
			SIMDVectorF4 y_axis = CrossVector3(z_axis, x_axis);

			ret = SIMDMatrixF4(
				GetX(x_axis), GetX(y_axis), GetX(z_axis), 0,
				GetY(x_axis), GetY(y_axis), GetY(z_axis), 0,
				GetZ(x_axis), GetZ(y_axis), GetZ(z_axis), 0,
				-GetX(DotVector3(x_axis, eye)), -GetX(DotVector3(y_axis, eye)), -GetX(DotVector3(z_axis, eye)), 1);
#endif
			return ret;
		}

		SIMDMatrixF4 OrthoLH(float w, float h, float near_plane, float far_plane)
		{
			SIMDMatrixF4 ret;
#if defined(SIMD_MATH_SSE)
			// TODO
#else
			float const w_2 = w / 2;
			float const h_2 = h / 2;
			ret = OrthoOffCenterLH(-w_2, w_2, -h_2, h_2, near_plane, far_plane);
#endif
			return ret;
		}

		SIMDMatrixF4 OrthoOffCenterLH(float left, float right, float bottom, float top,
			float near_plane, float far_plane)
		{
			SIMDMatrixF4 ret;
#if defined(SIMD_MATH_SSE)
			// TODO
#else
			float const q = 1 / (far_plane - near_plane);
			float const inv_width = 1 / (right - left);
			float const inv_height = 1 / (top - bottom);

			ret = SIMDMatrixF4(
				inv_width + inv_width, 0, 0, 0,
				0, inv_height + inv_height, 0, 0,
				0, 0, q, 0,
				-(left + right) * inv_width, -(top + bottom) * inv_height, -near_plane * q, 1);
#endif
			return ret;
		}

		SIMDMatrixF4 OrthoRH(float width, float height, float near_plane, float far_plane)
		{
			return LHToRH(OrthoLH(width, height, near_plane, far_plane));
		}

		SIMDMatrixF4 OrthoOffCenterRH(float left, float right, float bottom, float top,
			float near_plane, float far_plane)
		{
			return LHToRH(OrthoOffCenterLH(left, right, bottom, top, near_plane, far_plane));
		}

		SIMDMatrixF4 PerspectiveLH(float width, float height, float near_plane, float far_plane)
		{
			SIMDMatrixF4 ret;
#if defined(SIMD_MATH_SSE)
			// TODO
#else
			float const q = far_plane / (far_plane - near_plane);
			float const near2 = near_plane + near_plane;

			ret = SIMDMatrixF4(
				near2 / width,	0,				0,					0,
				0,				near2 / height,	0,					0,
				0,				0,				q,					1,
				0,				0,				-near_plane * q,	0);
#endif
			return ret;
		}

		SIMDMatrixF4 PerspectiveFovLH(float fov, float aspect, float near_plane, float far_plane)
		{
			SIMDMatrixF4 ret;
#if defined(SIMD_MATH_SSE)
			// TODO
#else
			float const h = 1 / tan(fov / 2);
			float const w = h / aspect;
			float const q = far_plane / (far_plane - near_plane);

			ret = SIMDMatrixF4(
				w, 0, 0, 0,
				0, h, 0, 0,
				0, 0, q, 1,
				0, 0, -near_plane * q, 0);
#endif
			return ret;
		}

		SIMDMatrixF4 PerspectiveOffCenterLH(float left, float right, float bottom, float top,
			float near_plane, float far_plane)
		{
			float const q = far_plane / (far_plane - near_plane);
			float const near2 = near_plane + near_plane;
			float const inv_width = 1 / (right - left);
			float const inv_height = 1 / (top - bottom);

			return SIMDMatrixF4(
				near2 * inv_width, 0, 0, 0,
				0, near2 * inv_height, 0, 0,
				-(left + right) * inv_width, -(top + bottom) * inv_height, q, 1,
				0, 0, -near_plane * q, 0);
		}

		SIMDMatrixF4 PerspectiveRH(float width, float height, float near_plane, float far_plane)
		{
			return LHToRH(PerspectiveLH(width, height, near_plane, far_plane));
		}

		SIMDMatrixF4 PerspectiveFovRH(float fov, float aspect, float near_plane, float far_plane)
		{
			return LHToRH(PerspectiveFovLH(fov, aspect, near_plane, far_plane));
		}

		SIMDMatrixF4 PerspectiveOffCenterRH(float left, float right, float bottom, float top,
			float near_plane, float far_plane)
		{
			return LHToRH(PerspectiveOffCenterLH(left, right, bottom, top, near_plane, far_plane));
		}

		SIMDMatrixF4 Reflect(SIMDVectorF4 const & p)
		{
			SIMDVectorF4 const np = NormalizePlane(p);
			float const aa2 = -2 * GetX(np) * GetX(np);
			float const ab2 = -2 * GetX(np) * GetY(np);
			float const ac2 = -2 * GetX(np) * GetZ(np);
			float const ad2 = -2 * GetX(np) * GetW(np);
			float const bb2 = -2 * GetY(np) * GetY(np);
			float const bc2 = -2 * GetY(np) * GetZ(np);
			float const bd2 = -2 * GetY(np) * GetW(np);
			float const cc2 = -2 * GetZ(np) * GetZ(np);
			float const cd2 = -2 * GetZ(np) * GetW(np);

			return SIMDMatrixF4(
				aa2 + 1, ab2, ac2, 0,
				ab2, bb2 + 1, bc2, 0,
				ac2, bc2, cc2 + 1, 0,
				ad2, bd2, cd2, 1);
		}

		SIMDMatrixF4 RotationX(float x)
		{
			float sx, cx;
			MathLib::sincos(x, sx, cx);

			return SIMDMatrixF4(
				1, 0, 0, 0,
				0, cx, sx, 0,
				0, -sx, cx, 0,
				0, 0, 0, 1);
		}

		SIMDMatrixF4 RotationY(float y)
		{
			float sy, cy;
			MathLib::sincos(y, sy, cy);

			return SIMDMatrixF4(
				cy, 0, -sy, 0,
				0, 1, 0, 0,
				sy, 0, cy, 0,
				0, 0, 0, 1);
		}

		SIMDMatrixF4 RotationZ(float z)
		{
			float sz, cz;
			MathLib::sincos(z, sz, cz);

			return SIMDMatrixF4(
				cz, sz, 0, 0,
				-sz, cz, 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1);
		}

		SIMDMatrixF4 Rotation(float angle, float x, float y, float z)
		{
			SIMDVectorF4 quat = RotationAxis(SetVector(x, y, z, 0), angle);
			return QuatToMatrix(quat);
		}

		SIMDMatrixF4 RotationMatrixYawPitchRoll(float yaw, float pitch, float roll)
		{
			SIMDMatrixF4 rotX(RotationX(pitch));
			SIMDMatrixF4 rotY(RotationY(yaw));
			SIMDMatrixF4 rotZ(RotationZ(roll));
			return rotZ * rotX * rotY;
		}

		SIMDMatrixF4 RotationMatrixYawPitchRoll(SIMDVectorF4 const & ang)
		{
			return RotationMatrixYawPitchRoll(GetX(ang), GetY(ang), GetZ(ang));
		}

		SIMDMatrixF4 Scaling(float sx, float sy, float sz)
		{
			return SIMDMatrixF4(
				sx, 0, 0, 0,
				0, sy, 0, 0,
				0, 0, sz, 0,
				0,	0,	0,	1);
		}

		SIMDMatrixF4 Scaling(SIMDVectorF4 const & s)
		{
			return Scaling(GetX(s), GetY(s), GetZ(s));
		}

		SIMDMatrixF4 Shadow(SIMDVectorF4 const & l, SIMDVectorF4 const & p)
		{
			SIMDVectorF4 const v = -l;
			SIMDVectorF4 const np = NormalizePlane(p);
			float const d = -GetX(DotPlane(np, v));

			return SIMDMatrixF4(
				GetX(np) * GetX(v) + d, GetX(np) * GetY(v),     GetX(np) * GetZ(v),     GetX(np) * GetW(v),
				GetY(np) * GetX(v),     GetY(np) * GetY(v) + d, GetY(np) * GetZ(v),     GetY(np) * GetW(v),
				GetZ(np) * GetX(v),     GetZ(np) * GetY(v),     GetZ(np) * GetZ(v) + d, GetZ(np) * GetW(v),
				GetW(np) * GetX(v),     GetW(np) * GetY(v),     GetW(np) * GetZ(v),     GetW(np) * GetW(v) + d);
		}

		SIMDMatrixF4 QuatToMatrix(SIMDVectorF4 const & quat)
		{
			// calculate coefficients
			float const x2 = GetX(quat) + GetX(quat);
			float const y2 = GetY(quat) + GetY(quat);
			float const z2 = GetZ(quat) + GetZ(quat);

			float const xx2 = GetX(quat) * x2, xy2 = GetX(quat) * y2, xz2 = GetX(quat) * z2;
			float const yy2 = GetY(quat) * y2, yz2 = GetY(quat) * z2, zz2 = GetZ(quat) * z2;
			float const wx2 = GetW(quat) * x2, wy2 = GetW(quat) * y2, wz2 = GetW(quat) * z2;

			return SIMDMatrixF4(
				1 - yy2 - zz2, xy2 + wz2, xz2 - wy2, 0,
				xy2 - wz2, 1 - xx2 - zz2, yz2 + wx2, 0,
				xz2 + wy2, yz2 - wx2, 1 - xx2 - yy2, 0,
				0, 0, 0, 1);
		}

		SIMDMatrixF4 Translation(float x, float y, float z)
		{
			return SIMDMatrixF4(
				1, 0, 0, 0,
				0, 1, 0, 0,
				0, 0, 1, 0,
				x, y, z, 1);
		}

		SIMDMatrixF4 Translation(SIMDVectorF4 const & pos)
		{
			return Translation(GetX(pos), GetY(pos), GetZ(pos));
		}

		SIMDMatrixF4 Transpose(SIMDMatrixF4 const & rhs)
		{
#if defined(SIMD_MATH_SSE)
			// TODO
			return rhs;
#else
			V4TYPE const & r0 = rhs.Row(0).Vec();
			V4TYPE const & r1 = rhs.Row(1).Vec();
			V4TYPE const & r2 = rhs.Row(2).Vec();
			V4TYPE const & r3 = rhs.Row(3).Vec();
			return SIMDMatrixF4(
				r0[0], r1[0], r2[0], r3[0],
				r0[1], r1[1], r2[1], r3[1],
				r0[2], r1[2], r2[2], r3[2],
				r0[3], r1[3], r2[3], r3[3]);
#endif
		}

		SIMDMatrixF4 LHToRH(SIMDMatrixF4 const & rhs)
		{
			SIMDMatrixF4 ret = rhs;
			ret.Row(2, -ret.Row(2));
			return ret;
		}

		SIMDMatrixF4 RHToLH(SIMDMatrixF4 const & rhs)
		{
			return LHToRH(rhs);
		}

		void Decompose(SIMDVectorF4& scale, SIMDVectorF4& rot, SIMDVectorF4& trans, SIMDMatrixF4 const & rhs)
		{
			scale = SetVector(sqrt(rhs(0, 0) * rhs(0, 0) + rhs(0, 1) * rhs(0, 1) + rhs(0, 2) * rhs(0, 2)),
				sqrt(rhs(1, 0) * rhs(1, 0) + rhs(1, 1) * rhs(1, 1) + rhs(1, 2) * rhs(1, 2)),
				sqrt(rhs(2, 0) * rhs(2, 0) + rhs(2, 1) * rhs(2, 1) + rhs(2, 2) * rhs(2, 2)),
				1);

			trans = SetVector(rhs(3, 0), rhs(3, 1), rhs(3, 2), 0);

			SIMDMatrixF4 rot_mat;
			rot_mat.Set(0, 0, rhs(0, 0) / GetX(scale));
			rot_mat.Set(0, 1, rhs(0, 1) / GetX(scale));
			rot_mat.Set(0, 2, rhs(0, 2) / GetX(scale));
			rot_mat.Set(0, 3, 0);
			rot_mat.Set(1, 0, rhs(1, 0) / GetY(scale));
			rot_mat.Set(1, 1, rhs(1, 1) / GetY(scale));
			rot_mat.Set(1, 2, rhs(1, 2) / GetY(scale));
			rot_mat.Set(1, 3, 0);
			rot_mat.Set(2, 0, rhs(2, 0) / GetZ(scale));
			rot_mat.Set(2, 1, rhs(2, 1) / GetZ(scale));
			rot_mat.Set(2, 2, rhs(2, 2) / GetZ(scale));
			rot_mat.Set(2, 3, 0);
			rot_mat.Set(3, 0, 0);
			rot_mat.Set(3, 1, 0);
			rot_mat.Set(3, 2, 0);
			rot_mat.Set(3, 3, 1);
			rot = ToQuaternion(rot_mat);
		}

		SIMDMatrixF4 Transformation(SIMDVectorF4 const * scaling_center, SIMDVectorF4 const * scaling_rotation, SIMDVectorF4 const * scale,
			SIMDVectorF4 const * rotation_center, SIMDVectorF4 const * rotation, SIMDVectorF4 const * trans)
		{
			SIMDVectorF4 psc, prc, pt;
			if (scaling_center)
			{
				psc = *scaling_center;
			}
			else
			{
				psc = SIMDVectorF4::Zero();
			}
			if (rotation_center)
			{
				prc = *rotation_center;
			}
			else
			{
				prc = SIMDVectorF4::Zero();
			}
			if (trans)
			{
				pt = *trans;
			}
			else
			{
				pt = SIMDVectorF4::Zero();
			}

			SIMDMatrixF4 m1, m2, m3, m4, m5, m6, m7;
			m1 = Translation(-psc);
			if (scaling_rotation)
			{
				m4 = QuatToMatrix(*scaling_rotation);
				m2 = Inverse(m4);
			}
			else
			{
				m2 = m4 = SIMDMatrixF4::Identity();
			}
			if (scale)
			{
				m3 = Scaling(*scale);
			}
			else
			{
				m3 = SIMDMatrixF4::Identity();
			}
			if (rotation)
			{
				m6 = QuatToMatrix(*rotation);
			}
			else
			{
				m6 = SIMDMatrixF4::Identity();
			}
			m5 = Translation(psc - prc);
			m7 = Translation(prc + pt);

			return m1 * m2 * m3 * m4 * m5 * m6 * m7;
		}

		// Quaternion
		///////////////////////////////////////////////////////////////////////////////
		SIMDVectorF4 Conjugate(SIMDVectorF4 const & rhs)
		{
			return SetVector(-GetX(rhs), -GetY(rhs), -GetZ(rhs), GetW(rhs));
		}

		SIMDVectorF4 AxisToAxis(SIMDVectorF4 const & from, SIMDVectorF4 const & to)
		{
			SIMDVectorF4 a = NormalizeVector3(from);
			SIMDVectorF4 b = NormalizeVector3(to);
			return UnitAxisToUnitAxis(a, b);
		}

		SIMDVectorF4 UnitAxisToUnitAxis(SIMDVectorF4 const & from, SIMDVectorF4 const & to)
		{
			float const cos_theta = GetX(DotVector3(from, to));
			if (MathLib::equal(cos_theta, 1.0f))
			{
				return SetVector(0, 0, 0, 1);
			}
			else
			{
				if (MathLib::equal(cos_theta, -1.0f))
				{
					return SetVector(1, 0, 0, 0);
				}
				else
				{
					// From http://lolengine.net/blog/2013/09/18/beautiful-maths-quaternion-from-vectors

					SIMDVectorF4 w = CrossVector3(from, to);
					return NormalizeVector4(SetVector(GetX(w), GetY(w), GetZ(w), 1 + cos_theta));
				}
			}
		}

		SIMDVectorF4 BaryCentricQuat(SIMDVectorF4 const & q1, SIMDVectorF4 const & q2, SIMDVectorF4 const & q3,
			float f, float g)
		{
			SIMDVectorF4 ret;
			float const s = f + g;
			if (s != 0)
			{
				ret = Slerp(Slerp(q1, q2, s), Slerp(q1, q3, s), g / s);
			}
			else
			{
				ret = q1;
			}
			return ret;
		}

		SIMDVectorF4 Exp(SIMDVectorF4 const & rhs)
		{
			float const theta = GetX(LengthVector3(rhs));
			SIMDVectorF4 ret = NormalizeVector3(rhs) * sin(theta);
			ret = SetW(ret, cos(theta));
			return ret;
		}

		SIMDVectorF4 Ln(SIMDVectorF4 const & rhs)
		{
			float const theta_2 = acos(GetW(rhs));
			SIMDVectorF4 ret = NormalizeVector3(rhs) * (theta_2 + theta_2);
			ret = SetW(ret, 0);
			return ret;
		}

		SIMDVectorF4 Inverse(SIMDVectorF4 const & rhs)
		{
			SIMDVectorF4 const inv = Divide(SetVector(1), LengthVector4(rhs));
			return SetVector(-GetX(rhs), -GetY(rhs), -GetZ(rhs), GetW(rhs)) * inv;
		}

		SIMDVectorF4 MultiplyQuat(SIMDVectorF4 const & lhs, SIMDVectorF4 const & rhs)
		{
			return SetVector(
				GetX(lhs) * GetW(rhs) - GetY(lhs) * GetZ(rhs) + GetZ(lhs) * GetY(rhs) + GetW(lhs) * GetX(rhs),
				GetX(lhs) * GetZ(rhs) + GetY(lhs) * GetW(rhs) - GetZ(lhs) * GetX(rhs) + GetW(lhs) * GetY(rhs),
				GetY(lhs) * GetX(rhs) - GetX(lhs) * GetY(rhs) + GetZ(lhs) * GetW(rhs) + GetW(lhs) * GetZ(rhs),
				GetW(lhs) * GetW(rhs) - GetX(lhs) * GetX(rhs) - GetY(lhs) * GetY(rhs) - GetZ(lhs) * GetZ(rhs));
		}

		SIMDVectorF4 RotationAxis(SIMDVectorF4 const & v, float angle)
		{
			float sa, ca;
			MathLib::sincos(angle * 0.5f, sa, ca);

			SIMDVectorF4 ret;
			if (MathLib::equal(GetX(LengthSqVector3(v)), 0.0f))
			{
				ret = SetVector(sa, sa, sa, ca);
			}
			else
			{
				ret = NormalizeVector3(v) * sa;
				ret = SetW(ret, ca);
			}
			return ret;
		}

		SIMDVectorF4 RotationQuatYawPitchRoll(float yaw, float pitch, float roll)
		{
			float const ang_x = pitch / 2;
			float const ang_y = yaw / 2;
			float const ang_z = roll / 2;
			float sx, sy, sz;
			float cx, cy, cz;
			MathLib::sincos(ang_x, sx, cx);
			MathLib::sincos(ang_y, sy, cy);
			MathLib::sincos(ang_z, sz, cz);

			return SetVector(
				sx * cy * cz + cx * sy * sz,
				cx * sy * cz - sx * cy * sz,
				cx * cy * sz - sx * sy * cz,
				sx * sy * sz + cx * cy * cz);
		}

		SIMDVectorF4 RotationQuatYawPitchRoll(SIMDVectorF4 const & ang)
		{
			return RotationQuatYawPitchRoll(GetX(ang), GetY(ang), GetZ(ang));
		}

		// From http://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToEuler/index.htm
		void ToYawPitchRoll(float& yaw, float& pitch, float& roll, SIMDVectorF4 const & quat)
		{
			float sqx = GetX(quat) * GetX(quat);
			float sqy = GetY(quat) * GetY(quat);
			float sqz = GetZ(quat) * GetZ(quat);
			float sqw = GetW(quat) * GetW(quat);
			float unit = sqx + sqy + sqz + sqw;
			float test = GetW(quat) * GetX(quat) + GetY(quat) * GetZ(quat);
			if (test > 0.499f * unit)
			{
				// singularity at north pole
				yaw = 2 * atan2(GetZ(quat), GetW(quat));
				pitch = PI / 2;
				roll = 0;
			}
			else
			{
				if (test < -0.499f * unit)
				{
					// singularity at south pole
					yaw = -2 * atan2(GetZ(quat), GetW(quat));
					pitch = -PI / 2;
					roll = 0;
				}
				else
				{
					yaw = atan2(2 * (GetY(quat) * GetW(quat) - GetX(quat) * GetZ(quat)), -sqx - sqy + sqz + sqw);
					pitch = asin(2 * test / unit);
					roll = atan2(2 * (GetZ(quat) * GetW(quat) - GetX(quat) * GetY(quat)), -sqx + sqy - sqz + sqw);
				}
			}
		}

		void ToAxisAngle(SIMDVectorF4& vec, float& ang, SIMDVectorF4 const & quat)
		{
			float const tw = acos(GetW(quat));
			float const stw = sin(tw);

			ang = tw + tw;
			vec = SetW(quat, 0);
			if (!MathLib::equal(stw, 0.0f))
			{
				vec /= stw;
			}
		}

		SIMDVectorF4 ToQuaternion(SIMDMatrixF4 const & mat)
		{
			SIMDVectorF4 quat;
			float s;
			float s2;
			float const tr = mat(0, 0) + mat(1, 1) + mat(2, 2) + 1;

			// check the diagonal
			if (tr > 1)
			{
				s = sqrt(tr);
				s2 = 0.5f / s;
				quat = SetVector(mat(1, 2) - mat(2, 1), mat(2, 0) - mat(0, 2),
					mat(0, 1) - mat(1, 0), 0.5f) * SetVector(s2, s2, s2, s);
			}
			else
			{
				int max_i = 0;
				float max_diag = mat(0, 0);
				for (int i = 1; i < 3; ++ i)
				{
					if (mat(i, i) > max_diag)
					{
						max_i = i;
						max_diag = mat(i, i);
					}
				}

				switch (max_i)
				{
				case 0:
					s = sqrt((mat(0, 0) - (mat(1, 1) + mat(2, 2))) + 1);
					s2 = MathLib::equal(s, 0.0f) ? s : 0.5f / s;

					quat = SetVector(0.5f, mat(1, 0) + mat(0, 1), mat(2, 0) + mat(0, 2), mat(1, 2) - mat(2, 1))
						* SetVector(s, s2, s2, s2);
					break;

				case 1:
					s = sqrt((mat(1, 1) - (mat(2, 2) + mat(0, 0))) + 1);
					s2 = MathLib::equal(s, 0.0f) ? s : 0.5f / s;

					quat = SetVector(mat(0, 1) + mat(1, 0), 0.5f, mat(2, 1) + mat(1, 2), mat(2, 0) - mat(0, 2))
						* SetVector(s2, s, s2, s2);
					break;

				case 2:
				default:
					s = sqrt((mat(2, 2) - (mat(0, 0) + mat(1, 1))) + 1);
					s2 = MathLib::equal(s, 0.0f) ? s : 0.5f / s;

					quat = SetVector(mat(0, 2) + mat(2, 0), mat(1, 2) + mat(2, 1), 0.5f, mat(0, 1) - mat(1, 0))
						* SetVector(s2, s2, s, s2);
					break;
				}
			}

			return NormalizeVector4(quat);
		}

		SIMDVectorF4 ToQuaternion(SIMDVectorF4 const & tangent, SIMDVectorF4 const & binormal, SIMDVectorF4 const & normal, int bits)
		{
			float k = 1;
			if (GetX(DotVector3(binormal, CrossVector3(normal, tangent))) < 0)
			{
				k = -1;
			}

			SIMDMatrixF4 tangent_frame(GetX(tangent), GetY(tangent), GetZ(tangent), 0,
				GetX(binormal), GetY(binormal), GetZ(binormal), 0,
				GetX(normal), GetY(normal), GetZ(normal), 0,
				0, 0, 0, 1);
			tangent_frame.Row(1, tangent_frame.Row(1) * k);
			SIMDVectorF4 tangent_quat = ToQuaternion(tangent_frame);
			if (GetW(tangent_quat) < 0)
			{
				tangent_quat = -tangent_quat;
			}
			if (bits > 0)
			{
				float const bias = 1.0f / ((1UL << (bits - 1)) - 1);
				if (GetW(tangent_quat) < bias)
				{
					float const factor = sqrt(1 - bias * bias);
					tangent_quat *= factor;
					tangent_quat = SetW(tangent_quat, bias);
				}
			}
			if (k < 0)
			{
				tangent_quat = -tangent_quat;
			}

			return tangent_quat;
		}

		SIMDVectorF4 Slerp(SIMDVectorF4 const & lhs, SIMDVectorF4 const & rhs, float s)
		{
			float scale0, scale1;

			// DOT the quats to get the cosine of the angle between them
			float cosom = GetX(DotVector4(lhs, rhs));

			float dir = 1;
			if (cosom < 0)
			{
				dir = -1;
				cosom = -cosom;
			}

			// make sure they are different enough to avoid a divide by 0
			if (cosom < 1 - std::numeric_limits<float>::epsilon())
			{
				// SLERP away
				float const omega = acos(cosom);
				float const isinom = 1 / sin(omega);
				scale0 = sin((1 - s) * omega) * isinom;
				scale1 = sin(s * omega) * isinom;
			}
			else
			{
				// LERP is good enough at this distance
				scale0 = 1 - s;
				scale1 = s;
			}

			// Compute the result
			return scale0 * lhs + dir * scale1 * rhs;
		}

		void SquadSetup(SIMDVectorF4& a, SIMDVectorF4& b, SIMDVectorF4& c,
			SIMDVectorF4 const & q0, SIMDVectorF4 const & q1, SIMDVectorF4 const & q2,
			SIMDVectorF4 const & q3)
		{
			SIMDVectorF4 q, temp1, temp2, temp3;

			if (GetX(DotVector4(q0, q1)) < 0)
			{
				temp2 = -q0;
			}
			else
			{
				temp2 = q0;
			}

			if (GetX(DotVector4(q1, q2)) < 0)
			{
				c = -q2;
			}
			else
			{
				c = q2;
			}

			if (GetX(DotVector4(c, q3)) < 0)
			{
				temp3 = -q3;
			}
			else
			{
				temp3 = q3;
			}

			temp1 = Inverse(q1);
			temp2 = Ln(Multiply(temp1, temp2));
			q = Ln(Multiply(temp1, c));
			temp1 = temp2 + q;
			temp1 = Exp(temp1 * -0.25f);
			a = Multiply(q1, temp1);

			temp1 = Inverse(c);
			temp2 = Ln(Multiply(temp1, q1));
			q = Ln(Multiply(temp1, temp3));
			temp1 = temp2 + q;
			temp1 = Exp(temp1 * -0.25f);
			b = Multiply(c, temp1);
		}

		SIMDVectorF4 Squad(SIMDVectorF4 const & q1, SIMDVectorF4 const & a, SIMDVectorF4 const & b,
			SIMDVectorF4 const & c, float t)
		{
			return Slerp(Slerp(q1, c, t), Slerp(a, b, t), 2 * t * (1 - t));
		}

		// Plane
		///////////////////////////////////////////////////////////////////////////////
		SIMDVectorF4 DotPlane(SIMDVectorF4 const & lhs, SIMDVectorF4 const & rhs)
		{
			return DotVector4(lhs, rhs);
		}

		SIMDVectorF4 DotCoord(SIMDVectorF4 const & lhs, SIMDVectorF4 const & rhs)
		{
			return DotVector4(lhs, SetW(rhs, 1));
		}

		SIMDVectorF4 DotNormal(SIMDVectorF4 const & lhs, SIMDVectorF4 const & rhs)
		{
			return DotVector4(lhs, SetW(rhs, 0));
		}

		SIMDVectorF4 FromPointNormal(SIMDVectorF4 const & point, SIMDVectorF4 const & normal)
		{
			return SetW(normal, -GetX(DotVector3(point, normal)));
		}

		SIMDVectorF4 FromPoints(SIMDVectorF4 const & v0, SIMDVectorF4 const & v1, SIMDVectorF4 const & v2)
		{
			SIMDVectorF4 vec = CrossVector3(v1 - v0, v2 - v0);
			return FromPointNormal(v0, NormalizeVector3(vec));
		}

		SIMDVectorF4 MultiplyPlane(SIMDVectorF4 const & p, SIMDMatrixF4 const & mat)
		{
			return SetVector(
				GetX(p) * mat(0, 0) + GetY(p) * mat(1, 0) + GetZ(p) * mat(2, 0) + GetW(p) * mat(3, 0),
				GetX(p) * mat(0, 1) + GetY(p) * mat(1, 1) + GetZ(p) * mat(2, 1) + GetW(p) * mat(3, 1),
				GetX(p) * mat(0, 2) + GetY(p) * mat(1, 2) + GetZ(p) * mat(2, 2) + GetW(p) * mat(3, 2),
				GetX(p) * mat(0, 3) + GetY(p) * mat(1, 3) + GetZ(p) * mat(2, 3) + GetW(p) * mat(3, 3));
		}

		SIMDVectorF4 NormalizePlane(SIMDVectorF4 const & rhs)
		{
			SIMDVectorF4 const inv = Divide(SetVector(1), LengthVector3(rhs));
			return rhs * inv;
		}

		float IntersectRay(SIMDVectorF4 const & p, SIMDVectorF4 const & orig, SIMDVectorF4 const & dir)
		{
			float deno = GetX(DotVector3(dir, p));
			if (MathLib::equal(deno, 0.0f))
			{
				deno = 0.0001f;
			}

			return -GetX(DotCoord(p, orig)) / deno;
		}

		// From Game Programming Gems 5, Section 2.6.
		void ObliqueClipping(SIMDMatrixF4& proj, SIMDVectorF4 const & clip_plane)
		{
			SIMDVectorF4 q = SetVector(
				(MathLib::sgn(GetX(clip_plane)) - proj(2, 0)) / proj(0, 0),
				(MathLib::sgn(GetY(clip_plane)) - proj(2, 1)) / proj(1, 1),
				1,
				(1 - proj(2, 2)) / proj(3, 2));

			float const c = 1 / GetX(DotPlane(clip_plane, q));
			proj.Col(2, clip_plane * SetVector(c));
		}

		// Color
		///////////////////////////////////////////////////////////////////////////////
		SIMDVectorF4 NegativeColor(SIMDVectorF4 const & rhs)
		{
			SIMDVectorF4 ret;
			ret = SetVector(1) - rhs;
			ret = SetW(ret, GetW(rhs));
			return ret;
		}

		SIMDVectorF4 ModulateColor(SIMDVectorF4 const & lhs, SIMDVectorF4 const & rhs)
		{
			return lhs * rhs;
		}
	}
}
