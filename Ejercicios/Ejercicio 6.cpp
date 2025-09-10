#include <iostream>
#include <cstring>
using namespace std;

int main(){
    char frase[256] = "JOSE ME PUEDE CHUPAR LA VERGA EN REVERSA ";

    int contador = 0;

    char vocales[11] = "AEIOUaeiou";

    for(int i = 0 ; i < strlen(frase); i++){
            
        if (c == 'a'|| c == 'e'|| c == 'i'|| c == 'o'|| c == 'u'){
            contador++;
        }
        
    }
    
    cout << "Tiene " << contador << "vocales" << endl;
}