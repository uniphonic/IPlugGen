#ifndef __IPLUGGEN__
#define __IPLUGGEN__

#include "IPlug_include_in_plug_hdr.h"

#include "gen_exported.h"
using namespace gen_exported;

class IPlugGen : public IPlug
{
public:
  IPlugGen(IPlugInstanceInfo instanceInfo);
  ~IPlugGen();

  void Reset();
  void OnParamChange(int paramIdx);
  void ProcessDoubleReplacing(double** inputs, double** outputs, int nFrames);

private:
  CommonState *gen;
};

#endif
