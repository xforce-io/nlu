#include "Python.h"
#include "../strategy_context_infer.h"
#include "../../conf/conf.h"

namespace xforce { namespace nlu { namespace pos {

bool StrategyContextInfer::Init() {
  /*
  Py_Initialize();
  if (!Py_IsInitialized()) {
    FATAL("fail_init_python");
    return false;
  }

  PyRun_SimpleString("import sys");
  PyRun_SimpleString("sys.path.append('../../context_infer/')");

  PyObject *name = PyUnicode_DecodeFSDefault("context_infer");
  PyObject *module = PyImport_Import(name);
  if (nullptr == module) {
    FATAL("fail_import_module_from[" 
        << *StrHelper::Str2Wstr(Conf::Get().GetPathContextInfer()) 
        << "]");
    return false;
  }

  PyObject *dict = PyModule_GetDict(module);
  if (nullptr == dict) {
    FATAL("fail_get_dict");
    return false;
  }

  PyObject *func = PyDict_GetItemString(dict, "pred");
  if (nullptr == func || !PyCallable_Check(func) ) {
    FATAL("fail_get_method");
    return false;
  }
  */
  return true;
}

void StrategyContextInfer::Process(basic::NluContext &nluContext) {
  UNUSE(nluContext)
}

}}}
