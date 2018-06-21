//
//  TestTable.cpp
//
//  Created by Eiji Adachi Medeiros Barbosa
//

#include "TestTable.h"
#include "HashTable.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

extern HashEntry<std::string, std::string> *ENTRY_DELETED;

bool testar_Inserir_Redimensionamento()
{
    cout << "INÍCIO: Testes Inserir-Redimensionamento" << endl;
    
    int tamanho = 117;
    
    HashTable tabela(tamanho);
    
    vector<string> itensInseridos;
    vector<string> chavesInseridas;
    
    int i = 0;
    do
    {
        string iStr = to_string(i);
        string chave = "chave-" + iStr;
        string valor = "valor-" + iStr;
        
        chavesInseridas.push_back(chave);
        itensInseridos.push_back(valor);
        
        tabela.put(chave, valor);

        i++;
    } while( tabela.getAlpha() < MAX_ALPHA );
    
    
    // Quando chegar aqui, está exatamente antes de fazer o redimensionamento
    int tamanhoAntes = tabela.getSize();
    
    string chaveNova = "ChaveNova";
    chavesInseridas.push_back(chaveNova);
    
    string valorNovo = "ConteudoNovo";
    itensInseridos.push_back(valorNovo);
    
    tabela.put( chaveNova, valorNovo);
    
    int tamanhoDepois = tabela.getSize();
    
    if( 1 + 2*tamanhoAntes != tamanhoDepois )
    {
        cout << "\t*ERRO - Teste Inserir_Redimensionamento: Tabela não foi redimensionada corretamente. Tamanho antes de inserir = " << tamanhoAntes << ". Tamanho depois de inserir = " << tamanhoDepois << ". Esperado após inserir era: " << 1+2*tamanhoAntes << endl;
        
        return false;
    }
    
    // Verifica se todos elementos que estavam antes do redimensionamento continuam na tabela
    for(string chave : chavesInseridas)
    {
        bool achou = false;
        for(int i = 0; i < tabela.getSize(); i++)
        {
            HashEntry<string, string>* entry = tabela.data[i];
            
            if(entry != nullptr && entry != ENTRY_DELETED && entry->getKey() == chave)
            {
                achou = true;
                break;
            }
        }
        if(!achou)
        {
            cout << "\t*ERRO - Teste Inserir_Redimensionamento: O item com chave igual a "<< chave << " estava na tabela antes do redimensionamento, mas não se encontra após." << endl;
            
            return false;
        }
    }
    
    // Verifica se todos elementos que estão na tabela após o redimensionamento já estavam na tabela
    for(int i = 0; i < tabela.getSize(); i++)
    {
        HashEntry<string, string>* entry = tabela.data[i];
        if(entry != nullptr && entry != ENTRY_DELETED)
        {
            bool achou = false;
            for(string chave : chavesInseridas)
            {
                if( entry->getKey() == chave )
                {
                    achou = true;
                    break;
                }
            }
            if(!achou)
            {
                cout << "\t*ERRO - Teste Inserir_Redimensionamento: Item com chave igual a "<< entry->getKey() << " está na tabela após o redimensionamento, mas não se encontrava antes." << endl;
                
                return false;
            }
        }
    }
    
    cout << "FIM: Testes Inserir-Redimensionamento\n" << endl;
    
    return true;
}

bool testar_Remover_Redimensionamento()
{
    cout << "INÍCIO: Testes Remover-Redimensionamento" << endl;
    
    bool removeu = true;
    
    int tamanho = 177;
    
    HashTable tabela(tamanho);
    
    // Essas quantidades evitam que a tabela sofra um redimensionamento
    int qtdInserido = tamanho/2;
    
    // Inicialização da tabela
    for(int i = 1; i <= qtdInserido; i++)
    {
        string iStr = to_string(i);
        string chave = "chave-" + iStr;
        string valor = "valor-" + iStr;
        
        if(!tabela.put(chave, valor))
        {
            cout << "\t*ERRO - Teste Remover_Redimensionamento: Não conseguiu inserir item: " << chave << "," << valor << endl;
            return false;
        }
    }
    
    int counter = qtdInserido;
    
    // Faça remoções sucessivas até ficar prestes a redimensionar
    do
    {
        string iStr = to_string(counter--);
        string chave = "chave-" + iStr;
        
        removeu = tabela.remove(chave);
        
        if(!removeu)
        {
            tabela.print();
            cout << chave << endl;
            cout << "\t*ERRO - Teste Remover_Redimensionamento: Não removeu corretamente item com chave igual a: " << chave << endl;
            return false;
        }
    }
    while( tabela.getAlpha() > MIN_ALPHA );
    
    // Ao chegar aqui a Tabela está prestes a sofrer uma redução no seu tamanho, basta mais uma remoção
    // Escolhe uma chave qualquer para remover item
    string chave;
    
    for(int i = 0; i < tabela.getSize(); i++)
    {
        HashEntry<string, string>* entry = tabela.data[i];
        if(entry != nullptr && entry != ENTRY_DELETED)
        {
            chave = entry->getKey();
            break;
        }
    }
    
    int tamanhoAntes = tabela.getSize();
    
    removeu = tabela.remove(chave);
    
    int tamanhoDepois = tabela.getSize();
    
    if( 1+tamanhoAntes/2 != tamanhoDepois )
    {
        cout << "\t*ERRO - Teste Remover_Redimensionamento: Tabela não foi redimensionada corretamente. Tamanho antes de remover = " << tamanhoAntes << ". Tamanho depois de remover = " << tamanhoDepois << ". Esperado após inserir era: " << 1+tamanho/2 << endl;
        removeu = false;
    }
    
    cout << "FIM: Testes Remover-Redimensionamento\n" << endl;
    
    return removeu;
}
