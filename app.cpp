#include <iostream>
#include <string>


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
            cout << ((status)?'X':'O') << ' '; // << ' ' here?
        }
    bool operator==(Bombeta a) {
        return a.getStatus()==getStatus();
    }
    bool operator!=(Bombeta a) {
        return a.getStatus()!=getStatus();
    }

    /* En  la  implementació  és  imprescindible  que  un  mètode  invoqui  a  l’altre  usant  la 
    simbologia de l’operador. ??? */
};


class Taulell {
    Bombeta container[8][8];
    int rows;
    int cols;
    int enceses;

    public:
        Taulell(){
            rows=cols=8;
            enceses=0;
        }
        void encendre(int quantes){
            
            int x,y,i;
            cout << container[0][0].status << '\n';

            for (i=0; i<quantes; i++){

                x=rand()%cols;
                y=rand()%rows;

                while (container[x][y].getStatus()) {
                    x=rand()*cols;
                    y=rand()*rows;
                }

                // no need to check if quantes == 8x8
                container[x][y].setStatus(true);
                enceses++;
            }
        }

        void visualitzar() {
            for(int row=0; row<rows; row++){
                for(int col=0; col<cols; col++){
                    container[row][col].visualize();
                }
                cout << endl;
            }
        }

        void premerBombeta(int f, int c){
            int coordzX[9]={0,1,2,2,1,-1,-2,-2,1};
            int coordzY[9]={0,2,1,1,2,-2,-1,-1,-2};

            for(int i=0; i<9; i++){
                int x=coordzX[i]+f, y=coordzY[i]+c;
                if(x<cols && y<rows && y>=0 && x>=0){
                    bool status=container[y][x].getStatus();
                    container[y][x].setStatus(!status);

                    if(status) enceses++;
                    else enceses--;
                }
            }
        }

        void apagar(){
            for(int row=0; row<rows; row++){
                for(int col=0; col<cols; col++){
                    container[row][col].setStatus(false);
                }
            }
            enceses=0;
        }


        // GETTERS
        int getCols(){
            return cols;
        }
        int getRows(){
            return rows;
        }
        int getEnceses(){
            return enceses;
        }
        Bombeta getBombeta(int f,int c){
            return container[f][c];
        }


};

int main() {

    int encendre=3;
    Taulell t=Taulell();
    t.encendre(encendre);
    t.visualitzar();
    
    return 0;
}
// https://www.tutorialspoint.com/cplusplus/cpp_overloading.htm
