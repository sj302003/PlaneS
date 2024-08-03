#include "constructor.h"
#include "constraints.h"
#include "initialize.h" // Ensure this line is present
#include <fstream>
#include <sstream>
#include <iostream>
#include <set>
#include <algorithm>
#include <numeric>
#include <omp.h>
#include <nlopt.h>

Constructor::Constructor() {};

void Constructor::assembleAmat() {
    std::cout << "numnode: " << numnode << " count_dc: " << count_dc << '\n';
    colm = 8 * numnode + count_dc;
    row = 7 * bndsdes + count_dc;

    std::cout << "column " << colm << " rows " << row << std::endl;
    vector<double> Fvector(row);

    vector<double> temp_Amatrow(colm);
    for (int i = 0; i < row; i++) {
        Amat.push_back(temp_Amatrow);
        Fvector.push_back(0);
        for (int j = 0; j < colm; j++)
            Amat[i][j] = 0;
    }

    int rowindx = 0;
    int tmpindx;
    double tractionvec[4];
    double displvec[4];
    vector<vector<double>> tempkmat;
    vector<vector<double>> tempFmat;
    vector<vector<double>> temptransmat;
    std::cout << "Going to assemble Amat" << std::endl;
    Initialize init; // Create an instance of Initialize
    for (int ab = 0; ab < bndsdes; ab++) {
        vector<int> colindx_sts;
        vector<int> colindx_disp;
        vector<int> colindx_trct;
        vector<int> ddof;
        bc temp = bc_arr[ab];
        RetBC res = init.boundry_condition_fun(temp, GQdata, order); // Use the instance to call the function
        tempkmat = res.Kmat;
        tempFmat = res.Fmat;

        tractionvec[0] = temp.tractvec[0];
        tractionvec[1] = temp.tractvec[1];
        tractionvec[2] = temp.tractvec[2];
        tractionvec[3] = temp.tractvec[3];

        displvec[0] = temp.dispvec[0];
        displvec[1] = temp.dispvec[1];
        displvec[2] = temp.dispvec[2];
        displvec[3] = temp.dispvec[3];

        tmpindx = 2 * numnode + 6 * temp.node1;
        for (int b = 0; b < 6; b++) {
            colindx_sts.push_back(tmpindx + b);
        }
        tmpindx = 2 * numnode + 6 * temp.node2;
        for (int b = 0; b < 6; b++) {
            colindx_sts.push_back(tmpindx + b);
        }
        if (temp.dc_x1 == 0 && temp.dc_x2 == 0 && temp.dc_y1 == 0 && temp.dc_y2 == 0) {
            std::cout << "Going to assign AMat pure tract bc" << std::endl;
            for (int a = 0; a < 7; a++) {
                for (int b = 0; b < 12; b++) {
                    Amat[rowindx + a][colindx_sts[b]] = tempkmat[a][b];
                }
                for (int c = 0; c < 4; c++) {
                    Fvector[rowindx + a] = Fvector[rowindx + a] + tempFmat[a][c] * tractionvec[c];
                }
            }
            rowindx = rowindx + 7;
        } else {
            if (temp.dc_x1 == 1 && temp.dc_x2 == 1 && temp.dc_y1 == 1 && temp.dc_y2 == 1) {
                std::cout << "Going to assign AMat pure disp bc " << std::endl;
                ddof.push_back(2 * temp.node1);
                ddof.push_back(2 * temp.node1 + 1);
                ddof.push_back(2 * temp.node2);
                ddof.push_back(2 * temp.node2 + 1);
                for (int e = 0; e < 4; e++) {
                    for (int d = 0; d < count_dc; d++) {
                        if (ddof[e] == rest_dispdof[d])
                            colindx_trct.push_back(d);
                    }
                }
                for (int a = 0; a < 7; a++) {
                    for (int b = 0; b < 12; b++) {
                        Amat[rowindx + a][colindx_sts[b]] = tempkmat[a][b];
                    }
                    for (int c = 0; c < 4; c++) {
                        Amat[rowindx + a][8 * numnode + colindx_trct[c]] = -tempFmat[a][c];
                        Fvector[rowindx + a] = 0;
                    }
                }
                rowindx = rowindx + 7;
            } else {
                std::cout << "Going to assign AMat mixed bc " << std::endl;
                int cntd = 0;
                int cntu = 0;
                vector<int> relind;
                vector<int> othind;
                vector<int> ddof;
                vector<int> udof;
                if (temp.dc_x1 == 1) {
                    ddof.push_back(2 * temp.node1);
                    relind.push_back(0);
                    cntd++;
                } else {
                    udof.push_back(2 * temp.node1);
                    othind.push_back(0);
                    cntu++;
                }
                if (temp.dc_y1 == 1) {
                    ddof.push_back(2 * temp.node1 + 1);
                    relind.push_back(1);
                    cntd++;
                } else {
                    udof.push_back(2 * temp.node1 + 1);
                    othind.push_back(1);
                    cntu++;
                }
                if (temp.dc_x2 == 1) {
                    ddof.push_back(2 * temp.node2);
                    relind.push_back(2);
                    cntd++;
                } else {
                    udof.push_back(2 * temp.node2);
                    othind.push_back(2);
                    cntu++;
                }
                if (temp.dc_y2 == 1) {
                    ddof.push_back(2 * temp.node2 + 1);
                    relind.push_back(3);
                    cntd++;
                } else {
                    udof.push_back(2 * temp.node2 + 1);
                    othind.push_back(3);
                    cntu++;
                }
                for (int e = 0; e < cntd; e++) {
                    for (int d = 0; d < count_dc; d++) {
                        if (ddof[e] == rest_dispdof[d])
                            colindx_trct.push_back(d);
                    }
                }
                for (int a = 0; a < 7; a++) {
                    for (int b = 0; b < 12; b++) {
                        Amat[rowindx + a][colindx_sts[b]] = tempkmat[a][b];
                    }
                    for (int c = 0; c < cntd; c++) {
                        std::cout << "IN col " << 8 * numnode + colindx_trct[c] << "\t" << relind[c] << "\t" << -tempFmat[a][relind[c]] << std::endl;
                        Amat[rowindx + a][8 * numnode + colindx_trct[c]] = -tempFmat[a][relind[c]];
                    }
                    for (int c = 0; c < cntu; c++) {
                        Fvector[rowindx + a] = Fvector[rowindx + a] + tempFmat[a][othind[c]] * tractionvec[othind[c]];
                    }
                }
                rowindx = rowindx + 7;
            }
        }
        std::cout << "Finished side - " << ab << std::endl;
    }
    std::cout << "Assignment of Amat is completed" << std::endl;
    for (int a = 0; a < count_dc; a++) {
        Amat[rowindx + a][rest_dispdof[a]] = 1;
        Fvector[rowindx + a] = knwndisp[a];
    }

    int rmcount = 0;
    std::set<int> rmrws;
    int counter1 = 0, counter2 = 0, counter3 = 0;
    std::cout << "Starting inconstistency elimination logic" << std::endl;
    std::cout << "Amat.size : " << Amat.size() << std::endl;
    std::cout << "Amat[0].size : " << Amat[0].size() << std::endl;

    constexpr double zeroset = 1e-13;
    for (int a = 0; a < 7 * bndsdes; a++) {
        std::vector<double> bsevec(Amat[a].begin(), Amat[a].begin() + (8 * numnode));
        std::vector<int> bseind(bsevec.size(), 0);
        for (std::size_t i = 0; i < bsevec.size(); i++) {
            if (abs(bsevec[i]) > 0) {
                bseind[i] = 1;
            }
        }

        for (int b = a + 1; b < 7 * bndsdes; b++) {
            std::vector<double> reqvec(Amat[b].begin(), Amat[b].begin() + (8 * numnode));
            double diff_value1 = 0;

            for (int diff_index = 0; diff_index < bsevec.size(); diff_index++) {
                diff_value1 += abs(abs(reqvec[diff_index]) - abs(bsevec[diff_index]));
            }

            if (diff_value1 < zeroset) {
                rmrws.insert(b);
                rmcount++;
                counter1++;
            } else {
                double sum, sum1 = 0, sum2 = 0;
                bool dep = true;
                std::vector<int> reqind(reqvec.size(), 0);
                for (std::size_t i = 0; i < reqvec.size(); i++) {
                    if (abs(reqvec[i]) > 0) {
                        reqind[i] = 1;
                    }
                }

                for (std::size_t i = 0; i < reqind.size(); i++) {
                    if (reqind[i] == bseind[i]) {
                        continue;
                    } else {
                        dep = false;
                        break;
                    }
                }

                if (dep == true) {
                    std::cout << "Dependent vector index: " << b << '\n';
                    std::vector<double> req_n, req_d, reqrat;
                    auto bseind_it1 = bseind.begin(), bseind_it2 = bseind.begin();

                    std::copy_if(reqvec.begin(), reqvec.end(), std::back_inserter(req_n), [&](int) { return *bseind_it1++; });
                    std::copy_if(bsevec.begin(), bsevec.end(), std::back_inserter(req_d), [&](int) { return *bseind_it2++; });
                    std::transform(req_n.begin(), req_n.end(), req_d.begin(), std::back_inserter(reqrat), std::divides<double>());

                    sum = std::accumulate(reqrat.begin(), reqrat.end(), 0.0);

                    double min = *std::min_element(reqrat.begin(), reqrat.end());
                    double max = *std::max_element(reqrat.begin(), reqrat.end());

                    for (const auto& elem : reqrat) {
                        sum1 += abs(elem - max);
                    }

                    for (const auto& elem : reqrat) {
                        sum2 += abs(elem - min);
                    }

                    if (sum > 0 && sum1 < zeroset) {
                        rmrws.insert(b);
                        rmcount++;
                        counter3++;
                    } else if (sum < 0 && sum2 < zeroset) {
                        rmrws.insert(b);
                        rmcount++;
                        counter3++;
                    }
                }
            }
        }
    }

    std::cout << "Rank before removing rows: " << init.compute_rank(Amat) << '\n'; // Use the instance to call the function

    std::cout << "counter1 " << counter1 << '\n';
    std::cout << "counter2 " << counter2 << '\n';
    std::cout << "counter3 " << counter3 << '\n';
    std::cout << "counter sum values " << counter1 + counter2 + counter3 << '\n';

    std::set<int>::reverse_iterator it = rmrws.rbegin();

    std::vector<int> all(7 * bndsdes + count_dc);
    std::iota(all.begin(), all.end(), 0);

    std::vector<int> diff;

    std::set_difference(all.begin(), all.end(), rset.begin(), rset.end(), std::back_inserter(diff));

    std::sort(diff.begin(), diff.end());

    auto it2 = diff.rbegin();

    std::cout << "Removing rows\n";
    while (it2 != diff.rend()) {
        Amat.erase(Amat.begin() + *it2);
        Fvector.erase(Fvector.begin() + *it2);
        it2++;
    }
    std::cout << "Just completed inconsistent rank code\n";
    std::cout << "Amat.size : " << Amat.size() << std::endl;
    std::cout << "Amat[0].size : " << Amat[0].size() << std::endl;
    row = Amat.size();
    std::cout << "Rank after removing rows: " << init.compute_rank(Amat) << '\n'; // Use the instance to call the function

    if ((Amat.size() - init.compute_rank(Amat)) > 0) { // Use the instance to call the function
        std::cout << "Inconsistent boundary condition" << std::endl;
        std::cout << "Amat.size : " << Amat.size() << std::endl;
        std::cout << "compute_rank(Amat) : " << init.compute_rank(Amat) << std::endl; // Use the instance to call the function
    }

    ofstream outfile_A;
    outfile_A.open("Amat.csv");
    for (int i = 0; i < Amat.size(); i++) {
        for (int j = 0; j < Amat[i].size() - 1; j++) {
            outfile_A << Amat[i][j] << ",";
        }
        outfile_A << Amat[i][colm - 1] << "\n";
    }
        outfile_A.close();
    std::cout << "Amat.csv file has been written successfully." << std::endl;

    ofstream outfile_F;
    outfile_F.open("Fvector.csv");
    for (int i = 0; i < Fvector.size(); i++) {
        outfile_F << Fvector[i] << "\n";
    }
    outfile_F.close();
    std::cout << "Fvector.csv file has been written successfully." << std::endl;
}