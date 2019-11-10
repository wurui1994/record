## 0.gl.h和glu.h中的
```c
#include <winapifamily.h>
//改为
#include <windows.h>
```
> 在使用glew.h头文件时, 在前面加上`#include <windows.h>`


## 1.对于GL.h:
```c
#ifndef __gl_h_
#ifndef __GL_H__

#define __gl_h_
#define __GL_H__

#ifdef __TINYC__
#include <windows.h>
#pragma comment(lib,"opengl32")
#else
#include <winapifamily.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif
```

## 2.对于GLU.h:
```c
#ifndef __glu_h__
#ifndef __GLU_H__

#define __glu_h__
#define __GLU_H__

#ifdef __TINYC__
#include <windows.h>
#pragma comment(lib,"glu32")
#else
#include <winapifamily.h>
#endif

#include <GL/gl.h>

#ifdef __cplusplus
extern "C" {
#endif
```

## 3.对于glew.h:
> [注意Path顺序,不要受mingw32中的glew32.dll干扰]
```c
#ifdef __TINYC__
#include <windows.h>
#pragma comment(lib,"glew32")
#endif

#ifndef __glew_h__
#define __glew_h__
#define __GLEW_H__
```

## 4.对于glfw3.h:
```c
#ifndef _glfw3_h_
#define _glfw3_h_

#ifdef __TINYC__
#include <windows.h>
#pragma comment(lib,"glfw3")
#pragma comment(lib,"opengl32")
#endif

#ifdef __cplusplus
extern "C" {
#endif
```