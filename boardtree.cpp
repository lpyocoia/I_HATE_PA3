#include"boardtree.h"

BoardTree::BoardTree(const Board& board){
    root = new BoardNode(board);
}

BoardTree::~BoardTree(){
    if(root!=nullptr){
        delete root;
        root = nullptr;
    }   //see if need to clear the child node as well!! (Probably needed)
}

BoardTree* BoardTree::getSubTree(const BoardCoordinate &coords){
    if(root->subTree[coords.row][coords.col].root == nullptr){
        // Board temp = Board(root->board);
        Board temp = root->board;
        if(temp.play(coords)){
            root->subTree[coords.row][coords.col].root = new BoardNode(temp);
            // root->subTree[coords.row][coords.col].root = new BoardNode(root->board);
        }else{
             root->subTree[coords.row][coords.col].root = nullptr;
        }
    }
    // std::cout << "getting subtree: "<< coords.row << ", " << coords.col << std::endl;
    return &root->subTree[coords.row][coords.col];
}

BoardOptimalMove BoardTree::getOptimalMove(const unsigned int depth){
    if(root == nullptr){
        return BoardOptimalMove();
    }
    if(depth == 0 || root->board.isFinished()){
        return BoardOptimalMove(root->board.getBoardScore(), BoardCoordinate(0, 0));
    }
    int estimatedScore = (root->board.getCurPlayer() == X) ? -99999 : 99999;

    BoardOptimalMove bestMove;
    for(int i=0; i<BOARD_SIZE; ++i){
        for(int j=0; j<BOARD_SIZE; ++j){
            BoardCoordinate coords(i,j);
            BoardTree* subtree = this->getSubTree(coords);;
            // if(root->subTree[i][j].root == nullptr){
            //     continue; 
            // }
            BoardOptimalMove childMove = subtree->getOptimalMove(depth - 1);
            // std::cout << "childMove.score = " << childMove.score << std::endl;
            if (childMove.score == ILLEGAL) {
                // If the move is illegal, the subtree corresponds to an invalid move/board, simply skip to the next subtree
                // std::cout << "ILLEGAL" << std::endl;
                continue;
            }
            if(root->board.getCurPlayer() == X && childMove.score > estimatedScore){
                    estimatedScore = childMove.score;
                    bestMove = BoardOptimalMove(estimatedScore, coords);
            }else if(root->board.getCurPlayer() == O && childMove.score < estimatedScore){
                estimatedScore = childMove.score;
                bestMove = BoardOptimalMove(estimatedScore, coords);
            }            
        }
    }
    return bestMove;
}

BoardOptimalMove BoardTree::getOptimalMoveAlphaBeta(const unsigned int depth, int alpha, int beta){

}

