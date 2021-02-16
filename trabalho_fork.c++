#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sstream>

using namespace std;

int h, m, s;

// pega a hora inicial(nascimento) e retorna a ela em segundos
time_t horas_nas(){
    struct tm *data_hora_ini;
    time_t ini;
    //pega a hora
    ini = time(NULL);
    //converte hora atual em segundos
    data_hora_ini = localtime(&ini);


    cout << " | "<< data_hora_ini->tm_hour << ":";
    cout << data_hora_ini->tm_min << ":";
    cout << data_hora_ini->tm_sec <<" |" <<endl;

    h = data_hora_ini->tm_hour;
    m = data_hora_ini->tm_min;
    s = data_hora_ini->tm_sec;

    return ini;
}

time_t ini_pai, ini_filho1, ini_filho2, ini_neto1, ini_neto2;



void horas_morte(time_t hora){
    
    struct tm *data_hora_fim;
    time_t fim;
    //pega a hora
    fim = time(NULL);
    //coverte hora atual para segundos
    data_hora_fim = localtime(&fim);


    int resultado = difftime(fim,hora);

    cout << " | "<< data_hora_fim->tm_hour << ":";
    cout << data_hora_fim->tm_min << ":";
    cout << data_hora_fim->tm_sec <<" |";
    cout << " tempo de vida: " << resultado <<endl;

}
void nascimento_filho1(){
    
    cout << "Filho 1 nasceu.  Hora do Nasci ";
    ini_filho1 = horas_nas();
   
}

void nascimento_filho2(){
    
    cout << "Filho 2 nasceu.  Hora do Nasci ";
    ini_filho2 = horas_nas();

}

void nascimento_neto1(){
    
    cout << "Neto 1 nasceu.   Hora do Nasci ";
    ini_neto1 = horas_nas();

}

void nascimento_neto2(){
    
    cout << "Neto 2 nasceu.   Hora do Nasci ";
    ini_neto2 = horas_nas();
    cout << " " << endl;
    cout << "****************************************************************************" << endl;
    cout << " " << endl;
}
void morte_neto1(){

    sleep(12);
    cout << "Neto 1 morreu. Hora do Nasci: | " << h << ":" << m << ":" << s << " |";
    cout << "Hora da Morte ";
    horas_morte(ini_neto1); 

}

void morte_neto2(){
    
    sleep(18);
    cout << "Neto 2 morreu. Hora do Nasci: | " << localtime(&ini_neto2)->tm_hour << ":" << m << ":" << s << " |";
    cout << "Hora da Morte ";
    horas_morte(ini_neto2);

}

void morte_filho1(){
    
    sleep(18);
    cout << "Filho 1 morreu. Hora do Nasci: | " << h << ":" << m << ":" << s << " |";
    cout << "Hora da Morte ";
    horas_morte(ini_filho1);

}

void morte_filho2(){
    
    sleep(16);
    cout << "Filho 2 morreu. Hora do Nasci: | " << h << ":" << m << ":" << s << " |";
    cout << "Hora da Morte ";
    horas_morte(ini_filho2);

}

void morte_pai(){
    
    sleep(16);
    cout << "Pai    morreu. Hora do Nasci: | " << h << ":" << m << ":" << s << " |";
    cout << "Hora da Morte ";
    horas_morte(ini_pai);    

}


int main(){
    pid_t familia[4] ={-1, -1, -1, -1};

    cout << "Pai nasceu.      Hora do Nasci ";
    
    ini_pai = horas_nas(); //guarda hora que o pai nasce

    //espera 14 anos(sec)
    sleep(14);
   
    //primeiro filho
    familia[0] = fork();
    if (familia[0] < 0){
        cout << "Erro ao criar o processo filho 1" << endl;
        return 1;
    }
    else if (familia[0] == 0){
        
        nascimento_filho1();   

        //primeiro neto
        familia[2] = fork();
        
        sleep(12);
        if(familia[2] < 0){
            cout << "Erro ao criar o processo neto 1" << endl;

        }
        else if (familia[2] == 0) {
            
            nascimento_neto1(); 
            wait(NULL);
            morte_neto1(); 
            
            exit(0);
    
        }
        
        morte_filho1();
        wait(NULL);
       
        exit(0); 
        
    }else{
        //segundo filho
        familia[1] = fork();

        if(familia[1] < 0){
            cout << "Erro ao criar processo filho 2" << endl;
            return 1;

        }
        else if (familia[1] == 0){
            sleep(2);
            
            nascimento_filho2();   
            //segundo neto
            familia[3] = fork();
            sleep(14);
            
            if(familia[3] < 0){
                cout << "Erro ao criar processo neto 2" << endl;
                return 1;
            }
            else if (familia[3] == 0){
                
                
                nascimento_neto2(); 
                wait(NULL); 
                morte_neto2();

                exit(0); 

            }

        
            morte_filho2();
            wait(NULL);

            exit(0);
        }
    
    }
    
        wait(NULL);
        morte_pai();


        exit(0);
}