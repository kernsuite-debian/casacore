//# NQWrapperParam.cc: Parameter handling for wrapped function objects 
//# Copyright (C) 2001
//# Associated Universities, Inc. Washington DC, USA.
//#
//# This library is free software; you can redistribute it and/or modify it
//# under the terms of the GNU Library General Public License as published by
//# the Free Software Foundation; either version 2 of the License, or (at your
//# option) any later version.
//#
//# This library is distributed in the hope that it will be useful, but WITHOUT
//# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
//# FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public
//# License for more details.
//#
//# You should have received a copy of the GNU Library General Public License
//# along with this library; if not, write to the Free Software Foundation,
//# Inc., 675 Massachusetts Ave, Cambridge, MA 02139, USA.
//#
//# Correspondence concerning AIPS++ should be addressed as follows:
//#        Internet email: aips2-request@nrao.edu.
//#        Postal address: AIPS++ Project Office
//#                        National Radio Astronomy Observatory
//#                        520 Edgemont Road
//#                        Charlottesville, VA 22903-2475 USA
//#
//# $Id$

//# Includes
#include <aips/Functionals/NQWrapperParam.h>

//# Constructors
template<class T>
NQWrapperParam<T>::NQWrapperParam() :
  Function<T>(0) {}

template<class T>
NQWrapperParam<T>::NQWrapperParam(const T &par) :
  Function<T>(1) {
  param_p[0] = par;
}

template<class T>
NQWrapperParam<T>::NQWrapperParam(const Vector<T> &par) :
  Function<T>(par) {}


template<class T>
NQWrapperParam<T>::NQWrapperParam(const NQWrapperParam<T> &other) :
  Function<T>(other) {}

template<class T>
NQWrapperParam<T>::~NQWrapperParam() {}

//# Operators
template<class T>
NQWrapperParam<T> &
NQWrapperParam<T>::operator=(const NQWrapperParam<T> &other) {
  if (this != &other) Function<T>::operator=(other);
  return *this;
}
