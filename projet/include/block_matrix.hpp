#ifndef BLOCK_MATRIX_H
#define BLOCK_MATRIX_H

#include <block.hpp>
#include <list>
#include <vecteur.hpp>

template <typename M>
class BlockMatrix {

private:

    int nr;
    int nc;
    std::list<Block<M>> val = std::list<Block<M>>();

    // =========================================================================

    static void validateMatrixVectors(std::vector<std::vector<int>> vectors, int n);

public:

    BlockMatrix(int nr, int nc);
    BlockMatrix(const BlockMatrix& blockMatrix);

    void operator=(const BlockMatrix& blockMarix);
    void operator+=(const Block<M>& block);

    void Extract(M &matrix, int l, int r);
    void Extract(M &matrix, const std::vector<std::vector<int>> I);

    void MvProdInv(const Vecteur& x, Vecteur& b);
    void MvProd(const Vecteur& x, Vecteur&  b);
    void MinRes(Vecteur& x, const Vecteur& b);

    // =========================================================================

    const std::list<Block<M>> getBlocks();
    M reconstructMatrix();

    std::vector<std::vector<int>> generateMatrixVectors(int l, int r, int n);
};

#endif // BLOCK_MATRIX_H
