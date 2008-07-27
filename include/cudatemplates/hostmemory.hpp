/*
  Cuda Templates.

  Copyright (C) 2008 Institute for Computer Graphics and Vision,
                     Graz University of Technology
  
  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 3 of the License, or
  (at your option) any later version.
  
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CUDA_HOSTMEMORY_H
#define CUDA_HOSTMEMORY_H


#include <cstdlib>
#include <cstring>

#include <cudatemplates/error.hpp>
#include <cudatemplates/storage.hpp>


namespace Cuda {

/**
   Representation of CPU memory.
   This is the base class for all kind of CPU memory.
*/
template <class Type, unsigned Dim>
class HostMemory: virtual public Pointer<Type, Dim>
{
public:
#ifndef CUDA_NO_DEFAULT_CONSTRUCTORS
  /**
     Default constructor.
  */
  inline HostMemory()
  {
  }
#endif

  /**
     Constructor.
     @param _size requested size of memory block
  */
  inline HostMemory(const Size<Dim> &_size):
    Layout<Type, Dim>(_size),
    Pointer<Type, Dim>(_size)
  {
  }

  /**
     Constructor.
     @param layout requested layout of memory block
  */
  inline HostMemory(const Layout<Type, Dim> &layout):
    Layout<Type, Dim>(layout),
    Pointer<Type, Dim>(layout)
  {
  }

protected:
  inline HostMemory(const HostMemory<Type, Dim> &x):
    Layout<Type, Dim>(x),
    Pointer<Type, Dim>(x)
  {
  }
};

/**
   Representation of CPU memory managed by the CUDA Toolkit.
   This is the base class for all kind of CPU memory for which memory
   management is performed by the CUDA Toolkit.
*/
template <class Type, unsigned Dim>
class HostMemoryStorage: public HostMemory<Type, Dim>, public PointerStorage<Type, Dim>
{
public:
#ifndef CUDA_NO_DEFAULT_CONSTRUCTORS
  /**
     Default constructor.
  */
  inline HostMemoryStorage()
  {
  }
#endif

  /**
     Constructor.
     @param _size requested size of memory block
  */
  inline HostMemoryStorage(const Size<Dim> &_size):
    Layout<Type, Dim>(_size),
    Pointer<Type, Dim>(_size),
    HostMemory<Type, Dim>(_size),
    PointerStorage<Type, Dim>(_size)
  {
  }

  /**
     Constructor.
     @param layout requested layout of memory block
  */
  inline HostMemoryStorage(const Layout<Type, Dim> &layout):
    Layout<Type, Dim>(layout),
    Pointer<Type, Dim>(layout),
    HostMemory<Type, Dim>(layout),
    PointerStorage<Type, Dim>(layout)
  {
  }

  inline void init() { this->buffer = 0; }

protected:
  inline HostMemoryStorage(const HostMemoryStorage<Type, Dim> &x):
    Layout<Type, Dim>(x),
    Pointer<Type, Dim>(x),
    HostMemory<Type, Dim>(x),
    PointerStorage<Type, Dim>(x)
  {
  }
};

}


#endif
