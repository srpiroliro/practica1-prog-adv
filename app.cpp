#include <iostream>
#include <string>
#include <cctype> // legal?
#include "Taulell.h"

using namespace std; 

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cin_verified_int(int min, int max, string msg="Tria un num. entre", string wrong=":( num. incorrecte. prova un altre vegada "){
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int tirada(Taulell &t, int itera){
    cout << "\n================ " << itera << " ================\n" << endl;
    int x=cin_verified_int(0,t.getCols()-1, "coord x"),
        y=cin_verified_int(0,t.getRows()-1, "coord y");
    t.premerBombeta(y,x);
    t.visualitzar();
    cout << "\n===================================" << endl;

    return t.getEnceses();
}

void resum(int hist[], int t, int total_b){
    cout << "\nHAS ACABAT!"<<endl;
    for(int i=0; i<t; i++){
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
        resum(history, tirades, total_bomb);
        cont=continuar();

        delete history;
    }
    cout << "ADEU!" << endl;
    
    return 0;
}