//
//  OSXIncludes.h
//  XGLMetalRenderer
//
//  Created by jacques tronconi on 14/07/2021.
//

#ifndef __XGL_OSXINCLUDES_H__
#define __XGL_OSXINCLUDES_H__

#include <XGL/XGL.h>

#ifdef __OBJC__
#include <Cocoa/Cocoa.h>
#include <Metal/Metal.h>
#include <MetalKit/MetalKit.h>
#include <MetalPerformanceShaders/MetalPerformanceShaders.h>

#else
#define id void*

#endif

#endif /* __XGL_OSXINCLUDES_H__ */
