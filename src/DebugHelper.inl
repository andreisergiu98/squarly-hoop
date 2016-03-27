#include "DebugHelper.h"

template<typename T>
void DebugHelper::print(T data) {
    cout << data << ' ';
}

template<typename T, typename... Args>
void DebugHelper::print(T t, Args... args) {
    if(dbgmsg) {
        cout << "DEBUG_MESSAGE: ";
        dbgmsg = !dbgmsg;
    }

    cout << t << ' ';

    print(args...);

    if(!dbgmsg) {

        cout << endl;

        dbgmsg = !dbgmsg;
    }
}
