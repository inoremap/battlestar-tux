/* IntegerVector.h
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


#ifndef INTEGERVECTOR_H_
#define INTEGERVECTOR_H_

#include <iostream>
#include <math.h>


// 3 Dimensional IntegerVector.
class ivec3 {
	public:
				ivec3() { vector[0] = 0; vector[1] = 0; vector[2] = 0; }
				ivec3( int x, int y, int z ) { vector[0] = x; vector[1] = y; vector[2] = z; }
				ivec3( const ivec3 &v ) { vector[0] = v.vector[0]; vector[1] = v.vector[1]; vector[2] = v.vector[2]; }

				inline float length() const { return sqrtf( vector[0]*vector[0] + vector[1]*vector[1] + vector[2]*vector[2] ); }

				inline void display( std::ostream & out ) const {
					out << "[" << vector[0] << ", " << vector[1] << ", " << vector[2] << "]";
				}

				inline int & operator[]( int n ) {
					if( n < 0 || n > 2 )
						return vector[0];
					else
						return vector[n];
				}

				inline ivec3 & operator=( const ivec3 &v ) {
					vector[0] = v.vector[0];
					vector[1] = v.vector[1];
					vector[2] = v.vector[2];
					return *this;
				}

				inline ivec3 & operator=( int x ) {
					vector[0] = x;
					vector[1] = x;
					vector[2] = x;
					return *this;
				}

				inline bool isIdentical( const ivec3 &v ) const {
					if (
						vector[0] == v.vector[0] &&
						vector[1] == v.vector[1] &&
						vector[2] == v.vector[2]
					) return true;
					else
						return false;
				}

				/* This is a BIG judgement call.  Comparisons are performed
				 * based on vector length, without taking direction into consideration.
				 * See isIdentical() above.
				 */
				inline bool operator==( const ivec3 &v ) const {
					if ( length() == v.length() )
						return true;
					else
						return false;
				}

				inline bool operator<=( const ivec3 &v ) const {
					if ( length() <= v.length() )
						return true;
					else
						return false;
				}

				inline bool operator>=( const ivec3 &v ) const {
					if ( length() >= v.length() )
						return true;
					else
						return false;
				}

				inline bool operator<( const ivec3 &v ) const {
					if ( length() < v.length() )
						return true;
					else
						return false;
				}

				inline bool operator>( const ivec3 &v ) const {
					if ( length() > v.length() )
						return true;
					else
						return false;
				}

				inline ivec3 & operator+=( const ivec3 &v ) {
					vector[0] += v.vector[0];
					vector[1] += v.vector[1];
					vector[2] += v.vector[2];
					return *this;
				}

				inline ivec3 & operator-=( const ivec3 &v ) {
					vector[0] -= v.vector[0];
					vector[1] -= v.vector[1];
					vector[2] -= v.vector[2];
					return *this;
				}

				inline ivec3 & operator*=( int x ) {
					vector[0] *= x;
					vector[1] *= x;
					vector[2] *= x;
					return *this;
				}

				inline ivec3 & operator/=( int x ) {
					vector[0] /= x;
					vector[1] /= x;
					vector[2] /= x;
					return *this;
				}


				inline ivec3 operator-( const ivec3 &v ) { return ivec3( -v.vector[0], -v.vector[1], -v.vector[2] ); }

				inline friend ivec3 operator-( const ivec3 &v, const ivec3 &w ) {
					return ivec3(
						v.vector[0] -  w.vector[0],
						v.vector[1] -  w.vector[1],
						v.vector[2] -  w.vector[2]
					);
				}

				inline friend ivec3 operator+( const ivec3 &v, const ivec3 &w ) {
					return ivec3(
						v.vector[0] +  w.vector[0],
						v.vector[1] +  w.vector[1],
						v.vector[2] +  w.vector[2]
					);
				}

				inline friend ivec3 operator*( const ivec3 &v, int x ) {
					return ivec3( v.vector[0] * x, v.vector[1] * x, v.vector[2] * x );
				}

				inline friend ivec3 operator*( int x, const ivec3 &v ) {
					return ivec3( v.vector[0] * x, v.vector[1] * x, v.vector[2] * x );
				}

				inline friend ivec3 operator/( const ivec3 &v, int x ) {
					return ivec3( v.vector[0] / x, v.vector[1] / x, v.vector[2] / x );
				}


				inline int dot( const ivec3 &v, const ivec3 &w ) const {
					return v.vector[0] * w.vector[0] + v.vector[1] * w.vector[1] + v.vector[2] * w.vector[2];
				}

				inline ivec3 cross( const ivec3 &v, const ivec3 &w ) const {
					return ivec3(
						v.vector[1] * w.vector[2] - v.vector[2] * w.vector[1],
						v.vector[2] * w.vector[0] - v.vector[0] * w.vector[2],
						v.vector[0] * w.vector[1] - v.vector[1] * w.vector[0]
					);
				}

	protected:
				int vector[3];
};


// 2 Dimensional IntegerVector.
class ivec2 {
	public:
				ivec2() { vector[0] = 0; vector[1] = 0; }
				ivec2( int x, int y ) { vector[0] = x; vector[1] = y; }
				ivec2( const ivec2 &v ) { vector[0] = v.vector[0]; vector[1] = v.vector[1]; }

				inline float length() const { return sqrtf( vector[0]*vector[0] + vector[1]*vector[1] ); 	}

				inline void display( std::ostream & out ) const {
					out << "[" << vector[0] << ", " << vector[1] << "]";
				}

				inline int & operator[]( int n ) {
					if( n < 0 || n > 1 )
						return vector[0];
					else
						return vector[n];
				}

				inline ivec2 & operator=( const ivec2 &v ) {
					vector[0] = v.vector[0];
					vector[1] = v.vector[1];
					return *this;
				}

				inline ivec2 & operator=( int x ) {
					vector[0] = x;
					vector[1] = x;
					return *this;
				}

				inline bool isIdentical( const ivec2 &v ) const {
					if (
						vector[0] == v.vector[0] &&
						vector[1] == v.vector[1] &&
						vector[2] == v.vector[2]
					) return true;
					else
						return false;
				}

				/* This is a BIG judgement call.  Comparisons are performed
				 * based on vector length, without taking direction into consideration.
				 * See isIdentical() above.
				 */
				inline bool operator==( const ivec2 &v ) const {
					if ( length() == v.length() )
						return true;
					else
						return false;
				}

				inline bool operator<=( const ivec2 &v ) const {
					if ( length() <= v.length() )
						return true;
					else
						return false;
				}

				inline bool operator>=( const ivec2 &v ) const {
					if ( length() >= v.length() )
						return true;
					else
						return false;
				}

				inline bool operator<( const ivec2 &v ) const {
					if ( length() < v.length() )
						return true;
					else
						return false;
				}

				inline bool operator>( const ivec2 &v ) const {
					if ( length() > v.length() )
						return true;
					else
						return false;
				}

				inline ivec2 & operator+=( const ivec2 &v ) {
					vector[0] += v.vector[0];
					vector[1] += v.vector[1];
					return *this;
				}

				inline ivec2 & operator-=( const ivec2 &v ) {
					vector[0] -= v.vector[0];
					vector[1] -= v.vector[1];
					return *this;
				}

				inline ivec2 & operator*=( int x ) {
					vector[0] *= x;
					vector[1] *= x;
					return *this;
				}

				inline ivec2 & operator/=( int x ) {
					vector[0] /= x;
					vector[1] /= x;
					return *this;
				}


				inline ivec2 operator-( const ivec2 &v ) { return ivec2( -v.vector[0], -v.vector[1] ); }

				inline friend ivec2 operator-( const ivec2 &v, const ivec2 &w ) {
					return ivec2(
						v.vector[0] -  w.vector[0],
						v.vector[1] -  w.vector[1]
					);
				}

				inline friend ivec2 operator+( const ivec2 &v, const ivec2 &w ) {
					return ivec2(
						v.vector[0] +  w.vector[0],
						v.vector[1] +  w.vector[1]
					);
				}

				inline friend ivec2 operator*( const ivec2 &v, int x ) {
					return ivec2( v.vector[0] * x, v.vector[1] * x );
				}

				inline friend ivec2 operator*( int x, const ivec2 &v ) {
					return ivec2( v.vector[0] * x, v.vector[1] * x );
				}

				inline friend ivec2 operator/( const ivec2 &v, int x ) {
					return ivec2( v.vector[0] / x, v.vector[1] / x );
				}


				inline int dot( const ivec2 &v, const ivec2 &w ) const {
					return v.vector[0] * w.vector[0] + v.vector[1] * w.vector[1];
				}

				inline ivec3 cross( const ivec2 &v, const ivec2 &w ) const {
					return ivec3(
						0,
						0,
						v.vector[0] * w.vector[1] - v.vector[1] * w.vector[0]
					);
				}

	protected:
				int vector[2];
};



inline std::ostream & operator<<( std::ostream & out, ivec3 v ) {
	v.display( out );
	return out;
}


inline std::ostream & operator<<( std::ostream & out, ivec2 v ) {
	v.display( out );
	return out;
}


#endif /*INTEGERVECTOR_H_*/
