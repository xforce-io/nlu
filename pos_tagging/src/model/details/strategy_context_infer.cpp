#include "Python.h"
#include "../strategy_context_infer.h"

namespace xforce { namespace nlu { namespace pos {

bool StrategyContextInfer::Init() {
  Py_Initialize();
  if ( !Py_IsInitialized() ) {
    return false;
  }

  PyObject *name = PyBytes_FromString("pytest");
  PyObject *module = PyImport_Import(name);
  if (nullptr == module) {
    return false;
  }

  PyObject *dict = PyModule_GetDict(module);
  if (nullptr == dict) {
    return false;
  }

  PyObject *func = PyDict_GetItemString(dict, "add");
  if (nullptr == func || !PyCallable_Check(func) ) {
    return false;
  }


  return true;
}

void StrategyContextInfer::Process(basic::NluContext &nluContext) {
  //TODO
}

}}}
