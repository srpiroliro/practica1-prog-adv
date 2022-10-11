#include <iostream>
using namespace std; 

class Bombeta {
    public:
        bool status;
        Bombeta() {
            status=false;
        }

        // setter
        void setStatus(bool new_status){
            status=new_status;
        }

        // getter
        bool getStatus(){
            return bool(status);
        }

        void visualize(){
            cout << ((status)?"■":"□") << ' ';
        }
    
    bool operator==(Bombeta a) {
        return a.getStatus()==getStatus();
    }
    bool operator!=(Bombeta a) {
        return a.getStatus()!=getStatus();
    }
};

