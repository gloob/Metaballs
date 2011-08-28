/*
 * OpenGL library include in different platforms
 *
 * Copyright (c) 2011 Alejandro Leiva <gloob@litio.org>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * Author: Alejandro Leiva <gloob@litio.org>
 *
 */

#ifdef __APPLE__
  #include <OpenGL/gl.h>
  #include <GLUT/glut.h>
#else
  #include <GL/gl.h>
  #include <GL/glut.h>
#endif
