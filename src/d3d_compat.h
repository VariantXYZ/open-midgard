#undef INTERFACE
/*
 * Copyright (C) the Wine project
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

#ifndef __WINE_D3D_H
#define __WINE_D3D_H

#include <stdlib.h>

#define COM_NO_WINDOWS_H
#include <objbase.h>


/*
 * Copyright (C) 2000 Peter Hunnisett
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

/* FIXME: Need to add C++ code for certain structs for headers - this is going to be a problem
 *          if WINE continues to only use C code  - I suppose that we could always inline in
 *          the header file to get around that little problem... */
/* FIXME: We need to implement versioning on everything directx 5 and up if these headers
 *          are going to be generically useful for directx stuff */

#ifndef __WINE_D3DTYPES_H
#define __WINE_D3DTYPES_H

#include <windows.h>
#include <float.h>
#include <ddraw.h>
#include <dxgitype.h>

#ifdef __i386__
#include <pshpack4.h>
#endif

#define D3DVALP(val, prec)      ((float)(val))
#define D3DVAL(val)             ((float)(val))
#define D3DDivide(a, b)         (float)((double) (a) / (double) (b))
#define D3DMultiply(a, b)       ((a) * (b))

typedef LONG D3DFIXED;


#ifndef RGB_MAKE
#define CI_GETALPHA(ci)    ((ci) >> 24)
#define CI_GETINDEX(ci)    (((ci) >> 8) & 0xffff)
#define CI_GETFRACTION(ci) ((ci) & 0xff)
#define CI_ROUNDINDEX(ci)  CI_GETINDEX((ci) + 0x80)
#define CI_MASKALPHA(ci)   ((ci) & 0xffffff)
#define CI_MAKE(a, i, f)    (((a) << 24) | ((i) << 8) | (f))

#define RGBA_GETALPHA(rgb)      ((rgb) >> 24)
#define RGBA_GETRED(rgb)        (((rgb) >> 16) & 0xff)
#define RGBA_GETGREEN(rgb)      (((rgb) >> 8) & 0xff)
#define RGBA_GETBLUE(rgb)       ((rgb) & 0xff)
#define RGBA_MAKE(r, g, b, a)   ((D3DCOLOR) (((a) << 24) | ((r) << 16) | ((g) << 8) | (b)))

#define D3DRGB(r, g, b) \
(0xff000000 | ( ((LONG)((r) * 255)) << 16) | (((LONG)((g) * 255)) << 8) | (LONG)((b) * 255))
#define D3DRGBA(r, g, b, a) \
(   (((LONG)((a) * 255)) << 24) | (((LONG)((r) * 255)) << 16) \
|   (((LONG)((g) * 255)) << 8) | (LONG)((b) * 255) \
)

#define RGB_GETRED(rgb)         (((rgb) >> 16) & 0xff)
#define RGB_GETGREEN(rgb)       (((rgb) >> 8) & 0xff)
#define RGB_GETBLUE(rgb)        ((rgb) & 0xff)
#define RGBA_SETALPHA(rgba, x) (((x) << 24) | ((rgba) & 0x00ffffff))
#define RGB_MAKE(r, g, b)       ((D3DCOLOR) (((r) << 16) | ((g) << 8) | (b)))
#define RGBA_TORGB(rgba)       ((D3DCOLOR) ((rgba) & 0xffffff))
#define RGB_TORGBA(rgb)        ((D3DCOLOR) ((rgb) | 0xff000000))

#endif

#define D3DENUMRET_CANCEL                        DDENUMRET_CANCEL
#define D3DENUMRET_OK                            DDENUMRET_OK

typedef HRESULT (CALLBACK *LPD3DVALIDATECALLBACK)(void *ctx, DWORD offset);
typedef HRESULT (CALLBACK *LPD3DENUMTEXTUREFORMATSCALLBACK)(DDSURFACEDESC *surface_desc, void *ctx);
typedef HRESULT (CALLBACK *LPD3DENUMPIXELFORMATSCALLBACK)(DDPIXELFORMAT *format, void *ctx);

#ifndef DX_SHARED_DEFINES

typedef float D3DVALUE,*LPD3DVALUE;

#ifndef D3DCOLOR_DEFINED
typedef DWORD D3DCOLOR, *LPD3DCOLOR;
#define D3DCOLOR_DEFINED
#endif

#ifndef D3DVECTOR_DEFINED
typedef struct _D3DVECTOR {
    union {
        D3DVALUE        x;
        D3DVALUE dvX;
    } DUMMYUNIONNAME1;
    union {
        D3DVALUE        y;
        D3DVALUE dvY;
    } DUMMYUNIONNAME2;
    union {
        D3DVALUE        z;
        D3DVALUE dvZ;
    } DUMMYUNIONNAME3;
    #if defined(__cplusplus) && defined(D3D_OVERLOADS)
    /* the definitions for these methods are in d3dvec.inl */
    public:
        /*** constructors ***/
        _D3DVECTOR() {}
        _D3DVECTOR(D3DVALUE f);
        _D3DVECTOR(D3DVALUE _x, D3DVALUE _y, D3DVALUE _z);
        _D3DVECTOR(const D3DVALUE f[3]);

        /*** assignment operators ***/
        _D3DVECTOR& operator += (const _D3DVECTOR& v);
        _D3DVECTOR& operator -= (const _D3DVECTOR& v);
        _D3DVECTOR& operator *= (const _D3DVECTOR& v);
        _D3DVECTOR& operator /= (const _D3DVECTOR& v);
        _D3DVECTOR& operator *= (D3DVALUE s);
        _D3DVECTOR& operator /= (D3DVALUE s);

        /*** unary operators ***/
        friend _D3DVECTOR operator + (const _D3DVECTOR& v);
        friend _D3DVECTOR operator - (const _D3DVECTOR& v);

        /*** binary operators ***/
        friend _D3DVECTOR operator + (const _D3DVECTOR& v1, const _D3DVECTOR& v2);
        friend _D3DVECTOR operator - (const _D3DVECTOR& v1, const _D3DVECTOR& v2);

        friend _D3DVECTOR operator * (const _D3DVECTOR& v, D3DVALUE s);
        friend _D3DVECTOR operator * (D3DVALUE s, const _D3DVECTOR& v);
        friend _D3DVECTOR operator / (const _D3DVECTOR& v, D3DVALUE s);

        friend D3DVALUE SquareMagnitude(const _D3DVECTOR& v);
        friend D3DVALUE Magnitude(const _D3DVECTOR& v);

        friend _D3DVECTOR Normalize(const _D3DVECTOR& v);

        friend D3DVALUE DotProduct(const _D3DVECTOR& v1, const _D3DVECTOR& v2);
        friend _D3DVECTOR CrossProduct(const _D3DVECTOR& v1, const _D3DVECTOR& v2);
        #endif
} D3DVECTOR,*LPD3DVECTOR;
#define D3DVECTOR_DEFINED
#endif

#define DX_SHARED_DEFINES
#endif /* DX_SHARED_DEFINES */

typedef DWORD D3DMATERIALHANDLE, *LPD3DMATERIALHANDLE;
typedef DWORD D3DTEXTUREHANDLE,  *LPD3DTEXTUREHANDLE;
typedef DWORD D3DMATRIXHANDLE,   *LPD3DMATRIXHANDLE;

// typedef struct _D3DCOLORVALUE {
//     union {
//         D3DVALUE r;
//         D3DVALUE dvR;
//     } DUMMYUNIONNAME1;
//     union {
//         D3DVALUE g;
//         D3DVALUE dvG;
//     } DUMMYUNIONNAME2;
//     union {
//         D3DVALUE b;
//         D3DVALUE dvB;
//     } DUMMYUNIONNAME3;
//     union {
//         D3DVALUE a;
//         D3DVALUE dvA;
//     } DUMMYUNIONNAME4;
// } D3DCOLORVALUE,*LPD3DCOLORVALUE;

typedef struct _D3DRECT {
    union {
        LONG x1;
        LONG lX1;
    } DUMMYUNIONNAME1;
    union {
        LONG y1;
        LONG lY1;
    } DUMMYUNIONNAME2;
    union {
        LONG x2;
        LONG lX2;
    } DUMMYUNIONNAME3;
    union {
        LONG y2;
        LONG lY2;
    } DUMMYUNIONNAME4;
} D3DRECT, *LPD3DRECT;

typedef struct _D3DHVERTEX {
    DWORD         dwFlags;
    union {
        D3DVALUE    hx;
        D3DVALUE    dvHX;
    } DUMMYUNIONNAME1;
    union {
        D3DVALUE    hy;
        D3DVALUE    dvHY;
    } DUMMYUNIONNAME2;
    union {
        D3DVALUE    hz;
        D3DVALUE    dvHZ;
    } DUMMYUNIONNAME3;
} D3DHVERTEX, *LPD3DHVERTEX;

/*
 * Transformed/lit vertices
 */
typedef struct _D3DTLVERTEX {
    union {
        D3DVALUE    sx;
        D3DVALUE    dvSX;
    } DUMMYUNIONNAME1;
    union {
        D3DVALUE    sy;
        D3DVALUE    dvSY;
    } DUMMYUNIONNAME2;
    union {
        D3DVALUE    sz;
        D3DVALUE    dvSZ;
    } DUMMYUNIONNAME3;
    union {
        D3DVALUE    rhw;
        D3DVALUE    dvRHW;
    } DUMMYUNIONNAME4;
    union {
        D3DCOLOR    color;
        D3DCOLOR    dcColor;
    } DUMMYUNIONNAME5;
    union {
        D3DCOLOR    specular;
        D3DCOLOR    dcSpecular;
    } DUMMYUNIONNAME6;
    union {
        D3DVALUE    tu;
        D3DVALUE    dvTU;
    } DUMMYUNIONNAME7;
    union {
        D3DVALUE    tv;
        D3DVALUE    dvTV;
    } DUMMYUNIONNAME8;
    #if defined(__cplusplus) && defined(D3D_OVERLOADS)
public:
    _D3DTLVERTEX() {}
    _D3DTLVERTEX(const D3DVECTOR& v, float _rhw, D3DCOLOR _color, D3DCOLOR _specular, float _tu, float _tv) {
        sx = v.x; sy = v.y; sz = v.z; rhw = _rhw;
        color = _color; specular = _specular;
        tu = _tu; tv = _tv;
    }
    #endif
} D3DTLVERTEX, *LPD3DTLVERTEX;

typedef struct _D3DLVERTEX {
    union {
        D3DVALUE x;
        D3DVALUE dvX;
    } DUMMYUNIONNAME1;
    union {
        D3DVALUE y;
        D3DVALUE dvY;
    } DUMMYUNIONNAME2;
    union {
        D3DVALUE z;
        D3DVALUE dvZ;
    } DUMMYUNIONNAME3;
    DWORD            dwReserved;
    union {
        D3DCOLOR     color;
        D3DCOLOR     dcColor;
    } DUMMYUNIONNAME4;
    union {
        D3DCOLOR     specular;
        D3DCOLOR     dcSpecular;
    } DUMMYUNIONNAME5;
    union {
        D3DVALUE     tu;
        D3DVALUE     dvTU;
    } DUMMYUNIONNAME6;
    union {
        D3DVALUE     tv;
        D3DVALUE     dvTV;
    } DUMMYUNIONNAME7;
} D3DLVERTEX, *LPD3DLVERTEX;

typedef struct _D3DVERTEX {
    union {
        D3DVALUE     x;
        D3DVALUE     dvX;
    } DUMMYUNIONNAME1;
    union {
        D3DVALUE     y;
        D3DVALUE     dvY;
    } DUMMYUNIONNAME2;
    union {
        D3DVALUE     z;
        D3DVALUE     dvZ;
    } DUMMYUNIONNAME3;
    union {
        D3DVALUE     nx;
        D3DVALUE     dvNX;
    } DUMMYUNIONNAME4;
    union {
        D3DVALUE     ny;
        D3DVALUE     dvNY;
    } DUMMYUNIONNAME5;
    union {
        D3DVALUE     nz;
        D3DVALUE     dvNZ;
    } DUMMYUNIONNAME6;
    union {
        D3DVALUE     tu;
        D3DVALUE     dvTU;
    } DUMMYUNIONNAME7;
    union {
        D3DVALUE     tv;
        D3DVALUE     dvTV;
    } DUMMYUNIONNAME8;
    #if defined(__cplusplus) && defined(D3D_OVERLOADS)
public:
    _D3DVERTEX() {}
    _D3DVERTEX(const D3DVECTOR& v, const D3DVECTOR& n, float _tu, float _tv) {
        x  = v.x; y  = v.y; z  = v.z;
        nx = n.x; ny = n.y; nz = n.z;
        tu = _tu; tv = _tv;
    }
    #endif
} D3DVERTEX, *LPD3DVERTEX;

typedef struct _D3DMATRIX {
    D3DVALUE        _11, _12, _13, _14;
    D3DVALUE        _21, _22, _23, _24;
    D3DVALUE        _31, _32, _33, _34;
    D3DVALUE        _41, _42, _43, _44;
    #if defined(__cplusplus) && defined(D3D_OVERLOADS)
    _D3DMATRIX() { }

    /* This is different from MS, but avoids anonymous structs. */
    D3DVALUE &operator () (int r, int c)
    { return (&_11)[r*4 + c]; }
    const D3DVALUE &operator() (int r, int c) const
    { return (&_11)[r*4 + c]; }
    #endif
} D3DMATRIX, *LPD3DMATRIX;

#if defined(__cplusplus) && defined(D3D_OVERLOADS)
#include <d3dvec.inl>
#endif

typedef struct _D3DVIEWPORT {
    DWORD       dwSize;
    DWORD       dwX;
    DWORD       dwY;
    DWORD       dwWidth;
    DWORD       dwHeight;
    D3DVALUE    dvScaleX;
    D3DVALUE    dvScaleY;
    D3DVALUE    dvMaxX;
    D3DVALUE    dvMaxY;
    D3DVALUE    dvMinZ;
    D3DVALUE    dvMaxZ;
} D3DVIEWPORT, *LPD3DVIEWPORT;

typedef struct _D3DVIEWPORT2 {
    DWORD       dwSize;
    DWORD       dwX;
    DWORD       dwY;
    DWORD       dwWidth;
    DWORD       dwHeight;
    D3DVALUE    dvClipX;
    D3DVALUE    dvClipY;
    D3DVALUE    dvClipWidth;
    D3DVALUE    dvClipHeight;
    D3DVALUE    dvMinZ;
    D3DVALUE    dvMaxZ;
} D3DVIEWPORT2, *LPD3DVIEWPORT2;

typedef struct _D3DVIEWPORT7 {
    DWORD       dwX;
    DWORD       dwY;
    DWORD       dwWidth;
    DWORD       dwHeight;
    D3DVALUE    dvMinZ;
    D3DVALUE    dvMaxZ;
} D3DVIEWPORT7, *LPD3DVIEWPORT7;

#define D3DMAXUSERCLIPPLANES 32

#define D3DCLIPPLANE0 (1 << 0)
#define D3DCLIPPLANE1 (1 << 1)
#define D3DCLIPPLANE2 (1 << 2)
#define D3DCLIPPLANE3 (1 << 3)
#define D3DCLIPPLANE4 (1 << 4)
#define D3DCLIPPLANE5 (1 << 5)

#define D3DCLIP_LEFT     0x00000001
#define D3DCLIP_RIGHT    0x00000002
#define D3DCLIP_TOP      0x00000004
#define D3DCLIP_BOTTOM   0x00000008
#define D3DCLIP_FRONT    0x00000010
#define D3DCLIP_BACK     0x00000020
#define D3DCLIP_GEN0     0x00000040
#define D3DCLIP_GEN1     0x00000080
#define D3DCLIP_GEN2     0x00000100
#define D3DCLIP_GEN3     0x00000200
#define D3DCLIP_GEN4     0x00000400
#define D3DCLIP_GEN5     0x00000800

#define D3DSTATUS_CLIPUNIONLEFT                 D3DCLIP_LEFT
#define D3DSTATUS_CLIPUNIONRIGHT                D3DCLIP_RIGHT
#define D3DSTATUS_CLIPUNIONTOP                  D3DCLIP_TOP
#define D3DSTATUS_CLIPUNIONBOTTOM               D3DCLIP_BOTTOM
#define D3DSTATUS_CLIPUNIONFRONT                D3DCLIP_FRONT
#define D3DSTATUS_CLIPUNIONBACK                 D3DCLIP_BACK
#define D3DSTATUS_CLIPUNIONGEN0                 D3DCLIP_GEN0
#define D3DSTATUS_CLIPUNIONGEN1                 D3DCLIP_GEN1
#define D3DSTATUS_CLIPUNIONGEN2                 D3DCLIP_GEN2
#define D3DSTATUS_CLIPUNIONGEN3                 D3DCLIP_GEN3
#define D3DSTATUS_CLIPUNIONGEN4                 D3DCLIP_GEN4
#define D3DSTATUS_CLIPUNIONGEN5                 D3DCLIP_GEN5

#define D3DSTATUS_CLIPINTERSECTIONLEFT          0x00001000
#define D3DSTATUS_CLIPINTERSECTIONRIGHT         0x00002000
#define D3DSTATUS_CLIPINTERSECTIONTOP           0x00004000
#define D3DSTATUS_CLIPINTERSECTIONBOTTOM        0x00008000
#define D3DSTATUS_CLIPINTERSECTIONFRONT         0x00010000
#define D3DSTATUS_CLIPINTERSECTIONBACK          0x00020000
#define D3DSTATUS_CLIPINTERSECTIONGEN0          0x00040000
#define D3DSTATUS_CLIPINTERSECTIONGEN1          0x00080000
#define D3DSTATUS_CLIPINTERSECTIONGEN2          0x00100000
#define D3DSTATUS_CLIPINTERSECTIONGEN3          0x00200000
#define D3DSTATUS_CLIPINTERSECTIONGEN4          0x00400000
#define D3DSTATUS_CLIPINTERSECTIONGEN5          0x00800000
#define D3DSTATUS_ZNOTVISIBLE                   0x01000000

#define D3DSTATUS_CLIPUNIONALL  (               \
D3DSTATUS_CLIPUNIONLEFT     |       \
D3DSTATUS_CLIPUNIONRIGHT    |       \
D3DSTATUS_CLIPUNIONTOP      |       \
D3DSTATUS_CLIPUNIONBOTTOM   |       \
D3DSTATUS_CLIPUNIONFRONT    |       \
D3DSTATUS_CLIPUNIONBACK     |       \
D3DSTATUS_CLIPUNIONGEN0     |       \
D3DSTATUS_CLIPUNIONGEN1     |       \
D3DSTATUS_CLIPUNIONGEN2     |       \
D3DSTATUS_CLIPUNIONGEN3     |       \
D3DSTATUS_CLIPUNIONGEN4     |       \
D3DSTATUS_CLIPUNIONGEN5             \
)

#define D3DSTATUS_CLIPINTERSECTIONALL   (               \
D3DSTATUS_CLIPINTERSECTIONLEFT      |       \
D3DSTATUS_CLIPINTERSECTIONRIGHT     |       \
D3DSTATUS_CLIPINTERSECTIONTOP       |       \
D3DSTATUS_CLIPINTERSECTIONBOTTOM    |       \
D3DSTATUS_CLIPINTERSECTIONFRONT     |       \
D3DSTATUS_CLIPINTERSECTIONBACK      |       \
D3DSTATUS_CLIPINTERSECTIONGEN0      |       \
D3DSTATUS_CLIPINTERSECTIONGEN1      |       \
D3DSTATUS_CLIPINTERSECTIONGEN2      |       \
D3DSTATUS_CLIPINTERSECTIONGEN3      |       \
D3DSTATUS_CLIPINTERSECTIONGEN4      |       \
D3DSTATUS_CLIPINTERSECTIONGEN5              \
)

#define D3DSTATUS_DEFAULT       (                       \
D3DSTATUS_CLIPINTERSECTIONALL       |       \
D3DSTATUS_ZNOTVISIBLE)

#define D3DTRANSFORM_CLIPPED       0x00000001
#define D3DTRANSFORM_UNCLIPPED     0x00000002

typedef struct _D3DTRANSFORMDATA {
    DWORD           dwSize;
    void            *lpIn;
    DWORD           dwInSize;
    void            *lpOut;
    DWORD           dwOutSize;
    D3DHVERTEX      *lpHOut;
    DWORD           dwClip;
    DWORD           dwClipIntersection;
    DWORD           dwClipUnion;
    D3DRECT         drExtent;
} D3DTRANSFORMDATA, *LPD3DTRANSFORMDATA;

typedef struct _D3DLIGHTINGELEMENT {
    D3DVECTOR dvPosition;
    D3DVECTOR dvNormal;
} D3DLIGHTINGELEMENT, *LPD3DLIGHTINGELEMENT;

typedef struct _D3DMATERIAL {
    DWORD               dwSize;
    union {
        D3DCOLORVALUE   diffuse;
        D3DCOLORVALUE   dcvDiffuse;
    } DUMMYUNIONNAME;
    union {
        D3DCOLORVALUE   ambient;
        D3DCOLORVALUE   dcvAmbient;
    } DUMMYUNIONNAME1;
    union {
        D3DCOLORVALUE   specular;
        D3DCOLORVALUE   dcvSpecular;
    } DUMMYUNIONNAME2;
    union {
        D3DCOLORVALUE   emissive;
        D3DCOLORVALUE   dcvEmissive;
    } DUMMYUNIONNAME3;
    union {
        D3DVALUE        power;
        D3DVALUE        dvPower;
    } DUMMYUNIONNAME4;
    D3DTEXTUREHANDLE    hTexture;
    DWORD               dwRampSize;
} D3DMATERIAL, *LPD3DMATERIAL;

typedef struct _D3DMATERIAL7 {
    union {
        D3DCOLORVALUE   diffuse;
        D3DCOLORVALUE   dcvDiffuse;
    } DUMMYUNIONNAME;
    union {
        D3DCOLORVALUE   ambient;
        D3DCOLORVALUE   dcvAmbient;
    } DUMMYUNIONNAME1;
    union {
        D3DCOLORVALUE   specular;
        D3DCOLORVALUE   dcvSpecular;
    } DUMMYUNIONNAME2;
    union {
        D3DCOLORVALUE   emissive;
        D3DCOLORVALUE   dcvEmissive;
    } DUMMYUNIONNAME3;
    union {
        D3DVALUE        power;
        D3DVALUE        dvPower;
    } DUMMYUNIONNAME4;
} D3DMATERIAL7, *LPD3DMATERIAL7;

typedef enum {
    D3DLIGHT_POINT          = 1,
    D3DLIGHT_SPOT           = 2,
    D3DLIGHT_DIRECTIONAL    = 3,
    D3DLIGHT_PARALLELPOINT  = 4,
    D3DLIGHT_GLSPOT         = 5,
    D3DLIGHT_FORCE_DWORD    = 0x7fffffff
} D3DLIGHTTYPE;

typedef struct _D3DLIGHT {
    DWORD           dwSize;
    D3DLIGHTTYPE    dltType;
    D3DCOLORVALUE   dcvColor;
    D3DVECTOR       dvPosition;
    D3DVECTOR       dvDirection;
    D3DVALUE        dvRange;
    D3DVALUE        dvFalloff;
    D3DVALUE        dvAttenuation0;
    D3DVALUE        dvAttenuation1;
    D3DVALUE        dvAttenuation2;
    D3DVALUE        dvTheta;
    D3DVALUE        dvPhi;
} D3DLIGHT,*LPD3DLIGHT;

typedef struct _D3DLIGHT7 {
    D3DLIGHTTYPE    dltType;
    D3DCOLORVALUE   dcvDiffuse;
    D3DCOLORVALUE   dcvSpecular;
    D3DCOLORVALUE   dcvAmbient;
    D3DVECTOR       dvPosition;
    D3DVECTOR       dvDirection;
    D3DVALUE        dvRange;
    D3DVALUE        dvFalloff;
    D3DVALUE        dvAttenuation0;
    D3DVALUE        dvAttenuation1;
    D3DVALUE        dvAttenuation2;
    D3DVALUE        dvTheta;
    D3DVALUE        dvPhi;
} D3DLIGHT7, *LPD3DLIGHT7;

#define D3DLIGHT_ACTIVE         0x00000001
#define D3DLIGHT_NO_SPECULAR    0x00000002
#define D3DLIGHT_ALL (D3DLIGHT_ACTIVE | D3DLIGHT_NO_SPECULAR) /* 0x3 */

#define D3DLIGHT_RANGE_MAX              ((float)sqrt(FLT_MAX))

typedef struct _D3DLIGHT2 {
    DWORD           dwSize;
    D3DLIGHTTYPE    dltType;
    D3DCOLORVALUE   dcvColor;
    D3DVECTOR       dvPosition;
    D3DVECTOR       dvDirection;
    D3DVALUE        dvRange;
    D3DVALUE        dvFalloff;
    D3DVALUE        dvAttenuation0;
    D3DVALUE        dvAttenuation1;
    D3DVALUE        dvAttenuation2;
    D3DVALUE        dvTheta;
    D3DVALUE        dvPhi;
    DWORD           dwFlags;
} D3DLIGHT2, *LPD3DLIGHT2;

typedef struct _D3DLIGHTDATA {
    DWORD                dwSize;
    D3DLIGHTINGELEMENT   *lpIn;
    DWORD                dwInSize;
    D3DTLVERTEX          *lpOut;
    DWORD                dwOutSize;
} D3DLIGHTDATA, *LPD3DLIGHTDATA;

#define D3DCOLOR_MONO   1
#define D3DCOLOR_RGB    2

typedef DWORD D3DCOLORMODEL;


#define D3DCLEAR_TARGET   0x00000001
#define D3DCLEAR_ZBUFFER  0x00000002
#define D3DCLEAR_STENCIL  0x00000004

typedef enum _D3DOPCODE {
    D3DOP_POINT           = 1,
    D3DOP_LINE            = 2,
    D3DOP_TRIANGLE        = 3,
    D3DOP_MATRIXLOAD      = 4,
    D3DOP_MATRIXMULTIPLY  = 5,
    D3DOP_STATETRANSFORM  = 6,
    D3DOP_STATELIGHT      = 7,
    D3DOP_STATERENDER     = 8,
    D3DOP_PROCESSVERTICES = 9,
    D3DOP_TEXTURELOAD     = 10,
    D3DOP_EXIT            = 11,
    D3DOP_BRANCHFORWARD   = 12,
    D3DOP_SPAN            = 13,
    D3DOP_SETSTATUS       = 14,

    D3DOP_FORCE_DWORD     = 0x7fffffff
} D3DOPCODE;

typedef struct _D3DINSTRUCTION {
    BYTE bOpcode;
    BYTE bSize;
    WORD wCount;
} D3DINSTRUCTION, *LPD3DINSTRUCTION;

typedef struct _D3DTEXTURELOAD {
    D3DTEXTUREHANDLE hDestTexture;
    D3DTEXTUREHANDLE hSrcTexture;
} D3DTEXTURELOAD, *LPD3DTEXTURELOAD;

typedef struct _D3DPICKRECORD {
    BYTE     bOpcode;
    BYTE     bPad;
    DWORD    dwOffset;
    D3DVALUE dvZ;
} D3DPICKRECORD, *LPD3DPICKRECORD;

typedef enum {
    D3DSHADE_FLAT         = 1,
    D3DSHADE_GOURAUD      = 2,
    D3DSHADE_PHONG        = 3,
    D3DSHADE_FORCE_DWORD  = 0x7fffffff
} D3DSHADEMODE;

typedef enum {
    D3DFILL_POINT         = 1,
    D3DFILL_WIREFRAME     = 2,
    D3DFILL_SOLID         = 3,
    D3DFILL_FORCE_DWORD   = 0x7fffffff
} D3DFILLMODE;

typedef struct _D3DLINEPATTERN {
    WORD    wRepeatFactor;
    WORD    wLinePattern;
} D3DLINEPATTERN;

typedef enum {
    D3DFILTER_NEAREST          = 1,
    D3DFILTER_LINEAR           = 2,
    D3DFILTER_MIPNEAREST       = 3,
    D3DFILTER_MIPLINEAR        = 4,
    D3DFILTER_LINEARMIPNEAREST = 5,
    D3DFILTER_LINEARMIPLINEAR  = 6,
    D3DFILTER_FORCE_DWORD      = 0x7fffffff
} D3DTEXTUREFILTER;

typedef enum {
    D3DBLEND_ZERO            = 1,
    D3DBLEND_ONE             = 2,
    D3DBLEND_SRCCOLOR        = 3,
    D3DBLEND_INVSRCCOLOR     = 4,
    D3DBLEND_SRCALPHA        = 5,
    D3DBLEND_INVSRCALPHA     = 6,
    D3DBLEND_DESTALPHA       = 7,
    D3DBLEND_INVDESTALPHA    = 8,
    D3DBLEND_DESTCOLOR       = 9,
    D3DBLEND_INVDESTCOLOR    = 10,
    D3DBLEND_SRCALPHASAT     = 11,
    D3DBLEND_BOTHSRCALPHA    = 12,
    D3DBLEND_BOTHINVSRCALPHA = 13,
    D3DBLEND_FORCE_DWORD     = 0x7fffffff
} D3DBLEND;

typedef enum {
    D3DTBLEND_DECAL         = 1,
    D3DTBLEND_MODULATE      = 2,
    D3DTBLEND_DECALALPHA    = 3,
    D3DTBLEND_MODULATEALPHA = 4,
    D3DTBLEND_DECALMASK     = 5,
    D3DTBLEND_MODULATEMASK  = 6,
    D3DTBLEND_COPY          = 7,
    D3DTBLEND_ADD           = 8,
    D3DTBLEND_FORCE_DWORD   = 0x7fffffff
} D3DTEXTUREBLEND;

typedef enum _D3DTEXTUREADDRESS {
    D3DTADDRESS_WRAP           = 1,
    D3DTADDRESS_MIRROR         = 2,
    D3DTADDRESS_CLAMP          = 3,
    D3DTADDRESS_BORDER         = 4,
    D3DTADDRESS_FORCE_DWORD    = 0x7fffffff
} D3DTEXTUREADDRESS;

typedef enum {
    D3DCULL_NONE        = 1,
    D3DCULL_CW          = 2,
    D3DCULL_CCW         = 3,
    D3DCULL_FORCE_DWORD = 0x7fffffff
} D3DCULL;

typedef enum {
    D3DCMP_NEVER        = 1,
    D3DCMP_LESS         = 2,
    D3DCMP_EQUAL        = 3,
    D3DCMP_LESSEQUAL    = 4,
    D3DCMP_GREATER      = 5,
    D3DCMP_NOTEQUAL     = 6,
    D3DCMP_GREATEREQUAL = 7,
    D3DCMP_ALWAYS       = 8,
    D3DCMP_FORCE_DWORD  = 0x7fffffff
} D3DCMPFUNC;

typedef enum _D3DSTENCILOP {
    D3DSTENCILOP_KEEP        = 1,
    D3DSTENCILOP_ZERO        = 2,
    D3DSTENCILOP_REPLACE     = 3,
    D3DSTENCILOP_INCRSAT     = 4,
    D3DSTENCILOP_DECRSAT     = 5,
    D3DSTENCILOP_INVERT      = 6,
    D3DSTENCILOP_INCR        = 7,
    D3DSTENCILOP_DECR        = 8,
    D3DSTENCILOP_FORCE_DWORD = 0x7fffffff
} D3DSTENCILOP;

typedef enum _D3DFOGMODE {
    D3DFOG_NONE         = 0,
    D3DFOG_EXP          = 1,
    D3DFOG_EXP2         = 2,
    D3DFOG_LINEAR       = 3,
    D3DFOG_FORCE_DWORD  = 0x7fffffff
} D3DFOGMODE;

typedef enum _D3DZBUFFERTYPE {
    D3DZB_FALSE        = 0,
    D3DZB_TRUE         = 1,
    D3DZB_USEW         = 2,
    D3DZB_FORCE_DWORD  = 0x7fffffff
} D3DZBUFFERTYPE;

typedef enum _D3DANTIALIASMODE {
    D3DANTIALIAS_NONE            = 0,
    D3DANTIALIAS_SORTDEPENDENT   = 1,
    D3DANTIALIAS_SORTINDEPENDENT = 2,
    D3DANTIALIAS_FORCE_DWORD     = 0x7fffffff
} D3DANTIALIASMODE;

typedef enum {
    D3DVT_VERTEX        = 1,
    D3DVT_LVERTEX       = 2,
    D3DVT_TLVERTEX      = 3,
    D3DVT_FORCE_DWORD   = 0x7fffffff
} D3DVERTEXTYPE;

typedef enum {
    D3DPT_POINTLIST     = 1,
    D3DPT_LINELIST      = 2,
    D3DPT_LINESTRIP     = 3,
    D3DPT_TRIANGLELIST  = 4,
    D3DPT_TRIANGLESTRIP = 5,
    D3DPT_TRIANGLEFAN   = 6,
    D3DPT_FORCE_DWORD   = 0x7fffffff
} D3DPRIMITIVETYPE;

#define D3DSTATE_OVERRIDE_BIAS      256

#define D3DSTATE_OVERRIDE(type) (D3DRENDERSTATETYPE)(((DWORD) (type) + D3DSTATE_OVERRIDE_BIAS))

typedef enum _D3DTRANSFORMSTATETYPE {
    D3DTRANSFORMSTATE_WORLD         = 1,
    D3DTRANSFORMSTATE_VIEW          = 2,
    D3DTRANSFORMSTATE_PROJECTION    = 3,
    D3DTRANSFORMSTATE_WORLD1        = 4,
    D3DTRANSFORMSTATE_WORLD2        = 5,
    D3DTRANSFORMSTATE_WORLD3        = 6,
    D3DTRANSFORMSTATE_TEXTURE0      = 16,
    D3DTRANSFORMSTATE_TEXTURE1      = 17,
    D3DTRANSFORMSTATE_TEXTURE2      = 18,
    D3DTRANSFORMSTATE_TEXTURE3      = 19,
    D3DTRANSFORMSTATE_TEXTURE4      = 20,
    D3DTRANSFORMSTATE_TEXTURE5      = 21,
    D3DTRANSFORMSTATE_TEXTURE6      = 22,
    D3DTRANSFORMSTATE_TEXTURE7      = 23,
    D3DTRANSFORMSTATE_FORCE_DWORD   = 0x7fffffff
} D3DTRANSFORMSTATETYPE;

typedef enum {
    D3DLIGHTSTATE_MATERIAL      = 1,
    D3DLIGHTSTATE_AMBIENT       = 2,
    D3DLIGHTSTATE_COLORMODEL    = 3,
    D3DLIGHTSTATE_FOGMODE       = 4,
    D3DLIGHTSTATE_FOGSTART      = 5,
    D3DLIGHTSTATE_FOGEND        = 6,
    D3DLIGHTSTATE_FOGDENSITY    = 7,
    D3DLIGHTSTATE_COLORVERTEX   = 8,
    D3DLIGHTSTATE_FORCE_DWORD   = 0x7fffffff
} D3DLIGHTSTATETYPE;

typedef enum {
    D3DRENDERSTATE_TEXTUREHANDLE      = 1,
    D3DRENDERSTATE_ANTIALIAS          = 2,
    D3DRENDERSTATE_TEXTUREADDRESS     = 3,
    D3DRENDERSTATE_TEXTUREPERSPECTIVE = 4,
    D3DRENDERSTATE_WRAPU              = 5, /* <= d3d6 */
    D3DRENDERSTATE_WRAPV              = 6, /* <= d3d6 */
    D3DRENDERSTATE_ZENABLE            = 7,
    D3DRENDERSTATE_FILLMODE           = 8,
    D3DRENDERSTATE_SHADEMODE          = 9,
    D3DRENDERSTATE_LINEPATTERN        = 10,
    D3DRENDERSTATE_MONOENABLE         = 11, /* <= d3d6 */
    D3DRENDERSTATE_ROP2               = 12, /* <= d3d6 */
    D3DRENDERSTATE_PLANEMASK          = 13, /* <= d3d6 */
    D3DRENDERSTATE_ZWRITEENABLE       = 14,
    D3DRENDERSTATE_ALPHATESTENABLE    = 15,
    D3DRENDERSTATE_LASTPIXEL          = 16,
    D3DRENDERSTATE_TEXTUREMAG         = 17,
    D3DRENDERSTATE_TEXTUREMIN         = 18,
    D3DRENDERSTATE_SRCBLEND           = 19,
    D3DRENDERSTATE_DESTBLEND          = 20,
    D3DRENDERSTATE_TEXTUREMAPBLEND    = 21,
    D3DRENDERSTATE_CULLMODE           = 22,
    D3DRENDERSTATE_ZFUNC              = 23,
    D3DRENDERSTATE_ALPHAREF           = 24,
    D3DRENDERSTATE_ALPHAFUNC          = 25,
    D3DRENDERSTATE_DITHERENABLE       = 26,
    D3DRENDERSTATE_ALPHABLENDENABLE   = 27,
    D3DRENDERSTATE_FOGENABLE          = 28,
    D3DRENDERSTATE_SPECULARENABLE     = 29,
    D3DRENDERSTATE_ZVISIBLE           = 30,
    D3DRENDERSTATE_SUBPIXEL           = 31, /* <= d3d6 */
    D3DRENDERSTATE_SUBPIXELX          = 32, /* <= d3d6 */
    D3DRENDERSTATE_STIPPLEDALPHA      = 33,
    D3DRENDERSTATE_FOGCOLOR           = 34,
    D3DRENDERSTATE_FOGTABLEMODE       = 35,
    D3DRENDERSTATE_FOGTABLESTART      = 36,
    D3DRENDERSTATE_FOGTABLEEND        = 37,
    D3DRENDERSTATE_FOGTABLEDENSITY    = 38,
    D3DRENDERSTATE_FOGSTART           = 36,
    D3DRENDERSTATE_FOGEND             = 37,
    D3DRENDERSTATE_FOGDENSITY         = 38,
    D3DRENDERSTATE_STIPPLEENABLE      = 39, /* <= d3d6 */
    /* d3d5 */
    D3DRENDERSTATE_EDGEANTIALIAS      = 40,
    D3DRENDERSTATE_COLORKEYENABLE     = 41,
    D3DRENDERSTATE_BORDERCOLOR        = 43,
    D3DRENDERSTATE_TEXTUREADDRESSU    = 44,
    D3DRENDERSTATE_TEXTUREADDRESSV    = 45,
    D3DRENDERSTATE_MIPMAPLODBIAS      = 46, /* <= d3d6 */
    D3DRENDERSTATE_ZBIAS              = 47,
    D3DRENDERSTATE_RANGEFOGENABLE     = 48,
    D3DRENDERSTATE_ANISOTROPY         = 49, /* <= d3d6 */
    D3DRENDERSTATE_FLUSHBATCH         = 50, /* <= d3d6 */
    /* d3d6 */
    D3DRENDERSTATE_TRANSLUCENTSORTINDEPENDENT = 51, /* <= d3d6 */

    D3DRENDERSTATE_STENCILENABLE      = 52,
    D3DRENDERSTATE_STENCILFAIL        = 53,
    D3DRENDERSTATE_STENCILZFAIL       = 54,
    D3DRENDERSTATE_STENCILPASS        = 55,
    D3DRENDERSTATE_STENCILFUNC        = 56,
    D3DRENDERSTATE_STENCILREF         = 57,
    D3DRENDERSTATE_STENCILMASK        = 58,
    D3DRENDERSTATE_STENCILWRITEMASK   = 59,
    D3DRENDERSTATE_TEXTUREFACTOR      = 60,

    D3DRENDERSTATE_STIPPLEPATTERN00   = 64,
    D3DRENDERSTATE_STIPPLEPATTERN01   = 65,
    D3DRENDERSTATE_STIPPLEPATTERN02   = 66,
    D3DRENDERSTATE_STIPPLEPATTERN03   = 67,
    D3DRENDERSTATE_STIPPLEPATTERN04   = 68,
    D3DRENDERSTATE_STIPPLEPATTERN05   = 69,
    D3DRENDERSTATE_STIPPLEPATTERN06   = 70,
    D3DRENDERSTATE_STIPPLEPATTERN07   = 71,
    D3DRENDERSTATE_STIPPLEPATTERN08   = 72,
    D3DRENDERSTATE_STIPPLEPATTERN09   = 73,
    D3DRENDERSTATE_STIPPLEPATTERN10   = 74,
    D3DRENDERSTATE_STIPPLEPATTERN11   = 75,
    D3DRENDERSTATE_STIPPLEPATTERN12   = 76,
    D3DRENDERSTATE_STIPPLEPATTERN13   = 77,
    D3DRENDERSTATE_STIPPLEPATTERN14   = 78,
    D3DRENDERSTATE_STIPPLEPATTERN15   = 79,
    D3DRENDERSTATE_STIPPLEPATTERN16   = 80,
    D3DRENDERSTATE_STIPPLEPATTERN17   = 81,
    D3DRENDERSTATE_STIPPLEPATTERN18   = 82,
    D3DRENDERSTATE_STIPPLEPATTERN19   = 83,
    D3DRENDERSTATE_STIPPLEPATTERN20   = 84,
    D3DRENDERSTATE_STIPPLEPATTERN21   = 85,
    D3DRENDERSTATE_STIPPLEPATTERN22   = 86,
    D3DRENDERSTATE_STIPPLEPATTERN23   = 87,
    D3DRENDERSTATE_STIPPLEPATTERN24   = 88,
    D3DRENDERSTATE_STIPPLEPATTERN25   = 89,
    D3DRENDERSTATE_STIPPLEPATTERN26   = 90,
    D3DRENDERSTATE_STIPPLEPATTERN27   = 91,
    D3DRENDERSTATE_STIPPLEPATTERN28   = 92,
    D3DRENDERSTATE_STIPPLEPATTERN29   = 93,
    D3DRENDERSTATE_STIPPLEPATTERN30   = 94,
    D3DRENDERSTATE_STIPPLEPATTERN31   = 95,

    D3DRENDERSTATE_WRAP0              = 128,
    D3DRENDERSTATE_WRAP1              = 129,
    D3DRENDERSTATE_WRAP2              = 130,
    D3DRENDERSTATE_WRAP3              = 131,
    D3DRENDERSTATE_WRAP4              = 132,
    D3DRENDERSTATE_WRAP5              = 133,
    D3DRENDERSTATE_WRAP6              = 134,
    D3DRENDERSTATE_WRAP7              = 135,
    /* d3d7 */
    D3DRENDERSTATE_CLIPPING            = 136,
    D3DRENDERSTATE_LIGHTING            = 137,
    D3DRENDERSTATE_EXTENTS             = 138,
    D3DRENDERSTATE_AMBIENT             = 139,
    D3DRENDERSTATE_FOGVERTEXMODE       = 140,
    D3DRENDERSTATE_COLORVERTEX         = 141,
    D3DRENDERSTATE_LOCALVIEWER         = 142,
    D3DRENDERSTATE_NORMALIZENORMALS    = 143,
    D3DRENDERSTATE_COLORKEYBLENDENABLE = 144,
    D3DRENDERSTATE_DIFFUSEMATERIALSOURCE    = 145,
    D3DRENDERSTATE_SPECULARMATERIALSOURCE   = 146,
    D3DRENDERSTATE_AMBIENTMATERIALSOURCE    = 147,
    D3DRENDERSTATE_EMISSIVEMATERIALSOURCE   = 148,
    D3DRENDERSTATE_VERTEXBLEND              = 151,
    D3DRENDERSTATE_CLIPPLANEENABLE          = 152,

    D3DRENDERSTATE_FORCE_DWORD        = 0x7fffffff

    /* FIXME: We have some retired values that are being reused for DirectX 7 */
} D3DRENDERSTATETYPE;

typedef enum _D3DMATERIALCOLORSOURCE
{
    D3DMCS_MATERIAL = 0,
    D3DMCS_COLOR1   = 1,
    D3DMCS_COLOR2   = 2,
    D3DMCS_FORCE_DWORD = 0x7fffffff
} D3DMATERIALCOLORSOURCE;

#define D3DRENDERSTATE_BLENDENABLE      D3DRENDERSTATE_ALPHABLENDENABLE
#define D3DRENDERSTATE_WRAPBIAS         __MSABI_LONG(128U)
#define D3DWRAP_U   __MSABI_LONG(0x00000001)
#define D3DWRAP_V   __MSABI_LONG(0x00000002)

#define D3DWRAPCOORD_0   __MSABI_LONG(0x00000001)
#define D3DWRAPCOORD_1   __MSABI_LONG(0x00000002)
#define D3DWRAPCOORD_2   __MSABI_LONG(0x00000004)
#define D3DWRAPCOORD_3   __MSABI_LONG(0x00000008)

#define D3DRENDERSTATE_STIPPLEPATTERN(y) (D3DRENDERSTATE_STIPPLEPATTERN00 + (y))

typedef struct _D3DSTATE {
    union {
        D3DTRANSFORMSTATETYPE dtstTransformStateType;
        D3DLIGHTSTATETYPE     dlstLightStateType;
        D3DRENDERSTATETYPE    drstRenderStateType;
    } DUMMYUNIONNAME1;
    union {
        DWORD                 dwArg[1];
        D3DVALUE              dvArg[1];
    } DUMMYUNIONNAME2;
} D3DSTATE, *LPD3DSTATE;

typedef struct _D3DMATRIXLOAD {
    D3DMATRIXHANDLE hDestMatrix;
    D3DMATRIXHANDLE hSrcMatrix;
} D3DMATRIXLOAD, *LPD3DMATRIXLOAD;

typedef struct _D3DMATRIXMULTIPLY {
    D3DMATRIXHANDLE hDestMatrix;
    D3DMATRIXHANDLE hSrcMatrix1;
    D3DMATRIXHANDLE hSrcMatrix2;
} D3DMATRIXMULTIPLY, *LPD3DMATRIXMULTIPLY;

typedef struct _D3DPROCESSVERTICES {
    DWORD dwFlags;
    WORD  wStart;
    WORD  wDest;
    DWORD dwCount;
    DWORD dwReserved;
} D3DPROCESSVERTICES, *LPD3DPROCESSVERTICES;

#define D3DPROCESSVERTICES_TRANSFORMLIGHT       __MSABI_LONG(0x00000000)
#define D3DPROCESSVERTICES_TRANSFORM            __MSABI_LONG(0x00000001)
#define D3DPROCESSVERTICES_COPY                 __MSABI_LONG(0x00000002)
#define D3DPROCESSVERTICES_OPMASK               __MSABI_LONG(0x00000007)

#define D3DPROCESSVERTICES_UPDATEEXTENTS        __MSABI_LONG(0x00000008)
#define D3DPROCESSVERTICES_NOCOLOR              __MSABI_LONG(0x00000010)

typedef enum _D3DTEXTURESTAGESTATETYPE
{
    D3DTSS_COLOROP        =  1,
    D3DTSS_COLORARG1      =  2,
    D3DTSS_COLORARG2      =  3,
    D3DTSS_ALPHAOP        =  4,
    D3DTSS_ALPHAARG1      =  5,
    D3DTSS_ALPHAARG2      =  6,
    D3DTSS_BUMPENVMAT00   =  7,
    D3DTSS_BUMPENVMAT01   =  8,
    D3DTSS_BUMPENVMAT10   =  9,
    D3DTSS_BUMPENVMAT11   = 10,
    D3DTSS_TEXCOORDINDEX  = 11,
    D3DTSS_ADDRESS        = 12,
    D3DTSS_ADDRESSU       = 13,
    D3DTSS_ADDRESSV       = 14,
    D3DTSS_BORDERCOLOR    = 15,
    D3DTSS_MAGFILTER      = 16,
    D3DTSS_MINFILTER      = 17,
    D3DTSS_MIPFILTER      = 18,
    D3DTSS_MIPMAPLODBIAS  = 19,
    D3DTSS_MAXMIPLEVEL    = 20,
    D3DTSS_MAXANISOTROPY  = 21,
    D3DTSS_BUMPENVLSCALE  = 22,
    D3DTSS_BUMPENVLOFFSET = 23,
    D3DTSS_TEXTURETRANSFORMFLAGS = 24,
    D3DTSS_FORCE_DWORD   = 0x7fffffff
} D3DTEXTURESTAGESTATETYPE;

#define D3DTSS_TCI_PASSTHRU                             0x00000000
#define D3DTSS_TCI_CAMERASPACENORMAL                    0x00010000
#define D3DTSS_TCI_CAMERASPACEPOSITION                  0x00020000
#define D3DTSS_TCI_CAMERASPACEREFLECTIONVECTOR          0x00030000

typedef enum _D3DTEXTUREOP
{
    D3DTOP_DISABLE    = 1,
    D3DTOP_SELECTARG1 = 2,
    D3DTOP_SELECTARG2 = 3,

    D3DTOP_MODULATE   = 4,
    D3DTOP_MODULATE2X = 5,
    D3DTOP_MODULATE4X = 6,

    D3DTOP_ADD          =  7,
    D3DTOP_ADDSIGNED    =  8,
    D3DTOP_ADDSIGNED2X  =  9,
    D3DTOP_SUBTRACT     = 10,
    D3DTOP_ADDSMOOTH    = 11,

    D3DTOP_BLENDDIFFUSEALPHA    = 12,
    D3DTOP_BLENDTEXTUREALPHA    = 13,
    D3DTOP_BLENDFACTORALPHA     = 14,
    D3DTOP_BLENDTEXTUREALPHAPM  = 15,
    D3DTOP_BLENDCURRENTALPHA    = 16,

    D3DTOP_PREMODULATE            = 17,
    D3DTOP_MODULATEALPHA_ADDCOLOR = 18,
    D3DTOP_MODULATECOLOR_ADDALPHA = 19,
    D3DTOP_MODULATEINVALPHA_ADDCOLOR = 20,
    D3DTOP_MODULATEINVCOLOR_ADDALPHA = 21,

    D3DTOP_BUMPENVMAP           = 22,
    D3DTOP_BUMPENVMAPLUMINANCE  = 23,
    D3DTOP_DOTPRODUCT3          = 24,

    D3DTOP_FORCE_DWORD = 0x7fffffff
} D3DTEXTUREOP;

#define D3DTA_SELECTMASK        0x0000000f
#define D3DTA_DIFFUSE           0x00000000
#define D3DTA_CURRENT           0x00000001
#define D3DTA_TEXTURE           0x00000002
#define D3DTA_TFACTOR           0x00000003
#define D3DTA_SPECULAR          0x00000004
#define D3DTA_COMPLEMENT        0x00000010
#define D3DTA_ALPHAREPLICATE    0x00000020

typedef enum _D3DTEXTUREMAGFILTER
{
    D3DTFG_POINT        = 1,
    D3DTFG_LINEAR       = 2,
    D3DTFG_FLATCUBIC    = 3,
    D3DTFG_GAUSSIANCUBIC = 4,
    D3DTFG_ANISOTROPIC  = 5,
    D3DTFG_FORCE_DWORD  = 0x7fffffff
} D3DTEXTUREMAGFILTER;

typedef enum _D3DTEXTUREMINFILTER
{
    D3DTFN_POINT        = 1,
    D3DTFN_LINEAR       = 2,
    D3DTFN_ANISOTROPIC  = 3,
    D3DTFN_FORCE_DWORD  = 0x7fffffff
} D3DTEXTUREMINFILTER;

typedef enum _D3DTEXTUREMIPFILTER
{
    D3DTFP_NONE         = 1,
    D3DTFP_POINT        = 2,
    D3DTFP_LINEAR       = 3,
    D3DTFP_FORCE_DWORD  = 0x7fffffff
} D3DTEXTUREMIPFILTER;

#define D3DTRIFLAG_START                        __MSABI_LONG(0x00000000)
#define D3DTRIFLAG_STARTFLAT(len) (len)
#define D3DTRIFLAG_ODD                          __MSABI_LONG(0x0000001e)
#define D3DTRIFLAG_EVEN                         __MSABI_LONG(0x0000001f)

#define D3DTRIFLAG_EDGEENABLE1                  __MSABI_LONG(0x00000100)
#define D3DTRIFLAG_EDGEENABLE2                  __MSABI_LONG(0x00000200)
#define D3DTRIFLAG_EDGEENABLE3                  __MSABI_LONG(0x00000400)
#define D3DTRIFLAG_EDGEENABLETRIANGLE \
(D3DTRIFLAG_EDGEENABLE1 | D3DTRIFLAG_EDGEENABLE2 | D3DTRIFLAG_EDGEENABLE3)

typedef struct _D3DTRIANGLE {
    union {
        WORD v1;
        WORD wV1;
    } DUMMYUNIONNAME1;
    union {
        WORD v2;
        WORD wV2;
    } DUMMYUNIONNAME2;
    union {
        WORD v3;
        WORD wV3;
    } DUMMYUNIONNAME3;
    WORD     wFlags;
} D3DTRIANGLE, *LPD3DTRIANGLE;

typedef struct _D3DLINE {
    union {
        WORD v1;
        WORD wV1;
    } DUMMYUNIONNAME1;
    union {
        WORD v2;
        WORD wV2;
    } DUMMYUNIONNAME2;
} D3DLINE, *LPD3DLINE;

typedef struct _D3DSPAN {
    WORD wCount;
    WORD wFirst;
} D3DSPAN, *LPD3DSPAN;

typedef struct _D3DPOINT {
    WORD wCount;
    WORD wFirst;
} D3DPOINT, *LPD3DPOINT;

typedef struct _D3DBRANCH {
    DWORD dwMask;
    DWORD dwValue;
    WINBOOL  bNegate;
    DWORD dwOffset;
} D3DBRANCH, *LPD3DBRANCH;

typedef struct _D3DSTATUS {
    DWORD   dwFlags;
    DWORD   dwStatus;
    D3DRECT drExtent;
} D3DSTATUS, *LPD3DSTATUS;

#define D3DSETSTATUS_STATUS   __MSABI_LONG(0x00000001)
#define D3DSETSTATUS_EXTENTS  __MSABI_LONG(0x00000002)
#define D3DSETSTATUS_ALL      (D3DSETSTATUS_STATUS | D3DSETSTATUS_EXTENTS)

typedef struct _D3DCLIPSTATUS {
    DWORD dwFlags;
    DWORD dwStatus;
    float minx, maxx;
    float miny, maxy;
    float minz, maxz;
} D3DCLIPSTATUS, *LPD3DCLIPSTATUS;

#define D3DCLIPSTATUS_STATUS        __MSABI_LONG(0x00000001)
#define D3DCLIPSTATUS_EXTENTS2      __MSABI_LONG(0x00000002)
#define D3DCLIPSTATUS_EXTENTS3      __MSABI_LONG(0x00000004)

typedef struct {
    DWORD        dwSize;
    DWORD        dwTrianglesDrawn;
    DWORD        dwLinesDrawn;
    DWORD        dwPointsDrawn;
    DWORD        dwSpansDrawn;
    DWORD        dwVerticesProcessed;
} D3DSTATS, *LPD3DSTATS;

#define D3DEXECUTE_CLIPPED       __MSABI_LONG(0x00000001)
#define D3DEXECUTE_UNCLIPPED     __MSABI_LONG(0x00000002)

typedef struct _D3DEXECUTEDATA {
    DWORD     dwSize;
    DWORD     dwVertexOffset;
    DWORD     dwVertexCount;
    DWORD     dwInstructionOffset;
    DWORD     dwInstructionLength;
    DWORD     dwHVertexOffset;
    D3DSTATUS dsStatus;
} D3DEXECUTEDATA, *LPD3DEXECUTEDATA;

#define D3DPAL_FREE 0x00
#define D3DPAL_READONLY 0x40
#define D3DPAL_RESERVED 0x80

typedef struct _D3DVERTEXBUFFERDESC {
    DWORD dwSize;
    DWORD dwCaps;
    DWORD dwFVF;
    DWORD dwNumVertices;
} D3DVERTEXBUFFERDESC, *LPD3DVERTEXBUFFERDESC;

#define D3DVBCAPS_SYSTEMMEMORY      __MSABI_LONG(0x00000800)
#define D3DVBCAPS_WRITEONLY         __MSABI_LONG(0x00010000)
#define D3DVBCAPS_OPTIMIZED         __MSABI_LONG(0x80000000)
#define D3DVBCAPS_DONOTCLIP         __MSABI_LONG(0x00000001)

#define D3DVOP_LIGHT       (1 << 10)
#define D3DVOP_TRANSFORM   (1 << 0)
#define D3DVOP_CLIP        (1 << 2)
#define D3DVOP_EXTENTS     (1 << 3)

#define D3DMAXNUMVERTICES    ((1<<16) - 1)

#define D3DMAXNUMPRIMITIVES  ((1<<16) - 1)

#define D3DPV_DONOTCOPYDATA (1 << 0)

#define D3DFVF_RESERVED0        0x001
#define D3DFVF_POSITION_MASK    0x00E
#define D3DFVF_XYZ              0x002
#define D3DFVF_XYZRHW           0x004
#define D3DFVF_XYZB1            0x006
#define D3DFVF_XYZB2            0x008
#define D3DFVF_XYZB3            0x00a
#define D3DFVF_XYZB4            0x00c
#define D3DFVF_XYZB5            0x00e

#define D3DFVF_NORMAL           0x010
#define D3DFVF_RESERVED1        0x020
#define D3DFVF_DIFFUSE          0x040
#define D3DFVF_SPECULAR         0x080
#define D3DFVF_TEXCOUNT_MASK    0xf00
#define D3DFVF_TEXCOUNT_SHIFT   8
#define D3DFVF_TEX0             0x000
#define D3DFVF_TEX1             0x100
#define D3DFVF_TEX2             0x200
#define D3DFVF_TEX3             0x300
#define D3DFVF_TEX4             0x400
#define D3DFVF_TEX5             0x500
#define D3DFVF_TEX6             0x600
#define D3DFVF_TEX7             0x700
#define D3DFVF_TEX8             0x800

#define D3DFVF_RESERVED2        0xf000

#define D3DFVF_VERTEX ( D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 )
#define D3DFVF_LVERTEX ( D3DFVF_XYZ | D3DFVF_RESERVED1 | D3DFVF_DIFFUSE | \
D3DFVF_SPECULAR | D3DFVF_TEX1 )
#define D3DFVF_TLVERTEX ( D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_SPECULAR | \
D3DFVF_TEX1 )

typedef struct _D3DDP_PTRSTRIDE
{
    void *lpvData;
    DWORD dwStride;
} D3DDP_PTRSTRIDE;

#define D3DDP_MAXTEXCOORD 8

typedef struct _D3DDRAWPRIMITIVESTRIDEDDATA  {
    D3DDP_PTRSTRIDE position;
    D3DDP_PTRSTRIDE normal;
    D3DDP_PTRSTRIDE diffuse;
    D3DDP_PTRSTRIDE specular;
    D3DDP_PTRSTRIDE textureCoords[D3DDP_MAXTEXCOORD];
} D3DDRAWPRIMITIVESTRIDEDDATA ,*LPD3DDRAWPRIMITIVESTRIDEDDATA;

#define D3DVIS_INSIDE_FRUSTUM       0
#define D3DVIS_INTERSECT_FRUSTUM    1
#define D3DVIS_OUTSIDE_FRUSTUM      2
#define D3DVIS_INSIDE_LEFT          0
#define D3DVIS_INTERSECT_LEFT       (1 << 2)
#define D3DVIS_OUTSIDE_LEFT         (2 << 2)
#define D3DVIS_INSIDE_RIGHT         0
#define D3DVIS_INTERSECT_RIGHT      (1 << 4)
#define D3DVIS_OUTSIDE_RIGHT        (2 << 4)
#define D3DVIS_INSIDE_TOP           0
#define D3DVIS_INTERSECT_TOP        (1 << 6)
#define D3DVIS_OUTSIDE_TOP          (2 << 6)
#define D3DVIS_INSIDE_BOTTOM        0
#define D3DVIS_INTERSECT_BOTTOM     (1 << 8)
#define D3DVIS_OUTSIDE_BOTTOM       (2 << 8)
#define D3DVIS_INSIDE_NEAR          0
#define D3DVIS_INTERSECT_NEAR       (1 << 10)
#define D3DVIS_OUTSIDE_NEAR         (2 << 10)
#define D3DVIS_INSIDE_FAR           0
#define D3DVIS_INTERSECT_FAR        (1 << 12)
#define D3DVIS_OUTSIDE_FAR          (2 << 12)

#define D3DVIS_MASK_FRUSTUM         (3 << 0)
#define D3DVIS_MASK_LEFT            (3 << 2)
#define D3DVIS_MASK_RIGHT           (3 << 4)
#define D3DVIS_MASK_TOP             (3 << 6)
#define D3DVIS_MASK_BOTTOM          (3 << 8)
#define D3DVIS_MASK_NEAR            (3 << 10)
#define D3DVIS_MASK_FAR             (3 << 12)

#define D3DDEVINFOID_TEXTUREMANAGER    1
#define D3DDEVINFOID_D3DTEXTUREMANAGER 2
#define D3DDEVINFOID_TEXTURING         3

typedef enum _D3DSTATEBLOCKTYPE
{
    D3DSBT_ALL           = 1,
    D3DSBT_PIXELSTATE    = 2,
    D3DSBT_VERTEXSTATE   = 3,
    D3DSBT_FORCE_DWORD   = 0xffffffff
} D3DSTATEBLOCKTYPE;

typedef enum _D3DVERTEXBLENDFLAGS
{
    D3DVBLEND_DISABLE  = 0,
    D3DVBLEND_1WEIGHT  = 1,
    D3DVBLEND_2WEIGHTS = 2,
    D3DVBLEND_3WEIGHTS = 3,
} D3DVERTEXBLENDFLAGS;

typedef enum _D3DTEXTURETRANSFORMFLAGS {
    D3DTTFF_DISABLE         = 0,
    D3DTTFF_COUNT1          = 1,
    D3DTTFF_COUNT2          = 2,
    D3DTTFF_COUNT3          = 3,
    D3DTTFF_COUNT4          = 4,
    D3DTTFF_PROJECTED       = 256,
    D3DTTFF_FORCE_DWORD     = 0x7fffffff
} D3DTEXTURETRANSFORMFLAGS;

#define D3DFVF_TEXTUREFORMAT2 0
#define D3DFVF_TEXTUREFORMAT1 3
#define D3DFVF_TEXTUREFORMAT3 1
#define D3DFVF_TEXTUREFORMAT4 2

#define D3DFVF_TEXCOORDSIZE3(CoordIndex) (D3DFVF_TEXTUREFORMAT3 << (CoordIndex*2 + 16))
#define D3DFVF_TEXCOORDSIZE2(CoordIndex) (D3DFVF_TEXTUREFORMAT2)
#define D3DFVF_TEXCOORDSIZE4(CoordIndex) (D3DFVF_TEXTUREFORMAT4 << (CoordIndex*2 + 16))
#define D3DFVF_TEXCOORDSIZE1(CoordIndex) (D3DFVF_TEXTUREFORMAT1 << (CoordIndex*2 + 16))

#ifdef __i386__
#include <poppack.h>
#endif

#endif



#include <d3dcaps.h>

/*****************************************************************************
 * Predeclare the interfaces
 */
DEFINE_GUID(IID_IDirect3D,              0x3BBA0080,0x2421,0x11CF,0xA3,0x1A,0x00,0xAA,0x00,0xB9,0x33,0x56);
DEFINE_GUID(IID_IDirect3D2,             0x6aae1ec1,0x662a,0x11d0,0x88,0x9d,0x00,0xaa,0x00,0xbb,0xb7,0x6a);
DEFINE_GUID(IID_IDirect3D3,             0xbb223240,0xe72b,0x11d0,0xa9,0xb4,0x00,0xaa,0x00,0xc0,0x99,0x3e);
DEFINE_GUID(IID_IDirect3D7,             0xf5049e77,0x4861,0x11d2,0xa4,0x07,0x00,0xa0,0xc9,0x06,0x29,0xa8);

DEFINE_GUID(IID_IDirect3DRampDevice,	0xF2086B20,0x259F,0x11CF,0xA3,0x1A,0x00,0xAA,0x00,0xB9,0x33,0x56);
DEFINE_GUID(IID_IDirect3DRGBDevice,	0xA4665C60,0x2673,0x11CF,0xA3,0x1A,0x00,0xAA,0x00,0xB9,0x33,0x56);
DEFINE_GUID(IID_IDirect3DHALDevice,	0x84E63dE0,0x46AA,0x11CF,0x81,0x6F,0x00,0x00,0xC0,0x20,0x15,0x6E);
DEFINE_GUID(IID_IDirect3DMMXDevice,	0x881949a1,0xd6f3,0x11d0,0x89,0xab,0x00,0xa0,0xc9,0x05,0x41,0x29);
DEFINE_GUID(IID_IDirect3DRefDevice,     0x50936643,0x13e9,0x11d1,0x89,0xaa,0x00,0xa0,0xc9,0x05,0x41,0x29);
DEFINE_GUID(IID_IDirect3DTnLHalDevice,  0xf5049e78,0x4861,0x11d2,0xa4,0x07,0x00,0xa0,0xc9,0x06,0x29,0xa8);
DEFINE_GUID(IID_IDirect3DNullDevice,    0x8767df22,0xbacc,0x11d1,0x89,0x69,0x00,0xa0,0xc9,0x06,0x29,0xa8);

DEFINE_GUID(IID_IDirect3DDevice,	0x64108800,0x957d,0x11D0,0x89,0xAB,0x00,0xA0,0xC9,0x05,0x41,0x29);
DEFINE_GUID(IID_IDirect3DDevice2,	0x93281501,0x8CF8,0x11D0,0x89,0xAB,0x00,0xA0,0xC9,0x05,0x41,0x29);
DEFINE_GUID(IID_IDirect3DDevice3,       0xb0ab3b60,0x33d7,0x11d1,0xa9,0x81,0x00,0xc0,0x4f,0xd7,0xb1,0x74);
DEFINE_GUID(IID_IDirect3DDevice7,       0xf5049e79,0x4861,0x11d2,0xa4,0x07,0x00,0xa0,0xc9,0x06,0x29,0xa8);

DEFINE_GUID(IID_IDirect3DTexture,	0x2CDCD9E0,0x25A0,0x11CF,0xA3,0x1A,0x00,0xAA,0x00,0xB9,0x33,0x56);
DEFINE_GUID(IID_IDirect3DTexture2,	0x93281502,0x8CF8,0x11D0,0x89,0xAB,0x00,0xA0,0xC9,0x05,0x41,0x29);

DEFINE_GUID(IID_IDirect3DLight,		0x4417C142,0x33AD,0x11CF,0x81,0x6F,0x00,0x00,0xC0,0x20,0x15,0x6E);

DEFINE_GUID(IID_IDirect3DMaterial,	0x4417C144,0x33AD,0x11CF,0x81,0x6F,0x00,0x00,0xC0,0x20,0x15,0x6E);
DEFINE_GUID(IID_IDirect3DMaterial2,	0x93281503,0x8CF8,0x11D0,0x89,0xAB,0x00,0xA0,0xC9,0x05,0x41,0x29);
DEFINE_GUID(IID_IDirect3DMaterial3,     0xca9c46f4,0xd3c5,0x11d1,0xb7,0x5a,0x00,0x60,0x08,0x52,0xb3,0x12);

DEFINE_GUID(IID_IDirect3DExecuteBuffer,	0x4417C145,0x33AD,0x11CF,0x81,0x6F,0x00,0x00,0xC0,0x20,0x15,0x6E);

DEFINE_GUID(IID_IDirect3DViewport,	0x4417C146,0x33AD,0x11CF,0x81,0x6F,0x00,0x00,0xC0,0x20,0x15,0x6E);
DEFINE_GUID(IID_IDirect3DViewport2,	0x93281500,0x8CF8,0x11D0,0x89,0xAB,0x00,0xA0,0xC9,0x05,0x41,0x29);
DEFINE_GUID(IID_IDirect3DViewport3,     0xb0ab3b61,0x33d7,0x11d1,0xa9,0x81,0x00,0xc0,0x4f,0xd7,0xb1,0x74);

DEFINE_GUID(IID_IDirect3DVertexBuffer,  0x7a503555,0x4a83,0x11d1,0xa5,0xdb,0x00,0xa0,0xc9,0x03,0x67,0xf8);
DEFINE_GUID(IID_IDirect3DVertexBuffer7, 0xf5049e7d,0x4861,0x11d2,0xa4,0x07,0x00,0xa0,0xc9,0x06,0x29,0xa8);


typedef struct IDirect3D *LPDIRECT3D;
typedef struct IDirect3D2 *LPDIRECT3D2;
typedef struct IDirect3D3 *LPDIRECT3D3;
typedef struct IDirect3D7 *LPDIRECT3D7;

typedef struct IDirect3DLight *LPDIRECT3DLIGHT;

typedef struct IDirect3DDevice *LPDIRECT3DDEVICE;
typedef struct IDirect3DDevice2 *LPDIRECT3DDEVICE2;
typedef struct IDirect3DDevice3 *LPDIRECT3DDEVICE3;
typedef struct IDirect3DDevice7 *LPDIRECT3DDEVICE7;

typedef struct IDirect3DViewport *LPDIRECT3DVIEWPORT;
typedef struct IDirect3DViewport2 *LPDIRECT3DVIEWPORT2;
typedef struct IDirect3DViewport3 *LPDIRECT3DVIEWPORT3;

typedef struct IDirect3DMaterial *LPDIRECT3DMATERIAL;
typedef struct IDirect3DMaterial2 *LPDIRECT3DMATERIAL2;
typedef struct IDirect3DMaterial3 *LPDIRECT3DMATERIAL3;

typedef struct IDirect3DTexture *LPDIRECT3DTEXTURE;
typedef struct IDirect3DTexture2 *LPDIRECT3DTEXTURE2;

typedef struct IDirect3DExecuteBuffer *LPDIRECT3DEXECUTEBUFFER;

typedef struct IDirect3DVertexBuffer *LPDIRECT3DVERTEXBUFFER;
typedef struct IDirect3DVertexBuffer7 *LPDIRECT3DVERTEXBUFFER7;

/* ********************************************************************
 *   Error Codes
 ******************************************************************** */
#define D3D_OK                          DD_OK
#define D3DERR_BADMAJORVERSION          MAKE_DDHRESULT(700)
#define D3DERR_BADMINORVERSION          MAKE_DDHRESULT(701)
#define D3DERR_INVALID_DEVICE           MAKE_DDHRESULT(705)
#define D3DERR_INITFAILED               MAKE_DDHRESULT(706)
#define D3DERR_DEVICEAGGREGATED         MAKE_DDHRESULT(707)
#define D3DERR_EXECUTE_CREATE_FAILED    MAKE_DDHRESULT(710)
#define D3DERR_EXECUTE_DESTROY_FAILED   MAKE_DDHRESULT(711)
#define D3DERR_EXECUTE_LOCK_FAILED      MAKE_DDHRESULT(712)
#define D3DERR_EXECUTE_UNLOCK_FAILED    MAKE_DDHRESULT(713)
#define D3DERR_EXECUTE_LOCKED           MAKE_DDHRESULT(714)
#define D3DERR_EXECUTE_NOT_LOCKED       MAKE_DDHRESULT(715)
#define D3DERR_EXECUTE_FAILED           MAKE_DDHRESULT(716)
#define D3DERR_EXECUTE_CLIPPED_FAILED   MAKE_DDHRESULT(717)
#define D3DERR_TEXTURE_NO_SUPPORT       MAKE_DDHRESULT(720)
#define D3DERR_TEXTURE_CREATE_FAILED    MAKE_DDHRESULT(721)
#define D3DERR_TEXTURE_DESTROY_FAILED   MAKE_DDHRESULT(722)
#define D3DERR_TEXTURE_LOCK_FAILED      MAKE_DDHRESULT(723)
#define D3DERR_TEXTURE_UNLOCK_FAILED    MAKE_DDHRESULT(724)
#define D3DERR_TEXTURE_LOAD_FAILED      MAKE_DDHRESULT(725)
#define D3DERR_TEXTURE_SWAP_FAILED      MAKE_DDHRESULT(726)
#define D3DERR_TEXTURE_LOCKED           MAKE_DDHRESULT(727)
#define D3DERR_TEXTURE_NOT_LOCKED       MAKE_DDHRESULT(728)
#define D3DERR_TEXTURE_GETSURF_FAILED   MAKE_DDHRESULT(729)
#define D3DERR_MATRIX_CREATE_FAILED     MAKE_DDHRESULT(730)
#define D3DERR_MATRIX_DESTROY_FAILED    MAKE_DDHRESULT(731)
#define D3DERR_MATRIX_SETDATA_FAILED    MAKE_DDHRESULT(732)
#define D3DERR_MATRIX_GETDATA_FAILED    MAKE_DDHRESULT(733)
#define D3DERR_SETVIEWPORTDATA_FAILED   MAKE_DDHRESULT(734)
#define D3DERR_INVALIDCURRENTVIEWPORT   MAKE_DDHRESULT(735)
#define D3DERR_INVALIDPRIMITIVETYPE     MAKE_DDHRESULT(736)
#define D3DERR_INVALIDVERTEXTYPE        MAKE_DDHRESULT(737)
#define D3DERR_TEXTURE_BADSIZE          MAKE_DDHRESULT(738)
#define D3DERR_INVALIDRAMPTEXTURE       MAKE_DDHRESULT(739)
#define D3DERR_MATERIAL_CREATE_FAILED   MAKE_DDHRESULT(740)
#define D3DERR_MATERIAL_DESTROY_FAILED  MAKE_DDHRESULT(741)
#define D3DERR_MATERIAL_SETDATA_FAILED  MAKE_DDHRESULT(742)
#define D3DERR_MATERIAL_GETDATA_FAILED  MAKE_DDHRESULT(743)
#define D3DERR_INVALIDPALETTE           MAKE_DDHRESULT(744)
#define D3DERR_ZBUFF_NEEDS_SYSTEMMEMORY MAKE_DDHRESULT(745)
#define D3DERR_ZBUFF_NEEDS_VIDEOMEMORY  MAKE_DDHRESULT(746)
#define D3DERR_SURFACENOTINVIDMEM       MAKE_DDHRESULT(747)
#define D3DERR_LIGHT_SET_FAILED         MAKE_DDHRESULT(750)
#define D3DERR_LIGHTHASVIEWPORT         MAKE_DDHRESULT(751)
#define D3DERR_LIGHTNOTINTHISVIEWPORT   MAKE_DDHRESULT(752)
#define D3DERR_SCENE_IN_SCENE           MAKE_DDHRESULT(760)
#define D3DERR_SCENE_NOT_IN_SCENE       MAKE_DDHRESULT(761)
#define D3DERR_SCENE_BEGIN_FAILED       MAKE_DDHRESULT(762)
#define D3DERR_SCENE_END_FAILED         MAKE_DDHRESULT(763)
#define D3DERR_INBEGIN                  MAKE_DDHRESULT(770)
#define D3DERR_NOTINBEGIN               MAKE_DDHRESULT(771)
#define D3DERR_NOVIEWPORTS              MAKE_DDHRESULT(772)
#define D3DERR_VIEWPORTDATANOTSET       MAKE_DDHRESULT(773)
#define D3DERR_VIEWPORTHASNODEVICE      MAKE_DDHRESULT(774)
#define D3DERR_NOCURRENTVIEWPORT        MAKE_DDHRESULT(775)
#define D3DERR_INVALIDVERTEXFORMAT	MAKE_DDHRESULT(2048)
#define D3DERR_COLORKEYATTACHED         MAKE_DDHRESULT(2050)
#define D3DERR_VERTEXBUFFEROPTIMIZED	MAKE_DDHRESULT(2060)
#define D3DERR_VBUF_CREATE_FAILED	MAKE_DDHRESULT(2061)
#define D3DERR_VERTEXBUFFERLOCKED	MAKE_DDHRESULT(2062)
#define D3DERR_VERTEXBUFFERUNLOCKFAILED	MAKE_DDHRESULT(2063)
#define D3DERR_ZBUFFER_NOTPRESENT	MAKE_DDHRESULT(2070)
#define D3DERR_STENCILBUFFER_NOTPRESENT	MAKE_DDHRESULT(2071)

#define D3DERR_WRONGTEXTUREFORMAT		MAKE_DDHRESULT(2072)
#define D3DERR_UNSUPPORTEDCOLOROPERATION	MAKE_DDHRESULT(2073)
#define D3DERR_UNSUPPORTEDCOLORARG		MAKE_DDHRESULT(2074)
#define D3DERR_UNSUPPORTEDALPHAOPERATION	MAKE_DDHRESULT(2075)
#define D3DERR_UNSUPPORTEDALPHAARG		MAKE_DDHRESULT(2076)
#define D3DERR_TOOMANYOPERATIONS		MAKE_DDHRESULT(2077)
#define D3DERR_CONFLICTINGTEXTUREFILTER		MAKE_DDHRESULT(2078)
#define D3DERR_UNSUPPORTEDFACTORVALUE		MAKE_DDHRESULT(2079)
#define D3DERR_CONFLICTINGRENDERSTATE		MAKE_DDHRESULT(2081)
#define D3DERR_UNSUPPORTEDTEXTUREFILTER		MAKE_DDHRESULT(2082)
#define D3DERR_TOOMANYPRIMITIVES		MAKE_DDHRESULT(2083)
#define D3DERR_INVALIDMATRIX			MAKE_DDHRESULT(2084)
#define D3DERR_TOOMANYVERTICES			MAKE_DDHRESULT(2085)
#define D3DERR_CONFLICTINGTEXTUREPALETTE	MAKE_DDHRESULT(2086)

#define D3DERR_INVALIDSTATEBLOCK	MAKE_DDHRESULT(2100)
#define D3DERR_INBEGINSTATEBLOCK	MAKE_DDHRESULT(2101)
#define D3DERR_NOTINBEGINSTATEBLOCK	MAKE_DDHRESULT(2102)

/* ********************************************************************
 *   Enums
 ******************************************************************** */
#define D3DNEXT_NEXT __MSABI_LONG(0x01)
#define D3DNEXT_HEAD __MSABI_LONG(0x02)
#define D3DNEXT_TAIL __MSABI_LONG(0x04)

#define D3DDP_WAIT               __MSABI_LONG(0x00000001)
#define D3DDP_OUTOFORDER         __MSABI_LONG(0x00000002)
#define D3DDP_DONOTCLIP          __MSABI_LONG(0x00000004)
#define D3DDP_DONOTUPDATEEXTENTS __MSABI_LONG(0x00000008)
#define D3DDP_DONOTLIGHT         __MSABI_LONG(0x00000010)

/* ********************************************************************
 *   Types and structures
 ******************************************************************** */
typedef DWORD D3DVIEWPORTHANDLE, *LPD3DVIEWPORTHANDLE;


/*****************************************************************************
 * IDirect3D interface
 */
#undef INTERFACE
#define INTERFACE IDirect3D
DECLARE_INTERFACE_(IDirect3D,IUnknown)
{
    /*** IUnknown methods ***/
    STDMETHOD_(HRESULT,QueryInterface)(THIS_ REFIID riid, void** ppvObject) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;
    /*** IDirect3D methods ***/
    STDMETHOD(Initialize)(THIS_ REFIID riid) PURE;
    STDMETHOD(EnumDevices)(THIS_ LPD3DENUMDEVICESCALLBACK cb, void *ctx) PURE;
    STDMETHOD(CreateLight)(THIS_ struct IDirect3DLight **light, IUnknown *outer) PURE;
    STDMETHOD(CreateMaterial)(THIS_ struct IDirect3DMaterial **material, IUnknown *outer) PURE;
    STDMETHOD(CreateViewport)(THIS_ struct IDirect3DViewport **viewport, IUnknown *outer) PURE;
    STDMETHOD(FindDevice)(THIS_ D3DFINDDEVICESEARCH *search, D3DFINDDEVICERESULT *result) PURE;
};
#undef INTERFACE

#if !defined(__cplusplus) || defined(CINTERFACE)
/*** IUnknown methods ***/
#define IDirect3D_QueryInterface(p,a,b) (p)->lpVtbl->QueryInterface(p,a,b)
#define IDirect3D_AddRef(p)             (p)->lpVtbl->AddRef(p)
#define IDirect3D_Release(p)            (p)->lpVtbl->Release(p)
/*** IDirect3D methods ***/
#define IDirect3D_Initialize(p,a)       (p)->lpVtbl->Initialize(p,a)
#define IDirect3D_EnumDevices(p,a,b)    (p)->lpVtbl->EnumDevices(p,a,b)
#define IDirect3D_CreateLight(p,a,b)    (p)->lpVtbl->CreateLight(p,a,b)
#define IDirect3D_CreateMaterial(p,a,b) (p)->lpVtbl->CreateMaterial(p,a,b)
#define IDirect3D_CreateViewport(p,a,b) (p)->lpVtbl->CreateViewport(p,a,b)
#define IDirect3D_FindDevice(p,a,b)     (p)->lpVtbl->FindDevice(p,a,b)
#else
/*** IUnknown methods ***/
#define IDirect3D_QueryInterface(p,a,b) (p)->QueryInterface(a,b)
#define IDirect3D_AddRef(p)             (p)->AddRef()
#define IDirect3D_Release(p)            (p)->Release()
/*** IDirect3D methods ***/
#define IDirect3D_Initialize(p,a)       (p)->Initialize(a)
#define IDirect3D_EnumDevices(p,a,b)    (p)->EnumDevices(a,b)
#define IDirect3D_CreateLight(p,a,b)    (p)->CreateLight(a,b)
#define IDirect3D_CreateMaterial(p,a,b) (p)->CreateMaterial(a,b)
#define IDirect3D_CreateViewport(p,a,b) (p)->CreateViewport(a,b)
#define IDirect3D_FindDevice(p,a,b)     (p)->FindDevice(a,b)
#endif


/*****************************************************************************
 * IDirect3D2 interface
 */
#define INTERFACE IDirect3D2
DECLARE_INTERFACE_(IDirect3D2,IUnknown)
{
    /*** IUnknown methods ***/
    STDMETHOD_(HRESULT,QueryInterface)(THIS_ REFIID riid, void** ppvObject) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;
    /*** IDirect3D2 methods ***/
    STDMETHOD(EnumDevices)(THIS_ LPD3DENUMDEVICESCALLBACK cb, void *ctx) PURE;
    STDMETHOD(CreateLight)(THIS_ struct IDirect3DLight **light, IUnknown *outer) PURE;
    STDMETHOD(CreateMaterial)(THIS_ struct IDirect3DMaterial2 **material, IUnknown *outer) PURE;
    STDMETHOD(CreateViewport)(THIS_ struct IDirect3DViewport2 **viewport, IUnknown *outer) PURE;
    STDMETHOD(FindDevice)(THIS_ D3DFINDDEVICESEARCH *search, D3DFINDDEVICERESULT *result) PURE;
    STDMETHOD(CreateDevice)(THIS_ REFCLSID rclsid, IDirectDrawSurface *surface,
                            struct IDirect3DDevice2 **device) PURE;
};
#undef INTERFACE

#if !defined(__cplusplus) || defined(CINTERFACE)
/*** IUnknown methods ***/
#define IDirect3D2_QueryInterface(p,a,b) (p)->lpVtbl->QueryInterface(p,a,b)
#define IDirect3D2_AddRef(p)             (p)->lpVtbl->AddRef(p)
#define IDirect3D2_Release(p)            (p)->lpVtbl->Release(p)
/*** IDirect3D2 methods ***/
#define IDirect3D2_EnumDevices(p,a,b)    (p)->lpVtbl->EnumDevices(p,a,b)
#define IDirect3D2_CreateLight(p,a,b)    (p)->lpVtbl->CreateLight(p,a,b)
#define IDirect3D2_CreateMaterial(p,a,b) (p)->lpVtbl->CreateMaterial(p,a,b)
#define IDirect3D2_CreateViewport(p,a,b) (p)->lpVtbl->CreateViewport(p,a,b)
#define IDirect3D2_FindDevice(p,a,b)     (p)->lpVtbl->FindDevice(p,a,b)
#define IDirect3D2_CreateDevice(p,a,b,c) (p)->lpVtbl->CreateDevice(p,a,b,c)
#else
/*** IUnknown methods ***/
#define IDirect3D2_QueryInterface(p,a,b) (p)->QueryInterface(a,b)
#define IDirect3D2_AddRef(p)             (p)->AddRef()
#define IDirect3D2_Release(p)            (p)->Release()
/*** IDirect3D2 methods ***/
#define IDirect3D2_EnumDevices(p,a,b)    (p)->EnumDevices(a,b)
#define IDirect3D2_CreateLight(p,a,b)    (p)->CreateLight(a,b)
#define IDirect3D2_CreateMaterial(p,a,b) (p)->CreateMaterial(a,b)
#define IDirect3D2_CreateViewport(p,a,b) (p)->CreateViewport(a,b)
#define IDirect3D2_FindDevice(p,a,b)     (p)->FindDevice(a,b)
#define IDirect3D2_CreateDevice(p,a,b,c) (p)->CreateDevice(a,b,c)
#endif


/*****************************************************************************
 * IDirect3D3 interface
 */
#define INTERFACE IDirect3D3
DECLARE_INTERFACE_(IDirect3D3,IUnknown)
{
    /*** IUnknown methods ***/
    STDMETHOD_(HRESULT,QueryInterface)(THIS_ REFIID riid, void** ppvObject) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;
    /*** IDirect3D3 methods ***/
    STDMETHOD(EnumDevices)(THIS_ LPD3DENUMDEVICESCALLBACK cb, void *ctx) PURE;
    STDMETHOD(CreateLight)(THIS_ struct IDirect3DLight **light, IUnknown *outer) PURE;
    STDMETHOD(CreateMaterial)(THIS_ struct IDirect3DMaterial3 **material, IUnknown *outer) PURE;
    STDMETHOD(CreateViewport)(THIS_ struct IDirect3DViewport3 **viewport, IUnknown *outer) PURE;
    STDMETHOD(FindDevice)(THIS_ D3DFINDDEVICESEARCH *search, D3DFINDDEVICERESULT *result) PURE;
    STDMETHOD(CreateDevice)(THIS_ REFCLSID rclsid, IDirectDrawSurface4 *surface,
                            struct IDirect3DDevice3 **device, IUnknown *outer) PURE;
                            STDMETHOD(CreateVertexBuffer)(THIS_ D3DVERTEXBUFFERDESC *desc, struct IDirect3DVertexBuffer **buffer,
                                                          DWORD flags, IUnknown *outer) PURE;
                                                          STDMETHOD(EnumZBufferFormats)(THIS_ REFCLSID device_iid, LPD3DENUMPIXELFORMATSCALLBACK cb, void *ctx) PURE;
                                                          STDMETHOD(EvictManagedTextures)(THIS) PURE;
};
#undef INTERFACE

#if !defined(__cplusplus) || defined(CINTERFACE)
/*** IUnknown methods ***/
#define IDirect3D3_QueryInterface(p,a,b) (p)->lpVtbl->QueryInterface(p,a,b)
#define IDirect3D3_AddRef(p)             (p)->lpVtbl->AddRef(p)
#define IDirect3D3_Release(p)            (p)->lpVtbl->Release(p)
/*** IDirect3D3 methods ***/
#define IDirect3D3_EnumDevices(p,a,b)            (p)->lpVtbl->EnumDevices(p,a,b)
#define IDirect3D3_CreateLight(p,a,b)            (p)->lpVtbl->CreateLight(p,a,b)
#define IDirect3D3_CreateMaterial(p,a,b)         (p)->lpVtbl->CreateMaterial(p,a,b)
#define IDirect3D3_CreateViewport(p,a,b)         (p)->lpVtbl->CreateViewport(p,a,b)
#define IDirect3D3_FindDevice(p,a,b)             (p)->lpVtbl->FindDevice(p,a,b)
#define IDirect3D3_CreateDevice(p,a,b,c,d)       (p)->lpVtbl->CreateDevice(p,a,b,c,d)
#define IDirect3D3_CreateVertexBuffer(p,a,b,c,d) (p)->lpVtbl->CreateVertexBuffer(p,a,b,c,d)
#define IDirect3D3_EnumZBufferFormats(p,a,b,c)   (p)->lpVtbl->EnumZBufferFormats(p,a,b,c)
#define IDirect3D3_EvictManagedTextures(p)       (p)->lpVtbl->EvictManagedTextures(p)
#else
/*** IUnknown methods ***/
#define IDirect3D3_QueryInterface(p,a,b) (p)->QueryInterface(a,b)
#define IDirect3D3_AddRef(p)             (p)->AddRef()
#define IDirect3D3_Release(p)            (p)->Release()
/*** IDirect3D3 methods ***/
#define IDirect3D3_EnumDevices(p,a,b)            (p)->EnumDevices(a,b)
#define IDirect3D3_CreateLight(p,a,b)            (p)->CreateLight(a,b)
#define IDirect3D3_CreateMaterial(p,a,b)         (p)->CreateMaterial(a,b)
#define IDirect3D3_CreateViewport(p,a,b)         (p)->CreateViewport(a,b)
#define IDirect3D3_FindDevice(p,a,b)             (p)->FindDevice(a,b)
#define IDirect3D3_CreateDevice(p,a,b,c,d)       (p)->CreateDevice(a,b,c,d)
#define IDirect3D3_CreateVertexBuffer(p,a,b,c,d) (p)->CreateVertexBuffer(a,b,c,d)
#define IDirect3D3_EnumZBufferFormats(p,a,b,c)   (p)->EnumZBufferFormats(a,b,c)
#define IDirect3D3_EvictManagedTextures(p)       (p)->EvictManagedTextures()
#endif

/*****************************************************************************
 * IDirect3D7 interface
 */
#define INTERFACE IDirect3D7
DECLARE_INTERFACE_(IDirect3D7,IUnknown)
{
    /*** IUnknown methods ***/
    STDMETHOD_(HRESULT,QueryInterface)(THIS_ REFIID riid, void** ppvObject) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;
    /*** IDirect3D7 methods ***/
    STDMETHOD(EnumDevices)(THIS_ LPD3DENUMDEVICESCALLBACK7 cb, void *ctx) PURE;
    STDMETHOD(CreateDevice)(THIS_ REFCLSID rclsid, IDirectDrawSurface7 *surface,
                            struct IDirect3DDevice7 **device) PURE;
                            STDMETHOD(CreateVertexBuffer)(THIS_ D3DVERTEXBUFFERDESC *desc,
                                                          struct IDirect3DVertexBuffer7 **buffer, DWORD flags) PURE;
                                                          STDMETHOD(EnumZBufferFormats)(THIS_ REFCLSID device_iid, LPD3DENUMPIXELFORMATSCALLBACK cb, void *ctx) PURE;
                                                          STDMETHOD(EvictManagedTextures)(THIS) PURE;
};
#undef INTERFACE

#if !defined(__cplusplus) || defined(CINTERFACE)
/*** IUnknown methods ***/
#define IDirect3D7_QueryInterface(p,a,b) (p)->lpVtbl->QueryInterface(p,a,b)
#define IDirect3D7_AddRef(p)             (p)->lpVtbl->AddRef(p)
#define IDirect3D7_Release(p)            (p)->lpVtbl->Release(p)
/*** IDirect3D3 methods ***/
#define IDirect3D7_EnumDevices(p,a,b)            (p)->lpVtbl->EnumDevices(p,a,b)
#define IDirect3D7_CreateDevice(p,a,b,c)         (p)->lpVtbl->CreateDevice(p,a,b,c)
#define IDirect3D7_CreateVertexBuffer(p,a,b,c)   (p)->lpVtbl->CreateVertexBuffer(p,a,b,c)
#define IDirect3D7_EnumZBufferFormats(p,a,b,c)   (p)->lpVtbl->EnumZBufferFormats(p,a,b,c)
#define IDirect3D7_EvictManagedTextures(p)       (p)->lpVtbl->EvictManagedTextures(p)
#else
/*** IUnknown methods ***/
#define IDirect3D7_QueryInterface(p,a,b) (p)->QueryInterface(a,b)
#define IDirect3D7_AddRef(p)             (p)->AddRef()
#define IDirect3D7_Release(p)            (p)->Release()
/*** IDirect3D3 methods ***/
#define IDirect3D7_EnumDevices(p,a,b)            (p)->EnumDevices(a,b)
#define IDirect3D7_CreateDevice(p,a,b,c)         (p)->CreateDevice(a,b,c)
#define IDirect3D7_CreateVertexBuffer(p,a,b,c)   (p)->CreateVertexBuffer(a,b,c)
#define IDirect3D7_EnumZBufferFormats(p,a,b,c)   (p)->EnumZBufferFormats(a,b,c)
#define IDirect3D7_EvictManagedTextures(p)       (p)->EvictManagedTextures()
#endif


/*****************************************************************************
 * IDirect3DLight interface
 */
#define INTERFACE IDirect3DLight
DECLARE_INTERFACE_(IDirect3DLight,IUnknown)
{
    /*** IUnknown methods ***/
    STDMETHOD_(HRESULT,QueryInterface)(THIS_ REFIID riid, void** ppvObject) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;
    /*** IDirect3DLight methods ***/
    STDMETHOD(Initialize)(THIS_ IDirect3D *d3d) PURE;
    STDMETHOD(SetLight)(THIS_ D3DLIGHT *data) PURE;
    STDMETHOD(GetLight)(THIS_ D3DLIGHT *data) PURE;
};
#undef INTERFACE

#if !defined(__cplusplus) || defined(CINTERFACE)
/*** IUnknown methods ***/
#define IDirect3DLight_QueryInterface(p,a,b) (p)->lpVtbl->QueryInterface(p,a,b)
#define IDirect3DLight_AddRef(p)             (p)->lpVtbl->AddRef(p)
#define IDirect3DLight_Release(p)            (p)->lpVtbl->Release(p)
/*** IDirect3DLight methods ***/
#define IDirect3DLight_Initialize(p,a) (p)->lpVtbl->Initialize(p,a)
#define IDirect3DLight_SetLight(p,a)   (p)->lpVtbl->SetLight(p,a)
#define IDirect3DLight_GetLight(p,a)   (p)->lpVtbl->GetLight(p,a)
#else
/*** IUnknown methods ***/
#define IDirect3DLight_QueryInterface(p,a,b) (p)->QueryInterface(a,b)
#define IDirect3DLight_AddRef(p)             (p)->AddRef()
#define IDirect3DLight_Release(p)            (p)->Release()
/*** IDirect3DLight methods ***/
#define IDirect3DLight_Initialize(p,a) (p)->Initialize(a)
#define IDirect3DLight_SetLight(p,a)   (p)->SetLight(a)
#define IDirect3DLight_GetLight(p,a)   (p)->GetLight(a)
#endif


/*****************************************************************************
 * IDirect3DMaterial interface
 */
#define INTERFACE IDirect3DMaterial
DECLARE_INTERFACE_(IDirect3DMaterial,IUnknown)
{
    /*** IUnknown methods ***/
    STDMETHOD_(HRESULT,QueryInterface)(THIS_ REFIID riid, void** ppvObject) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;
    /*** IDirect3DMaterial methods ***/
    STDMETHOD(Initialize)(THIS_ IDirect3D *d3d) PURE;
    STDMETHOD(SetMaterial)(THIS_ D3DMATERIAL *data) PURE;
    STDMETHOD(GetMaterial)(THIS_ D3DMATERIAL *data) PURE;
    STDMETHOD(GetHandle)(THIS_ struct IDirect3DDevice *device, D3DMATERIALHANDLE *handle) PURE;
    STDMETHOD(Reserve)(THIS) PURE;
    STDMETHOD(Unreserve)(THIS) PURE;
};
#undef INTERFACE

#if !defined(__cplusplus) || defined(CINTERFACE)
/*** IUnknown methods ***/
#define IDirect3DMaterial_QueryInterface(p,a,b) (p)->lpVtbl->QueryInterface(p,a,b)
#define IDirect3DMaterial_AddRef(p)             (p)->lpVtbl->AddRef(p)
#define IDirect3DMaterial_Release(p)            (p)->lpVtbl->Release(p)
/*** IDirect3DMaterial methods ***/
#define IDirect3DMaterial_Initialize(p,a)  (p)->lpVtbl->Initialize(p,a)
#define IDirect3DMaterial_SetMaterial(p,a) (p)->lpVtbl->SetMaterial(p,a)
#define IDirect3DMaterial_GetMaterial(p,a) (p)->lpVtbl->GetMaterial(p,a)
#define IDirect3DMaterial_GetHandle(p,a,b) (p)->lpVtbl->GetHandle(p,a,b)
#define IDirect3DMaterial_Reserve(p)       (p)->lpVtbl->Reserve(p)
#define IDirect3DMaterial_Unreserve(p)     (p)->lpVtbl->Unreserve(p)
#else
/*** IUnknown methods ***/
#define IDirect3DMaterial_QueryInterface(p,a,b) (p)->QueryInterface(a,b)
#define IDirect3DMaterial_AddRef(p)             (p)->AddRef()
#define IDirect3DMaterial_Release(p)            (p)->Release()
/*** IDirect3DMaterial methods ***/
#define IDirect3DMaterial_Initialize(p,a)  (p)->Initialize(a)
#define IDirect3DMaterial_SetMaterial(p,a) (p)->SetMaterial(a)
#define IDirect3DMaterial_GetMaterial(p,a) (p)->GetMaterial(a)
#define IDirect3DMaterial_GetHandle(p,a,b) (p)->GetHandle(a,b)
#define IDirect3DMaterial_Reserve(p)       (p)->Reserve()
#define IDirect3DMaterial_Unreserve(p)     (p)->Unreserve()
#endif


/*****************************************************************************
 * IDirect3DMaterial2 interface
 */
#define INTERFACE IDirect3DMaterial2
DECLARE_INTERFACE_(IDirect3DMaterial2,IUnknown)
{
    /*** IUnknown methods ***/
    STDMETHOD_(HRESULT,QueryInterface)(THIS_ REFIID riid, void** ppvObject) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;
    /*** IDirect3DMaterial2 methods ***/
    STDMETHOD(SetMaterial)(THIS_ D3DMATERIAL *data) PURE;
    STDMETHOD(GetMaterial)(THIS_ D3DMATERIAL *data) PURE;
    STDMETHOD(GetHandle)(THIS_ struct IDirect3DDevice2 *device, D3DMATERIALHANDLE *handle) PURE;
};
#undef INTERFACE

#if !defined(__cplusplus) || defined(CINTERFACE)
/*** IUnknown methods ***/
#define IDirect3DMaterial2_QueryInterface(p,a,b) (p)->lpVtbl->QueryInterface(p,a,b)
#define IDirect3DMaterial2_AddRef(p)             (p)->lpVtbl->AddRef(p)
#define IDirect3DMaterial2_Release(p)            (p)->lpVtbl->Release(p)
/*** IDirect3DMaterial2 methods ***/
#define IDirect3DMaterial2_SetMaterial(p,a) (p)->lpVtbl->SetMaterial(p,a)
#define IDirect3DMaterial2_GetMaterial(p,a) (p)->lpVtbl->GetMaterial(p,a)
#define IDirect3DMaterial2_GetHandle(p,a,b) (p)->lpVtbl->GetHandle(p,a,b)
#else
/*** IUnknown methods ***/
#define IDirect3DMaterial2_QueryInterface(p,a,b) (p)->QueryInterface(a,b)
#define IDirect3DMaterial2_AddRef(p)             (p)->AddRef()
#define IDirect3DMaterial2_Release(p)            (p)->Release()
/*** IDirect3DMaterial2 methods ***/
#define IDirect3DMaterial2_SetMaterial(p,a) (p)->SetMaterial(a)
#define IDirect3DMaterial2_GetMaterial(p,a) (p)->GetMaterial(a)
#define IDirect3DMaterial2_GetHandle(p,a,b) (p)->GetHandle(a,b)
#endif


/*****************************************************************************
 * IDirect3DMaterial3 interface
 */
#define INTERFACE IDirect3DMaterial3
DECLARE_INTERFACE_(IDirect3DMaterial3,IUnknown)
{
    /*** IUnknown methods ***/
    STDMETHOD_(HRESULT,QueryInterface)(THIS_ REFIID riid, void** ppvObject) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;
    /*** IDirect3DMaterial3 methods ***/
    STDMETHOD(SetMaterial)(THIS_ D3DMATERIAL *data) PURE;
    STDMETHOD(GetMaterial)(THIS_ D3DMATERIAL *data) PURE;
    STDMETHOD(GetHandle)(THIS_ struct IDirect3DDevice3 *device, D3DMATERIALHANDLE *handle) PURE;
};
#undef INTERFACE

#if !defined(__cplusplus) || defined(CINTERFACE)
/*** IUnknown methods ***/
#define IDirect3DMaterial3_QueryInterface(p,a,b) (p)->lpVtbl->QueryInterface(p,a,b)
#define IDirect3DMaterial3_AddRef(p)             (p)->lpVtbl->AddRef(p)
#define IDirect3DMaterial3_Release(p)            (p)->lpVtbl->Release(p)
/*** IDirect3DMaterial3 methods ***/
#define IDirect3DMaterial3_SetMaterial(p,a) (p)->lpVtbl->SetMaterial(p,a)
#define IDirect3DMaterial3_GetMaterial(p,a) (p)->lpVtbl->GetMaterial(p,a)
#define IDirect3DMaterial3_GetHandle(p,a,b) (p)->lpVtbl->GetHandle(p,a,b)
#else
/*** IUnknown methods ***/
#define IDirect3DMaterial3_QueryInterface(p,a,b) (p)->QueryInterface(a,b)
#define IDirect3DMaterial3_AddRef(p)             (p)->AddRef()
#define IDirect3DMaterial3_Release(p)            (p)->Release()
/*** IDirect3DMaterial3 methods ***/
#define IDirect3DMaterial3_SetMaterial(p,a) (p)->SetMaterial(a)
#define IDirect3DMaterial3_GetMaterial(p,a) (p)->GetMaterial(a)
#define IDirect3DMaterial3_GetHandle(p,a,b) (p)->GetHandle(a,b)
#endif


/*****************************************************************************
 * IDirect3DTexture interface
 */
#define INTERFACE IDirect3DTexture
DECLARE_INTERFACE_(IDirect3DTexture,IUnknown)
{
    /*** IUnknown methods ***/
    STDMETHOD_(HRESULT,QueryInterface)(THIS_ REFIID riid, void** ppvObject) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;
    /*** IDirect3DTexture methods ***/
    STDMETHOD(Initialize)(THIS_ struct IDirect3DDevice *device, IDirectDrawSurface *surface) PURE;
    STDMETHOD(GetHandle)(THIS_ struct IDirect3DDevice *device, D3DTEXTUREHANDLE *handle) PURE;
    STDMETHOD(PaletteChanged)(THIS_ DWORD dwStart, DWORD dwCount) PURE;
    STDMETHOD(Load)(THIS_ IDirect3DTexture *texture) PURE;
    STDMETHOD(Unload)(THIS) PURE;
};
#undef INTERFACE

#if !defined(__cplusplus) || defined(CINTERFACE)
/*** IUnknown methods ***/
#define IDirect3DTexture_QueryInterface(p,a,b) (p)->lpVtbl->QueryInterface(p,a,b)
#define IDirect3DTexture_AddRef(p)             (p)->lpVtbl->AddRef(p)
#define IDirect3DTexture_Release(p)            (p)->lpVtbl->Release(p)
/*** IDirect3DTexture methods ***/
#define IDirect3DTexture_Initialize(p,a,b) (p)->lpVtbl->Initialize(p,a,b)
#define IDirect3DTexture_GetHandle(p,a,b) (p)->lpVtbl->GetHandle(p,a,b)
#define IDirect3DTexture_PaletteChanged(p,a,b) (p)->lpVtbl->PaletteChanged(p,a,b)
#define IDirect3DTexture_Load(p,a) (p)->lpVtbl->Load(p,a)
#define IDirect3DTexture_Unload(p) (p)->lpVtbl->Unload(p)
#else
/*** IUnknown methods ***/
#define IDirect3DTexture_QueryInterface(p,a,b) (p)->QueryInterface(a,b)
#define IDirect3DTexture_AddRef(p)             (p)->AddRef()
#define IDirect3DTexture_Release(p)            (p)->Release()
/*** IDirect3DTexture methods ***/
#define IDirect3DTexture_Initialize(p,a,b) (p)->Initialize(a,b)
#define IDirect3DTexture_GetHandle(p,a,b) (p)->GetHandle(a,b)
#define IDirect3DTexture_PaletteChanged(p,a,b) (p)->PaletteChanged(a,b)
#define IDirect3DTexture_Load(p,a) (p)->Load(a)
#define IDirect3DTexture_Unload(p) (p)->Unload()
#endif


/*****************************************************************************
 * IDirect3DTexture2 interface
 */
#define INTERFACE IDirect3DTexture2
DECLARE_INTERFACE_(IDirect3DTexture2,IUnknown)
{
    /*** IUnknown methods ***/
    STDMETHOD_(HRESULT,QueryInterface)(THIS_ REFIID riid, void** ppvObject) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;
    /*** IDirect3DTexture2 methods ***/
    STDMETHOD(GetHandle)(THIS_ struct IDirect3DDevice2 *device, D3DTEXTUREHANDLE *handle) PURE;
    STDMETHOD(PaletteChanged)(THIS_ DWORD dwStart, DWORD dwCount) PURE;
    STDMETHOD(Load)(THIS_ IDirect3DTexture2 *texture) PURE;
};
#undef INTERFACE

#if !defined(__cplusplus) || defined(CINTERFACE)
/*** IUnknown methods ***/
#define IDirect3DTexture2_QueryInterface(p,a,b) (p)->lpVtbl->QueryInterface(p,a,b)
#define IDirect3DTexture2_AddRef(p)             (p)->lpVtbl->AddRef(p)
#define IDirect3DTexture2_Release(p)            (p)->lpVtbl->Release(p)
/*** IDirect3DTexture2 methods ***/
#define IDirect3DTexture2_GetHandle(p,a,b)      (p)->lpVtbl->GetHandle(p,a,b)
#define IDirect3DTexture2_PaletteChanged(p,a,b) (p)->lpVtbl->PaletteChanged(p,a,b)
#define IDirect3DTexture2_Load(p,a)             (p)->lpVtbl->Load(p,a)
#else
/*** IUnknown methods ***/
#define IDirect3DTexture2_QueryInterface(p,a,b) (p)->QueryInterface(a,b)
#define IDirect3DTexture2_AddRef(p)             (p)->AddRef()
#define IDirect3DTexture2_Release(p)            (p)->Release()
/*** IDirect3DTexture2 methods ***/
#define IDirect3DTexture2_GetHandle(p,a,b)      (p)->GetHandle(a,b)
#define IDirect3DTexture2_PaletteChanged(p,a,b) (p)->PaletteChanged(a,b)
#define IDirect3DTexture2_Load(p,a)             (p)->Load(a)
#endif


/*****************************************************************************
 * IDirect3DViewport interface
 */
#define INTERFACE IDirect3DViewport
DECLARE_INTERFACE_(IDirect3DViewport,IUnknown)
{
    /*** IUnknown methods ***/
    STDMETHOD_(HRESULT,QueryInterface)(THIS_ REFIID riid, void** ppvObject) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;
    /*** IDirect3DViewport methods ***/
    STDMETHOD(Initialize)(THIS_ IDirect3D *d3d) PURE;
    STDMETHOD(GetViewport)(THIS_ D3DVIEWPORT *data) PURE;
    STDMETHOD(SetViewport)(THIS_ D3DVIEWPORT *data) PURE;
    STDMETHOD(TransformVertices)(THIS_ DWORD vertex_count, D3DTRANSFORMDATA *data, DWORD flags, DWORD *offscreen) PURE;
    STDMETHOD(LightElements)(THIS_ DWORD element_count, D3DLIGHTDATA *data) PURE;
    STDMETHOD(SetBackground)(THIS_ D3DMATERIALHANDLE hMat) PURE;
    STDMETHOD(GetBackground)(THIS_ D3DMATERIALHANDLE *material, WINBOOL *valid) PURE;
    STDMETHOD(SetBackgroundDepth)(THIS_ IDirectDrawSurface *surface) PURE;
    STDMETHOD(GetBackgroundDepth)(THIS_ IDirectDrawSurface **surface, WINBOOL *valid) PURE;
    STDMETHOD(Clear)(THIS_ DWORD count, D3DRECT *rects, DWORD flags) PURE;
    STDMETHOD(AddLight)(THIS_ IDirect3DLight *light) PURE;
    STDMETHOD(DeleteLight)(THIS_ IDirect3DLight *light) PURE;
    STDMETHOD(NextLight)(THIS_ IDirect3DLight *ref, IDirect3DLight **light, DWORD flags) PURE;
};
#undef INTERFACE

#if !defined(__cplusplus) || defined(CINTERFACE)
/*** IUnknown methods ***/
#define IDirect3DViewport_QueryInterface(p,a,b) (p)->lpVtbl->QueryInterface(p,a,b)
#define IDirect3DViewport_AddRef(p)             (p)->lpVtbl->AddRef(p)
#define IDirect3DViewport_Release(p)            (p)->lpVtbl->Release(p)
/*** IDirect3DViewport methods ***/
#define IDirect3DViewport_Initialize(p,a)              (p)->lpVtbl->Initialize(p,a)
#define IDirect3DViewport_GetViewport(p,a)             (p)->lpVtbl->GetViewport(p,a)
#define IDirect3DViewport_SetViewport(p,a)             (p)->lpVtbl->SetViewport(p,a)
#define IDirect3DViewport_TransformVertices(p,a,b,c,d) (p)->lpVtbl->TransformVertices(p,a,b,c,d)
#define IDirect3DViewport_LightElements(p,a,b)         (p)->lpVtbl->LightElements(p,a,b)
#define IDirect3DViewport_SetBackground(p,a)           (p)->lpVtbl->SetBackground(p,a)
#define IDirect3DViewport_GetBackground(p,a,b)         (p)->lpVtbl->GetBackground(p,a,b)
#define IDirect3DViewport_SetBackgroundDepth(p,a)      (p)->lpVtbl->SetBackgroundDepth(p,a)
#define IDirect3DViewport_GetBackgroundDepth(p,a,b)    (p)->lpVtbl->GetBackgroundDepth(p,a,b)
#define IDirect3DViewport_Clear(p,a,b,c)               (p)->lpVtbl->Clear(p,a,b,c)
#define IDirect3DViewport_AddLight(p,a)                (p)->lpVtbl->AddLight(p,a)
#define IDirect3DViewport_DeleteLight(p,a)             (p)->lpVtbl->DeleteLight(p,a)
#define IDirect3DViewport_NextLight(p,a,b,c)           (p)->lpVtbl->NextLight(p,a,b,c)
#else
/*** IUnknown methods ***/
#define IDirect3DViewport_QueryInterface(p,a,b) (p)->QueryInterface(a,b)
#define IDirect3DViewport_AddRef(p)             (p)->AddRef()
#define IDirect3DViewport_Release(p)            (p)->Release()
/*** IDirect3DViewport methods ***/
#define IDirect3DViewport_Initialize(p,a)              (p)->Initialize(a)
#define IDirect3DViewport_GetViewport(p,a)             (p)->GetViewport(a)
#define IDirect3DViewport_SetViewport(p,a)             (p)->SetViewport(a)
#define IDirect3DViewport_TransformVertices(p,a,b,c,d) (p)->TransformVertices(a,b,c,d)
#define IDirect3DViewport_LightElements(p,a,b)         (p)->LightElements(a,b)
#define IDirect3DViewport_SetBackground(p,a)           (p)->SetBackground(a)
#define IDirect3DViewport_GetBackground(p,a,b)         (p)->GetBackground(a,b)
#define IDirect3DViewport_SetBackgroundDepth(p,a)      (p)->SetBackgroundDepth(a)
#define IDirect3DViewport_GetBackgroundDepth(p,a,b)    (p)->GetBackgroundDepth(a,b)
#define IDirect3DViewport_Clear(p,a,b,c)               (p)->Clear(a,b,c)
#define IDirect3DViewport_AddLight(p,a)                (p)->AddLight(a)
#define IDirect3DViewport_DeleteLight(p,a)             (p)->DeleteLight(a)
#define IDirect3DViewport_NextLight(p,a,b,c)           (p)->NextLight(a,b,c)
#endif


/*****************************************************************************
 * IDirect3DViewport2 interface
 */
#define INTERFACE IDirect3DViewport2
DECLARE_INTERFACE_(IDirect3DViewport2,IDirect3DViewport)
{
    /*** IUnknown methods ***/
    STDMETHOD_(HRESULT,QueryInterface)(THIS_ REFIID riid, void** ppvObject) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;
    /*** IDirect3DViewport methods ***/
    STDMETHOD(Initialize)(THIS_ IDirect3D *d3d) PURE;
    STDMETHOD(GetViewport)(THIS_ D3DVIEWPORT *data) PURE;
    STDMETHOD(SetViewport)(THIS_ D3DVIEWPORT *data) PURE;
    STDMETHOD(TransformVertices)(THIS_ DWORD vertex_count, D3DTRANSFORMDATA *data, DWORD flags, DWORD *offscreen) PURE;
    STDMETHOD(LightElements)(THIS_ DWORD element_count, D3DLIGHTDATA *data) PURE;
    STDMETHOD(SetBackground)(THIS_ D3DMATERIALHANDLE hMat) PURE;
    STDMETHOD(GetBackground)(THIS_ D3DMATERIALHANDLE *material, WINBOOL *valid) PURE;
    STDMETHOD(SetBackgroundDepth)(THIS_ IDirectDrawSurface *surface) PURE;
    STDMETHOD(GetBackgroundDepth)(THIS_ IDirectDrawSurface **surface, WINBOOL *valid) PURE;
    STDMETHOD(Clear)(THIS_ DWORD count, D3DRECT *rects, DWORD flags) PURE;
    STDMETHOD(AddLight)(THIS_ IDirect3DLight *light) PURE;
    STDMETHOD(DeleteLight)(THIS_ IDirect3DLight *light) PURE;
    STDMETHOD(NextLight)(THIS_ IDirect3DLight *ref, IDirect3DLight **light, DWORD flags) PURE;
    /*** IDirect3DViewport2 methods ***/
    STDMETHOD(GetViewport2)(THIS_ D3DVIEWPORT2 *data) PURE;
    STDMETHOD(SetViewport2)(THIS_ D3DVIEWPORT2 *data) PURE;
};
#undef INTERFACE

#if !defined(__cplusplus) || defined(CINTERFACE)
/*** IUnknown methods ***/
#define IDirect3DViewport2_QueryInterface(p,a,b) (p)->lpVtbl->QueryInterface(p,a,b)
#define IDirect3DViewport2_AddRef(p)             (p)->lpVtbl->AddRef(p)
#define IDirect3DViewport2_Release(p)            (p)->lpVtbl->Release(p)
/*** IDirect3Viewport methods ***/
#define IDirect3DViewport2_Initialize(p,a)              (p)->lpVtbl->Initialize(p,a)
#define IDirect3DViewport2_GetViewport(p,a)             (p)->lpVtbl->GetViewport(p,a)
#define IDirect3DViewport2_SetViewport(p,a)             (p)->lpVtbl->SetViewport(p,a)
#define IDirect3DViewport2_TransformVertices(p,a,b,c,d) (p)->lpVtbl->TransformVertices(p,a,b,c,d)
#define IDirect3DViewport2_LightElements(p,a,b)         (p)->lpVtbl->LightElements(p,a,b)
#define IDirect3DViewport2_SetBackground(p,a)           (p)->lpVtbl->SetBackground(p,a)
#define IDirect3DViewport2_GetBackground(p,a,b)         (p)->lpVtbl->GetBackground(p,a,b)
#define IDirect3DViewport2_SetBackgroundDepth(p,a)      (p)->lpVtbl->SetBackgroundDepth(p,a)
#define IDirect3DViewport2_GetBackgroundDepth(p,a,b)    (p)->lpVtbl->GetBackgroundDepth(p,a,b)
#define IDirect3DViewport2_Clear(p,a,b,c)               (p)->lpVtbl->Clear(p,a,b,c)
#define IDirect3DViewport2_AddLight(p,a)                (p)->lpVtbl->AddLight(p,a)
#define IDirect3DViewport2_DeleteLight(p,a)             (p)->lpVtbl->DeleteLight(p,a)
#define IDirect3DViewport2_NextLight(p,a,b,c)           (p)->lpVtbl->NextLight(p,a,b,c)
/*** IDirect3DViewport2 methods ***/
#define IDirect3DViewport2_GetViewport2(p,a) (p)->lpVtbl->GetViewport2(p,a)
#define IDirect3DViewport2_SetViewport2(p,a) (p)->lpVtbl->SetViewport2(p,a)
#else
/*** IUnknown methods ***/
#define IDirect3DViewport2_QueryInterface(p,a,b) (p)->QueryInterface(a,b)
#define IDirect3DViewport2_AddRef(p)             (p)->AddRef()
#define IDirect3DViewport2_Release(p)            (p)->Release()
/*** IDirect3Viewport methods ***/
#define IDirect3DViewport2_Initialize(p,a)              (p)->Initialize(a)
#define IDirect3DViewport2_GetViewport(p,a)             (p)->GetViewport(a)
#define IDirect3DViewport2_SetViewport(p,a)             (p)->SetViewport(a)
#define IDirect3DViewport2_TransformVertices(p,a,b,c,d) (p)->TransformVertices(a,b,c,d)
#define IDirect3DViewport2_LightElements(p,a,b)         (p)->LightElements(a,b)
#define IDirect3DViewport2_SetBackground(p,a)           (p)->SetBackground(a)
#define IDirect3DViewport2_GetBackground(p,a,b)         (p)->GetBackground(a,b)
#define IDirect3DViewport2_SetBackgroundDepth(p,a)      (p)->SetBackgroundDepth(a)
#define IDirect3DViewport2_GetBackgroundDepth(p,a,b)    (p)->GetBackgroundDepth(a,b)
#define IDirect3DViewport2_Clear(p,a,b,c)               (p)->Clear(a,b,c)
#define IDirect3DViewport2_AddLight(p,a)                (p)->AddLight(a)
#define IDirect3DViewport2_DeleteLight(p,a)             (p)->DeleteLight(a)
#define IDirect3DViewport2_NextLight(p,a,b,c)           (p)->NextLight(a,b,c)
/*** IDirect3DViewport2 methods ***/
#define IDirect3DViewport2_GetViewport2(p,a) (p)->GetViewport2(a)
#define IDirect3DViewport2_SetViewport2(p,a) (p)->SetViewport2(a)
#endif

/*****************************************************************************
 * IDirect3DViewport3 interface
 */
#define INTERFACE IDirect3DViewport3
DECLARE_INTERFACE_(IDirect3DViewport3,IDirect3DViewport2)
{
    /*** IUnknown methods ***/
    STDMETHOD_(HRESULT,QueryInterface)(THIS_ REFIID riid, void** ppvObject) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;
    /*** IDirect3DViewport methods ***/
    STDMETHOD(Initialize)(THIS_ IDirect3D *d3d) PURE;
    STDMETHOD(GetViewport)(THIS_ D3DVIEWPORT *data) PURE;
    STDMETHOD(SetViewport)(THIS_ D3DVIEWPORT *data) PURE;
    STDMETHOD(TransformVertices)(THIS_ DWORD vertex_count, D3DTRANSFORMDATA *data, DWORD flags, DWORD *offscreen) PURE;
    STDMETHOD(LightElements)(THIS_ DWORD element_count, D3DLIGHTDATA *data) PURE;
    STDMETHOD(SetBackground)(THIS_ D3DMATERIALHANDLE hMat) PURE;
    STDMETHOD(GetBackground)(THIS_ D3DMATERIALHANDLE *material, WINBOOL *valid) PURE;
    STDMETHOD(SetBackgroundDepth)(THIS_ IDirectDrawSurface *surface) PURE;
    STDMETHOD(GetBackgroundDepth)(THIS_ IDirectDrawSurface **surface, WINBOOL *valid) PURE;
    STDMETHOD(Clear)(THIS_ DWORD count, D3DRECT *rects, DWORD flags) PURE;
    STDMETHOD(AddLight)(THIS_ IDirect3DLight *light) PURE;
    STDMETHOD(DeleteLight)(THIS_ IDirect3DLight *light) PURE;
    STDMETHOD(NextLight)(THIS_ IDirect3DLight *ref, IDirect3DLight **light, DWORD flags) PURE;
    /*** IDirect3DViewport2 methods ***/
    STDMETHOD(GetViewport2)(THIS_ D3DVIEWPORT2 *data) PURE;
    STDMETHOD(SetViewport2)(THIS_ D3DVIEWPORT2 *data) PURE;
    /*** IDirect3DViewport3 methods ***/
    STDMETHOD(SetBackgroundDepth2)(THIS_ IDirectDrawSurface4 *surface) PURE;
    STDMETHOD(GetBackgroundDepth2)(THIS_ IDirectDrawSurface4 **surface, WINBOOL *valid) PURE;
    STDMETHOD(Clear2)(THIS_ DWORD count, D3DRECT *rects, DWORD flags, DWORD color, D3DVALUE z, DWORD stencil) PURE;
};
#undef INTERFACE

#if !defined(__cplusplus) || defined(CINTERFACE)
/*** IUnknown methods ***/
#define IDirect3DViewport3_QueryInterface(p,a,b) (p)->lpVtbl->QueryInterface(p,a,b)
#define IDirect3DViewport3_AddRef(p)             (p)->lpVtbl->AddRef(p)
#define IDirect3DViewport3_Release(p)            (p)->lpVtbl->Release(p)
/*** IDirect3Viewport methods ***/
#define IDirect3DViewport3_Initialize(p,a)              (p)->lpVtbl->Initialize(p,a)
#define IDirect3DViewport3_GetViewport(p,a)             (p)->lpVtbl->GetViewport(p,a)
#define IDirect3DViewport3_SetViewport(p,a)             (p)->lpVtbl->SetViewport(p,a)
#define IDirect3DViewport3_TransformVertices(p,a,b,c,d) (p)->lpVtbl->TransformVertices(p,a,b,c,d)
#define IDirect3DViewport3_LightElements(p,a,b)         (p)->lpVtbl->LightElements(p,a,b)
#define IDirect3DViewport3_SetBackground(p,a)           (p)->lpVtbl->SetBackground(p,a)
#define IDirect3DViewport3_GetBackground(p,a,b)         (p)->lpVtbl->GetBackground(p,a,b)
#define IDirect3DViewport3_SetBackgroundDepth(p,a)      (p)->lpVtbl->SetBackgroundDepth(p,a)
#define IDirect3DViewport3_GetBackgroundDepth(p,a,b)    (p)->lpVtbl->GetBackgroundDepth(p,a,b)
#define IDirect3DViewport3_Clear(p,a,b,c)               (p)->lpVtbl->Clear(p,a,b,c)
#define IDirect3DViewport3_AddLight(p,a)                (p)->lpVtbl->AddLight(p,a)
#define IDirect3DViewport3_DeleteLight(p,a)             (p)->lpVtbl->DeleteLight(p,a)
#define IDirect3DViewport3_NextLight(p,a,b,c)           (p)->lpVtbl->NextLight(p,a,b,c)
/*** IDirect3DViewport2 methods ***/
#define IDirect3DViewport3_GetViewport2(p,a) (p)->lpVtbl->GetViewport2(p,a)
#define IDirect3DViewport3_SetViewport2(p,a) (p)->lpVtbl->SetViewport2(p,a)
/*** IDirect3DViewport3 methods ***/
#define IDirect3DViewport3_SetBackgroundDepth2(p,a)   (p)->lpVtbl->SetBackgroundDepth2(p,a)
#define IDirect3DViewport3_GetBackgroundDepth2(p,a,b) (p)->lpVtbl->GetBackgroundDepth2(p,a,b)
#define IDirect3DViewport3_Clear2(p,a,b,c,d,e,f)      (p)->lpVtbl->Clear2(p,a,b,c,d,e,f)
#else
/*** IUnknown methods ***/
#define IDirect3DViewport3_QueryInterface(p,a,b) (p)->QueryInterface(a,b)
#define IDirect3DViewport3_AddRef(p)             (p)->AddRef()
#define IDirect3DViewport3_Release(p)            (p)->Release()
/*** IDirect3Viewport methods ***/
#define IDirect3DViewport3_Initialize(p,a)              (p)->Initialize(a)
#define IDirect3DViewport3_GetViewport(p,a)             (p)->GetViewport(a)
#define IDirect3DViewport3_SetViewport(p,a)             (p)->SetViewport(a)
#define IDirect3DViewport3_TransformVertices(p,a,b,c,d) (p)->TransformVertices(a,b,c,d)
#define IDirect3DViewport3_LightElements(p,a,b)         (p)->LightElements(a,b)
#define IDirect3DViewport3_SetBackground(p,a)           (p)->SetBackground(a)
#define IDirect3DViewport3_GetBackground(p,a,b)         (p)->GetBackground(a,b)
#define IDirect3DViewport3_SetBackgroundDepth(p,a)      (p)->SetBackgroundDepth(a)
#define IDirect3DViewport3_GetBackgroundDepth(p,a,b)    (p)->GetBackgroundDepth(a,b)
#define IDirect3DViewport3_Clear(p,a,b,c)               (p)->Clear(a,b,c)
#define IDirect3DViewport3_AddLight(p,a)                (p)->AddLight(a)
#define IDirect3DViewport3_DeleteLight(p,a)             (p)->DeleteLight(a)
#define IDirect3DViewport3_NextLight(p,a,b,c)           (p)->NextLight(a,b,c)
/*** IDirect3DViewport2 methods ***/
#define IDirect3DViewport3_GetViewport2(p,a) (p)->GetViewport2(a)
#define IDirect3DViewport3_SetViewport2(p,a) (p)->SetViewport2(a)
/*** IDirect3DViewport3 methods ***/
#define IDirect3DViewport3_SetBackgroundDepth2(p,a)   (p)->SetBackgroundDepth2(a)
#define IDirect3DViewport3_GetBackgroundDepth2(p,a,b) (p)->GetBackgroundDepth2(a,b)
#define IDirect3DViewport3_Clear2(p,a,b,c,d,e,f)      (p)->Clear2(a,b,c,d,e,f)
#endif



/*****************************************************************************
 * IDirect3DExecuteBuffer interface
 */
#define INTERFACE IDirect3DExecuteBuffer
DECLARE_INTERFACE_(IDirect3DExecuteBuffer,IUnknown)
{
    /*** IUnknown methods ***/
    STDMETHOD_(HRESULT,QueryInterface)(THIS_ REFIID riid, void** ppvObject) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;
    /*** IDirect3DExecuteBuffer methods ***/
    STDMETHOD(Initialize)(THIS_ struct IDirect3DDevice *device, D3DEXECUTEBUFFERDESC *desc) PURE;
    STDMETHOD(Lock)(THIS_ D3DEXECUTEBUFFERDESC *desc) PURE;
    STDMETHOD(Unlock)(THIS) PURE;
    STDMETHOD(SetExecuteData)(THIS_ D3DEXECUTEDATA *data) PURE;
    STDMETHOD(GetExecuteData)(THIS_ D3DEXECUTEDATA *data) PURE;
    STDMETHOD(Validate)(THIS_ DWORD *offset, LPD3DVALIDATECALLBACK cb, void *ctx, DWORD reserved) PURE;
    STDMETHOD(Optimize)(THIS_ DWORD dwDummy) PURE;
};
#undef INTERFACE

#if !defined(__cplusplus) || defined(CINTERFACE)
/*** IUnknown methods ***/
#define IDirect3DExecuteBuffer_QueryInterface(p,a,b) (p)->lpVtbl->QueryInterface(p,a,b)
#define IDirect3DExecuteBuffer_AddRef(p)             (p)->lpVtbl->AddRef(p)
#define IDirect3DExecuteBuffer_Release(p)            (p)->lpVtbl->Release(p)
/*** IDirect3DExecuteBuffer methods ***/
#define IDirect3DExecuteBuffer_Initialize(p,a,b)   (p)->lpVtbl->Initialize(p,a,b)
#define IDirect3DExecuteBuffer_Lock(p,a)           (p)->lpVtbl->Lock(p,a)
#define IDirect3DExecuteBuffer_Unlock(p)           (p)->lpVtbl->Unlock(p)
#define IDirect3DExecuteBuffer_SetExecuteData(p,a) (p)->lpVtbl->SetExecuteData(p,a)
#define IDirect3DExecuteBuffer_GetExecuteData(p,a) (p)->lpVtbl->GetExecuteData(p,a)
#define IDirect3DExecuteBuffer_Validate(p,a,b,c,d) (p)->lpVtbl->Validate(p,a,b,c,d)
#define IDirect3DExecuteBuffer_Optimize(p,a)       (p)->lpVtbl->Optimize(p,a)
#else
/*** IUnknown methods ***/
#define IDirect3DExecuteBuffer_QueryInterface(p,a,b) (p)->QueryInterface(a,b)
#define IDirect3DExecuteBuffer_AddRef(p)             (p)->AddRef()
#define IDirect3DExecuteBuffer_Release(p)            (p)->Release()
/*** IDirect3DExecuteBuffer methods ***/
#define IDirect3DExecuteBuffer_Initialize(p,a,b)   (p)->Initialize(a,b)
#define IDirect3DExecuteBuffer_Lock(p,a)           (p)->Lock(a)
#define IDirect3DExecuteBuffer_Unlock(p)           (p)->Unlock()
#define IDirect3DExecuteBuffer_SetExecuteData(p,a) (p)->SetExecuteData(a)
#define IDirect3DExecuteBuffer_GetExecuteData(p,a) (p)->GetExecuteData(a)
#define IDirect3DExecuteBuffer_Validate(p,a,b,c,d) (p)->Validate(a,b,c,d)
#define IDirect3DExecuteBuffer_Optimize(p,a)       (p)->Optimize(a)
#endif


/*****************************************************************************
 * IDirect3DDevice interface
 */
#define INTERFACE IDirect3DDevice
DECLARE_INTERFACE_(IDirect3DDevice,IUnknown)
{
    /*** IUnknown methods ***/
    STDMETHOD_(HRESULT,QueryInterface)(THIS_ REFIID riid, void** ppvObject) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;
    /*** IDirect3DDevice methods ***/
    STDMETHOD(Initialize)(THIS_ IDirect3D *d3d, GUID *guid, D3DDEVICEDESC *desc) PURE;
    STDMETHOD(GetCaps)(THIS_ D3DDEVICEDESC *hal_desc, D3DDEVICEDESC *hel_desc) PURE;
    STDMETHOD(SwapTextureHandles)(THIS_ IDirect3DTexture *tex1, IDirect3DTexture *tex2) PURE;
    STDMETHOD(CreateExecuteBuffer)(THIS_ D3DEXECUTEBUFFERDESC *desc,
                                   IDirect3DExecuteBuffer **buffer, IUnknown *outer) PURE;
                                   STDMETHOD(GetStats)(THIS_ D3DSTATS *stats) PURE;
                                   STDMETHOD(Execute)(THIS_ IDirect3DExecuteBuffer *buffer, IDirect3DViewport *viewport,
                                                      DWORD flags) PURE;
                                                      STDMETHOD(AddViewport)(THIS_ IDirect3DViewport *viewport) PURE;
                                                      STDMETHOD(DeleteViewport)(THIS_ IDirect3DViewport *viewport) PURE;
                                                      STDMETHOD(NextViewport)(THIS_ IDirect3DViewport *ref,
                                                                              IDirect3DViewport **viewport, DWORD flags) PURE;
                                                                              STDMETHOD(Pick)(THIS_ IDirect3DExecuteBuffer *buffer, IDirect3DViewport *viewport,
                                                                                              DWORD flags, D3DRECT *rect) PURE;
                                                                                              STDMETHOD(GetPickRecords)(THIS_ DWORD *count, D3DPICKRECORD *records) PURE;
                                                                                              STDMETHOD(EnumTextureFormats)(THIS_ LPD3DENUMTEXTUREFORMATSCALLBACK cb, void *ctx) PURE;
                                                                                              STDMETHOD(CreateMatrix)(THIS_ D3DMATRIXHANDLE *matrix) PURE;
                                                                                              STDMETHOD(SetMatrix)(THIS_ D3DMATRIXHANDLE handle, D3DMATRIX *matrix) PURE;
                                                                                              STDMETHOD(GetMatrix)(THIS_ D3DMATRIXHANDLE handle, D3DMATRIX *matrix) PURE;
                                                                                              STDMETHOD(DeleteMatrix)(THIS_ D3DMATRIXHANDLE D3DMatHandle) PURE;
                                                                                              STDMETHOD(BeginScene)(THIS) PURE;
                                                                                              STDMETHOD(EndScene)(THIS) PURE;
                                                                                              STDMETHOD(GetDirect3D)(THIS_ IDirect3D **d3d) PURE;
};
#undef INTERFACE

#if !defined(__cplusplus) || defined(CINTERFACE)
/*** IUnknown methods ***/
#define IDirect3DDevice_QueryInterface(p,a,b) (p)->lpVtbl->QueryInterface(p,a,b)
#define IDirect3DDevice_AddRef(p)             (p)->lpVtbl->AddRef(p)
#define IDirect3DDevice_Release(p)            (p)->lpVtbl->Release(p)
/*** IDirect3DDevice methods ***/
#define IDirect3DDevice_Initialize(p,a,b,c)          (p)->lpVtbl->Initialize(p,a,b,c)
#define IDirect3DDevice_GetCaps(p,a,b)               (p)->lpVtbl->GetCaps(p,a,b)
#define IDirect3DDevice_SwapTextureHandles(p,a,b)    (p)->lpVtbl->SwapTextureHandles(p,a,b)
#define IDirect3DDevice_CreateExecuteBuffer(p,a,b,c) (p)->lpVtbl->CreateExecuteBuffer(p,a,b,c)
#define IDirect3DDevice_GetStats(p,a)                (p)->lpVtbl->GetStats(p,a)
#define IDirect3DDevice_Execute(p,a,b,c)             (p)->lpVtbl->Execute(p,a,b,c)
#define IDirect3DDevice_AddViewport(p,a)             (p)->lpVtbl->AddViewport(p,a)
#define IDirect3DDevice_DeleteViewport(p,a)          (p)->lpVtbl->DeleteViewport(p,a)
#define IDirect3DDevice_NextViewport(p,a,b,c)        (p)->lpVtbl->NextViewport(p,a,b,c)
#define IDirect3DDevice_Pick(p,a,b,c,d)              (p)->lpVtbl->Pick(p,a,b,c,d)
#define IDirect3DDevice_GetPickRecords(p,a,b)        (p)->lpVtbl->GetPickRecords(p,a,b)
#define IDirect3DDevice_EnumTextureFormats(p,a,b)    (p)->lpVtbl->EnumTextureFormats(p,a,b)
#define IDirect3DDevice_CreateMatrix(p,a)            (p)->lpVtbl->CreateMatrix(p,a)
#define IDirect3DDevice_SetMatrix(p,a,b)             (p)->lpVtbl->SetMatrix(p,a,b)
#define IDirect3DDevice_GetMatrix(p,a,b)             (p)->lpVtbl->GetMatrix(p,a,b)
#define IDirect3DDevice_DeleteMatrix(p,a)            (p)->lpVtbl->DeleteMatrix(p,a)
#define IDirect3DDevice_BeginScene(p)                (p)->lpVtbl->BeginScene(p)
#define IDirect3DDevice_EndScene(p)                  (p)->lpVtbl->EndScene(p)
#define IDirect3DDevice_GetDirect3D(p,a)             (p)->lpVtbl->GetDirect3D(p,a)
#else
/*** IUnknown methods ***/
#define IDirect3DDevice_QueryInterface(p,a,b) (p)->QueryInterface(a,b)
#define IDirect3DDevice_AddRef(p)             (p)->AddRef()
#define IDirect3DDevice_Release(p)            (p)->Release()
/*** IDirect3DDevice methods ***/
#define IDirect3DDevice_Initialize(p,a,b,c)          (p)->Initialize(a,b,c)
#define IDirect3DDevice_GetCaps(p,a,b)               (p)->GetCaps(a,b)
#define IDirect3DDevice_SwapTextureHandles(p,a,b)    (p)->SwapTextureHandles(a,b)
#define IDirect3DDevice_CreateExecuteBuffer(p,a,b,c) (p)->CreateExecuteBuffer(a,b,c)
#define IDirect3DDevice_GetStats(p,a)                (p)->GetStats(a)
#define IDirect3DDevice_Execute(p,a,b,c)             (p)->Execute(a,b,c)
#define IDirect3DDevice_AddViewport(p,a)             (p)->AddViewport(a)
#define IDirect3DDevice_DeleteViewport(p,a)          (p)->DeleteViewport(a)
#define IDirect3DDevice_NextViewport(p,a,b,c)        (p)->NextViewport(a,b,c)
#define IDirect3DDevice_Pick(p,a,b,c,d)              (p)->Pick(a,b,c,d)
#define IDirect3DDevice_GetPickRecords(p,a,b)        (p)->GetPickRecords(a,b)
#define IDirect3DDevice_EnumTextureFormats(p,a,b)    (p)->EnumTextureFormats(a,b)
#define IDirect3DDevice_CreateMatrix(p,a)            (p)->CreateMatrix(a)
#define IDirect3DDevice_SetMatrix(p,a,b)             (p)->SetMatrix(a,b)
#define IDirect3DDevice_GetMatrix(p,a,b)             (p)->GetMatrix(a,b)
#define IDirect3DDevice_DeleteMatrix(p,a)            (p)->DeleteMatrix(a)
#define IDirect3DDevice_BeginScene(p)                (p)->BeginScene()
#define IDirect3DDevice_EndScene(p)                  (p)->EndScene()
#define IDirect3DDevice_GetDirect3D(p,a)             (p)->GetDirect3D(a)
#endif


/*****************************************************************************
 * IDirect3DDevice2 interface
 */
#define INTERFACE IDirect3DDevice2
DECLARE_INTERFACE_(IDirect3DDevice2,IUnknown)
{
    /*** IUnknown methods ***/
    STDMETHOD_(HRESULT,QueryInterface)(THIS_ REFIID riid, void** ppvObject) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;
    /*** IDirect3DDevice2 methods ***/
    STDMETHOD(GetCaps)(THIS_ D3DDEVICEDESC *hal_desc, D3DDEVICEDESC *hel_desc) PURE;
    STDMETHOD(SwapTextureHandles)(THIS_ IDirect3DTexture2 *tex1, IDirect3DTexture2 *tex2) PURE;
    STDMETHOD(GetStats)(THIS_ D3DSTATS *stats) PURE;
    STDMETHOD(AddViewport)(THIS_ IDirect3DViewport2 *viewport) PURE;
    STDMETHOD(DeleteViewport)(THIS_ IDirect3DViewport2 *viewport) PURE;
    STDMETHOD(NextViewport)(THIS_ IDirect3DViewport2 *ref,
                            IDirect3DViewport2 **viewport, DWORD flags) PURE;
                            STDMETHOD(EnumTextureFormats)(THIS_ LPD3DENUMTEXTUREFORMATSCALLBACK cb, void *ctx) PURE;
                            STDMETHOD(BeginScene)(THIS) PURE;
                            STDMETHOD(EndScene)(THIS) PURE;
                            STDMETHOD(GetDirect3D)(THIS_ IDirect3D2 **d3d) PURE;
                            /*** DrawPrimitive API ***/
                            STDMETHOD(SetCurrentViewport)(THIS_ IDirect3DViewport2 *viewport) PURE;
                            STDMETHOD(GetCurrentViewport)(THIS_ IDirect3DViewport2 **viewport) PURE;
                            STDMETHOD(SetRenderTarget)(THIS_ IDirectDrawSurface *surface, DWORD flags) PURE;
                            STDMETHOD(GetRenderTarget)(THIS_ IDirectDrawSurface **surface) PURE;
                            STDMETHOD(Begin)(THIS_ D3DPRIMITIVETYPE d3dpt,D3DVERTEXTYPE dwVertexTypeDesc,DWORD dwFlags) PURE;
                            STDMETHOD(BeginIndexed)(THIS_ D3DPRIMITIVETYPE primitive_type, D3DVERTEXTYPE vertex_type,
                                                    void *vertices, DWORD vertex_count, DWORD flags) PURE;
                                                    STDMETHOD(Vertex)(THIS_ void *vertex) PURE;
                                                    STDMETHOD(Index)(THIS_ WORD wVertexIndex) PURE;
                                                    STDMETHOD(End)(THIS_ DWORD dwFlags) PURE;
                                                    STDMETHOD(GetRenderState)(THIS_ D3DRENDERSTATETYPE dwRenderStateType, LPDWORD lpdwRenderState) PURE;
                                                    STDMETHOD(SetRenderState)(THIS_ D3DRENDERSTATETYPE dwRenderStateType, DWORD dwRenderState) PURE;
                                                    STDMETHOD(GetLightState)(THIS_ D3DLIGHTSTATETYPE dwLightStateType, LPDWORD lpdwLightState) PURE;
                                                    STDMETHOD(SetLightState)(THIS_ D3DLIGHTSTATETYPE dwLightStateType, DWORD dwLightState) PURE;
                                                    STDMETHOD(SetTransform)(THIS_ D3DTRANSFORMSTATETYPE state, D3DMATRIX *matrix) PURE;
                                                    STDMETHOD(GetTransform)(THIS_ D3DTRANSFORMSTATETYPE state, D3DMATRIX *matrix) PURE;
                                                    STDMETHOD(MultiplyTransform)(THIS_ D3DTRANSFORMSTATETYPE state, D3DMATRIX *matrix) PURE;
                                                    STDMETHOD(DrawPrimitive)(THIS_ D3DPRIMITIVETYPE primitive_type, D3DVERTEXTYPE vertex_type,
                                                                             void *vertices, DWORD vertex_count, DWORD flags) PURE;
                                                                             STDMETHOD(DrawIndexedPrimitive)(THIS_ D3DPRIMITIVETYPE primitive_type, D3DVERTEXTYPE vertex_type,
                                                                                                             void *vertices, DWORD vertex_count, WORD *indices, DWORD index_count, DWORD flags) PURE;
                                                                                                             STDMETHOD(SetClipStatus)(THIS_ D3DCLIPSTATUS *clip_status) PURE;
                                                                                                             STDMETHOD(GetClipStatus)(THIS_ D3DCLIPSTATUS *clip_status) PURE;
};
#undef INTERFACE

#if !defined(__cplusplus) || defined(CINTERFACE)
/*** IUnknown methods ***/
#define IDirect3DDevice2_QueryInterface(p,a,b) (p)->lpVtbl->QueryInterface(p,a,b)
#define IDirect3DDevice2_AddRef(p)             (p)->lpVtbl->AddRef(p)
#define IDirect3DDevice2_Release(p)            (p)->lpVtbl->Release(p)
/*** IDirect3DDevice2 methods ***/
#define IDirect3DDevice2_GetCaps(p,a,b)                        (p)->lpVtbl->GetCaps(p,a,b)
#define IDirect3DDevice2_SwapTextureHandles(p,a,b)             (p)->lpVtbl->SwapTextureHandles(p,a,b)
#define IDirect3DDevice2_GetStats(p,a)                         (p)->lpVtbl->GetStats(p,a)
#define IDirect3DDevice2_AddViewport(p,a)                      (p)->lpVtbl->AddViewport(p,a)
#define IDirect3DDevice2_DeleteViewport(p,a)                   (p)->lpVtbl->DeleteViewport(p,a)
#define IDirect3DDevice2_NextViewport(p,a,b,c)                 (p)->lpVtbl->NextViewport(p,a,b,c)
#define IDirect3DDevice2_EnumTextureFormats(p,a,b)             (p)->lpVtbl->EnumTextureFormats(p,a,b)
#define IDirect3DDevice2_BeginScene(p)                         (p)->lpVtbl->BeginScene(p)
#define IDirect3DDevice2_EndScene(p)                           (p)->lpVtbl->EndScene(p)
#define IDirect3DDevice2_GetDirect3D(p,a)                      (p)->lpVtbl->GetDirect3D(p,a)
#define IDirect3DDevice2_SetCurrentViewport(p,a)               (p)->lpVtbl->SetCurrentViewport(p,a)
#define IDirect3DDevice2_GetCurrentViewport(p,a)               (p)->lpVtbl->GetCurrentViewport(p,a)
#define IDirect3DDevice2_SetRenderTarget(p,a,b)                (p)->lpVtbl->SetRenderTarget(p,a,b)
#define IDirect3DDevice2_GetRenderTarget(p,a)                  (p)->lpVtbl->GetRenderTarget(p,a)
#define IDirect3DDevice2_Begin(p,a,b,c)                        (p)->lpVtbl->Begin(p,a,b,c)
#define IDirect3DDevice2_BeginIndexed(p,a,b,c,d,e)             (p)->lpVtbl->BeginIndexed(p,a,b,c,d,e)
#define IDirect3DDevice2_Vertex(p,a)                           (p)->lpVtbl->Vertex(p,a)
#define IDirect3DDevice2_Index(p,a)                            (p)->lpVtbl->Index(p,a)
#define IDirect3DDevice2_End(p,a)                              (p)->lpVtbl->End(p,a)
#define IDirect3DDevice2_GetRenderState(p,a,b)                 (p)->lpVtbl->GetRenderState(p,a,b)
#define IDirect3DDevice2_SetRenderState(p,a,b)                 (p)->lpVtbl->SetRenderState(p,a,b)
#define IDirect3DDevice2_GetLightState(p,a,b)                  (p)->lpVtbl->GetLightState(p,a,b)
#define IDirect3DDevice2_SetLightState(p,a,b)                  (p)->lpVtbl->SetLightState(p,a,b)
#define IDirect3DDevice2_SetTransform(p,a,b)                   (p)->lpVtbl->SetTransform(p,a,b)
#define IDirect3DDevice2_GetTransform(p,a,b)                   (p)->lpVtbl->GetTransform(p,a,b)
#define IDirect3DDevice2_MultiplyTransform(p,a,b)              (p)->lpVtbl->MultiplyTransform(p,a,b)
#define IDirect3DDevice2_DrawPrimitive(p,a,b,c,d,e)            (p)->lpVtbl->DrawPrimitive(p,a,b,c,d,e)
#define IDirect3DDevice2_DrawIndexedPrimitive(p,a,b,c,d,e,f,g) (p)->lpVtbl->DrawIndexedPrimitive(p,a,b,c,d,e,f,g)
#define IDirect3DDevice2_SetClipStatus(p,a)                    (p)->lpVtbl->SetClipStatus(p,a)
#define IDirect3DDevice2_GetClipStatus(p,a)                    (p)->lpVtbl->GetClipStatus(p,a)
#else
/*** IUnknown methods ***/
#define IDirect3DDevice2_QueryInterface(p,a,b) (p)->QueryInterface(a,b)
#define IDirect3DDevice2_AddRef(p)             (p)->AddRef()
#define IDirect3DDevice2_Release(p)            (p)->Release()
/*** IDirect3DDevice2 methods ***/
#define IDirect3DDevice2_GetCaps(p,a,b)                        (p)->GetCaps(a,b)
#define IDirect3DDevice2_SwapTextureHandles(p,a,b)             (p)->SwapTextureHandles(a,b)
#define IDirect3DDevice2_GetStats(p,a)                         (p)->GetStats(a)
#define IDirect3DDevice2_AddViewport(p,a)                      (p)->AddViewport(a)
#define IDirect3DDevice2_DeleteViewport(p,a)                   (p)->DeleteViewport(a)
#define IDirect3DDevice2_NextViewport(p,a,b,c)                 (p)->NextViewport(a,b,c)
#define IDirect3DDevice2_EnumTextureFormats(p,a,b)             (p)->EnumTextureFormats(a,b)
#define IDirect3DDevice2_BeginScene(p)                         (p)->BeginScene()
#define IDirect3DDevice2_EndScene(p)                           (p)->EndScene()
#define IDirect3DDevice2_GetDirect3D(p,a)                      (p)->GetDirect3D(a)
#define IDirect3DDevice2_SetCurrentViewport(p,a)               (p)->SetCurrentViewport(a)
#define IDirect3DDevice2_GetCurrentViewport(p,a)               (p)->GetCurrentViewport(a)
#define IDirect3DDevice2_SetRenderTarget(p,a,b)                (p)->SetRenderTarget(a,b)
#define IDirect3DDevice2_GetRenderTarget(p,a)                  (p)->GetRenderTarget(a)
#define IDirect3DDevice2_Begin(p,a,b,c)                        (p)->Begin(a,b,c)
#define IDirect3DDevice2_BeginIndexed(p,a,b,c,d,e)             (p)->BeginIndexed(a,b,c,d,e)
#define IDirect3DDevice2_Vertex(p,a)                           (p)->Vertex(a)
#define IDirect3DDevice2_Index(p,a)                            (p)->Index(a)
#define IDirect3DDevice2_End(p,a)                              (p)->End(a)
#define IDirect3DDevice2_GetRenderState(p,a,b)                 (p)->GetRenderState(a,b)
#define IDirect3DDevice2_SetRenderState(p,a,b)                 (p)->SetRenderState(a,b)
#define IDirect3DDevice2_GetLightState(p,a,b)                  (p)->GetLightState(a,b)
#define IDirect3DDevice2_SetLightState(p,a,b)                  (p)->SetLightState(a,b)
#define IDirect3DDevice2_SetTransform(p,a,b)                   (p)->SetTransform(a,b)
#define IDirect3DDevice2_GetTransform(p,a,b)                   (p)->GetTransform(a,b)
#define IDirect3DDevice2_MultiplyTransform(p,a,b)              (p)->MultiplyTransform(a,b)
#define IDirect3DDevice2_DrawPrimitive(p,a,b,c,d,e)            (p)->DrawPrimitive(a,b,c,d,e)
#define IDirect3DDevice2_DrawIndexedPrimitive(p,a,b,c,d,e,f,g) (p)->DrawIndexedPrimitive(a,b,c,d,e,f,g)
#define IDirect3DDevice2_SetClipStatus(p,a)                    (p)->SetClipStatus(a)
#define IDirect3DDevice2_GetClipStatus(p,a)                    (p)->GetClipStatus(a)
#endif

/*****************************************************************************
 * IDirect3DDevice3 interface
 */
#define INTERFACE IDirect3DDevice3
DECLARE_INTERFACE_(IDirect3DDevice3,IUnknown)
{
    /*** IUnknown methods ***/
    STDMETHOD_(HRESULT,QueryInterface)(THIS_ REFIID riid, void** ppvObject) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;
    /*** IDirect3DDevice3 methods ***/
    STDMETHOD(GetCaps)(THIS_ D3DDEVICEDESC *hal_desc, D3DDEVICEDESC *hel_desc) PURE;
    STDMETHOD(GetStats)(THIS_ D3DSTATS *stats) PURE;
    STDMETHOD(AddViewport)(THIS_ IDirect3DViewport3 *viewport) PURE;
    STDMETHOD(DeleteViewport)(THIS_ IDirect3DViewport3 *viewport) PURE;
    STDMETHOD(NextViewport)(THIS_ IDirect3DViewport3 *ref,
                            IDirect3DViewport3 **viewport, DWORD flags) PURE;
                            STDMETHOD(EnumTextureFormats)(THIS_ LPD3DENUMPIXELFORMATSCALLBACK cb, void *ctx) PURE;
                            STDMETHOD(BeginScene)(THIS) PURE;
                            STDMETHOD(EndScene)(THIS) PURE;
                            STDMETHOD(GetDirect3D)(THIS_ IDirect3D3 **d3d) PURE;
                            /*** DrawPrimitive API ***/
                            STDMETHOD(SetCurrentViewport)(THIS_ IDirect3DViewport3 *viewport) PURE;
                            STDMETHOD(GetCurrentViewport)(THIS_ IDirect3DViewport3 **viewport) PURE;
                            STDMETHOD(SetRenderTarget)(THIS_ IDirectDrawSurface4 *surface, DWORD flags) PURE;
                            STDMETHOD(GetRenderTarget)(THIS_ IDirectDrawSurface4 **surface) PURE;
                            STDMETHOD(Begin)(THIS_ D3DPRIMITIVETYPE d3dptPrimitiveType,DWORD dwVertexTypeDesc, DWORD dwFlags) PURE;
                            STDMETHOD(BeginIndexed)(THIS_ D3DPRIMITIVETYPE primitive_type, DWORD fvf,
                                                    void *vertices, DWORD vertex_count, DWORD flags) PURE;
                                                    STDMETHOD(Vertex)(THIS_ void *vertex) PURE;
                                                    STDMETHOD(Index)(THIS_ WORD wVertexIndex) PURE;
                                                    STDMETHOD(End)(THIS_ DWORD dwFlags) PURE;
                                                    STDMETHOD(GetRenderState)(THIS_ D3DRENDERSTATETYPE dwRenderStateType, LPDWORD lpdwRenderState) PURE;
                                                    STDMETHOD(SetRenderState)(THIS_ D3DRENDERSTATETYPE dwRenderStateType, DWORD dwRenderState) PURE;
                                                    STDMETHOD(GetLightState)(THIS_ D3DLIGHTSTATETYPE dwLightStateType, LPDWORD lpdwLightState) PURE;
                                                    STDMETHOD(SetLightState)(THIS_ D3DLIGHTSTATETYPE dwLightStateType, DWORD dwLightState) PURE;
                                                    STDMETHOD(SetTransform)(THIS_ D3DTRANSFORMSTATETYPE state, D3DMATRIX *matrix) PURE;
                                                    STDMETHOD(GetTransform)(THIS_ D3DTRANSFORMSTATETYPE state, D3DMATRIX *matrix) PURE;
                                                    STDMETHOD(MultiplyTransform)(THIS_ D3DTRANSFORMSTATETYPE state, D3DMATRIX *matrix) PURE;
                                                    STDMETHOD(DrawPrimitive)(THIS_ D3DPRIMITIVETYPE primitive_type, DWORD vertex_type,
                                                                             void *vertices, DWORD vertex_count, DWORD flags) PURE;
                                                                             STDMETHOD(DrawIndexedPrimitive)(THIS_ D3DPRIMITIVETYPE primitive_type, DWORD fvf,
                                                                                                             void *vertices, DWORD vertex_count, WORD *indices, DWORD index_count, DWORD flags) PURE;
                                                                                                             STDMETHOD(SetClipStatus)(THIS_ D3DCLIPSTATUS *clip_status) PURE;
                                                                                                             STDMETHOD(GetClipStatus)(THIS_ D3DCLIPSTATUS *clip_status) PURE;
                                                                                                             STDMETHOD(DrawPrimitiveStrided)(THIS_ D3DPRIMITIVETYPE primitive_type, DWORD fvf,
                                                                                                                                             D3DDRAWPRIMITIVESTRIDEDDATA *strided_data, DWORD vertex_count, DWORD flags) PURE;
                                                                                                                                             STDMETHOD(DrawIndexedPrimitiveStrided)(THIS_ D3DPRIMITIVETYPE primitive_type, DWORD fvf,
                                                                                                                                                                                    D3DDRAWPRIMITIVESTRIDEDDATA *strided_data, DWORD vertex_count, WORD *indices, DWORD index_count,
                                                                                                                                                                                    DWORD flags) PURE;
                                                                                                                                                                                    STDMETHOD(DrawPrimitiveVB)(THIS_ D3DPRIMITIVETYPE primitive_type, struct IDirect3DVertexBuffer *vb,
                                                                                                                                                                                                               DWORD start_vertex, DWORD vertex_count, DWORD flags) PURE;
                                                                                                                                                                                                               STDMETHOD(DrawIndexedPrimitiveVB)(THIS_ D3DPRIMITIVETYPE primitive_type, struct IDirect3DVertexBuffer *vb,
                                                                                                                                                                                                                                                 WORD *indices, DWORD index_count, DWORD flags) PURE;
                                                                                                                                                                                                                                                 STDMETHOD(ComputeSphereVisibility)(THIS_ D3DVECTOR *centers, D3DVALUE *radii, DWORD sphere_count,
                                                                                                                                                                                                                                                                DWORD flags, DWORD *ret) PURE;
                                                                                                                                                                                                                                                                STDMETHOD(GetTexture)(THIS_ DWORD stage, IDirect3DTexture2 **texture) PURE;
                                                                                                                                                                                                                                                                STDMETHOD(SetTexture)(THIS_ DWORD stage, IDirect3DTexture2 *texture) PURE;
                                                                                                                                                                                                                                                                STDMETHOD(GetTextureStageState)(THIS_ DWORD dwStage,D3DTEXTURESTAGESTATETYPE d3dTexStageStateType,LPDWORD lpdwState) PURE;
                                                                                                                                                                                                                                                                STDMETHOD(SetTextureStageState)(THIS_ DWORD dwStage,D3DTEXTURESTAGESTATETYPE d3dTexStageStateType,DWORD dwState) PURE;
                                                                                                                                                                                                                                                                STDMETHOD(ValidateDevice)(THIS_ LPDWORD lpdwPasses) PURE;
};
#undef INTERFACE

#if !defined(__cplusplus) || defined(CINTERFACE)
/*** IUnknown methods ***/
#define IDirect3DDevice3_QueryInterface(p,a,b) (p)->lpVtbl->QueryInterface(p,a,b)
#define IDirect3DDevice3_AddRef(p)             (p)->lpVtbl->AddRef(p)
#define IDirect3DDevice3_Release(p)            (p)->lpVtbl->Release(p)
/*** IDirect3DDevice3 methods ***/
#define IDirect3DDevice3_GetCaps(p,a,b)                        (p)->lpVtbl->GetCaps(p,a,b)
#define IDirect3DDevice3_GetStats(p,a)                         (p)->lpVtbl->GetStats(p,a)
#define IDirect3DDevice3_AddViewport(p,a)                      (p)->lpVtbl->AddViewport(p,a)
#define IDirect3DDevice3_DeleteViewport(p,a)                   (p)->lpVtbl->DeleteViewport(p,a)
#define IDirect3DDevice3_NextViewport(p,a,b,c)                 (p)->lpVtbl->NextViewport(p,a,b,c)
#define IDirect3DDevice3_EnumTextureFormats(p,a,b)             (p)->lpVtbl->EnumTextureFormats(p,a,b)
#define IDirect3DDevice3_BeginScene(p)                         (p)->lpVtbl->BeginScene(p)
#define IDirect3DDevice3_EndScene(p)                           (p)->lpVtbl->EndScene(p)
#define IDirect3DDevice3_GetDirect3D(p,a)                      (p)->lpVtbl->GetDirect3D(p,a)
#define IDirect3DDevice3_SetCurrentViewport(p,a)               (p)->lpVtbl->SetCurrentViewport(p,a)
#define IDirect3DDevice3_GetCurrentViewport(p,a)               (p)->lpVtbl->GetCurrentViewport(p,a)
#define IDirect3DDevice3_SetRenderTarget(p,a,b)                (p)->lpVtbl->SetRenderTarget(p,a,b)
#define IDirect3DDevice3_GetRenderTarget(p,a)                  (p)->lpVtbl->GetRenderTarget(p,a)
#define IDirect3DDevice3_Begin(p,a,b,c)                        (p)->lpVtbl->Begin(p,a,b,c)
#define IDirect3DDevice3_BeginIndexed(p,a,b,c,d,e)             (p)->lpVtbl->BeginIndexed(p,a,b,c,d,e)
#define IDirect3DDevice3_Vertex(p,a)                           (p)->lpVtbl->Vertex(p,a)
#define IDirect3DDevice3_Index(p,a)                            (p)->lpVtbl->Index(p,a)
#define IDirect3DDevice3_End(p,a)                              (p)->lpVtbl->End(p,a)
#define IDirect3DDevice3_GetRenderState(p,a,b)                 (p)->lpVtbl->GetRenderState(p,a,b)
#define IDirect3DDevice3_SetRenderState(p,a,b)                 (p)->lpVtbl->SetRenderState(p,a,b)
#define IDirect3DDevice3_GetLightState(p,a,b)                  (p)->lpVtbl->GetLightState(p,a,b)
#define IDirect3DDevice3_SetLightState(p,a,b)                  (p)->lpVtbl->SetLightState(p,a,b)
#define IDirect3DDevice3_SetTransform(p,a,b)                   (p)->lpVtbl->SetTransform(p,a,b)
#define IDirect3DDevice3_GetTransform(p,a,b)                   (p)->lpVtbl->GetTransform(p,a,b)
#define IDirect3DDevice3_MultiplyTransform(p,a,b)              (p)->lpVtbl->MultiplyTransform(p,a,b)
#define IDirect3DDevice3_DrawPrimitive(p,a,b,c,d,e)            (p)->lpVtbl->DrawPrimitive(p,a,b,c,d,e)
#define IDirect3DDevice3_DrawIndexedPrimitive(p,a,b,c,d,e,f,g) (p)->lpVtbl->DrawIndexedPrimitive(p,a,b,c,d,e,f,g)
#define IDirect3DDevice3_SetClipStatus(p,a)                    (p)->lpVtbl->SetClipStatus(p,a)
#define IDirect3DDevice3_GetClipStatus(p,a)                    (p)->lpVtbl->GetClipStatus(p,a)
#define IDirect3DDevice3_DrawPrimitiveStrided(p,a,b,c,d,e)     (p)->lpVtbl->DrawPrimitiveStrided(p,a,b,c,d,e)
#define IDirect3DDevice3_DrawIndexedPrimitiveStrided(p,a,b,c,d,e,f,g) (p)->lpVtbl->DrawIndexedPrimitiveStrided(p,a,b,c,d,e,f,g)
#define IDirect3DDevice3_DrawPrimitiveVB(p,a,b,c,d,e)          (p)->lpVtbl->DrawPrimitiveVB(p,a,b,c,d,e)
#define IDirect3DDevice3_DrawIndexedPrimitiveVB(p,a,b,c,d,e)   (p)->lpVtbl->DrawIndexedPrimitiveVB(p,a,b,c,d,e)
#define IDirect3DDevice3_ComputeSphereVisibility(p,a,b,c,d,e)  (p)->lpVtbl->ComputeSphereVisibility(p,a,b,c,d,e)
#define IDirect3DDevice3_GetTexture(p,a,b)                     (p)->lpVtbl->GetTexture(p,a,b)
#define IDirect3DDevice3_SetTexture(p,a,b)                     (p)->lpVtbl->SetTexture(p,a,b)
#define IDirect3DDevice3_GetTextureStageState(p,a,b,c)         (p)->lpVtbl->GetTextureStageState(p,a,b,c)
#define IDirect3DDevice3_SetTextureStageState(p,a,b,c)         (p)->lpVtbl->SetTextureStageState(p,a,b,c)
#define IDirect3DDevice3_ValidateDevice(p,a)                   (p)->lpVtbl->ValidateDevice(p,a)
#else
/*** IUnknown methods ***/
#define IDirect3DDevice3_QueryInterface(p,a,b) (p)->QueryInterface(a,b)
#define IDirect3DDevice3_AddRef(p)             (p)->AddRef()
#define IDirect3DDevice3_Release(p)            (p)->Release()
/*** IDirect3DDevice3 methods ***/
#define IDirect3DDevice3_GetCaps(p,a,b)                        (p)->GetCaps(a,b)
#define IDirect3DDevice3_GetStats(p,a)                         (p)->GetStats(a)
#define IDirect3DDevice3_AddViewport(p,a)                      (p)->AddViewport(a)
#define IDirect3DDevice3_DeleteViewport(p,a)                   (p)->DeleteViewport(a)
#define IDirect3DDevice3_NextViewport(p,a,b,c)                 (p)->NextViewport(a,b,c)
#define IDirect3DDevice3_EnumTextureFormats(p,a,b)             (p)->EnumTextureFormats(a,b)
#define IDirect3DDevice3_BeginScene(p)                         (p)->BeginScene()
#define IDirect3DDevice3_EndScene(p)                           (p)->EndScene()
#define IDirect3DDevice3_GetDirect3D(p,a)                      (p)->GetDirect3D(a)
#define IDirect3DDevice3_SetCurrentViewport(p,a)               (p)->SetCurrentViewport(a)
#define IDirect3DDevice3_GetCurrentViewport(p,a)               (p)->GetCurrentViewport(a)
#define IDirect3DDevice3_SetRenderTarget(p,a,b)                (p)->SetRenderTarget(a,b)
#define IDirect3DDevice3_GetRenderTarget(p,a)                  (p)->GetRenderTarget(a)
#define IDirect3DDevice3_Begin(p,a,b,c)                        (p)->Begin(a,b,c)
#define IDirect3DDevice3_BeginIndexed(p,a,b,c,d,e)             (p)->BeginIndexed(a,b,c,d,e)
#define IDirect3DDevice3_Vertex(p,a)                           (p)->Vertex(a)
#define IDirect3DDevice3_Index(p,a)                            (p)->Index(a)
#define IDirect3DDevice3_End(p,a)                              (p)->End(a)
#define IDirect3DDevice3_GetRenderState(p,a,b)                 (p)->GetRenderState(a,b)
#define IDirect3DDevice3_SetRenderState(p,a,b)                 (p)->SetRenderState(a,b)
#define IDirect3DDevice3_GetLightState(p,a,b)                  (p)->GetLightState(a,b)
#define IDirect3DDevice3_SetLightState(p,a,b)                  (p)->SetLightState(a,b)
#define IDirect3DDevice3_SetTransform(p,a,b)                   (p)->SetTransform(a,b)
#define IDirect3DDevice3_GetTransform(p,a,b)                   (p)->GetTransform(a,b)
#define IDirect3DDevice3_MultiplyTransform(p,a,b)              (p)->MultiplyTransform(a,b)
#define IDirect3DDevice3_DrawPrimitive(p,a,b,c,d,e)            (p)->DrawPrimitive(a,b,c,d,e)
#define IDirect3DDevice3_DrawIndexedPrimitive(p,a,b,c,d,e,f,g) (p)->DrawIndexedPrimitive(a,b,c,d,e,f,g)
#define IDirect3DDevice3_SetClipStatus(p,a)                    (p)->SetClipStatus(a)
#define IDirect3DDevice3_GetClipStatus(p,a)                    (p)->GetClipStatus(a)
#define IDirect3DDevice3_DrawPrimitiveStrided(p,a,b,c,d,e)     (p)->DrawPrimitiveStrided(a,b,c,d,e)
#define IDirect3DDevice3_DrawIndexedPrimitiveStrided(p,a,b,c,d,e,f,g) (p)->DrawIndexedPrimitiveStrided(a,b,c,d,e,f,g)
#define IDirect3DDevice3_DrawPrimitiveVB(p,a,b,c,d,e)          (p)->DrawPrimitiveVB(a,b,c,d,e)
#define IDirect3DDevice3_DrawIndexedPrimitiveVB(p,a,b,c,d,e)   (p)->DrawIndexedPrimitiveVB(a,b,c,d,e)
#define IDirect3DDevice3_ComputeSphereVisibility(p,a,b,c,d,e)  (p)->ComputeSphereVisibility(a,b,c,d,e)
#define IDirect3DDevice3_GetTexture(p,a,b)                     (p)->GetTexture(a,b)
#define IDirect3DDevice3_SetTexture(p,a,b)                     (p)->SetTexture(a,b)
#define IDirect3DDevice3_GetTextureStageState(p,a,b,c)         (p)->GetTextureStageState(a,b,c)
#define IDirect3DDevice3_SetTextureStageState(p,a,b,c)         (p)->SetTextureStageState(a,b,c)
#define IDirect3DDevice3_ValidateDevice(p,a)                   (p)->ValidateDevice(a)
#endif

/*****************************************************************************
 * IDirect3DDevice7 interface
 */
#define INTERFACE IDirect3DDevice7
DECLARE_INTERFACE_(IDirect3DDevice7,IUnknown)
{
    /*** IUnknown methods ***/
    STDMETHOD_(HRESULT,QueryInterface)(THIS_ REFIID riid, void** ppvObject) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;
    /*** IDirect3DDevice7 methods ***/
    STDMETHOD(GetCaps)(THIS_ D3DDEVICEDESC7 *desc) PURE;
    STDMETHOD(EnumTextureFormats)(THIS_ LPD3DENUMPIXELFORMATSCALLBACK cb, void *ctx) PURE;
    STDMETHOD(BeginScene)(THIS) PURE;
    STDMETHOD(EndScene)(THIS) PURE;
    STDMETHOD(GetDirect3D)(THIS_ IDirect3D7 **d3d) PURE;
    STDMETHOD(SetRenderTarget)(THIS_ IDirectDrawSurface7 *surface, DWORD flags) PURE;
    STDMETHOD(GetRenderTarget)(THIS_ IDirectDrawSurface7 **surface) PURE;
    STDMETHOD(Clear)(THIS_ DWORD count, D3DRECT *rects, DWORD flags, D3DCOLOR color, D3DVALUE z, DWORD stencil) PURE;
    STDMETHOD(SetTransform)(THIS_ D3DTRANSFORMSTATETYPE state, D3DMATRIX *matrix) PURE;
    STDMETHOD(GetTransform)(THIS_ D3DTRANSFORMSTATETYPE state, D3DMATRIX *matrix) PURE;
    STDMETHOD(SetViewport)(THIS_ D3DVIEWPORT7 *data) PURE;
    STDMETHOD(MultiplyTransform)(THIS_ D3DTRANSFORMSTATETYPE state, D3DMATRIX *matrix) PURE;
    STDMETHOD(GetViewport)(THIS_ D3DVIEWPORT7 *data) PURE;
    STDMETHOD(SetMaterial)(THIS_ D3DMATERIAL7 *data) PURE;
    STDMETHOD(GetMaterial)(THIS_ D3DMATERIAL7 *data) PURE;
    STDMETHOD(SetLight)(THIS_ DWORD idx, D3DLIGHT7 *data) PURE;
    STDMETHOD(GetLight)(THIS_ DWORD idx, D3DLIGHT7 *data) PURE;
    STDMETHOD(SetRenderState)(THIS_ D3DRENDERSTATETYPE dwRenderStateType, DWORD dwRenderState) PURE;
    STDMETHOD(GetRenderState)(THIS_ D3DRENDERSTATETYPE dwRenderStateType, LPDWORD lpdwRenderState) PURE;
    STDMETHOD(BeginStateBlock)(THIS) PURE;
    STDMETHOD(EndStateBlock)(THIS_ LPDWORD lpdwBlockHandle) PURE;
    STDMETHOD(PreLoad)(THIS_ IDirectDrawSurface7 *surface) PURE;
    STDMETHOD(DrawPrimitive)(THIS_ D3DPRIMITIVETYPE primitive_type, DWORD fvf,
                             void *vertices, DWORD vertex_count, DWORD flags) PURE;
                             STDMETHOD(DrawIndexedPrimitive)(THIS_ D3DPRIMITIVETYPE primitive_type, DWORD fvf,
                                                             void *vertices, DWORD vertex_count, WORD *indices, DWORD index_count, DWORD flags) PURE;
                                                             STDMETHOD(SetClipStatus)(THIS_ D3DCLIPSTATUS *clip_status) PURE;
                                                             STDMETHOD(GetClipStatus)(THIS_ D3DCLIPSTATUS *clip_status) PURE;
                                                             STDMETHOD(DrawPrimitiveStrided)(THIS_ D3DPRIMITIVETYPE primitive_type, DWORD fvf,
                                                                                             D3DDRAWPRIMITIVESTRIDEDDATA *strided_data, DWORD vertex_count, DWORD flags) PURE;
                                                                                             STDMETHOD(DrawIndexedPrimitiveStrided)(THIS_ D3DPRIMITIVETYPE primitive_type, DWORD fvf,
                                                                                                                                    D3DDRAWPRIMITIVESTRIDEDDATA *strided_data, DWORD vertex_count, WORD *indices, DWORD index_count,
                                                                                                                                    DWORD flags) PURE;
                                                                                                                                    STDMETHOD(DrawPrimitiveVB)(THIS_ D3DPRIMITIVETYPE primitive_type, struct IDirect3DVertexBuffer7 *vb,
                                                                                                                                                               DWORD start_vertex, DWORD vertex_count, DWORD flags) PURE;
                                                                                                                                                               STDMETHOD(DrawIndexedPrimitiveVB)(THIS_ D3DPRIMITIVETYPE primitive_type, struct IDirect3DVertexBuffer7 *vb,
                                                                                                                                                                                                 DWORD start_vertex, DWORD vertex_count, WORD *indices, DWORD index_count, DWORD flags) PURE;
                                                                                                                                                                                                 STDMETHOD(ComputeSphereVisibility)(THIS_ D3DVECTOR *centers, D3DVALUE *radii, DWORD sphere_count,
                                                                                                                                                                                                                                    DWORD flags, DWORD *ret) PURE;
                                                                                                                                                                                                                                    STDMETHOD(GetTexture)(THIS_ DWORD stage, IDirectDrawSurface7 **surface) PURE;
                                                                                                                                                                                                                                    STDMETHOD(SetTexture)(THIS_ DWORD stage, IDirectDrawSurface7 *surface) PURE;
                                                                                                                                                                                                                                    STDMETHOD(GetTextureStageState)(THIS_ DWORD dwStage,D3DTEXTURESTAGESTATETYPE d3dTexStageStateType,LPDWORD lpdwState) PURE;
                                                                                                                                                                                                                                    STDMETHOD(SetTextureStageState)(THIS_ DWORD dwStage,D3DTEXTURESTAGESTATETYPE d3dTexStageStateType,DWORD dwState) PURE;
                                                                                                                                                                                                                                    STDMETHOD(ValidateDevice)(THIS_ LPDWORD lpdwPasses) PURE;
                                                                                                                                                                                                                                    STDMETHOD(ApplyStateBlock)(THIS_ DWORD dwBlockHandle) PURE;
                                                                                                                                                                                                                                    STDMETHOD(CaptureStateBlock)(THIS_ DWORD dwBlockHandle) PURE;
                                                                                                                                                                                                                                    STDMETHOD(DeleteStateBlock)(THIS_ DWORD dwBlockHandle) PURE;
                                                                                                                                                                                                                                    STDMETHOD(CreateStateBlock)(THIS_ D3DSTATEBLOCKTYPE d3dsbType,LPDWORD lpdwBlockHandle) PURE;
                                                                                                                                                                                                                                    STDMETHOD(Load)(THIS_ IDirectDrawSurface7 *dst_surface, POINT *dst_point,
                                                                                                                                                                                                                                                    IDirectDrawSurface7 *src_surface, RECT *src_rect, DWORD flags) PURE;
                                                                                                                                                                                                                                                    STDMETHOD(LightEnable)(THIS_ DWORD dwLightIndex,WINBOOL bEnable) PURE;
                                                                                                                                                                                                                                                    STDMETHOD(GetLightEnable)(THIS_ DWORD dwLightIndex,WINBOOL *pbEnable) PURE;
                                                                                                                                                                                                                                                    STDMETHOD(SetClipPlane)(THIS_ DWORD dwIndex,D3DVALUE *pPlaneEquation) PURE;
                                                                                                                                                                                                                                                    STDMETHOD(GetClipPlane)(THIS_ DWORD dwIndex,D3DVALUE *pPlaneEquation) PURE;
                                                                                                                                                                                                                                                    STDMETHOD(GetInfo)(THIS_ DWORD info_id, void *info, DWORD info_size) PURE;
};
#undef INTERFACE

#if !defined(__cplusplus) || defined(CINTERFACE)
/*** IUnknown methods ***/
#define IDirect3DDevice7_QueryInterface(p,a,b)                        (p)->lpVtbl->QueryInterface(p,a,b)
#define IDirect3DDevice7_AddRef(p)                                    (p)->lpVtbl->AddRef(p)
#define IDirect3DDevice7_Release(p)                                   (p)->lpVtbl->Release(p)
/*** IDirect3DDevice7 methods ***/
#define IDirect3DDevice7_GetCaps(p,a)                                 (p)->lpVtbl->GetCaps(p,a)
#define IDirect3DDevice7_EnumTextureFormats(p,a,b)                    (p)->lpVtbl->EnumTextureFormats(p,a,b)
#define IDirect3DDevice7_BeginScene(p)                                (p)->lpVtbl->BeginScene(p)
#define IDirect3DDevice7_EndScene(p)                                  (p)->lpVtbl->EndScene(p)
#define IDirect3DDevice7_GetDirect3D(p,a)                             (p)->lpVtbl->GetDirect3D(p,a)
#define IDirect3DDevice7_SetRenderTarget(p,a,b)                       (p)->lpVtbl->SetRenderTarget(p,a,b)
#define IDirect3DDevice7_GetRenderTarget(p,a)                         (p)->lpVtbl->GetRenderTarget(p,a)
#define IDirect3DDevice7_Clear(p,a,b,c,d,e,f)                         (p)->lpVtbl->Clear(p,a,b,c,d,e,f)
#define IDirect3DDevice7_SetTransform(p,a,b)                          (p)->lpVtbl->SetTransform(p,a,b)
#define IDirect3DDevice7_GetTransform(p,a,b)                          (p)->lpVtbl->GetTransform(p,a,b)
#define IDirect3DDevice7_SetViewport(p,a)                             (p)->lpVtbl->SetViewport(p,a)
#define IDirect3DDevice7_MultiplyTransform(p,a,b)                     (p)->lpVtbl->MultiplyTransform(p,a,b)
#define IDirect3DDevice7_GetViewport(p,a)                             (p)->lpVtbl->GetViewport(p,a)
#define IDirect3DDevice7_SetMaterial(p,a)                             (p)->lpVtbl->SetMaterial(p,a)
#define IDirect3DDevice7_GetMaterial(p,a)                             (p)->lpVtbl->GetMaterial(p,a)
#define IDirect3DDevice7_SetLight(p,a,b)                              (p)->lpVtbl->SetLight(p,a,b)
#define IDirect3DDevice7_GetLight(p,a,b)                              (p)->lpVtbl->GetLight(p,a,b)
#define IDirect3DDevice7_SetRenderState(p,a,b)                        (p)->lpVtbl->SetRenderState(p,a,b)
#define IDirect3DDevice7_GetRenderState(p,a,b)                        (p)->lpVtbl->GetRenderState(p,a,b)
#define IDirect3DDevice7_BeginStateBlock(p)                           (p)->lpVtbl->BeginStateBlock(p)
#define IDirect3DDevice7_EndStateBlock(p,a)                           (p)->lpVtbl->EndStateBlock(p,a)
#define IDirect3DDevice7_PreLoad(p,a)                                 (p)->lpVtbl->PreLoad(p,a)
#define IDirect3DDevice7_DrawPrimitive(p,a,b,c,d,e)                   (p)->lpVtbl->DrawPrimitive(p,a,b,c,d,e)
#define IDirect3DDevice7_DrawIndexedPrimitive(p,a,b,c,d,e,f,g)        (p)->lpVtbl->DrawIndexedPrimitive(p,a,b,c,d,e,f,g)
#define IDirect3DDevice7_SetClipStatus(p,a)                           (p)->lpVtbl->SetClipStatus(p,a)
#define IDirect3DDevice7_GetClipStatus(p,a)                           (p)->lpVtbl->GetClipStatus(p,a)
#define IDirect3DDevice7_DrawPrimitiveStrided(p,a,b,c,d,e)            (p)->lpVtbl->DrawPrimitiveStrided(p,a,b,c,d,e)
#define IDirect3DDevice7_DrawIndexedPrimitiveStrided(p,a,b,c,d,e,f,g) (p)->lpVtbl->DrawIndexedPrimitiveStrided(p,a,b,c,d,e,f,g)
#define IDirect3DDevice7_DrawPrimitiveVB(p,a,b,c,d,e)                 (p)->lpVtbl->DrawPrimitiveVB(p,a,b,c,d,e)
#define IDirect3DDevice7_DrawIndexedPrimitiveVB(p,a,b,c,d,e,f,g)      (p)->lpVtbl->DrawIndexedPrimitiveVB(p,a,b,c,d,e,f,g)
#define IDirect3DDevice7_ComputeSphereVisibility(p,a,b,c,d,e)         (p)->lpVtbl->ComputeSphereVisibility(p,a,b,c,d,e)
#define IDirect3DDevice7_GetTexture(p,a,b)                            (p)->lpVtbl->GetTexture(p,a,b)
#define IDirect3DDevice7_SetTexture(p,a,b)                            (p)->lpVtbl->SetTexture(p,a,b)
#define IDirect3DDevice7_GetTextureStageState(p,a,b,c)                (p)->lpVtbl->GetTextureStageState(p,a,b,c)
#define IDirect3DDevice7_SetTextureStageState(p,a,b,c)                (p)->lpVtbl->SetTextureStageState(p,a,b,c)
#define IDirect3DDevice7_ValidateDevice(p,a)                          (p)->lpVtbl->ValidateDevice(p,a)
#define IDirect3DDevice7_ApplyStateBlock(p,a)                         (p)->lpVtbl->ApplyStateBlock(p,a)
#define IDirect3DDevice7_CaptureStateBlock(p,a)                       (p)->lpVtbl->CaptureStateBlock(p,a)
#define IDirect3DDevice7_DeleteStateBlock(p,a)                        (p)->lpVtbl->DeleteStateBlock(p,a)
#define IDirect3DDevice7_CreateStateBlock(p,a,b)                      (p)->lpVtbl->CreateStateBlock(p,a,b)
#define IDirect3DDevice7_Load(p,a,b,c,d,e)                            (p)->lpVtbl->Load(p,a,b,c,d,e)
#define IDirect3DDevice7_LightEnable(p,a,b)                           (p)->lpVtbl->LightEnable(p,a,b)
#define IDirect3DDevice7_GetLightEnable(p,a,b)                        (p)->lpVtbl->GetLightEnable(p,a,b)
#define IDirect3DDevice7_SetClipPlane(p,a,b)                          (p)->lpVtbl->SetClipPlane(p,a,b)
#define IDirect3DDevice7_GetClipPlane(p,a,b)                          (p)->lpVtbl->GetClipPlane(p,a,b)
#define IDirect3DDevice7_GetInfo(p,a,b,c)                             (p)->lpVtbl->GetInfo(p,a,b,c)
#else
/*** IUnknown methods ***/
#define IDirect3DDevice7_QueryInterface(p,a,b)                        (p)->QueryInterface(a,b)
#define IDirect3DDevice7_AddRef(p)                                    (p)->AddRef()
#define IDirect3DDevice7_Release(p)                                   (p)->Release()
/*** IDirect3DDevice7 methods ***/
#define IDirect3DDevice7_GetCaps(p,a)                                 (p)->GetCaps(a)
#define IDirect3DDevice7_EnumTextureFormats(p,a,b)                    (p)->EnumTextureFormats(a,b)
#define IDirect3DDevice7_BeginScene(p)                                (p)->BeginScene()
#define IDirect3DDevice7_EndScene(p)                                  (p)->EndScene()
#define IDirect3DDevice7_GetDirect3D(p,a)                             (p)->GetDirect3D(a)
#define IDirect3DDevice7_SetRenderTarget(p,a,b)                       (p)->SetRenderTarget(a,b)
#define IDirect3DDevice7_GetRenderTarget(p,a)                         (p)->GetRenderTarget(a)
#define IDirect3DDevice7_Clear(p,a,b,c,d,e,f)                         (p)->Clear(a,b,c,d,e,f)
#define IDirect3DDevice7_SetTransform(p,a,b)                          (p)->SetTransform(a,b)
#define IDirect3DDevice7_GetTransform(p,a,b)                          (p)->GetTransform(a,b)
#define IDirect3DDevice7_SetViewport(p,a)                             (p)->SetViewport(a)
#define IDirect3DDevice7_MultiplyTransform(p,a,b)                     (p)->MultiplyTransform(a,b)
#define IDirect3DDevice7_GetViewport(p,a)                             (p)->GetViewport(a)
#define IDirect3DDevice7_SetMaterial(p,a)                             (p)->SetMaterial(a)
#define IDirect3DDevice7_GetMaterial(p,a)                             (p)->GetMaterial(a)
#define IDirect3DDevice7_SetLight(p,a,b)                              (p)->SetLight(a,b)
#define IDirect3DDevice7_GetLight(p,a,b)                              (p)->GetLight(a,b)
#define IDirect3DDevice7_SetRenderState(p,a,b)                        (p)->SetRenderState(a,b)
#define IDirect3DDevice7_GetRenderState(p,a,b)                        (p)->GetRenderState(a,b)
#define IDirect3DDevice7_BeginStateBlock(p)                           (p)->BeginStateBlock()
#define IDirect3DDevice7_EndStateBlock(p,a)                           (p)->EndStateBlock(a)
#define IDirect3DDevice7_PreLoad(p,a)                                 (p)->PreLoad(a)
#define IDirect3DDevice7_DrawPrimitive(p,a,b,c,d,e)                   (p)->DrawPrimitive(a,b,c,d,e)
#define IDirect3DDevice7_DrawIndexedPrimitive(p,a,b,c,d,e,f,g)        (p)->DrawIndexedPrimitive(a,b,c,d,e,f,g)
#define IDirect3DDevice7_SetClipStatus(p,a)                           (p)->SetClipStatus(a)
#define IDirect3DDevice7_GetClipStatus(p,a)                           (p)->GetClipStatus(a)
#define IDirect3DDevice7_DrawPrimitiveStrided(p,a,b,c,d,e)            (p)->DrawPrimitiveStrided(a,b,c,d,e)
#define IDirect3DDevice7_DrawIndexedPrimitiveStrided(p,a,b,c,d,e,f,g) (p)->DrawIndexedPrimitiveStrided(a,b,c,d,e,f,g)
#define IDirect3DDevice7_DrawPrimitiveVB(p,a,b,c,d,e)                 (p)->DrawPrimitiveVB(a,b,c,d,e)
#define IDirect3DDevice7_DrawIndexedPrimitiveVB(p,a,b,c,d,e,f,g)      (p)->DrawIndexedPrimitiveVB(a,b,c,d,e,f,g)
#define IDirect3DDevice7_ComputeSphereVisibility(p,a,b,c,d,e)         (p)->ComputeSphereVisibility(a,b,c,d,e)
#define IDirect3DDevice7_GetTexture(p,a,b)                            (p)->GetTexture(a,b)
#define IDirect3DDevice7_SetTexture(p,a,b)                            (p)->SetTexture(a,b)
#define IDirect3DDevice7_GetTextureStageState(p,a,b,c)                (p)->GetTextureStageState(a,b,c)
#define IDirect3DDevice7_SetTextureStageState(p,a,b,c)                (p)->SetTextureStageState(a,b,c)
#define IDirect3DDevice7_ValidateDevice(p,a)                          (p)->ValidateDevice(a)
#define IDirect3DDevice7_ApplyStateBlock(p,a)                         (p)->ApplyStateBlock(a)
#define IDirect3DDevice7_CaptureStateBlock(p,a)                       (p)->CaptureStateBlock(a)
#define IDirect3DDevice7_DeleteStateBlock(p,a)                        (p)->DeleteStateBlock(a)
#define IDirect3DDevice7_CreateStateBlock(p,a,b)                      (p)->CreateStateBlock(a,b)
#define IDirect3DDevice7_Load(p,a,b,c,d,e)                            (p)->Load(a,b,c,d,e)
#define IDirect3DDevice7_LightEnable(p,a,b)                           (p)->LightEnable(a,b)
#define IDirect3DDevice7_GetLightEnable(p,a,b)                        (p)->GetLightEnable(a,b)
#define IDirect3DDevice7_SetClipPlane(p,a,b)                          (p)->SetClipPlane(a,b)
#define IDirect3DDevice7_GetClipPlane(p,a,b)                          (p)->GetClipPlane(a,b)
#define IDirect3DDevice7_GetInfo(p,a,b,c)                             (p)->GetInfo(a,b,c)
#endif



/*****************************************************************************
 * IDirect3DVertexBuffer interface
 */
#define INTERFACE IDirect3DVertexBuffer
DECLARE_INTERFACE_(IDirect3DVertexBuffer,IUnknown)
{
    /*** IUnknown methods ***/
    STDMETHOD_(HRESULT,QueryInterface)(THIS_ REFIID riid, void** ppvObject) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;
    /*** IDirect3DVertexBuffer methods ***/
    STDMETHOD(Lock)(THIS_ DWORD flags, void **data, DWORD *data_size) PURE;
    STDMETHOD(Unlock)(THIS) PURE;
    STDMETHOD(ProcessVertices)(THIS_ DWORD vertex_op, DWORD dst_idx, DWORD count,
                               IDirect3DVertexBuffer *src_buffer, DWORD src_idx,
                               IDirect3DDevice3 *device, DWORD flags) PURE;
                               STDMETHOD(GetVertexBufferDesc)(THIS_ D3DVERTEXBUFFERDESC *desc) PURE;
                               STDMETHOD(Optimize)(THIS_ IDirect3DDevice3 *device, DWORD flags) PURE;
};
#undef INTERFACE

#if !defined(__cplusplus) || defined(CINTERFACE)
/*** IUnknown methods ***/
#define IDirect3DVertexBuffer_QueryInterface(p,a,b) (p)->lpVtbl->QueryInterface(p,a,b)
#define IDirect3DVertexBuffer_AddRef(p)             (p)->lpVtbl->AddRef(p)
#define IDirect3DVertexBuffer_Release(p)            (p)->lpVtbl->Release(p)
/*** IDirect3DVertexBuffer methods ***/
#define IDirect3DVertexBuffer_Lock(p,a,b,c)                    (p)->lpVtbl->Lock(p,a,b,c)
#define IDirect3DVertexBuffer_Unlock(p)                        (p)->lpVtbl->Unlock(p)
#define IDirect3DVertexBuffer_ProcessVertices(p,a,b,c,d,e,f,g) (p)->lpVtbl->ProcessVertices(p,a,b,c,d,e,f,g)
#define IDirect3DVertexBuffer_GetVertexBufferDesc(p,a)         (p)->lpVtbl->GetVertexBufferDesc(p,a)
#define IDirect3DVertexBuffer_Optimize(p,a,b)                  (p)->lpVtbl->Optimize(p,a,b)
#else
/*** IUnknown methods ***/
#define IDirect3DVertexBuffer_QueryInterface(p,a,b) (p)->QueryInterface(a,b)
#define IDirect3DVertexBuffer_AddRef(p)             (p)->AddRef()
#define IDirect3DVertexBuffer_Release(p)            (p)->Release()
/*** IDirect3DVertexBuffer methods ***/
#define IDirect3DVertexBuffer_Lock(p,a,b,c)                    (p)->Lock(a,b,c)
#define IDirect3DVertexBuffer_Unlock(p)                        (p)->Unlock()
#define IDirect3DVertexBuffer_ProcessVertices(p,a,b,c,d,e,f,g) (p)->ProcessVertices(a,b,c,d,e,f,g)
#define IDirect3DVertexBuffer_GetVertexBufferDesc(p,a)         (p)->GetVertexBufferDesc(a)
#define IDirect3DVertexBuffer_Optimize(p,a,b)                  (p)->Optimize(a,b)
#endif

/*****************************************************************************
 * IDirect3DVertexBuffer7 interface
 */
#define INTERFACE IDirect3DVertexBuffer7
DECLARE_INTERFACE_(IDirect3DVertexBuffer7,IUnknown)
{
    /*** IUnknown methods ***/
    STDMETHOD_(HRESULT,QueryInterface)(THIS_ REFIID riid, void** ppvObject) PURE;
    STDMETHOD_(ULONG,AddRef)(THIS) PURE;
    STDMETHOD_(ULONG,Release)(THIS) PURE;
    /*** IDirect3DVertexBuffer7 methods ***/
    STDMETHOD(Lock)(THIS_ DWORD flags, void **data, DWORD *data_size) PURE;
    STDMETHOD(Unlock)(THIS) PURE;
    STDMETHOD(ProcessVertices)(THIS_ DWORD vertex_op, DWORD dst_idx, DWORD count,
                               IDirect3DVertexBuffer7 *src_buffer, DWORD src_idx,
                               IDirect3DDevice7 *device, DWORD flags) PURE;
                               STDMETHOD(GetVertexBufferDesc)(THIS_ D3DVERTEXBUFFERDESC *desc) PURE;
                               STDMETHOD(Optimize)(THIS_ IDirect3DDevice7 *device, DWORD flags) PURE;
                               STDMETHOD(ProcessVerticesStrided)(THIS_ DWORD vertex_op, DWORD dst_idx, DWORD count,
                                                                 D3DDRAWPRIMITIVESTRIDEDDATA *data, DWORD fvf, IDirect3DDevice7 *device, DWORD flags) PURE;
};
#undef INTERFACE

#if !defined(__cplusplus) || defined(CINTERFACE)
/*** IUnknown methods ***/
#define IDirect3DVertexBuffer7_QueryInterface(p,a,b)                   (p)->lpVtbl->QueryInterface(p,a,b)
#define IDirect3DVertexBuffer7_AddRef(p)                               (p)->lpVtbl->AddRef(p)
#define IDirect3DVertexBuffer7_Release(p)                              (p)->lpVtbl->Release(p)
/*** IDirect3DVertexBuffer7 methods ***/
#define IDirect3DVertexBuffer7_Lock(p,a,b,c)                           (p)->lpVtbl->Lock(p,a,b,c)
#define IDirect3DVertexBuffer7_Unlock(p)                               (p)->lpVtbl->Unlock(p)
#define IDirect3DVertexBuffer7_ProcessVertices(p,a,b,c,d,e,f,g)        (p)->lpVtbl->ProcessVertices(p,a,b,c,d,e,f,g)
#define IDirect3DVertexBuffer7_GetVertexBufferDesc(p,a)                (p)->lpVtbl->GetVertexBufferDesc(p,a)
#define IDirect3DVertexBuffer7_Optimize(p,a,b)                         (p)->lpVtbl->Optimize(p,a,b)
#define IDirect3DVertexBuffer7_ProcessVerticesStrided(p,a,b,c,d,e,f,g) (p)->lpVtbl->ProcessVerticesStrided(p,a,b,c,d,e,f,g)
#else
/*** IUnknown methods ***/
#define IDirect3DVertexBuffer7_QueryInterface(p,a,b)                   (p)->QueryInterface(a,b)
#define IDirect3DVertexBuffer7_AddRef(p)                               (p)->AddRef()
#define IDirect3DVertexBuffer7_Release(p)                              (p)->Release()
/*** IDirect3DVertexBuffer7 methods ***/
#define IDirect3DVertexBuffer7_Lock(p,a,b,c)                           (p)->Lock(a,b,c)
#define IDirect3DVertexBuffer7_Unlock(p)                               (p)->Unlock()
#define IDirect3DVertexBuffer7_ProcessVertices(p,a,b,c,d,e,f,g)        (p)->ProcessVertices(a,b,c,d,e,f,g)
#define IDirect3DVertexBuffer7_GetVertexBufferDesc(p,a)                (p)->GetVertexBufferDesc(a)
#define IDirect3DVertexBuffer7_Optimize(p,a,b)                         (p)->Optimize(a,b)
#define IDirect3DVertexBuffer7_ProcessVerticesStrided(p,a,b,c,d,e,f,g) (p)->ProcessVerticesStrided(a,b,c,d,e,f,g)
#endif

#endif /* __WINE_D3D_H */
