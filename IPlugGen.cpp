#include "IPlugGen.h"
#include "IPlug_include_in_plug_src.h"
#include "IControl.h"
#include "resource.h"

const int kNumPrograms = 1;

IPlugGen::IPlugGen(IPlugInstanceInfo instanceInfo)
  : IPLUG_CTOR(num_params(), kNumPrograms, instanceInfo)
{
  TRACE;

  gen = (CommonState *)create(44100., DEFAULT_BLOCK_SIZE);
  
  for (int i = 0; i< num_params(); i++) {
    ParamInfo* p = gen->params+i;
    GetParam(i)->InitDouble(p->name, p->defaultvalue, p->outputmin, p->outputmax, 0.00001 /*step*/, p->units);
  }

  MakeDefaultPreset((char *) "-", kNumPrograms);
}

IPlugGen::~IPlugGen() 
{
  destroy(gen);
}

void IPlugGen::ProcessDoubleReplacing(double** inputs, double** outputs, int nFrames)
{
  // Mutex is already locked for us.

  perform(gen, inputs, num_inputs(), outputs, num_outputs(), nFrames);
}

void IPlugGen::Reset()
{
  TRACE;
  IMutexLock lock(this);
  
  gen->sr = GetSampleRate();
  reset(gen);
}

void IPlugGen::OnParamChange(int paramIdx)
{
  IMutexLock lock(this);

  setparameter(gen, paramIdx, GetParam(paramIdx)->Value(), 0);
}
