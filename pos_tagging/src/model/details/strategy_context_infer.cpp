#include "Python.h"
#include "../strategy_context_infer.h"

namespace xforce { namespace nlu { namespace pos {

bool StrategyContextInfer::Init() {
  Py_Initialize();
  if ( !Py_IsInitialized() ) {
    FATAL("fail_init_python");
    return false;
  }

  PyObject *name = PyBytes_FromString("pytest");
  PyObject *module = PyImport_Import(name);
  if (nullptr == module) {
    FATAL("fail_import_module");
    return false;
  }

  PyObject *dict = PyModule_GetDict(module);
  if (nullptr == dict) {
    FATAL("fail_get_dict");
    return false;
  }

  PyObject *func = PyDict_GetItemString(dict, "add");
  if (nullptr == func || !PyCallable_Check(func) ) {
    FATAL("fail_get_method");
    return false;
  }


  return true;
}

void StrategyContextInfer::Process(basic::NluContext &nluContext) {
  //TODO
}

}}}
