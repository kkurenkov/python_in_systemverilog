#include <Python.h>
#include <stdlib.h>
int py_func(int x)
{
       // Set PYTHONPATH TO working directory
       setenv("PYTHONPATH",".",1);
       
       // This is a type which contains the information Python needs to treat a pointer to an object as an object.
       PyObject *pName, *pModule, *pDict, *pFunc, *pValue, *presult;

       // Initialize the Python interpreter. 
       // In an application embedding Python, this should be called before using any other Python/C API functions
       Py_Initialize();

       // Build the name object
       // Take a C printf()-style format string and a variable number of arguments, 
       // calculate the size of the resulting Python Unicode string and return a string with the values formatted into it.
       pName = PyUnicode_FromString("py_file");
       
       // Print a standard traceback to sys.stderr and clear the error indicator. 
       PyErr_Print(); 
       
       // Load the module object
       // This is a higher-level interface that calls the current “import hook function”
       pModule = PyImport_Import(pName);
       PyErr_Print();

       // pDict is a borrowed reference 
       // Return the dictionary object that implements module’s namespace; 
       // this object is the same as the __dict__ attribute of the module object.
       pDict = PyModule_GetDict(pModule);
       PyErr_Print();

       // pFunc is also a borrowed reference 
       pFunc = PyDict_GetItemString(pDict, (char*)"Python_Function");

       // int PyCallable_Check(PyObject *o)
       // Determine if the object o is callable.
       // Return 1 if the object is callable and 0 otherwise. This function always succeeds.
       if (PyCallable_Check(pFunc))
       {
              // PyObject *Py_BuildValue(const char *format, ...)
              // Create a new value based on a format string similar to those accepted by the PyArg_Parse* 
              // family of functions and a sequence of values.
              // Example
              // Py_BuildValue("i", 123)                  123
              // Py_BuildValue("iii", 123, 456, 789)      (123, 456, 789)
              // Py_BuildValue("s", "hello")              'hello'
              pValue=Py_BuildValue("(zi)",(char*)"Python_Function", x);
              PyErr_Print();
              printf("Let's give this a shot! x = %d\n", x);
              presult=PyObject_CallObject(pFunc,pValue);
              PyErr_Print();
       } else 
       {
              PyErr_Print();
       }
       // Return a C long representation of obj. If obj is not an instance of PyLongObject,
       // first call its __index__() method (if present) to convert it to a PyLongObject.
       printf("Result is %d\n",(unsigned int)PyLong_AsLong(presult));
       
       // Clean up

       // Decrement the reference count for object o. 
       Py_DECREF(pValue);
       Py_DECREF(pModule);
       Py_DECREF(pName);

       // Finish the Python Interpreter
       // Undo all initializations made by Py_Initialize() and subsequent use of Python/C API functions, 
       // and destroy all sub-interpreters
       Py_Finalize();
       return 0;
}


int main(int argc, char const *argv[])
{
       printf("Hello in main! \n"); 
       printf("Call py_func! \n"); 
       py_func(10);
       return 0;
}
