#include "Game.h"
#include <ctime>

Game::Game(){
    // prints title, gets name of ship and creates a ship object
    GameTitle();
    cout << "What is the name of your ship?" << endl;
    string name;
    getline(cin, name);
    m_myShip = Ship(name);

}
void Game::LoadMaterials(){
    // initializes variables used to split info
    string material_list[4];
    string data_line;
    int material_count = 0;
    ifstream theFile(PROJ2_DATA);
    //getline to read through every line
    if(theFile.is_open()) {
        while (getline(theFile, data_line)) {
            string data1 = "";
            int count = 0;
            //for loop to iterate through every character in the line
            for (int j = 0; j < int(data_line.length()); j += 1) {
                //if statement to split through by comma b/c 44 = ',' and put the pieces into the material_list
                if (int(data_line[j]) == 44) {
                    material_list[count] = data1;
                    count += 1;
                    data1 = "";
                } else {
                    data1 += data_line[j];
                }
            }
            material_list[3] = data1;
            //put all pieces together to create the object and add it to the game, and ship
            Material load_material = Material(material_list[0], material_list[1], material_list[2], material_list[3], 0);
            m_materials[material_count] = load_material;
            m_myShip.AddMaterial(load_material);
            material_count += 1;

        }
    }else {
        cout << "Error opening file." << endl;
    }
    theFile.close();
    cout << material_count << " materials loaded." << endl;
}
void Game::StartGame(){
    LoadMaterials();
    int menu_option;
    Material unique_array[5];
    // while loop to keep the continuation of the game
    do{
        menu_option = MainMenu();
        if (menu_option == 1){
            DisplayMaterials();
        }else if (menu_option == 2){
            SearchMaterials();
        }else if (menu_option == 3){
            CombineMaterials();
        }else if (menu_option == 4){
            CalcScore();
        }
        //for loop to keep track of the different unique items gained throughout the game
        //once one is gained it will be put in the unique_array so that the player will have to find 4 different ones
        for(int j = 0; j < PROJ2_SIZE; j += 1){
            if (m_myShip.GetMaterial(j).m_type == "unique" and m_myShip.GetMaterial(j).m_quantity > 0){
                if (m_myShip.GetRank() == 'D'){
                    unique_array[0] = m_myShip.GetMaterial(j);
                    m_myShip.IncRank();
                    cout << "*****NEW unique item found! Rank up!*****" << endl;
                }else if (m_myShip.GetRank() == 'C'){
                    if (unique_array[0].m_name != m_myShip.GetMaterial(j).m_name){
                        unique_array[1] = m_myShip.GetMaterial(j);
                        m_myShip.IncRank();
                        cout << "*****NEW unique item found! Rank up!*****" << endl;
                    }
                }else if (m_myShip.GetRank() == 'B'){
                    if (unique_array[0].m_name != m_myShip.GetMaterial(j).m_name and
                        unique_array[1].m_name != m_myShip.GetMaterial(j).m_name){
                        unique_array[2] = m_myShip.GetMaterial(j);
                        m_myShip.IncRank();
                        cout << "*****NEW unique item found! Rank up!*****" << endl;
                    }
                }else if (m_myShip.GetRank() == 'A'){
                    if (unique_array[0].m_name != m_myShip.GetMaterial(j).m_name and
                        unique_array[1].m_name != m_myShip.GetMaterial(j).m_name and
                        unique_array[2].m_name != m_myShip.GetMaterial(j).m_name){
                        unique_array[3] = m_myShip.GetMaterial(j);
                        m_myShip.IncRank();
                        cout << "*****NEW unique item found! Rank up!*****" << endl;
                    }
                }

            }
        }
    }while(menu_option != 5);
}
int Game::MainMenu(){
    //main menu for the game with the win condition
    if (m_myShip.GetRank() == TOP_RANK) {
        cout << "Congratulations you have won the game!" << endl;
        return EXIT;
    }
    int choice;
    do{
        cout << "What would you like to do?" << endl;
        cout << "1. Display your Ship's Materials" << endl;
        cout << "2. Search for Raw Materials" << endl;
        cout << "3. Attempt to Merge Materials" << endl;
        cout << "4. See Score" << endl;
        cout << "5. Quit" << endl;

        cin >> choice;
    }while(choice < 1 or choice > 5);

    return choice;
}
void Game::DisplayMaterials(){
    //displays the name and quantity of every material in the ship
    for (int j = 0; j < PROJ2_SIZE; j += 1){
        cout << j + 1 << ". " << m_myShip.GetMaterial(j).m_name << " " << m_myShip.GetMaterial(j).m_quantity << endl;
    }
}
void Game::SearchMaterials(){
    //finds a random raw material and add the quantity to the ship
    srand(time(NULL));
    int rand_num = 0;
    Material raw_material;
    do{
        rand_num = rand() % PROJ2_SIZE;
        raw_material = m_myShip.GetMaterial(rand_num);
    }while(raw_material.m_type != "raw");


    m_myShip.IncrementQuantity(raw_material);
    cout << raw_material.m_name << " found!" << endl;

}
void Game::CombineMaterials(){
    int choice;
    string name1;
    string name2;
    int index;
    //attempts to combines materials
    RequestMaterial(choice);
    name1 = m_materials[choice - 1].m_name;
    Material material1;
    material1 = m_myShip.GetMaterial(choice - 1);
    RequestMaterial(choice);
    name2 = m_materials[choice - 1].m_name;
    Material material2;
    material2 = m_myShip.GetMaterial(choice - 1);

    if (m_myShip.CheckQuantity(material1, material2)){
        index = SearchRecipes(name1, name2);
        if (index != -1){
            //this merges the materials and makes sure that you can't have more than one unique at the same time
            if (m_myShip.GetMaterial(index).m_type == "unique"){
                if (m_myShip.GetMaterial(index).m_quantity > 0){
                    cout << "You can't make another of this item being that it's unique." << endl;
                }else{
                    cout << name1 << " combined with " << name2 << " to make " << m_materials[index].m_name << "!" << endl;
                    m_myShip.IncrementQuantity(m_myShip.GetMaterial(index));
                    m_myShip.DecrementQuantity(material1);
                    m_myShip.DecrementQuantity(material2);

                }
            }else{
                cout << name1 << " combined with " << name2 << " to make " << m_materials[index].m_name << "!" << endl;
                m_myShip.IncrementQuantity(m_myShip.GetMaterial(index));
                m_myShip.DecrementQuantity(material1);
                m_myShip.DecrementQuantity(material2);
            }


        }else{
            cout << "Nothing happened when you tried to combine " << name1 << " and " << name2 << "." << endl;
        }
    }else{
        cout << "You don't have enough of one or more materials." << endl;
    }
}
void Game::RequestMaterial(int &choice){
//requests materials using a while loop to loop until a valid option is choosen
    do{
        cout << "Which materials would you like to merge?" << endl;
        cout << "To list known materials enter -1" << endl;
        cin >> choice;
        if ((choice == 0) or (choice < -1 or choice > 62)){
            cout << "Invalid choice" << endl;
        }
        if (choice == -1){
            DisplayMaterials();
        }
    }while(choice < 1 or choice > 62);

}
int Game::SearchRecipes(string string1, string string2) {
    //uses two for loops to return the index of a material that comprises of the other materials
    for (int j = 0; j < PROJ2_SIZE; j += 1) {
        if (m_materials[j].m_material1 == string1 and m_materials[j].m_material2 == string2) {
            return j;
        }
    }
    for (int j = 0; j < PROJ2_SIZE; j += 1) {
        if (m_materials[j].m_material1 == string2 and m_materials[j].m_material2 == string1) {
            return j;
        }
    }
    return -1;
}
void Game::CalcScore(){
    //uses getters to obtain the score and name
    cout << "***The Ship***" << endl;
    cout << m_myShip.GetName() << endl;
    cout << "Ship Rank: " << m_myShip.GetRank() << endl;
}
