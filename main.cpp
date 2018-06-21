//
//  main.cpp
//
//  Created by Eiji Adachi Medeiros Barbosa
//

#include "TestTable.h"
#include <iostream>
#include <cassert>

using namespace std;

int main(int argc, const char * argv[]) {
    
    assert( testar_Inserir_Redimensionamento() );
    assert( testar_Remover_Redimensionamento() );
    
    cout << "\nTodos os testes rodaram sem falhas." << endl;
    
    return 0;
}
