//
//  HashTable.h
//
//  Created by Eiji Adachi Medeiros Barbosa
//

#ifndef HashTable_h
#define HashTable_h

#include "HashEntry.h"
#include <string>

static const int TABLE_SIZE = 17;
static const float MIN_ALPHA = 0.125f;
static const float MAX_ALPHA = 0.5f;

class HashTable {
private:
    int size;
    
    int quantity;
    
    void init();
    
    unsigned long preHash(const std::string);
    
    unsigned long hash(const std::string);
    
    void resize(int);
    
    void reduce();
    
    void expand();
    
public:
    // Internamente, a Tabela Hash é este array para ponteiros de HashEntry.
    // Deixei público só pra facilitar a implementação dos testes.
    // Mais correto seria deixar este atributo priado.
    HashEntry<std::string, std::string> **data;
    
    HashTable();
    
    HashTable(const int size);
    
    ~HashTable();
    
    std::string get(const std::string key);
    
    bool put(const std::string key, const std::string value);
    
    bool remove(const std::string k);
    
    int getSize();
    
    int getQuantity();
    
    bool isEmpty();
    
    bool isFull();
    
    void print();
    
    float getAlpha();
};


#endif /* HashTable_h */
