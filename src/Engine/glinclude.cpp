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

#include "glinclude.h"

#include "SDL_video.h"
#include "Profiler.h"

// ARB extensions
PFNGLQUERYCOUNTERPROC			enGlQueryCounter;
PFNGLGETQUERYOBJECTI64VPROC		enGlGetQueryObjecti64v;
PFNGLGETQUERYOBJECTUI64VPROC	enGlGetQueryObjectui64v;


// 1.3
PFNGLACTIVETEXTUREPROC		enGlActiveTexture;


// 1.5
PFNGLGENQUERIESPROC				enGlGenQueries;
PFNGLDELETEQUERIESPROC			enGlDeleteQueries;
PFNGLISQUERYPROC				enGlIsQuery;
PFNGLBEGINQUERYPROC				enGlBeginQuery;
PFNGLENDQUERYPROC				enGlEndQuery;
PFNGLGETQUERYIVPROC				enGlGetQueryiv;
PFNGLGETQUERYOBJECTIVPROC		enGlGetQueryObjectiv;
PFNGLGETQUERYOBJECTUIVPROC		enGlGetQueryObjectuiv;
PFNGLBINDBUFFERPROC				enGlBindBuffer;
PFNGLDELETEBUFFERSPROC			enGlDeleteBuffers;
PFNGLGENBUFFERSPROC				enGlGenBuffers;
PFNGLISBUFFERPROC				enGlIsBuffer;
PFNGLBUFFERDATAPROC				enGlBufferData;
PFNGLBUFFERSUBDATAPROC			enGlBufferSubData;
PFNGLGETBUFFERSUBDATAPROC		enGlGetBufferSubData;
PFNGLMAPBUFFERPROC				enGlMapBuffer;
PFNGLUNMAPBUFFERPROC			enGlUnmapBuffer;
PFNGLGETBUFFERPARAMETERIVPROC	enGlGetBufferParameteriv;
PFNGLGETBUFFERPOINTERVPROC		enGlGetBufferPointerv;


// 2.0
PFNGLBLENDEQUATIONSEPARATEPROC		enGlBlendEquationSeparate;
PFNGLDRAWBUFFERSPROC				enGlDrawBuffers;
PFNGLSTENCILOPSEPARATEPROC			enGlStencilOpSeparate;
PFNGLSTENCILFUNCSEPARATEPROC		enGlStencilFuncSeparate;
PFNGLSTENCILMASKSEPARATEPROC		enGlStencilMaskSeparate;
PFNGLATTACHSHADERPROC				enGlAttachShader;
PFNGLBINDATTRIBLOCATIONPROC			enGlBindAttribLocation;
PFNGLCOMPILESHADERPROC				enGlCompileShader;
PFNGLCREATEPROGRAMPROC				enGlCreateProgram;
PFNGLCREATESHADERPROC				enGlCreateShader;
PFNGLDELETEPROGRAMPROC				enGlDeleteProgram;
PFNGLDELETESHADERPROC				enGlDeleteShader;
PFNGLDETACHSHADERPROC				enGlDetachShader;
PFNGLDISABLEVERTEXATTRIBARRAYPROC	enGlDisableVertexAttribArray;
PFNGLENABLEVERTEXATTRIBARRAYPROC	enGlEnableVertexAttribArray;
PFNGLGETACTIVEATTRIBPROC			enGlGetActiveAttrib;
PFNGLGETACTIVEUNIFORMPROC			enGlGetActiveUniform;
PFNGLGETATTACHEDSHADERSPROC			enGlGetAttachedShaders;
PFNGLGETATTRIBLOCATIONPROC			enGlGetAttribLocation;
PFNGLGETPROGRAMIVPROC				enGlGetProgramiv;
PFNGLGETPROGRAMINFOLOGPROC			enGlGetProgramInfoLog;
PFNGLGETSHADERIVPROC				enGlGetShaderiv;
PFNGLGETSHADERINFOLOGPROC			enGlGetShaderInfoLog;
PFNGLGETSHADERSOURCEPROC			enGlGetShaderSource;
PFNGLGETUNIFORMLOCATIONPROC			enGlGetUniformLocation;
PFNGLGETUNIFORMFVPROC				enGlGetUniformfv;
PFNGLGETUNIFORMIVPROC				enGlGetUniformiv;
PFNGLGETVERTEXATTRIBDVPROC			enGlGetVertexAttribdv;
PFNGLGETVERTEXATTRIBFVPROC			enGlGetVertexAttribfv;
PFNGLGETVERTEXATTRIBIVPROC			enGlGetVertexAttribiv;
PFNGLGETVERTEXATTRIBPOINTERVPROC	enGlGetVertexAttribPointerv;
PFNGLISPROGRAMPROC					enGlIsProgram;
PFNGLISSHADERPROC					enGlIsShader;
PFNGLLINKPROGRAMPROC				enGlLinkProgram;
PFNGLSHADERSOURCEPROC				enGlShaderSource;
PFNGLUSEPROGRAMPROC					enGlUseProgram;
PFNGLUNIFORM1FPROC					enGlUniform1f;
PFNGLUNIFORM2FPROC					enGlUniform2f;
PFNGLUNIFORM3FPROC					enGlUniform3f;
PFNGLUNIFORM4FPROC					enGlUniform4f;
PFNGLUNIFORM1IPROC					enGlUniform1i;
PFNGLUNIFORM2IPROC					enGlUniform2i;
PFNGLUNIFORM3IPROC					enGlUniform3i;
PFNGLUNIFORM4IPROC					enGlUniform4i;
PFNGLUNIFORM1FVPROC					enGlUniform1fv;
PFNGLUNIFORM2FVPROC					enGlUniform2fv;
PFNGLUNIFORM3FVPROC					enGlUniform3fv;
PFNGLUNIFORM4FVPROC					enGlUniform4fv;
PFNGLUNIFORM1IVPROC					enGlUniform1iv;
PFNGLUNIFORM2IVPROC					enGlUniform2iv;
PFNGLUNIFORM3IVPROC					enGlUniform3iv;
PFNGLUNIFORM4IVPROC					enGlUniform4iv;
PFNGLUNIFORMMATRIX2FVPROC			enGlUniformMatrix2fv;
PFNGLUNIFORMMATRIX3FVPROC			enGlUniformMatrix3fv;
PFNGLUNIFORMMATRIX4FVPROC			enGlUniformMatrix4fv;
PFNGLVALIDATEPROGRAMPROC			enGlValidateProgram;
PFNGLVERTEXATTRIB1DPROC				enGlVertexAttrib1d;
PFNGLVERTEXATTRIB1DVPROC			enGlVertexAttrib1dv;
PFNGLVERTEXATTRIB1FPROC				enGlVertexAttrib1f;
PFNGLVERTEXATTRIB1FVPROC			enGlVertexAttrib1fv;
PFNGLVERTEXATTRIB1SPROC				enGlVertexAttrib1s;
PFNGLVERTEXATTRIB1SVPROC			enGlVertexAttrib1sv;
PFNGLVERTEXATTRIB2DPROC				enGlVertexAttrib2d;
PFNGLVERTEXATTRIB2DVPROC			enGlVertexAttrib2dv;
PFNGLVERTEXATTRIB2FPROC				enGlVertexAttrib2f;
PFNGLVERTEXATTRIB2FVPROC			enGlVertexAttrib2fv;
PFNGLVERTEXATTRIB2SPROC				enGlVertexAttrib2s;
PFNGLVERTEXATTRIB2SVPROC			enGlVertexAttrib2sv;
PFNGLVERTEXATTRIB3DPROC				enGlVertexAttrib3d;
PFNGLVERTEXATTRIB3DVPROC			enGlVertexAttrib3dv;
PFNGLVERTEXATTRIB3FPROC				enGlVertexAttrib3f;
PFNGLVERTEXATTRIB3FVPROC			enGlVertexAttrib3fv;
PFNGLVERTEXATTRIB3SPROC				enGlVertexAttrib3s;
PFNGLVERTEXATTRIB3SVPROC			enGlVertexAttrib3sv;
PFNGLVERTEXATTRIB4NBVPROC			enGlVertexAttrib4Nbv;
PFNGLVERTEXATTRIB4NIVPROC			enGlVertexAttrib4Niv;
PFNGLVERTEXATTRIB4NSVPROC			enGlVertexAttrib4Nsv;
PFNGLVERTEXATTRIB4NUBPROC			enGlVertexAttrib4Nub;
PFNGLVERTEXATTRIB4NUBVPROC			enGlVertexAttrib4Nubv;
PFNGLVERTEXATTRIB4NUIVPROC			enGlVertexAttrib4Nuiv;
PFNGLVERTEXATTRIB4NUSVPROC			enGlVertexAttrib4Nusv;
PFNGLVERTEXATTRIB4BVPROC			enGlVertexAttrib4bv;
PFNGLVERTEXATTRIB4DPROC				enGlVertexAttrib4d;
PFNGLVERTEXATTRIB4DVPROC			enGlVertexAttrib4dv;
PFNGLVERTEXATTRIB4FPROC				enGlVertexAttrib4f;
PFNGLVERTEXATTRIB4FVPROC			enGlVertexAttrib4fv;
PFNGLVERTEXATTRIB4IVPROC			enGlVertexAttrib4iv;
PFNGLVERTEXATTRIB4SPROC				enGlVertexAttrib4s;
PFNGLVERTEXATTRIB4SVPROC			enGlVertexAttrib4sv;
PFNGLVERTEXATTRIB4UBVPROC			enGlVertexAttrib4ubv;
PFNGLVERTEXATTRIB4UIVPROC			enGlVertexAttrib4uiv;
PFNGLVERTEXATTRIB4USVPROC			enGlVertexAttrib4usv;
PFNGLVERTEXATTRIBPOINTERPROC		enGlVertexAttribPointer;

void *EnOpenGLGetProc(const char *proc)
{
	void *ptr = SDL_GL_GetProcAddress(proc);

	if (!ptr)
		ELOG("Bad address for: %s\n", proc);

	return ptr;
}

void InitializeGL()
{
	static bool initialized = false;
	EN_ASSERT(initialized == 0);

	// Initialize all functions
	
	// ARB extensions
	enGlQueryCounter = (PFNGLQUERYCOUNTERPROC)EnOpenGLGetProc("glQueryCounter");
	enGlGetQueryObjecti64v = (PFNGLGETQUERYOBJECTI64VPROC)EnOpenGLGetProc("glGetQueryObjecti64v");
	enGlGetQueryObjectui64v = (PFNGLGETQUERYOBJECTUI64VPROC)EnOpenGLGetProc("glGetQueryObjectui64v");


	// 1.3
	enGlActiveTexture = (PFNGLACTIVETEXTUREPROC)EnOpenGLGetProc("glActiveTexture");

	
	// 1.5
	enGlGenQueries = (PFNGLGENQUERIESPROC)EnOpenGLGetProc("glGenQueries");
	enGlDeleteQueries = (PFNGLDELETEQUERIESPROC)EnOpenGLGetProc("glDeleteQueries");
	enGlIsQuery	= (PFNGLISQUERYPROC)EnOpenGLGetProc("glIsQuery");
	enGlBeginQuery = (PFNGLBEGINQUERYPROC)EnOpenGLGetProc("glBeginQuery");
	enGlEndQuery = (PFNGLENDQUERYPROC)EnOpenGLGetProc("glEndQuery");
	enGlGetQueryiv = (PFNGLGETQUERYIVPROC)EnOpenGLGetProc("glGetQueryiv");
	enGlGetQueryObjectiv = (PFNGLGETQUERYOBJECTIVPROC)EnOpenGLGetProc("glGetQueryObjectiv");
	enGlGetQueryObjectuiv = (PFNGLGETQUERYOBJECTUIVPROC)EnOpenGLGetProc("glGetQueryObjectuiv");
	enGlBindBuffer = (PFNGLBINDBUFFERPROC)EnOpenGLGetProc("glBindBuffer");
	enGlDeleteBuffers = (PFNGLDELETEBUFFERSPROC)EnOpenGLGetProc("glDeleteBuffers");
	enGlGenBuffers = (PFNGLGENBUFFERSPROC)EnOpenGLGetProc("glGenBuffers");
	enGlIsBuffer = (PFNGLISBUFFERPROC)EnOpenGLGetProc("glIsBuffer");
	enGlBufferData = (PFNGLBUFFERDATAPROC)EnOpenGLGetProc("glBufferData");
	enGlBufferSubData = (PFNGLBUFFERSUBDATAPROC)EnOpenGLGetProc("glBufferSubData");
	enGlGetBufferSubData = (PFNGLGETBUFFERSUBDATAPROC)EnOpenGLGetProc("glGetBufferSubData");
	enGlMapBuffer = (PFNGLMAPBUFFERPROC)EnOpenGLGetProc("glMapBuffer");
	enGlUnmapBuffer = (PFNGLUNMAPBUFFERPROC)EnOpenGLGetProc("glUnmapBuffer");
	enGlGetBufferParameteriv = (PFNGLGETBUFFERPARAMETERIVPROC)EnOpenGLGetProc("glGetBufferParameteriv");
	enGlGetBufferPointerv = (PFNGLGETBUFFERPOINTERVPROC)EnOpenGLGetProc("glGetBufferPointerv");


	// 2.0
	enGlBlendEquationSeparate = (PFNGLBLENDEQUATIONSEPARATEPROC)EnOpenGLGetProc("glBlendEquationSeparate");
	enGlDrawBuffers = (PFNGLDRAWBUFFERSPROC)EnOpenGLGetProc("glDrawBuffers");
	enGlStencilOpSeparate = (PFNGLSTENCILOPSEPARATEPROC)EnOpenGLGetProc("glStencilOpSeparate");
	enGlStencilFuncSeparate = (PFNGLSTENCILFUNCSEPARATEPROC)EnOpenGLGetProc("glStencilFuncSeparate");
	enGlStencilMaskSeparate = (PFNGLSTENCILMASKSEPARATEPROC)EnOpenGLGetProc("glStencilMaskSeparate");
	enGlAttachShader = (PFNGLATTACHSHADERPROC)EnOpenGLGetProc("glAttachShader");
	enGlBindAttribLocation = (PFNGLBINDATTRIBLOCATIONPROC)EnOpenGLGetProc("glBindAttribLocation");
	enGlCompileShader = (PFNGLCOMPILESHADERPROC)EnOpenGLGetProc("glCompileShader");
	enGlCreateProgram = (PFNGLCREATEPROGRAMPROC)EnOpenGLGetProc("glCreateProgram");
	enGlCreateShader = (PFNGLCREATESHADERPROC)EnOpenGLGetProc("glCreateShader");
	enGlDeleteProgram = (PFNGLDELETEPROGRAMPROC)EnOpenGLGetProc("glDeleteProgram");
	enGlDeleteShader = (PFNGLDELETESHADERPROC)EnOpenGLGetProc("glDeleteShader");
	enGlDetachShader = (PFNGLDETACHSHADERPROC)EnOpenGLGetProc("glDetachShader");
	enGlDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)EnOpenGLGetProc("glDisableVertexAttribArray");
	enGlEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)EnOpenGLGetProc("glEnableVertexAttribArray");
	enGlGetActiveAttrib = (PFNGLGETACTIVEATTRIBPROC)EnOpenGLGetProc("glGetActiveAttrib");
	enGlGetActiveUniform = (PFNGLGETACTIVEUNIFORMPROC)EnOpenGLGetProc("glGetActiveUniform");
	enGlGetAttachedShaders = (PFNGLGETATTACHEDSHADERSPROC)EnOpenGLGetProc("glGetAttachedShaders");
	enGlGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC)EnOpenGLGetProc("glGetAttribLocation");
	enGlGetProgramiv = (PFNGLGETPROGRAMIVPROC)EnOpenGLGetProc("glGetProgramiv");
	enGlGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)EnOpenGLGetProc("glGetProgramInfoLog");
	enGlGetShaderiv = (PFNGLGETSHADERIVPROC)EnOpenGLGetProc("glGetShaderiv");
	enGlGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)EnOpenGLGetProc("glGetShaderInfoLog");
	enGlGetShaderSource = (PFNGLGETSHADERSOURCEPROC)EnOpenGLGetProc("glGetShaderSource");
	enGlGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)EnOpenGLGetProc("glGetUniformLocation");
	enGlGetUniformfv = (PFNGLGETUNIFORMFVPROC)EnOpenGLGetProc("glGetUniformfv");
	enGlGetUniformiv = (PFNGLGETUNIFORMIVPROC)EnOpenGLGetProc("glGetUniformiv");
	enGlGetVertexAttribdv = (PFNGLGETVERTEXATTRIBDVPROC)EnOpenGLGetProc("glGetVertexAttribdv");
	enGlGetVertexAttribfv = (PFNGLGETVERTEXATTRIBFVPROC)EnOpenGLGetProc("glGetVertexAttribfv");
	enGlGetVertexAttribiv = (PFNGLGETVERTEXATTRIBIVPROC)EnOpenGLGetProc("glGetVertexAttribiv");
	enGlGetVertexAttribPointerv = (PFNGLGETVERTEXATTRIBPOINTERVPROC)EnOpenGLGetProc("glGetVertexAttribPointerv");
	enGlIsProgram = (PFNGLISPROGRAMPROC)EnOpenGLGetProc("glIsProgram");
	enGlIsShader = (PFNGLISSHADERPROC)EnOpenGLGetProc("glIsShader");
	enGlLinkProgram = (PFNGLLINKPROGRAMPROC)EnOpenGLGetProc("glLinkProgram");
	enGlShaderSource = (PFNGLSHADERSOURCEPROC)EnOpenGLGetProc("glShaderSource");
	enGlUseProgram = (PFNGLUSEPROGRAMPROC)EnOpenGLGetProc("glUseProgram");
	enGlUniform1f = (PFNGLUNIFORM1FPROC)EnOpenGLGetProc("glUniform1f");
	enGlUniform2f = (PFNGLUNIFORM2FPROC)EnOpenGLGetProc("glUniform2f");
	enGlUniform3f = (PFNGLUNIFORM3FPROC)EnOpenGLGetProc("glUniform3f");
	enGlUniform4f = (PFNGLUNIFORM4FPROC)EnOpenGLGetProc("glUniform4f");
	enGlUniform1i = (PFNGLUNIFORM1IPROC)EnOpenGLGetProc("glUniform1i");
	enGlUniform2i = (PFNGLUNIFORM2IPROC)EnOpenGLGetProc("glUniform2i");
	enGlUniform3i = (PFNGLUNIFORM3IPROC)EnOpenGLGetProc("glUniform3i");
	enGlUniform4i = (PFNGLUNIFORM4IPROC)EnOpenGLGetProc("glUniform4i");
	enGlUniform1fv = (PFNGLUNIFORM1FVPROC)EnOpenGLGetProc("glUniform1fv");
	enGlUniform2fv = (PFNGLUNIFORM2FVPROC)EnOpenGLGetProc("glUniform2fv");
	enGlUniform3fv = (PFNGLUNIFORM3FVPROC)EnOpenGLGetProc("glUniform3fv");
	enGlUniform4fv = (PFNGLUNIFORM4FVPROC)EnOpenGLGetProc("glUniform4fv");
	enGlUniform1iv = (PFNGLUNIFORM1IVPROC)EnOpenGLGetProc("glUniform1iv");
	enGlUniform2iv = (PFNGLUNIFORM2IVPROC)EnOpenGLGetProc("glUniform2iv");
	enGlUniform3iv = (PFNGLUNIFORM3IVPROC)EnOpenGLGetProc("glUniform3iv");
	enGlUniform4iv = (PFNGLUNIFORM4IVPROC)EnOpenGLGetProc("glUniform4iv");
	enGlUniformMatrix2fv = (PFNGLUNIFORMMATRIX2FVPROC)EnOpenGLGetProc("glUniformMatrix2fv");
	enGlUniformMatrix3fv = (PFNGLUNIFORMMATRIX3FVPROC)EnOpenGLGetProc("glUniformMatrix3fv");
	enGlUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)EnOpenGLGetProc("glUniformMatrix4fv");
	enGlValidateProgram = (PFNGLVALIDATEPROGRAMPROC)EnOpenGLGetProc("glValidateProgram");
	enGlVertexAttrib1d = (PFNGLVERTEXATTRIB1DPROC)EnOpenGLGetProc("glVertexAttrib1d");
	enGlVertexAttrib1dv = (PFNGLVERTEXATTRIB1DVPROC)EnOpenGLGetProc("glVertexAttrib1dv");
	enGlVertexAttrib1f = (PFNGLVERTEXATTRIB1FPROC)EnOpenGLGetProc("glVertexAttrib1f");
	enGlVertexAttrib1fv = (PFNGLVERTEXATTRIB1FVPROC)EnOpenGLGetProc("glVertexAttrib1fv");
	enGlVertexAttrib1s = (PFNGLVERTEXATTRIB1SPROC)EnOpenGLGetProc("glVertexAttrib1s");
	enGlVertexAttrib1sv = (PFNGLVERTEXATTRIB1SVPROC)EnOpenGLGetProc("glVertexAttrib1sv");
	enGlVertexAttrib2d = (PFNGLVERTEXATTRIB2DPROC)EnOpenGLGetProc("glVertexAttrib2d");
	enGlVertexAttrib2dv = (PFNGLVERTEXATTRIB2DVPROC)EnOpenGLGetProc("glVertexAttrib2dv");
	enGlVertexAttrib2f = (PFNGLVERTEXATTRIB2FPROC)EnOpenGLGetProc("glVertexAttrib2f");
	enGlVertexAttrib2fv = (PFNGLVERTEXATTRIB2FVPROC)EnOpenGLGetProc("glVertexAttrib2fv");
	enGlVertexAttrib2s = (PFNGLVERTEXATTRIB2SPROC)EnOpenGLGetProc("glVertexAttrib2s");
	enGlVertexAttrib2sv = (PFNGLVERTEXATTRIB2SVPROC)EnOpenGLGetProc("glVertexAttrib2sv");
	enGlVertexAttrib3d = (PFNGLVERTEXATTRIB3DPROC)EnOpenGLGetProc("glVertexAttrib3d");
	enGlVertexAttrib3dv = (PFNGLVERTEXATTRIB3DVPROC)EnOpenGLGetProc("glVertexAttrib3dv");
	enGlVertexAttrib3f = (PFNGLVERTEXATTRIB3FPROC)EnOpenGLGetProc("glVertexAttrib3f");
	enGlVertexAttrib3fv = (PFNGLVERTEXATTRIB3FVPROC)EnOpenGLGetProc("glVertexAttrib3fv");
	enGlVertexAttrib3s = (PFNGLVERTEXATTRIB3SPROC)EnOpenGLGetProc("glVertexAttrib3s");
	enGlVertexAttrib3sv = (PFNGLVERTEXATTRIB3SVPROC)EnOpenGLGetProc("glVertexAttrib3sv");
	enGlVertexAttrib4Nbv = (PFNGLVERTEXATTRIB4NBVPROC)EnOpenGLGetProc("glVertexAttrib4Nbv");
	enGlVertexAttrib4Niv = (PFNGLVERTEXATTRIB4NIVPROC)EnOpenGLGetProc("glVertexAttrib4Niv");
	enGlVertexAttrib4Nsv = (PFNGLVERTEXATTRIB4NSVPROC)EnOpenGLGetProc("glVertexAttrib4Nsv");
	enGlVertexAttrib4Nub = (PFNGLVERTEXATTRIB4NUBPROC)EnOpenGLGetProc("glVertexAttrib4Nub");
	enGlVertexAttrib4Nubv = (PFNGLVERTEXATTRIB4NUBVPROC)EnOpenGLGetProc("glVertexAttrib4Nubv");
	enGlVertexAttrib4Nuiv = (PFNGLVERTEXATTRIB4NUIVPROC)EnOpenGLGetProc("glVertexAttrib4Nuiv");
	enGlVertexAttrib4Nusv = (PFNGLVERTEXATTRIB4NUSVPROC)EnOpenGLGetProc("glVertexAttrib4Nusv");
	enGlVertexAttrib4bv = (PFNGLVERTEXATTRIB4BVPROC)EnOpenGLGetProc("glVertexAttrib4bv");
	enGlVertexAttrib4d = (PFNGLVERTEXATTRIB4DPROC)EnOpenGLGetProc("glVertexAttrib4d");
	enGlVertexAttrib4dv = (PFNGLVERTEXATTRIB4DVPROC)EnOpenGLGetProc("glVertexAttrib4dv");
	enGlVertexAttrib4f = (PFNGLVERTEXATTRIB4FPROC)EnOpenGLGetProc("glVertexAttrib4f");
	enGlVertexAttrib4fv = (PFNGLVERTEXATTRIB4FVPROC)EnOpenGLGetProc("glVertexAttrib4fv");
	enGlVertexAttrib4iv = (PFNGLVERTEXATTRIB4IVPROC)EnOpenGLGetProc("glVertexAttrib4iv");
	enGlVertexAttrib4s = (PFNGLVERTEXATTRIB4SPROC)EnOpenGLGetProc("glVertexAttrib4s");
	enGlVertexAttrib4sv = (PFNGLVERTEXATTRIB4SVPROC)EnOpenGLGetProc("glVertexAttrib4sv");
	enGlVertexAttrib4ubv = (PFNGLVERTEXATTRIB4UBVPROC)EnOpenGLGetProc("glVertexAttrib4ubv");
	enGlVertexAttrib4uiv = (PFNGLVERTEXATTRIB4UIVPROC)EnOpenGLGetProc("glVertexAttrib4uiv");
	enGlVertexAttrib4usv = (PFNGLVERTEXATTRIB4USVPROC)EnOpenGLGetProc("glVertexAttrib4usv");
	enGlVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)EnOpenGLGetProc("glVertexAttribPointer");

	initialized = true;
}