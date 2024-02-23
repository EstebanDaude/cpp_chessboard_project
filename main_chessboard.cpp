#include "chessboard.h"

int main (int argc, char* argv[]){
    Chessboard chessboard;
    chessboard.print_chessboard();
    

    while (!chessboard.test_checkmate()){
        cout << chessboard.turn <<"'s turn"<< endl;
        try {
        int x1;
        int y1;
        int x2;
        int y2;

        read_input (x1, y1, x2, y2);

        Piece* p = chessboard.get_piece(x1, y1);
        
        p->move_is_valid(x1,y1,x2,y2, chessboard.pieces_on_path(x1,y1,x2,y2), chessboard.color_valid(x1,y1,x2,y2));
        chessboard.move(x1, y1, x2, y2);
        chessboard.print_chessboard();
        }
        catch (MoveError e){
            e.print_error();
            cout << "play again" << endl;
            continue;
        }
        chessboard.switch_turn();
        
        if (chessboard.test_check()){
            cout << chessboard.turn << " est en echec au roi" << endl;
        }
    }

    cout << chessboard.turn << " est en echec et mat, victoire de " << switch_color(chessboard.turn) << endl;

    return 0;
}