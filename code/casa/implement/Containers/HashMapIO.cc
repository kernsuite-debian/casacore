//# HashMapIO.cc: Classes to perform IO for HashMap classas
//# Copyright (C) 1993,1994,1995,2000
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


#include <trial/Containers/HashMapIO.h>
#include <aips/IO/AipsIO.h>

#if MAPIO_COMPATIBILITY
#include <aips/Containers/OrderedMap.h>
#include <aips/Exceptions/Error.h>
#endif
#if defined(AIPS_STUPID_SUN)
#undef AIPS_STUPID_SUN
#endif

template<class key, class val> AipsIO &operator<<(AipsIO &ios, const HashMap<key,val> &map) {
  ConstHashMapIter<key,val> mapP(map);
  ios.putstart (rtti_decode(map.id()), HashMap<key,val>::HashMapVersion);
  mapP.toStart();
  ios << map.maxLoad();
  ios << map.ndefined();
  ios << map.defaultVal();
  while (mapP.atEnd() != True) {
    ios << mapP.getKey();
    ios << mapP.getVal();
    mapP++;
  }
  ios.putend ();
  return ios;
}

template<class key, class val> AipsIO &operator>>(AipsIO &ios, HashMap<key,val> &map) {
  key k;
  int len,i;

#if MAPIO_COMPATIBILITY
  int vers = -1;
  try {
      vers = ios.getstart(rtti_decode(map.id()));
      float max_load;
      ios >> max_load;
      map.setMaxLoad(max_load);
  } catch ( AipsError xxx ) {
      OrderedMap<key,val> om(map.defaultVal());
      vers = ios.getstart(rtti_decode(((Map<key,val>*)&om)->id()));
  } 
#else
  int vers = ios.getstart(rtti_decode(map.id()));
  float max_load;
  ios >> max_load;
  map.setMaxLoad(max_load);
#endif

  map.clear();
  ios >> len;
  ios >> map.defaultVal();
  for (i=0; i<len; i++) {
    ios >> k;
    ios >> map(k);
  }
  ios.getend ();

  return ios;
}

template<class key, class val> AipsIO &operator<<(AipsIO &ios, const ConstHashMapIter<key,val> &map) {

  return operator<<(ios,map.container());

}

template<class key, class val> AipsIO &operator>>(AipsIO &ios, HashMapIter<key,val> &map) {

  return operator>>(ios,map.container());

}

template<class key, class val> ostream &operator<<(ostream &ios, const HashMap<key,val> &map) {
#if !defined(AIPS_STUPID_SUN)
  ConstHashMapIter<key,val> mapP(map);
#else
  ConstHashMapIter<key,val> *mapPP = map.getIter();
  ConstHashMapIter<key,val> &mapP = *mapPP;
#endif
  mapP.toStart();
//ios << map.ndefined();
//ios << map.defaultVal();
  while (mapP.atEnd() != True) {
    ios << "(";
    ios << mapP.getKey();
    ios << ",";
    ios << mapP.getVal();
    ios << ")";
    mapP++;
  }
#if defined(AIPS_STUPID_SUN)
  delete mapPP;
#endif
  return ios;
}

template<class key, class val> ostream &operator<<(ostream &ios, const ConstHashMapIter<key,val> &map) {

  return operator<<(ios,map.container());

}
