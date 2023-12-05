#include <iostream>
#include <iomanip>
#include <string>
#include <dirent.h>

using std::cout, std::endl;
using std::setw;
using std::string;

/**
 * @brief Procédure affichant le contenu d'un répertoire passé en paramètre
 * @param[in] source Le nom du répertoire
 */
void ls(const string &source){
    // Déclare un pointeur vers la structure DIR, qui représente un répertoire
    DIR *rep;
    rep = opendir(source.c_str());

    if(!rep) cout << "Répertoire introuvable " << endl;
    else{
        // Déclare un pointeur vers la structure dirent, qui contient des informations sur un élément du répertoire
        dirent *elem;
        elem = readdir(rep); // Lit le premier élément du répertoire

        while(elem){
            cout << elem->d_name << endl;
            elem = readdir(rep);
        }
        closedir(rep);
    }
}

/**
 * @brief Procédure affichant le contenu d'un répertoire ainsi que de ses enfants
 * @param[in] source Le nom du répertoire
 */
void lsr(const string &source){
    DIR *rep;
    rep = opendir(source.c_str());
    if(!rep) cout << "Répertoire introuvable " << endl;
    else{
        dirent *elem;
        while(elem = readdir(rep)){
            if(string (elem->d_name) != "." && string(elem->d_name) != ".."){
                cout << elem->d_name << endl;
                if(elem->d_type == DT_DIR) lsr(source + "/" + elem->d_name);
            }
        }
        closedir(rep);
    }
}

inline void indentation(unsigned i){
    if(i <= 0) return;
    for(unsigned j = 0; j < i; j++){
        cout << std::left << setw(10) << "|";
    }
}

void afficheLsr(const string &source, unsigned i){
    DIR *rep;
    rep = opendir(source.c_str());
    if(!rep) cout << "Répertoire introuvable " << endl;
    else {
        dirent *elem;
        while(elem = readdir(rep)){
            if(string (elem->d_name) != "." && string(elem->d_name) != ".."){
                indentation(i);
                cout << elem->d_name << endl;
                if(elem->d_type == DT_DIR) afficheLsr(source + "/" + elem->d_name, i+1);
            }
        }
        closedir(rep);
    }
}

void find(const string &ch, const string &nomRep){
    DIR *rep;
    rep = opendir(nomRep.c_str());
    if(!rep) cout << "Répertoire introuvable " << endl;
    else {
        dirent *elem;
        while(elem = readdir(rep)){
            string e = elem->d_name;
            if(e.string::find(ch) != string::npos){
                cout << e << endl;
                if(elem->d_type == DT_DIR) find(ch, nomRep + "/" + elem->d_name);
            }
        }
        closedir(rep);
    }
}

void afficheFind(const string &ch, const string &nomRep, unsigned i){
    DIR *rep;
    rep = opendir(nomRep.c_str());
    if(!rep) cout << "Répertoire introuvable " << endl;
    else {
        dirent *elem;
        while(elem = readdir(rep)){
            string e = elem->d_name;
            if(e.string::find(ch) != string::npos){
                indentation(i);
                cout << e << endl;
                if(elem->d_type == DT_DIR) afficheFind(ch, nomRep + "/" + elem->d_name, i+1);
            }
        }
        closedir(rep);
    }
}

void testLS(){
    cout << "testLS" << endl;
    string c{"CMakeFiles"};
    ls(c);
    cout << endl << endl;
}

void testLSR(){
    cout << "testLSR" << endl;
    string c{"CMakeFiles"};
    lsr(c);
    cout << endl << endl;
}

void testAfficheLsr(){
    cout << "test afficheLsr" << endl;
    string c{"CMakeFiles"};
    afficheLsr(c, 0);
    cout << endl << endl;
}

void testFind(){
    cout << "test find" << endl;
    string c{"CMakeFiles"};
    find("o",c);
    cout << endl << endl;
}

void testAfficheFind(){
    cout << "test AfficheFind" << endl;
    string c{"CMakeFiles"};
    afficheFind("o",c, 0);
    cout << endl << endl;
}

int main() {
    testLS();
    testLSR();
    testAfficheLsr();
    testFind();
    testAfficheFind();
    return 0;
}
