#include <iostream>
#include <string>
#include <map>

using namespace std;

class MoveError { //Exception qui servira pour les moves illegaux mais on veut pouvoir specifier
public :
    string message;
    MoveError (string m){
    message = m;
    }
    void print_error(){
        cout << message << endl;
    }
};

//On créer une classe générale abstraite pour les pieces
class Piece{
protected :
    string couleur; // Trois couleurs : N,B et NoneCouleur
public :
    virtual string printPiece () = 0;
    virtual bool move_is_valid (int x1, int y1, int x2, int y2, bool p_o_p, int c_v) = 0; // p_o_p = resultat de pieces_on_path, c_v = resultat du color_valid (cf plus loin)
    string get_couleur(){
        return couleur;
    };

    Piece(){}

    ~Piece () {}

    Piece(string c) {
        couleur = c;
    }

    /*Quelques fonctions pour traiter des cas particuliers du pion*/
    virtual bool premier_coup(int x1, int y1, int x2, int y2, bool p_o_p, int c_v){
        throw MoveError("illegal move");
    }
    virtual bool prise(int x1, int y1, int x2, int y2, bool c_v){
        throw MoveError("illegal move");
    }

};



//Puis on utilise de l'heritage de classe pour faire chaque type de piece avec ses regles de jeu
class Roi : public Piece{
public :
    virtual string printPiece (){
        if (couleur == "N"){
            return "r";
        }
        else{
            return"R";
        }
    };

    virtual bool move_is_valid(int x1, int y1, int x2, int y2, bool p_o_p, int c_v){
        if ((x1 > 7) || (x2 > 7) || (y1 > 7) || (y2 > 7) || (x1 < 0) || (x2 < 0) || (y1 < 0) || (y2 < 0)){
            throw MoveError ("out of bounds");
        }
        else if ((x1 == x2) && (y1 == y2)) {
            throw MoveError ("no move");
        }
        else if ((abs(x2-x1) < 2) && (abs(y2-y1) < 2) && p_o_p && (c_v > 0)){
            return true;
        }
        else{
            throw MoveError ("illegal move");
        }
    };

    Roi(string c) {
        couleur = c;
    }

    ~Roi(){}
};

class Dame : public Piece{
public :
    virtual string printPiece (){
        if (couleur == "N"){
            return "d";
        }
        else{
            return"D";
        }
    };

    virtual bool move_is_valid(int x1, int y1, int x2, int y2, bool p_o_p, int c_v){
        if ((x1 > 7) || (x2 > 7) || (y1 > 7) || (y2 > 7) || (x1 < 0) || (x2 < 0) || (y1 < 0) || (y2 < 0)){
            throw MoveError ("out of bounds");
        }
        else if ((x1 == x2) && (y1 == y2)) {
            throw MoveError ("no move");
        }
        else if (((x1 == x2) || (y1 == y2) || (abs(y2 - y1) == abs(x2 - x1))) && p_o_p && (c_v > 0)){
            return true;
        }
        else{
            throw MoveError ("illegal move");
        }
    };

    Dame(string c) {
        couleur = c;
    }

    ~Dame(){}
};

class Fou : public Piece{
public : 
    virtual string printPiece (){
        if (couleur == "N"){
            return "f";
        }
        else{
            return"F";
        }
    };

    virtual bool move_is_valid(int x1, int y1, int x2, int y2, bool p_o_p, int c_v){
        if ((x1 > 7) || (x2 > 7) || (y1 > 7) || (y2 > 7) || (x1 < 0) || (x2 < 0) || (y1 < 0) || (y2 < 0)){
            throw MoveError ("out of bounds");
        }
        else if ((x1 == x2) && (y1 == y2)) {
            throw MoveError ("no move");
        }
        else if ((abs(y2 - y1) == abs(x2 - x1)) && p_o_p && (c_v > 0)){
            return true;
        }
        else{
            throw MoveError ("illegal move");
        }
    };

    Fou(string c) {
        couleur = c;
    }

    ~Fou(){}
};

class Cavalier : public Piece{
public : 
    virtual string printPiece (){
        if (couleur == "N"){
            return "c";
        }
        else{
            return"C";
        }
    };

    virtual bool move_is_valid(int x1, int y1, int x2, int y2, bool p_o_p, int c_v){
        if ((x1 > 7) || (x2 > 7) || (y1 > 7) || (y2 > 7) || (x1 < 0) || (x2 < 0) || (y1 < 0) || (y2 < 0)){
            throw MoveError ("out of bounds");
        }
        else if ((x1 == x2) && (y1 == y2)) {
            throw MoveError ("no move");
        }
        else if ((((abs(x2 - x1) == 2) && (abs(y2 - y1) == 1))||((abs(x2 - x1) == 1) && (abs(y2 - y1) == 2))) && (c_v > 0)){ //Le cavalier saute par dessus les pieces (pas besoin de p_o_p)
            return true;
        }
        else{
            throw MoveError ("illegal move");
        }
    };

    Cavalier(string c) {
        couleur = c;
    }

    ~Cavalier(){}
};

class Tour : public Piece{
public : 
    virtual string printPiece (){
        if (couleur == "N"){
            return "t";
        }
        else{
            return"T";
        }
    };

    virtual bool move_is_valid(int x1, int y1, int x2, int y2, bool p_o_p, int c_v){
        if ((x1 > 7) || (x2 > 7) || (y1 > 7) || (y2 > 7) || (x1 < 0) || (x2 < 0) || (y1 < 0) || (y2 < 0)){
            throw MoveError ("out of bounds");
        }
        else if ((x1 == x2) && (y1 == y2)) {
            throw MoveError ("no move");
        }
        else if (((x1 == x2) || (y1 == y2)) && p_o_p && (c_v > 0)){
            return true;
        }
        else{
            throw MoveError ("illegal move");
        }
    };

    Tour(string c) {
        couleur = c;
    }

    ~Tour(){}
};

class Pion : public Piece{
public : 
    virtual string printPiece (){
        if (get_couleur() == "N"){
            return "p";
        }
        else{
            return"P";
        }
    };

    virtual bool move_is_valid(int x1, int y1, int x2, int y2, bool p_o_p, int c_v){
        if ((x1 > 7) || (x2 > 7) || (y1 > 7) || (y2 > 7) || (x1 < 0) || (x2 < 0) || (y1 < 0) || (y2 < 0)){
            throw MoveError ("out of bounds");
        }
        else if ((x1 == x2) && (y1 == y2)) {
            throw MoveError ("no move");
        }
        else if ((x2 - x1 == 1) && (y1 == y2) && (couleur == "N") && p_o_p && (c_v == 1)){ //Cas standard
            return true;
        }
        else if ((x1 - x2 == 1) && (y1 == y2) && (couleur == "B") && p_o_p && (c_v == 1)){ //Cas standard
            return true;
        }
        else if ((x1 == 1) && (x2 - x1 == 2) && (y1 == y2) && (couleur == "N") && (c_v > 0) && p_o_p){ //Avance de 2 cases au départ
            return true;
        }
        else if ((x1 == 6) && (x1 - x2 == 2) && (y1 == y2) && (couleur == "B") && (c_v > 0) && p_o_p){ //Avance de 2 cases au départ
            return true;
        }
        else if ((((x2 - x1 == 1) && (y2 - y1 == 1))||((x2 - x1 == 1) && (y2 - y1 == -1))) && (couleur == "N") && (c_v == 2)){ //Prise en diagonale
            return true;
        }
        else if ((((x1 - x2 == 1) && (y2 - y1 == 1))||((x1 - x2 == 1) && (y2 - y1 == -1))) && (couleur == "B") && (c_v == 2)){ //Prise en diagonale
            return true;
        }
        else{
            throw MoveError("illegal move");
        }
    };

    Pion(string c) {
        couleur = c;
    }

    ~Pion(){}
};

//On ajoute une classe NonePiece pour les cases vides du plateau
class NonePiece : public Piece{
public :
    virtual string printPiece (){
        return "*";
    };
    
    NonePiece (string c){
        couleur = c;
    }

    ~NonePiece(){}
    
    virtual bool move_is_valid (int x1, int y1, int x2, int y2, bool p_o_p, int c_v){
        throw MoveError ("no piece on this square"); //Ne devrait pas etre utile si color_valid fait son travail
    };
};

/*Fonction toute simple qui permet juste d'inverser les couleurs N et B, qui sera utilisee pour changer de tour*/
string switch_color(string s){
    if (s == "N"){
        return "B";
    }
    else{
        return "N";
    }
}

/*Classe qui modelise le plateau avec ses pieces dessus*/
class Chessboard{
public :
    Piece* board[8][8];
    string turn;
    Chessboard(){
        turn = "B";
        //On remplit les pieces cote noir
        for (int i = 0; i < 8; i++){
            board[1][i] = new Pion ("N");
        }
        board[0][0] = new Tour ("N");
        board[0][1] = new Cavalier ("N");
        board[0][2] = new Fou ("N");
        board[0][3] = new Dame ("N");
        board[0][4] = new Roi ("N");
        board[0][5] = new Fou ("N");
        board[0][6] = new Cavalier ("N");
        board[0][7] = new Tour ("N");

        //On remplit les pieces cote blanc
        for (int i = 0; i < 8; i++){
            board[6][i] = new Pion ("B");
        }
        board[7][0] = new Tour ("B");
        board[7][1] = new Cavalier ("B");
        board[7][2] = new Fou ("B");
        board[7][3] = new Dame ("B");
        board[7][4] = new Roi ("B");
        board[7][5] = new Fou ("B");
        board[7][6] = new Cavalier ("B");
        board[7][7] = new Tour ("B");
        
        //Puis on met des None au centre
        for (int i = 2; i < 6; i++){
            for (int j = 0; j < 8; j++){
                board[i][j] = new NonePiece("NoneCouleur");
            }
        }
    }

    ~Chessboard(){
        for (int i = 0; i < 8; i++){
            for (int j = 0; j < 8; j++){
                delete board[i][j];
            }
        }
    }
    
    void print_chessboard () {
        cout << "   a b c d e f g h" << endl;
        cout << endl;
        for (int i = 0; i<8; i++){
            cout << 8 - i << "  ";
            for (int j = 0; j<8;j++){
                cout << board[i][j]->printPiece() << " " ;
            }
            cout << "  " << 8 - i << endl;
        }
        cout << endl;
        cout << "   a b c d e f g h" << endl;
    }
    
    Piece* get_piece (int x, int y){
        return board[x][y];
    }

    /*Fonction qui permet de changer de tour*/
    void switch_turn(){
        turn = switch_color(turn);
    }
    /*Fonction qui effectue le move, apres que toutes les modifs ait ete faites*/
    void move (int x1, int y1, int x2, int y2){
        board[x2][y2] = board[x1][y1];
        board[x1][y1] = new NonePiece("NoneCouleur");
    }

    /*Fonction qui teste s'il y a une piece sur le chemin (move invalide); j'admet que son ecriture est tres artisanale...*/
    bool pieces_on_path (int x1, int y1, int x2, int y2) {
        if (x1 == x2 && y2 > y1){ //Pour un mouvement vertical vers le bas
            for (int i = y1+1; i < y2; i++){
                if (board[x1][i]->get_couleur() != "NoneCouleur"){
                    return false;
                    break;
                }
            }
        }
        else if (x1 == x2 && y2 < y1){ //Pour un mouvement vertical vers le haut
            for (int i = y2+1; i < y1; i++){
                if (board[x1][i]->get_couleur() != "NoneCouleur"){
                    return false;
                    break;
                }
            }
        }
        else if (y1 == y2 && x2 > x1){ //Pour un mouvement horizontal vers la droite
            for (int i = x1+1; i < x2; i++){
                if (board[i][y1]->get_couleur() != "NoneCouleur"){
                    return false;
                    break;
                }
            }
        }
        else if (y1 == y2 && x1 > x2){ //Pour un mouvement horizontal vers la gauche
            for (int i = x2+1; i < x1; i++){
                if (board[i][y1]->get_couleur() != "NoneCouleur"){
                    return false;
                    break;
                }
            }
        }
        else if (abs(x2-x1) == abs (y2-y1) && x2 > x1 && y2 > y1){ //Pour un mouvement en diagonale montante vers la droite
            for (int i = x1 + 1 ; i < x2; i++){
                for (int j = y1 + 1; j < y2; j++){
                    if ((board[i][j]->get_couleur() != "NoneCouleur") && ((i - x1)*(x2-x1) == (j-y1)*(y2-y1))){
                        return false;
                        break;
                    }
                }
            }
        }
        else if (abs(x2-x1) == abs (y2-y1) && x2 > x1 && y1 > y2){ //Pour un mouvement en diagonale montante vers la gauche
            for (int i = x1 + 1 ; i < x2; i++){
                for (int j = y2 + 1; j < y1; j++){
                    if ((board[i][j]->get_couleur() != "NoneCouleur") && ((i - x1)*(x2-x1) == (j-y1)*(y2-y1))){
                        return false;
                        break;
                    }
                }
            }
        }
        else if (abs(x2-x1) == abs (y2-y1) && x1 > x2 && y2 > y1){ //Pour un mouvement en diagonale descendante vers la droite
            for (int i = x2 + 1 ; i < x1; i++){
                for (int j = y1 + 1; j < y2; j++){
                    if ((board[i][j]->get_couleur() != "NoneCouleur") && ((i - x1)*(x2-x1) == (j-y1)*(y2-y1))){
                        return false;
                        break;
                    }
                }
            }
        }
        else if (abs(x2-x1) == abs (y2-y1) && x1 > x2 && y1 > y2){ //Pour un mouvement en diagonale descendante vers la gauche
            for (int i = x2 + 1 ; i < x1; i++){
                for (int j = y2 + 1; j < y1; j++){
                    if ((board[i][j]->get_couleur() != "NoneCouleur") && ((i - x1)*(x2-x1) == (j-y1)*(y2-y1))){
                        return false;
                        break;
                    }
                }
            }
        }
        return true;
    }

    /*Fonction qui teste si la piece sur la case de depart est bien de la couleur du joueur et si l'eventuelle piece sur la case d'arrivee est
    bien de la couleur adversaire, ou vide (sinon move invalide)*/
    int color_valid (int x1, int y1, int x2, int y2){
        string c1 = get_piece(x1,y1)->get_couleur();
        string c2 = get_piece(x2,y2)->get_couleur();
        if ((c1 == turn) && (c2 != turn)){
            if ((c1 == "N") && (c2 == "B")){
                return 2;
            }
            if ((c1 == "B") && (c2 == "N")){
                return 2;
            }
            else {
                return 1;
            }
        }
        else {
            return 0;
        }
    }

/*Fonction qui test si le joueur du tour en cours est en echec*/
    bool test_check(){
        bool r = false;
        string adv = switch_color(turn);
        for (int i = 0; i<8; i++){
            for (int j = 0; j<8; j++){
                if (board[i][j]->get_couleur() == adv){
                    for(int di =0; di < 8; di++){
                        for(int dj = 0; dj < 8; dj++){
                            try{ 
                            board[i][j]->move_is_valid(i,j,di,dj,pieces_on_path(i,j,di,dj),true);
                            if (((board[di][dj]->printPiece() == "R") || (board[di][dj]->printPiece() == "r")) && (board[di][dj]->get_couleur() == turn)){
                                r = true;
                            }}
                            catch(MoveError){}
                        }
                    }
                }
            }
        }
    return r;
    }

    /*Fonction qui test si le joueur est en echec et mat pour arreter le jeu*/
    bool test_checkmate(){
        if (test_check()){
            //On cherche la position du roi
            int xr;
            int yr;
            for(int i = 0; i <8; i++){
                for (int j = 0 ; j < 8; j++){
                    if (((board[i][j]->printPiece() == "R") || (board[i][j]->printPiece() == "r")) && (board[i][j]->get_couleur() == turn)){
                        xr = i;
                        yr = j;
                    }
                }
            }

            //Puis on regarde s'il reste en echec avec tout les mouvements qu'il peut faire (i.e se deplacer d'une case dans toutes les directions)
            int r = true;
            for (int i = -1; i<2; i++){
                for (int j = -1; j<2; j++){
                    try{
                        if ((xr > 7) || (xr+i > 7) || (yr > 7) || (yr+j > 7) || (xr < 0) || (xr+i < 0) || (yr < 0) || (yr+j < 0)){
                            throw MoveError ("out of bounds");
                        }
                        else if ((xr == xr+i) && (yr == yr+j)) {
                            throw MoveError ("no move");
                        }
                        else{
                            board[xr][yr]->move_is_valid(xr,yr,xr+i,yr+j, pieces_on_path(xr,yr,xr+i,yr+j), color_valid(xr,yr,xr+i,yr+j));
                            Piece* mem = get_piece(xr+i,yr+j);
                            move(xr,yr,xr+i, yr+j); //On fait le move pour le test
                            if (!test_check()){
                                r = false;
                            }
                            move(xr+i, yr+j, xr, yr); //puis on revient en position initiale
                            board[xr+i][yr+j] = mem;
                        }
                    }
                    catch(MoveError){}
                }
            }
            return r;
        }
        else{
            return false;
        }
    }

};

/*On templatise cette fonction pour les besoins de l'exercice*/
template<typename T>
int letter_to_number (T l){
    map<char, int> d = {{'a',0,}, {'b',1,}, {'c',2,}, {'d',3,}, {'e',4,}, {'f',5,}, {'g',6,}, {'h',7,}};
    try{
        return d[l];
    }
    catch(out_of_range){
        throw MoveError("out of bounds");
    }
}
/*Fonction qui sera appelee a chaque tour pour lire l'entree du joueur et la mettre au bon format pour etre utilisee par le programme*/
void read_input(int& x1, int& y1, int& x2, int& y2){
    string s;
    int x;
    cout << "Enter your move (with the pattern a1b2) : ";
    cin >> s;
    if (s.size() == 4){
        y1 = letter_to_number<char>(s[0]);
        x = s[1] - '0';
        x1 = 8 - x;
        y2 = letter_to_number<char>(s[2]);
        x = s[3] - '0';
        x2 = 8 - x;
        if ((x1 > 7) || (x2 > 7) || (y1 > 7) || (y2 > 7)){
            throw MoveError ("out of bounds");
        }
    }
    else{
        throw MoveError("invalid entry");
    }
}

