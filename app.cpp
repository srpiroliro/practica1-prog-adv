#include <iostream>
#include <string>
#include <cctype> // legal?

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
            cout << ((status)?"■":"□") << ' '; // << ' ' here?
        }
    bool operator==(Bombeta a) {
        return a.getStatus()==getStatus();
    }
    bool operator!=(Bombeta a) {
        return a.getStatus()!=getStatus();
    }
};

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

        void visualitzar() {
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
int array_size(T ar[]){
    return sizeof(ar)/sizeof(ar[0]);
}

bool char_in_array(char c, char array[]){
    for (int i=0; i<array_size(array); i++){
        if(c==array[i]) return true;
    }
    return false;
}

int cin_verified_int(int min, int max, string msg="Tria un num. entre", string wrong=":( num. incorrecte. prova unaltre vegada "){
    int x;
    string rnge=" ["+to_string(min)+", "+to_string(max)+"] : ";
    cout << msg << rnge; cin >> x;
    while(!(min<=x && x<max) or (!x and int(x)!=0)){
        cout << wrong << rnge; 
        cin >> x;
    }
    cout << endl;
    return x;
}

int cin_expected_char(char options[], string wrong=":( char incorrecte. prova unaltre vegada: "){
    char c;
    cin >> c;
    while (!char_in_array(c, options)){
        cout << wrong << endl;
        cin >> c;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int tirada(Taulell t, int itera){
    cout << "\n================ " << itera << " ================\n" << endl;
    int x=cin_verified_int(0,t.getCols()-1, "coord x"),
        y=cin_verified_int(0,t.getRows()-1, "coord y");
    t.premerBombeta(y,x);
    t.visualitzar();
    cout << "\n===================================" << endl;

    return t.getEnceses();
}

void resum(int hist[], int total_b){
    cout << "\nHAS ACABAT!"<<endl;
    for(int i=0; i<array_size(hist); i++){
        cout << (i+1) << " -> " << hist[i] << " enceses i " << (total_b-hist[i]) << " apagades." << endl;
    }
}

bool continuar(){
    cout << "\nvols tornar a jugar? prem n o N per acabar (qualsevol altre per seguir)" << endl;
    char o; cin >> o;
    cout << "\n\n" << endl;
    return (char)tolower(o)!='n';
}

int main() {
    Taulell taulell=Taulell();

    int total_bomb=taulell.getRows()*taulell.getCols();
    bool game_over=false,cont=true;

    while(cont){
        int *history, tirades, encendre;

        taulell.apagar();

        encendre=cin_verified_int(1,total_bomb,"quantes vols encendre");
        tirades=cin_verified_int(1,99,"quantes tirades vols fer");
        history=new int[tirades];

        taulell.encendre(encendre);
        taulell.visualitzar();

        for(int i=0;i<tirades;i++){
            history[i]=tirada(taulell, i);
            
            if(history[i]==0) {
                cout << "\nHas perdut! Totes estan apagades!" << endl;
                break;
            }
        }
        
        resum(history, total_bomb);
        cont=continuar();

        delete history;
    }
    cout << "ADEU!" << endl;
    
    return 0;
}