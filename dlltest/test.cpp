// https://helloacm.com/how-to-use-the-dynamic-link-library-in-c-linux-gcc-compiler/
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
 
// function export from the *.so
typedef double (*double_ptr)(double);
 
int main(int argc, char **argv) {
    char *error;
    double_ptr GetDouble;
    void *handle;
    // open the *.so
    handle = dlopen ("./libhello.so", RTLD_LAZY);
    if (!handle) {
        fputs (dlerror(), stderr);
        exit(1);
    }
    // get the function address and make it ready for use
    GetDouble = (double_ptr)dlsym(handle, "GetDouble");
    if ((error = dlerror()) != NULL)  {
        fputs(error, stderr);
        exit(1);
    }
    // call the function in *.so
    printf ("%f\n", (*GetDouble)(2.0));
    // remember to free the resource
    dlclose(handle);
}