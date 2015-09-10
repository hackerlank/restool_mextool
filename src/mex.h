#ifndef __MEX_H__
#define __MEX_H__

#include "define.h"


#pragma pack(4)
typedef struct _Mtl
{
    vector<int>     blend;
    vector<int>     flags;
    vector<int>     texid;
    vector<float>   alpha;
} Mtl;

typedef struct _Face
{
    uint16 ids[3];
} Face;

typedef struct _Geo
{
    char name[80];
    int vert;
    int face;
    int mtlid;
    int lightmap;

    vector<vec3>           vertList;
    vector<uint32>         colorList;
    vector<vec3>           normalList;
    vector< vector<vec2> > uvList;
    vector<uint8>          boneList;
    vector<Face>           faceList;
} Geo;

#pragma pack()


class Mex
{
public:
	Mex(const char* filename);
	~Mex();

	void info();
	void save();
public:
	char 	 _path[255];
	ifstream _file;


    int              _version;
    vector<char*>    _texs;
    vector<Mtl>      _mtls;
    vector<Geo>      _geos;
};



#endif

