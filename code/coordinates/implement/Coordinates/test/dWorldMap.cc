//# dWorldMap.cc: demonstarte use of CoordinateSystem::worldMap
//# Copyright (C) 1994,1995,1996,1997,1998,1999
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

#include <aips/aips.h>
#include <aips/Arrays.h>
#include <aips/Utilities/String.h>
#include <aips/Exceptions/Error.h>
#include <trial/Coordinates.h>
#include <iostream.h>

void list (Bool ok, Vector<Int>& map,
           Vector<Int>& transpose,
           CoordinateSystem& cSys1,
           CoordinateSystem& cSys2);


main (int argc, char **argv)
//
// Test out the worldMap function in CoordinateSYstem
{
try {

   Vector<Int> map;
   Vector<Int> transpose;

   {
      cout << "2D [ra, dec] & 0D" << endl;
      CoordinateSystem cSys1 = CoordinateUtil::defaultCoords2D();
      CoordinateSystem cSys2;
      Bool ok = cSys1.worldMap(map, transpose, cSys2);
      list (ok, map, transpose, cSys1, cSys2);
      cout << endl << endl;
   }

   {
      cout << "0D & 2D [ra, dec]" << endl;
      CoordinateSystem cSys1;
      CoordinateSystem cSys2 = CoordinateUtil::defaultCoords2D();
      Bool ok = cSys1.worldMap(map, transpose, cSys2);
      list (ok, map, transpose, cSys1, cSys2);
      cout << endl << endl;
   }


   {
      cout << "3D [ra, dec, spec] & 3D [ra, dec, spec]" << endl;
      CoordinateSystem cSys1 = CoordinateUtil::defaultCoords3D();
      CoordinateSystem cSys2 = CoordinateUtil::defaultCoords3D();
      Bool ok = cSys1.worldMap(map, transpose, cSys2);
      list (ok, map, transpose, cSys1, cSys2);
      cout << endl << endl;
   }

   {
      cout << "2D [ra, dec] & 3D [ra, dec, spec]" << endl;
      CoordinateSystem cSys1 = CoordinateUtil::defaultCoords2D();
      CoordinateSystem cSys2 = CoordinateUtil::defaultCoords3D();
      Bool ok = cSys1.worldMap(map, transpose, cSys2);
      list (ok, map, transpose, cSys1, cSys2);
      cout << endl << endl;
   }

   {
      cout << "3D [ra, dec, spec] & 2D [ra, dec]" << endl;
      CoordinateSystem cSys1 = CoordinateUtil::defaultCoords3D();
      CoordinateSystem cSys2 = CoordinateUtil::defaultCoords2D();
      Bool ok = cSys1.worldMap(map, transpose, cSys2);
      list (ok, map, transpose, cSys1, cSys2);
      cout << endl << endl;
   }

   {
      cout << "3D [ra, dec, spec] & 3D [dec, spec, ra]" << endl;
     
      CoordinateSystem cSys1 = CoordinateUtil::defaultCoords3D();
      CoordinateSystem cSys2 = CoordinateUtil::defaultCoords3D();
      Vector<Int> worldOrder(cSys2.nWorldAxes());
      Vector<Int> pixelOrder(cSys2.nPixelAxes());
      worldOrder(0) = 1; worldOrder(1) = 2; worldOrder(2) = 0;
      pixelOrder = worldOrder;
      cSys2.transpose(worldOrder, pixelOrder);
  
      Bool ok = cSys1.worldMap(map, transpose, cSys2);
      list (ok, map, transpose, cSys1, cSys2);
      cout << endl << endl;
   }

   {
      cout << "2D [ra,dec] & 3D [ra, dec, spec] " << endl;
      cout << "   [0, 1]   &    [0, 1, -1]" << endl;
      CoordinateSystem cSys2 = CoordinateUtil::defaultCoords3D();
      Int pSpec = CoordinateUtil::findSpectralAxis(cSys2);
      if (pSpec >= 0) {
         Int wSpec = cSys2.pixelAxisToWorldAxis(pSpec);
         cSys2.removeWorldAxis(wSpec, cSys2.referenceValue()(wSpec));
//
         CoordinateSystem cSys1 = CoordinateUtil::defaultCoords2D();
         Bool ok = cSys1.worldMap(map, transpose, cSys2);
         list (ok, map, transpose, cSys1, cSys2);
      } else {
         cout << "Spectral missing.  This was not expected" << endl;
      }
      cout << endl << endl;
   }

   {
      cout << "2D [ra,dec] & 3D [spec, dec, ra] " << endl;
      cout << "   [0, 1]   &    [-1, 0, 1]" << endl;
      CoordinateSystem cSys1 = CoordinateUtil::defaultCoords2D();
      CoordinateSystem cSys2 = CoordinateUtil::defaultCoords3D();

      Vector<Int> worldOrder(cSys2.nWorldAxes());
      Vector<Int> pixelOrder(cSys2.nPixelAxes());
      worldOrder(0) = 2; worldOrder(1) = 1; worldOrder(2) = 0;
      pixelOrder = worldOrder;
      cSys2.transpose(worldOrder, pixelOrder);
//
      Int pSpec = CoordinateUtil::findSpectralAxis(cSys2);
      if (pSpec >= 0) {
         Int wSpec = cSys2.pixelAxisToWorldAxis(pSpec);
         cSys2.removeWorldAxis(wSpec, cSys2.referenceValue()(wSpec));
//
         Bool ok = cSys1.worldMap(map, transpose, cSys2);
         list (ok, map, transpose, cSys1, cSys2);
      } else {
         cout << "Spectral missing.  This was not expected" << endl;
      }
      cout << endl << endl;
   }

   {
      cout << "3D [spec, dec, ra] & 2D [ra,dec]" << endl;
      cout << "   [-1, 0, 1]      &    [0,  1]" << endl;

      CoordinateSystem cSys1 = CoordinateUtil::defaultCoords3D();
      CoordinateSystem cSys2 = CoordinateUtil::defaultCoords2D();

      Vector<Int> worldOrder(cSys1.nWorldAxes());
      Vector<Int> pixelOrder(cSys1.nPixelAxes());
      worldOrder(0) = 2; worldOrder(1) = 1; worldOrder(2) = 0;
      pixelOrder = worldOrder;
      cSys1.transpose(worldOrder, pixelOrder);
//
      Int pSpec = CoordinateUtil::findSpectralAxis(cSys1);
      if (pSpec >= 0) {
         Int wSpec = cSys1.pixelAxisToWorldAxis(pSpec);
         cSys1.removeWorldAxis(wSpec, cSys1.referenceValue()(wSpec));
//
         Bool ok = cSys1.worldMap(map, transpose, cSys2);
         list (ok, map, transpose, cSys1, cSys2);
      } else {
         cout << "Spectral missing.  This was not expected" << endl;
      }
      cout << endl << endl;
   }

   {
      cout << "2D [ra, dec] & 2D [spec, stokes]" << endl;

      CoordinateSystem cSys1 = CoordinateUtil::defaultCoords2D();
      CoordinateSystem cSys2;
      CoordinateUtil::addFreqAxis(cSys2);
      CoordinateUtil::addIQUVAxis(cSys2);

      Bool ok = cSys1.worldMap(map, transpose, cSys2);
      list (ok, map, transpose, cSys1, cSys2);
      cout << endl << endl;
   }

   {
      cout << "3D [ra, dec, spec] & 4D [ra, dec, stokes, spec]" << endl;
 
      CoordinateSystem cSys1 = CoordinateUtil::defaultCoords3D();
      CoordinateSystem cSys2;
      CoordinateUtil::addDirAxes(cSys2);
      CoordinateUtil::addIQUVAxis(cSys2);
      CoordinateUtil::addFreqAxis(cSys2);
 
      Bool ok = cSys1.worldMap(map, transpose, cSys2);
      list (ok, map, transpose, cSys1, cSys2);
      cout << endl << endl;
   }
 


}
   catch (AipsError x) {
      cerr << "aipserror: error " << x.getMesg() << endl;
      exit(1);
  }end_try;
 
  exit(0);
 
}

void list (Bool ok, Vector<Int>& map,
           Vector<Int>& transpose,
           CoordinateSystem& cSys1,
           CoordinateSystem& cSys2)
{
   cout << endl;
   if (!ok) {
      cout << "Failed with message " << cSys1.errorMessage() << endl;
   } else {
      cout << "Success returned" << endl;
    }
   cout << "cSys1.worldAxisNames = " << cSys1.worldAxisNames() << endl;
   cout << "cSys2.worldAxisNames = " << cSys2.worldAxisNames() << endl;
   cout << "map = " << map << endl;
   cout << "transpose = " << transpose << endl << endl;
}
