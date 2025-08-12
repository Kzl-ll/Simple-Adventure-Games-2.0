#include <iostream>
#include <cstring>
#include <string>
#include <stack>
#include <queue>
#include <cstdlib>
#include <vector>
using namespace std;

bool quest = false;
struct treeskills{
    string name;
    bool unlocked = false;
    treeskills* left;
    treeskills* right;
    treeskills(string name) {
        this->name = name;
    }
};

treeskills* createnewskills(string name){
    treeskills* baru = new treeskills(name);
    baru->name= name;
    baru->left= nullptr;
    baru->right= nullptr;
    return baru;
}



treeskills* root1 = createnewskills("Sword Mastery");
treeskills* child1 = createnewskills("Sword Aura");
treeskills* child2 = createnewskills("Slash Wind");
treeskills* child1_1 = createnewskills("Sword God");
treeskills* child1_2 = createnewskills("Demon Slash");
treeskills* child2_1 = createnewskills("Storm of Heaven");
treeskills* child2_2 = createnewskills("Hero Ultimate");




treeskills* root2 = createnewskills("Magic Mastery");
treeskills* magchild1 = createnewskills("Inferno");
treeskills* magchild2 = createnewskills("Ice Rain");
treeskills* magchild1_1 = createnewskills("Dark Void");
treeskills* magchild1_2 = createnewskills("Holy Lance");
treeskills* magchild2_1 = createnewskills("Lightning Wrath");
treeskills* magchild2_2 = createnewskills("Iron Maiden");



const int MAX_CITY = 10;
const int INF = 999999; // Representasi "tak hingga"

struct EdgeNode {
    int destinationIndex;
    int weight;
    EdgeNode* next;
};

struct CityNode {
    string name;
    EdgeNode* adjacencyList;
};

CityNode cities[MAX_CITY];
int cityCount = 0;

// Cari indeks kota berdasarkan nama
int findCityIndex(string name) {
    for (int i = 0; i < cityCount; ++i) {
        if (cities[i].name == name) return i;
    }
    return -1;
}

// Tambah kota baru
void addCity(string name) {
    if (cityCount >= MAX_CITY) {
        cout << "Kapasitas kota sudah maksimal.\n";
        return;
    }
    cities[cityCount].name = name;
    cities[cityCount].adjacencyList = nullptr;
    ++cityCount;
}

// Tambah jalur antar kota (dua arah)
void addEdge(string from, string to, int weight) {
    int fromIndex = findCityIndex(from);
    int toIndex = findCityIndex(to);

    if (fromIndex == -1 || toIndex == -1) {
        cout << "Kota tidak ditemukan.\n";
        return;
    }

    // Tambah edge dari -> ke
    EdgeNode* newEdge = new EdgeNode{toIndex, weight, cities[fromIndex].adjacencyList};
    cities[fromIndex].adjacencyList = newEdge;

    // Tambah edge ke -> dari (karena dua arah)
    EdgeNode* newEdgeBack = new EdgeNode{fromIndex, weight, cities[toIndex].adjacencyList};
    cities[toIndex].adjacencyList = newEdgeBack;
}


void fastTravel(string from, string to) {
    int start = findCityIndex(from);
    int end = findCityIndex(to);

    if (start == -1 || end == -1) {
        cout << "Kota asal atau tujuan tidak ditemukan.\n";
        return;
    }

    int dist[MAX_CITY];
    bool visited[MAX_CITY];
    int previous[MAX_CITY];

    for (int i = 0; i < cityCount; ++i) {
        dist[i] = INF;
        visited[i] = false;
        previous[i] = -1;
    }

    dist[start] = 0;

    for (int i = 0; i < cityCount; ++i) {
        // Temukan node dengan jarak terkecil
        int u = -1;
        for (int j = 0; j < cityCount; ++j) {
            if (!visited[j] && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }

        if (u == -1 || dist[u] == INF) break;
        visited[u] = true;

        EdgeNode* current = cities[u].adjacencyList;
        while (current != nullptr) {
            int v = current->destinationIndex;
            int weight = current->weight;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                previous[v] = u;
            }

            current = current->next;
        }
    }

    if (dist[end] == INF) {
        cout << "Tidak ada jalur ke kota " << cities[end].name << ".\n";
        return;
    }

    // Cetak jalur
    cout << "\nFast Travel dari " << from << " ke " << to << " (jarak: " << dist[end] << "):\n";
    int path[MAX_CITY];
    int count = 0;
    for (int at = end; at != -1; at = previous[at]) {
        path[count++] = at;
    }

    for (int i = count - 1; i >= 0; --i) {
        cout << cities[path[i]].name;
        if (i > 0) cout << " -> ";
    }
    cout << "\n";
}






class potion{
    public:
        string name;
        int healthrecovery;
        int manarecovery;
        potion* next;
        potion(string n, int he, int man, potion* nxt = nullptr){
            name = n;
            healthrecovery = he;
            manarecovery = man;
            next = nxt;
        }
};


class weapon {
    public:
        string name;
        int attack;
        int magicdamage;
        bool digunakan;
        weapon* next;
        weapon(string n, int a, int m, bool used, weapon* nxt = nullptr){
            name = n; 
            attack = a; 
            magicdamage = m; 
            digunakan = used;
            next = nxt;
        }
};


class armor{
    public:
        string name;
        int health;
        int defense;
        bool digunakan;
        armor* next;
        armor(string n, int he, int def, bool used, armor* nxt = nullptr){
            name = n;
            health = he;
            defense = def;
            digunakan = used;
            next = nxt; 
        }
};

potion* hashtablepotion[100] = {nullptr};
weapon* hashtableweapon[100] = {nullptr};
armor* hashtablearmor[100] = {nullptr};
weapon* weaponArray[100];
int weaponCount = 0;
armor* armorArray[100];
int armorCount = 0;
potion* potionArray[100];
int potionCount = 0;

const int maxspirit = 5;
int kebutuhanexpbertambah = 1;
class player {
    public:
    string name;
    int health;
    int maxhealth;
    int attack;
    int magicdamage;
    int magicpoint;
    int maxmagicpoint;
    int defense;
    int evasion;
    int experience;
    int level;
    int skillpoint;
    int statuspoint;
    bool isusedweapon;
    bool isusedarmor;
    bool elarion;
    bool mengalahkanrajaiblis;
    weapon* memakaisenjataini;
    armor* memakaiarmorini;
    stack<int> herospirit;
    queue<int> eventIbuKota;
    queue<int> eventHutanKegelapan;
    queue<int> eventAkademiHero;
    queue<int> eventIstanaRajaIblis;
    string position;
    player(string nama,int he,int att, int mag,int mp, int def,int eva, int exp, int lev, int sp, int statp){
        name = nama;
        health = he;
        maxhealth = he;
        attack = att;
        magicdamage = mag;
        magicpoint = mp;
        maxmagicpoint = mp;
        defense = def;
        evasion = eva;
        experience = exp;
        level = lev;
        skillpoint = sp;
        statuspoint = statp;
        elarion = false;
        position = "Rumah";
        mengalahkanrajaiblis = false;
        eventIbuKota.push(1);
        eventIbuKota.push(1);
        eventHutanKegelapan.push(1);
        eventHutanKegelapan.push(1);
        eventAkademiHero.push(1);
        eventAkademiHero.push(1);
        eventIstanaRajaIblis.push(1);
        eventIstanaRajaIblis.push(1);
    }
    bool gunakanspirit(int &att){
        if (herospirit.empty()){
            cout << "Dont have enough Hero Spirit" << endl;
            return false;
        } else {
            herospirit.pop();
            att = att + att / 10;
            return true;
        }
        
    }
    void serang (int att, int &heMusuh, int &defMusuh, bool gunakanspirit){
        if (gunakanspirit == false){
            int menyerang = att - defMusuh;
            if (menyerang < 0){
                menyerang = 0;
            }
            heMusuh = heMusuh - menyerang;
            if (heMusuh < 0){
                heMusuh = 0;
            }
            if (herospirit.size()>= maxspirit){
                return;
            } else {
                herospirit.push(1);
            }
        }
        else{
            int menyerang = att - defMusuh;
            if (menyerang < 0){
                menyerang = 0;
            }
            heMusuh = heMusuh - menyerang;
            if (heMusuh < 0){
                heMusuh = 0;
            }

        }
    }
    bool serangdengansihirapi(int mag, int &heMusuh, int &defMusuh, bool gunakanspirit){
        if (gunakanspirit == false){
            int menyerang = mag - defMusuh / 2;
            if (menyerang < 0){
                menyerang = 0;
            }
            heMusuh = heMusuh - menyerang;
            if (heMusuh < 0){
                heMusuh = 0;
            }
            if (herospirit.size()>= maxspirit){
                return true;
            } else {
                herospirit.push(1);
            }
            return true;
        }
        else{
            int menyerang = mag - defMusuh / 2;
            if (menyerang < 0){
                menyerang = 0;
            }
            heMusuh = heMusuh - menyerang;
            if (heMusuh < 0){
                heMusuh = 0;
            }
            return true;

        }
    }

    void levelup(){

        while (experience >= level * 500 * kebutuhanexpbertambah / 2){
            cout << "Selamat Anda Telah Naik Level" << endl;
            level++;
            cout << "Levelmu Sekarang : " << level << endl;
            statuspoint = statuspoint + 5;
            cout << "Status Pointmu Sekarang : " << statuspoint << endl;
            skillpoint++;
            cout << "Skill Pointmu Sekarang : " << skillpoint << endl;
            kebutuhanexpbertambah++;
        }
        return;
    }
    void terapkanstatuspoint(){
        int pilihan = 0;
        if (statuspoint != 0){
            do{
                cout << "\nTerapkan ke : \n1. Health\n2. Attack\n3. Magic\n4. Defense\n5. Evasion" << endl;
                cin >> pilihan;
                switch (pilihan)
                {
                case 1:
                    maxhealth = maxhealth + 500;
                    statuspoint--;
                    cout << "Max Health Anda Menjadi : " << maxhealth << endl;
                    cout << "Status Poin Tersisa : " << statuspoint << endl;
                    break;
                case 2:
                    attack = attack + 50;
                    statuspoint--;
                    cout << "Attack Anda Menjadi : " << attack << endl;
                    cout << "Status Poin Tersisa : " << statuspoint << endl;
                    break;
                case 3:
                    magicdamage = magicdamage + 100;
                    maxmagicpoint = maxmagicpoint + 200;
                    statuspoint--;
                    cout << "Magic Damage Anda Menjadi : " << magicdamage << endl;
                    cout << "Max Magic Point Anda Menjadi : " << maxmagicpoint << endl;
                    cout << "Status Poin Tersisa : " << statuspoint << endl;
                    break;
                case 4:
                    defense = defense + 50;
                    statuspoint--;
                    cout << "Defense Anda Menjadi : " << defense << endl;
                    cout << "Status Poin Tersisa : " << statuspoint << endl;
                    break;
                case 5:
                    evasion = evasion + 1;
                    statuspoint--;
                    cout << "Evasion Anda Menjadi : " << evasion << endl;
                    cout << "Status Poin Tersisa : " << statuspoint << endl;
                    break;
                default:
                    break;
                }
            } while (statuspoint != 0 && pilihan != 0);
        } else {
            cout << "You dont have enough Status Point" << endl;
        }
    }
    void bukastatus(){
        if(statuspoint != 0){
            char pilihan;
            cout << name << endl;
            cout << "Level: " << level << endl;
            cout << "Health: " << health << endl;
            cout << "Attack: " << attack << endl;
            cout << "Magic Damage: " << magicdamage << endl;
            cout << "MP: " << magicpoint << endl;
            cout << "Defense: " << defense << endl;
            cout << "Evasion: " << evasion << endl;
            cout << "Skill Point: " << skillpoint << endl;
            cout << "Status Point: " << statuspoint << endl;
            cout << "Exp: " << experience << endl;
            cout << "Apakah anda ingin menerapkan Status Point? Y/N" << endl;
            cin >> pilihan;
            char pilihan2 = tolower(pilihan);
            if (pilihan2 == 'y'){
                terapkanstatuspoint();
            } else {
                return;
            }
        } else {
            cout << name << endl;
            cout << "Level: " << level << endl;
            cout << "Health: " << health << endl;
            cout << "Attack: " << attack << endl;
            cout << "Magic Damage: " << magicdamage << endl;
            cout << "MP: " << magicpoint << endl;
            cout << "Defense: " << defense << endl;
            cout << "Evasion: " << evasion << endl;
            cout << "Skill Point: " << skillpoint << endl;
            cout << "Status Point: " << statuspoint << endl;
            cout << "Exp: " << experience << endl;
        }
    }



    int hashfunc(string &name){
        int hasil = 0;
        for (char c : name){
            hasil = hasil + c;
        }
        return hasil % 100;
    }
    void insertpotion(potion* potion1){
        int index = hashfunc(potion1->name);
        potion* baru = new potion{potion1->name, potion1->healthrecovery, potion1->manarecovery, hashtablepotion[index]};
        hashtablepotion[index] = baru;
    }
    void insertweapon(weapon* weapon1){
        int index = hashfunc(weapon1->name);
        weapon* baru = new weapon{weapon1->name, weapon1->attack, weapon1->magicdamage, weapon1->digunakan, hashtableweapon[index]};
        hashtableweapon[index] = baru;
    }
    void insertarmor(armor* armor1){
        int index = hashfunc(armor1->name);
        armor* baru = new armor{armor1->name, armor1->health, armor1->defense, armor1->digunakan, hashtablearmor[index]};
        hashtablearmor[index] = baru;
    }

    void gunakanweapon(weapon* weapon1){
        if (isusedweapon == false){
            attack = attack + weapon1->attack;
            magicdamage = magicdamage + weapon1->magicdamage;
            isusedweapon = true;
            weapon1->digunakan = true;
            memakaisenjataini = new weapon(weapon1->name, weapon1->attack, weapon1->magicdamage, weapon1->digunakan);
        } else {
            cout << "Anda Sudah Menggunakan Senjata!" << endl;
        }
    }
    void lepaskanweapon(weapon* weapon1){
        if (isusedweapon == true && weapon1->name == memakaisenjataini->name){
            attack = attack - weapon1->attack;
            magicdamage = magicdamage - weapon1->magicdamage;
            isusedweapon = false;
            weapon1->digunakan = false;
        } else {
            cout << "Anda Tidak Sedang Menggunakan Senjata!" << endl;
        }
    }

    void gunakanarmor(armor* armor1){
        if (isusedarmor == false){
            maxhealth = maxhealth + armor1->health;
            defense = defense + armor1->defense;
            isusedarmor = true;
            armor1->digunakan = true;
            memakaiarmorini = new armor(armor1->name, armor1->health, armor1->defense, armor1->digunakan);
        } else {
            cout << "Anda Sudah Menggunakan Armor!" << endl;
        }
    }
    void lepaskanarmor(armor* armor1){
        if (isusedarmor == true && armor1->name == memakaiarmorini->name){
            maxhealth = maxhealth - armor1->health;
            if (health > maxhealth) health = maxhealth;
            defense = defense - armor1->defense;
            isusedarmor = false;
            armor1->digunakan = false;
        } else {
            cout << "Anda Tidak Sedang Menggunakan Armor!" << endl;
        }
    }

    void hapuspotion(string &name){
        int index = hashfunc(name);
        potion* current = hashtablepotion[index];
        potion* prev = nullptr;
        while (current != nullptr){
            if (current->name == name){
                if (prev == nullptr){
                    hashtablepotion[index] = current->next;
                }else {
                    prev->next = current->next;
                }
                delete current;
                cout << "Potion Digunakan" << endl;
            }
            prev = current;
            current = current->next;
        }
        
    }

    void gunakanpotion(potion* potion1){
        int heSementara = health;
        int magSementara = magicpoint;
        health = health + potion1->healthrecovery;
        if (health > maxhealth){
            health = maxhealth;
        }
        magicpoint = magicpoint + potion1->manarecovery;
        if (magicpoint > maxmagicpoint){
            magicpoint = maxmagicpoint;
        }
        cout << "Health anda bertambah dari " << heSementara << " menjadi -> " << health << endl;
        cout << "MP anda bertambah dari " << magSementara << " menjadi -> " << magicpoint << endl;

        hapuspotion(potion1->name);
        
        

    }
    
    void searchpotion(string &name){
        int index = hashfunc(name);
        potion* current = hashtablepotion[index];
        while (current){
            if (current->name == name){
                cout << "Potion : " << current->name << "\nHealth Recovery : " << current->healthrecovery << "\nMana Recovery : " << current->manarecovery << endl;
                cout << "Gunakan? 1" << endl;
                int x = 0;
                cin >> x;
                if (x == 1){
                    gunakanpotion(current);
                }
                return;
            }
            current = current->next;
        }
        cout << "Barang Tidak Ditemukan!" << endl;
        return;
    }
    void searchweapon(string &name){
        int index = hashfunc(name);
        weapon* current = hashtableweapon[index];
        while (current){
            if (current->name == name){
                cout << "Weapon : " << current->name << "\nAttack : " << current->attack << "\nMagic Damage : " << current->magicdamage << endl;
                cout << "Gunakan? 1, Lepaskan? 2" << endl;
                int x = 0;
                cin >> x;
                if (x == 1){
                    gunakanweapon(current);
                } else if(x == 2){
                    lepaskanweapon(current);
                }
                return;
            }
            current = current->next;

        }
        cout << "Barang Tidak Ditemukan!" << endl;
        return;
    }


    void searchweaponElarion(string name){
        int index = hashfunc(name);
        weapon* current = hashtableweapon[index];
        while (current){
            if (current->name == name){    
                gunakanweapon(current);
                return;
            }
            current = current->next;

        }
        cout << "Barang Tidak Ditemukan!" << endl;
        return;
    }

    void searcharmor(string &name){
        int index = hashfunc(name);
        armor* current = hashtablearmor[index];
        while (current){
            if (current->name == name){
                cout << "Armor : " << current->name << "\nHealth : " << current->health << "\nDefense : " << current->defense << endl;
                cout << "Gunakan? 1, Lepaskan? 2" << endl;
                int x = 0;
                cin >> x;
                if (x == 1){
                    gunakanarmor(current);
                } else if(x == 2){
                    lepaskanarmor(current);
                }
                return;
            }
            current = current->next;
        }
        cout << "Barang Tidak Ditemukan!" << endl;
        return;
    }



    void extractWeaponsToArray() {
        weaponCount = 0;
        for (int i = 0; i < 100; ++i) {
            weapon* current = hashtableweapon[i];
            while (current != nullptr) {
                weaponArray[weaponCount++] = current;
                current = current->next;
            }
        }
    }
    void extractArmorToArray() {
        armorCount = 0;
        for (int i = 0; i < 100; ++i) {
            armor* current = hashtablearmor[i];
            while (current != nullptr) {
                armorArray[armorCount++] = current;
                current = current->next;
            }
        }
    }
    void extractPotionToArray() {
        potionCount = 0;
        for (int i = 0; i < 100; ++i) {
            potion* current = hashtablepotion[i];
            while (current != nullptr) {
                potionArray[potionCount++] = current;
                current = current->next;
            }
        }
    }
    void quicksortWeapons(int left, int right) {
        int i = left, j = right;
        string pivot = weaponArray[(left + right) / 2]->name;

        while (i <= j) {
            while (weaponArray[i]->name < pivot) i++;
            while (weaponArray[j]->name > pivot) j--;

            if (i <= j) {
                swap(weaponArray[i], weaponArray[j]);
                i++; j--;
            }
        }

        if (left < j) quicksortWeapons(left, j);
        if (i < right) quicksortWeapons(i, right);
    }
    void quicksortArmor(int left, int right) {
        int i = left, j = right;
        string pivot = armorArray[(left + right) / 2]->name;

        while (i <= j) {
            while (armorArray[i]->name < pivot) i++;
            while (armorArray[j]->name > pivot) j--;

            if (i <= j) {
                swap(armorArray[i], armorArray[j]);
                i++; j--;
            }
        }

        if (left < j) quicksortArmor(left, j);
        if (i < right) quicksortArmor(i, right);
    }
    void quicksortPotion(int left, int right) {
        int i = left, j = right;
        string pivot = potionArray[(left + right) / 2]->name;

        while (i <= j) {
            while (potionArray[i]->name < pivot) i++;
            while (potionArray[j]->name > pivot) j--;

            if (i <= j) {
                swap(potionArray[i], potionArray[j]);
                i++; j--;
            }
        }

        if (left < j) quicksortPotion(left, j);
        if (i < right) quicksortPotion(i, right);
    }
    void displaySortedWeapons() {
        extractWeaponsToArray(); // Ambil dari hash table
        quicksortWeapons(0, weaponCount - 1); // Sort
        cout << "\n== Weapon Terurut (berdasarkan nama) ==\n";
        for (int i = 0; i < weaponCount; ++i) {
            cout << "- " << weaponArray[i]->name << " | ATK: " << weaponArray[i]->attack << ", Magic: " << weaponArray[i]->magicdamage << endl;
            
        }
    }
    void displaySortedArmor() {
        extractArmorToArray(); // Ambil dari hash table
        quicksortArmor(0, armorCount - 1); // Sort
        cout << "\n== Armor Terurut (berdasarkan nama) ==\n";
        for (int i = 0; i < armorCount; ++i) {
            cout << "- " << armorArray[i]->name << " | Health: " << armorArray[i]->health << ", Defense: " << armorArray[i]->defense << endl;
        }
    }
    void displaySortedPotion() {
        extractPotionToArray(); // Ambil dari hash table
        quicksortPotion(0, potionCount - 1); // Sort
        cout << "\n== Potion Terurut (berdasarkan nama) ==\n";
        for (int i = 0; i < potionCount; ++i) {
            cout << "- " << potionArray[i]->name << " | Health Recovery: " << potionArray[i]->healthrecovery << ", Mana Recovery: " << potionArray[i]->manarecovery << endl;
        }
    }
    void displayall(){
        cout << "=============INVENTORY=============" << endl;
        for (int i = 0; i < 100; i++){
            weapon* current = hashtableweapon[i];
            while (current){
                cout  << "Weapon : " << current->name  << "| Attack : " << current->attack << ", Magic Damage : " << current->magicdamage << endl;
                current = current->next; 
            }
        }
        for (int i = 0; i < 100; i++){
            armor* current = hashtablearmor[i];
            while (current){
                cout << "Armor : " << current->name << "| Health : " << current->health << ", Defense : " << current->defense << endl;
                current = current->next; 
            }
        }
        for (int i = 0; i < 100; i++){
            potion* current = hashtablepotion[i];
            while (current){
                cout << "Potion : " << current->name << "| Health Recovery : " << current->healthrecovery << ", Mana Recovery : " << current->manarecovery << endl;
                current = current->next; 
            }
        }
    }
    void urut(){
        int pilihan = 0;
        
        do{
            cout << "\n1. Tampilkan Senjata Terurut\n2. Tampilkan Armor Terurut\n3. Tampilkan Potion Terurut\n0. Keluar" << endl;
            cin >> pilihan;
            if (pilihan == 1){
                displaySortedWeapons();
            } else if (pilihan == 2) {
                displaySortedArmor();
            } else if (pilihan == 3){
                displaySortedPotion();
            }
        } while (pilihan != 0);
    }
    void unlockskill(treeskills* root1, treeskills* root2) {
        if (skillpoint <= 0) {
            cout << "Skill Point Anda Tidak Cukup!" << endl;
            return;
        }

        cout << "\nPilih Skill yang ingin dibuka:\n";
        cout << "1. Sword Mastery\n";
        cout << "2. Sword Aura\n";
        cout << "3. Sword God\n";
        cout << "4. Demon Slash\n";
        cout << "5. Slash Wind\n";
        cout << "6. Storm of Heaven\n";
        cout << "7. Hero Ultimate\n";
        cout << "8. Magic Mastery\n";
        cout << "9. Inferno\n";
        cout << "10. Dark Void\n";
        cout << "11. Holy Lance\n";
        cout << "12. Ice Rain\n";
        cout << "13. Lightning Wrath\n";
        cout << "14. Iron Maiden\n";
        cout << "Pilihan Anda: ";
        int choice;
        cin >> choice;

        // pointer ke skill yang ingin dibuka dan parent-nya
        treeskills* target = nullptr;
        treeskills* parent = nullptr;

        switch (choice) {
            case 1: target = root1; break;
            case 2: target = root1->left; parent = root1; break;
            case 3: target = root1->left->left; parent = root1->left; break;
            case 4: target = root1->left->right; parent = root1->left; break;
            case 5: target = root1->right; parent = root1; break;
            case 6: target = root1->right->left; parent = root1->right; break;
            case 7: target = root1->right->right; parent = root1->right; break;
            case 8: target = root2; break;
            case 9: target = root2->left; parent = root2; break;
            case 10: target = root2->left->left; parent = root2->left; break;
            case 11: target = root2->left->right; parent = root2->left; break;
            case 12: target = root2->right; parent = root2; break;
            case 13: target = root2->right->left; parent = root2->right; break;
            case 14: target = root2->right->right; parent = root2->right; break;
            default:
                cout << "Pilihan tidak valid.\n";
                return;
        }

        // Cek apakah sudah dibuka
        if (target->unlocked) {
            cout << "Skill '" << target->name << "' sudah dibuka.\n";
            return;
        }

        // Jika root, langsung buka
        if (parent == nullptr) {
            target->unlocked = true;
            skillpoint--;
            cout << "Skill '" << target->name << "' berhasil dibuka!\n";
        } else {
            if (parent->unlocked) {
                target->unlocked = true;
                skillpoint--;
                cout << "Skill '" << target->name << "' berhasil dibuka!\n";
            } else {
                cout << "Skill '" << parent->name << "' belum dibuka. Tidak bisa membuka '" << target->name << "'.\n";
            }
        }

        cout << "Sisa Skill Point: " << skillpoint << endl;
    }


    void inginmenambahkanstatusatauunlockskill(){
        int pilihan = 0;
        int name;
        do
        {
            cout << "1. Terapkan Status Point\n2. Buka Skill\n0. Keluar\n";
            
            cin >> pilihan;
            
            if (pilihan == 1){
                terapkanstatuspoint();
                
            } else if(pilihan == 2){
                unlockskill(root1, root2);
                
            } else {
                return;
            }
        } while (pilihan != 0);
        
        
    }


};

class musuh {
    public:
    int health;
    int attack;
    int defense;
    int evasion;
    musuh(int he,int att,int def,int eva){
        health = he;
        attack = att;
        defense = def;
        evasion = eva;
    }
    void serang (int att, int &hePlayer, int &defPlayer){
        int menyerang = att - defPlayer;
        if (menyerang < 0){
            menyerang = 0;
        }
        hePlayer = hePlayer - menyerang;
        if (hePlayer < 0){
            hePlayer = 0;
        }   
    }

};











player kzl("kzl",500, 100, 100, 250, 50, 10, 0, 1, 100, 0);

void serangRajaIblis(){
    int x = 0;
    musuh rajaiblis(1000000, 50000, 20000, 0);
    int healthmusuhawal = rajaiblis.health;
    int attsementara = kzl.attack;
    int magsementara = kzl.magicdamage;
    int evasionsementara = kzl.evasion;
    stack<int> gerakanplayer;
    stack<int> gerakanmusuh;
    bool firemagic = false;
    int waktuterbakar = 0;
    bool gunakanspirit = false;
    cout << "Anda bertemu dengan Raja Iblis" << endl;
    do{
        cout << "1. Serang\n2. Serang dengan sihir api (100 MP)\n3. Gunakan Skill\n4. Gunakan Spirit\n5. Gunakan Potion\n0. Lari!" << endl;
        cout << "Spirit : " << kzl.herospirit.size() << endl;
        cin >> x;
        if (x == 1){
            
            int randomeva = rand() % 101;
            if (randomeva <= evasionsementara) {
                cout << "Anda menghindari serangan lawan dan menyerangnya" << endl;
                kzl.serang(attsementara, rajaiblis.health, rajaiblis.defense, gunakanspirit);
                cout << "Health Musuh : " << rajaiblis.health << endl;
                if (firemagic == true && waktuterbakar >= gerakanplayer.size()){
                    cout << "Musuh terbakar, memberikan damage 20% dari total magic damage" << endl;
                    rajaiblis.health = rajaiblis.health - magsementara * 20 / 100;
                    if(rajaiblis.health < 0){
                        rajaiblis.health = 0;
                    }
                    cout << "Health Musuh : " << rajaiblis.health << endl;
                } else if (waktuterbakar < gerakanplayer.size()){
                    firemagic == false;
                }
                cout << "Health Player : " << kzl.health << endl;
            } else {
                kzl.serang(attsementara, rajaiblis.health, rajaiblis.defense, gunakanspirit);
                cout << "Health Musuh : " << rajaiblis.health << endl;
                if (firemagic == true && waktuterbakar >= gerakanplayer.size()){
                    cout << "Musuh terbakar, memberikan damage 20% dari total magic damage" << endl;
                    rajaiblis.health = rajaiblis.health - magsementara * 20 / 100;
                    if(rajaiblis.health < 0){
                        rajaiblis.health = 0;
                    }
                    cout << "Health Musuh : " << rajaiblis.health << endl;
                } else if (waktuterbakar < gerakanplayer.size()){
                    firemagic == false;
                }

                rajaiblis.serang(rajaiblis.attack, kzl.health, kzl.defense);
                cout << "Health Player : " << kzl.health << endl;
            }
            attsementara = kzl.attack;
            gunakanspirit = false;
            evasionsementara = kzl.evasion;
            gerakanplayer.push(1);
            gerakanmusuh.push(1);
        }
        else if (x == 4){
            gunakanspirit = kzl.gunakanspirit(attsementara);
        }
        else if (x == 2){
            if (kzl.magicpoint >= 100){
                int randomeva = rand() % 101;
                if (randomeva <= evasionsementara) {
                    cout << "Anda menghindari serangan lawan dan menyerangnya" << endl;
                    firemagic = kzl.serangdengansihirapi(magsementara, rajaiblis.health, rajaiblis.defense, gunakanspirit);
                    waktuterbakar = gerakanplayer.size() + 3;
                    cout << "Health Musuh : " << rajaiblis.health << endl;
                    cout << "Health Player : " << kzl.health << endl;
                } else {
                    firemagic = kzl.serangdengansihirapi(magsementara, rajaiblis.health, rajaiblis.defense, gunakanspirit);
                    waktuterbakar = gerakanplayer.size() + 3;
                    cout << "Health Musuh : " << rajaiblis.health << endl;
                    rajaiblis.serang(rajaiblis.attack, kzl.health, kzl.defense);
                    cout << "Health Player : " << kzl.health << endl;
                }
                kzl.magicpoint = kzl.magicpoint - 50;
                cout << "MP Tersisa : " << kzl.magicpoint << endl;
                magsementara = kzl.magicdamage;
                gunakanspirit = false;
                evasionsementara = kzl.evasion;
            }
            else {
                cout << "You dont have enough MP" << endl;
            }
        }
        else if (x == 3) {
            cout << "===== Daftar Skills yang Terbuka =====" << endl;

            vector<treeskills*> skillList = {
                root1, child1, child2, child1_1, child1_2, child2_1, child2_2,
                root2, magchild1, magchild2, magchild1_1, magchild1_2, magchild2_1, magchild2_2
            };

            vector<string> skillNames;
            for (auto skill : skillList) {
                if (skill->unlocked) {
                    cout << "- " << skill->name << endl;
                    skillNames.push_back(skill->name);
                }
            }

            if (!skillNames.empty()) {
                cout << "Pilih skill untuk digunakan: ";
                string pilih;
                cin.ignore();
                getline(cin, pilih);

                // Biaya MP default (jika ada)
                int biayaMP = 0;
                bool skillBerhasil = false;

                if (pilih == "Sword Aura") {
                    biayaMP = 50;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Seranganmu diperkuat oleh aura pedang (+20% attack untuk 1 serangan)\n";
                        attsementara += 20*attsementara/100;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Sword God") {
                    biayaMP = 100;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Kekuatan dewa pedang! (+100% attack dan menghindari 1 serangan)\n";
                        attsementara += attsementara;
                        evasionsementara = 100;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Demon Slash") {
                    biayaMP = 200;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Serangan iblis meledak! (Damage x2)\n";
                        attsementara *= 2;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Storm of Heaven") {
                    biayaMP = 230;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Kamu menciptakan badai suci yang melukai musuh\n";
                        rajaiblis.health -= 5000;
                        if (rajaiblis.health < 0) rajaiblis.health = 0;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Hero Ultimate") {
                    biayaMP = 1000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Skill pamungkas pahlawan! (+1000% semua atribut)\n";
                        attsementara += attsementara*10;
                        magsementara += magsementara*10;
                        evasionsementara += 100;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Inferno") {
                    biayaMP = 450;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Membakar musuh! Efek terbakar aktif hingga 10 giliran\n";
                        rajaiblis.health -= 10000;
                        firemagic = true;
                        waktuterbakar = gerakanplayer.size() + 10;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Ice Rain") {
                    biayaMP = 90;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Hujan es memperlambat musuh! Mengurangi defense musuh 50%\n";
                        rajaiblis.defense = max(0, rajaiblis.defense - rajaiblis.defense*50/100);
                        skillBerhasil = true;
                    }
                } else if (pilih == "Dark Void") {
                    biayaMP = 1000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Void kegelapan menyerap jiwa musuh (-20000 HP)\n";
                        rajaiblis.health -= 20000;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Holy Lance") {
                    biayaMP = 300;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Tombak suci menusuk! +100% magic damage sementara\n";
                        magsementara += magsementara;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Lightning Wrath") {
                    biayaMP = 2000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Petir murka! Musuh kehilangan 50% HP saat ini\n";
                        rajaiblis.health -= rajaiblis.health * 50 / 100;
                        if (rajaiblis.health < 0) rajaiblis.health = 0;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Iron Maiden") {
                    biayaMP = 10000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Instant Death\n";
                        rajaiblis.health = 0;
                        skillBerhasil = true;
                    }
          else if (x == 5){
            kzl.displaySortedPotion();
            string name;
            cin.ignore();
            cout << "Masukkan Nama Potion : ";
            getline(cin, name);
            kzl.searchpotion(name);
        }      } else {
                    cout << "Skill tidak ditemukan atau belum dibuka!\n";
                }

                if (skillBerhasil) {
                    kzl.magicpoint -= biayaMP;
                    cout << "MP tersisa: " << kzl.magicpoint << endl;
                } else if (biayaMP > 0) {
                    cout << "MP Anda tidak cukup untuk menggunakan skill ini!\n";
                }
            } else {
                cout << "Tidak ada skill yang terbuka\n";
            }
        } else if (x == 5){
            int jadi = 0;
            kzl.displaySortedPotion();
            cout << "1.Cari Potion\n2. Batal\n";
            cin >> jadi;
            if (jadi == 1){
                string name;
                cin.ignore();
                cout << "Masukkan Nama Potion : ";
                getline(cin, name);
                kzl.searchpotion(name);
            }
        }
        else if (x == 0){
            cout << "Anda Membiarkan Dunia Hancur\n";
            kzl.health = 0;
            cout << "Game Over";
            break;
        }

    } while (rajaiblis.health > 0 && kzl.health > 0);
    if(rajaiblis.health == 0) {
        kzl.mengalahkanrajaiblis = true;
        kzl.experience += 50000;
        kzl.levelup();
        int randomitem = rand() % 4;
        switch (randomitem)
        {
        case 1:
            kzl.insertweapon(new weapon("Demon King Sword", 40000, 45000, false));
            cout << "Anda Mendapatkan Senjata : Demon King Sword" << endl; 
            break;
        case 2:
            kzl.insertarmor(new armor("Demon King Armor", 505000, 20000, false));
            cout << "Anda Mendapatkan Armor : Demon King Armor" << endl; 
            break;
        default:
            break;
        }
    }
}


void serangRajaIblisdenganArdelia() {
    int x = 0;
    musuh musuh1(500000, 25000, 5000, 0);
    int healthmusuhawal = musuh1.health;
    int attsementara = kzl.attack;
    int magsementara = kzl.magicdamage;
    int evasionsementara = kzl.evasion;
    stack<int> gerakanplayer;
    stack<int> gerakanmusuh;
    bool firemagic = false;
    int waktuterbakar = 0;
    bool gunakanspirit = false;
    cout << "Anda bertemu dengan Raja Iblis" << endl;
    do {
        cout << "1. Serang \n2. Serang dengan sihir api (100 MP)\n3. Gunakan Skill\n4. Gunakan Spirit\n5. Gunakan Potion" << endl;
        cout << "Spirit : " << kzl.herospirit.size() << endl;
        cin >> x;
        if (x == 1) {
            int randomeva = rand() % 101;
            if (randomeva <= evasionsementara) {
                cout << "Anda menghindari serangan lawan dan menyerangnya" << endl;
                kzl.serang(attsementara, musuh1.health, musuh1.defense, gunakanspirit);
                cout << "Ardelia Memberikan 10000 damage" << endl;
                musuh1.health -= 10000;
                if(musuh1.health < 0) musuh1.health = 0;
                cout << "Health Musuh : " << musuh1.health << endl;
                if (firemagic == true && waktuterbakar >= gerakanplayer.size()) {
                    cout << "Musuh terbakar, memberikan damage 20% dari total magic damage" << endl;
                    musuh1.health = musuh1.health - magsementara * 20 / 100;
                    if(musuh1.health < 0) musuh1.health = 0;
                    cout << "Health Musuh : " << musuh1.health << endl;
                } else if (waktuterbakar < gerakanplayer.size()) {
                    firemagic == false;
                }
                cout << "Health Player : " << kzl.health << endl;
            } else {
                kzl.serang(attsementara, musuh1.health, musuh1.defense, gunakanspirit);
                cout << "Ardelia Memberikan 10000 damage" << endl;
                musuh1.health -= 10000;
                if(musuh1.health < 0) musuh1.health = 0;
                cout << "Health Musuh : " << musuh1.health << endl;
                if (firemagic == true && waktuterbakar >= gerakanplayer.size()) {
                    cout << "Musuh terbakar, memberikan damage 20% dari total magic damage" << endl;
                    musuh1.health = musuh1.health - magsementara * 20 / 100;
                    if(musuh1.health < 0) musuh1.health = 0;
                    cout << "Health Musuh : " << musuh1.health << endl;
                } else if (waktuterbakar < gerakanplayer.size()) {
                    firemagic == false;
                }
                musuh1.serang(musuh1.attack, kzl.health, kzl.defense);
                cout << "Health Player : " << kzl.health << endl;
            }
            attsementara = kzl.attack;
            gunakanspirit = false;
            evasionsementara = kzl.evasion;
            gerakanplayer.push(1);
            gerakanmusuh.push(1);
        }
        else if (x == 4) {
            gunakanspirit = kzl.gunakanspirit(attsementara);
        }
        else if (x == 2) {
            if (kzl.magicpoint >= 100) {
                int randomeva = rand() % 101;
                if (randomeva <= evasionsementara) {
                    cout << "Anda menghindari serangan lawan dan menyerangnya" << endl;
                    firemagic = kzl.serangdengansihirapi(magsementara, musuh1.health, musuh1.defense, gunakanspirit);
                    waktuterbakar = gerakanplayer.size() + 3;
                    cout << "Ardelia Memberikan 10000 damage" << endl;
                    musuh1.health -= 10000;
                    if(musuh1.health < 0) musuh1.health = 0;
                    cout << "Health Musuh : " << musuh1.health << endl;
                    cout << "Health Player : " << kzl.health << endl;
                } else {
                    firemagic = kzl.serangdengansihirapi(magsementara, musuh1.health, musuh1.defense, gunakanspirit);
                    waktuterbakar = gerakanplayer.size() + 3;
                    cout << "Ardelia Memberikan 10000 damage" << endl;
                    musuh1.health -= 10000;
                    if(musuh1.health < 0) musuh1.health = 0;
                    cout << "Health Musuh : " << musuh1.health << endl;
                    musuh1.serang(musuh1.attack, kzl.health, kzl.defense);
                    cout << "Health Player : " << kzl.health << endl;
                }
                kzl.magicpoint = kzl.magicpoint - 50;
                cout << "MP Tersisa : " << kzl.magicpoint << endl;
                magsementara = kzl.magicdamage;
                gunakanspirit = false;
                evasionsementara = kzl.evasion;
            }
            else {
                cout << "You dont have enough MP" << endl;
            }
        }
        else if (x == 3) {
            cout << "===== Daftar Skills yang Terbuka =====" << endl;
            vector<treeskills*> skillList = {
                root1, child1, child2, child1_1, child1_2, child2_1, child2_2,
                root2, magchild1, magchild2, magchild1_1, magchild1_2, magchild2_1, magchild2_2
            };
            vector<string> skillNames;
            for (auto skill : skillList) {
                if (skill->unlocked) {
                    cout << "- " << skill->name << endl;
                    skillNames.push_back(skill->name);
                }
            }
            if (!skillNames.empty()) {
                cout << "Pilih skill untuk digunakan: ";
                string pilih;
                cin.ignore();
                getline(cin, pilih);
                int biayaMP = 0;
                bool skillBerhasil = false;
                if (pilih == "Sword Aura") {
                    biayaMP = 50;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Seranganmu diperkuat oleh aura pedang (+20% attack untuk 1 serangan)\n";
                        attsementara += 20*attsementara/100;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Sword God") {
                    biayaMP = 100;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Kekuatan dewa pedang! (+100% attack dan menghindari 1 serangan)\n";
                        attsementara += attsementara;
                        evasionsementara = 100;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Demon Slash") {
                    biayaMP = 200;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Serangan iblis meledak! (Damage x2)\n";
                        attsementara *= 2;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Storm of Heaven") {
                    biayaMP = 230;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Kamu menciptakan badai suci yang melukai musuh\n";
                        musuh1.health -= 500;
                        if (musuh1.health < 0) musuh1.health = 0;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Hero Ultimate") {
                    biayaMP = 1000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Skill pamungkas pahlawan! (+1000% semua atribut)\n";
                        attsementara += attsementara*10;
                        magsementara += magsementara*10;
                        evasionsementara += 100;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Inferno") {
                    biayaMP = 450;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Membakar musuh! Efek terbakar aktif hingga 10 giliran\n";
                        musuh1.health -= 1000;
                        firemagic = true;
                        waktuterbakar = gerakanplayer.size() + 10;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Ice Rain") {
                    biayaMP = 90;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Hujan es memperlambat musuh! Mengurangi defense musuh 50%\n";
                        musuh1.defense = max(0, musuh1.defense - musuh1.defense*50/100);
                        skillBerhasil = true;
                    }
                } else if (pilih == "Dark Void") {
                    biayaMP = 1000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Void kegelapan menyerap jiwa musuh (-2000 HP)\n";
                        musuh1.health -= 2000;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Holy Lance") {
                    biayaMP = 300;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Tombak suci menusuk! +100% magic damage sementara\n";
                        magsementara += magsementara;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Lightning Wrath") {
                    biayaMP = 2000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Petir murka! Musuh kehilangan 50% HP saat ini\n";
                        musuh1.health -= musuh1.health * 50 / 100;
                        if (musuh1.health < 0) musuh1.health = 0;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Iron Maiden") {
                    biayaMP = 10000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Instant Death\n";
                        musuh1.health = 0;
                        skillBerhasil = true;
                    }
                } else {
                    cout << "Skill tidak ditemukan atau belum dibuka!\n";
                }
                if (skillBerhasil) {
                    kzl.magicpoint -= biayaMP;
                    cout << "MP tersisa: " << kzl.magicpoint << endl;
                } else if (biayaMP > 0) {
                    cout << "MP Anda tidak cukup untuk menggunakan skill ini!\n";
                }
            } else {
                cout << "Tidak ada skill yang terbuka\n";
            }
        }else if (x == 5){
            int jadi = 0;
            kzl.displaySortedPotion();
            cout << "1.Cari Potion\n2. Batal\n";
            cin >> jadi;
            if (jadi == 1){
                string name;
                cin.ignore();
                cout << "Masukkan Nama Potion : ";
                getline(cin, name);
                kzl.searchpotion(name);
            }
        }
        else if (x == 0){
            cout << "Meninggalkan Ardelia Sendirian\n";
            kzl.health = 0;
            cout << "Game Over";
            break;
        }
    } while (musuh1.health > 0 && kzl.health > 0);
    if(musuh1.health == 0) {
        kzl.experience += 20000;
        kzl.levelup();
        int randomitem = rand() % 4;
        switch (randomitem) {
            case 1:
                kzl.insertweapon(new weapon("Demon Blade", 8000, 1500, false));
                cout << "Anda Mendapatkan Senjata : Demon Blade" << endl; 
                break;
            case 2:
                kzl.insertarmor(new armor("Infernal Plate", 10000, 2500, false));
                cout << "Anda Mendapatkan Armor : Infernal Plate" << endl; 
                break;
            case 3:
                kzl.insertpotion(new potion("Demon Blood Elixir", 10000, 2500));
                cout << "Anda Mendapatkan Potion : Demon Blood Elixir" << endl; 
                break;
            default:
                break;
        }
    }
}


void serangNaga(){
    int x = 0;
    musuh naga(20000, 5000, 1000, 0);
    int healthmusuhawal = naga.health;
    int attsementara = kzl.attack;
    int magsementara = kzl.magicdamage;
    int evasionsementara = kzl.evasion;
    stack<int> gerakanplayer;
    stack<int> gerakanmusuh;
    bool firemagic = false;
    int waktuterbakar = 0;
    bool gunakanspirit = false;
    cout << "Anda bertemu dengan Naga" << endl;
    do{
        cout << "1. Serang \n2. Serang dengan sihir api (100 MP)\n3. Gunakan Skill\n4. Gunakan Spirit\n5. Gunakan Potion\n0. Lari!" << endl;
        cout << "Spirit : " << kzl.herospirit.size() << endl;
        cin >> x;
        if (x == 1){
            
            int randomeva = rand() % 101;
            if (randomeva <= evasionsementara) {
                cout << "Anda menghindari serangan lawan dan menyerangnya" << endl;
                kzl.serang(attsementara, naga.health, naga.defense, gunakanspirit);
                cout << "Health Musuh : " << naga.health << endl;
                if (firemagic == true && waktuterbakar >= gerakanplayer.size()){
                    cout << "Musuh terbakar, memberikan damage 20% dari total magic damage" << endl;
                    naga.health = naga.health - magsementara * 20 / 100;
                    if(naga.health < 0){
                        naga.health = 0;
                    }
                    cout << "Health Musuh : " << naga.health << endl;
                } else if (waktuterbakar < gerakanplayer.size()){
                    firemagic == false;
                }
                cout << "Health Player : " << kzl.health << endl;
            } else {
                kzl.serang(attsementara, naga.health, naga.defense, gunakanspirit);
                cout << "Health Musuh : " << naga.health << endl;
                if (firemagic == true && waktuterbakar >= gerakanplayer.size()){
                    cout << "Musuh terbakar, memberikan damage 20% dari total magic damage" << endl;
                    naga.health = naga.health - magsementara * 20 / 100;
                    if(naga.health < 0){
                        naga.health = 0;
                    }
                    cout << "Health Musuh : " << naga.health << endl;
                } else if (waktuterbakar < gerakanplayer.size()){
                    firemagic == false;
                }

                naga.serang(naga.attack, kzl.health, kzl.defense);
                cout << "Health Player : " << kzl.health << endl;
            }
            attsementara = kzl.attack;
            gunakanspirit = false;
            evasionsementara = kzl.evasion;
            gerakanplayer.push(1);
            gerakanmusuh.push(1);
        }
        else if (x == 4){
            gunakanspirit = kzl.gunakanspirit(attsementara);
        }
        else if (x == 2){
            if (kzl.magicpoint >= 100){
                int randomeva = rand() % 101;
                if (randomeva <= evasionsementara) {
                    cout << "Anda menghindari serangan lawan dan menyerangnya" << endl;
                    firemagic = kzl.serangdengansihirapi(magsementara, naga.health, naga.defense, gunakanspirit);
                    waktuterbakar = gerakanplayer.size() + 3;
                    cout << "Health Musuh : " << naga.health << endl;
                    cout << "Health Player : " << kzl.health << endl;
                } else {
                    firemagic = kzl.serangdengansihirapi(magsementara, naga.health, naga.defense, gunakanspirit);
                    waktuterbakar = gerakanplayer.size() + 3;
                    cout << "Health Musuh : " << naga.health << endl;
                    naga.serang(naga.attack, kzl.health, kzl.defense);
                    cout << "Health Player : " << kzl.health << endl;
                }
                kzl.magicpoint = kzl.magicpoint - 50;
                cout << "MP Tersisa : " << kzl.magicpoint << endl;
                magsementara = kzl.magicdamage;
                gunakanspirit = false;
                evasionsementara = kzl.evasion;
            }
            else {
                cout << "You dont have enough MP" << endl;
            }
        }
        else if (x == 3) {
            cout << "===== Daftar Skills yang Terbuka =====" << endl;

            vector<treeskills*> skillList = {
                root1, child1, child2, child1_1, child1_2, child2_1, child2_2,
                root2, magchild1, magchild2, magchild1_1, magchild1_2, magchild2_1, magchild2_2
            };

            vector<string> skillNames;
            for (auto skill : skillList) {
                if (skill->unlocked) {
                    cout << "- " << skill->name << endl;
                    skillNames.push_back(skill->name);
                }
            }

            if (!skillNames.empty()) {
                cout << "Pilih skill untuk digunakan: ";
                string pilih;
                cin.ignore();
                getline(cin, pilih);

                // Biaya MP default (jika ada)
                int biayaMP = 0;
                bool skillBerhasil = false;

                if (pilih == "Sword Aura") {
                    biayaMP = 50;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Seranganmu diperkuat oleh aura pedang (+20% attack untuk 1 serangan)\n";
                        attsementara += 20*attsementara/100;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Sword God") {
                    biayaMP = 100;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Kekuatan dewa pedang! (+100% attack dan menghindari 1 serangan)\n";
                        attsementara += attsementara;
                        evasionsementara = 100;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Demon Slash") {
                    biayaMP = 200;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Serangan iblis meledak! (Damage x2)\n";
                        attsementara *= 2;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Storm of Heaven") {
                    biayaMP = 230;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Kamu menciptakan badai suci yang melukai musuh\n";
                        naga.health -= 5000;
                        if (naga.health < 0) naga.health = 0;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Hero Ultimate") {
                    biayaMP = 1000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Skill pamungkas pahlawan! (+1000% semua atribut)\n";
                        attsementara += attsementara*10;
                        magsementara += magsementara*10;
                        evasionsementara += 100;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Inferno") {
                    biayaMP = 450;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Membakar musuh! Efek terbakar aktif hingga 10 giliran\n";
                        naga.health -= 10000;
                        firemagic = true;
                        waktuterbakar = gerakanplayer.size() + 10;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Ice Rain") {
                    biayaMP = 90;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Hujan es memperlambat musuh! Mengurangi defense musuh 50%\n";
                        naga.defense = max(0, naga.defense - naga.defense*50/100);
                        skillBerhasil = true;
                    }
                } else if (pilih == "Dark Void") {
                    biayaMP = 1000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Void kegelapan menyerap jiwa musuh (-20000 HP)\n";
                        naga.health -= 20000;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Holy Lance") {
                    biayaMP = 300;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Tombak suci menusuk! +100% magic damage sementara\n";
                        magsementara += magsementara;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Lightning Wrath") {
                    biayaMP = 2000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Petir murka! Musuh kehilangan 50% HP saat ini\n";
                        naga.health -= naga.health * 50 / 100;
                        if (naga.health < 0) naga.health = 0;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Iron Maiden") {
                    biayaMP = 10000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Instant Death\n";
                        naga.health = 0;
                        skillBerhasil = true;
                    }
                } else {
                    cout << "Skill tidak ditemukan atau belum dibuka!\n";
                }

                if (skillBerhasil) {
                    kzl.magicpoint -= biayaMP;
                    cout << "MP tersisa: " << kzl.magicpoint << endl;
                } else if (biayaMP > 0) {
                    cout << "MP Anda tidak cukup untuk menggunakan skill ini!\n";
                }
            } else {
                cout << "Tidak ada skill yang terbuka\n";
            }
        }else if (x == 5){
            int jadi = 0;
            kzl.displaySortedPotion();
            cout << "1.Cari Potion\n2. Batal\n";
            cin >> jadi;
            if (jadi == 1){
                string name;
                cin.ignore();
                cout << "Masukkan Nama Potion : ";
                getline(cin, name);
                kzl.searchpotion(name);
            }
        }


        else if (x == 0){
            break;
        }

    } while (naga.health > 0 && kzl.health > 0);
    if(naga.health == 0) {
        kzl.experience += 1500;
        kzl.levelup();
        int randomitem = rand() % 4;
        switch (randomitem)
        {
        case 1:
            kzl.insertweapon(new weapon("Mahoraga", 1000, 1000, false));
            cout << "Anda Mendapatkan Senjata : Mahoraga" << endl; 
            break;
        case 2:
            kzl.insertarmor(new armor("Armor of Gods", 1000, 1000, false));
            cout << "Anda Mendapatkan Armor : Armor of Gods" << endl; 
            break;
        case 3:
            kzl.insertpotion(new potion("Potion of Life", 10000, 100));
            cout << "Anda Mendapatkan Potion : Potion of Life" << endl; 
            break;
        default:
            break;
        }

        
        
    }

}

void serangSlime() {
    int x = 0;
    musuh musuh1(500, 100, 50, 0);
    int healthmusuhawal = musuh1.health;
    int attsementara = kzl.attack;
    int magsementara = kzl.magicdamage;
    int evasionsementara = kzl.evasion;
    stack<int> gerakanplayer;
    stack<int> gerakanmusuh;
    bool firemagic = false;
    int waktuterbakar = 0;
    bool gunakanspirit = false;
    cout << "Anda bertemu dengan Slime" << endl;
    do {
        cout << "1. Serang \n2. Serang dengan sihir api (100 MP)\n3. Gunakan Skill\n4. Gunakan Spirit\n5. Gunakan Potion\n0. Lari!" << endl;
        cout << "Spirit : " << kzl.herospirit.size() << endl;
        cin >> x;
        if (x == 1) {
            int randomeva = rand() % 101;
            if (randomeva <= evasionsementara) {
                cout << "Anda menghindari serangan lawan dan menyerangnya" << endl;
                kzl.serang(attsementara, musuh1.health, musuh1.defense, gunakanspirit);
                cout << "Health Musuh : " << musuh1.health << endl;
                if (firemagic == true && waktuterbakar >= gerakanplayer.size()) {
                    cout << "Musuh terbakar, memberikan damage 20% dari total magic damage" << endl;
                    musuh1.health = musuh1.health - magsementara * 20 / 100;
                    if(musuh1.health < 0) musuh1.health = 0;
                    cout << "Health Musuh : " << musuh1.health << endl;
                } else if (waktuterbakar < gerakanplayer.size()) {
                    firemagic == false;
                }
                cout << "Health Player : " << kzl.health << endl;
            } else {
                kzl.serang(attsementara, musuh1.health, musuh1.defense, gunakanspirit);
                cout << "Health Musuh : " << musuh1.health << endl;
                if (firemagic == true && waktuterbakar >= gerakanplayer.size()) {
                    cout << "Musuh terbakar, memberikan damage 20% dari total magic damage" << endl;
                    musuh1.health = musuh1.health - magsementara * 20 / 100;
                    if(musuh1.health < 0) musuh1.health = 0;
                    cout << "Health Musuh : " << musuh1.health << endl;
                } else if (waktuterbakar < gerakanplayer.size()) {
                    firemagic == false;
                }
                musuh1.serang(musuh1.attack, kzl.health, kzl.defense);
                cout << "Health Player : " << kzl.health << endl;
            }
            attsementara = kzl.attack;
            gunakanspirit = false;
            evasionsementara = kzl.evasion;
            gerakanplayer.push(1);
            gerakanmusuh.push(1);
        }
        else if (x == 4) {
            gunakanspirit = kzl.gunakanspirit(attsementara);
        }
        else if (x == 2) {
            if (kzl.magicpoint >= 100) {
                int randomeva = rand() % 101;
                if (randomeva <= evasionsementara) {
                    cout << "Anda menghindari serangan lawan dan menyerangnya" << endl;
                    firemagic = kzl.serangdengansihirapi(magsementara, musuh1.health, musuh1.defense, gunakanspirit);
                    waktuterbakar = gerakanplayer.size() + 3;
                    cout << "Health Musuh : " << musuh1.health << endl;
                    cout << "Health Player : " << kzl.health << endl;
                } else {
                    firemagic = kzl.serangdengansihirapi(magsementara, musuh1.health, musuh1.defense, gunakanspirit);
                    waktuterbakar = gerakanplayer.size() + 3;
                    cout << "Health Musuh : " << musuh1.health << endl;
                    musuh1.serang(musuh1.attack, kzl.health, kzl.defense);
                    cout << "Health Player : " << kzl.health << endl;
                }
                kzl.magicpoint = kzl.magicpoint - 50;
                cout << "MP Tersisa : " << kzl.magicpoint << endl;
                magsementara = kzl.magicdamage;
                gunakanspirit = false;
                evasionsementara = kzl.evasion;
            }
            else {
                cout << "You dont have enough MP" << endl;
            }
        }
        else if (x == 3) {
            cout << "===== Daftar Skills yang Terbuka =====" << endl;
            vector<treeskills*> skillList = {
                root1, child1, child2, child1_1, child1_2, child2_1, child2_2,
                root2, magchild1, magchild2, magchild1_1, magchild1_2, magchild2_1, magchild2_2
            };
            vector<string> skillNames;
            for (auto skill : skillList) {
                if (skill->unlocked) {
                    cout << "- " << skill->name << endl;
                    skillNames.push_back(skill->name);
                }
            }
            if (!skillNames.empty()) {
                cout << "Pilih skill untuk digunakan: ";
                string pilih;
                cin.ignore();
                getline(cin, pilih);
                int biayaMP = 0;
                bool skillBerhasil = false;
                if (pilih == "Sword Aura") {
                    biayaMP = 50;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Seranganmu diperkuat oleh aura pedang (+20% attack untuk 1 serangan)\n";
                        attsementara += 20*attsementara/100;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Sword God") {
                    biayaMP = 100;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Kekuatan dewa pedang! (+100% attack dan menghindari 1 serangan)\n";
                        attsementara += attsementara;
                        evasionsementara = 100;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Demon Slash") {
                    biayaMP = 200;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Serangan iblis meledak! (Damage x2)\n";
                        attsementara *= 2;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Storm of Heaven") {
                    biayaMP = 230;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Kamu menciptakan badai suci yang melukai musuh\n";
                        musuh1.health -= 500;
                        if (musuh1.health < 0) musuh1.health = 0;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Hero Ultimate") {
                    biayaMP = 1000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Skill pamungkas pahlawan! (+1000% semua atribut)\n";
                        attsementara += attsementara*10;
                        magsementara += magsementara*10;
                        evasionsementara += 100;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Inferno") {
                    biayaMP = 450;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Membakar musuh! Efek terbakar aktif hingga 10 giliran\n";
                        musuh1.health -= 1000;
                        firemagic = true;
                        waktuterbakar = gerakanplayer.size() + 10;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Ice Rain") {
                    biayaMP = 90;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Hujan es memperlambat musuh! Mengurangi defense musuh 50%\n";
                        musuh1.defense = max(0, musuh1.defense - musuh1.defense*50/100);
                        skillBerhasil = true;
                    }
                } else if (pilih == "Dark Void") {
                    biayaMP = 1000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Void kegelapan menyerap jiwa musuh (-2000 HP)\n";
                        musuh1.health -= 2000;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Holy Lance") {
                    biayaMP = 300;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Tombak suci menusuk! +100% magic damage sementara\n";
                        magsementara += magsementara;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Lightning Wrath") {
                    biayaMP = 2000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Petir murka! Musuh kehilangan 50% HP saat ini\n";
                        musuh1.health -= musuh1.health * 50 / 100;
                        if (musuh1.health < 0) musuh1.health = 0;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Iron Maiden") {
                    biayaMP = 10000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Instant Death\n";
                        musuh1.health = 0;
                        skillBerhasil = true;
                    }
                } else {
                    cout << "Skill tidak ditemukan atau belum dibuka!\n";
                }
                if (skillBerhasil) {
                    kzl.magicpoint -= biayaMP;
                    cout << "MP tersisa: " << kzl.magicpoint << endl;
                } else if (biayaMP > 0) {
                    cout << "MP Anda tidak cukup untuk menggunakan skill ini!\n";
                }
            } else {
                cout << "Tidak ada skill yang terbuka\n";
            }
        }else if (x == 5){
            int jadi = 0;
            kzl.displaySortedPotion();
            cout << "1.Cari Potion\n2. Batal\n";
            cin >> jadi;
            if (jadi == 1){
                string name;
                cin.ignore();
                cout << "Masukkan Nama Potion : ";
                getline(cin, name);
                kzl.searchpotion(name);
            }
        }
        else if (x == 0){
            break;
        }
    } while (musuh1.health > 0 && kzl.health > 0);
    if(musuh1.health == 0) {
        kzl.experience += 300;
        kzl.levelup();
        int randomitem = rand() % 4;
        switch (randomitem) {
            case 1:
                kzl.insertweapon(new weapon("Rusty Sword", 150, 0, false));
                cout << "Anda Mendapatkan Senjata : Rusty Sword" << endl; 
                break;
            case 2:
                kzl.insertarmor(new armor("Common Armor", 200, 50, false));
                cout << "Anda Mendapatkan Armor : Common Armor" << endl; 
                break;
            case 3:
                kzl.insertpotion(new potion("Small Potion", 500, 200));
                cout << "Anda Mendapatkan Potion : Small Potion" << endl; 
                break;
            default:
                break;
        }
    }
}

void serangGoblin() {
    int x = 0;
    musuh goblin(800, 150, 80, 0);
    int healthmusuhawal = goblin.health;
    int attsementara = kzl.attack;
    int magsementara = kzl.magicdamage;
    int evasionsementara = kzl.evasion;
    stack<int> gerakanplayer;
    stack<int> gerakanmusuh;
    bool firemagic = false;
    int waktuterbakar = 0;
    bool gunakanspirit = false;
    cout << "Anda bertemu dengan Goblin" << endl;
    do {
        cout << "1. Serang \n2. Serang dengan sihir api (100 MP)\n3. Gunakan Skill\n4. Gunakan Spirit\n5. Gunakan Potion\n0. Lari!" << endl;
        cout << "Spirit : " << kzl.herospirit.size() << endl;
        cin >> x;
        if (x == 1) {
            int randomeva = rand() % 101;
            if (randomeva <= evasionsementara) {
                cout << "Anda menghindari serangan lawan dan menyerangnya" << endl;
                kzl.serang(attsementara, goblin.health, goblin.defense, gunakanspirit);
                cout << "Health Musuh : " << goblin.health << endl;
                if (firemagic == true && waktuterbakar >= gerakanplayer.size()) {
                    cout << "Musuh terbakar, memberikan damage 20% dari total magic damage" << endl;
                    goblin.health = goblin.health - magsementara * 20 / 100;
                    if(goblin.health < 0) goblin.health = 0;
                    cout << "Health Musuh : " << goblin.health << endl;
                } else if (waktuterbakar < gerakanplayer.size()) {
                    firemagic == false;
                }
                cout << "Health Player : " << kzl.health << endl;
            } else {
                kzl.serang(attsementara, goblin.health, goblin.defense, gunakanspirit);
                cout << "Health Musuh : " << goblin.health << endl;
                if (firemagic == true && waktuterbakar >= gerakanplayer.size()) {
                    cout << "Musuh terbakar, memberikan damage 20% dari total magic damage" << endl;
                    goblin.health = goblin.health - magsementara * 20 / 100;
                    if(goblin.health < 0) goblin.health = 0;
                    cout << "Health Musuh : " << goblin.health << endl;
                } else if (waktuterbakar < gerakanplayer.size()) {
                    firemagic == false;
                }
                goblin.serang(goblin.attack, kzl.health, kzl.defense);
                cout << "Health Player : " << kzl.health << endl;
            }
            attsementara = kzl.attack;
            gunakanspirit = false;
            evasionsementara = kzl.evasion;
            gerakanplayer.push(1);
            gerakanmusuh.push(1);
        }
        else if (x == 4) {
            gunakanspirit = kzl.gunakanspirit(attsementara);
        }
        else if (x == 2) {
            if (kzl.magicpoint >= 100) {
                int randomeva = rand() % 101;
                if (randomeva <= evasionsementara) {
                    cout << "Anda menghindari serangan lawan dan menyerangnya" << endl;
                    firemagic = kzl.serangdengansihirapi(magsementara, goblin.health, goblin.defense, gunakanspirit);
                    waktuterbakar = gerakanplayer.size() + 3;
                    cout << "Health Musuh : " << goblin.health << endl;
                    cout << "Health Player : " << kzl.health << endl;
                } else {
                    firemagic = kzl.serangdengansihirapi(magsementara, goblin.health, goblin.defense, gunakanspirit);
                    waktuterbakar = gerakanplayer.size() + 3;
                    cout << "Health Musuh : " << goblin.health << endl;
                    goblin.serang(goblin.attack, kzl.health, kzl.defense);
                    cout << "Health Player : " << kzl.health << endl;
                }
                kzl.magicpoint = kzl.magicpoint - 50;
                cout << "MP Tersisa : " << kzl.magicpoint << endl;
                magsementara = kzl.magicdamage;
                gunakanspirit = false;
                evasionsementara = kzl.evasion;
            }
            else {
                cout << "You dont have enough MP" << endl;
            }
        }
        else if (x == 3) {
            cout << "===== Daftar Skills yang Terbuka =====" << endl;
            vector<treeskills*> skillList = {
                root1, child1, child2, child1_1, child1_2, child2_1, child2_2,
                root2, magchild1, magchild2, magchild1_1, magchild1_2, magchild2_1, magchild2_2
            };
            vector<string> skillNames;
            for (auto skill : skillList) {
                if (skill->unlocked) {
                    cout << "- " << skill->name << endl;
                    skillNames.push_back(skill->name);
                }
            }
            if (!skillNames.empty()) {
                cout << "Pilih skill untuk digunakan: ";
                string pilih;
                cin.ignore();
                getline(cin, pilih);
                int biayaMP = 0;
                bool skillBerhasil = false;
                if (pilih == "Sword Aura") {
                    biayaMP = 50;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Seranganmu diperkuat oleh aura pedang (+20% attack untuk 1 serangan)\n";
                        attsementara += 20*attsementara/100;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Sword God") {
                    biayaMP = 100;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Kekuatan dewa pedang! (+100% attack dan menghindari 1 serangan)\n";
                        attsementara += attsementara;
                        evasionsementara = 100;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Demon Slash") {
                    biayaMP = 200;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Serangan iblis meledak! (Damage x2)\n";
                        attsementara *= 2;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Storm of Heaven") {
                    biayaMP = 230;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Kamu menciptakan badai suci yang melukai musuh\n";
                        goblin.health -= 800;
                        if (goblin.health < 0) goblin.health = 0;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Hero Ultimate") {
                    biayaMP = 1000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Skill pamungkas pahlawan! (+1000% semua atribut)\n";
                        attsementara += attsementara*10;
                        magsementara += magsementara*10;
                        evasionsementara += 100;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Inferno") {
                    biayaMP = 450;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Membakar musuh! Efek terbakar aktif hingga 10 giliran\n";
                        goblin.health -= 1600;
                        firemagic = true;
                        waktuterbakar = gerakanplayer.size() + 10;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Ice Rain") {
                    biayaMP = 90;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Hujan es memperlambat musuh! Mengurangi defense musuh 50%\n";
                        goblin.defense = max(0, goblin.defense - goblin.defense*50/100);
                        skillBerhasil = true;
                    }
                } else if (pilih == "Dark Void") {
                    biayaMP = 1000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Void kegelapan menyerap jiwa musuh (-1600 HP)\n";
                        goblin.health -= 1600;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Holy Lance") {
                    biayaMP = 300;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Tombak suci menusuk! +100% magic damage sementara\n";
                        magsementara += magsementara;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Lightning Wrath") {
                    biayaMP = 2000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Petir murka! Musuh kehilangan 50% HP saat ini\n";
                        goblin.health -= goblin.health * 50 / 100;
                        if (goblin.health < 0) goblin.health = 0;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Iron Maiden") {
                    biayaMP = 10000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Instant Death\n";
                        goblin.health = 0;
                        skillBerhasil = true;
                    }
                } else {
                    cout << "Skill tidak ditemukan atau belum dibuka!\n";
                }
                if (skillBerhasil) {
                    kzl.magicpoint -= biayaMP;
                    cout << "MP tersisa: " << kzl.magicpoint << endl;
                } else if (biayaMP > 0) {
                    cout << "MP Anda tidak cukup untuk menggunakan skill ini!\n";
                }
            } else {
                cout << "Tidak ada skill yang terbuka\n";
            }
        }else if (x == 5){
            int jadi = 0;
            kzl.displaySortedPotion();
            cout << "1.Cari Potion\n2. Batal\n";
            cin >> jadi;
            if (jadi == 1){
                string name;
                cin.ignore();
                cout << "Masukkan Nama Potion : ";
                getline(cin, name);
                kzl.searchpotion(name);
            }
        }
        else if (x == 0){
            break;
        }
    } while (goblin.health > 0 && kzl.health > 0);
    if(goblin.health == 0) {
        kzl.experience += 500;
        kzl.levelup();
        int randomitem = rand() % 4;
        switch (randomitem) {
            case 1:
                kzl.insertweapon(new weapon("Goblin Cleaver", 300, 0, false));
                cout << "Anda Mendapatkan Senjata : Goblin Cleaver" << endl; 
                break;
            case 2:
                kzl.insertarmor(new armor("Goblin Mail", 400, 100, false));
                cout << "Anda Mendapatkan Armor : Goblin Mail" << endl; 
                break;
            case 3:
                kzl.insertpotion(new potion("Medium Potion", 800, 300));
                cout << "Anda Mendapatkan Potion : Medium Potion" << endl; 
                break;
            default:
                break;
        }
    }
}

void serangOrc() {
    int x = 0;
    musuh musuh1(2000, 250, 100, 0);
    int healthmusuhawal = musuh1.health;
    int attsementara = kzl.attack;
    int magsementara = kzl.magicdamage;
    int evasionsementara = kzl.evasion;
    stack<int> gerakanplayer;
    stack<int> gerakanmusuh;
    bool firemagic = false;
    int waktuterbakar = 0;
    bool gunakanspirit = false;
    cout << "Anda bertemu dengan Orc" << endl;
    do {
        cout << "1. Serang \n2. Serang dengan sihir api (100 MP)\n3. Gunakan Skill\n4. Gunakan Spirit\n5. Gunakan Potion\n0. Lari!" << endl;
        cout << "Spirit : " << kzl.herospirit.size() << endl;
        cin >> x;
        if (x == 1) {
            int randomeva = rand() % 101;
            if (randomeva <= evasionsementara) {
                cout << "Anda menghindari serangan lawan dan menyerangnya" << endl;
                kzl.serang(attsementara, musuh1.health, musuh1.defense, gunakanspirit);
                cout << "Health Musuh : " << musuh1.health << endl;
                if (firemagic == true && waktuterbakar >= gerakanplayer.size()) {
                    cout << "Musuh terbakar, memberikan damage 20% dari total magic damage" << endl;
                    musuh1.health = musuh1.health - magsementara * 20 / 100;
                    if(musuh1.health < 0) musuh1.health = 0;
                    cout << "Health Musuh : " << musuh1.health << endl;
                } else if (waktuterbakar < gerakanplayer.size()) {
                    firemagic == false;
                }
                cout << "Health Player : " << kzl.health << endl;
            } else {
                kzl.serang(attsementara, musuh1.health, musuh1.defense, gunakanspirit);
                cout << "Health Musuh : " << musuh1.health << endl;
                if (firemagic == true && waktuterbakar >= gerakanplayer.size()) {
                    cout << "Musuh terbakar, memberikan damage 20% dari total magic damage" << endl;
                    musuh1.health = musuh1.health - magsementara * 20 / 100;
                    if(musuh1.health < 0) musuh1.health = 0;
                    cout << "Health Musuh : " << musuh1.health << endl;
                } else if (waktuterbakar < gerakanplayer.size()) {
                    firemagic == false;
                }
                musuh1.serang(musuh1.attack, kzl.health, kzl.defense);
                cout << "Health Player : " << kzl.health << endl;
            }
            attsementara = kzl.attack;
            gunakanspirit = false;
            evasionsementara = kzl.evasion;
            gerakanplayer.push(1);
            gerakanmusuh.push(1);
        }
        else if (x == 4) {
            gunakanspirit = kzl.gunakanspirit(attsementara);
        }
        else if (x == 2) {
            if (kzl.magicpoint >= 100) {
                int randomeva = rand() % 101;
                if (randomeva <= evasionsementara) {
                    cout << "Anda menghindari serangan lawan dan menyerangnya" << endl;
                    firemagic = kzl.serangdengansihirapi(magsementara, musuh1.health, musuh1.defense, gunakanspirit);
                    waktuterbakar = gerakanplayer.size() + 3;
                    cout << "Health Musuh : " << musuh1.health << endl;
                    cout << "Health Player : " << kzl.health << endl;
                } else {
                    firemagic = kzl.serangdengansihirapi(magsementara, musuh1.health, musuh1.defense, gunakanspirit);
                    waktuterbakar = gerakanplayer.size() + 3;
                    cout << "Health Musuh : " << musuh1.health << endl;
                    musuh1.serang(musuh1.attack, kzl.health, kzl.defense);
                    cout << "Health Player : " << kzl.health << endl;
                }
                kzl.magicpoint = kzl.magicpoint - 50;
                cout << "MP Tersisa : " << kzl.magicpoint << endl;
                magsementara = kzl.magicdamage;
                gunakanspirit = false;
                evasionsementara = kzl.evasion;
            }
            else {
                cout << "You dont have enough MP" << endl;
            }
        }
        else if (x == 3) {
            cout << "===== Daftar Skills yang Terbuka =====" << endl;
            vector<treeskills*> skillList = {
                root1, child1, child2, child1_1, child1_2, child2_1, child2_2,
                root2, magchild1, magchild2, magchild1_1, magchild1_2, magchild2_1, magchild2_2
            };
            vector<string> skillNames;
            for (auto skill : skillList) {
                if (skill->unlocked) {
                    cout << "- " << skill->name << endl;
                    skillNames.push_back(skill->name);
                }
            }
            if (!skillNames.empty()) {
                cout << "Pilih skill untuk digunakan: ";
                string pilih;
                cin.ignore();
                getline(cin, pilih);
                int biayaMP = 0;
                bool skillBerhasil = false;
                if (pilih == "Sword Aura") {
                    biayaMP = 50;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Seranganmu diperkuat oleh aura pedang (+20% attack untuk 1 serangan)\n";
                        attsementara += 20*attsementara/100;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Sword God") {
                    biayaMP = 100;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Kekuatan dewa pedang! (+100% attack dan menghindari 1 serangan)\n";
                        attsementara += attsementara;
                        evasionsementara = 100;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Demon Slash") {
                    biayaMP = 200;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Serangan iblis meledak! (Damage x2)\n";
                        attsementara *= 2;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Storm of Heaven") {
                    biayaMP = 230;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Kamu menciptakan badai suci yang melukai musuh\n";
                        musuh1.health -= 500;
                        if (musuh1.health < 0) musuh1.health = 0;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Hero Ultimate") {
                    biayaMP = 1000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Skill pamungkas pahlawan! (+1000% semua atribut)\n";
                        attsementara += attsementara*10;
                        magsementara += magsementara*10;
                        evasionsementara += 100;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Inferno") {
                    biayaMP = 450;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Membakar musuh! Efek terbakar aktif hingga 10 giliran\n";
                        musuh1.health -= 1000;
                        firemagic = true;
                        waktuterbakar = gerakanplayer.size() + 10;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Ice Rain") {
                    biayaMP = 90;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Hujan es memperlambat musuh! Mengurangi defense musuh 50%\n";
                        musuh1.defense = max(0, musuh1.defense - musuh1.defense*50/100);
                        skillBerhasil = true;
                    }
                } else if (pilih == "Dark Void") {
                    biayaMP = 1000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Void kegelapan menyerap jiwa musuh (-2000 HP)\n";
                        musuh1.health -= 2000;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Holy Lance") {
                    biayaMP = 300;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Tombak suci menusuk! +100% magic damage sementara\n";
                        magsementara += magsementara;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Lightning Wrath") {
                    biayaMP = 2000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Petir murka! Musuh kehilangan 50% HP saat ini\n";
                        musuh1.health -= musuh1.health * 50 / 100;
                        if (musuh1.health < 0) musuh1.health = 0;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Iron Maiden") {
                    biayaMP = 10000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Instant Death\n";
                        musuh1.health = 0;
                        skillBerhasil = true;
                    }
                } else {
                    cout << "Skill tidak ditemukan atau belum dibuka!\n";
                }
                if (skillBerhasil) {
                    kzl.magicpoint -= biayaMP;
                    cout << "MP tersisa: " << kzl.magicpoint << endl;
                } else if (biayaMP > 0) {
                    cout << "MP Anda tidak cukup untuk menggunakan skill ini!\n";
                }
            } else {
                cout << "Tidak ada skill yang terbuka\n";
            }
        }else if (x == 5){
            int jadi = 0;
            kzl.displaySortedPotion();
            cout << "1.Cari Potion\n2. Batal\n";
            cin >> jadi;
            if (jadi == 1){
                string name;
                cin.ignore();
                cout << "Masukkan Nama Potion : ";
                getline(cin, name);
                kzl.searchpotion(name);
            }
        }
        else if (x == 0){
            break;
        }
    } while (musuh1.health > 0 && kzl.health > 0);
    if(musuh1.health == 0) {
        kzl.experience += 1000;
        kzl.levelup();
        int randomitem = rand() % 4;
        switch (randomitem) {
            case 1:
                kzl.insertweapon(new weapon("Orcish Axe", 300, 50, false));
                cout << "Anda Mendapatkan Senjata : Orcish Axe" << endl; 
                break;
            case 2:
                kzl.insertarmor(new armor("Orcish Plate", 500, 100, false));
                cout << "Anda Mendapatkan Armor : Orcish Plate" << endl; 
                break;
            case 3:
                kzl.insertpotion(new potion("Large Health Potion", 500, 100));
                cout << "Anda Mendapatkan Potion : Large Health Potion" << endl; 
                break;
            default:
                break;
        }
    }

}
void serangLizardMen() {
    int x = 0;
    musuh musuh1(3500, 400, 200, 0);
    int healthmusuhawal = musuh1.health;
    int attsementara = kzl.attack;
    int magsementara = kzl.magicdamage;
    int evasionsementara = kzl.evasion;
    stack<int> gerakanplayer;
    stack<int> gerakanmusuh;
    bool firemagic = false;
    int waktuterbakar = 0;
    bool gunakanspirit = false;
    cout << "Anda bertemu dengan Lizard Man" << endl;
    do {
        cout << "1. Serang \n2. Serang dengan sihir api (100 MP)\n3. Gunakan Skill\n4. Gunakan Spirit\n5. Gunakan Potion\n0. Lari!" << endl;
        cout << "Spirit : " << kzl.herospirit.size() << endl;
        cin >> x;
        if (x == 1) {
            int randomeva = rand() % 101;
            if (randomeva <= evasionsementara) {
                cout << "Anda menghindari serangan lawan dan menyerangnya" << endl;
                kzl.serang(attsementara, musuh1.health, musuh1.defense, gunakanspirit);
                cout << "Health Musuh : " << musuh1.health << endl;
                if (firemagic == true && waktuterbakar >= gerakanplayer.size()) {
                    cout << "Musuh terbakar, memberikan damage 20% dari total magic damage" << endl;
                    musuh1.health = musuh1.health - magsementara * 20 / 100;
                    if(musuh1.health < 0) musuh1.health = 0;
                    cout << "Health Musuh : " << musuh1.health << endl;
                } else if (waktuterbakar < gerakanplayer.size()) {
                    firemagic == false;
                }
                cout << "Health Player : " << kzl.health << endl;
            } else {
                kzl.serang(attsementara, musuh1.health, musuh1.defense, gunakanspirit);
                cout << "Health Musuh : " << musuh1.health << endl;
                if (firemagic == true && waktuterbakar >= gerakanplayer.size()) {
                    cout << "Musuh terbakar, memberikan damage 20% dari total magic damage" << endl;
                    musuh1.health = musuh1.health - magsementara * 20 / 100;
                    if(musuh1.health < 0) musuh1.health = 0;
                    cout << "Health Musuh : " << musuh1.health << endl;
                } else if (waktuterbakar < gerakanplayer.size()) {
                    firemagic == false;
                }
                musuh1.serang(musuh1.attack, kzl.health, kzl.defense);
                cout << "Health Player : " << kzl.health << endl;
            }
            attsementara = kzl.attack;
            gunakanspirit = false;
            evasionsementara = kzl.evasion;
            gerakanplayer.push(1);
            gerakanmusuh.push(1);
        }
        else if (x == 4) {
            gunakanspirit = kzl.gunakanspirit(attsementara);
        }
        else if (x == 2) {
            if (kzl.magicpoint >= 100) {
                int randomeva = rand() % 101;
                if (randomeva <= evasionsementara) {
                    cout << "Anda menghindari serangan lawan dan menyerangnya" << endl;
                    firemagic = kzl.serangdengansihirapi(magsementara, musuh1.health, musuh1.defense, gunakanspirit);
                    waktuterbakar = gerakanplayer.size() + 3;
                    cout << "Health Musuh : " << musuh1.health << endl;
                    cout << "Health Player : " << kzl.health << endl;
                } else {
                    firemagic = kzl.serangdengansihirapi(magsementara, musuh1.health, musuh1.defense, gunakanspirit);
                    waktuterbakar = gerakanplayer.size() + 3;
                    cout << "Health Musuh : " << musuh1.health << endl;
                    musuh1.serang(musuh1.attack, kzl.health, kzl.defense);
                    cout << "Health Player : " << kzl.health << endl;
                }
                kzl.magicpoint = kzl.magicpoint - 50;
                cout << "MP Tersisa : " << kzl.magicpoint << endl;
                magsementara = kzl.magicdamage;
                gunakanspirit = false;
                evasionsementara = kzl.evasion;
            }
            else {
                cout << "You dont have enough MP" << endl;
            }
        }
        else if (x == 3) {
            cout << "===== Daftar Skills yang Terbuka =====" << endl;
            vector<treeskills*> skillList = {
                root1, child1, child2, child1_1, child1_2, child2_1, child2_2,
                root2, magchild1, magchild2, magchild1_1, magchild1_2, magchild2_1, magchild2_2
            };
            vector<string> skillNames;
            for (auto skill : skillList) {
                if (skill->unlocked) {
                    cout << "- " << skill->name << endl;
                    skillNames.push_back(skill->name);
                }
            }
            if (!skillNames.empty()) {
                cout << "Pilih skill untuk digunakan: ";
                string pilih;
                cin.ignore();
                getline(cin, pilih);
                int biayaMP = 0;
                bool skillBerhasil = false;
                if (pilih == "Sword Aura") {
                    biayaMP = 50;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Seranganmu diperkuat oleh aura pedang (+20% attack untuk 1 serangan)\n";
                        attsementara += 20*attsementara/100;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Sword God") {
                    biayaMP = 100;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Kekuatan dewa pedang! (+100% attack dan menghindari 1 serangan)\n";
                        attsementara += attsementara;
                        evasionsementara = 100;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Demon Slash") {
                    biayaMP = 200;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Serangan iblis meledak! (Damage x2)\n";
                        attsementara *= 2;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Storm of Heaven") {
                    biayaMP = 230;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Kamu menciptakan badai suci yang melukai musuh\n";
                        musuh1.health -= 500;
                        if (musuh1.health < 0) musuh1.health = 0;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Hero Ultimate") {
                    biayaMP = 1000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Skill pamungkas pahlawan! (+1000% semua atribut)\n";
                        attsementara += attsementara*10;
                        magsementara += magsementara*10;
                        evasionsementara += 100;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Inferno") {
                    biayaMP = 450;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Membakar musuh! Efek terbakar aktif hingga 10 giliran\n";
                        musuh1.health -= 1000;
                        firemagic = true;
                        waktuterbakar = gerakanplayer.size() + 10;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Ice Rain") {
                    biayaMP = 90;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Hujan es memperlambat musuh! Mengurangi defense musuh 50%\n";
                        musuh1.defense = max(0, musuh1.defense - musuh1.defense*50/100);
                        skillBerhasil = true;
                    }
                } else if (pilih == "Dark Void") {
                    biayaMP = 1000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Void kegelapan menyerap jiwa musuh (-2000 HP)\n";
                        musuh1.health -= 2000;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Holy Lance") {
                    biayaMP = 300;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Tombak suci menusuk! +100% magic damage sementara\n";
                        magsementara += magsementara;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Lightning Wrath") {
                    biayaMP = 2000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Petir murka! Musuh kehilangan 50% HP saat ini\n";
                        musuh1.health -= musuh1.health * 50 / 100;
                        if (musuh1.health < 0) musuh1.health = 0;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Iron Maiden") {
                    biayaMP = 10000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Instant Death\n";
                        musuh1.health = 0;
                        skillBerhasil = true;
                    }
                } else {
                    cout << "Skill tidak ditemukan atau belum dibuka!\n";
                }
                if (skillBerhasil) {
                    kzl.magicpoint -= biayaMP;
                    cout << "MP tersisa: " << kzl.magicpoint << endl;
                } else if (biayaMP > 0) {
                    cout << "MP Anda tidak cukup untuk menggunakan skill ini!\n";
                }
            } else {
                cout << "Tidak ada skill yang terbuka\n";
            }
        }else if (x == 5){
            int jadi = 0;
            kzl.displaySortedPotion();
            cout << "1.Cari Potion\n2. Batal\n";
            cin >> jadi;
            if (jadi == 1){
                string name;
                cin.ignore();
                cout << "Masukkan Nama Potion : ";
                getline(cin, name);
                kzl.searchpotion(name);
            }
        }
        else if (x == 0){
            break;
        }
    } while (musuh1.health > 0 && kzl.health > 0);
    if(musuh1.health == 0) {
        kzl.experience += 2000;
        kzl.levelup();
        int randomitem = rand() % 4;
        switch (randomitem) {
            case 1:
                kzl.insertweapon(new weapon("Lizard Spear", 600, 100, false));
                cout << "Anda Mendapatkan Senjata : Lizard Spear" << endl; 
                break;
            case 2:
                kzl.insertarmor(new armor("Scale Mail", 800, 200, false));
                cout << "Anda Mendapatkan Armor : Scale Mail" << endl; 
                break;
            case 3:
                kzl.insertpotion(new potion("Greater Health Potion", 800, 200));
                cout << "Anda Mendapatkan Potion : Greater Health Potion" << endl; 
                break;
            default:
                break;
        }
    }
}
void serangOgre() {
    int x = 0;
    musuh musuh1(6000, 800, 400, 0);;
    int healthmusuhawal = musuh1.health;
    int attsementara = kzl.attack;
    int magsementara = kzl.magicdamage;
    int evasionsementara = kzl.evasion;
    stack<int> gerakanplayer;
    stack<int> gerakanmusuh;
    bool firemagic = false;
    int waktuterbakar = 0;
    bool gunakanspirit = false;
    cout << "Anda bertemu dengan Ogre" << endl;
    do {
        cout << "1. Serang \n2. Serang dengan sihir api (100 MP)\n3. Gunakan Skill\n4. Gunakan Spirit\n5. Gunakan Potion\n0. Lari!" << endl;
        cout << "Spirit : " << kzl.herospirit.size() << endl;
        cin >> x;
        if (x == 1) {
            int randomeva = rand() % 101;
            if (randomeva <= evasionsementara) {
                cout << "Anda menghindari serangan lawan dan menyerangnya" << endl;
                kzl.serang(attsementara, musuh1.health, musuh1.defense, gunakanspirit);
                cout << "Health Musuh : " << musuh1.health << endl;
                if (firemagic == true && waktuterbakar >= gerakanplayer.size()) {
                    cout << "Musuh terbakar, memberikan damage 20% dari total magic damage" << endl;
                    musuh1.health = musuh1.health - magsementara * 20 / 100;
                    if(musuh1.health < 0) musuh1.health = 0;
                    cout << "Health Musuh : " << musuh1.health << endl;
                } else if (waktuterbakar < gerakanplayer.size()) {
                    firemagic == false;
                }
                cout << "Health Player : " << kzl.health << endl;
            } else {
                kzl.serang(attsementara, musuh1.health, musuh1.defense, gunakanspirit);
                cout << "Health Musuh : " << musuh1.health << endl;
                if (firemagic == true && waktuterbakar >= gerakanplayer.size()) {
                    cout << "Musuh terbakar, memberikan damage 20% dari total magic damage" << endl;
                    musuh1.health = musuh1.health - magsementara * 20 / 100;
                    if(musuh1.health < 0) musuh1.health = 0;
                    cout << "Health Musuh : " << musuh1.health << endl;
                } else if (waktuterbakar < gerakanplayer.size()) {
                    firemagic == false;
                }
                musuh1.serang(musuh1.attack, kzl.health, kzl.defense);
                cout << "Health Player : " << kzl.health << endl;
            }
            attsementara = kzl.attack;
            gunakanspirit = false;
            evasionsementara = kzl.evasion;
            gerakanplayer.push(1);
            gerakanmusuh.push(1);
        }
        else if (x == 4) {
            gunakanspirit = kzl.gunakanspirit(attsementara);
        }
        else if (x == 2) {
            if (kzl.magicpoint >= 100) {
                int randomeva = rand() % 101;
                if (randomeva <= evasionsementara) {
                    cout << "Anda menghindari serangan lawan dan menyerangnya" << endl;
                    firemagic = kzl.serangdengansihirapi(magsementara, musuh1.health, musuh1.defense, gunakanspirit);
                    waktuterbakar = gerakanplayer.size() + 3;
                    cout << "Health Musuh : " << musuh1.health << endl;
                    cout << "Health Player : " << kzl.health << endl;
                } else {
                    firemagic = kzl.serangdengansihirapi(magsementara, musuh1.health, musuh1.defense, gunakanspirit);
                    waktuterbakar = gerakanplayer.size() + 3;
                    cout << "Health Musuh : " << musuh1.health << endl;
                    musuh1.serang(musuh1.attack, kzl.health, kzl.defense);
                    cout << "Health Player : " << kzl.health << endl;
                }
                kzl.magicpoint = kzl.magicpoint - 50;
                cout << "MP Tersisa : " << kzl.magicpoint << endl;
                magsementara = kzl.magicdamage;
                gunakanspirit = false;
                evasionsementara = kzl.evasion;
            }
            else {
                cout << "You dont have enough MP" << endl;
            }
        }
        else if (x == 3) {
            cout << "===== Daftar Skills yang Terbuka =====" << endl;
            vector<treeskills*> skillList = {
                root1, child1, child2, child1_1, child1_2, child2_1, child2_2,
                root2, magchild1, magchild2, magchild1_1, magchild1_2, magchild2_1, magchild2_2
            };
            vector<string> skillNames;
            for (auto skill : skillList) {
                if (skill->unlocked) {
                    cout << "- " << skill->name << endl;
                    skillNames.push_back(skill->name);
                }
            }
            if (!skillNames.empty()) {
                cout << "Pilih skill untuk digunakan: ";
                string pilih;
                cin.ignore();
                getline(cin, pilih);
                int biayaMP = 0;
                bool skillBerhasil = false;
                if (pilih == "Sword Aura") {
                    biayaMP = 50;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Seranganmu diperkuat oleh aura pedang (+20% attack untuk 1 serangan)\n";
                        attsementara += 20*attsementara/100;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Sword God") {
                    biayaMP = 100;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Kekuatan dewa pedang! (+100% attack dan menghindari 1 serangan)\n";
                        attsementara += attsementara;
                        evasionsementara = 100;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Demon Slash") {
                    biayaMP = 200;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Serangan iblis meledak! (Damage x2)\n";
                        attsementara *= 2;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Storm of Heaven") {
                    biayaMP = 230;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Kamu menciptakan badai suci yang melukai musuh\n";
                        musuh1.health -= 500;
                        if (musuh1.health < 0) musuh1.health = 0;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Hero Ultimate") {
                    biayaMP = 1000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Skill pamungkas pahlawan! (+1000% semua atribut)\n";
                        attsementara += attsementara*10;
                        magsementara += magsementara*10;
                        evasionsementara += 100;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Inferno") {
                    biayaMP = 450;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Membakar musuh! Efek terbakar aktif hingga 10 giliran\n";
                        musuh1.health -= 1000;
                        firemagic = true;
                        waktuterbakar = gerakanplayer.size() + 10;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Ice Rain") {
                    biayaMP = 90;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Hujan es memperlambat musuh! Mengurangi defense musuh 50%\n";
                        musuh1.defense = max(0, musuh1.defense - musuh1.defense*50/100);
                        skillBerhasil = true;
                    }
                } else if (pilih == "Dark Void") {
                    biayaMP = 1000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Void kegelapan menyerap jiwa musuh (-2000 HP)\n";
                        musuh1.health -= 2000;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Holy Lance") {
                    biayaMP = 300;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Tombak suci menusuk! +100% magic damage sementara\n";
                        magsementara += magsementara;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Lightning Wrath") {
                    biayaMP = 2000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Petir murka! Musuh kehilangan 50% HP saat ini\n";
                        musuh1.health -= musuh1.health * 50 / 100;
                        if (musuh1.health < 0) musuh1.health = 0;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Iron Maiden") {
                    biayaMP = 10000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Instant Death\n";
                        musuh1.health = 0;
                        skillBerhasil = true;
                    }
                } else {
                    cout << "Skill tidak ditemukan atau belum dibuka!\n";
                }
                if (skillBerhasil) {
                    kzl.magicpoint -= biayaMP;
                    cout << "MP tersisa: " << kzl.magicpoint << endl;
                } else if (biayaMP > 0) {
                    cout << "MP Anda tidak cukup untuk menggunakan skill ini!\n";
                }
            } else {
                cout << "Tidak ada skill yang terbuka\n";
            }
        }else if (x == 5){
            int jadi = 0;
            kzl.displaySortedPotion();
            cout << "1.Cari Potion\n2. Batal\n";
            cin >> jadi;
            if (jadi == 1){
                string name;
                cin.ignore();
                cout << "Masukkan Nama Potion : ";
                getline(cin, name);
                kzl.searchpotion(name);
            }
        }
        else if (x == 0){
            break;
        }
    } while (musuh1.health > 0 && kzl.health > 0);
    if(musuh1.health == 0) {
        kzl.experience += 4000;
        kzl.levelup();
        int randomitem = rand() % 4;
        switch (randomitem) {
            case 1:
                kzl.insertweapon(new weapon("Ogre Club", 1200, 200, false));
                cout << "Anda Mendapatkan Senjata : Ogre Club" << endl; 
                break;
            case 2:
                kzl.insertarmor(new armor("Ogre Hide", 1500, 400, false));
                cout << "Anda Mendapatkan Armor : Ogre Hide" << endl; 
                break;
            case 3:
                kzl.insertpotion(new potion("Super Health Potion", 1500, 400));
                cout << "Anda Mendapatkan Potion : Super Health Potion" << endl; 
                break;
            default:
                break;
        }
    }
}
void serangWyvern() {
    int x = 0;
    musuh musuh1(10000, 1500, 800, 0);
    int healthmusuhawal = musuh1.health;
    int attsementara = kzl.attack;
    int magsementara = kzl.magicdamage;
    int evasionsementara = kzl.evasion;
    stack<int> gerakanplayer;
    stack<int> gerakanmusuh;
    bool firemagic = false;
    int waktuterbakar = 0;
    bool gunakanspirit = false;
    cout << "Anda bertemu dengan Wyvern" << endl;
    do {
        cout << "1. Serang \n2. Serang dengan sihir api (100 MP)\n3. Gunakan Skill\n4. Gunakan Spirit\n5. Gunakan Potion\n0. Lari!" << endl;
        cout << "Spirit : " << kzl.herospirit.size() << endl;
        cin >> x;
        if (x == 1) {
            int randomeva = rand() % 101;
            if (randomeva <= evasionsementara) {
                cout << "Anda menghindari serangan lawan dan menyerangnya" << endl;
                kzl.serang(attsementara, musuh1.health, musuh1.defense, gunakanspirit);
                cout << "Health Musuh : " << musuh1.health << endl;
                if (firemagic == true && waktuterbakar >= gerakanplayer.size()) {
                    cout << "Musuh terbakar, memberikan damage 20% dari total magic damage" << endl;
                    musuh1.health = musuh1.health - magsementara * 20 / 100;
                    if(musuh1.health < 0) musuh1.health = 0;
                    cout << "Health Musuh : " << musuh1.health << endl;
                } else if (waktuterbakar < gerakanplayer.size()) {
                    firemagic == false;
                }
                cout << "Health Player : " << kzl.health << endl;
            } else {
                kzl.serang(attsementara, musuh1.health, musuh1.defense, gunakanspirit);
                cout << "Health Musuh : " << musuh1.health << endl;
                if (firemagic == true && waktuterbakar >= gerakanplayer.size()) {
                    cout << "Musuh terbakar, memberikan damage 20% dari total magic damage" << endl;
                    musuh1.health = musuh1.health - magsementara * 20 / 100;
                    if(musuh1.health < 0) musuh1.health = 0;
                    cout << "Health Musuh : " << musuh1.health << endl;
                } else if (waktuterbakar < gerakanplayer.size()) {
                    firemagic == false;
                }
                musuh1.serang(musuh1.attack, kzl.health, kzl.defense);
                cout << "Health Player : " << kzl.health << endl;
            }
            attsementara = kzl.attack;
            gunakanspirit = false;
            evasionsementara = kzl.evasion;
            gerakanplayer.push(1);
            gerakanmusuh.push(1);
        }
        else if (x == 4) {
            gunakanspirit = kzl.gunakanspirit(attsementara);
        }
        else if (x == 2) {
            if (kzl.magicpoint >= 100) {
                int randomeva = rand() % 101;
                if (randomeva <= evasionsementara) {
                    cout << "Anda menghindari serangan lawan dan menyerangnya" << endl;
                    firemagic = kzl.serangdengansihirapi(magsementara, musuh1.health, musuh1.defense, gunakanspirit);
                    waktuterbakar = gerakanplayer.size() + 3;
                    cout << "Health Musuh : " << musuh1.health << endl;
                    cout << "Health Player : " << kzl.health << endl;
                } else {
                    firemagic = kzl.serangdengansihirapi(magsementara, musuh1.health, musuh1.defense, gunakanspirit);
                    waktuterbakar = gerakanplayer.size() + 3;
                    cout << "Health Musuh : " << musuh1.health << endl;
                    musuh1.serang(musuh1.attack, kzl.health, kzl.defense);
                    cout << "Health Player : " << kzl.health << endl;
                }
                kzl.magicpoint = kzl.magicpoint - 50;
                cout << "MP Tersisa : " << kzl.magicpoint << endl;
                magsementara = kzl.magicdamage;
                gunakanspirit = false;
                evasionsementara = kzl.evasion;
            }
            else {
                cout << "You dont have enough MP" << endl;
            }
        }
        else if (x == 3) {
            cout << "===== Daftar Skills yang Terbuka =====" << endl;
            vector<treeskills*> skillList = {
                root1, child1, child2, child1_1, child1_2, child2_1, child2_2,
                root2, magchild1, magchild2, magchild1_1, magchild1_2, magchild2_1, magchild2_2
            };
            vector<string> skillNames;
            for (auto skill : skillList) {
                if (skill->unlocked) {
                    cout << "- " << skill->name << endl;
                    skillNames.push_back(skill->name);
                }
            }
            if (!skillNames.empty()) {
                cout << "Pilih skill untuk digunakan: ";
                string pilih;
                cin.ignore();
                getline(cin, pilih);
                int biayaMP = 0;
                bool skillBerhasil = false;
                if (pilih == "Sword Aura") {
                    biayaMP = 50;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Seranganmu diperkuat oleh aura pedang (+20% attack untuk 1 serangan)\n";
                        attsementara += 20*attsementara/100;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Sword God") {
                    biayaMP = 100;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Kekuatan dewa pedang! (+100% attack dan menghindari 1 serangan)\n";
                        attsementara += attsementara;
                        evasionsementara = 100;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Demon Slash") {
                    biayaMP = 200;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Serangan iblis meledak! (Damage x2)\n";
                        attsementara *= 2;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Storm of Heaven") {
                    biayaMP = 230;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Kamu menciptakan badai suci yang melukai musuh\n";
                        musuh1.health -= 500;
                        if (musuh1.health < 0) musuh1.health = 0;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Hero Ultimate") {
                    biayaMP = 1000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Skill pamungkas pahlawan! (+1000% semua atribut)\n";
                        attsementara += attsementara*10;
                        magsementara += magsementara*10;
                        evasionsementara += 100;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Inferno") {
                    biayaMP = 450;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Membakar musuh! Efek terbakar aktif hingga 10 giliran\n";
                        musuh1.health -= 1000;
                        firemagic = true;
                        waktuterbakar = gerakanplayer.size() + 10;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Ice Rain") {
                    biayaMP = 90;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Hujan es memperlambat musuh! Mengurangi defense musuh 50%\n";
                        musuh1.defense = max(0, musuh1.defense - musuh1.defense*50/100);
                        skillBerhasil = true;
                    }
                } else if (pilih == "Dark Void") {
                    biayaMP = 1000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Void kegelapan menyerap jiwa musuh (-2000 HP)\n";
                        musuh1.health -= 2000;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Holy Lance") {
                    biayaMP = 300;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Tombak suci menusuk! +100% magic damage sementara\n";
                        magsementara += magsementara;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Lightning Wrath") {
                    biayaMP = 2000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Petir murka! Musuh kehilangan 50% HP saat ini\n";
                        musuh1.health -= musuh1.health * 50 / 100;
                        if (musuh1.health < 0) musuh1.health = 0;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Iron Maiden") {
                    biayaMP = 10000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Instant Death\n";
                        musuh1.health = 0;
                        skillBerhasil = true;
                    }
                } else {
                    cout << "Skill tidak ditemukan atau belum dibuka!\n";
                }
                if (skillBerhasil) {
                    kzl.magicpoint -= biayaMP;
                    cout << "MP tersisa: " << kzl.magicpoint << endl;
                } else if (biayaMP > 0) {
                    cout << "MP Anda tidak cukup untuk menggunakan skill ini!\n";
                }
            } else {
                cout << "Tidak ada skill yang terbuka\n";
            }
        }else if (x == 5){
            int jadi = 0;
            kzl.displaySortedPotion();
            cout << "1.Cari Potion\n2. Batal\n";
            cin >> jadi;
            if (jadi == 1){
                string name;
                cin.ignore();
                cout << "Masukkan Nama Potion : ";
                getline(cin, name);
                kzl.searchpotion(name);
            }
        }
        else if (x == 0){
            break;
        }
    } while (musuh1.health > 0 && kzl.health > 0);
    if(musuh1.health == 0) {
        kzl.experience += 8000;
        kzl.levelup();
        int randomitem = rand() % 4;
        switch (randomitem) {
            case 1:
                kzl.insertweapon(new weapon("Wyvern Fang", 2500, 500, false));
                cout << "Anda Mendapatkan Senjata : Wyvern Fang" << endl; 
                break;
            case 2:
                kzl.insertarmor(new armor("Wyvern Scale", 3000, 800, false));
                cout << "Anda Mendapatkan Armor : Wyvern Scale" << endl; 
                break;
            case 3:
                kzl.insertpotion(new potion("Mega Health Potion", 3000, 800));
                cout << "Anda Mendapatkan Potion : Mega Health Potion" << endl; 
                break;
            default:
                break;
        }
    }
}
void serangGolem() {
    int x = 0;
    musuh musuh1(15000, 2000, 1500, 0);
    int healthmusuhawal = musuh1.health;
    int attsementara = kzl.attack;
    int magsementara = kzl.magicdamage;
    int evasionsementara = kzl.evasion;
    stack<int> gerakanplayer;
    stack<int> gerakanmusuh;
    bool firemagic = false;
    int waktuterbakar = 0;
    bool gunakanspirit = false;
    cout << "Anda bertemu dengan Golem" << endl;
    do {
        cout << "1. Serang \n2. Serang dengan sihir api (100 MP)\n3. Gunakan Skill\n4. Gunakan Spirit\n5. Gunakan Potion\n0. Lari!" << endl;
        cout << "Spirit : " << kzl.herospirit.size() << endl;
        cin >> x;
        if (x == 1) {
            int randomeva = rand() % 101;
            if (randomeva <= evasionsementara) {
                cout << "Anda menghindari serangan lawan dan menyerangnya" << endl;
                kzl.serang(attsementara, musuh1.health, musuh1.defense, gunakanspirit);
                cout << "Health Musuh : " << musuh1.health << endl;
                if (firemagic == true && waktuterbakar >= gerakanplayer.size()) {
                    cout << "Musuh terbakar, memberikan damage 20% dari total magic damage" << endl;
                    musuh1.health = musuh1.health - magsementara * 20 / 100;
                    if(musuh1.health < 0) musuh1.health = 0;
                    cout << "Health Musuh : " << musuh1.health << endl;
                } else if (waktuterbakar < gerakanplayer.size()) {
                    firemagic == false;
                }
                cout << "Health Player : " << kzl.health << endl;
            } else {
                kzl.serang(attsementara, musuh1.health, musuh1.defense, gunakanspirit);
                cout << "Health Musuh : " << musuh1.health << endl;
                if (firemagic == true && waktuterbakar >= gerakanplayer.size()) {
                    cout << "Musuh terbakar, memberikan damage 20% dari total magic damage" << endl;
                    musuh1.health = musuh1.health - magsementara * 20 / 100;
                    if(musuh1.health < 0) musuh1.health = 0;
                    cout << "Health Musuh : " << musuh1.health << endl;
                } else if (waktuterbakar < gerakanplayer.size()) {
                    firemagic == false;
                }
                musuh1.serang(musuh1.attack, kzl.health, kzl.defense);
                cout << "Health Player : " << kzl.health << endl;
            }
            attsementara = kzl.attack;
            gunakanspirit = false;
            evasionsementara = kzl.evasion;
            gerakanplayer.push(1);
            gerakanmusuh.push(1);
        }
        else if (x == 4) {
            gunakanspirit = kzl.gunakanspirit(attsementara);
        }
        else if (x == 2) {
            if (kzl.magicpoint >= 100) {
                int randomeva = rand() % 101;
                if (randomeva <= evasionsementara) {
                    cout << "Anda menghindari serangan lawan dan menyerangnya" << endl;
                    firemagic = kzl.serangdengansihirapi(magsementara, musuh1.health, musuh1.defense, gunakanspirit);
                    waktuterbakar = gerakanplayer.size() + 3;
                    cout << "Health Musuh : " << musuh1.health << endl;
                    cout << "Health Player : " << kzl.health << endl;
                } else {
                    firemagic = kzl.serangdengansihirapi(magsementara, musuh1.health, musuh1.defense, gunakanspirit);
                    waktuterbakar = gerakanplayer.size() + 3;
                    cout << "Health Musuh : " << musuh1.health << endl;
                    musuh1.serang(musuh1.attack, kzl.health, kzl.defense);
                    cout << "Health Player : " << kzl.health << endl;
                }
                kzl.magicpoint = kzl.magicpoint - 50;
                cout << "MP Tersisa : " << kzl.magicpoint << endl;
                magsementara = kzl.magicdamage;
                gunakanspirit = false;
                evasionsementara = kzl.evasion;
            }
            else {
                cout << "You dont have enough MP" << endl;
            }
        }
        else if (x == 3) {
            cout << "===== Daftar Skills yang Terbuka =====" << endl;
            vector<treeskills*> skillList = {
                root1, child1, child2, child1_1, child1_2, child2_1, child2_2,
                root2, magchild1, magchild2, magchild1_1, magchild1_2, magchild2_1, magchild2_2
            };
            vector<string> skillNames;
            for (auto skill : skillList) {
                if (skill->unlocked) {
                    cout << "- " << skill->name << endl;
                    skillNames.push_back(skill->name);
                }
            }
            if (!skillNames.empty()) {
                cout << "Pilih skill untuk digunakan: ";
                string pilih;
                cin.ignore();
                getline(cin, pilih);
                int biayaMP = 0;
                bool skillBerhasil = false;
                if (pilih == "Sword Aura") {
                    biayaMP = 50;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Seranganmu diperkuat oleh aura pedang (+20% attack untuk 1 serangan)\n";
                        attsementara += 20*attsementara/100;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Sword God") {
                    biayaMP = 100;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Kekuatan dewa pedang! (+100% attack dan menghindari 1 serangan)\n";
                        attsementara += attsementara;
                        evasionsementara = 100;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Demon Slash") {
                    biayaMP = 200;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Serangan iblis meledak! (Damage x2)\n";
                        attsementara *= 2;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Storm of Heaven") {
                    biayaMP = 230;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Kamu menciptakan badai suci yang melukai musuh\n";
                        musuh1.health -= 500;
                        if (musuh1.health < 0) musuh1.health = 0;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Hero Ultimate") {
                    biayaMP = 1000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Skill pamungkas pahlawan! (+1000% semua atribut)\n";
                        attsementara += attsementara*10;
                        magsementara += magsementara*10;
                        evasionsementara += 100;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Inferno") {
                    biayaMP = 450;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Membakar musuh! Efek terbakar aktif hingga 10 giliran\n";
                        musuh1.health -= 1000;
                        firemagic = true;
                        waktuterbakar = gerakanplayer.size() + 10;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Ice Rain") {
                    biayaMP = 90;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Hujan es memperlambat musuh! Mengurangi defense musuh 50%\n";
                        musuh1.defense = max(0, musuh1.defense - musuh1.defense*50/100);
                        skillBerhasil = true;
                    }
                } else if (pilih == "Dark Void") {
                    biayaMP = 1000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Void kegelapan menyerap jiwa musuh (-2000 HP)\n";
                        musuh1.health -= 2000;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Holy Lance") {
                    biayaMP = 300;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Tombak suci menusuk! +100% magic damage sementara\n";
                        magsementara += magsementara;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Lightning Wrath") {
                    biayaMP = 2000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Petir murka! Musuh kehilangan 50% HP saat ini\n";
                        musuh1.health -= musuh1.health * 50 / 100;
                        if (musuh1.health < 0) musuh1.health = 0;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Iron Maiden") {
                    biayaMP = 10000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Instant Death\n";
                        musuh1.health = 0;
                        skillBerhasil = true;
                    }
                } else {
                    cout << "Skill tidak ditemukan atau belum dibuka!\n";
                }
                if (skillBerhasil) {
                    kzl.magicpoint -= biayaMP;
                    cout << "MP tersisa: " << kzl.magicpoint << endl;
                } else if (biayaMP > 0) {
                    cout << "MP Anda tidak cukup untuk menggunakan skill ini!\n";
                }
            } else {
                cout << "Tidak ada skill yang terbuka\n";
            }
        }else if (x == 5){
            int jadi = 0;
            kzl.displaySortedPotion();
            cout << "1.Cari Potion\n2. Batal\n";
            cin >> jadi;
            if (jadi == 1){
                string name;
                cin.ignore();
                cout << "Masukkan Nama Potion : ";
                getline(cin, name);
                kzl.searchpotion(name);
            }
        }
        else if (x == 0){
            break;
        }
    } while (musuh1.health > 0 && kzl.health > 0);
    if(musuh1.health == 0) {
        kzl.experience += 12000;
        kzl.levelup();
        int randomitem = rand() % 4;
        switch (randomitem) {
            case 1:
                kzl.insertweapon(new weapon("Golem Fist", 4000, 800, false));
                cout << "Anda Mendapatkan Senjata : Golem Fist" << endl; 
                break;
            case 2:
                kzl.insertarmor(new armor("Stone Plate", 5000, 1500, false));
                cout << "Anda Mendapatkan Armor : Stone Plate" << endl; 
                break;
            case 3:
                kzl.insertpotion(new potion("Ultra Health Potion", 5000, 1200));
                cout << "Anda Mendapatkan Potion : Ultra Health Potion" << endl; 
                break;
            default:
                break;
        }
    }
}
void serangChimera() {
    int x = 0;
    musuh musuh1(20000, 3000, 2000, 0);
    int healthmusuhawal = musuh1.health;
    int attsementara = kzl.attack;
    int magsementara = kzl.magicdamage;
    int evasionsementara = kzl.evasion;
    stack<int> gerakanplayer;
    stack<int> gerakanmusuh;
    bool firemagic = false;
    int waktuterbakar = 0;
    bool gunakanspirit = false;
    cout << "Anda bertemu dengan Chimera" << endl;
    do {
        cout << "1. Serang \n2. Serang dengan sihir api (100 MP)\n3. Gunakan Skill\n4. Gunakan Spirit\n5. Gunakan Potion\n0. Lari!" << endl;
        cout << "Spirit : " << kzl.herospirit.size() << endl;
        cin >> x;
        if (x == 1) {
            int randomeva = rand() % 101;
            if (randomeva <= evasionsementara) {
                cout << "Anda menghindari serangan lawan dan menyerangnya" << endl;
                kzl.serang(attsementara, musuh1.health, musuh1.defense, gunakanspirit);
                cout << "Health Musuh : " << musuh1.health << endl;
                if (firemagic == true && waktuterbakar >= gerakanplayer.size()) {
                    cout << "Musuh terbakar, memberikan damage 20% dari total magic damage" << endl;
                    musuh1.health = musuh1.health - magsementara * 20 / 100;
                    if(musuh1.health < 0) musuh1.health = 0;
                    cout << "Health Musuh : " << musuh1.health << endl;
                } else if (waktuterbakar < gerakanplayer.size()) {
                    firemagic == false;
                }
                cout << "Health Player : " << kzl.health << endl;
            } else {
                kzl.serang(attsementara, musuh1.health, musuh1.defense, gunakanspirit);
                cout << "Health Musuh : " << musuh1.health << endl;
                if (firemagic == true && waktuterbakar >= gerakanplayer.size()) {
                    cout << "Musuh terbakar, memberikan damage 20% dari total magic damage" << endl;
                    musuh1.health = musuh1.health - magsementara * 20 / 100;
                    if(musuh1.health < 0) musuh1.health = 0;
                    cout << "Health Musuh : " << musuh1.health << endl;
                } else if (waktuterbakar < gerakanplayer.size()) {
                    firemagic == false;
                }
                musuh1.serang(musuh1.attack, kzl.health, kzl.defense);
                cout << "Health Player : " << kzl.health << endl;
            }
            attsementara = kzl.attack;
            gunakanspirit = false;
            evasionsementara = kzl.evasion;
            gerakanplayer.push(1);
            gerakanmusuh.push(1);
        }
        else if (x == 4) {
            gunakanspirit = kzl.gunakanspirit(attsementara);
        }
        else if (x == 2) {
            if (kzl.magicpoint >= 100) {
                int randomeva = rand() % 101;
                if (randomeva <= evasionsementara) {
                    cout << "Anda menghindari serangan lawan dan menyerangnya" << endl;
                    firemagic = kzl.serangdengansihirapi(magsementara, musuh1.health, musuh1.defense, gunakanspirit);
                    waktuterbakar = gerakanplayer.size() + 3;
                    cout << "Health Musuh : " << musuh1.health << endl;
                    cout << "Health Player : " << kzl.health << endl;
                } else {
                    firemagic = kzl.serangdengansihirapi(magsementara, musuh1.health, musuh1.defense, gunakanspirit);
                    waktuterbakar = gerakanplayer.size() + 3;
                    cout << "Health Musuh : " << musuh1.health << endl;
                    musuh1.serang(musuh1.attack, kzl.health, kzl.defense);
                    cout << "Health Player : " << kzl.health << endl;
                }
                kzl.magicpoint = kzl.magicpoint - 50;
                cout << "MP Tersisa : " << kzl.magicpoint << endl;
                magsementara = kzl.magicdamage;
                gunakanspirit = false;
                evasionsementara = kzl.evasion;
            }
            else {
                cout << "You dont have enough MP" << endl;
            }
        }
        else if (x == 3) {
            cout << "===== Daftar Skills yang Terbuka =====" << endl;
            vector<treeskills*> skillList = {
                root1, child1, child2, child1_1, child1_2, child2_1, child2_2,
                root2, magchild1, magchild2, magchild1_1, magchild1_2, magchild2_1, magchild2_2
            };
            vector<string> skillNames;
            for (auto skill : skillList) {
                if (skill->unlocked) {
                    cout << "- " << skill->name << endl;
                    skillNames.push_back(skill->name);
                }
            }
            if (!skillNames.empty()) {
                cout << "Pilih skill untuk digunakan: ";
                string pilih;
                cin.ignore();
                getline(cin, pilih);
                int biayaMP = 0;
                bool skillBerhasil = false;
                if (pilih == "Sword Aura") {
                    biayaMP = 50;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Seranganmu diperkuat oleh aura pedang (+20% attack untuk 1 serangan)\n";
                        attsementara += 20*attsementara/100;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Sword God") {
                    biayaMP = 100;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Kekuatan dewa pedang! (+100% attack dan menghindari 1 serangan)\n";
                        attsementara += attsementara;
                        evasionsementara = 100;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Demon Slash") {
                    biayaMP = 200;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Serangan iblis meledak! (Damage x2)\n";
                        attsementara *= 2;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Storm of Heaven") {
                    biayaMP = 230;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Kamu menciptakan badai suci yang melukai musuh\n";
                        musuh1.health -= 500;
                        if (musuh1.health < 0) musuh1.health = 0;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Hero Ultimate") {
                    biayaMP = 1000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Skill pamungkas pahlawan! (+1000% semua atribut)\n";
                        attsementara += attsementara*10;
                        magsementara += magsementara*10;
                        evasionsementara += 100;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Inferno") {
                    biayaMP = 450;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Membakar musuh! Efek terbakar aktif hingga 10 giliran\n";
                        musuh1.health -= 1000;
                        firemagic = true;
                        waktuterbakar = gerakanplayer.size() + 10;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Ice Rain") {
                    biayaMP = 90;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Hujan es memperlambat musuh! Mengurangi defense musuh 50%\n";
                        musuh1.defense = max(0, musuh1.defense - musuh1.defense*50/100);
                        skillBerhasil = true;
                    }
                } else if (pilih == "Dark Void") {
                    biayaMP = 1000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Void kegelapan menyerap jiwa musuh (-2000 HP)\n";
                        musuh1.health -= 2000;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Holy Lance") {
                    biayaMP = 300;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Tombak suci menusuk! +100% magic damage sementara\n";
                        magsementara += magsementara;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Lightning Wrath") {
                    biayaMP = 2000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Petir murka! Musuh kehilangan 50% HP saat ini\n";
                        musuh1.health -= musuh1.health * 50 / 100;
                        if (musuh1.health < 0) musuh1.health = 0;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Iron Maiden") {
                    biayaMP = 10000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Instant Death\n";
                        musuh1.health = 0;
                        skillBerhasil = true;
                    }
                } else {
                    cout << "Skill tidak ditemukan atau belum dibuka!\n";
                }
                if (skillBerhasil) {
                    kzl.magicpoint -= biayaMP;
                    cout << "MP tersisa: " << kzl.magicpoint << endl;
                } else if (biayaMP > 0) {
                    cout << "MP Anda tidak cukup untuk menggunakan skill ini!\n";
                }
            } else {
                cout << "Tidak ada skill yang terbuka\n";
            }
        }else if (x == 5){
            int jadi = 0;
            kzl.displaySortedPotion();
            cout << "1.Cari Potion\n2. Batal\n";
            cin >> jadi;
            if (jadi == 1){
                string name;
                cin.ignore();
                cout << "Masukkan Nama Potion : ";
                getline(cin, name);
                kzl.searchpotion(name);
            }
        }
        else if (x == 0){
            break;
        }
    } while (musuh1.health > 0 && kzl.health > 0);
    if(musuh1.health == 0) {
        kzl.experience += 18000;
        kzl.levelup();
        int randomitem = rand() % 4;
        switch (randomitem) {
            case 1:
                kzl.insertweapon(new weapon("Chimera Claw", 6000, 1200, false));
                cout << "Anda Mendapatkan Senjata : Chimera Claw" << endl; 
                break;
            case 2:
                kzl.insertarmor(new armor("Chimeric Hide", 8000, 2000, false));
                cout << "Anda Mendapatkan Armor : Chimeric Hide" << endl; 
                break;
            case 3:
                kzl.insertpotion(new potion("Hyper Health Potion", 8000, 2000));
                cout << "Anda Mendapatkan Potion : Hyper Health Potion" << endl; 
                break;
            default:
                break;
        }
    }
}
void serangUndead() {
    int x = 0;
    musuh musuh1(12000, 1800, 1000, 0);
    int healthmusuhawal = musuh1.health;
    int attsementara = kzl.attack;
    int magsementara = kzl.magicdamage;
    int evasionsementara = kzl.evasion;
    stack<int> gerakanplayer;
    stack<int> gerakanmusuh;
    bool firemagic = false;
    int waktuterbakar = 0;
    bool gunakanspirit = false;
    cout << "Anda bertemu dengan Undead King" << endl;
    do {
        cout << "1. Serang \n2. Serang dengan sihir api (100 MP)\n3. Gunakan Skill\n4. Gunakan Spirit\n5. Gunakan Potion\n0. Lari!" << endl;
        cout << "Spirit : " << kzl.herospirit.size() << endl;
        cin >> x;
        if (x == 1) {
            int randomeva = rand() % 101;
            if (randomeva <= evasionsementara) {
                cout << "Anda menghindari serangan lawan dan menyerangnya" << endl;
                kzl.serang(attsementara, musuh1.health, musuh1.defense, gunakanspirit);
                cout << "Health Musuh : " << musuh1.health << endl;
                if (firemagic == true && waktuterbakar >= gerakanplayer.size()) {
                    cout << "Musuh terbakar, memberikan damage 20% dari total magic damage" << endl;
                    musuh1.health = musuh1.health - magsementara * 20 / 100;
                    if(musuh1.health < 0) musuh1.health = 0;
                    cout << "Health Musuh : " << musuh1.health << endl;
                } else if (waktuterbakar < gerakanplayer.size()) {
                    firemagic == false;
                }
                cout << "Health Player : " << kzl.health << endl;
            } else {
                kzl.serang(attsementara, musuh1.health, musuh1.defense, gunakanspirit);
                cout << "Health Musuh : " << musuh1.health << endl;
                if (firemagic == true && waktuterbakar >= gerakanplayer.size()) {
                    cout << "Musuh terbakar, memberikan damage 20% dari total magic damage" << endl;
                    musuh1.health = musuh1.health - magsementara * 20 / 100;
                    if(musuh1.health < 0) musuh1.health = 0;
                    cout << "Health Musuh : " << musuh1.health << endl;
                } else if (waktuterbakar < gerakanplayer.size()) {
                    firemagic == false;
                }
                musuh1.serang(musuh1.attack, kzl.health, kzl.defense);
                cout << "Health Player : " << kzl.health << endl;
            }
            attsementara = kzl.attack;
            gunakanspirit = false;
            evasionsementara = kzl.evasion;
            gerakanplayer.push(1);
            gerakanmusuh.push(1);
        }
        else if (x == 4) {
            gunakanspirit = kzl.gunakanspirit(attsementara);
        }
        else if (x == 2) {
            if (kzl.magicpoint >= 100) {
                int randomeva = rand() % 101;
                if (randomeva <= evasionsementara) {
                    cout << "Anda menghindari serangan lawan dan menyerangnya" << endl;
                    firemagic = kzl.serangdengansihirapi(magsementara, musuh1.health, musuh1.defense, gunakanspirit);
                    waktuterbakar = gerakanplayer.size() + 3;
                    cout << "Health Musuh : " << musuh1.health << endl;
                    cout << "Health Player : " << kzl.health << endl;
                } else {
                    firemagic = kzl.serangdengansihirapi(magsementara, musuh1.health, musuh1.defense, gunakanspirit);
                    waktuterbakar = gerakanplayer.size() + 3;
                    cout << "Health Musuh : " << musuh1.health << endl;
                    musuh1.serang(musuh1.attack, kzl.health, kzl.defense);
                    cout << "Health Player : " << kzl.health << endl;
                }
                kzl.magicpoint = kzl.magicpoint - 50;
                cout << "MP Tersisa : " << kzl.magicpoint << endl;
                magsementara = kzl.magicdamage;
                gunakanspirit = false;
                evasionsementara = kzl.evasion;
            }
            else {
                cout << "You dont have enough MP" << endl;
            }
        }
        else if (x == 3) {
            cout << "===== Daftar Skills yang Terbuka =====" << endl;
            vector<treeskills*> skillList = {
                root1, child1, child2, child1_1, child1_2, child2_1, child2_2,
                root2, magchild1, magchild2, magchild1_1, magchild1_2, magchild2_1, magchild2_2
            };
            vector<string> skillNames;
            for (auto skill : skillList) {
                if (skill->unlocked) {
                    cout << "- " << skill->name << endl;
                    skillNames.push_back(skill->name);
                }
            }
            if (!skillNames.empty()) {
                cout << "Pilih skill untuk digunakan: ";
                string pilih;
                cin.ignore();
                getline(cin, pilih);
                int biayaMP = 0;
                bool skillBerhasil = false;
                if (pilih == "Sword Aura") {
                    biayaMP = 50;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Seranganmu diperkuat oleh aura pedang (+20% attack untuk 1 serangan)\n";
                        attsementara += 20*attsementara/100;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Sword God") {
                    biayaMP = 100;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Kekuatan dewa pedang! (+100% attack dan menghindari 1 serangan)\n";
                        attsementara += attsementara;
                        evasionsementara = 100;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Demon Slash") {
                    biayaMP = 200;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Serangan iblis meledak! (Damage x2)\n";
                        attsementara *= 2;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Storm of Heaven") {
                    biayaMP = 230;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Kamu menciptakan badai suci yang melukai musuh\n";
                        musuh1.health -= 500;
                        if (musuh1.health < 0) musuh1.health = 0;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Hero Ultimate") {
                    biayaMP = 1000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Skill pamungkas pahlawan! (+1000% semua atribut)\n";
                        attsementara += attsementara*10;
                        magsementara += magsementara*10;
                        evasionsementara += 100;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Inferno") {
                    biayaMP = 450;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Membakar musuh! Efek terbakar aktif hingga 10 giliran\n";
                        musuh1.health -= 1000;
                        firemagic = true;
                        waktuterbakar = gerakanplayer.size() + 10;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Ice Rain") {
                    biayaMP = 90;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Hujan es memperlambat musuh! Mengurangi defense musuh 50%\n";
                        musuh1.defense = max(0, musuh1.defense - musuh1.defense*50/100);
                        skillBerhasil = true;
                    }
                } else if (pilih == "Dark Void") {
                    biayaMP = 1000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Void kegelapan menyerap jiwa musuh (-2000 HP)\n";
                        musuh1.health -= 2000;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Holy Lance") {
                    biayaMP = 300;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Tombak suci menusuk! +100% magic damage sementara\n";
                        magsementara += magsementara;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Lightning Wrath") {
                    biayaMP = 2000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Petir murka! Musuh kehilangan 50% HP saat ini\n";
                        musuh1.health -= musuh1.health * 50 / 100;
                        if (musuh1.health < 0) musuh1.health = 0;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Iron Maiden") {
                    biayaMP = 10000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Instant Death\n";
                        musuh1.health = 0;
                        skillBerhasil = true;
                    }
                } else {
                    cout << "Skill tidak ditemukan atau belum dibuka!\n";
                }
                if (skillBerhasil) {
                    kzl.magicpoint -= biayaMP;
                    cout << "MP tersisa: " << kzl.magicpoint << endl;
                } else if (biayaMP > 0) {
                    cout << "MP Anda tidak cukup untuk menggunakan skill ini!\n";
                }
            } else {
                cout << "Tidak ada skill yang terbuka\n";
            }
        }else if (x == 5){
            int jadi = 0;
            kzl.displaySortedPotion();
            cout << "1.Cari Potion\n2. Batal\n";
            cin >> jadi;
            if (jadi == 1){
                string name;
                cin.ignore();
                cout << "Masukkan Nama Potion : ";
                getline(cin, name);
                kzl.searchpotion(name);
            }
        }
        else if (x == 0){
            break;
        }
    } while (musuh1.health > 0 && kzl.health > 0);
    if(musuh1.health == 0) {
        kzl.experience += 10000;
        kzl.levelup();
        int randomitem = rand() % 4;
        switch (randomitem) {
            case 1:
                kzl.insertweapon(new weapon("Bone Sword", 3500, 700, false));
                cout << "Anda Mendapatkan Senjata : Bone Sword" << endl; 
                break;
            case 2:
                kzl.insertarmor(new armor("Ghost Armor", 4000, 1000, false));
                cout << "Anda Mendapatkan Armor : Ghost Armor" << endl; 
                break;
            case 3:
                kzl.insertpotion(new potion("Elixir of Undeath", 4000, 1000));
                cout << "Anda Mendapatkan Potion : Elixir of Undeath" << endl; 
                break;
            default:
                break;
        }
    }
}
void serangDemon() {
    int x = 0;
    musuh musuh1(25000, 4000, 2500, 0);
    int healthmusuhawal = musuh1.health;
    int attsementara = kzl.attack;
    int magsementara = kzl.magicdamage;
    int evasionsementara = kzl.evasion;
    stack<int> gerakanplayer;
    stack<int> gerakanmusuh;
    bool firemagic = false;
    int waktuterbakar = 0;
    bool gunakanspirit = false;
    cout << "Anda bertemu dengan Demon" << endl;
    do {
        cout << "1. Serang \n2. Serang dengan sihir api (100 MP)\n3. Gunakan Skill\n4. Gunakan Spirit\n5. Gunakan Potion\n0. Lari!" << endl;
        cout << "Spirit : " << kzl.herospirit.size() << endl;
        cin >> x;
        if (x == 1) {
            int randomeva = rand() % 101;
            if (randomeva <= evasionsementara) {
                cout << "Anda menghindari serangan lawan dan menyerangnya" << endl;
                kzl.serang(attsementara, musuh1.health, musuh1.defense, gunakanspirit);
                cout << "Health Musuh : " << musuh1.health << endl;
                if (firemagic == true && waktuterbakar >= gerakanplayer.size()) {
                    cout << "Musuh terbakar, memberikan damage 20% dari total magic damage" << endl;
                    musuh1.health = musuh1.health - magsementara * 20 / 100;
                    if(musuh1.health < 0) musuh1.health = 0;
                    cout << "Health Musuh : " << musuh1.health << endl;
                } else if (waktuterbakar < gerakanplayer.size()) {
                    firemagic == false;
                }
                cout << "Health Player : " << kzl.health << endl;
            } else {
                kzl.serang(attsementara, musuh1.health, musuh1.defense, gunakanspirit);
                cout << "Health Musuh : " << musuh1.health << endl;
                if (firemagic == true && waktuterbakar >= gerakanplayer.size()) {
                    cout << "Musuh terbakar, memberikan damage 20% dari total magic damage" << endl;
                    musuh1.health = musuh1.health - magsementara * 20 / 100;
                    if(musuh1.health < 0) musuh1.health = 0;
                    cout << "Health Musuh : " << musuh1.health << endl;
                } else if (waktuterbakar < gerakanplayer.size()) {
                    firemagic == false;
                }
                musuh1.serang(musuh1.attack, kzl.health, kzl.defense);
                cout << "Health Player : " << kzl.health << endl;
            }
            attsementara = kzl.attack;
            gunakanspirit = false;
            evasionsementara = kzl.evasion;
            gerakanplayer.push(1);
            gerakanmusuh.push(1);
        }
        else if (x == 4) {
            gunakanspirit = kzl.gunakanspirit(attsementara);
        }
        else if (x == 2) {
            if (kzl.magicpoint >= 100) {
                int randomeva = rand() % 101;
                if (randomeva <= evasionsementara) {
                    cout << "Anda menghindari serangan lawan dan menyerangnya" << endl;
                    firemagic = kzl.serangdengansihirapi(magsementara, musuh1.health, musuh1.defense, gunakanspirit);
                    waktuterbakar = gerakanplayer.size() + 3;
                    cout << "Health Musuh : " << musuh1.health << endl;
                    cout << "Health Player : " << kzl.health << endl;
                } else {
                    firemagic = kzl.serangdengansihirapi(magsementara, musuh1.health, musuh1.defense, gunakanspirit);
                    waktuterbakar = gerakanplayer.size() + 3;
                    cout << "Health Musuh : " << musuh1.health << endl;
                    musuh1.serang(musuh1.attack, kzl.health, kzl.defense);
                    cout << "Health Player : " << kzl.health << endl;
                }
                kzl.magicpoint = kzl.magicpoint - 50;
                cout << "MP Tersisa : " << kzl.magicpoint << endl;
                magsementara = kzl.magicdamage;
                gunakanspirit = false;
                evasionsementara = kzl.evasion;
            }
            else {
                cout << "You dont have enough MP" << endl;
            }
        }
        else if (x == 3) {
            cout << "===== Daftar Skills yang Terbuka =====" << endl;
            vector<treeskills*> skillList = {
                root1, child1, child2, child1_1, child1_2, child2_1, child2_2,
                root2, magchild1, magchild2, magchild1_1, magchild1_2, magchild2_1, magchild2_2
            };
            vector<string> skillNames;
            for (auto skill : skillList) {
                if (skill->unlocked) {
                    cout << "- " << skill->name << endl;
                    skillNames.push_back(skill->name);
                }
            }
            if (!skillNames.empty()) {
                cout << "Pilih skill untuk digunakan: ";
                string pilih;
                cin.ignore();
                getline(cin, pilih);
                int biayaMP = 0;
                bool skillBerhasil = false;
                if (pilih == "Sword Aura") {
                    biayaMP = 50;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Seranganmu diperkuat oleh aura pedang (+20% attack untuk 1 serangan)\n";
                        attsementara += 20*attsementara/100;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Sword God") {
                    biayaMP = 100;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Kekuatan dewa pedang! (+100% attack dan menghindari 1 serangan)\n";
                        attsementara += attsementara;
                        evasionsementara = 100;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Demon Slash") {
                    biayaMP = 200;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Serangan iblis meledak! (Damage x2)\n";
                        attsementara *= 2;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Storm of Heaven") {
                    biayaMP = 230;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Kamu menciptakan badai suci yang melukai musuh\n";
                        musuh1.health -= 500;
                        if (musuh1.health < 0) musuh1.health = 0;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Hero Ultimate") {
                    biayaMP = 1000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Skill pamungkas pahlawan! (+1000% semua atribut)\n";
                        attsementara += attsementara*10;
                        magsementara += magsementara*10;
                        evasionsementara += 100;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Inferno") {
                    biayaMP = 450;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Membakar musuh! Efek terbakar aktif hingga 10 giliran\n";
                        musuh1.health -= 1000;
                        firemagic = true;
                        waktuterbakar = gerakanplayer.size() + 10;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Ice Rain") {
                    biayaMP = 90;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Hujan es memperlambat musuh! Mengurangi defense musuh 50%\n";
                        musuh1.defense = max(0, musuh1.defense - musuh1.defense*50/100);
                        skillBerhasil = true;
                    }
                } else if (pilih == "Dark Void") {
                    biayaMP = 1000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Void kegelapan menyerap jiwa musuh (-2000 HP)\n";
                        musuh1.health -= 2000;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Holy Lance") {
                    biayaMP = 300;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Tombak suci menusuk! +100% magic damage sementara\n";
                        magsementara += magsementara;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Lightning Wrath") {
                    biayaMP = 2000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Petir murka! Musuh kehilangan 50% HP saat ini\n";
                        musuh1.health -= musuh1.health * 50 / 100;
                        if (musuh1.health < 0) musuh1.health = 0;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Iron Maiden") {
                    biayaMP = 10000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Instant Death\n";
                        musuh1.health = 0;
                        skillBerhasil = true;
                    }
                } else {
                    cout << "Skill tidak ditemukan atau belum dibuka!\n";
                }
                if (skillBerhasil) {
                    kzl.magicpoint -= biayaMP;
                    cout << "MP tersisa: " << kzl.magicpoint << endl;
                } else if (biayaMP > 0) {
                    cout << "MP Anda tidak cukup untuk menggunakan skill ini!\n";
                }
            } else {
                cout << "Tidak ada skill yang terbuka\n";
            }
        }else if (x == 5){
            int jadi = 0;
            kzl.displaySortedPotion();
            cout << "1.Cari Potion\n2. Batal\n";
            cin >> jadi;
            if (jadi == 1){
                string name;
                cin.ignore();
                cout << "Masukkan Nama Potion : ";
                getline(cin, name);
                kzl.searchpotion(name);
            }
        }
        else if (x == 0){
            break;
        }
    } while (musuh1.health > 0 && kzl.health > 0);
    if(musuh1.health == 0) {
        kzl.experience += 20000;
        kzl.levelup();
        int randomitem = rand() % 4;
        switch (randomitem) {
            case 1:
                kzl.insertweapon(new weapon("Demon Blade", 8000, 1500, false));
                cout << "Anda Mendapatkan Senjata : Demon Blade" << endl; 
                break;
            case 2:
                kzl.insertarmor(new armor("Infernal Plate", 10000, 2500, false));
                cout << "Anda Mendapatkan Armor : Infernal Plate" << endl; 
                break;
            case 3:
                kzl.insertpotion(new potion("Demon Blood Elixir", 10000, 2500));
                cout << "Anda Mendapatkan Potion : Demon Blood Elixir" << endl; 
                break;
            default:
                break;
        }
    }
}


void serangDemondenganArdelia() {
    int x = 0;
    musuh musuh1(10000, 4000, 2500, 0);
    int healthmusuhawal = musuh1.health;
    int attsementara = kzl.attack;
    int magsementara = kzl.magicdamage;
    int evasionsementara = kzl.evasion;
    stack<int> gerakanplayer;
    stack<int> gerakanmusuh;
    bool firemagic = false;
    int waktuterbakar = 0;
    bool gunakanspirit = false;
    cout << "Anda bertemu dengan Demon" << endl;
    do {
        cout << "1. Serang \n2. Serang dengan sihir api (100 MP)\n3. Gunakan Skill\n4. Gunakan Spirit\n5. Gunakan Potion" << endl;
        cout << "Spirit : " << kzl.herospirit.size() << endl;
        cin >> x;
        if (x == 1) {
            int randomeva = rand() % 101;
            if (randomeva <= evasionsementara) {
                cout << "Anda menghindari serangan lawan dan menyerangnya" << endl;
                kzl.serang(attsementara, musuh1.health, musuh1.defense, gunakanspirit);
                cout << "Ardelia Memberikan 2000 damage" << endl;
                musuh1.health -= 2000;
                if(musuh1.health < 0) musuh1.health = 0;
                cout << "Health Musuh : " << musuh1.health << endl;
                if (firemagic == true && waktuterbakar >= gerakanplayer.size()) {
                    cout << "Musuh terbakar, memberikan damage 20% dari total magic damage" << endl;
                    musuh1.health = musuh1.health - magsementara * 20 / 100;
                    if(musuh1.health < 0) musuh1.health = 0;
                    cout << "Health Musuh : " << musuh1.health << endl;
                } else if (waktuterbakar < gerakanplayer.size()) {
                    firemagic == false;
                }
                cout << "Health Player : " << kzl.health << endl;
            } else {
                kzl.serang(attsementara, musuh1.health, musuh1.defense, gunakanspirit);
                cout << "Ardelia Memberikan 2000 damage" << endl;
                musuh1.health -= 2000;
                if(musuh1.health < 0) musuh1.health = 0;
                cout << "Health Musuh : " << musuh1.health << endl;
                if (firemagic == true && waktuterbakar >= gerakanplayer.size()) {
                    cout << "Musuh terbakar, memberikan damage 20% dari total magic damage" << endl;
                    musuh1.health = musuh1.health - magsementara * 20 / 100;
                    if(musuh1.health < 0) musuh1.health = 0;
                    cout << "Health Musuh : " << musuh1.health << endl;
                } else if (waktuterbakar < gerakanplayer.size()) {
                    firemagic == false;
                }
                musuh1.serang(musuh1.attack, kzl.health, kzl.defense);
                cout << "Health Player : " << kzl.health << endl;
            }
            attsementara = kzl.attack;
            gunakanspirit = false;
            evasionsementara = kzl.evasion;
            gerakanplayer.push(1);
            gerakanmusuh.push(1);
        }
        else if (x == 4) {
            gunakanspirit = kzl.gunakanspirit(attsementara);
        }
        else if (x == 2) {
            if (kzl.magicpoint >= 100) {
                int randomeva = rand() % 101;
                if (randomeva <= evasionsementara) {
                    cout << "Anda menghindari serangan lawan dan menyerangnya" << endl;
                    firemagic = kzl.serangdengansihirapi(magsementara, musuh1.health, musuh1.defense, gunakanspirit);
                    waktuterbakar = gerakanplayer.size() + 3;
                    cout << "Ardelia Memberikan 2000 damage" << endl;
                    musuh1.health -= 2000;
                    if(musuh1.health < 0) musuh1.health = 0;
                    cout << "Health Musuh : " << musuh1.health << endl;
                    cout << "Health Player : " << kzl.health << endl;
                } else {
                    firemagic = kzl.serangdengansihirapi(magsementara, musuh1.health, musuh1.defense, gunakanspirit);
                    waktuterbakar = gerakanplayer.size() + 3;
                    cout << "Ardelia Memberikan 2000 damage" << endl;
                    musuh1.health -= 2000;
                    if(musuh1.health < 0) musuh1.health = 0;
                    cout << "Health Musuh : " << musuh1.health << endl;
                    musuh1.serang(musuh1.attack, kzl.health, kzl.defense);
                    cout << "Health Player : " << kzl.health << endl;
                }
                kzl.magicpoint = kzl.magicpoint - 50;
                cout << "MP Tersisa : " << kzl.magicpoint << endl;
                magsementara = kzl.magicdamage;
                gunakanspirit = false;
                evasionsementara = kzl.evasion;
            }
            else {
                cout << "You dont have enough MP" << endl;
            }
        }
        else if (x == 3) {
            cout << "===== Daftar Skills yang Terbuka =====" << endl;
            vector<treeskills*> skillList = {
                root1, child1, child2, child1_1, child1_2, child2_1, child2_2,
                root2, magchild1, magchild2, magchild1_1, magchild1_2, magchild2_1, magchild2_2
            };
            vector<string> skillNames;
            for (auto skill : skillList) {
                if (skill->unlocked) {
                    cout << "- " << skill->name << endl;
                    skillNames.push_back(skill->name);
                }
            }
            if (!skillNames.empty()) {
                cout << "Pilih skill untuk digunakan: ";
                string pilih;
                cin.ignore();
                getline(cin, pilih);
                int biayaMP = 0;
                bool skillBerhasil = false;
                if (pilih == "Sword Aura") {
                    biayaMP = 50;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Seranganmu diperkuat oleh aura pedang (+20% attack untuk 1 serangan)\n";
                        attsementara += 20*attsementara/100;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Sword God") {
                    biayaMP = 100;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Kekuatan dewa pedang! (+100% attack dan menghindari 1 serangan)\n";
                        attsementara += attsementara;
                        evasionsementara = 100;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Demon Slash") {
                    biayaMP = 200;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Serangan iblis meledak! (Damage x2)\n";
                        attsementara *= 2;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Storm of Heaven") {
                    biayaMP = 230;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Kamu menciptakan badai suci yang melukai musuh\n";
                        musuh1.health -= 500;
                        if (musuh1.health < 0) musuh1.health = 0;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Hero Ultimate") {
                    biayaMP = 1000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Skill pamungkas pahlawan! (+1000% semua atribut)\n";
                        attsementara += attsementara*10;
                        magsementara += magsementara*10;
                        evasionsementara += 100;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Inferno") {
                    biayaMP = 450;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Membakar musuh! Efek terbakar aktif hingga 10 giliran\n";
                        musuh1.health -= 1000;
                        firemagic = true;
                        waktuterbakar = gerakanplayer.size() + 10;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Ice Rain") {
                    biayaMP = 90;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Hujan es memperlambat musuh! Mengurangi defense musuh 50%\n";
                        musuh1.defense = max(0, musuh1.defense - musuh1.defense*50/100);
                        skillBerhasil = true;
                    }
                } else if (pilih == "Dark Void") {
                    biayaMP = 1000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Void kegelapan menyerap jiwa musuh (-2000 HP)\n";
                        musuh1.health -= 2000;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Holy Lance") {
                    biayaMP = 300;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Tombak suci menusuk! +100% magic damage sementara\n";
                        magsementara += magsementara;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Lightning Wrath") {
                    biayaMP = 2000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Petir murka! Musuh kehilangan 50% HP saat ini\n";
                        musuh1.health -= musuh1.health * 50 / 100;
                        if (musuh1.health < 0) musuh1.health = 0;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Iron Maiden") {
                    biayaMP = 10000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Instant Death\n";
                        musuh1.health = 0;
                        skillBerhasil = true;
                    }
                } else {
                    cout << "Skill tidak ditemukan atau belum dibuka!\n";
                }
                if (skillBerhasil) {
                    kzl.magicpoint -= biayaMP;
                    cout << "MP tersisa: " << kzl.magicpoint << endl;
                } else if (biayaMP > 0) {
                    cout << "MP Anda tidak cukup untuk menggunakan skill ini!\n";
                }
            } else {
                cout << "Tidak ada skill yang terbuka\n";
            }
        }else if (x == 5){
            int jadi = 0;
            kzl.displaySortedPotion();
            cout << "1.Cari Potion\n2. Batal\n";
            cin >> jadi;
            if (jadi == 1){
                string name;
                cin.ignore();
                cout << "Masukkan Nama Potion : ";
                getline(cin, name);
                kzl.searchpotion(name);
            }
        }
        else if (x == 0){
            cout << "Meninggalkan Ardelia Sendirian\n";
            kzl.health = 0;
            cout << "Game Over";
            break;
        }
    } while (musuh1.health > 0 && kzl.health > 0);
    if(musuh1.health == 0) {
        kzl.experience += 20000;
        kzl.levelup();
        int randomitem = rand() % 4;
        switch (randomitem) {
            case 1:
                kzl.insertweapon(new weapon("Demon Blade", 5000, 1500, false));
                cout << "Anda Mendapatkan Senjata : Demon Blade" << endl; 
                break;
            case 2:
                kzl.insertarmor(new armor("Infernal Plate", 7000, 2500, false));
                cout << "Anda Mendapatkan Armor : Infernal Plate" << endl; 
                break;
            case 3:
                kzl.insertpotion(new potion("Demon Blood Elixir", 10000, 2500));
                cout << "Anda Mendapatkan Potion : Demon Blood Elixir" << endl; 
                break;
            default:
                break;
        }
    }
}

void serangBehemothdenganArdelia() {
    int x = 0;
    musuh musuh1(20000, 5000, 3000, 0);
    int healthmusuhawal = musuh1.health;
    int attsementara = kzl.attack;
    int magsementara = kzl.magicdamage;
    int evasionsementara = kzl.evasion;
    stack<int> gerakanplayer;
    stack<int> gerakanmusuh;
    bool firemagic = false;
    int waktuterbakar = 0;
    bool gunakanspirit = false;
    cout << "Anda bertemu dengan Behemoth" << endl;
    do {
        cout << "1. Serang \n2. Serang dengan sihir api (100 MP)\n3. Gunakan Skill\n4. Gunakan Spirit\n5. Gunakan Potion" << endl;
        cout << "Spirit : " << kzl.herospirit.size() << endl;
        cin >> x;
        if (x == 1) {
            int randomeva = rand() % 101;
            if (randomeva <= evasionsementara) {
                cout << "Anda menghindari serangan lawan dan menyerangnya" << endl;
                kzl.serang(attsementara, musuh1.health, musuh1.defense, gunakanspirit);
                cout << "Ardelia Memberikan 2000 damage" << endl;
                musuh1.health -= 2000;
                if(musuh1.health < 0) musuh1.health = 0;
                cout << "Health Musuh : " << musuh1.health << endl;
                if (firemagic == true && waktuterbakar >= gerakanplayer.size()) {
                    cout << "Musuh terbakar, memberikan damage 20% dari total magic damage" << endl;
                    musuh1.health = musuh1.health - magsementara * 20 / 100;
                    if(musuh1.health < 0) musuh1.health = 0;
                    cout << "Health Musuh : " << musuh1.health << endl;
                } else if (waktuterbakar < gerakanplayer.size()) {
                    firemagic == false;
                }
                cout << "Health Player : " << kzl.health << endl;
            } else {
                kzl.serang(attsementara, musuh1.health, musuh1.defense, gunakanspirit);
                cout << "Ardelia Memberikan 2000 damage" << endl;
                musuh1.health -= 2000;
                if(musuh1.health < 0) musuh1.health = 0;
                cout << "Health Musuh : " << musuh1.health << endl;
                if (firemagic == true && waktuterbakar >= gerakanplayer.size()) {
                    cout << "Musuh terbakar, memberikan damage 20% dari total magic damage" << endl;
                    musuh1.health = musuh1.health - magsementara * 20 / 100;
                    if(musuh1.health < 0) musuh1.health = 0;
                    cout << "Health Musuh : " << musuh1.health << endl;
                } else if (waktuterbakar < gerakanplayer.size()) {
                    firemagic == false;
                }
                musuh1.serang(musuh1.attack, kzl.health, kzl.defense);
                cout << "Health Player : " << kzl.health << endl;
            }
            attsementara = kzl.attack;
            gunakanspirit = false;
            evasionsementara = kzl.evasion;
            gerakanplayer.push(1);
            gerakanmusuh.push(1);
        }
        else if (x == 4) {
            gunakanspirit = kzl.gunakanspirit(attsementara);
        }
        else if (x == 2) {
            if (kzl.magicpoint >= 100) {
                int randomeva = rand() % 101;
                if (randomeva <= evasionsementara) {
                    cout << "Anda menghindari serangan lawan dan menyerangnya" << endl;
                    firemagic = kzl.serangdengansihirapi(magsementara, musuh1.health, musuh1.defense, gunakanspirit);
                    waktuterbakar = gerakanplayer.size() + 3;
                    cout << "Ardelia Memberikan 2000 damage" << endl;
                    musuh1.health -= 2000;
                    if(musuh1.health < 0) musuh1.health = 0;
                    cout << "Health Musuh : " << musuh1.health << endl;
                    cout << "Health Player : " << kzl.health << endl;
                } else {
                    firemagic = kzl.serangdengansihirapi(magsementara, musuh1.health, musuh1.defense, gunakanspirit);
                    waktuterbakar = gerakanplayer.size() + 3;
                    cout << "Ardelia Memberikan 2000 damage" << endl;
                    musuh1.health -= 2000;
                    if(musuh1.health < 0) musuh1.health = 0;
                    cout << "Health Musuh : " << musuh1.health << endl;
                    musuh1.serang(musuh1.attack, kzl.health, kzl.defense);
                    cout << "Health Player : " << kzl.health << endl;
                }
                kzl.magicpoint = kzl.magicpoint - 50;
                cout << "MP Tersisa : " << kzl.magicpoint << endl;
                magsementara = kzl.magicdamage;
                gunakanspirit = false;
                evasionsementara = kzl.evasion;
            }
            else {
                cout << "You dont have enough MP" << endl;
            }
        }
        else if (x == 3) {
            cout << "===== Daftar Skills yang Terbuka =====" << endl;
            vector<treeskills*> skillList = {
                root1, child1, child2, child1_1, child1_2, child2_1, child2_2,
                root2, magchild1, magchild2, magchild1_1, magchild1_2, magchild2_1, magchild2_2
            };
            vector<string> skillNames;
            for (auto skill : skillList) {
                if (skill->unlocked) {
                    cout << "- " << skill->name << endl;
                    skillNames.push_back(skill->name);
                }
            }
            if (!skillNames.empty()) {
                cout << "Pilih skill untuk digunakan: ";
                string pilih;
                cin.ignore();
                getline(cin, pilih);
                int biayaMP = 0;
                bool skillBerhasil = false;
                if (pilih == "Sword Aura") {
                    biayaMP = 50;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Seranganmu diperkuat oleh aura pedang (+20% attack untuk 1 serangan)\n";
                        attsementara += 20*attsementara/100;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Sword God") {
                    biayaMP = 100;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Kekuatan dewa pedang! (+100% attack dan menghindari 1 serangan)\n";
                        attsementara += attsementara;
                        evasionsementara = 100;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Demon Slash") {
                    biayaMP = 200;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Serangan iblis meledak! (Damage x2)\n";
                        attsementara *= 2;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Storm of Heaven") {
                    biayaMP = 230;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Kamu menciptakan badai suci yang melukai musuh\n";
                        musuh1.health -= 500;
                        if (musuh1.health < 0) musuh1.health = 0;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Hero Ultimate") {
                    biayaMP = 1000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Skill pamungkas pahlawan! (+1000% semua atribut)\n";
                        attsementara += attsementara*10;
                        magsementara += magsementara*10;
                        evasionsementara += 100;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Inferno") {
                    biayaMP = 450;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Membakar musuh! Efek terbakar aktif hingga 10 giliran\n";
                        musuh1.health -= 1000;
                        firemagic = true;
                        waktuterbakar = gerakanplayer.size() + 10;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Ice Rain") {
                    biayaMP = 90;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Hujan es memperlambat musuh! Mengurangi defense musuh 50%\n";
                        musuh1.defense = max(0, musuh1.defense - musuh1.defense*50/100);
                        skillBerhasil = true;
                    }
                } else if (pilih == "Dark Void") {
                    biayaMP = 1000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Void kegelapan menyerap jiwa musuh (-2000 HP)\n";
                        musuh1.health -= 2000;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Holy Lance") {
                    biayaMP = 300;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Tombak suci menusuk! +100% magic damage sementara\n";
                        magsementara += magsementara;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Lightning Wrath") {
                    biayaMP = 2000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Petir murka! Musuh kehilangan 50% HP saat ini\n";
                        musuh1.health -= musuh1.health * 50 / 100;
                        if (musuh1.health < 0) musuh1.health = 0;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Iron Maiden") {
                    biayaMP = 10000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Instant Death\n";
                        musuh1.health = 0;
                        skillBerhasil = true;
                    }
                } else {
                    cout << "Skill tidak ditemukan atau belum dibuka!\n";
                }
                if (skillBerhasil) {
                    kzl.magicpoint -= biayaMP;
                    cout << "MP tersisa: " << kzl.magicpoint << endl;
                } else if (biayaMP > 0) {
                    cout << "MP Anda tidak cukup untuk menggunakan skill ini!\n";
                }
            } else {
                cout << "Tidak ada skill yang terbuka\n";
            }
        }else if (x == 5){
            int jadi = 0;
            kzl.displaySortedPotion();
            cout << "1.Cari Potion\n2. Batal\n";
            cin >> jadi;
            if (jadi == 1){
                string name;
                cin.ignore();
                cout << "Masukkan Nama Potion : ";
                getline(cin, name);
                kzl.searchpotion(name);
            }
        }
        else if (x == 0){
            cout << "Meninggalkan Ardelia Sendirian\n";
            kzl.health = 0;
            cout << "Game Over";
            break;
        }
    } while (musuh1.health > 0 && kzl.health > 0);
    if(musuh1.health == 0) {
        kzl.experience += 20000;
        kzl.levelup();
        int randomitem = rand() % 4;
        switch (randomitem) {
            case 1:
                kzl.insertweapon(new weapon("Demon Blade", 8000, 1500, false));
                cout << "Anda Mendapatkan Senjata : Demon Blade" << endl; 
                break;
            case 2:
                kzl.insertarmor(new armor("Infernal Plate", 10000, 2500, false));
                cout << "Anda Mendapatkan Armor : Infernal Plate" << endl; 
                break;
            case 3:
                kzl.insertpotion(new potion("Demon Blood Elixir", 10000, 2500));
                cout << "Anda Mendapatkan Potion : Demon Blood Elixir" << endl; 
                break;
            default:
                break;
        }
    }
}

void serangBehemoth() {
    int x = 0;
    musuh musuh1(30000, 5000, 3000, 0);
    int healthmusuhawal = musuh1.health;
    int attsementara = kzl.attack;
    int magsementara = kzl.magicdamage;
    int evasionsementara = kzl.evasion;
    stack<int> gerakanplayer;
    stack<int> gerakanmusuh;
    bool firemagic = false;
    int waktuterbakar = 0;
    bool gunakanspirit = false;
    cout << "Anda bertemu dengan Behemoth" << endl;
    do {
        cout << "1. Serang \n2. Serang dengan sihir api (100 MP)\n3. Gunakan Skill\n4. Gunakan Spirit\n5. Gunakan Potion\n0. Lari!" << endl;
        cout << "Spirit : " << kzl.herospirit.size() << endl;
        cin >> x;
        if (x == 1) {
            int randomeva = rand() % 101;
            if (randomeva <= evasionsementara) {
                cout << "Anda menghindari serangan lawan dan menyerangnya" << endl;
                kzl.serang(attsementara, musuh1.health, musuh1.defense, gunakanspirit);
                cout << "Health Musuh : " << musuh1.health << endl;
                if (firemagic == true && waktuterbakar >= gerakanplayer.size()) {
                    cout << "Musuh terbakar, memberikan damage 20% dari total magic damage" << endl;
                    musuh1.health = musuh1.health - magsementara * 20 / 100;
                    if(musuh1.health < 0) musuh1.health = 0;
                    cout << "Health Musuh : " << musuh1.health << endl;
                } else if (waktuterbakar < gerakanplayer.size()) {
                    firemagic == false;
                }
                cout << "Health Player : " << kzl.health << endl;
            } else {
                kzl.serang(attsementara, musuh1.health, musuh1.defense, gunakanspirit);
                cout << "Health Musuh : " << musuh1.health << endl;
                if (firemagic == true && waktuterbakar >= gerakanplayer.size()) {
                    cout << "Musuh terbakar, memberikan damage 20% dari total magic damage" << endl;
                    musuh1.health = musuh1.health - magsementara * 20 / 100;
                    if(musuh1.health < 0) musuh1.health = 0;
                    cout << "Health Musuh : " << musuh1.health << endl;
                } else if (waktuterbakar < gerakanplayer.size()) {
                    firemagic == false;
                }
                musuh1.serang(musuh1.attack, kzl.health, kzl.defense);
                cout << "Health Player : " << kzl.health << endl;
            }
            attsementara = kzl.attack;
            gunakanspirit = false;
            evasionsementara = kzl.evasion;
            gerakanplayer.push(1);
            gerakanmusuh.push(1);
        }
        else if (x == 4) {
            gunakanspirit = kzl.gunakanspirit(attsementara);
        }
        else if (x == 2) {
            if (kzl.magicpoint >= 100) {
                int randomeva = rand() % 101;
                if (randomeva <= evasionsementara) {
                    cout << "Anda menghindari serangan lawan dan menyerangnya" << endl;
                    firemagic = kzl.serangdengansihirapi(magsementara, musuh1.health, musuh1.defense, gunakanspirit);
                    waktuterbakar = gerakanplayer.size() + 3;
                    cout << "Health Musuh : " << musuh1.health << endl;
                    cout << "Health Player : " << kzl.health << endl;
                } else {
                    firemagic = kzl.serangdengansihirapi(magsementara, musuh1.health, musuh1.defense, gunakanspirit);
                    waktuterbakar = gerakanplayer.size() + 3;
                    cout << "Health Musuh : " << musuh1.health << endl;
                    musuh1.serang(musuh1.attack, kzl.health, kzl.defense);
                    cout << "Health Player : " << kzl.health << endl;
                }
                kzl.magicpoint = kzl.magicpoint - 50;
                cout << "MP Tersisa : " << kzl.magicpoint << endl;
                magsementara = kzl.magicdamage;
                gunakanspirit = false;
                evasionsementara = kzl.evasion;
            }
            else {
                cout << "You dont have enough MP" << endl;
            }
        }
        else if (x == 3) {
            cout << "===== Daftar Skills yang Terbuka =====" << endl;
            vector<treeskills*> skillList = {
                root1, child1, child2, child1_1, child1_2, child2_1, child2_2,
                root2, magchild1, magchild2, magchild1_1, magchild1_2, magchild2_1, magchild2_2
            };
            vector<string> skillNames;
            for (auto skill : skillList) {
                if (skill->unlocked) {
                    cout << "- " << skill->name << endl;
                    skillNames.push_back(skill->name);
                }
            }
            if (!skillNames.empty()) {
                cout << "Pilih skill untuk digunakan: ";
                string pilih;
                cin.ignore();
                getline(cin, pilih);
                int biayaMP = 0;
                bool skillBerhasil = false;
                if (pilih == "Sword Aura") {
                    biayaMP = 50;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Seranganmu diperkuat oleh aura pedang (+20% attack untuk 1 serangan)\n";
                        attsementara += 20*attsementara/100;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Sword God") {
                    biayaMP = 100;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Kekuatan dewa pedang! (+100% attack dan menghindari 1 serangan)\n";
                        attsementara += attsementara;
                        evasionsementara = 100;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Demon Slash") {
                    biayaMP = 200;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Serangan iblis meledak! (Damage x2)\n";
                        attsementara *= 2;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Storm of Heaven") {
                    biayaMP = 230;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Kamu menciptakan badai suci yang melukai musuh\n";
                        musuh1.health -= 500;
                        if (musuh1.health < 0) musuh1.health = 0;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Hero Ultimate") {
                    biayaMP = 1000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Skill pamungkas pahlawan! (+1000% semua atribut)\n";
                        attsementara += attsementara*10;
                        magsementara += magsementara*10;
                        evasionsementara += 100;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Inferno") {
                    biayaMP = 450;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Membakar musuh! Efek terbakar aktif hingga 10 giliran\n";
                        musuh1.health -= 1000;
                        firemagic = true;
                        waktuterbakar = gerakanplayer.size() + 10;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Ice Rain") {
                    biayaMP = 90;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Hujan es memperlambat musuh! Mengurangi defense musuh 50%\n";
                        musuh1.defense = max(0, musuh1.defense - musuh1.defense*50/100);
                        skillBerhasil = true;
                    }
                } else if (pilih == "Dark Void") {
                    biayaMP = 1000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Void kegelapan menyerap jiwa musuh (-2000 HP)\n";
                        musuh1.health -= 2000;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Holy Lance") {
                    biayaMP = 300;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Tombak suci menusuk! +100% magic damage sementara\n";
                        magsementara += magsementara;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Lightning Wrath") {
                    biayaMP = 2000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Petir murka! Musuh kehilangan 50% HP saat ini\n";
                        musuh1.health -= musuh1.health * 50 / 100;
                        if (musuh1.health < 0) musuh1.health = 0;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Iron Maiden") {
                    biayaMP = 10000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Instant Death\n";
                        musuh1.health = 0;
                        skillBerhasil = true;
                    }
                } else {
                    cout << "Skill tidak ditemukan atau belum dibuka!\n";
                }
                if (skillBerhasil) {
                    kzl.magicpoint -= biayaMP;
                    cout << "MP tersisa: " << kzl.magicpoint << endl;
                } else if (biayaMP > 0) {
                    cout << "MP Anda tidak cukup untuk menggunakan skill ini!\n";
                }
            } else {
                cout << "Tidak ada skill yang terbuka\n";
            }
        }else if (x == 5){
            int jadi = 0;
            kzl.displaySortedPotion();
            cout << "1.Cari Potion\n2. Batal\n";
            cin >> jadi;
            if (jadi == 1){
                string name;
                cin.ignore();
                cout << "Masukkan Nama Potion : ";
                getline(cin, name);
                kzl.searchpotion(name);
            }
        }
        else if (x == 0){
            break;
        }
    } while (musuh1.health > 0 && kzl.health > 0);
    if(musuh1.health == 0) {
        kzl.experience += 25000;
        kzl.levelup();
        int randomitem = rand() % 4;
        switch (randomitem) {
            case 1:
                kzl.insertweapon(new weapon("Behemoth Fang", 10000, 2000, false));
                cout << "Anda Mendapatkan Senjata : Behemoth Fang" << endl; 
                break;
            case 2:
                kzl.insertarmor(new armor("Behemoth Hide", 12000, 3000, false));
                cout << "Anda Mendapatkan Armor : Behemoth Hide" << endl; 
                break;
            case 3:
                kzl.insertpotion(new potion("Titan's Elixir", 12000, 3000));
                cout << "Anda Mendapatkan Potion : Titan's Elixir" << endl; 
                break;
            default:
                break;
        }
    }
}

void serangGriffin() {
    int x = 0;
    musuh musuh1(18000, 3500, 1800, 0);
    int healthmusuhawal = musuh1.health;
    int attsementara = kzl.attack;
    int magsementara = kzl.magicdamage;
    int evasionsementara = kzl.evasion;
    stack<int> gerakanplayer;
    stack<int> gerakanmusuh;
    bool firemagic = false;
    int waktuterbakar = 0;
    bool gunakanspirit = false;
    cout << "Anda bertemu dengan Griffin" << endl;
    do {
        cout << "1. Serang \n2. Serang dengan sihir api (100 MP)\n3. Gunakan Skill\n4. Gunakan Spirit\n5. Gunakan Potion\n0. Lari!" << endl;
        cout << "Spirit : " << kzl.herospirit.size() << endl;
        cin >> x;
        if (x == 1) {
            int randomeva = rand() % 101;
            if (randomeva <= evasionsementara) {
                cout << "Anda menghindari serangan lawan dan menyerangnya" << endl;
                kzl.serang(attsementara, musuh1.health, musuh1.defense, gunakanspirit);
                cout << "Health Musuh : " << musuh1.health << endl;
                if (firemagic == true && waktuterbakar >= gerakanplayer.size()) {
                    cout << "Musuh terbakar, memberikan damage 20% dari total magic damage" << endl;
                    musuh1.health = musuh1.health - magsementara * 20 / 100;
                    if(musuh1.health < 0) musuh1.health = 0;
                    cout << "Health Musuh : " << musuh1.health << endl;
                } else if (waktuterbakar < gerakanplayer.size()) {
                    firemagic == false;
                }
                cout << "Health Player : " << kzl.health << endl;
            } else {
                kzl.serang(attsementara, musuh1.health, musuh1.defense, gunakanspirit);
                cout << "Health Musuh : " << musuh1.health << endl;
                if (firemagic == true && waktuterbakar >= gerakanplayer.size()) {
                    cout << "Musuh terbakar, memberikan damage 20% dari total magic damage" << endl;
                    musuh1.health = musuh1.health - magsementara * 20 / 100;
                    if(musuh1.health < 0) musuh1.health = 0;
                    cout << "Health Musuh : " << musuh1.health << endl;
                } else if (waktuterbakar < gerakanplayer.size()) {
                    firemagic == false;
                }
                musuh1.serang(musuh1.attack, kzl.health, kzl.defense);
                cout << "Health Player : " << kzl.health << endl;
            }
            attsementara = kzl.attack;
            gunakanspirit = false;
            evasionsementara = kzl.evasion;
            gerakanplayer.push(1);
            gerakanmusuh.push(1);
        }
        else if (x == 4) {
            gunakanspirit = kzl.gunakanspirit(attsementara);
        }
        else if (x == 2) {
            if (kzl.magicpoint >= 100) {
                int randomeva = rand() % 101;
                if (randomeva <= evasionsementara) {
                    cout << "Anda menghindari serangan lawan dan menyerangnya" << endl;
                    firemagic = kzl.serangdengansihirapi(magsementara, musuh1.health, musuh1.defense, gunakanspirit);
                    waktuterbakar = gerakanplayer.size() + 3;
                    cout << "Health Musuh : " << musuh1.health << endl;
                    cout << "Health Player : " << kzl.health << endl;
                } else {
                    firemagic = kzl.serangdengansihirapi(magsementara, musuh1.health, musuh1.defense, gunakanspirit);
                    waktuterbakar = gerakanplayer.size() + 3;
                    cout << "Health Musuh : " << musuh1.health << endl;
                    musuh1.serang(musuh1.attack, kzl.health, kzl.defense);
                    cout << "Health Player : " << kzl.health << endl;
                }
                kzl.magicpoint = kzl.magicpoint - 50;
                cout << "MP Tersisa : " << kzl.magicpoint << endl;
                magsementara = kzl.magicdamage;
                gunakanspirit = false;
                evasionsementara = kzl.evasion;
            }
            else {
                cout << "You dont have enough MP" << endl;
            }
        }
        else if (x == 3) {
            cout << "===== Daftar Skills yang Terbuka =====" << endl;
            vector<treeskills*> skillList = {
                root1, child1, child2, child1_1, child1_2, child2_1, child2_2,
                root2, magchild1, magchild2, magchild1_1, magchild1_2, magchild2_1, magchild2_2
            };
            vector<string> skillNames;
            for (auto skill : skillList) {
                if (skill->unlocked) {
                    cout << "- " << skill->name << endl;
                    skillNames.push_back(skill->name);
                }
            }
            if (!skillNames.empty()) {
                cout << "Pilih skill untuk digunakan: ";
                string pilih;
                cin.ignore();
                getline(cin, pilih);
                int biayaMP = 0;
                bool skillBerhasil = false;
                if (pilih == "Sword Aura") {
                    biayaMP = 50;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Seranganmu diperkuat oleh aura pedang (+20% attack untuk 1 serangan)\n";
                        attsementara += 20*attsementara/100;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Sword God") {
                    biayaMP = 100;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Kekuatan dewa pedang! (+100% attack dan menghindari 1 serangan)\n";
                        attsementara += attsementara;
                        evasionsementara = 100;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Demon Slash") {
                    biayaMP = 200;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Serangan iblis meledak! (Damage x2)\n";
                        attsementara *= 2;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Storm of Heaven") {
                    biayaMP = 230;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Kamu menciptakan badai suci yang melukai musuh\n";
                        musuh1.health -= 500;
                        if (musuh1.health < 0) musuh1.health = 0;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Hero Ultimate") {
                    biayaMP = 1000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Skill pamungkas pahlawan! (+1000% semua atribut)\n";
                        attsementara += attsementara*10;
                        magsementara += magsementara*10;
                        evasionsementara += 100;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Inferno") {
                    biayaMP = 450;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Membakar musuh! Efek terbakar aktif hingga 10 giliran\n";
                        musuh1.health -= 1000;
                        firemagic = true;
                        waktuterbakar = gerakanplayer.size() + 10;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Ice Rain") {
                    biayaMP = 90;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Hujan es memperlambat musuh! Mengurangi defense musuh 50%\n";
                        musuh1.defense = max(0, musuh1.defense - musuh1.defense*50/100);
                        skillBerhasil = true;
                    }
                } else if (pilih == "Dark Void") {
                    biayaMP = 1000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Void kegelapan menyerap jiwa musuh (-2000 HP)\n";
                        musuh1.health -= 2000;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Holy Lance") {
                    biayaMP = 300;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Tombak suci menusuk! +100% magic damage sementara\n";
                        magsementara += magsementara;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Lightning Wrath") {
                    biayaMP = 2000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Petir murka! Musuh kehilangan 50% HP saat ini\n";
                        musuh1.health -= musuh1.health * 50 / 100;
                        if (musuh1.health < 0) musuh1.health = 0;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Iron Maiden") {
                    biayaMP = 10000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Instant Death\n";
                        musuh1.health = 0;
                        skillBerhasil = true;
                    }
                } else {
                    cout << "Skill tidak ditemukan atau belum dibuka!\n";
                }
                if (skillBerhasil) {
                    kzl.magicpoint -= biayaMP;
                    cout << "MP tersisa: " << kzl.magicpoint << endl;
                } else if (biayaMP > 0) {
                    cout << "MP Anda tidak cukup untuk menggunakan skill ini!\n";
                }
            } else {
                cout << "Tidak ada skill yang terbuka\n";
            }
        }else if (x == 5){
            int jadi = 0;
            kzl.displaySortedPotion();
            cout << "1.Cari Potion\n2. Batal\n";
            cin >> jadi;
            if (jadi == 1){
                string name;
                cin.ignore();
                cout << "Masukkan Nama Potion : ";
                getline(cin, name);
                kzl.searchpotion(name);
            }
        }
        else if (x == 0){
            break;
        }
    } while (musuh1.health > 0 && kzl.health > 0);
    if(musuh1.health == 0) {
        kzl.experience += 15000;
        kzl.levelup();
        int randomitem = rand() % 4;
        switch (randomitem) {
            case 1:
                kzl.insertweapon(new weapon("Griffin Talon", 7000, 1400, false));
                cout << "Anda Mendapatkan Senjata : Griffin Talon" << endl; 
                break;
            case 2:
                kzl.insertarmor(new armor("Griffin Feather Cloak", 9000, 1800, false));
                cout << "Anda Mendapatkan Armor : Griffin Feather Cloak" << endl; 
                break;
            case 3:
                kzl.insertpotion(new potion("Sky Elixir", 9000, 1800));
                cout << "Anda Mendapatkan Potion : Sky Elixir" << endl; 
                break;
            default:
                break;
        }
    }
}
void serangBasilisk(){
    int x = 0;
    musuh musuh1(22000, 4500, 2200, 0);
    int healthmusuhawal = musuh1.health;
    int attsementara = kzl.attack;
    int magsementara = kzl.magicdamage;
    int evasionsementara = kzl.evasion;
    stack<int> gerakanplayer;
    stack<int> gerakanmusuh;
    bool firemagic = false;
    int waktuterbakar = 0;
    bool gunakanspirit = false;
    cout << "Anda bertemu dengan Basilisk" << endl;
    do {
        cout << "1. Serang \n2. Serang dengan sihir api (100 MP)\n3. Gunakan Skill\n4. Gunakan Spirit\n5. Gunakan Potion\n0. Lari!" << endl;
        cout << "Spirit : " << kzl.herospirit.size() << endl;
        cin >> x;
        if (x == 1) {
            int randomeva = rand() % 101;
            if (randomeva <= evasionsementara) {
                cout << "Anda menghindari serangan lawan dan menyerangnya" << endl;
                kzl.serang(attsementara, musuh1.health, musuh1.defense, gunakanspirit);
                cout << "Health Musuh : " << musuh1.health << endl;
                if (firemagic == true && waktuterbakar >= gerakanplayer.size()) {
                    cout << "Musuh terbakar, memberikan damage 20% dari total magic damage" << endl;
                    musuh1.health = musuh1.health - magsementara * 20 / 100;
                    if(musuh1.health < 0) musuh1.health = 0;
                    cout << "Health Musuh : " << musuh1.health << endl;
                } else if (waktuterbakar < gerakanplayer.size()) {
                    firemagic == false;
                }
                cout << "Health Player : " << kzl.health << endl;
            } else {
                kzl.serang(attsementara, musuh1.health, musuh1.defense, gunakanspirit);
                cout << "Health Musuh : " << musuh1.health << endl;
                if (firemagic == true && waktuterbakar >= gerakanplayer.size()) {
                    cout << "Musuh terbakar, memberikan damage 20% dari total magic damage" << endl;
                    musuh1.health = musuh1.health - magsementara * 20 / 100;
                    if(musuh1.health < 0) musuh1.health = 0;
                    cout << "Health Musuh : " << musuh1.health << endl;
                } else if (waktuterbakar < gerakanplayer.size()) {
                    firemagic == false;
                }
                musuh1.serang(musuh1.attack, kzl.health, kzl.defense);
                cout << "Health Player : " << kzl.health << endl;
            }
            attsementara = kzl.attack;
            gunakanspirit = false;
            evasionsementara = kzl.evasion;
            gerakanplayer.push(1);
            gerakanmusuh.push(1);
        }
        else if (x == 4) {
            gunakanspirit = kzl.gunakanspirit(attsementara);
        }
        else if (x == 2) {
            if (kzl.magicpoint >= 100) {
                int randomeva = rand() % 101;
                if (randomeva <= evasionsementara) {
                    cout << "Anda menghindari serangan lawan dan menyerangnya" << endl;
                    firemagic = kzl.serangdengansihirapi(magsementara, musuh1.health, musuh1.defense, gunakanspirit);
                    waktuterbakar = gerakanplayer.size() + 3;
                    cout << "Health Musuh : " << musuh1.health << endl;
                    cout << "Health Player : " << kzl.health << endl;
                } else {
                    firemagic = kzl.serangdengansihirapi(magsementara, musuh1.health, musuh1.defense, gunakanspirit);
                    waktuterbakar = gerakanplayer.size() + 3;
                    cout << "Health Musuh : " << musuh1.health << endl;
                    musuh1.serang(musuh1.attack, kzl.health, kzl.defense);
                    cout << "Health Player : " << kzl.health << endl;
                }
                kzl.magicpoint = kzl.magicpoint - 50;
                cout << "MP Tersisa : " << kzl.magicpoint << endl;
                magsementara = kzl.magicdamage;
                gunakanspirit = false;
                evasionsementara = kzl.evasion;
            }
            else {
                cout << "You dont have enough MP" << endl;
            }
        }
        else if (x == 3) {
            cout << "===== Daftar Skills yang Terbuka =====" << endl;
            vector<treeskills*> skillList = {
                root1, child1, child2, child1_1, child1_2, child2_1, child2_2,
                root2, magchild1, magchild2, magchild1_1, magchild1_2, magchild2_1, magchild2_2
            };
            vector<string> skillNames;
            for (auto skill : skillList) {
                if (skill->unlocked) {
                    cout << "- " << skill->name << endl;
                    skillNames.push_back(skill->name);
                }
            }
            if (!skillNames.empty()) {
                cout << "Pilih skill untuk digunakan: ";
                string pilih;
                cin.ignore();
                getline(cin, pilih);
                int biayaMP = 0;
                bool skillBerhasil = false;
                if (pilih == "Sword Aura") {
                    biayaMP = 50;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Seranganmu diperkuat oleh aura pedang (+20% attack untuk 1 serangan)\n";
                        attsementara += 20*attsementara/100;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Sword God") {
                    biayaMP = 100;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Kekuatan dewa pedang! (+100% attack dan menghindari 1 serangan)\n";
                        attsementara += attsementara;
                        evasionsementara = 100;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Demon Slash") {
                    biayaMP = 200;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Serangan iblis meledak! (Damage x2)\n";
                        attsementara *= 2;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Storm of Heaven") {
                    biayaMP = 230;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Kamu menciptakan badai suci yang melukai musuh\n";
                        musuh1.health -= 500;
                        if (musuh1.health < 0) musuh1.health = 0;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Hero Ultimate") {
                    biayaMP = 1000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Skill pamungkas pahlawan! (+1000% semua atribut)\n";
                        attsementara += attsementara*10;
                        magsementara += magsementara*10;
                        evasionsementara += 100;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Inferno") {
                    biayaMP = 450;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Membakar musuh! Efek terbakar aktif hingga 10 giliran\n";
                        musuh1.health -= 1000;
                        firemagic = true;
                        waktuterbakar = gerakanplayer.size() + 10;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Ice Rain") {
                    biayaMP = 90;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Hujan es memperlambat musuh! Mengurangi defense musuh 50%\n";
                        musuh1.defense = max(0, musuh1.defense - musuh1.defense*50/100);
                        skillBerhasil = true;
                    }
                } else if (pilih == "Dark Void") {
                    biayaMP = 1000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Void kegelapan menyerap jiwa musuh (-2000 HP)\n";
                        musuh1.health -= 2000;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Holy Lance") {
                    biayaMP = 300;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Tombak suci menusuk! +100% magic damage sementara\n";
                        magsementara += magsementara;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Lightning Wrath") {
                    biayaMP = 2000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Petir murka! Musuh kehilangan 50% HP saat ini\n";
                        musuh1.health -= musuh1.health * 50 / 100;
                        if (musuh1.health < 0) musuh1.health = 0;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Iron Maiden") {
                    biayaMP = 10000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Instant Death\n";
                        musuh1.health = 0;
                        skillBerhasil = true;
                    }
                } else {
                    cout << "Skill tidak ditemukan atau belum dibuka!\n";
                }
                if (skillBerhasil) {
                    kzl.magicpoint -= biayaMP;
                    cout << "MP tersisa: " << kzl.magicpoint << endl;
                } else if (biayaMP > 0) {
                    cout << "MP Anda tidak cukup untuk menggunakan skill ini!\n";
                }
            } else {
                cout << "Tidak ada skill yang terbuka\n";
            }
        }else if (x == 5){
            int jadi = 0;
            kzl.displaySortedPotion();
            cout << "1.Cari Potion\n2. Batal\n";
            cin >> jadi;
            if (jadi == 1){
                string name;
                cin.ignore();
                cout << "Masukkan Nama Potion : ";
                getline(cin, name);
                kzl.searchpotion(name);
            }
        }
        else if (x == 0){
            break;
        }
    } while (musuh1.health > 0 && kzl.health > 0);
    if(musuh1.health == 0) {
        kzl.experience += 22000;
        kzl.levelup();
        int randomitem = rand() % 4;
        switch (randomitem) {
            case 1:
                kzl.insertweapon(new weapon("Basilisk Fang", 9000, 1800, false));
                cout << "Anda Mendapatkan Senjata : Basilisk Fang" << endl; 
                break;
            case 2:
                kzl.insertarmor(new armor("Basilisk Scale", 11000, 2200, false));
                cout << "Anda Mendapatkan Armor : Basilisk Scale" << endl; 
                break;
            case 3:
                kzl.insertpotion(new potion("Petrification Antidote", 11000, 2200));
                cout << "Anda Mendapatkan Potion : Petrification Antidote" << endl; 
                break;
            default:
                break;
        }
    }
}
void serangSpiritBeast() {
    int x = 0;
    musuh musuh1(28000, 6000, 2800, 0);
    int healthmusuhawal = musuh1.health;
    int attsementara = kzl.attack;
    int magsementara = kzl.magicdamage;
    int evasionsementara = kzl.evasion;
    stack<int> gerakanplayer;
    stack<int> gerakanmusuh;
    bool firemagic = false;
    int waktuterbakar = 0;
    bool gunakanspirit = false;
    cout << "Anda bertemu dengan Spirit Beast" << endl;
    do {
        cout << "1. Serang \n2. Serang dengan sihir api (100 MP)\n3. Gunakan Skill\n4. Gunakan Spirit\n5. Gunakan Potion\n0. Lari!" << endl;
        cout << "Spirit : " << kzl.herospirit.size() << endl;
        cin >> x;
        if (x == 1) {
            int randomeva = rand() % 101;
            if (randomeva <= evasionsementara) {
                cout << "Anda menghindari serangan lawan dan menyerangnya" << endl;
                kzl.serang(attsementara, musuh1.health, musuh1.defense, gunakanspirit);
                cout << "Health Musuh : " << musuh1.health << endl;
                if (firemagic == true && waktuterbakar >= gerakanplayer.size()) {
                    cout << "Musuh terbakar, memberikan damage 20% dari total magic damage" << endl;
                    musuh1.health = musuh1.health - magsementara * 20 / 100;
                    if(musuh1.health < 0) musuh1.health = 0;
                    cout << "Health Musuh : " << musuh1.health << endl;
                } else if (waktuterbakar < gerakanplayer.size()) {
                    firemagic == false;
                }
                cout << "Health Player : " << kzl.health << endl;
            } else {
                kzl.serang(attsementara, musuh1.health, musuh1.defense, gunakanspirit);
                cout << "Health Musuh : " << musuh1.health << endl;
                if (firemagic == true && waktuterbakar >= gerakanplayer.size()) {
                    cout << "Musuh terbakar, memberikan damage 20% dari total magic damage" << endl;
                    musuh1.health = musuh1.health - magsementara * 20 / 100;
                    if(musuh1.health < 0) musuh1.health = 0;
                    cout << "Health Musuh : " << musuh1.health << endl;
                } else if (waktuterbakar < gerakanplayer.size()) {
                    firemagic == false;
                }
                musuh1.serang(musuh1.attack, kzl.health, kzl.defense);
                cout << "Health Player : " << kzl.health << endl;
            }
            attsementara = kzl.attack;
            gunakanspirit = false;
            evasionsementara = kzl.evasion;
            gerakanplayer.push(1);
            gerakanmusuh.push(1);
        }
        else if (x == 4) {
            gunakanspirit = kzl.gunakanspirit(attsementara);
        }
        else if (x == 2) {
            if (kzl.magicpoint >= 100) {
                int randomeva = rand() % 101;
                if (randomeva <= evasionsementara) {
                    cout << "Anda menghindari serangan lawan dan menyerangnya" << endl;
                    firemagic = kzl.serangdengansihirapi(magsementara, musuh1.health, musuh1.defense, gunakanspirit);
                    waktuterbakar = gerakanplayer.size() + 3;
                    cout << "Health Musuh : " << musuh1.health << endl;
                    cout << "Health Player : " << kzl.health << endl;
                } else {
                    firemagic = kzl.serangdengansihirapi(magsementara, musuh1.health, musuh1.defense, gunakanspirit);
                    waktuterbakar = gerakanplayer.size() + 3;
                    cout << "Health Musuh : " << musuh1.health << endl;
                    musuh1.serang(musuh1.attack, kzl.health, kzl.defense);
                    cout << "Health Player : " << kzl.health << endl;
                }
                kzl.magicpoint = kzl.magicpoint - 50;
                cout << "MP Tersisa : " << kzl.magicpoint << endl;
                magsementara = kzl.magicdamage;
                gunakanspirit = false;
                evasionsementara = kzl.evasion;
            }
            else {
                cout << "You dont have enough MP" << endl;
            }
        }
        else if (x == 3) {
            cout << "===== Daftar Skills yang Terbuka =====" << endl;
            vector<treeskills*> skillList = {
                root1, child1, child2, child1_1, child1_2, child2_1, child2_2,
                root2, magchild1, magchild2, magchild1_1, magchild1_2, magchild2_1, magchild2_2
            };
            vector<string> skillNames;
            for (auto skill : skillList) {
                if (skill->unlocked) {
                    cout << "- " << skill->name << endl;
                    skillNames.push_back(skill->name);
                }
            }
            if (!skillNames.empty()) {
                cout << "Pilih skill untuk digunakan: ";
                string pilih;
                cin.ignore();
                getline(cin, pilih);
                int biayaMP = 0;
                bool skillBerhasil = false;
                if (pilih == "Sword Aura") {
                    biayaMP = 50;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Seranganmu diperkuat oleh aura pedang (+20% attack untuk 1 serangan)\n";
                        attsementara += 20*attsementara/100;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Sword God") {
                    biayaMP = 100;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Kekuatan dewa pedang! (+100% attack dan menghindari 1 serangan)\n";
                        attsementara += attsementara;
                        evasionsementara = 100;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Demon Slash") {
                    biayaMP = 200;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Serangan iblis meledak! (Damage x2)\n";
                        attsementara *= 2;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Storm of Heaven") {
                    biayaMP = 230;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Kamu menciptakan badai suci yang melukai musuh\n";
                        musuh1.health -= 500;
                        if (musuh1.health < 0) musuh1.health = 0;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Hero Ultimate") {
                    biayaMP = 1000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Skill pamungkas pahlawan! (+1000% semua atribut)\n";
                        attsementara += attsementara*10;
                        magsementara += magsementara*10;
                        evasionsementara += 100;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Inferno") {
                    biayaMP = 450;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Membakar musuh! Efek terbakar aktif hingga 10 giliran\n";
                        musuh1.health -= 1000;
                        firemagic = true;
                        waktuterbakar = gerakanplayer.size() + 10;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Ice Rain") {
                    biayaMP = 90;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Hujan es memperlambat musuh! Mengurangi defense musuh 50%\n";
                        musuh1.defense = max(0, musuh1.defense - musuh1.defense*50/100);
                        skillBerhasil = true;
                    }
                } else if (pilih == "Dark Void") {
                    biayaMP = 1000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Void kegelapan menyerap jiwa musuh (-2000 HP)\n";
                        musuh1.health -= 2000;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Holy Lance") {
                    biayaMP = 300;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Tombak suci menusuk! +100% magic damage sementara\n";
                        magsementara += magsementara;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Lightning Wrath") {
                    biayaMP = 2000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Petir murka! Musuh kehilangan 50% HP saat ini\n";
                        musuh1.health -= musuh1.health * 50 / 100;
                        if (musuh1.health < 0) musuh1.health = 0;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Iron Maiden") {
                    biayaMP = 10000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Instant Death\n";
                        musuh1.health = 0;
                        skillBerhasil = true;
                    }
                } else {
                    cout << "Skill tidak ditemukan atau belum dibuka!\n";
                }
                if (skillBerhasil) {
                    kzl.magicpoint -= biayaMP;
                    cout << "MP tersisa: " << kzl.magicpoint << endl;
                } else if (biayaMP > 0) {
                    cout << "MP Anda tidak cukup untuk menggunakan skill ini!\n";
                }
            } else {
                cout << "Tidak ada skill yang terbuka\n";
            }
        }else if (x == 5){
            int jadi = 0;
            kzl.displaySortedPotion();
            cout << "1.Cari Potion\n2. Batal\n";
            cin >> jadi;
            if (jadi == 1){
                string name;
                cin.ignore();
                cout << "Masukkan Nama Potion : ";
                getline(cin, name);
                kzl.searchpotion(name);
            }
        }
        else if (x == 0){
            break;
        }
    } while (musuh1.health > 0 && kzl.health > 0);
    if(musuh1.health == 0) {
        kzl.experience += 30000;
        kzl.levelup();
        int randomitem = rand() % 4;
        switch (randomitem) {
            case 1:
                kzl.insertweapon(new weapon("Spirit Blade", 12000, 2500, false));
                cout << "Anda Mendapatkan Senjata : Spirit Blade" << endl; 
                break;
            case 2:
                kzl.insertarmor(new armor("Spirit Robe", 15000, 2800, false));
                cout << "Anda Mendapatkan Armor : Spirit Robe" << endl; 
                break;
            case 3:
                kzl.insertpotion(new potion("Spirit Essence", 15000, 3000));
                cout << "Anda Mendapatkan Potion : Spirit Essence" << endl; 
                break;
            default:
                break;
        }
    }
}
void serangSlimeEmperor() {
    int x = 0;
    musuh musuh1(35000, 7000, 3500, 0);
    int healthmusuhawal = musuh1.health;
    int attsementara = kzl.attack;
    int magsementara = kzl.magicdamage;
    int evasionsementara = kzl.evasion;
    stack<int> gerakanplayer;
    stack<int> gerakanmusuh;
    bool firemagic = false;
    int waktuterbakar = 0;
    bool gunakanspirit = false;
    cout << "Anda bertemu dengan Slime Emperor" << endl;
    do {
        cout << "1. Serang \n2. Serang dengan sihir api (100 MP)\n3. Gunakan Skill\n4. Gunakan Spirit\n5. Gunakan Potion\n0. Lari!" << endl;
        cout << "Spirit : " << kzl.herospirit.size() << endl;
        cin >> x;
        if (x == 1) {
            int randomeva = rand() % 101;
            if (randomeva <= evasionsementara) {
                cout << "Anda menghindari serangan lawan dan menyerangnya" << endl;
                kzl.serang(attsementara, musuh1.health, musuh1.defense, gunakanspirit);
                cout << "Health Musuh : " << musuh1.health << endl;
                if (firemagic == true && waktuterbakar >= gerakanplayer.size()) {
                    cout << "Musuh terbakar, memberikan damage 20% dari total magic damage" << endl;
                    musuh1.health = musuh1.health - magsementara * 20 / 100;
                    if(musuh1.health < 0) musuh1.health = 0;
                    cout << "Health Musuh : " << musuh1.health << endl;
                } else if (waktuterbakar < gerakanplayer.size()) {
                    firemagic == false;
                }
                cout << "Health Player : " << kzl.health << endl;
            } else {
                kzl.serang(attsementara, musuh1.health, musuh1.defense, gunakanspirit);
                cout << "Health Musuh : " << musuh1.health << endl;
                if (firemagic == true && waktuterbakar >= gerakanplayer.size()) {
                    cout << "Musuh terbakar, memberikan damage 20% dari total magic damage" << endl;
                    musuh1.health = musuh1.health - magsementara * 20 / 100;
                    if(musuh1.health < 0) musuh1.health = 0;
                    cout << "Health Musuh : " << musuh1.health << endl;
                } else if (waktuterbakar < gerakanplayer.size()) {
                    firemagic == false;
                }
                musuh1.serang(musuh1.attack, kzl.health, kzl.defense);
                cout << "Health Player : " << kzl.health << endl;
            }
            attsementara = kzl.attack;
            gunakanspirit = false;
            evasionsementara = kzl.evasion;
            gerakanplayer.push(1);
            gerakanmusuh.push(1);
        }
        else if (x == 4) {
            gunakanspirit = kzl.gunakanspirit(attsementara);
        }
        else if (x == 2) {
            if (kzl.magicpoint >= 100) {
                int randomeva = rand() % 101;
                if (randomeva <= evasionsementara) {
                    cout << "Anda menghindari serangan lawan dan menyerangnya" << endl;
                    firemagic = kzl.serangdengansihirapi(magsementara, musuh1.health, musuh1.defense, gunakanspirit);
                    waktuterbakar = gerakanplayer.size() + 3;
                    cout << "Health Musuh : " << musuh1.health << endl;
                    cout << "Health Player : " << kzl.health << endl;
                } else {
                    firemagic = kzl.serangdengansihirapi(magsementara, musuh1.health, musuh1.defense, gunakanspirit);
                    waktuterbakar = gerakanplayer.size() + 3;
                    cout << "Health Musuh : " << musuh1.health << endl;
                    musuh1.serang(musuh1.attack, kzl.health, kzl.defense);
                    cout << "Health Player : " << kzl.health << endl;
                }
                kzl.magicpoint = kzl.magicpoint - 50;
                cout << "MP Tersisa : " << kzl.magicpoint << endl;
                magsementara = kzl.magicdamage;
                gunakanspirit = false;
                evasionsementara = kzl.evasion;
            }
            else {
                cout << "You dont have enough MP" << endl;
            }
        }
        else if (x == 3) {
            cout << "===== Daftar Skills yang Terbuka =====" << endl;
            vector<treeskills*> skillList = {
                root1, child1, child2, child1_1, child1_2, child2_1, child2_2,
                root2, magchild1, magchild2, magchild1_1, magchild1_2, magchild2_1, magchild2_2
            };
            vector<string> skillNames;
            for (auto skill : skillList) {
                if (skill->unlocked) {
                    cout << "- " << skill->name << endl;
                    skillNames.push_back(skill->name);
                }
            }
            if (!skillNames.empty()) {
                cout << "Pilih skill untuk digunakan: ";
                string pilih;
                cin.ignore();
                getline(cin, pilih);
                int biayaMP = 0;
                bool skillBerhasil = false;
                if (pilih == "Sword Aura") {
                    biayaMP = 50;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Seranganmu diperkuat oleh aura pedang (+20% attack untuk 1 serangan)\n";
                        attsementara += 20*attsementara/100;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Sword God") {
                    biayaMP = 100;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Kekuatan dewa pedang! (+100% attack dan menghindari 1 serangan)\n";
                        attsementara += attsementara;
                        evasionsementara = 100;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Demon Slash") {
                    biayaMP = 200;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Serangan iblis meledak! (Damage x2)\n";
                        attsementara *= 2;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Storm of Heaven") {
                    biayaMP = 230;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Kamu menciptakan badai suci yang melukai musuh\n";
                        musuh1.health -= 500;
                        if (musuh1.health < 0) musuh1.health = 0;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Hero Ultimate") {
                    biayaMP = 1000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Skill pamungkas pahlawan! (+1000% semua atribut)\n";
                        attsementara += attsementara*10;
                        magsementara += magsementara*10;
                        evasionsementara += 100;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Inferno") {
                    biayaMP = 450;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Membakar musuh! Efek terbakar aktif hingga 10 giliran\n";
                        musuh1.health -= 1000;
                        firemagic = true;
                        waktuterbakar = gerakanplayer.size() + 10;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Ice Rain") {
                    biayaMP = 90;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Hujan es memperlambat musuh! Mengurangi defense musuh 50%\n";
                        musuh1.defense = max(0, musuh1.defense - musuh1.defense*50/100);
                        skillBerhasil = true;
                    }
                } else if (pilih == "Dark Void") {
                    biayaMP = 1000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Void kegelapan menyerap jiwa musuh (-2000 HP)\n";
                        musuh1.health -= 2000;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Holy Lance") {
                    biayaMP = 300;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Tombak suci menusuk! +100% magic damage sementara\n";
                        magsementara += magsementara;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Lightning Wrath") {
                    biayaMP = 2000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Petir murka! Musuh kehilangan 50% HP saat ini\n";
                        musuh1.health -= musuh1.health * 50 / 100;
                        if (musuh1.health < 0) musuh1.health = 0;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Iron Maiden") {
                    biayaMP = 10000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Instant Death\n";
                        musuh1.health = 0;
                        skillBerhasil = true;
                    }
                } else {
                    cout << "Skill tidak ditemukan atau belum dibuka!\n";
                }
                if (skillBerhasil) {
                    kzl.magicpoint -= biayaMP;
                    cout << "MP tersisa: " << kzl.magicpoint << endl;
                } else if (biayaMP > 0) {
                    cout << "MP Anda tidak cukup untuk menggunakan skill ini!\n";
                }
            } else {
                cout << "Tidak ada skill yang terbuka\n";
            }
        }else if (x == 5){
            int jadi = 0;
            kzl.displaySortedPotion();
            cout << "1.Cari Potion\n2. Batal\n";
            cin >> jadi;
            if (jadi == 1){
                string name;
                cin.ignore();
                cout << "Masukkan Nama Potion : ";
                getline(cin, name);
                kzl.searchpotion(name);
            }
        }
        else if (x == 0){
            break;
        }
    } while (musuh1.health > 0 && kzl.health > 0);
    if(musuh1.health == 0) {
        kzl.experience += 35000;
        kzl.levelup();
        int randomitem = rand() % 4;
        switch (randomitem) {
            case 1:
                kzl.insertweapon(new weapon("Royal Slime Core", 15000, 3000, false));
                cout << "Anda Mendapatkan Senjata : Royal Slime Core" << endl; 
                break;
            case 2:
                kzl.insertarmor(new armor("Emperor's Gel", 18000, 3500, false));
                cout << "Anda Mendapatkan Armor : Emperor's Gel" << endl; 
                break;
            case 3:
                kzl.insertpotion(new potion("Royal Jelly", 18000, 3500));
                cout << "Anda Mendapatkan Potion : Royal Jelly" << endl; 
                break;
            default:
                break;
        }
    }
}
void serangNagaKuno() {
    int x = 0;
    musuh musuh1(40000, 8000, 4000, 0);
    int healthmusuhawal = musuh1.health;
    int attsementara = kzl.attack;
    int magsementara = kzl.magicdamage;
    int evasionsementara = kzl.evasion;
    stack<int> gerakanplayer;
    stack<int> gerakanmusuh;
    bool firemagic = false;
    int waktuterbakar = 0;
    bool gunakanspirit = false;
    cout << "Anda bertemu dengan Naga Kuno" << endl;
    do {
        cout << "1. Serang \n2. Serang dengan sihir api (100 MP)\n3. Gunakan Skill\n4. Gunakan Spirit\n5. Gunakan Potion\n0. Lari!" << endl;
        cout << "Spirit : " << kzl.herospirit.size() << endl;
        cin >> x;
        if (x == 1) {
            int randomeva = rand() % 101;
            if (randomeva <= evasionsementara) {
                cout << "Anda menghindari serangan lawan dan menyerangnya" << endl;
                kzl.serang(attsementara, musuh1.health, musuh1.defense, gunakanspirit);
                cout << "Health Musuh : " << musuh1.health << endl;
                if (firemagic == true && waktuterbakar >= gerakanplayer.size()) {
                    cout << "Musuh terbakar, memberikan damage 20% dari total magic damage" << endl;
                    musuh1.health = musuh1.health - magsementara * 20 / 100;
                    if(musuh1.health < 0) musuh1.health = 0;
                    cout << "Health Musuh : " << musuh1.health << endl;
                } else if (waktuterbakar < gerakanplayer.size()) {
                    firemagic == false;
                }
                cout << "Health Player : " << kzl.health << endl;
            } else {
                kzl.serang(attsementara, musuh1.health, musuh1.defense, gunakanspirit);
                cout << "Health Musuh : " << musuh1.health << endl;
                if (firemagic == true && waktuterbakar >= gerakanplayer.size()) {
                    cout << "Musuh terbakar, memberikan damage 20% dari total magic damage" << endl;
                    musuh1.health = musuh1.health - magsementara * 20 / 100;
                    if(musuh1.health < 0) musuh1.health = 0;
                    cout << "Health Musuh : " << musuh1.health << endl;
                } else if (waktuterbakar < gerakanplayer.size()) {
                    firemagic == false;
                }
                musuh1.serang(musuh1.attack, kzl.health, kzl.defense);
                cout << "Health Player : " << kzl.health << endl;
            }
            attsementara = kzl.attack;
            gunakanspirit = false;
            evasionsementara = kzl.evasion;
            gerakanplayer.push(1);
            gerakanmusuh.push(1);
        }
        else if (x == 4) {
            gunakanspirit = kzl.gunakanspirit(attsementara);
        }
        else if (x == 2) {
            if (kzl.magicpoint >= 100) {
                int randomeva = rand() % 101;
                if (randomeva <= evasionsementara) {
                    cout << "Anda menghindari serangan lawan dan menyerangnya" << endl;
                    firemagic = kzl.serangdengansihirapi(magsementara, musuh1.health, musuh1.defense, gunakanspirit);
                    waktuterbakar = gerakanplayer.size() + 3;
                    cout << "Health Musuh : " << musuh1.health << endl;
                    cout << "Health Player : " << kzl.health << endl;
                } else {
                    firemagic = kzl.serangdengansihirapi(magsementara, musuh1.health, musuh1.defense, gunakanspirit);
                    waktuterbakar = gerakanplayer.size() + 3;
                    cout << "Health Musuh : " << musuh1.health << endl;
                    musuh1.serang(musuh1.attack, kzl.health, kzl.defense);
                    cout << "Health Player : " << kzl.health << endl;
                }
                kzl.magicpoint = kzl.magicpoint - 50;
                cout << "MP Tersisa : " << kzl.magicpoint << endl;
                magsementara = kzl.magicdamage;
                gunakanspirit = false;
                evasionsementara = kzl.evasion;
            }
            else {
                cout << "You dont have enough MP" << endl;
            }
        }
        else if (x == 3) {
            cout << "===== Daftar Skills yang Terbuka =====" << endl;
            vector<treeskills*> skillList = {
                root1, child1, child2, child1_1, child1_2, child2_1, child2_2,
                root2, magchild1, magchild2, magchild1_1, magchild1_2, magchild2_1, magchild2_2
            };
            vector<string> skillNames;
            for (auto skill : skillList) {
                if (skill->unlocked) {
                    cout << "- " << skill->name << endl;
                    skillNames.push_back(skill->name);
                }
            }
            if (!skillNames.empty()) {
                cout << "Pilih skill untuk digunakan: ";
                string pilih;
                cin.ignore();
                getline(cin, pilih);
                int biayaMP = 0;
                bool skillBerhasil = false;
                if (pilih == "Sword Aura") {
                    biayaMP = 50;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Seranganmu diperkuat oleh aura pedang (+20% attack untuk 1 serangan)\n";
                        attsementara += 20*attsementara/100;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Sword God") {
                    biayaMP = 100;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Kekuatan dewa pedang! (+100% attack dan menghindari 1 serangan)\n";
                        attsementara += attsementara;
                        evasionsementara = 100;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Demon Slash") {
                    biayaMP = 200;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Serangan iblis meledak! (Damage x2)\n";
                        attsementara *= 2;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Storm of Heaven") {
                    biayaMP = 230;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Kamu menciptakan badai suci yang melukai musuh\n";
                        musuh1.health -= 500;
                        if (musuh1.health < 0) musuh1.health = 0;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Hero Ultimate") {
                    biayaMP = 1000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Skill pamungkas pahlawan! (+1000% semua atribut)\n";
                        attsementara += attsementara*10;
                        magsementara += magsementara*10;
                        evasionsementara += 100;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Inferno") {
                    biayaMP = 450;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Membakar musuh! Efek terbakar aktif hingga 10 giliran\n";
                        musuh1.health -= 1000;
                        firemagic = true;
                        waktuterbakar = gerakanplayer.size() + 10;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Ice Rain") {
                    biayaMP = 90;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Hujan es memperlambat musuh! Mengurangi defense musuh 50%\n";
                        musuh1.defense = max(0, musuh1.defense - musuh1.defense*50/100);
                        skillBerhasil = true;
                    }
                } else if (pilih == "Dark Void") {
                    biayaMP = 1000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Void kegelapan menyerap jiwa musuh (-2000 HP)\n";
                        musuh1.health -= 2000;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Holy Lance") {
                    biayaMP = 300;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Tombak suci menusuk! +100% magic damage sementara\n";
                        magsementara += magsementara;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Lightning Wrath") {
                    biayaMP = 2000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Petir murka! Musuh kehilangan 50% HP saat ini\n";
                        musuh1.health -= musuh1.health * 50 / 100;
                        if (musuh1.health < 0) musuh1.health = 0;
                        skillBerhasil = true;
                    }
                } else if (pilih == "Iron Maiden") {
                    biayaMP = 10000;
                    if (kzl.magicpoint >= biayaMP) {
                        cout << "Instant Death\n";
                        musuh1.health = 0;
                        skillBerhasil = true;
                    }
                } else {
                    cout << "Skill tidak ditemukan atau belum dibuka!\n";
                }
                if (skillBerhasil) {
                    kzl.magicpoint -= biayaMP;
                    cout << "MP tersisa: " << kzl.magicpoint << endl;
                } else if (biayaMP > 0) {
                    cout << "MP Anda tidak cukup untuk menggunakan skill ini!\n";
                }
            } else {
                cout << "Tidak ada skill yang terbuka\n";
            }
        }else if (x == 5){
            int jadi = 0;
            kzl.displaySortedPotion();
            cout << "1.Cari Potion\n2. Batal\n";
            cin >> jadi;
            if (jadi == 1){
                string name;
                cin.ignore();
                cout << "Masukkan Nama Potion : ";
                getline(cin, name);
                kzl.searchpotion(name);
            }
        }
        else if (x == 0){
            break;
        }
    } while (musuh1.health > 0 && kzl.health > 0);
    if(musuh1.health == 0) {
        kzl.experience += 40000;
        kzl.levelup();
        int randomitem = rand() % 4;
        switch (randomitem) {
            case 1:
                kzl.insertweapon(new weapon("Ancient Naga Fang", 20000, 4000, false));
                cout << "Anda Mendapatkan Senjata : Ancient Naga Fang" << endl; 
                break;
            case 2:
                kzl.insertarmor(new armor("Naga King Scale", 25000, 4000, false));
                cout << "Anda Mendapatkan Armor : Naga King Scale" << endl; 
                break;
            case 3:
                kzl.insertpotion(new potion("Elixir of the Ancients", 25000, 4000));
                cout << "Anda Mendapatkan Potion : Elixir of the Ancients" << endl; 
                break;
            default:
                break;
        }
    }
}


void waitForNext() {
    cout << "\nTekan Enter untuk melanjutkan...";
    string dummy;
    getline(cin, dummy);
}



    // Rumah
void event1Rumah() {
    int y = 10;
    cout << "Apakah anda mau beristirahat?\n1. Bobooo Cape\n2. Gak dl" << endl;
    cin >> y;
    if (y == 1){
        kzl.health = kzl.maxhealth;
        kzl.magicpoint = kzl.maxmagicpoint;
        cout << "Health dan Magic Point dipulihkan!" << endl;
        return;
    }
}
// Ibu Kota
void event1IbuKota() {
    int pilihan;

    cout << "Anda memasuki aula megah istana kerajaan.\n";
    cout << "Di ujung ruangan, Raja berdiri dengan jubah emas dan mahkota berkilau.\n";
    cout << "Raja: \"Akhirnya, Adventurer terkuat telah tiba...\"\n\n";

    cout << "1. \"Perihal apakah yang Anda butuhkan, Wahai Rajaku?\"\n";
    cout << "2. \"Apakah Anda memerlukan sesuatu, Wahai Rajaku?\"\n";
    cout << ">> Pilih (1/2): ";
    cin >> pilihan;
    cout << endl;

    // Semua pilihan mengarah ke quest
    cout << "Raja: \"Dunia kita berada di ambang kehancuran. Raja Iblis telah bangkit kembali...\"\n";
    cout << "Raja: \"Pasukan kami tak sanggup menahannya. Hanya kau, Adventurer terkuat, yang bisa menyelamatkan dunia ini.\"\n";
    cout << "Raja: \"Aku memohon padamu, demi seluruh rakyat di benua ini... Kalahkan Raja Iblis dan bawa kedamaian abadi.\"\n\n";
    waitForNext();
    cout << "Anda mengangguk dengan tekad yang membara.\n";
    cout << "QUEST UTAMA DITERIMA: 'Mengalahkan Raja Iblis'\n";
    cout << "Lokasi: Istana Kegelapan di Puncak Gunung Neraka\n";
    cout << "Hadiah: Gelar Legenda Cahaya, Harta Tertinggi Kerajaan, dan Ramalan Sang Penyelamat\n\n";
    cout << "Raja: \"Semoga cahaya para dewa menyertaimu, Pahlawan Dunia.\"\n";
}
void event2IbuKota() {
    cout << " Setelah pertarungan panjang dan penuh pengorbanan...\n";
    cout << " RAJA IBLIS TELAH DIKALAHKAN!\n\n";
    cout << " Anda kembali ke ibu kota. Gerbang dibuka lebar, dan ribuan orang telah berkumpul.\n";
    cout << " Rakyat dari segala penjuru bersorak: \"Hidup Sang Pahlawan! Hidup Sang Penyelamat Dunia!\"\n";
    cout << " Konfeti dan bunga dilemparkan ke udara. Suara lonceng berdentang dari menara istana.\n\n";
    waitForNext();
    cout << "Raja berdiri di atas balkon istana, mengangkat tangannya.\n";
    cout << "Raja: \"Hari ini... dunia diselamatkan oleh dua orang luar biasa.\"\n";
    cout << "Raja: \"Mulai hari ini, engkau tidak hanya petualang terkuat... tapi juga LEGENDA ABADI KERAJAAN!\"\n\n";
    waitForNext();
    cout << "Anda dianugerahi Gelar 'Legenda Cahaya'.\n";
    cout << "Harta Karun Kerajaan diberikan padamu.\n";
    cout << "Pedang Raja Iblis telah dimurnikan dan menjadi simbol harapan.\n\n";    
    cout << "Lagu kebangsaan dimainkan. Semua orang bersujud dan bersorak:\n";
    cout << "\"PANJANG UMUR PAHLAWAN KITA! PANJANG UMUR PENYELAMAT DUNIA!\"\n\n";
    waitForNext();
    cout << "Dunia berubah. Kerajaan-kerajaan saling berdamai. Akademi Hero menjadi simbol harapan baru.\n";
    cout << "Patung dua pahlawan dibangun di halaman akademi — satu dengan pedang cahaya, satu lagi membaca buku sihir...\n";

    waitForNext();

    cout << "Semua orang mengenang 'Duo Cahaya'.\n";
    cout << "Namun hanya sedikit yang tahu kisah di balik kemenangan itu...\n";
    cout << "Tentang cinta, pengorbanan, dan kekuatan yang lahir dari hati manusia.\n";

    waitForNext();

    cout << "Anda menjalani hari-hari sebagai legenda hidup. Tapi di setiap senyum, ada luka yang tak pernah benar-benar hilang.\n";
    cout << "Dan setiap malam, kau menatap bintang-bintang... berharap bisa berbagi cerita baru dengan sahabatmu di sisi lain dunia.\n";

    waitForNext();

    cout << "Sebuah era baru dimulai. Namamu dan namanya tercatat dalam sejarah selamanya...\n";
}
// Akademi Hero
void event1AkademiHero() {
    int pilihan = 0;

    cout << "Akademi Hero sedang membuka pendaftaran untuk calon pahlawan masa depan...\n";
    waitForNext();
    cout << "Petugas Akademi: \"Apakah Anda ingin mendaftar dan mengikuti ujian masuk?\"\n";
    cout << "1. Ikut\n2. Malas\n";
    cout << ">> Pilihan Anda: ";
    cin >> pilihan;

    cout << "\nAnda mengikuti serangkaian ujian sihir, pertarungan, dan kecerdasan...\n";
    waitForNext();
    cout << "Dengan kemampuan luar biasa, Anda menyelesaikan semua tes dengan sempurna.\n +2000 Exp";
    waitForNext();
    kzl.experience += 2000;
    kzl.levelup();
    kzl.inginmenambahkanstatusatauunlockskill();
    cout << "Hasil diumumkan... Anda berada di PERINGKAT PERTAMA dari seluruh peserta!\n";
    waitForNext();
    cout << "Selamat! Anda resmi diterima di Akademi Hero sebagai murid terbaik!\n\n";
    waitForNext();
    cout << "Hari pertama dimulai...\n";
    cout << "Anda berjalan memasuki gedung utama akademi dan menuju ruang kelas 1-A.\n";
    cout << "Ruang kelas dipenuhi wajah-wajah baru, calon pahlawan dari seluruh benua.\n";
    waitForNext();
    cout << "\nDi dekat jendela, duduk seorang gadis dengan rambut putih keperakan dan mata biru jernih.\n";
    cout << "Dia tampak diam, sedang membaca buku sihir tingkat lanjut.\n";
    waitForNext();
    cout << "\n(Mungkin aku bisa mulai mengenal teman sekelas...)";
    cout << "\nIngin bicara dengannya?\n";
    cout << "1. \"Hai, boleh aku duduk di sini?\"\n";
    cout << "2. \"Kau terlihat pintar. Siapa namamu?\"\n";
    cout << ">> Pilih: ";
    cin >> pilihan;
    cin.ignore();
    cout << endl;
    if (pilihan == 1) {
        cout << "Gadis itu menoleh perlahan, tampak sedikit terkejut tapi tersenyum tipis.\n";
        cout << "\"Tentu, silakan. Tak banyak orang yang ramah di hari pertama.\"\n";
        waitForNext();
        cout << "Dia menutup bukunya dan berkata, \"Namaku Ardelia. Aku berasal dari Kerajaan Utara.\"\n";
        waitForNext();
        cout << "\"Kau peringkat pertama, bukan? Hebat... Aku berharap kita bisa belajar bersama.\"\n";
        waitForNext();
        cout << "Ardelia tampak mulai nyaman dan kalian berbincang soal kelas dan pelajaran sihir.\n";
        waitForNext();
    } else if (pilihan == 2) {
        cout << "Ardelia menatapmu dengan ekspresi sedikit bingung.\n";
        waitForNext();
        cout << "\"Hm? Terima kasih... Aku Ardelia. Aku suka belajar sihir—itu saja.\"\n";
        waitForNext();
        cout << "Dia kembali membaca bukunya sejenak, lalu bertanya, \"Kau peringkat pertama, kan?\"\n";
        waitForNext();
        cout << "\"Kalau begitu... jangan buat aku tertinggal, ya.\"\n";
        waitForNext();
        cout << "Suasana menjadi agak kaku, tapi kalian mulai mengenal satu sama lain.\n";
        waitForNext();
    } else {
        cout << "Kau hanya duduk diam, dan waktu pelajaran segera dimulai.\n";
        waitForNext();
    }
    cout << "\nBel berbunyi. Guru dengan jubah panjang masuk ke kelas dan memperkenalkan diri.\n";
    waitForNext();
    cout << "\"Selamat datang di Akademi Hero. Di sinilah kalian akan ditempa menjadi legenda.\"\n";
    waitForNext();
    cout << "\"Hari ini... pelatihan kalian sebagai calon pahlawan dimulai.\"\n";
    waitForNext();
    cout << "Aura kelas mulai berubah... Sebuah petualangan besar baru saja dimulai.\n\n";
    waitForNext();
    cout << "\nHari-hari di akademi pun dimulai...\n +1000 Exp";
    waitForNext();
    kzl.experience += 1000;
    kzl.levelup();
    kzl.inginmenambahkanstatusatauunlockskill();
    cout << "Setelah pelajaran pertama usai, para murid mulai berdiskusi di kelompok kecil.\n";
    cout << "Ardelia melirik ke arahmu, lalu menghampiri dengan ragu.\n";
    waitForNext();
    cout << "Ardelia: \"Hei... soal tadi, kamu bisa mengendalikan sihir energi dengan sangat lancar.\"\n";
    cout << "Ardelia: \"Aku belum bisa mengontrol sihirku sebaik itu...\"\n";
    
    cout << "\nApa yang akan kamu katakan?\n";
    cout << "1. \"Mau latihan bareng? Kita bisa saling bantu.\"\n";
    cout << "2. \"Sudah kubilang aku jenius, kan?\"\n";
    cout << ">> Pilihan: ";
    cin >> pilihan;
    cin.ignore();
    cout << endl;
    if (pilihan == 1) {
        cout << "Ardelia tersenyum untuk pertama kalinya dengan tulus.\n";
        waitForNext();
        cout << "Ardelia: \"Serius? Itu akan sangat membantu. Aku... senang bisa bekerjasama.\"\n";
        cout << "Sejak hari itu, kalian berlatih bersama setiap sore di halaman akademi yang sepi.\n";
        cout << "Kekompakan kalian membuat kalian dijuluki 'Duo Cahaya' oleh para murid lain. +1000 Exp\n\n";
        waitForNext();
        kzl.experience += 1000;
        kzl.levelup();
        kzl.inginmenambahkanstatusatauunlockskill();
    } else {
        cout << "Ardelia menatapmu datar, lalu tertawa kecil.\n";
        waitForNext();
        cout << "Ardelia: \"Sombong juga, ya... Tapi aku tidak akan kalah.\"\n";
        cout << "Meski begitu, ia tetap berlatih bersamamu — dan mulai melihatmu sebagai rival yang menyenangkan. +1000 Exp\n\n";
        waitForNext();
        kzl.experience += 1000;
        kzl.levelup();
        kzl.inginmenambahkanstatusatauunlockskill();
    }
    cout << "Suatu hari, saat kalian sedang latihan di bawah pohon besar...\n";
    waitForNext();
    cout << "Ardelia: \"Kau tahu... di masa kecil, aku pernah menyaksikan desaku dihancurkan oleh iblis.\"\n";
    waitForNext();
    cout << "Ardelia: \"Itulah alasan aku ingin menjadi kuat. Aku ingin bisa melindungi orang lain.\"\n";
    waitForNext();
    cout << "\nApa balasanmu?\n";
    cout << "1. \"Aku akan membantumu. Kau tidak sendiri sekarang.\"\n";
    cout << "2. \"Masa lalu itu menyakitkan. Tapi sekarang kau bisa membuat masa depan.\"\n";
    cout << ">> Pilihan: ";
    cin >> pilihan;
    cin.ignore();
    cout << endl;
    if (pilihan == 1) {
        cout << "Ardelia menatapmu lama, lalu tersenyum tipis.\n";
        waitForNext();
        cout << "Ardelia: \"Terima kasih... Aku tak pernah bilang ini ke siapa pun sebelumnya.\"\n";
        waitForNext();
        cout << "Sejak saat itu, kedekatan kalian tumbuh melebihi sekadar rekan latihan.\n\n";
        waitForNext();
    } else {
        cout << "Ardelia terdiam sejenak, lalu berkata:\n";
        cout << "\"Kau benar... Aku ingin menciptakan masa depan yang tidak seperti masa laluku.\"\n";
        waitForNext();
        cout << "Kau melihat semangat baru di matanya — dan ia mulai membuka dirinya lebih banyak padamu.\n\n";
        waitForNext();
    }
    cout << "Bulan-bulan berlalu. Kalian belajar bersama, bertarung bersama, dan tumbuh bersama. +10000 Exp\n";
    kzl.experience += 10000;
    kzl.levelup();
    waitForNext();
    cout << "Tak satu pun tantangan akademi yang kalian hadapi sendirian. +10000 Exp\n";
    kzl.experience += 10000;
    kzl.levelup();
    waitForNext();
    cout << "Sebuah ikatan mulai terbentuk — tidak hanya sebagai rekan seperjuangan, tapi sebagai sesuatu yang lebih...\n";
    waitForNext();
    kzl.inginmenambahkanstatusatauunlockskill();
    cout << "\nBeberapa minggu kemudian... +1000 Exp\n";
    kzl.experience += 1000;
    kzl.levelup();
    waitForNext();
    
    cout << "Akademi mengadakan latihan gabungan antar kelas untuk mengukur kemajuan murid.\n";
    waitForNext();
    cout << "Anda dipasangkan dengan murid dari kelas lain: Eliz, pendekar tombak karismatik.\n";
    waitForNext();
    cout << "Dalam simulasi, Anda mengeksekusi kombo sihir-taktik yang sangat cerdas, mengalahkan semua lawan.\n";
    cout << "Seluruh arena bersorak, termasuk guru dan kepala akademi.\n";
    waitForNext();
    cout << "Namun, Anda melihat Ardelia di pinggir lapangan - menatap Anda diam.\n";
    waitForNext();
    cout << "Ardelia: \"...Kamu hebat sekali bersama Eliz. Kalian terlihat cocok.\"\n";
    waitForNext();
    cout << "\nApa yang kamu katakan?\n";
    cout << "1. \"Tapi tetap saja, aku lebih suka latihan denganmu.\"\n";
    cout << "2. \"Dia kuat, tapi tidak bisa menggantikanmu.\"\n";
    cin >> pilihan;
    cin.ignore();
    if (pilihan == 1 || pilihan == 2) {
        cout << "Ardelia tersenyum tipis, lalu berkata: \"Benarkah...? Aku senang dengar itu.\"\n";
        waitForNext();
    }
    cout << "\nDi kelas sejarah sihir dan dunia kuno, seorang guru tua menunjukkan lukisan kuno bertema peperangan.\n";
    waitForNext();
    cout << "Guru: \"Ini adalah Raja Iblis Pertama. Dulu, ia menghancurkan separuh dunia sebelum dikalahkan oleh Hero Cahaya.\"\n";
    waitForNext();
    cout << "Ardelia berbisik: \"Kalau raja iblis kembali... apa kita cukup kuat menghentikannya...?\"\n";
    waitForNext();
    cout << "Kamu merasakan sesuatu... seolah lukisan itu menatap langsung ke jiwamu.\n";
    waitForNext();
    cout << "\nMalam festival akademi pun tiba. Lapangan penuh lampion dan tawa murid-murid.\n";
    waitForNext();
    cout << "Ardelia mengenakan pakaian festival yang berbeda dari biasanya. Ia menghampiri dengan wajah sedikit memerah.\n";
    waitForNext();
    cout << "Ardelia: \"Malam ini... mau jalan berdua saja?\"\n";
    waitForNext();
    cout << "\nKalian berjalan menyusuri jalan lampion. Suasana terasa tenang, damai...\n";
    waitForNext();
    cout << "Di atas bukit, kalian melihat kembang api meledak di langit.\n";
    waitForNext();
    cout << "Ardelia: \"Bersamamu... aku merasa dunia ini tidak seburuk itu.\"\n";
    waitForNext();
    cout << "\nTiba-tiba, alarm akademi berbunyi nyaring. Langit berubah gelap.\n";
    waitForNext();
    cout << "Guru: \"Pasukan Raja Iblis! Mereka berhasil menerobos penghalang akademi!\"\n";
    waitForNext();
    cout << "Para murid panik. Ardelia menarik tanganmu: \"Ayo! Kita harus bantu warga di asrama!\"\n";
    waitForNext();
    cout << "Kalian bertarung bersama menghadapi iblis-iblis kecil yang muncul dari portal gelap.\n";
    waitForNext();
    serangDemondenganArdelia();
    if (kzl.health == 0) return;
    serangDemondenganArdelia();
    if (kzl.health == 0) return;
    cout << "\nSeorang iblis elit muncul. Bertanduk, bersayap, dan bersenjata dua.\n";
    waitForNext();
    cout << "Ardelia: \"Kita hadapi dia... bersama!\"\n";
    serangBehemothdenganArdelia();
    if (kzl.health == 0) return;
    cout << "Dengan strategi dan kombinasi skill kalian, kalian akhirnya berhasil mengalahkannya.\n";
    cout << "Pasukan iblis mundur... namun ini hanya awal dari kembalinya kekuatan kegelapan.\n";
    waitForNext();
    cout << "\n2 tahun kemudian...\n";
    cout << "Pelatihan akademi dipercepat. Kamu dan Ardelia diakui sebagai duo terkuat angkatan kalian.\n";
    waitForNext();
    cout << "Di hari kelulusan, kalian berdiri di podium bersama.\n";
    waitForNext();
    cout << "Kepala Akademi: \"Keduanya lulus dengan predikat *Lulusan Istimewa*. Mereka akan menjadi cahaya dunia.\"\n";
    waitForNext();
    cout << "Kamu mendapatkan:\n";
    cout << "Weapon: Royal Sword\n";
    cout << "Armor: Royal Armor\n";
    cout << "Title: Pelindung Cahaya\n";
    kzl.insertweapon(new weapon("Royal Sword", 7500, 5000, false));
    kzl.insertarmor(new armor("Royal Armor", 25000, 5000, false));
    waitForNext();
    cout << "Ardelia menatapmu dan berkata:\n";
    waitForNext();
    cout << "\"Setelah ini... mari lindungi dunia bersama, ya?\"";
    waitForNext();
} 

// Hutan Kegelapan
void event1HutanKegelapan(int level) {
    cin.ignore();
    int pilihan = 0;
    do{
        if (level <= 10){
            int random = rand() % 5;
            switch (random)
            {
            case 1:
                cout << "Kamu disergap oleh monster di kegelapan hutan!\n";
                serangSlime();
                break;
            case 2:
                cout << "Kamu disergap oleh monster di kegelapan hutan!\n";
                serangGoblin();
                break;
            case 3:
                cout << "Kamu disergap oleh monster di kegelapan hutan!\n";
                serangOrc();
                break;
            case 4:
                cout << "Kamu disergap oleh monster di kegelapan hutan!\n";
                serangLizardMen();
                break;
            
            default:
                cout << "Anda Tidak Menemukan Apa Apa\n";
                break;
            }
        } else if (level <= 20){
            int random1 = rand() % 5;
            switch (random1)
            {
            case 1:
                cout << "Kamu disergap oleh monster di kegelapan hutan!\n";
                serangOgre();
                break;
            case 2:
                cout << "Kamu disergap oleh monster di kegelapan hutan!\n";
                serangWyvern();
                break;
            case 3:
                cout << "Kamu disergap oleh monster di kegelapan hutan!\n";
                serangGolem();
                break;
            case 4:
                cout << "Kamu disergap oleh monster di kegelapan hutan!\n";
                serangChimera();
                break;
            
            default:
                cout << "Anda Tidak Menemukan Apa Apa\n";
                break;
            }
        } else if (level <= 40){
            int random2 = rand() % 6;
            switch (random2)
            {
            case 1:
                cout << "Kamu disergap oleh monster di kegelapan hutan!\n";
                serangUndead();
                break;
            case 2:
                cout << "Kamu disergap oleh monster di kegelapan hutan!\n";
                serangDemon();
                break;
            case 3:
                cout << "Kamu disergap oleh monster di kegelapan hutan!\n";
                serangBasilisk();
                break;
            case 4:
                cout << "Kamu disergap oleh monster di kegelapan hutan!\n";
                serangGriffin();
                break;
            case 5:
                cout << "Kamu disergap oleh monster di kegelapan hutan!\n";
                serangNaga();
                break;
            
            default:
                cout << "Anda Tidak Menemukan Apa Apa\n";
                break;
            }
        } else if (level > 40){
            int random3 = rand() % 5;
            switch (random3)
            {
            case 1:
                cout << "Kamu disergap oleh monster di kegelapan hutan!\n";
                serangBehemoth();
                break;
            case 2:
                cout << "Kamu disergap oleh monster di kegelapan hutan!\n";
                serangSpiritBeast();
                break;
            case 3:
                cout << "Kamu disergap oleh monster di kegelapan hutan!\n";
                serangSlimeEmperor();
                break;
            case 4:
                cout << "Kamu disergap oleh monster di kegelapan hutan!\n";
                serangNagaKuno();
                break;
            
            default:
                cout << "Anda Tidak Menemukan Apa Apa\n";
                break;
            }
        }
        if (kzl.health != 0){ 
            cout << "Jelajahi Lagi?\n";
            cout << "1. Lagii dong, Kasih yang keras banh\n0. Muliih\n";
            cin >> pilihan;
        } else return;
        
    } while (pilihan != 0 && kzl.health != 0);
}
void event2HutanKegelapan(int level) {
    cout << "\nAnda melangkah lebih dalam ke dalam Hutan Kegelapan...\n";
    cout << "Udara semakin dingin, dan bisikan gaib makin kuat terdengar dari segala arah.\n";
    cout << "Kabut hitam menyelimuti tanah, seolah menyembunyikan rahasia kuno yang sudah terlupakan.\n";

    waitForNext();

    if (level < 50) {
        cout << "Kekuatan Anda belum cukup untuk menghadapi energi gelap di tempat ini.\n";
        cout << "Insting Anda berteriak untuk mundur... seolah ada sesuatu yang mengintai dari balik pepohonan.\n";
        cout << "Dengan berat hati, Anda memutuskan untuk kembali dan bersiap lebih matang di lain waktu.\n";
        return;
    }
    kzl.eventHutanKegelapan.pop();
    cout << "Aura energi kuno terasa menarik Anda menuju celah sempit di antara akar raksasa pohon purba.\n";
    cout << "Di sana... sebuah altar batu berlumut tergeletak, memancarkan cahaya biru kehijauan.\n";
    cout << "Di atasnya, tertancap sebuah pedang panjang dengan ukiran suci di bilahnya.\n";

    waitForNext();

    cout << "[Legenda: Pedang Pahlawan - 'Elarion']\n";
    cout << "Konon hanya pahlawan sejati yang bisa mencabutnya... dan Anda merasakan ikatan yang aneh dengannya.\n";
    cout << "Saat Anda mencoba menyentuh gagangnya...\n";

    waitForNext();

    cout << "Tanah bergetar hebat. Akar pohon berputar seperti ular...\n";
    cout << "Dari balik kabut, muncul siluet besar dengan mata emas menyala—\n";
    cout << "SEEKOR NAGA KUNO bangkit dari peristirahatannya!\n";
    cout << "[Boss: Varkhal, Naga Kuno]\n";
    cout << "Suara dalam benak Anda: \"Hanya yang pantas... yang boleh membawa cahaya...\"\n";

    waitForNext();

    serangNagaKuno();

    if (kzl.health == 0) return;


    cout << "Setelah pertarungan yang menguji nyawa dan keberanian...\n";
    cout << "Tubuh naga itu runtuh perlahan dan berubah menjadi energi sihir murni.\n";
    cout << "Anda mencabut pedang Elarion dari altar. Energi cahaya menyelimuti Anda.\n";
    cout << "[Anda memperoleh: Pedang Pahlawan - Elarion]\n";
    kzl.insertweapon(new weapon("Elarion", 45000, 40000, false));

    waitForNext();

    cout << "Suara Ardelia melalui kristal komunikasi:\n";
    cout << "\"Kau... berhasil menemukan Elarion? Itu... benar-benar senjata pahlawan legendaris.\"\n";
    cout << "Ardelia: \"Kalau begitu... mungkin takdir memang memilihmu untuk melawan Raja Iblis.\"\n";

    waitForNext();

    cout << "Cahaya dari pedang itu membelah kabut hutan, membuka jalan baru...\n";
    cout << "Namun... di kejauhan, bayangan besar menatap dari balik celah dimensi...\n";
    cout << "Sebuah kekuatan jauh lebih besar sedang menunggu...\n";

    waitForNext();
    kzl.elarion = true;
}
// Istana Raja Iblis
void event1IstanaRajaIblis(int level) {
    cout << "\nKabut hitam menyelimuti langit, dan angin dingin membawa bisikan penderitaan...\n";
    cout << "Anda berdiri di depan gerbang megah dari obsidian—menjulang tinggi, bengkok oleh sihir kegelapan.\n";
    cout << "Ini adalah Istana Raja Iblis... pusat segala kehancuran yang melanda dunia.\n";

    waitForNext();

    if (kzl.elarion == false && level < 50) {
        cout << "Aura gelap di sekitar istana terlalu pekat...\n";
        cout << "Tubuh Anda gemetar, dan energi sihir Anda terasa terkunci.\n";
        cout << "Anda belum cukup kuat untuk menghadapi kegelapan ini. Kembalilah setelah memperkuat diri.\n";
        return;
    }

    cout << "Ardelia berdiri di sampingmu, jubahnya berkibar oleh angin sihir.\n";
    cout << "Ardelia: \"Kita... benar-benar sampai di sini. Tak kusangka, kita akan menghadapi akhir bersama.\"\n";
    cout << "Ardelia: \"Apa kau siap...?\"\n";

    waitForNext();

    cout << "Anda memandang langit merah darah di atas istana.\n";
    cout << "Kenangan masa latihan, senyum teman, dan pengorbanan yang terjadi di perjalanan... semuanya bermuara di sini.\n";
    cout << "\"Aku sudah memutuskan. Dunia ini layak mendapat harapan baru.\"\n";

    waitForNext();

    cout << "Anda menggenggam pedang Elarion erat-erat. Cahaya dari bilahnya menembus kabut kelam.\n";
    kzl.searchweaponElarion("Elarion");
    cout << "Langkah demi langkah, Anda dan Ardelia berjalan menyusuri aula panjang istana, dipenuhi patung iblis dan api ungu.\n";

    waitForNext();

    cout << "Di ujung ruangan singgasana... duduk makhluk raksasa bersayap hitam, bertanduk, dengan mata menyala merah.\n";
    cout << "[Raja Iblis Azaroth - The Endbringer]\n";
    cout << "Azaroth: \"Jadi ini cahaya terakhir yang dikirim dunia padaku...? Menyedihkan.\"\n";
    cout << "Azaroth: \"Mari kubakar harapan kalian dan kukubur bersama dunia ini.\"\n";

    waitForNext();

    cout << "Musik perang berkumandang...\n";
    cout << "Ardelia berdiri di belakang Anda, tangannya bersinar dengan sihir terlarang.\n";
    cout << "Ardelia: \"Bersama. Kali ini... kita lawan ini bersama.\"\n";

    waitForNext();

    serangRajaIblisdenganArdelia();
    if (kzl.health == 0) return;

    cout << "Serangan akhir dimulai. Kalian menembakkan gelombang sihir dan mengayunkan pedang secara bersamaan.\n";
    cout << "Azaroth terengah engah.\n";

    waitForNext();

    cout << "Azaroth mengangkat tangannya. Bola energi hitam pekat muncul dan langsung diluncurkan ke arah kalian!\n";
    cout << "Ardelia: \"AWAS!\"\n";
    cout << "Dia mendorongmu ke belakang—dan menerima seluruh serangan itu seorang diri...\n";

    waitForNext();

    cout << "Tubuh Ardelia terpental keras dan menghantam dinding istana. Darah mengalir dari mulutnya.\n";
    cout << "Kau berlari ke arahnya...\n";

    waitForNext();

    cout << "Ardelia (terengah): \"Aku... minta maaf... Sepertinya... aku tak bisa melanjutkan bersamamu...\"\n";
    cout << "Ardelia: \"Tapi... jangan menyerah... Aku percaya padamu...\"\n";

    waitForNext();

    cout << "Matanya perlahan tertutup. Tangannya terkulai lemah.\n";
    cout << "Duniamu seolah runtuh. Seseorang yang kau lindungi... pergi di depan matamu.\n";

    waitForNext();

    cout << "Suara Azaroth menggema: \"Itulah nasib mereka yang menentang kegelapan. Kau berikutnya.(Azaroth memulai fase kedua)\"\n";
    cout << "Tiba-tiba tubuhmu bergetar hebat. Aura putih keemasan mulai membakar dari dalam dirimu.\n";
    cout << "Kenangan bersama Ardelia, tekad masa kecilmu, dan kekuatan hatimu memicu sesuatu yang tersegel selama ini...\n";

    waitForNext();

    cout << "Sistem: 'Kekuatan Terpendam Aktif — Mode Ascension: Awakening Hero Form'\n";
    cout << "Pedang Elarion menyala sepuluh kali lebih terang, dan sihirmu memanifestasi sebagai sayap cahaya di punggungmu.\n";
    cout << "\"AZAROTH!! ATAS NAMA ARDELIA... AKU AKAN MENGHANCURKANMU!!\"\n";

    waitForNext();
    int att = kzl.attack;
    int mag = kzl.magicdamage;
    int def = kzl.defense;
    int he = kzl.health;
    int mp = kzl.magicpoint;
    kzl.maxhealth +=1000000;
    kzl.maxmagicpoint +=10000;
    kzl.magicdamage += 74301;
    kzl.attack +=84900;
    kzl.health +=500000;
    kzl.magicpoint += 10000;
    kzl.defense += 25000;

    cout << "Health : dari " << he << " Menjadi -> " << kzl.health << endl;
    cout << "Defense : dari " << def << " Menjadi -> "  << kzl.defense << endl;
    cout << "Attack : dari " << att << " Menjadi -> "  << kzl.attack << endl;
    cout << "Magic Damage : dari " << mag << " Menjadi -> "  << kzl.magicdamage << endl;
    cout << "Magic Point : dari " << mp << " Menjadi -> "  << kzl.magicpoint << endl;

    cout << "Pertarungan terakhir dimulai... kekuatan penuh vs kehancuran murni.\n";


    serangRajaIblis();
    if (kzl.health == 0) return;

    cout << "\nDengan satu tebasan terakhir, pedang Elarion menyapu seluruh kegelapan yang menyelimuti dunia...\n";
    cout << "Tubuh Raja Iblis Azaroth terpecah oleh cahaya suci, menjerit saat kekuatannya hancur berkeping-keping.\n";
    cout << "Azaroth: \"T-tidak... ini mustahil... aku... abadi...\"\n";
    cout << "Suara itu memudar... dan akhirnya, senyap.\n";

    waitForNext();

    cout << "Langit di atas Istana Iblis mulai bersih. Awan gelap yang selama ini membungkus dunia perlahan memudar.\n";
    cout << "Cahaya matahari pertama dalam puluhan tahun menerobos reruntuhan istana...\n";

    waitForNext();

    cout << "Kau terhuyung, tubuhmu lelah, lututmu menyentuh lantai batu. Tapi hatimu tahu... segalanya telah berakhir.\n";
    cout << "Kau menatap ke arah tubuh Ardelia, yang diam di pojok ruangan...\n";

    waitForNext();

    cout << "Perlahan kau melangkah ke arahnya. Duduk di sampingnya. Menggenggam tangannya yang sudah dingin.\n";
    cout << "\"Ardelia... kita menang. Dunia bebas. Kau berhasil...\"\n";
    cout << "Sebuah angin lembut berhembus... dan untuk sesaat, kau merasa seperti dia sedang tersenyum...\n";

    waitForNext();

    cout << "Tiba-tiba, sebuah cahaya hangat menyelubungi tubuh Ardelia.\n";
    cout << "Suara lembut terdengar: \"Terima kasih telah mengorbankan segalanya demi dunia...\"\n";
    cout << "Cahaya itu menyerap tubuhnya dan menghilang ke langit — seperti jiwa yang kembali ke tempat asalnya.\n";

    waitForNext();
    kzl.eventIstanaRajaIblis.pop();
    return;
}



void jalankanEvent(string lokasi) {
    if (lokasi == "Rumah") {
        event1Rumah();

    } else if (lokasi == "Ibu Kota") {
        if (quest == true && kzl.eventIbuKota.size() == 2) {
            event1IbuKota(); 
            kzl.eventIbuKota.pop();

        } else if (kzl.mengalahkanrajaiblis == true && kzl.eventIbuKota.size() == 1){ 
            event2IbuKota();
            kzl.eventIbuKota.pop();
        }
    } else if (lokasi == "Akademi Hero") {
        if (kzl.eventAkademiHero.size() == 2){ 
            event1AkademiHero();
            kzl.eventAkademiHero.pop();
        } else {
            return;
        }
    } else if (lokasi == "Hutan Kegelapan") {
        cout << "Masuk Lebih dalam?\n1. Ya\n2. Tidak\n";
        int pilih = 0;
        cin >> pilih;

        if (pilih == 1) {
            if (kzl.level > 40 && kzl.eventHutanKegelapan.size() == 2) {
                event2HutanKegelapan(kzl.level);
            } else {
                event1HutanKegelapan(kzl.level);
            }
        } else {
            event1HutanKegelapan(kzl.level);
        }
    }else if (lokasi == "Istana Raja Iblis") {
        if (kzl.level > 40 && kzl.elarion == true && kzl.eventIstanaRajaIblis.size() == 2) {
            event1IstanaRajaIblis(kzl.level);
            
        } else{
            return;
        }
    }
}
void jelajahiKota() {
    int pilihan = 0;
    do {
        cout << "\n--- Anda sekarang berada di: " << kzl.position << " ---\n";
        
        jalankanEvent(kzl.position);
        if (kzl.health == 0) break;
        cout << "Mau Pergi Kemana?\n";
        // Tampilkan hanya kota yang terhubung langsung
        int currentIndex = findCityIndex(kzl.position);
        EdgeNode* current = cities[currentIndex].adjacencyList;
        int opsi = 1;
        string opsiNama[MAX_CITY];
        while (current != nullptr) {
            cout << opsi << ". " << cities[current->destinationIndex].name << endl;
            opsiNama[opsi] = cities[current->destinationIndex].name;
            ++opsi;
            current = current->next;
        }
        cout << "0. Keluar\n10. Fast Travel\n";
        cout << "Pilihan: ";
        cin >> pilihan;
        if (pilihan == 10){
            cout << "Kemana?\n";
            cout << "Rumah?\n";
            cout << "Ibu Kota?\n";
            cout << "Akademi Hero?\n";
            cout << "Hutan Kegelapan?\n";
            cout << "Istana Raja Iblis?\n";
            cout << "Masukkan Text : ";
            string tujuan;
            cin.ignore();
            getline(cin, tujuan);
            fastTravel(kzl.position, tujuan);
            kzl.position = tujuan;
        }
        else if (pilihan == 0) {
            cout << "Keluar dari penjelajahan.\n";
            break;
        }
        else if (pilihan > 0 && pilihan < opsi) {
            kzl.position = opsiNama[pilihan];
            cout << "Anda Mengunjungi " << kzl.position << endl;
        } else {
            cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 0 && kzl.health != 0);
}


int main(){
    // Buat kota
    addCity("Rumah");
    addCity("Akademi Hero");
    addCity("Hutan Kegelapan");
    addCity("Ibu Kota");
    addCity("Istana Raja Iblis");

    // Buat jalur antar kota
    addEdge("Rumah", "Akademi Hero", 5);
    addEdge("Akademi Hero", "Hutan Kegelapan", 7);
    addEdge("Hutan Kegelapan", "Istana Raja Iblis", 9);
    addEdge("Rumah", "Ibu Kota", 8);
    addEdge("Ibu Kota", "Hutan Kegelapan", 6);

    root1->left = child1;
    root1->right = child2;
    child1->left = child1_1;
    child1->right = child1_2;
    child2->left = child2_1;
    child2->right = child2_2;

    root2->left = magchild1;
    root2->right = magchild2;
    magchild1->left = magchild1_1;
    magchild1->right = magchild1_2;
    magchild2->left = magchild2_1;
    magchild2->right = magchild2_2;
    int pilihan = 1;
    int pilihan2 = 1;

    cout << "Hello Adventurer Welcome to the game" << endl;
    waitForNext();
    cout << "Make A Name : ";
    string name;
    getline(cin, name);
    kzl.name = name;
    cout << "First Distribute your Status Point +20 STATPOINT" << endl;
    kzl.statuspoint = 20;
    kzl.bukastatus();
    kzl.insertweapon(new weapon("Pedang Kayu", 10, 0, false));
    kzl.insertarmor(new armor("Common Clothes", 100, 10, false));
    kzl.insertpotion(new potion("Mini Health Potion", 200, 50));
    while (kzl.health != 0 && pilihan != 0){
        cout << "Welcome Adventurer"  << endl;
        if (kzl.level > 50 && quest == false && kzl.position != "Ibu Kota"){
            cout << "===ALERT QUEST!!===\nPergi ke Ibu Kota untuk berbicara dengan Raja" << endl;
            quest = true;
        }
        cout << "1. Jelajahi Kota\n2. Status\n3. Buka Inventory\n4. Unlock Skills\n0. Keluar" << endl;
        cin >> pilihan;
        string cari;
        switch (pilihan)
        {
        case 1:
            jelajahiKota();
            break;
        case 2:
            kzl.bukastatus();
            break;
        case 3:
            do
            {
                kzl.displayall();
                cout << "1. Cari Senjata\n2. Cari Armor\n3. Cari Potion\n4. Tampilkan Urut\n0. Keluar" << endl;
                cin >> pilihan2;
                switch (pilihan2)
                {
                case 1:
                    cin.ignore();
                    getline(cin, cari);
                    kzl.searchweapon(cari);
                    break;
                case 2:
                    cin.ignore();
                    getline(cin, cari);
                    kzl.searcharmor(cari);
                    break;
                case 3:
                    cin.ignore();
                    getline(cin, cari);
                    kzl.searchpotion(cari);
                    break;
                case 4:
                    kzl.urut();
                    break;
                default:
                    break;
                }
            } while (pilihan2 != 0);
            


            break;
        case 4:
            kzl.unlockskill(root1, root2);
        default:
            break;
        }
    }
    



    return 0;
    
}