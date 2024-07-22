#include "initialize.h"
#include "constraints.h"
#include "constructor.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cmath>

Initialize::Initialize() {}

void Initialize::startInitializing()
{
    nnode = m_nodes.size();
    nmemb = m_elements.size();

    for (int i = 0; i < nmemb; i++){
        vector<double> temp(1, 0.0);
        L.push_back(temp);
    }

    for (int i = 0; i < nmemb; i++){
        vector<double> temp(1, parameters[i][0]);
        A.push_back(temp);
    }

    for (int i = 0; i < m_loads.size(); i++){
        for(int j = 1; j < 3; j++){
            vector<double> temp(1, m_loads[i][j]);
            F.push_back(temp);
        }
    }

    Fm = 0;
    for (const auto& load : F) {
        double absF = abs(load[0]);
        if (absF > Fm) {
            Fm = absF;
        }
    }
    avgforce = Fm;

    vector<vector<double>> elements, nodes1, bc;

    for (const auto& element : m_elements) {
        vector<double> temp(3);
        Oceane::Index index = element->getIndex();
        temp[0] = static_cast<int>(index);
        vector<Oceane::Nodeptr> temp1 = element->getNodes();
        Oceane::Nodeptr node1 = temp1[0];
        Oceane::Nodeptr node2 = temp1[1];
        temp[1] = static_cast<int>(node1->getIndex());
        temp[2] = static_cast<int>(node2->getIndex());
        elements.push_back(temp);
    }

    for (const auto& node : m_nodes) {
        vector<double> temp(3);
        temp[0] = static_cast<int>(node->getIndex());
        vector<double> coords = node->getCoord();
        temp[1] = coords[0];
        temp[2] = coords[1];
        nodes1.push_back(temp);
    }

    for (const auto& boundaryNode : m_boundaryElements) {
        vector<double> temp(3);
        temp[0] = static_cast<int>(boundaryNode->getIndex());
        vector<double> coords = boundaryNode->getCoord();
        temp[1] = coords[0];
        temp[2] = coords[1];
        bc.push_back(temp);
    }

    for (int i = 0; i < nmemb; i++) {
        double lx = nodes1[elements[i][2]-1][1] - nodes1[elements[i][1]-1][1];
        double mx = nodes1[elements[i][2]-1][2] - nodes1[elements[i][1]-1][2];
        L[i][0] = std::ceil(std::sqrt(std::pow(lx, 2) + std::pow(mx, 2)) * 1e8) / 1e8;
    }

    vector<vector<double>> B(2 * nnode, vector<double>(nmemb, 0.0));
    for (int i = 0; i < nnode; i++) {
        vector<int> mem;
        for (int j = 0; j < nmemb; j++) {
            for(int k = 1; k < 3; k++){
                if(elements[j][k] == i+1){
                    mem.push_back(j);
                }
            }
        }

        for (int k : mem) {
            B[2 * i][k] = (-nodes1[elements[k][1] - 1][1] + nodes1[elements[k][2] - 1][1]) / L[k][0];
            B[2 * i + 1][k] = (-nodes1[elements[k][1] - 1][2] + nodes1[elements[k][2] - 1][2]) / L[k][0];
        }
        mem.clear();
        for (int j = 0; j < nmemb; j++) {
            if (elements[j][2] == i + 1) {
                mem.push_back(j);
            }
        }
        for (int k : mem) {
            B[2 * i][k] = (nodes1[elements[k][1] - 1][1] - nodes1[elements[k][2] - 1][1]) / L[k][0];
            B[2 * i + 1][k] = (nodes1[elements[k][1] - 1][2] - nodes1[elements[k][2] - 1][2]) / L[k][0];
        }
    }
    for (auto& row : B) {
        for (auto& val : row) {
            val = -val;
        }
    }

    for (int i = 1; i < 3; i++) {
        for(int j = 0; j < m_boundaryElements.size(); j++){
            if (bc[j][i] == 0){
                nodenum.push_back(i-1);
                xyz.push_back(j);
            }
        }
    }

    ns = nodenum.size();
    for(int i = 0; i < ns; i++) {
        vector<double> temp(nmemb, 0.0);
        Br.push_back(temp);
    }

    for(int i = 0; i < ns; i++){
        int temp = 2*xyz[i] + nodenum[i];
        for(int j = 0; j < B[0].size(); j++){
            Br[i][j] = B[temp][j];
        }
    }

    vector<int> temp2;
    for(int i = 0; i < ns; i++){
        temp2.push_back(2*xyz[i] + nodenum[i]);
    }
    std::sort(temp2.begin(), temp2.end());
    int index = 0;
    for(int i = 0; i < 2*nnode-1; i++){
        if(i != temp2[index]){
            vector<double> temp;
            for(int j = 0; j < B[i].size(); j++){
                temp.push_back(B[i][j]);
            }
            Breq.push_back(temp);
        }
        index += 1;
    }

    vector<vector<int>> Suppsettle(m_fixity[0].size(), vector<int>());
    for(int i = 0; i < m_fixity.size(); i++){
        for(int j = 0; j < m_fixity[0].size(); j++){
            Suppsettle[j].push_back(m_fixity[i][j]);
        }
    }
    vector<int> temp4;
    vector<int> temp5;
    for(int i = 0; i < Suppsettle.size(); i++){
        for(int j = 0; j < Suppsettle[0].size(); j++){
            temp4.push_back(Suppsettle[i][j]);
        }
    }
    for(int i = 0; i < ns; i++){
        temp5.push_back(nnode*(nodenum[i] + 1) + xyz[i]);
    }
    for(int i = 0; i < ns; i++){
        qs.push_back(temp4[temp5[i]]);
    }

    for (int i = 0; i < nmemb; i++) {
        int x = 0;
        for (int j = 0; j < ns; j++) {
            x += Br[j][i] * qs[j];
        }
        vector<double> y(1, x);
        deltasupp.push_back(y);
    }

    for (int i = 0; i < 2*nnode; i++){
        vector<double> temp(2 * nnode + nmemb, 0.0);
        BC.push_back(temp);
    }
    for (int i = 0; i < 2 * nnode; i++) {
        for (int j = 0; j < nmemb; j++) {
            BC[i][j] = B[i][j];
        }
    }

    for (int i = 0; i < ns; i++) {
        nodepos.push_back(2 * xyz[i] + nodenum[i]);
    }
    for (int i = nmemb + 2 * nnode - ns; i < nmemb + 2 * nnode; i++) {
        reactpos.push_back(i);
    }
    for (int i = 0; i < reactpos.size(); i++) {
        BC[(2 * nnode * reactpos[i] + nodepos[i]) % BC.size()][(2 * nnode * reactpos[i] + nodepos[i]) / B.size()] = -1;
    }

    sb[0] = Breq.size();
    sb[1] = Breq[0].size();

    for (int i = 0; i < sb[1]; i++){
        vector<double> temp(sb[1] + sb[0] + ns, 0.0);
        S.push_back(temp);
    }
    for(int i = 0; i < sb[1]; i++){
        for(int j = sb[1]; j < sb[1] + sb[0]; j++){
            S[i][j] = Breq[j-sb[1]][i];
        }
    }

    for(int i = 0; i < sb[0]; i++){
        vector<double> temp(sb[1] + sb[0] + ns, 0.0);
        S.push_back(temp);
    }
    for(int i = sb[1]; i < sb[1] + sb[0]; i++){
        for(int j = 0; j < sb[1]; j++){
            S[i][j] = Breq[i-sb[1]][j];
        }
    }

    for(int i = sb[1] + sb[0]; i < sb[1] + sb[0] + ns; i++){
        S[i][i] = -1;
    }

    for(int i = 0; i < 2*nnode; i++){
        vector<double> temp(1, 0.0);
        f.push_back(temp);
    }
    for(int i = 0; i < 2*nnode; i++){
        f[i][0] = F[i][0];
    }

    for(int i = 0; i < ns; i++){
        vector<double> temp(1, 0.0);
        deltacheck.push_back(temp);
    }

    for(int i = 0; i < ns; i++){
        deltacheck[i][0] = deltasupp[i][0];
    }

    for(int i = 0; i < 2*nnode; i++){
        vector<double> temp(1, 0.0);
        f.push_back(temp);
    }
    for(int i = 0; i < 2*nnode; i++){
        f[i][0] = F[i][0];
    }
    for(int i = 0; i < ns; i++){
        vector<double> temp(1, 0.0);
        f.push_back(temp);
    }
    for(int i = 0; i < ns; i++){
        f[2*nnode+i][0] = deltacheck[i][0];
    }
}

