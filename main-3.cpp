
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <string>
#include <ctime>
using namespace std;
struct Pokemon
{
    int pokenum;
    int catchpercentage;
    int numcaught;
    int numseen;
    string name;
    string type;
    string region;
    string pokeinfo;
};
//Declaring Functions
void menu();
string lower(string);
int inventory();
int main()
{
    //Declaring varriables
    srand((unsigned int)time(0));
    int size;
    string username;
    string useregion;
    string selection;
    int randomvalue;
    int pokeball = 10;
    int greatball = 10;
    int ultraball = 10;
    int ballselected;
    int numofcatch;
    int totalseen = 0;
    int totalcatch = 0;
    char temp;
    Pokemon * dex;
    ifstream fin;
    fin.open("poke.txt");
    //Checking if poke.txt file opened
    if(!fin)
    {
        cout << "POKE.TXT FILE FAILED TO OPEN, ENDING PROGRAM\n";
        exit(0);
    }
    fin >> size;
    dex = new Pokemon [size];
    //Getting information from poke text
    for(int i = 0; i < size; i++)
    {
        fin >> dex[i].pokenum;
        fin >> temp;
        getline(fin,dex[i].name,',');
        getline(fin,dex[i].type, ',');
        getline(fin,dex[i].region,',');
        fin >> dex[i].catchpercentage;
        fin >> temp;
        getline(fin,dex[i].pokeinfo);
    }
    cout << "What's your name, trainer?";
    getline(cin,username);
    cout << "\n";
    //Welcomes users
    cout << "Welcome," << username << " to the programming I safari Zone!\n";
    cout << "You'll have 30 chances to catch Pokemon make them count!\n";
    cout << "This hunt will end when you choose or run out of Pokeballs\n";
    cout << "\n";
    cout << "What region would you like to vist?\n";
    do{
    cout << "Enter Kanto, Johto, Hoenn, or Sinnoh\n";
    cin >> useregion;
    for(int i = 0; i< useregion.length(); i++)
    useregion[i] = toupper(useregion[i]);
    }while(useregion != "KANTO" && useregion != "JOHTO" && useregion != "HOENN" && useregion != "SINNOH");
    cout << "\n";
    cout << "Travelling to " << useregion << endl;
    cout << "\n";
    menu();
    do{
    cout << "Selection > ";
    cin >> selection;
    selection = lower(selection);
    if(selection == "menu")
    {
        //Displays menu function
        menu();
    }
    if(selection == "hunt")
    {
        if (useregion == "KANTO")
        {
        randomvalue = rand() % 151 + 0;
        }
        else if(useregion == "JOHTO")
        {
        randomvalue = rand() % 100 + 151;
        }
        else if(useregion == "HOENN") 
        {
        randomvalue = rand() % 135 + 251;
        }
        else if(useregion == "SINNOH")
        {
        randomvalue = rand() % 107 + 386;
        }
        //Shows users what random pokemon appreared
        cout << "A wild "<< dex[randomvalue].name << "has appreared" << endl;
        //Menu for balls to throw
        cout << "Choose a ball to throw: \n";
        cout << "1 - Poke Ball  (You have: " << pokeball << " ) " << endl;
        cout << "2 - Great Ball (You have: " << greatball << " ) " << endl;
        cout << "3 - Ultra Ball (You have: " << ultraball << " ) " << endl;
        cout << "Selection > ";
        cin >> ballselected;
        if(ballselected == 1)
        {
            //Subtracts pokeball when user selects 1
            pokeball --;
            cout << "Threw a Poke Ball\n";
            numofcatch = dex[randomvalue].catchpercentage;
        }
        if(ballselected == 2)
        {
            //Subtracts greatball when user selects 2
            greatball --;
            cout << "Threw a Great Ball\n";
            numofcatch = dex[randomvalue].catchpercentage + 20;
        }
        if(ballselected == 3)
        {
             //Subtracts ultraball when user selects 3
            ultraball --;
            cout << "Threw a Ultra Ball\n";
            numofcatch = dex[randomvalue].catchpercentage + 40;
        }
        if((rand() % 100 + 1) <= numofcatch)
        {
            cout << "Congratulations! You caught " << dex[randomvalue].name << endl;
            dex[randomvalue].numseen++;
            dex[randomvalue].numcaught++;
            totalcatch++;
            totalseen++;
        }
        else{
            cout << dex[randomvalue].name << " ran away " << endl;
            dex[randomvalue].numseen++;
            totalseen++;
        }
        
    }
//Shows users how many pokemons caught, name amd number. 
if(selection == "pokemon")
{
    for(int i = 0; i < size; i++)
    {
        if(dex[i].numcaught > 0)
        {
          cout << username << " POKEMON: " << endl;
          cout << " no " << dex[i].pokenum << " " << dex[i].name << endl; 
        }
    }
}
//Pokemon statistics
if(selection == "statistics")
{
    cout << "Total Pokemon Caught: "<< totalcatch << " " << "Total Pokemon Seen: "<< totalseen << endl;
    cout << fixed << setprecision(2);
    cout << "Overall Catch Rate: " << totalcatch * 100.0/totalseen << "%" << endl;
}
//Pokemon inventory
if(selection == "inventory")
{
    cout << "You have: \n";
    cout << pokeball << " Pokeballs\n";
    cout << greatball << " Great Balls\n";
    cout << ultraball << " Ultra Balls\n";
}
    //Valid selection for menu
    if(selection != "menu" && selection != "hunt" && selection != "pokemon" && selection != "statistics" && selection != "inventory" && selection != "dex name" && selection != "menu" && selection != "exit")
    {
        cout << "invalid option\n";
    }
    }while(selection != "exit");
return 0;
}
//Pokemon menu
void menu()
{
cout << "HUNT (Go hunting for Pokemon!)\n";
cout << "POKEMON (See the Pokemon you've caught.)\n";
cout << "STATISTICS (See your catch statistics.)\n";
cout << "INVENTORY (See your current inventory.)\n";
cout << "DEX NAME (ex: DEX BULBASAUR would view Bulbasaur's Pokedex entry.)\n";
cout << "MENU (Reprint this menu.)\n";
cout << "EXIT\n";
}
string lower(string userentry)
{
    for(int i = 0; i <= userentry.length() -1; i++)
                userentry[i] = tolower(userentry[i]);
    return userentry;
}
