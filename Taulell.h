#include <iostream>
#include "Bombeta.h"

using namespace std; 

class Taulell {
    Bombeta container[8][8];
    int rows,cols,enceses;

    public:
        Taulell(){
            rows=cols=8;
            enceses=0;
        }
        void encendre(int quantes){
            int x,y,i;
            for (i=0; i<quantes; i++){
                x=rand()%cols, y=rand()%rows;
                while (container[x][y].getStatus()) {
                    x=rand()%cols, y=rand()%rows;
                }

                container[x][y].setStatus(true);
                enceses++;
            }
        }

        void visualitzar(){
            for(int row=0; row<rows; row++){
                for(int col=0; col<cols; col++){
                    container[row][col].visualize();
                }
                cout << endl;
            }
        }

        void premerBombeta(int f, int c){
            int coordzX[9]={0,1,2, 2, 1,-1,-2,-2,-1};
            int coordzY[9]={0,2,1,-1,-2, 2, 1,-1,-2};

            for(int i=0; i<9; i++){
                int x=coordzX[i]+f, 
                    y=coordzY[i]+c;

                if(x<cols && y<rows && y>=0 && x>=0){
                    bool status=!(container[y][x].getStatus());
                    container[y][x].setStatus(status);

                    cout << x << ", " << y << " - " << status << endl;

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
        int getCols(){return cols;}
        int getRows(){return rows;}
        int getEnceses(){return enceses;}
        Bombeta getBombeta(int f,int c){return container[f][c];} // never used?
};
