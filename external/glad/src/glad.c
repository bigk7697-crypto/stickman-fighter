/*
    GLAD OpenGL Loader
    Generated for OpenGL 3.3 Core
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glad/glad.h>

#ifndef GLAD_IMPL_UTIL_C_
#define GLAD_IMPL_UTIL_C_

#ifdef _MSC_VER
#define GLAD_IMPL_UTIL_SSCANF sscanf_s
#else
#define GLAD_IMPL_UTIL_SSCANF sscanf
#endif

#endif /* GLAD_IMPL_UTIL_C_ */

#ifdef __cplusplus
extern "C" {
#endif

static void* glad_get_proc_address_impl(const char *name);

int gladLoadGLLoader(GLADloadproc load) {
    if (load == NULL) return 0;
    glad_get_proc_address_impl = load;
    return gladLoadGL();
}

/* This is a replacement for glGetString, which can be NULL on some GL implementations */
#ifndef GLAD_IMPL_GL_GET_STRING
#define GLAD_IMPL_GL_GET_STRING
static const char *glad_glGetString(GLenum name);
#endif

struct gladGLversionStruct {
    int major;
    int minor;
};

/* OpenGL 1.0 function pointers */
PFNGLCULLFACEPROC glad_glCullFace = NULL;
PFNGLFRONTFACEPROC glad_glFrontFace = NULL;
PFNGLHINTPROC glad_glHint = NULL;
PFNGLLINEWIDTHPROC glad_glLineWidth = NULL;
PFNGLPOINTSIZEPROC glad_glPointSize = NULL;
PFNGLPOLYGONMODEPROC glad_glPolygonMode = NULL;
PFNGLSCISSORPROC glad_glScissor = NULL;
PFNGLTEXPARAMETERFPROC glad_glTexParameterf = NULL;
PFNGLTEXPARAMETERFVPROC glad_glTexParameterfv = NULL;
PFNGLTEXPARAMETERIPROC glad_glTexParameteri = NULL;
PFNGLTEXPARAMETERIVPROC glad_glTexParameteriv = NULL;
PFNGLTEXIMAGE1DPROC glad_glTexImage1D = NULL;
PFNGLTEXIMAGE2DPROC glad_glTexImage2D = NULL;
PFNGLDRAWBUFFERPROC glad_glDrawBuffer = NULL;
PFNGLCLEARPROC glad_glClear = NULL;
PFNGLCLEARCOLORPROC glad_glClearColor = NULL;
PFNGLCLEARSTENCILPROC glad_glClearStencil = NULL;
PFNGLCLEARDEPTHPROC glad_glClearDepth = NULL;
PFNGLSTENCILMASKPROC glad_glStencilMask = NULL;
PFNGLSTENCILFUNCPROC glad_glStencilFunc = NULL;
PFNGLSTENCILOPPROC glad_glStencilOp = NULL;
PFNGLDEPTHMASKPROC glad_glDepthMask = NULL;
PFNGLDEPTHFUNCPROC glad_glDepthFunc = NULL;
PFNGLVIEWPORTPROC glad_glViewport = NULL;
PFNGLBLENDFUNCPROC glad_glBlendFunc = NULL;
PFNGLBLENDFUNCSEPARATEPROC glad_glBlendFuncSeparate = NULL;
PFNGLBLENDEQUATIONPROC glad_glBlendEquation = NULL;
PFNGLENABLEPROC glad_glEnable = NULL;
PFNGLDISABLEPROC glad_glDisable = NULL;
PFNGLISENABLEDPROC glad_glIsEnabled = NULL;
PFNGLGETERRORPROC glad_glGetError = NULL;
PFNGLGETSTRINGPROC glad_glGetString = NULL;
PFNGLGETINTEGERVPROC glad_glGetIntegerv = NULL;
PFNGLGETFLOATVPROC glad_glGetFloatv = NULL;
PFNGLGETBOOLEANVPROC glad_glGetBooleanv = NULL;

/* OpenGL 1.5+ function pointers */
PFNGLBINDBUFFERPROC glad_glBindBuffer = NULL;
PFNGLDELETEBUFFERSPROC glad_glDeleteBuffers = NULL;
PFNGLGENBUFFERSPROC glad_glGenBuffers = NULL;
PFNGLBUFFERDATAPROC glad_glBufferData = NULL;
PFNGLBUFFERSUBDATAPROC glad_glBufferSubData = NULL;
PFNGLGETBUFFERPARAMETERIVPROC glad_glGetBufferParameteriv = NULL;
PFNGLMAPBUFFERPROC glad_glMapBuffer = NULL;
PFNGLUNMAPBUFFERPROC glad_glUnmapBuffer = NULL;

/* Shader function pointers */
PFNGLCREATESHADERPROC glad_glCreateShader = NULL;
PFNGLSHADERSOURCEPROC glad_glShaderSource = NULL;
PFNGLCOMPILESHADERPROC glad_glCompileShader = NULL;
PFNGLGETSHADERIVPROC glad_glGetShaderiv = NULL;
PFNGLGETSHADERINFOLOGPROC glad_glGetShaderInfoLog = NULL;
PFNGLDELETESHADERPROC glad_glDeleteShader = NULL;
PFNGLCREATEPROGRAMPROC glad_glCreateProgram = NULL;
PFNGLATTACHSHADERPROC glad_glAttachShader = NULL;
PFNGLLINKPROGRAMPROC glad_glLinkProgram = NULL;
PFNGLVALIDATEPROGRAMPROC glad_glValidateProgram = NULL;
PFNGLUSEPROGRAMPROC glad_glUseProgram = NULL;
PFNGLDELETEPROGRAMPROC glad_glDeleteProgram = NULL;
PFNGLGETPROGRAMIVPROC glad_glGetProgramiv = NULL;
PFNGLGETPROGRAMINFOLOGPROC glad_glGetProgramInfoLog = NULL;
PFNGLGETUNIFORMLOCATIONPROC glad_glGetUniformLocation = NULL;
PFNGLUNIFORM1FPROC glad_glUniform1f = NULL;
PFNGLUNIFORM2FPROC glad_glUniform2f = NULL;
PFNGLUNIFORM3FPROC glad_glUniform3f = NULL;
PFNGLUNIFORM4FPROC glad_glUniform4f = NULL;
PFNGLUNIFORM1IPROC glad_glUniform1i = NULL;
PFNGLUNIFORM2IPROC glad_glUniform2i = NULL;
PFNGLUNIFORM3IPROC glad_glUniform3i = NULL;
PFNGLUNIFORM4IPROC glad_glUniform4i = NULL;
PFNGLUNIFORMMATRIX2FVPROC glad_glUniformMatrix2fv = NULL;
PFNGLUNIFORMMATRIX3FVPROC glad_glUniformMatrix3fv = NULL;
PFNGLUNIFORMMATRIX4FVPROC glad_glUniformMatrix4fv = NULL;

/* VAO function pointers */
PFNGLGENVERTEXARRAYSPROC glad_glGenVertexArrays = NULL;
PFNGLBINDVERTEXARRAYPROC glad_glBindVertexArray = NULL;
PFNGLDELETEVERTEXARRAYSPROC glad_glDeleteVertexArrays = NULL;
PFNGLENABLEVERTEXATTRIBARRAYPROC glad_glEnableVertexAttribArray = NULL;
PFNGLDISABLEVERTEXATTRIBARRAYPROC glad_glDisableVertexAttribArray = NULL;
PFNGLVERTEXATTRIBPOINTERPROC glad_glVertexAttribPointer = NULL;
PFNGLBINDATTRIBLOCATIONPROC glad_glBindAttribLocation = NULL;
PFNGLGETATTRIBLOCATIONPROC glad_glGetAttribLocation = NULL;

/* Drawing function pointers */
PFNGLDRAWARRAYSPROC glad_glDrawArrays = NULL;
PFNGLDRAWELEMENTSPROC glad_glDrawElements = NULL;
PFNGLACTIVETEXTUREPROC glad_glActiveTexture = NULL;
PFNGLGETSTRINGIPROC glad_glGetStringi = NULL;
PFNGLCLEARBUFFERFVPROC glad_glClearBufferfv = NULL;
PFNGLCLEARBUFFERIVPROC glad_glClearBufferiv = NULL;
PFNGLCLEARBUFFERUIVPROC glad_glClearBufferuiv = NULL;
PFNGLCLEARBUFFERFIPROC glad_glClearBufferfi = NULL;

static void* glad_get_proc_address_impl(const char *name) {
    return NULL;
}

static GLADloadproc gladLoadProc = NULL;

static void* glad_get_proc(const char *name) {
    if (gladLoadProc == NULL) return NULL;
    return gladLoadProc(name);
}

int gladLoadGLLoader(GLADloadproc load) {
    gladLoadProc = load;
    if (load == NULL) return 0;
    
    /* Load OpenGL 1.0 functions */
    glad_glCullFace = (PFNGLCULLFACEPROC)glad_get_proc("glCullFace");
    glad_glFrontFace = (PFNGLFRONTFACEPROC)glad_get_proc("glFrontFace");
    glad_glHint = (PFNGLHINTPROC)glad_get_proc("glHint");
    glad_glLineWidth = (PFNGLLINEWIDTHPROC)glad_get_proc("glLineWidth");
    glad_glPointSize = (PFNGLPOINTSIZEPROC)glad_get_proc("glPointSize");
    glad_glPolygonMode = (PFNGLPOLYGONMODEPROC)glad_get_proc("glPolygonMode");
    glad_glScissor = (PFNGLSCISSORPROC)glad_get_proc("glScissor");
    glad_glTexParameterf = (PFNGLTEXPARAMETERFPROC)glad_get_proc("glTexParameterf");
    glad_glTexParameterfv = (PFNGLTEXPARAMETERFVPROC)glad_get_proc("glTexParameterfv");
    glad_glTexParameteri = (PFNGLTEXPARAMETERIPROC)glad_get_proc("glTexParameteri");
    glad_glTexParameteriv = (PFNGLTEXPARAMETERIVPROC)glad_get_proc("glTexParameteriv");
    glad_glTexImage1D = (PFNGLTEXIMAGE1DPROC)glad_get_proc("glTexImage1D");
    glad_glTexImage2D = (PFNGLTEXIMAGE2DPROC)glad_get_proc("glTexImage2D");
    glad_glDrawBuffer = (PFNGLDRAWBUFFERPROC)glad_get_proc("glDrawBuffer");
    glad_glClear = (PFNGLCLEARPROC)glad_get_proc("glClear");
    glad_glClearColor = (PFNGLCLEARCOLORPROC)glad_get_proc("glClearColor");
    glad_glClearStencil = (PFNGLCLEARSTENCILPROC)glad_get_proc("glClearStencil");
    glad_glClearDepth = (PFNGLCLEARDEPTHPROC)glad_get_proc("glClearDepth");
    glad_glStencilMask = (PFNGLSTENCILMASKPROC)glad_get_proc("glStencilMask");
    glad_glStencilFunc = (PFNGLSTENCILFUNCPROC)glad_get_proc("glStencilFunc");
    glad_glStencilOp = (PFNGLSTENCILOPPROC)glad_get_proc("glStencilOp");
    glad_glDepthMask = (PFNGLDEPTHMASKPROC)glad_get_proc("glDepthMask");
    glad_glDepthFunc = (PFNGLDEPTHFUNCPROC)glad_get_proc("glDepthFunc");
    glad_glViewport = (PFNGLVIEWPORTPROC)glad_get_proc("glViewport");
    glad_glBlendFunc = (PFNGLBLENDFUNCPROC)glad_get_proc("glBlendFunc");
    glad_glBlendFuncSeparate = (PFNGLBLENDFUNCSEPARATEPROC)glad_get_proc("glBlendFuncSeparate");
    glad_glBlendEquation = (PFNGLBLENDEQUATIONPROC)glad_get_proc("glBlendEquation");
    glad_glEnable = (PFNGLENABLEPROC)glad_get_proc("glEnable");
    glad_glDisable = (PFNGLDISABLEPROC)glad_get_proc("glDisable");
    glad_glIsEnabled = (PFNGLISENABLEDPROC)glad_get_proc("glIsEnabled");
    glad_glGetError = (PFNGLGETERRORPROC)glad_get_proc("glGetError");
    glad_glGetString = (PFNGLGETSTRINGPROC)glad_get_proc("glGetString");
    glad_glGetIntegerv = (PFNGLGETINTEGERVPROC)glad_get_proc("glGetIntegerv");
    glad_glGetFloatv = (PFNGLGETFLOATVPROC)glad_get_proc("glGetFloatv");
    glad_glGetBooleanv = (PFNGLGETBOOLEANVPROC)glad_get_proc("glGetBooleanv");
    
    /* Load OpenGL 1.5+ buffer functions */
    glad_glBindBuffer = (PFNGLBINDBUFFERPROC)glad_get_proc("glBindBuffer");
    glad_glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)glad_get_proc("glDeleteBuffers");
    glad_glGenBuffers = (PFNGLGENBUFFERSPROC)glad_get_proc("glGenBuffers");
    glad_glBufferData = (PFNGLBUFFERDATAPROC)glad_get_proc("glBufferData");
    glad_glBufferSubData = (PFNGLBUFFERSUBDATAPROC)glad_get_proc("glBufferSubData");
    glad_glGetBufferParameteriv = (PFNGLGETBUFFERPARAMETERIVPROC)glad_get_proc("glGetBufferParameteriv");
    glad_glMapBuffer = (PFNGLMAPBUFFERPROC)glad_get_proc("glMapBuffer");
    glad_glUnmapBuffer = (PFNGLUNMAPBUFFERPROC)glad_get_proc("glUnmapBuffer");
    
    /* Load shader functions */
    glad_glCreateShader = (PFNGLCREATESHADERPROC)glad_get_proc("glCreateShader");
    glad_glShaderSource = (PFNGLSHADERSOURCEPROC)glad_get_proc("glShaderSource");
    glad_glCompileShader = (PFNGLCOMPILESHADERPROC)glad_get_proc("glCompileShader");
    glad_glGetShaderiv = (PFNGLGETSHADERIVPROC)glad_get_proc("glGetShaderiv");
    glad_glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)glad_get_proc("glGetShaderInfoLog");
    glad_glDeleteShader = (PFNGLDELETESHADERPROC)glad_get_proc("glDeleteShader");
    glad_glCreateProgram = (PFNGLCREATEPROGRAMPROC)glad_get_proc("glCreateProgram");
    glad_glAttachShader = (PFNGLATTACHSHADERPROC)glad_get_proc("glAttachShader");
    glad_glLinkProgram = (PFNGLLINKPROGRAMPROC)glad_get_proc("glLinkProgram");
    glad_glValidateProgram = (PFNGLVALIDATEPROGRAMPROC)glad_get_proc("glValidateProgram");
    glad_glUseProgram = (PFNGLUSEPROGRAMPROC)glad_get_proc("glUseProgram");
    glad_glDeleteProgram = (PFNGLDELETEPROGRAMPROC)glad_get_proc("glDeleteProgram");
    glad_glGetProgramiv = (PFNGLGETPROGRAMIVPROC)glad_get_proc("glGetProgramiv");
    glad_glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)glad_get_proc("glGetProgramInfoLog");
    glad_glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)glad_get_proc("glGetUniformLocation");
    glad_glUniform1f = (PFNGLUNIFORM1FPROC)glad_get_proc("glUniform1f");
    glad_glUniform2f = (PFNGLUNIFORM2FPROC)glad_get_proc("glUniform2f");
    glad_glUniform3f = (PFNGLUNIFORM3FPROC)glad_get_proc("glUniform3f");
    glad_glUniform4f = (PFNGLUNIFORM4FPROC)glad_get_proc("glUniform4f");
    glad_glUniform1i = (PFNGLUNIFORM1IPROC)glad_get_proc("glUniform1i");
    glad_glUniform2i = (PFNGLUNIFORM2IPROC)glad_get_proc("glUniform2i");
    glad_glUniform3i = (PFNGLUNIFORM3IPROC)glad_get_proc("glUniform3i");
    glad_glUniform4i = (PFNGLUNIFORM4IPROC)glad_get_proc("glUniform4i");
    glad_glUniformMatrix2fv = (PFNGLUNIFORMMATRIX2FVPROC)glad_get_proc("glUniformMatrix2fv");
    glad_glUniformMatrix3fv = (PFNGLUNIFORMMATRIX3FVPROC)glad_get_proc("glUniformMatrix3fv");
    glad_glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)glad_get_proc("glUniformMatrix4fv");
    
    /* Load VAO functions */
    glad_glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)glad_get_proc("glGenVertexArrays");
    glad_glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)glad_get_proc("glBindVertexArray");
    glad_glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)glad_get_proc("glDeleteVertexArrays");
    glad_glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)glad_get_proc("glEnableVertexAttribArray");
    glad_glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)glad_get_proc("glDisableVertexAttribArray");
    glad_glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)glad_get_proc("glVertexAttribPointer");
    glad_glBindAttribLocation = (PFNGLBINDATTRIBLOCATIONPROC)glad_get_proc("glBindAttribLocation");
    glad_glGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC)glad_get_proc("glGetAttribLocation");
    
    /* Load drawing functions */
    glad_glDrawArrays = (PFNGLDRAWARRAYSPROC)glad_get_proc("glDrawArrays");
    glad_glDrawElements = (PFNGLDRAWELEMENTSPROC)glad_get_proc("glDrawElements");
    glad_glActiveTexture = (PFNGLACTIVETEXTUREPROC)glad_get_proc("glActiveTexture");
    glad_glGetStringi = (PFNGLGETSTRINGIPROC)glad_get_proc("glGetStringi");
    glad_glClearBufferfv = (PFNGLCLEARBUFFERFVPROC)glad_get_proc("glClearBufferfv");
    glad_glClearBufferiv = (PFNGLCLEARBUFFERIVPROC)glad_get_proc("glClearBufferiv");
    glad_glClearBufferuiv = (PFNGLCLEARBUFFERUIVPROC)glad_get_proc("glClearBufferuiv");
    glad_glClearBufferfi = (PFNGLCLEARBUFFERFIPROC)glad_get_proc("glClearBufferfi");
    
    return 1;
}

int gladLoadGL(void) {
    return gladLoadGLLoader(glad_get_proc_address_impl);
}

#ifdef __cplusplus
}
#endif
