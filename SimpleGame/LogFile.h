#ifndef LogFile_h_
#define LogFile_h_

#include <fstream>
#include <time.h>

class LogFile
{
public:
    static LogFile* get(){
        static LogFile instance;
        return &instance;
    }

    //
    void log(int level, int code, std::string msg){
        if (initialized){
            time_t t;
            time(&t);
            char str[0x100];
            if(!ctime_s(str, 0x100, &t)){
                str[24] = '\0';//we change \n to \0.
                out << str << ", ";
            }

            out << level << ", " << code << ", "
                << msg << std::endl << std::flush;
        }
    }
    
    ~LogFile(){
        if (initialized){
            out.close();
        }
    }
private:
    std::ofstream out;
    bool initialized;


    LogFile(){
        initialized = false;
        out.open("log.txt", std::ios::out |  std::ios::app);
        if (out.is_open()){
            initialized = true;
            time_t t;
            time(&t);
            char str[0x100];
            if(!ctime_s(str, 0x100, &t)){
                str[24] = '\0';//we change \n to \0.
                out << str;
            }
            out << "  ========== New Instance ==========" << std::endl << std::flush;
            
        }
    }

    
};

#endif

