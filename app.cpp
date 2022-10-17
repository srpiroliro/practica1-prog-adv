#include <iostream>
#include <string>

#include "classes/Taulell.h"

using namespace std; 

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int cin_verified_int(int min, int max, string msg="Tria un num. entre", string wrong=":( num. incorrecte. prova un altre vegada "){
    int x;
    string rnge=" ["+to_string(min)+", "+to_string(max)+"] : ";
    cout << msg << rnge; cin >> x;
    while(!(min<=x && x<=max) or (!x and int(x)!=0)){
        cout << wrong << rnge; 
        cin >> x;
    }
    return x;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int tirada(Taulell &t, int itera){
    cout << "\n================ " << itera << " ================\n" << '\n';
    int x=cin_verified_int(0,t.getCols()-1, "coord x"),
        y=cin_verified_int(0,t.getRows()-1, "coord y");
    cout << '\n';
    t.premerBombeta(x,y);
    t.visualitzar();
    cout << "\n===================================" << '\n';

    return t.getEnceses();
}

void resum(int hist[], int t, int total_b){
    int darkest=hist[0];
    cout << "\nHAS ACABAT!"<<endl;
    for(int i=0; i<t; i++){
        cout << (i+1) << " -> " << hist[i] << " enceses i " << (total_b-hist[i]) << " apagades." << '\n';
        if(hist[i]<darkest) darkest=i;
    }

    cout << "\nLa tirada mes fosca ha sigut: " << (darkest+1) << " amb " << hist[darkest] << " enceses" << endl;
}

int* dades(int total_bombetes){
    int d[2]={
        cin_verified_int(1,total_bombetes,"quantes vols encendre"),
        cin_verified_int(1,99,"quantes tirades vols fer")
    };
    return d;
}

bool continuar(){
    cout << "\nvols tornar a jugar? prem n o N per acabar (qualsevol altre per seguir)" << '\n';
    char o; cin >> o;
    cout << '\n' << endl;
    return (char)tolower(o)!='n';
}

bool tornarJugar(Taulell *taulell){
    if(continuar()){
        taulell->apagar();
        return true;
    } else return false;
}

int main() {
    Taulell taulell=Taulell();

    int total_bomb=taulell.getRows()*taulell.getCols();
    bool game_over=false,cont=true;

    while(cont){
        int *history, tirades, encendre;

        cout << "===================================" << '\n' << "===================================" << "\n\n\n";
        encendre=cin_verified_int(1,total_bomb,"quantes vols encendre");
        tirades=cin_verified_int(1,99,"quantes tirades vols fer");
        cout << '\n';

        history=new int[tirades];

        taulell.encendre(encendre);
        taulell.visualitzar();

        int tirades_fetes=0;
        while(tirades_fetes<tirades){
            history[tirades_fetes]=tirada(taulell, tirades_fetes);
            
            bool totes_apagades=history[tirades_fetes]==0;
            if(totes_apagades) {
                cout << "\nHas guanyat! Totes estan apagades!" << endl;
                break;
            } else tirades_fetes++;
            
        }
        resum(history, tirades_fetes, total_bomb);
        delete history;

        cont=tornarJugar(&taulell);
    }
    cout << "ADEU!" << endl;
    
    return 0;
}