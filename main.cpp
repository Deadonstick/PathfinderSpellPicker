#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <ctime>
#include <random>

using namespace std;

vector<string> readSpells()
{
    vector<string> spells;
    ifstream spellFile;
    spellFile.open("spells.txt");
    string spell;
    if(spellFile.is_open())
    {
        while(std::getline(spellFile, spell, ';'))
        {
            if(spell.front() == ' ')
            {
                spell.erase(spell.begin());
            }
            spells.push_back(spell);
        }
    }
    else
    {
        cerr << "No file named spells.txt found! Exiting..." << endl;
        exit(0);
    }
    spellFile.close();
    return spells;
}

vector<string> chooseSpells(vector<string>& allSpells, uint16_t amount)
{
    vector<string> chosenSpells;
    mt19937 g((unsigned) time(NULL));
    shuffle(allSpells.begin(), allSpells.end(), g);
    for(uint16_t i = 0; i < amount ; ++i)
    {
        chosenSpells.push_back(allSpells.at(i));
    }
    return chosenSpells;

}

void outputChosen(const vector<string>& chosenSpells)
{
    for(string s : chosenSpells)
    {
        cout << s << endl;
    }
}

int main(int argc, char **argv)
{
    vector<string> spells = readSpells();
    uint16_t amount;
    if(argc==1)
    {
        cout << "How many spells would you like to select? (Max: " << spells.size() << ") ";
        cin >> amount;
        cout << endl;
    }
    else if (argc == 2)
    {
        amount = atoi(argv[1]);
    }
    else if (argc > 2)
    {
        cerr << "Too many arguments! Exiting..." << endl;
        exit(0);
    }
    if(amount > spells.size())
    {
        cerr << "You have selected more spells than are available! Exiting..." << endl;
        exit(0);
    }
    outputChosen(chooseSpells(spells,amount));
    return 0;
}
