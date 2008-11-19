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

#ifndef CUDA_IPL_REFERENCE_H
#define CUDA_IPL_REFERENCE_H


#include "cv.h"

#include <cudatemplates/hostmemoryreference.hpp>


namespace Cuda {

/**
   Reference to existing IPL image.
*/
template <class Type, unsigned Dim>
class IplReference: public HostMemoryReference<Type, Dim>
{
public:
  /**
     Constructor.
     @param image IPL image to reference
  */
  inline IplReference(IplImage *image):
    Layout<Type, Dim>(),
    Pointer<Type, Dim>(),
    HostMemoryReference<Type, Dim>()
  {
    setImage(image);
  }

  /**
     Constructor.
     This allocates memory for the Ipl image of the given size.
     @param _size size of image
     @param _image pointer to IplImage to be referenced.
  */
  inline IplReference(const Size<Dim> &_size, IplImage *_image):
    Layout<Type, Dim>(),
    Pointer<Type, Dim>(),
    HostMemoryReference<Type, Dim>()
  {
    setImage(_image);
  }

private:
  /**
     Extract image information from IPL image.
     @param image IPL image
  */
  void setImage(IplImage *image)
  {
    image_ptr = image;

    this->size[0] = image->width;
    this->size[1] = image->height;
    this->setPitch(image->widthStep);

    // buffer is always interpreted as given template type -> TODO convert function?
    this->buffer = (Type*)image->imageData;
  }

  /**
     Pointer to IPL image.  This pointer is not used in the
     IplReference class, but it offers the possibility to handle smart
     pointers at some time. In future the IplReference should handle
     the memory of the referenced IplImage.
  */
  IplImage *image_ptr;
};

}  // namespace Cuda


#include "auto/specdim_iplreference.hpp"


#endif
