#include "util.h"
#include "mex.h"


Mex::Mex(const char* filename)
{
	strcpy(_path, filename);
	_file.open(filename, ios::in|ios::binary);
	_file.seekg(0);

    uint32 ftag;
    uint32 size;
    
    streamoff pos;
    int n;
    int ni;
    float nf;
    char* p;
    Mtl* mtl;
    Geo* geo;

    while(_file.good())
    {
	    _file.read((char *)&ftag, 4);
	    _file.read((char *)&size, 4);
        switch(FTAG(ftag))
        {
        case 'vers':
	        _file.read((char *)&_version, 4);
            break;
        case 'texs':
	        _file.read((char *)&n, 4);
            for(int i = 0; i < n; i++)
            {
                p = new char[256];
                _file.read(p, 256);
                _texs.push_back(p);
            }
            break;
        case 'mtls':
            break;
        case 'matl':
            n = _mtls.size();
            _mtls.resize(n + 1);
            mtl = &_mtls[n];
            break;
        case 'lays':
	        _file.read((char *)&n, 4);
            for(int i = 0; i < n; i++)
            {
	            _file.read((char *)&ni, 4);
                mtl->blend.push_back(ni);
	            _file.read((char *)&ni, 4);
                mtl->flags.push_back(ni);
	            _file.read((char *)&ni, 4);
                mtl->texid.push_back(ni);
	            _file.read((char *)&nf, 4);
                mtl->alpha.push_back(nf);
            }
            break;
        case 'geom':
	        _file.read((char *)&n, 4);//0
            break;
        case 'chks':
            n = _geos.size();
            _geos.resize(n + 1);
            geo = &_geos[n];

	        _file.read((char *)&(geo->vert), 4);
	        _file.read((char *)&(geo->face), 4);
	        _file.read((char *)&(geo->mtlid), 4);

            geo->vertList.resize(geo->vert);
	        _file.read((char *)&(geo->vertList[0]), sizeof(vec3) * geo->vert);

            geo->normalList.resize(geo->vert);
	        _file.read((char *)&(geo->normalList[0]), sizeof(vec3) * geo->vert);

            geo->uvList.resize(1);
            geo->uvList[0].resize(geo->vert);
	        _file.read((char *)&(geo->uvList[0][0]), sizeof(vec2) * geo->vert);

            geo->boneList.resize(geo->vert);
	        _file.read((char *)&(geo->boneList[0]), sizeof(uint8) * geo->vert);

            geo->faceList.resize(geo->face);
	        _file.read((char *)&(geo->faceList[0]), sizeof(Face) * geo->face);

            break;
        case 'mtuv':
            pos = _file.tellg() + (streamoff)size;
	        _file.read((char *)&n, 4);
            geo->uvList.resize(n);
            for(int i = 1; i < n; i++)
            {
                geo->uvList[i].resize(geo->vert);
	            _file.read((char *)&(geo->uvList[i][0]), sizeof(vec2) * geo->vert);
            }
            if(_file.tellg() < pos)
	            _file.read((char *)&(geo->lightmap), 4);
            else
                geo->lightmap = 0;

            break;
        case 'vcol':
            geo->colorList.resize(geo->vert);
	        _file.read((char *)&(geo->colorList[0]), sizeof(uint32) * geo->vert);
            break;
        case 'name':
	        _file.read((char *)&(geo->name), 80);
            break;
        default:
            _file.seekg(_file.tellg() + (streamoff)size);
            break;
        }
    }

}


Mex::~Mex()
{
	_file.close();
}


void Mex::info()
{
	cout << "=================================================" << endl;
	cout << "[Head]" << _path << endl;
    cout << "version " << dec << showbase << _version << endl; 
    cout << "texs    " << dec << showbase << _texs.size() << endl; 
    cout << "mtls    " << dec << showbase << _mtls.size() << endl; 
    cout << "geos    " << dec << showbase << _geos.size() << endl; 
	cout << "=================================================" << endl;
    cout << dec << showbase << endl;


    for(int i = 0; i < _texs.size(); i++)
    {
        cout << "tex " << _texs[i] << endl;
    }
    for(int i = 0; i < _geos.size(); i++)
    {
        cout << "geo " << _geos[i].name << endl;
    }
}

void Mex::save()
{

}







