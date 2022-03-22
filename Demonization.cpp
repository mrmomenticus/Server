#include "Demonization.h"
template<typename T>
void Demonization::examination(const T &value) {
    if (value != 0){
        exit(0);
    }
}
void Demonization::daemon() {
    parpid = fork();
    examination(parpid);

}




