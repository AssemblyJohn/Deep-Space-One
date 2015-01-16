/**
* Copyright (c) 2015 Lazu Ioan-Bogdan
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, without any restrictions.
*/

#ifndef GL_INCLUDE_H
#define GL_INCLUDE_H

#include <Windows.h>
#include <gl\GL.h>
#include "../../thirdparty/OpenGL/glext.h"

// Must be called to initialize functions
void InitializeGL();

// ARB extensions
extern PFNGLQUERYCOUNTERPROC		enGlQueryCounter;
extern PFNGLGETQUERYOBJECTI64VPROC	enGlGetQueryObjecti64v;
extern PFNGLGETQUERYOBJECTUI64VPROC enGlGetQueryObjectui64v;

#define glQueryCounter				enGlQueryCounter
#define glGetQueryObjecti64v		enGlGetQueryObjecti64v
#define glGetQueryObjectui64v		enGlGetQueryObjectui64v

// 1.3 Compliant
extern PFNGLACTIVETEXTUREPROC		enGlActiveTexture;

#define glActiveTexture enGlActiveTexture


// 1.5 Compliant
extern PFNGLGENQUERIESPROC				enGlGenQueries;
extern PFNGLDELETEQUERIESPROC			enGlDeleteQueries;
extern PFNGLISQUERYPROC					enGlIsQuery;
extern PFNGLBEGINQUERYPROC				enGlBeginQuery;
extern PFNGLENDQUERYPROC				enGlEndQuery;
extern PFNGLGETQUERYIVPROC				enGlGetQueryiv;
extern PFNGLGETQUERYOBJECTIVPROC		enGlGetQueryObjectiv;
extern PFNGLGETQUERYOBJECTUIVPROC		enGlGetQueryObjectuiv;
extern PFNGLBINDBUFFERPROC				enGlBindBuffer;
extern PFNGLDELETEBUFFERSPROC			enGlDeleteBuffers;
extern PFNGLGENBUFFERSPROC				enGlGenBuffers;
extern PFNGLISBUFFERPROC				enGlIsBuffer;
extern PFNGLBUFFERDATAPROC				enGlBufferData;
extern PFNGLBUFFERSUBDATAPROC			enGlBufferSubData;
extern PFNGLGETBUFFERSUBDATAPROC		enGlGetBufferSubData;
extern PFNGLMAPBUFFERPROC				enGlMapBuffer;
extern PFNGLUNMAPBUFFERPROC				enGlUnmapBuffer;
extern PFNGLGETBUFFERPARAMETERIVPROC	enGlGetBufferParameteriv;
extern PFNGLGETBUFFERPOINTERVPROC		enGlGetBufferPointerv;

#define glGenQueries			enGlGenQueries
#define glDeleteQueries			enGlDeleteQueries
#define glIsQuery				enGlIsQuery
#define glBeginQuery			enGlBeginQuery
#define glEndQuery				enGlEndQuery
#define glGetQueryiv			enGlGetQueryiv
#define glGetQueryObjectiv		enGlGetQueryObjectiv
#define glGetQueryObjectuiv		enGlGetQueryObjectuiv
#define glBindBuffer			enGlBindBuffer
#define glDeleteBuffers			enGlDeleteBuffers
#define glGenBuffers			enGlGenBuffers
#define glIsBuffer				enGlIsBuffer
#define glBufferData			enGlBufferData
#define glBufferSubData			enGlBufferSubData
#define glGetBufferSubData		enGlGetBufferSubData
#define glMapBuffer				enGlMapBuffer
#define glUnmapBuffer			enGlUnmapBuffer
#define glGetBufferParameteriv	enGlGetBufferParameteriv
#define glGetBufferPointerv		enGlGetBufferPointerv


// 2.0 Compliant
extern PFNGLBLENDEQUATIONSEPARATEPROC		enGlBlendEquationSeparate;
extern PFNGLDRAWBUFFERSPROC					enGlDrawBuffers;
extern PFNGLSTENCILOPSEPARATEPROC			enGlStencilOpSeparate;
extern PFNGLSTENCILFUNCSEPARATEPROC			enGlStencilFuncSeparate;
extern PFNGLSTENCILMASKSEPARATEPROC			enGlStencilMaskSeparate;
extern PFNGLATTACHSHADERPROC				enGlAttachShader;
extern PFNGLBINDATTRIBLOCATIONPROC			enGlBindAttribLocation;
extern PFNGLCOMPILESHADERPROC				enGlCompileShader;
extern PFNGLCREATEPROGRAMPROC				enGlCreateProgram;
extern PFNGLCREATESHADERPROC				enGlCreateShader;
extern PFNGLDELETEPROGRAMPROC				enGlDeleteProgram;
extern PFNGLDELETESHADERPROC				enGlDeleteShader;
extern PFNGLDETACHSHADERPROC				enGlDetachShader;
extern PFNGLDISABLEVERTEXATTRIBARRAYPROC	enGlDisableVertexAttribArray;
extern PFNGLENABLEVERTEXATTRIBARRAYPROC		enGlEnableVertexAttribArray;
extern PFNGLGETACTIVEATTRIBPROC				enGlGetActiveAttrib;
extern PFNGLGETACTIVEUNIFORMPROC			enGlGetActiveUniform;
extern PFNGLGETATTACHEDSHADERSPROC			enGlGetAttachedShaders;
extern PFNGLGETATTRIBLOCATIONPROC			enGlGetAttribLocation;
extern PFNGLGETPROGRAMIVPROC				enGlGetProgramiv;
extern PFNGLGETPROGRAMINFOLOGPROC			enGlGetProgramInfoLog;
extern PFNGLGETSHADERIVPROC					enGlGetShaderiv;
extern PFNGLGETSHADERINFOLOGPROC			enGlGetShaderInfoLog;
extern PFNGLGETSHADERSOURCEPROC				enGlGetShaderSource;
extern PFNGLGETUNIFORMLOCATIONPROC			enGlGetUniformLocation;
extern PFNGLGETUNIFORMFVPROC				enGlGetUniformfv;
extern PFNGLGETUNIFORMIVPROC				enGlGetUniformiv;
extern PFNGLGETVERTEXATTRIBDVPROC			enGlGetVertexAttribdv;
extern PFNGLGETVERTEXATTRIBFVPROC			enGlGetVertexAttribfv;
extern PFNGLGETVERTEXATTRIBIVPROC			enGlGetVertexAttribiv;
extern PFNGLGETVERTEXATTRIBPOINTERVPROC		enGlGetVertexAttribPointerv;
extern PFNGLISPROGRAMPROC					enGlIsProgram;
extern PFNGLISSHADERPROC					enGlIsShader;
extern PFNGLLINKPROGRAMPROC					enGlLinkProgram;
extern PFNGLSHADERSOURCEPROC				enGlShaderSource;
extern PFNGLUSEPROGRAMPROC					enGlUseProgram;
extern PFNGLUNIFORM1FPROC					enGlUniform1f;
extern PFNGLUNIFORM2FPROC					enGlUniform2f;
extern PFNGLUNIFORM3FPROC					enGlUniform3f;
extern PFNGLUNIFORM4FPROC					enGlUniform4f;
extern PFNGLUNIFORM1IPROC					enGlUniform1i;
extern PFNGLUNIFORM2IPROC					enGlUniform2i;
extern PFNGLUNIFORM3IPROC					enGlUniform3i;
extern PFNGLUNIFORM4IPROC					enGlUniform4i;
extern PFNGLUNIFORM1FVPROC					enGlUniform1fv;
extern PFNGLUNIFORM2FVPROC					enGlUniform2fv;
extern PFNGLUNIFORM3FVPROC					enGlUniform3fv;
extern PFNGLUNIFORM4FVPROC					enGlUniform4fv;
extern PFNGLUNIFORM1IVPROC					enGlUniform1iv;
extern PFNGLUNIFORM2IVPROC					enGlUniform2iv;
extern PFNGLUNIFORM3IVPROC					enGlUniform3iv;
extern PFNGLUNIFORM4IVPROC					enGlUniform4iv;
extern PFNGLUNIFORMMATRIX2FVPROC			enGlUniformMatrix2fv;
extern PFNGLUNIFORMMATRIX3FVPROC			enGlUniformMatrix3fv;
extern PFNGLUNIFORMMATRIX4FVPROC			enGlUniformMatrix4fv;
extern PFNGLVALIDATEPROGRAMPROC				enGlValidateProgram;
extern PFNGLVERTEXATTRIB1DPROC				enGlVertexAttrib1d;
extern PFNGLVERTEXATTRIB1DVPROC				enGlVertexAttrib1dv;
extern PFNGLVERTEXATTRIB1FPROC				enGlVertexAttrib1f;
extern PFNGLVERTEXATTRIB1FVPROC				enGlVertexAttrib1fv;
extern PFNGLVERTEXATTRIB1SPROC				enGlVertexAttrib1s;
extern PFNGLVERTEXATTRIB1SVPROC				enGlVertexAttrib1sv;
extern PFNGLVERTEXATTRIB2DPROC				enGlVertexAttrib2d;
extern PFNGLVERTEXATTRIB2DVPROC				enGlVertexAttrib2dv;
extern PFNGLVERTEXATTRIB2FPROC				enGlVertexAttrib2f;
extern PFNGLVERTEXATTRIB2FVPROC				enGlVertexAttrib2fv;
extern PFNGLVERTEXATTRIB2SPROC				enGlVertexAttrib2s;
extern PFNGLVERTEXATTRIB2SVPROC				enGlVertexAttrib2sv;
extern PFNGLVERTEXATTRIB3DPROC				enGlVertexAttrib3d;
extern PFNGLVERTEXATTRIB3DVPROC				enGlVertexAttrib3dv;
extern PFNGLVERTEXATTRIB3FPROC				enGlVertexAttrib3f;
extern PFNGLVERTEXATTRIB3FVPROC				enGlVertexAttrib3fv;
extern PFNGLVERTEXATTRIB3SPROC				enGlVertexAttrib3s;
extern PFNGLVERTEXATTRIB3SVPROC				enGlVertexAttrib3sv;
extern PFNGLVERTEXATTRIB4NBVPROC			enGlVertexAttrib4Nbv;
extern PFNGLVERTEXATTRIB4NIVPROC			enGlVertexAttrib4Niv;
extern PFNGLVERTEXATTRIB4NSVPROC			enGlVertexAttrib4Nsv;
extern PFNGLVERTEXATTRIB4NUBPROC			enGlVertexAttrib4Nub;
extern PFNGLVERTEXATTRIB4NUBVPROC			enGlVertexAttrib4Nubv;
extern PFNGLVERTEXATTRIB4NUIVPROC			enGlVertexAttrib4Nuiv;
extern PFNGLVERTEXATTRIB4NUSVPROC			enGlVertexAttrib4Nusv;
extern PFNGLVERTEXATTRIB4BVPROC				enGlVertexAttrib4bv;
extern PFNGLVERTEXATTRIB4DPROC				enGlVertexAttrib4d;
extern PFNGLVERTEXATTRIB4DVPROC				enGlVertexAttrib4dv;
extern PFNGLVERTEXATTRIB4FPROC				enGlVertexAttrib4f;
extern PFNGLVERTEXATTRIB4FVPROC				enGlVertexAttrib4fv;
extern PFNGLVERTEXATTRIB4IVPROC				enGlVertexAttrib4iv;
extern PFNGLVERTEXATTRIB4SPROC				enGlVertexAttrib4s;
extern PFNGLVERTEXATTRIB4SVPROC				enGlVertexAttrib4sv;
extern PFNGLVERTEXATTRIB4UBVPROC			enGlVertexAttrib4ubv;
extern PFNGLVERTEXATTRIB4UIVPROC			enGlVertexAttrib4uiv;
extern PFNGLVERTEXATTRIB4USVPROC			enGlVertexAttrib4usv;
extern PFNGLVERTEXATTRIBPOINTERPROC			enGlVertexAttribPointer;

#define glBlendEquationSeparate		enGlBlendEquationSeparate	
#define glDrawBuffers				enGlDrawBuffers				
#define glStencilOpSeparate			enGlStencilOpSeparate		
#define glStencilFuncSeparate		enGlStencilFuncSeparate		
#define glStencilMaskSeparate		enGlStencilMaskSeparate		
#define glAttachShader				enGlAttachShader			
#define glBindAttribLocation		enGlBindAttribLocation		
#define glCompileShader				enGlCompileShader			
#define glCreateProgram				enGlCreateProgram			
#define glCreateShader				enGlCreateShader			
#define glDeleteProgram				enGlDeleteProgram			
#define glDeleteShader				enGlDeleteShader			
#define glDetachShader				enGlDetachShader			
#define glDisableVertexAttribArray	enGlDisableVertexAttribArray
#define glEnableVertexAttribArray	enGlEnableVertexAttribArray	
#define glGetActiveAttrib			enGlGetActiveAttrib			
#define glGetActiveUniform			enGlGetActiveUniform		
#define glGetAttachedShaders		enGlGetAttachedShaders		
#define glGetAttribLocation			enGlGetAttribLocation		
#define glGetProgramiv				enGlGetProgramiv			
#define glGetProgramInfoLog			enGlGetProgramInfoLog		
#define glGetShaderiv				enGlGetShaderiv				
#define glGetShaderInfoLog			enGlGetShaderInfoLog		
#define glGetShaderSource			enGlGetShaderSource			
#define glGetUniformLocation		enGlGetUniformLocation		
#define glGetUniformfv				enGlGetUniformfv			
#define glGetUniformiv				enGlGetUniformiv			
#define glGetVertexAttribdv			enGlGetVertexAttribdv		
#define glGetVertexAttribfv			enGlGetVertexAttribfv		
#define glGetVertexAttribiv			enGlGetVertexAttribiv		
#define glGetVertexAttribPointerv	enGlGetVertexAttribPointerv	
#define glIsProgram					enGlIsProgram				
#define glIsShader					enGlIsShader				
#define glLinkProgram				enGlLinkProgram				
#define glShaderSource				enGlShaderSource			
#define glUseProgram				enGlUseProgram				
#define glUniform1f					enGlUniform1f				
#define glUniform2f					enGlUniform2f				
#define glUniform3f					enGlUniform3f				
#define glUniform4f					enGlUniform4f				
#define glUniform1i					enGlUniform1i				
#define glUniform2i					enGlUniform2i				
#define glUniform3i					enGlUniform3i				
#define glUniform4i					enGlUniform4i				
#define glUniform1fv				enGlUniform1fv				
#define glUniform2fv				enGlUniform2fv				
#define glUniform3fv				enGlUniform3fv				
#define glUniform4fv				enGlUniform4fv				
#define glUniform1iv				enGlUniform1iv				
#define glUniform2iv				enGlUniform2iv				
#define glUniform3iv				enGlUniform3iv				
#define glUniform4iv				enGlUniform4iv				
#define glUniformMatrix2fv			enGlUniformMatrix2fv		
#define glUniformMatrix3fv			enGlUniformMatrix3fv		
#define glUniformMatrix4fv			enGlUniformMatrix4fv		
#define glValidateProgram			enGlValidateProgram			
#define glVertexAttrib1d			enGlVertexAttrib1d			
#define glVertexAttrib1dv			enGlVertexAttrib1dv			
#define glVertexAttrib1f			enGlVertexAttrib1f			
#define glVertexAttrib1fv			enGlVertexAttrib1fv			
#define glVertexAttrib1s			enGlVertexAttrib1s			
#define glVertexAttrib1sv			enGlVertexAttrib1sv			
#define glVertexAttrib2d			enGlVertexAttrib2d			
#define glVertexAttrib2dv			enGlVertexAttrib2dv			
#define glVertexAttrib2f			enGlVertexAttrib2f			
#define glVertexAttrib2fv			enGlVertexAttrib2fv			
#define glVertexAttrib2s			enGlVertexAttrib2s			
#define glVertexAttrib2sv			enGlVertexAttrib2sv			
#define glVertexAttrib3d			enGlVertexAttrib3d			
#define glVertexAttrib3dv			enGlVertexAttrib3dv			
#define glVertexAttrib3f			enGlVertexAttrib3f			
#define glVertexAttrib3fv			enGlVertexAttrib3fv			
#define glVertexAttrib3s			enGlVertexAttrib3s			
#define glVertexAttrib3sv			enGlVertexAttrib3sv			
#define glVertexAttrib4Nbv			enGlVertexAttrib4Nbv		
#define glVertexAttrib4Niv			enGlVertexAttrib4Niv		
#define glVertexAttrib4Nsv			enGlVertexAttrib4Nsv		
#define glVertexAttrib4Nub			enGlVertexAttrib4Nub		
#define glVertexAttrib4Nubv			enGlVertexAttrib4Nubv		
#define glVertexAttrib4Nuiv			enGlVertexAttrib4Nuiv		
#define glVertexAttrib4Nusv			enGlVertexAttrib4Nusv		
#define glVertexAttrib4bv			enGlVertexAttrib4bv			
#define glVertexAttrib4d			enGlVertexAttrib4d			
#define glVertexAttrib4dv			enGlVertexAttrib4dv			
#define glVertexAttrib4f			enGlVertexAttrib4f			
#define glVertexAttrib4fv			enGlVertexAttrib4fv			
#define glVertexAttrib4iv			enGlVertexAttrib4iv			
#define glVertexAttrib4s			enGlVertexAttrib4s			
#define glVertexAttrib4sv			enGlVertexAttrib4sv			
#define glVertexAttrib4ubv			enGlVertexAttrib4ubv		
#define glVertexAttrib4uiv			enGlVertexAttrib4uiv		
#define glVertexAttrib4usv			enGlVertexAttrib4usv		
#define glVertexAttribPointer		enGlVertexAttribPointer		

#endif