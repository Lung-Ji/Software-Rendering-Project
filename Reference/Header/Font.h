#pragma once
#include "Component.h"


BEGIN(Engine)
struct ENGINE_DLL FontINFO {
  wstring MSG;
  UINT  WEIGHT, WIDTH, MIPLEVELS;
  BOOL  ITALIC;
  DWORD CHARSET;
  DWORD OUTPUTPRECISION;
  DWORD QUALITY;
  DWORD PITCHANDFAMILY;
  LPCWSTR FACENAME;

  FontINFO(CONST TCHAR* _msg, UINT _weight, UINT _width, UINT _mipLevels, BOOL _italic,
    DWORD _charset, DWORD _outputprecision, DWORD _quality, DWORD _pitchandfamily,
    DWORD _facename) :MSG(_msg), WEIGHT(_weight), WIDTH(_width), MIPLEVELS(_mipLevels),
    ITALIC(false), CHARSET(DEFAULT_CHARSET), OUTPUTPRECISION(1), QUALITY(DEFAULT_QUALITY),
    PITCHANDFAMILY(DEFAULT_PITCH), FACENAME(L"Times New Roman"){}
};

class ENGINE_DLL Font : public Component {
private:


};

END