#include "initialize.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <set>

Initialize::Initialize(const std::vector<node>& nodes, const std::vector<element>& elements, const std::vector<bc>& bc_arr, int order)
    : nodes(nodes), elements(elements), bc_arr(bc_arr), order(order), count_dc(0) {}

void Initialize::startInitializing() {
    handleBoundaryConditions();
    assembleAmat();
}

void Initialize::handleBoundaryConditions() {
    for (const auto& temp : bc_arr) {
        if (temp.dc_x1 == 1) {
            int dof = 2 * temp.node1;
            if (std::find(rest_dispdof.begin(), rest_dispdof.end(), dof) == rest_dispdof.end()) {
                rest_dispdof.push_back(dof);
                knwndisp.push_back(temp.dispvec[0]);
                count_dc++;
            }
        }
        if (temp.dc_y1 == 1) {
            int dof = 2 * temp.node1 + 1;
            if (std::find(rest_dispdof.begin(), rest_dispdof.end(), dof) == rest_dispdof.end()) {
                rest_dispdof.push_back(dof);
                knwndisp.push_back(temp.dispvec[1]);
                count_dc++;
            }
        }
        if (temp.dc_x2 == 1) {
            int dof = 2 * temp.node2;
            if (std::find(rest_dispdof.begin(), rest_dispdof.end(), dof) == rest_dispdof.end()) {
                rest_dispdof.push_back(dof);
                knwndisp.push_back(temp.dispvec[2]);
                count_dc++;
            }
        }
        if (temp.dc_y2 == 1) {
            int dof = 2 * temp.node2 + 1;
            if (std::find(rest_dispdof.begin(), rest_dispdof.end(), dof) == rest_dispdof.end()) {
                rest_dispdof.push_back(dof);
                knwndisp.push_back(temp.dispvec[3]);
                count_dc++;
            }
        }
    }

    std::sort(rest_dispdof.begin(), rest_dispdof.end());
}

void Initialize::assembleAmat() {
    GQVandW GQdata = getWeightAndValues(order);
    int numnode = nodes.size();
    int bndsdes = bc_arr.size();
    int colm = 8 * numnode + count_dc;
    int row = 7 * bndsdes + count_dc;

    Amat.resize(row, std::vector<double>(colm, 0));
    Fvector.resize(row, 0);

    int rowindx = 0;
    for (const auto& temp : bc_arr) {
        RetBC res = boundry_condition_fun(temp, GQdata, order);
        const auto& tempkmat = res.Kmat;
        const auto& tempFmat = res.Fmat;

        std::vector<int> colindx_sts(12);
        for (int i = 0; i < 6; ++i) {
            colindx_sts[i] = 2 * numnode + 6 * temp.node1 + i;
            colindx_sts[i + 6] = 2 * numnode + 6 * temp.node2 + i;
        }

        if (temp.dc_x1 == 0 && temp.dc_x2 == 0 && temp.dc_y1 == 0 && temp.dc_y2 == 0) {
            for (int a = 0; a < 7; ++a) {
                for (int b = 0; b < 12; ++b) {
                    Amat[rowindx + a][colindx_sts[b]] = tempkmat[a][b];
                }
                for (int c = 0; c < 4; ++c) {
                    Fvector[rowindx + a] += tempFmat[a][c] * temp.tractvec[c];
                }
            }
            rowindx += 7;
        } else {
            std::vector<int> colindx_trct;
            std::vector<int> ddof;
            if (temp.dc_x1 == 1) ddof.push_back(2 * temp.node1);
            if (temp.dc_y1 == 1) ddof.push_back(2 * temp.node1 + 1);
            if (temp.dc_x2 == 1) ddof.push_back(2 * temp.node2);
            if (temp.dc_y2 == 1) ddof.push_back(2 * temp.node2 + 1);

            for (int d : ddof) {
                auto it = std::find(rest_dispdof.begin(), rest_dispdof.end(), d);
                if (it != rest_dispdof.end()) {
                    colindx_trct.push_back(std::distance(rest_dispdof.begin(), it));
                }
            }

            for (int a = 0; a < 7; ++a) {
                for (int b = 0; b < 12; ++b) {
                    Amat[rowindx + a][colindx_sts[b]] = tempkmat[a][b];
                }
                for (int c = 0; c < colindx_trct.size(); ++c) {
                    Amat[rowindx + a][8 * numnode + colindx_trct[c]] = -tempFmat[a][c];
                }
            }
            rowindx += 7;
        }
    }

    for (int a = 0; a < count_dc; ++a) {
        Amat[rowindx + a][rest_dispdof[a]] = 1;
        Fvector[rowindx + a] = knwndisp[a];
    }
}

const std::vector<std::vector<double>>& Initialize::getAmat() const {
    return Amat;
}

const std::vector<double>& Initialize::getFvector() const {
    return Fvector;
}
