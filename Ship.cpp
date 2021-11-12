#include "Ship.h"

Ship::Ship(){
    m_shipName = "My ship";
    m_shipRank = {'D'};
    m_numMaterials = 0;
}
Ship::Ship(string name){
    //initialize variables
    m_shipName = name;
    m_shipRank = {'D'};
    m_numMaterials = 0;

}
string Ship::GetName(){
    //returns the name
    return m_shipName;
}
void Ship::SetName(string name){
    //changes the name
    m_shipName = name;
}
int Ship::CheckMaterial(Material material){
    //iterates the list of material and returns index
    for (int i = 0; i < PROJ2_SIZE; i++){
        if (material.m_name == m_myMaterials[i].m_name)
            return i;
    }
    return -1;
}
void Ship::AddMaterial(Material material){
    //adds a material to the material list
    m_myMaterials[m_numMaterials] = material;
    m_numMaterials += 1;
}
void Ship::IncrementQuantity(Material material){
    // adds one to m_quantity
    for (int i = 0; i < PROJ2_SIZE; i++){
        if (material.m_name == m_myMaterials[i].m_name)
            m_myMaterials[i].m_quantity += 1;
    }
}
bool Ship::DecrementQuantity(Material material) {
    //decreases one to m_quantity returns false if this isn't possible
    for (int i = 0; i < PROJ2_SIZE; i++) {
        if (material.m_name == m_myMaterials[i].m_name) {
            if (m_myMaterials[i].m_quantity > 0) {
                m_myMaterials[i].m_quantity -= 1;
                return true;
            } else {
                return false;
            }
        }
    }
    return false;
}
bool Ship::CheckQuantity(Material material1, Material material2){
    //checks m_quantity of both materials to make sure it's greater than one
    if (material1.m_name == material2.m_name){
        if (material1.m_quantity > 1){
            return true;
        }
    }else{
        if (material1.m_quantity > 0 and material2.m_quantity > 0){
            return true;
        }
    }
    return false;
}
Material Ship::GetMaterial(int index){
    //returns material based on index
    return m_myMaterials[index];
}
void Ship::IncRank() {
    // increases the rank
    if (int(m_shipRank) == 68) {
        m_shipRank = {'C'};
    } else if (int(m_shipRank) == 67) {
        m_shipRank = {'B'};
    } else if (int(m_shipRank) == 66) {
        m_shipRank = {'A'};
    } else if (int(m_shipRank) == 65) {
        m_shipRank = {'S'};
    }
}
char Ship::GetRank(){
    //returns the ship's rank
    return m_shipRank;
}
