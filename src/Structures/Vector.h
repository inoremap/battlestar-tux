/* Vector.h
 *
 * Copyright 2007 Eliot Eshelman
 * battlestartux@6by9.net
 *
 *
 *  This file is part of Battlestar Tux.
 *
 *  Battlestar Tux is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; version 2 of the License.
 *
 *  Battlestar Tux is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Battlestar Tux; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */


#ifndef VECTOR_H_
#define VECTOR_H_

#include <iostream.h>
#include <math.h>


// 3 Dimensional Vector.
class vec3 {
	public:
				vec3() { vector[0] = 0.0; vector[1] = 0.0; vector[2] = 0.0; }
				vec3( float x, float y, float z ) { vector[0] = x; vector[1] = y; vector[2] = z; }
				vec3( const vec3 &v ) { vector[0] = v.vector[0]; vector[1] = v.vector[1]; vector[2] = v.vector[2]; }

				inline float length() { return sqrtf( vector[0]*vector[0] + vector[1]*vector[1] + vector[2]*vector[2] ); }

				inline void display( ostream & out ) {
					out << "[" << vector[0] << ", " << vector[1] << ", " << vector[2] << "]";
				}

				inline float & operator[]( int n ) {
					if( n < 0 || n > 2 )
						return vector[0];
					else
						return vector[n];
				}


				inline vec3 & operator=( const vec3 &v ) {
					vector[0] = v.vector[0];
					vector[1] = v.vector[1];
					vector[2] = v.vector[2];
					return *this;
				}

				inline vec3 & operator=( float x ) {
					vector[0] = x;
					vector[1] = x;
					vector[2] = x;
					return *this;
				}

				inline vec3 & operator+=( const vec3 &v ) {
					vector[0] += v.vector[0];
					vector[1] += v.vector[1];
					vector[2] += v.vector[2];
					return *this;
				}

				inline vec3 & operator-=( const vec3 &v ) {
					vector[0] -= v.vector[0];
					vector[1] -= v.vector[1];
					vector[2] -= v.vector[2];
					return *this;
				}

				inline vec3 & operator*=( float x ) {
					vector[0] *= x;
					vector[1] *= x;
					vector[2] *= x;
					return *this;
				}

				inline vec3 & operator/=( float x ) {
					vector[0] /= x;
					vector[1] /= x;
					vector[2] /= x;
					return *this;
				}


				inline vec3 operator-( const vec3 &v ) { return vec3( -v.vector[0], -v.vector[1], -v.vector[2] ); }

				inline friend vec3 operator-( const vec3 &v, const vec3 &w ) {
					return vec3(
						v.vector[0] -  w.vector[0],
						v.vector[1] -  w.vector[1],
						v.vector[2] -  w.vector[2]
					);
				}

				inline friend vec3 operator+( const vec3 &v, const vec3 &w ) {
					return vec3(
						v.vector[0] +  w.vector[0],
						v.vector[1] +  w.vector[1],
						v.vector[2] +  w.vector[2]
					);
				}

				inline friend vec3 operator*( const vec3 &v, float x ) {
					return vec3( v.vector[0] * x, v.vector[1] * x, v.vector[2] * x );
				}

				inline friend vec3 operator*( float x, const vec3 &v ) {
					return vec3( v.vector[0] * x, v.vector[1] * x, v.vector[2] * x );
				}

				inline friend vec3 operator/( const vec3 &v, float x ) {
					return vec3( v.vector[0] / x, v.vector[1] / x, v.vector[2] / x );
				}


				inline float dot( const vec3 &v, const vec3 &w ) {
					return v.vector[0] * w.vector[0] + v.vector[1] * w.vector[1] + v.vector[2] * w.vector[2];
				}

				inline vec3 cross( const vec3 &v, const vec3 &w ) {
					return vec3(
						v.vector[1] * w.vector[2] - v.vector[2] * w.vector[1],
						v.vector[2] * w.vector[0] - v.vector[0] * w.vector[2],
						v.vector[0] * w.vector[1] - v.vector[1] * w.vector[0]
					);
				}

	protected:
				float vector[3];
};




// 2 Dimensional Vector.
class vec2 {
	public:
				vec2() { vector[0] = 0.0; vector[1] = 0.0; }
				vec2( float x, float y ) { vector[0] = x; vector[1] = y; }
				vec2( const vec2 &v ) { vector[0] = v.vector[0]; vector[1] = v.vector[1]; }

				inline void display( ostream & out ) { out << vector[0] << vector[1]; }

				inline float & operator[]( int n ) {
					if( n < 0 || n > 1 )
						return vector[0];
					else
						return vector[n];
				}


				inline vec2 & operator=( const vec2 &v ) {
					vector[0] = v.vector[0];
					vector[1] = v.vector[1];
					return *this;
				}

				inline vec2 & operator=( float x ) {
					vector[0] = x;
					vector[1] = x;
					return *this;
				}

				inline vec2 & operator+=( const vec2 &v ) {
					vector[0] += v.vector[0];
					vector[1] += v.vector[1];
					return *this;
				}

				inline vec2 & operator-=( const vec2 &v ) {
					vector[0] -= v.vector[0];
					vector[1] -= v.vector[1];
					return *this;
				}

				inline vec2 & operator*=( float x ) {
					vector[0] *= x;
					vector[1] *= x;
					return *this;
				}

				inline vec2 & operator/=( float x ) {
					vector[0] /= x;
					vector[1] /= x;
					return *this;
				}


				inline vec2 operator-( const vec2 &v ) { return vec2( -v.vector[0], -v.vector[1] ); }

				inline friend vec2 operator-( const vec2 &v, const vec2 &w ) {
					return vec2(
						v.vector[0] -  w.vector[0],
						v.vector[1] -  w.vector[1]
					);
				}

				inline friend vec2 operator+( const vec2 &v, const vec2 &w ) {
					return vec2(
						v.vector[0] +  w.vector[0],
						v.vector[1] +  w.vector[1]
					);
				}

				inline friend vec2 operator*( const vec2 &v, float x ) {
					return vec2( v.vector[0] * x, v.vector[1] * x );
				}

				inline friend vec2 operator*( float x, const vec2 &v ) {
					return vec2( v.vector[0] * x, v.vector[1] * x );
				}

				inline friend vec2 operator/( const vec2 &v, float x ) {
					return vec2( v.vector[0] / x, v.vector[1] / x );
				}


				inline float dot( const vec2 &v, const vec2 &w ) {
					return v.vector[0] * w.vector[0] + v.vector[1] * w.vector[1];
				}

				inline vec3 cross( const vec2 &v, const vec2 &w ) {
					return vec3(
						0.0,
						0.0,
						v.vector[0] * w.vector[1] - v.vector[1] * w.vector[0]
					);
				}

	protected:
				float vector[2];
};



inline ostream & operator<<( ostream & out, vec3 v ) {
	v.display( out );
	return out;
}


inline ostream & operator<<( ostream & out, vec2 v ) {
	v.display( out );
	return out;
}


#endif /*VECTOR_H_*/
