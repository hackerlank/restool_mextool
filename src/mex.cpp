#include "util.h"
#include "mex.h"


Mex::Mex(const char* filename)
{
	strcpy(_path, filename);
	_file.open(filename, ios::in|ios::binary);
	_file.seekg(0);

    uint32 ftag;
    uint32 size;
    
    int n;
    char* p;

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







