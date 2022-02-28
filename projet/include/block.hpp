#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>
#include <vector>
#include <vecteur.hpp>

template <typename M>
class Block {

private:

    int nr;
    int nc;
    std::vector<int> Ir;
    std::vector<int> Ic;
    M mat;

    // =========================================================================

    static M generateRowMatrix(int height, const std::vector<int>& rowVector);

public:

    Block(int nr, int nc, const std::vector<int>& Ir, const std::vector<int>& Ic);
    Block(const Block& block);

    void operator=(const Block& block);
    void MvProd(const Vecteur& x, Vecteur& b);
    void MvProdInv(const Vecteur& x, Vecteur& b);

    // =========================================================================

    void productLeftMatrix(const Vecteur& x, Vecteur& b);
    void productRightMatrixTranspose(const Vecteur& x, Vecteur& b);

    int getHeight() const;
    int getWidth() const;

    std::vector<int> getLeftVector() const;
    std::vector<int> getRightVector() const;

    void setCenterMatrix(const M& centerMatrix);

    M getMatrix() const;

    M getCenterMatrix() const;
    M getLeftMatrix() const;
    M getRightMatrix() const;
};

#endif // BLOCK_H
