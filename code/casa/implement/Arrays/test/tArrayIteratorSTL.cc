//# tArrayIteratorSTL.cc: Test program for the Array Iterator member class
//# Copyright (C) 2002
//# Associated Universities, Inc. Washington DC, USA.
//#
//# This program is free software; you can redistribute it and/or modify it
//# under the terms of the GNU General Public License as published by the Free
//# Software Foundation; either version 2 of the License, or (at your option)
//# any later version.
//#
//# This program is distributed in the hope that it will be useful, but WITHOUT
//# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
//# FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
//# more details.
//#
//# You should have received a copy of the GNU General Public License along
//# with this program; if not, write to the Free Software Foundation, Inc.,
//# 675 Massachusetts Ave, Cambridge, MA 02139, USA.
//#
//# Correspondence concerning AIPS++ should be addressed as follows:
//#        Internet email: aips2-request@nrao.edu.
//#        Postal address: AIPS++ Project Office
//#                        National Radio Astronomy Observatory
//#                        520 Edgemont Road
//#                        Charlottesville, VA 22903-2475 USA
//#
//# $Id$

#include <aips/Arrays/Array.h>
#include <aips/Arrays/ArrayMath.h>
#include <aips/OS/Timer.h>


void testSub (Array<Int>& arr1, const IPosition& blc,
	      const IPosition& trc, const IPosition& inc)
{
  Array<Int> arr = arr1(blc,trc,inc);
  Array<Int> arrs;
  arrs = arr;
  Array<Int>::iterator iters = arrs.begin();
  uInt i=0;
  for (Array<Int>::iterator iter=arr.begin(); iter!=arr.end(); iter++) {
    if (*iter != *iters) {
      cout << "error: " << *iter << ' ' << *iters << endl;
    }
    iters++;
    i++;
  }
  if (i != arr.nelements()) {
    cout << "error: i!=" << arr.nelements() << endl;
  }
}


void testIt()
{
  Array<Int> arr(IPosition(3,4,5,6));
  indgen(arr);
  {
    Int i=0;
    for (Array<Int>::iterator iter=arr.begin(); iter!=arr.end(); iter++) {
      if (*iter != i) {
	cout << "error: " << *iter << ' ' << i << endl;
      }
      i++;
    }
    if (uInt(i) != arr.nelements()) {
      cout << "error: i!=" << arr.nelements() << endl;
    }
  }
  testSub (arr, IPosition(3,0,0,0), IPosition(3,3,4,5), IPosition(3,1,1,1));
  testSub (arr, IPosition(3,0,0,0), IPosition(3,3,4,5), IPosition(3,2,1,1));
  testSub (arr, IPosition(3,0,0,0), IPosition(3,3,4,5), IPosition(3,1,1,2));
  testSub (arr, IPosition(3,3,0,0), IPosition(3,3,4,5), IPosition(3,1,1,1));
  testSub (arr, IPosition(3,3,4,1), IPosition(3,3,4,4), IPosition(3,1,1,1));
}


int main()
{
  testIt();
  const Int nelem = 1000000;
  //  const Int nelem = 5;
  const Int nstep = 100;
  {
    Array<Int> arr(IPosition(1,nelem));
    indgen(arr);
    Timer tim;
    for (Int j=0; j<nstep; j++) {
      Int inx=0;
      for (Array<Int>::const_iterator iter=arr.begin(); iter!=arr.end(); iter++) {
	if (*iter != inx) {
	  cout << "err" << endl;
	}
	inx++;
      }
    }
    tim.show("read  full, enditer() ");
  }
  {
    Array<Int> arr(IPosition(1,nelem));
    indgen(arr);
    Timer tim;
    for (Int j=0; j<nstep; j++) {
      Int inx=0;
      const Array<Int>::const_iterator& iterend = arr.end();
      for (Array<Int>::const_iterator iter=arr.begin(); iter!=iterend; iter++) {
	if (*iter != inx) {
	  cout << "err" << endl;
	}
	inx++;
      }
    }
    tim.show("read  full; enditer&  ");
  }
  {
    Array<Int> arr(IPosition(1,nelem));
    indgen(arr);
    Timer tim;
    for (Int j=0; j<nstep; j++) {
      Int inx=0;
      const Array<Int>::const_iterator iterend = arr.end();
      for (Array<Int>::const_iterator iter=arr.begin(); iter!=iterend; iter++) {
	if (*iter != inx) {
	  cout << "err" << endl;
	}
	inx++;
      }
    }
    tim.show("read  full, enditer   ");
  }
  {
    Array<Int> bl(IPosition(1,nelem));
    indgen(bl);
    Timer tim;
    for (Int j=0; j<nstep; j++) {
      Int inx=0;
      Bool deleteIt;
      const Int* str = bl.getStorage(deleteIt);
      for (Int i=0; i<nelem; i++) {
	if (str[i] != inx) {
	  cout << "err" << endl;
	}
	inx++;
      }
      bl.freeStorage(str, deleteIt);
    }
    tim.show("read  full, getStorage");
  }
  {
    Array<Int> bl1(IPosition(2,1000,1000));
    Array<Int> bl = bl1(IPosition(2,50,50), bl1.shape()-50);
    indgen(bl);
    Timer tim;
    for (Int j=0; j<nstep; j++) {
      Int inx=0;
      Bool deleteIt;
      uInt n = bl.nelements();
      const Int* str = bl.getStorage(deleteIt);
      for (uInt i=0; i<n; i++) {
	if (str[i] != inx) {
	  cout << "err" << endl;
	}
	inx++;
      }
      bl.freeStorage(str, deleteIt);
    }
    tim.show("read  part, getStorage");
  }
  {
    Array<Int> bl1(IPosition(2,1000,1000));
    Array<Int> arr = bl1(IPosition(2,50,50), bl1.shape()-50);
    indgen(arr);
    Timer tim;
    for (Int j=0; j<nstep; j++) {
      Int inx=0;
      for (Array<Int>::const_iterator iter=arr.begin(); iter!=arr.end(); iter++) {
	if (*iter != inx) {
	  cout << "err" << endl;
	}
	inx++;
      }
    }
    tim.show("read  part, enditer() ");
  }
  {
    Array<Int> bl1(IPosition(2,1000,1000));
    Array<Int> bl = bl1(IPosition(2,50,50), bl1.shape()-50, IPosition(2,2,2));
    indgen(bl);
    Timer tim;
    for (Int j=0; j<nstep; j++) {
      Int inx=0;
      Bool deleteIt;
      uInt n = bl.nelements();
      const Int* str = bl.getStorage(deleteIt);
      for (uInt i=0; i<n; i++) {
	if (str[i] != inx) {
	  cout << "err" << endl;
	}
	inx++;
      }
      bl.freeStorage(str, deleteIt);
    }
    tim.show("read  incr, getStorage");
  }
  {
    Array<Int> bl1(IPosition(2,1000,1000));
    Array<Int> arr = bl1(IPosition(2,50,50), bl1.shape()-50, IPosition(2,2,2));
    indgen(arr);
    Timer tim;
    for (Int j=0; j<nstep; j++) {
      Int inx=0;
      for (Array<Int>::const_iterator iter=arr.begin(); iter!=arr.end(); iter++) {
	if (*iter != inx) {
	  cout << "err" << endl;
	}
	inx++;
      }
    }
    tim.show("read  incr, enditer() ");
  }
  {
    Array<Int> bl1(IPosition(2,1000,1000));
    Array<Int> bl = bl1(IPosition(2,50,0), IPosition(2,50,999));
    indgen(bl);
    Timer tim;
    for (Int j=0; j<nstep; j++) {
      Int inx=0;
      Bool deleteIt;
      uInt n = bl.nelements();
      const Int* str = bl.getStorage(deleteIt);
      for (uInt i=0; i<n; i++) {
	if (str[i] != inx) {
	  cout << "err" << endl;
	}
	inx++;
      }
      bl.freeStorage(str, deleteIt);
    }
    tim.show("read  small getStorage");
  }
  {
    Array<Int> bl1(IPosition(2,1000,1000));
    Array<Int> arr = bl1(IPosition(2,50,0), IPosition(2,50,999));
    indgen(arr);
    Timer tim;
    for (Int j=0; j<nstep; j++) {
      Int inx=0;
      for (Array<Int>::const_iterator iter=arr.begin(); iter!=arr.end(); iter++) {
	if (*iter != inx) {
	  cout << "err" << endl;
	}
	inx++;
      }
    }
    tim.show("read  small enditer() ");
  }

  {
    Array<Int> arr(IPosition(1,nelem));
    Timer tim;
    for (Int j=0; j<nstep; j++) {
      Int inx=0;
      for (Array<Int>::iterator iter=arr.begin(); iter!=arr.end(); iter++) {
	*iter = inx;
	inx++;
      }
    }
    tim.show("write full, enditer() ");
  }
  {
    Array<Int> arr(IPosition(1,nelem));
    Timer tim;
    for (Int j=0; j<nstep; j++) {
      Int inx=0;
      const Array<Int>::iterator& iterend = arr.end();
      for (Array<Int>::iterator iter=arr.begin(); iter!=iterend; iter++) {
	*iter = inx;
	inx++;
      }
    }
    tim.show("write full; enditer&  ");
  }
  {
    Array<Int> arr(IPosition(1,nelem));
    Timer tim;
    for (Int j=0; j<nstep; j++) {
      Int inx=0;
      const Array<Int>::iterator iterend = arr.end();
      for (Array<Int>::iterator iter=arr.begin(); iter!=iterend; iter++) {
	*iter = inx;
	inx++;
      }
    }
    tim.show("write full, enditer   ");
  }
  {
    Array<Int> bl(IPosition(1,nelem));
    Timer tim;
    for (Int j=0; j<nstep; j++) {
      Int inx=0;
      Bool deleteIt;
      Int* str = bl.getStorage(deleteIt);
      for (Int i=0; i<nelem; i++) {
	str[i] = inx;
	inx++;
      }
      bl.putStorage(str, deleteIt);
    }
    tim.show("write full, getStorage");
  }
  {
    Array<Int> bl1(IPosition(2,1000,1000));
    Array<Int> bl = bl1(IPosition(2,50,50), bl1.shape()-50);
    Timer tim;
    for (Int j=0; j<nstep; j++) {
      Int inx=0;
      Bool deleteIt;
      uInt n = bl.nelements();
      Int* str = bl.getStorage(deleteIt);
      for (uInt i=0; i<n; i++) {
	str[i] = inx;
	inx++;
      }
      bl.putStorage(str, deleteIt);
    }
    tim.show("write part, getStorage");
  }
  {
    Array<Int> bl1(IPosition(2,1000,1000));
    Array<Int> arr = bl1(IPosition(2,50,50), bl1.shape()-50);
    Timer tim;
    for (Int j=0; j<nstep; j++) {
      Int inx=0;
      for (Array<Int>::iterator iter=arr.begin(); iter!=arr.end(); iter++) {
	*iter = inx;
	inx++;
      }
    }
    tim.show("write part, enditer() ");
  }
  {
    Array<Int> bl1(IPosition(2,1000,1000));
    Array<Int> bl = bl1(IPosition(2,50,50), bl1.shape()-50, IPosition(2,2,2));
    Timer tim;
    for (Int j=0; j<nstep; j++) {
      Int inx=0;
      Bool deleteIt;
      uInt n = bl.nelements();
      Int* str = bl.getStorage(deleteIt);
      for (uInt i=0; i<n; i++) {
	str[i] = inx;
	inx++;
      }
      bl.putStorage(str, deleteIt);
    }
    tim.show("write incr, getStorage");
  }
  {
    Array<Int> bl1(IPosition(2,1000,1000));
    Array<Int> arr = bl1(IPosition(2,50,50), bl1.shape()-50, IPosition(2,2,2));
    Timer tim;
    for (Int j=0; j<nstep; j++) {
      Int inx=0;
      for (Array<Int>::iterator iter=arr.begin(); iter!=arr.end(); iter++) {
	*iter = inx;
	inx++;
      }
    }
    tim.show("write incr, enditer() ");
  }
  {
    Array<Int> bl1(IPosition(2,1000,1000));
    Array<Int> bl = bl1(IPosition(2,50,0), IPosition(2,50,999));
    Timer tim;
    for (Int j=0; j<nstep; j++) {
      Int inx=0;
      Bool deleteIt;
      uInt n = bl.nelements();
      Int* str = bl.getStorage(deleteIt);
      for (uInt i=0; i<n; i++) {
	str[i] = inx;
	inx++;
      }
      bl.putStorage(str, deleteIt);
    }
    tim.show("write small getStorage");
  }
  {
    Array<Int> bl1(IPosition(2,1000,1000));
    Array<Int> arr = bl1(IPosition(2,50,0), IPosition(2,50,999));
    Timer tim;
    for (Int j=0; j<nstep; j++) {
      Int inx=0;
      for (Array<Int>::iterator iter=arr.begin(); iter!=arr.end(); iter++) {
	*iter = inx;
	inx++;
      }
    }
    tim.show("write small enditer() ");
  }
}
