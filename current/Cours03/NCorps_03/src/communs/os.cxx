
#include <sys/types.h>
#include <cstring>
#include <cstdlib>
#include <string>
#include <cstdio>

#include "os.hxx"

#ifdef _WIN32
#include <direct.h>
#else
#include <unistd.h>
#endif

bool fileExists(const std::string & fileName)
{
    FILE *file = fopen(fileName.c_str(), "rb");
    if (file) {
        fclose(file);
        return true;
   } else {
        return false;
   }
}

