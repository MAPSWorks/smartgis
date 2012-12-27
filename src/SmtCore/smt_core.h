/*
File:    smt_core.h

Desc:    SmartGis基础头文件

Version: Version 1.0

Writter:  陈春亮

Date:    2010.11.17

Copyright (c) 2010 CCL. All rights reserved.
*/
#ifndef _SMT_CORE_H
#define _SMT_CORE_H

#if defined(BUILD_AS_DLL)
	#define SMT_EXPORT_DLL __declspec(dllexport)
#else
	#define SMT_EXPORT_DLL __declspec(dllimport)
#endif


#define SMT_EXPORT_CLASS   SMT_EXPORT_DLL
#define SMT_EXPORT_API     SMT_EXPORT_DLL
#define SMT_EXPORT_DATA    SMT_EXPORT_DLL

#define SmartVersion		1.0

#include <windows.h>
#include <windef.h>
#include <assert.h>
#include <string>
#include <vector>
#include <limits>
#include <math.h>
#include <fstream>
#include <map>

using namespace std;

#define SMT_SAFE_DELETE(p)   {if(p!=NULL){ delete (p);   (p)=NULL;}}
#define SMT_SAFE_DELETE_A(p) {if(p!=NULL){ delete [](p); (p)=NULL;}}

#if defined(BUILD_AS_DLL) ||  defined(BUILD_AS_DLL)
#if    defined( _DEBUG)
#          pragma comment(linker,"/NODEFAULTLIB:libcd.lib")//ignore default library 
#      else
#          pragma comment(linker,"/NODEFAULTLIB:libc.lib")//ignore default library 
#	   endif   
#   endif

// Turn off warnings generated by long std templates
// This warns about truncation to 255 characters in debug/browse info
#   pragma warning (disable : 4786)

// Turn off warnings generated by long std templates
// This warns about truncation to 255 characters in debug/browse info
#   pragma warning (disable : 4503)

// disable: "conversion from 'double' to 'float', possible loss of data
#   pragma warning (disable : 4244)

// disable: "truncation from 'double' to 'float'
#   pragma warning (disable : 4305)

// disable: "<type> needs to have dll-interface to be used by clients'
// Happens on STL member variables which are not public therefore is ok
#   pragma warning (disable : 4251)

// disable: "non dll-interface class used as base for dll-interface class"
// Happens when deriving from Singleton because bug in compiler ignores
// template export
#   pragma warning (disable : 4275)

// disable: "C++ Exception Specification ignored"
// This is because MSVC 6 did not implement all the C++ exception
// specifications in the ANSI C++ draft.
#   pragma warning( disable : 4290 )

// disable: "no suitable definition provided for explicit template
// instantiation request" Occurs in VC7 for no justifiable reason on all
// #includes of Singleton
#   pragma warning( disable: 4661)

// disable: deprecation warnings when using CRT calls in VC8
// These show up on all C runtime lib code in VC8, disable since they clutter
// the warnings with things we may not be able to do anything about (e.g.
// generated code from nvparse etc). I doubt very much that these calls
// will ever be actually removed from VC anyway, it would break too much code.
#	pragma warning( disable: 4996)

// disable: "conditional expression constant"
#   pragma warning (disable : 201)

// everything run ok
#define SMT_OK							S_OK

// general error message ref
#define SMT_FALSE						S_FALSE

//返回码
enum SmtErr
{
	SMT_ERR_NONE					=0,	//正确
	SMT_ERR_FAILURE,					//失败
	SMT_ERR_UNKOWN,						//未知错误
	SMT_ERR_NOT_ENOUGH_MEM,				//内存不足

	SMT_ERR_OPEN_INNER,					//打开错误
	SMT_ERR_ARCHIVE_INNER,				//获取错误
	SMT_ERR_CREATE_INNER,				//创建错误
	SMT_ERR_SAVE_INNER,					//保存错误
	SMT_ERR_MATH_INNER,					//数学错误

	SMT_ERR_FUNC_INNER,					//函数内部错误

	SMT_ERR_INVALID_HANDLE,				//无效句柄
	SMT_ERR_INVALID_PARAM,				//无效参数
	SMT_ERR_INVALID_FILE,				//无效文件

	SMT_ERR_UNSUPPORTED,				//不支持
	SMT_ERR_UNSUPPORTED_DEVICE,			//不支持的驱动
	SMT_ERR_UNSUPPORTED_FMTS,			//不支持格式
	SMT_ERR_UNSUPPORTED_GEOTYPE,		//正确不支持几何类型

	SMT_ERR_DS_INNER,					//数据源内部错误
	SMT_ERR_DB_OPER,					//db操作错误
	SMT_ERR_SMF_OPER,					//smf操作错误
				
	SMT_WRN_ALREADYEXIST,				//警告对象已存在
};

namespace Smt_Core
{
	enum eMouseStatusType
	{
		typeNoStatus,
		typeDLButtonDown,
		typeLButtonDown,
		typeLButtonUp,
		typeMouseMove,
		typeDRButtonDown,
		typeRButtonDown,
		typeRButtonUp,
		typeMouseWeel
	};

	enum eOperType
	{
		typeNoOper,
		typeAppendFeature,
		typeModifyFeature,
		typeAnalysis,
		typeViewMap
	};
}

#define MAX_NAME_LENGTH					50
#define MAX_FILE_PATH					MAX_PATH

#define SmtUnsetMarker					0
#define SmtSetMarker					1


#if defined(WIN32) || defined(_WIN32)
#  ifndef snprintf
#     define snprintf _snprintf
#  endif
#endif

const double							SMT_C_INVALID_DBF_VALUE = 1E+10;
const unsigned int						SMT_C_INVALID_UINT_VALUE = 999999;
const int								SMT_C_INVALID_INT_VALUE = 99999999;
const unsigned long						SMT_C_INVALID_ULONG_VALUE = 999999;
const long								SMT_C_INVALID_LONG_VALUE = 99999999;
const float								SMT_C_INVALID_FLOAT_VALUE = 1E+10;

#define SMT_EQUAL(a,b)					(fabs(a - b) < 1E-5)

#define toString(x)						#x					//转字符串
#define makeChar(x)						#@x					//转字符，a = makeChar(b) 等价于 a='b'

//////////////////////////////////////////////////////////////////////////
//
#define	SMT_THREAD_SAFE										//线程安全

#endif //_SMT_CORE_H