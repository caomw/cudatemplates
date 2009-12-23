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

#ifndef CUDA_GRAPHICS_OPENGL_COPY_H
#define CUDA_GRAPHICS_OPENGL_COPY_H


// #include <cudatemplates/hostmemory.hpp>
#include <cudatemplates/graphics/resource.hpp>
#include <cudatemplates/opengl/error.hpp>
#include <cudatemplates/opengl/texture.hpp>


#define CUDA_CHECK_SIZE if(dst.size != src.size) CUDA_ERROR("size mismatch")


namespace Cuda {

/**
   This namespace contains all graphics-related classes and functions of the CUDA templates.
*/
namespace Graphics {

/**
   Copy buffer object to texture.
   @param dst generic destination pointer
   @param src generic source pointer
*/
template<class Type, unsigned Dim>
void
copy(Cuda::OpenGL::Texture<Type, Dim> &dst, const OpenGL::Buffer<Type, Dim> &src)
{
  CUDA_CHECK_SIZE;

  // copying a buffer object to a texture requires unmapping the buffer object,
  // we therefore need a non-const pointer (nvcc can't handle references here):
  typedef OpenGL::Buffer<Type, Dim> buf_t;
  buf_t *src2;
  src2 = const_cast<buf_t *>(&src);

  src2->disconnect();
  src2->bind(GL_PIXEL_UNPACK_BUFFER);
  dst.glTexSubImage(0);
  src2->unbind(GL_PIXEL_UNPACK_BUFFER);
  src2->connect();
}

/**
   Copy host memory to texture.
   @param dst generic destination pointer
   @param src generic source pointer
*/
/*!!!
template<class Type, unsigned Dim>
void
copy(Texture<Type, Dim> &dst, const HostMemory<Type, Dim> &src)
{
  CUDA_CHECK_SIZE;
  dst.glTexSubImage(src.getBuffer());
}
*/

}  // namespace Graphics
}  // namespace Cuda


#undef CUDA_CHECK_SIZE


#endif
