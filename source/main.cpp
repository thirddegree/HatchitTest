/**
**    Hatchit Engine
**    Copyright(c) 2015 Third-Degree
**
**    GNU Lesser General Public License
**    This file may be used under the terms of the GNU Lesser
**    General Public License version 3 as published by the Free
**    Software Foundation and appearing in the file LICENSE.LGPLv3 included
**    in the packaging of this file. Please review the following information
**    to ensure the GNU Lesser General Public License requirements
**    will be met: https://www.gnu.org/licenses/lgpl.html
**
**/


#include <ht_application.h>
#include <ht_debug.h>
#include <ht_os.h>
#include <ht_bitmap.h>
#include <HatchitTest.h>
#include <Python.h>

using namespace Hatchit;
using namespace Hatchit::Core;
using namespace Hatchit::Image;
using namespace Hatchit::Game;

int main(int argc, char* argv[])
{
    PyObject *pName, *pModule, *pDict, *pFunc;
    PyObject *pArgs, *pValue;
    int i;

   /* if (argc < 3) {
        fprintf(stderr, "Usage: call pythonfile funcname [args]\n");
        return 1;
    }*/

    std::string exe_path = os_exec_dir();
    std::wstring wexe_path(exe_path.begin(), exe_path.end());
    std::string pylib_dir = os_path("python/lib");
    std::string pyscript_dir = os_path("python/");
    std::wstring pylib = (wexe_path + std::wstring(pylib_dir.begin(), pylib_dir.end()));
    std::wstring pyscript = (wexe_path + std::wstring(pyscript_dir.begin(), pyscript_dir.end()));
    std::wstring python_path = pylib + L";" + pyscript;
    Py_SetPath(python_path.c_str());

    Py_Initialize();
    pName = PyUnicode_FromString("bobchock");
    /* Error checking of pName left out */

    pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule != NULL) {
        pFunc = PyObject_GetAttrString(pModule, "multiply");
        /* pFunc is a new reference */

        if (pFunc && PyCallable_Check(pFunc)) {
            pArgs = PyTuple_New(2);
            for (i = 0; i < 2; ++i) {
                pValue = PyLong_FromLong(2);
                if (!pValue) {
                    Py_DECREF(pArgs);
                    Py_DECREF(pModule);
                    fprintf(stderr, "Cannot convert argument\n");
                    return 1;
                }
                /* pValue reference stolen here: */
                PyTuple_SetItem(pArgs, i, pValue);
            }
            pValue = PyObject_CallObject(pFunc, pArgs);
            Py_DECREF(pArgs);
            if (pValue != NULL) {
                printf("Result of call: %ld\n", PyLong_AsLong(pValue));
                Py_DECREF(pValue);
            }
            else {
                Py_DECREF(pFunc);
                Py_DECREF(pModule);
                PyErr_Print();
                fprintf(stderr, "Call failed\n");
                return 1;
            }
        }
        else {
            if (PyErr_Occurred())
                PyErr_Print();
            fprintf(stderr, "Cannot find function \"%s\"\n", "multiply");
        }
        Py_XDECREF(pFunc);
        Py_DECREF(pModule);
    }
    else {
        PyErr_Print();
        fprintf(stderr, "Failed to load \"%s\"\n", "bobchock");
        return 1;
    }
    Py_Finalize();

    return 0;
}
