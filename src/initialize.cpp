#include "initialize.h"
#include "constraints.h"
#include "constructor.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;


Initialize::Initialize() {};

GQVandW Initialize::getWeightAndValues(int order) {
   
GQVandW result;
	vector<double> weights;
	vector<double> values;
	if (order == 2) {
		weights.push_back(1.0000000000000000);
		weights.push_back(1.0000000000000000);
		values.push_back(-0.5773502691896257);
		values.push_back(0.5773502691896257);
	}

	if (order == 3) {
		weights.push_back(0.8888888888888888);
		weights.push_back(0.5555555555555556);
		weights.push_back(0.5555555555555556);
		values.push_back(0.0000000000000000);
		values.push_back(-0.7745966692414834);
		values.push_back(0.7745966692414834);
	}

	if (order == 4) {
		weights.push_back(0.6521451548625461);
		weights.push_back(0.6521451548625461);
		weights.push_back(0.3478548451374538);
		weights.push_back(0.3478548451374538);

		values.push_back(-0.3399810435848563);
		values.push_back(0.3399810435848563);
		values.push_back(-0.8611363115940526);
		values.push_back(0.8611363115940526);

	}

	if (order == 5) {
		weights.push_back(0.5688888888888889);
		weights.push_back(0.4786286704993665);
		weights.push_back(0.4786286704993665);
		weights.push_back(0.2369268850561891);
		weights.push_back(0.2369268850561891);

		values.push_back(0.0000000000000000);
		values.push_back(-0.5384693101056831);
		values.push_back(0.5384693101056831);
		values.push_back(-0.9061798459386640);
		values.push_back(0.9061798459386640);

	}

	if (order == 6) {
		weights.push_back(0.3607615730481386);
		weights.push_back(0.3607615730481386);
		weights.push_back(0.4679139345726910);
		weights.push_back(0.4679139345726910);
		weights.push_back(0.1713244923791704);
		weights.push_back(0.1713244923791704);

		values.push_back(-0.6612093864662645);
		values.push_back(0.6612093864662645);
		values.push_back(-0.2386191860831969);
		values.push_back(0.2386191860831969);
		values.push_back(-0.9324695142031521);
		values.push_back(0.9324695142031521);
	}

	if (order == 7) {
		weights.push_back(0.4179591836734694);
		weights.push_back(0.3818300505051189);
		weights.push_back(0.3818300505051189);
		weights.push_back(0.2797053914892766);
		weights.push_back(0.2797053914892766);
		weights.push_back(0.1294849661688697);
		weights.push_back(0.1294849661688697);

		values.push_back(0.0000000000000000);
		values.push_back(-0.4058451513773972);
		values.push_back(0.4058451513773972);
		values.push_back(-0.7415311855993945);
		values.push_back(0.7415311855993945);
		values.push_back(-0.9491079123427585);
		values.push_back(0.9491079123427585);

	}

	if (order == 8) {
		weights.push_back(0.3626837833783620);
		weights.push_back(0.3626837833783620);
		weights.push_back(0.3137066458778873);
		weights.push_back(0.3137066458778873);
		weights.push_back(0.2223810344533745);
		weights.push_back(0.2223810344533745);
		weights.push_back(0.1012285362903763);
		weights.push_back(0.1012285362903763);

		values.push_back(-0.1834346424956498);
		values.push_back(0.1834346424956498);
		values.push_back(-0.5255324099163290);
		values.push_back(0.5255324099163290);
		values.push_back(-0.7966664774136267);
		values.push_back(0.7966664774136267);
		values.push_back(-0.9602898564975363);
		values.push_back(0.9602898564975363);
	}

	if (order == 9) {
		weights.push_back(0.3302393550012598);
		weights.push_back(0.1806481606948574);
		weights.push_back(0.1806481606948574);
		weights.push_back(0.0812743883615744);
		weights.push_back(0.0812743883615744);
		weights.push_back(0.3123470770400029);
		weights.push_back(0.3123470770400029);
		weights.push_back(0.2606106964029354);
		weights.push_back(0.2606106964029354);

		values.push_back(0.0000000000000000);
		values.push_back(-0.8360311073266358);
		values.push_back(0.8360311073266358);
		values.push_back(-0.9681602395076261);
		values.push_back(0.9681602395076261);
		values.push_back(-0.3242534234038089);
		values.push_back(0.3242534234038089);
		values.push_back(-0.6133714327005904);
		values.push_back(0.6133714327005904);
	}

	if (order == 10) {
		weights.push_back(0.2955242247147529);
		weights.push_back(0.2955242247147529);
		weights.push_back(0.2692667193099963);
		weights.push_back(0.2692667193099963);
		weights.push_back(0.2190863625159820);
		weights.push_back(0.2190863625159820);
		weights.push_back(0.1494513491505806);
		weights.push_back(0.1494513491505806);
		weights.push_back(0.0666713443086881);
		weights.push_back(0.0666713443086881);

		values.push_back(-0.1488743389816312);
		values.push_back(0.1488743389816312);
		values.push_back(-0.4333953941292472);
		values.push_back(0.4333953941292472);
		values.push_back(-0.6794095682990244);
		values.push_back(0.6794095682990244);
		values.push_back(-0.8650633666889845);
		values.push_back(0.8650633666889845);
		values.push_back(-0.9739065285171717);
		values.push_back(0.9739065285171717);
	}
	result.weight = weights;
	result.value = values;
	return result;
}

BB Initialize::Bsigma_Bd(double *xcoord, double  *ycoord, double s, double t) {

	vector<double>Nis(4);
	Nis[0] = (t - 1) / 4;
	Nis[1] = (1 - t) / 4;
	Nis[2] = (t + 1) / 4;
	Nis[3] = -(t + 1) / 4;

	vector<double>Nit(4);
	Nit[0] = (s - 1) / 4;
	Nit[1] = -(s + 1) / 4;
	Nit[2] = (s + 1) / 4;
	Nit[3] = (1 - s) / 4;

	vector<double>N(4);
	N[0] = (1 - s) * (1 - t) / 4;
	N[1] = (1 + s) * (1 - t) / 4;
	N[2] = (1 + s) * (1 + t) / 4;
	N[3] = (1 - s) * (1 + t) / 4;

	double matX = 0, matY = 0;
	for (int i = 0; i < 4; i++) {
		matX += N[i] * xcoord[i];
		matY += N[i] * ycoord[i];
	}

	vector<vector<double> > Jmat;
	vector<double> Jmatrow(2);
	for (int i = 0; i < 2; i++) {
		Jmat.push_back(Jmatrow);
		for (int j = 0; j < 2; j++)
			Jmat[i][j] = 0;
	}

	for (int i = 0; i < 4; i++) {
		Jmat[0][0] += Nis[i] * xcoord[i];
		Jmat[0][1] += Nit[i] * xcoord[i];
		Jmat[1][0] += Nis[i] * ycoord[i];
		Jmat[1][1] += Nit[i] * ycoord[i];
	}

	vector<vector<double> > invJ(2, vector<double>(2, 0));
	double detJ = (Jmat[0][0] * Jmat[1][1]) - (Jmat[0][1] * Jmat[1][0]);
	invJ[0][0] = Jmat[1][1] / detJ;
	invJ[0][1] = -(Jmat[0][1]) / detJ;
	invJ[1][0] = -(Jmat[1][0]) / detJ;
	invJ[1][1] = Jmat[0][0] / detJ;

	vector<vector<double> > Bd;
	vector<double>Bdrow(8);
	vector<vector<double> > Bs;
	vector<double> Bsrow(24);
	for (int i = 0; i < 3; i++) {
		Bd.push_back(Bdrow);
		Bs.push_back(Bsrow);
		for (int j = 0; j < 8; j++)
			Bd[i][j] = 0;
		for (int j = 0; j < 24; j++)
			Bs[i][j] = 0;
	}

	vector<vector<double> > Tmat;
	vector<double>Tmatrow(24);
	for (int i = 0; i < 24; i++) {
		Tmat.push_back(Tmatrow);
		for (int j = 0; j < 24; j++)
			Tmat[i][j] = 0;
	}
	vector<vector<double> > T1mat;
	vector<double>T1matrow(6);
	for (int i = 0; i < 6; i++) {
		T1mat.push_back(T1matrow);
		for (int j = 0; j < 6; j++)
			T1mat[i][j] = 0;
	}

	Bd[0][0] = ((Nis[0] * invJ[0][0]) + (Nit[0] * invJ[1][0]));
	Bd[0][2] = ((Nis[1] * invJ[0][0]) + (Nit[1] * invJ[1][0]));
	Bd[0][4] = ((Nis[2] * invJ[0][0]) + (Nit[2] * invJ[1][0]));
	Bd[0][6] = ((Nis[3] * invJ[0][0]) + (Nit[3] * invJ[1][0]));

	Bd[1][1] = ((Nis[0] * invJ[0][1]) + (Nit[0] * invJ[1][1]));
	Bd[1][3] = ((Nis[1] * invJ[0][1]) + (Nit[1] * invJ[1][1]));
	Bd[1][5] = ((Nis[2] * invJ[0][1]) + (Nit[2] * invJ[1][1]));
	Bd[1][7] = ((Nis[3] * invJ[0][1]) + (Nit[3] * invJ[1][1]));

	Bd[2][0] = ((Nis[0] * invJ[0][1]) + (Nit[0] * invJ[1][1]));
	Bd[2][2] = ((Nis[1] * invJ[0][1]) + (Nit[1] * invJ[1][1]));
	Bd[2][4] = ((Nis[2] * invJ[0][1]) + (Nit[2] * invJ[1][1]));
	Bd[2][6] = ((Nis[3] * invJ[0][1]) + (Nit[3] * invJ[1][1]));

	Bd[2][1] = ((Nis[0] * invJ[0][0]) + (Nit[0] * invJ[1][0]));
	Bd[2][3] = ((Nis[1] * invJ[0][0]) + (Nit[1] * invJ[1][0]));
	Bd[2][5] = ((Nis[2] * invJ[0][0]) + (Nit[2] * invJ[1][0]));
	Bd[2][7] = ((Nis[3] * invJ[0][0]) + (Nit[3] * invJ[1][0]));

	vector<vector<double> > Dmat(3, vector<double>(3, 0));
	Dmat[0][0] = (invJ[1][1] * invJ[1][1]);
	Dmat[0][1] = (invJ[0][1] * invJ[0][1]);
	Dmat[0][2] = -2 * (invJ[1][1] * invJ[0][1]);
	Dmat[1][0] = (invJ[1][0] * invJ[1][0]);
	Dmat[1][1] = (invJ[0][0] * invJ[0][0]);
	Dmat[1][2] = -2 * (invJ[0][0] * invJ[1][0]);
	Dmat[2][0] = -(invJ[1][0] * invJ[1][1]);
	Dmat[2][1] = -(invJ[0][0] * invJ[0][1]);
	Dmat[2][2] = ((invJ[0][0] * invJ[1][1]) + (invJ[0][1] * invJ[1][0]));

	T1mat[0][0] = 1;
	T1mat[1][1] = Jmat[0][0];
	T1mat[1][2] = Jmat[1][0];
	T1mat[2][1] = Jmat[0][1];
	T1mat[2][2] = Jmat[1][1];
	T1mat[3][3] = (Jmat[0][0] * Jmat[0][0]);
	T1mat[3][4] = (Jmat[1][0] * Jmat[1][0]);
	T1mat[3][5] = 2 * (Jmat[0][0] * Jmat[1][0]);
	T1mat[4][3] = (Jmat[0][1] * Jmat[0][1]);
	T1mat[4][4] = (Jmat[1][1] * Jmat[1][1]);
	T1mat[4][5] = 2 * (Jmat[0][1] * Jmat[1][1]);
	T1mat[5][3] = (Jmat[0][0] * Jmat[0][1]);
	T1mat[5][4] = (Jmat[1][0] * Jmat[1][1]);
	T1mat[5][5] = ((Jmat[0][0] * Jmat[1][1]) + (Jmat[0][1] * Jmat[1][0]));

	Tmat[0][0] = Tmat[6][6] = Tmat[12][12] = Tmat[18][18] = 1;
	Tmat[1][1] = Tmat[7][7] = Tmat[13][13] = Tmat[19][19] = T1mat[1][1];
	Tmat[1][2] = Tmat[7][8] = Tmat[13][14] = Tmat[19][20] = T1mat[1][2];
	Tmat[2][1] = Tmat[8][7] = Tmat[14][13] = Tmat[20][19] = T1mat[2][1];
	Tmat[2][2] = Tmat[8][8] = Tmat[14][14] = Tmat[20][20] = T1mat[2][2];
	Tmat[3][3] = Tmat[9][9] = Tmat[15][15] = Tmat[21][21] = T1mat[3][3];
	Tmat[3][4] = Tmat[9][10] = Tmat[15][16] = Tmat[21][22] = T1mat[3][4];
	Tmat[3][5] = Tmat[9][11] = Tmat[15][17] = Tmat[21][23] = T1mat[3][5];
	Tmat[4][3] = Tmat[10][9] = Tmat[16][15] = Tmat[22][21] = T1mat[4][3];
	Tmat[4][4] = Tmat[10][10] = Tmat[16][16] = Tmat[22][22] = T1mat[4][4];
	Tmat[4][5] = Tmat[10][11] = Tmat[16][17] = Tmat[22][23] = T1mat[4][5];
	Tmat[5][3] = Tmat[11][9] = Tmat[17][15] = Tmat[23][21] = T1mat[5][3];
	Tmat[5][4] = Tmat[11][10] = Tmat[17][16] = Tmat[23][22] = T1mat[5][4];
	Tmat[5][5] = Tmat[11][11] = Tmat[17][17] = Tmat[23][23] = T1mat[5][5];

	Bs[0][0] = (3 * t * (s - 1) * (s * s + s + 5 * t * t - 5)) / 8;
	Bs[0][1] = (3 * t * (s - 1) * (s - 1) * (s + 1)) / 8;
	Bs[0][2] = -((s - 1) * (-3 * s * s * t + s * s - 3 * s * t + s - 15 * t * t * t + 3 * t * t + 15 * t - 3)) / 8;
	Bs[0][4] = ((s - 1) * (t - 1) * (5 * t * t + 2 * t - 1)) / 8;
	Bs[0][5] = ((3 * t - 1) * (s - 1) * (s - 1) * (s + 1)) / 8;
	Bs[0][6] = (3 * t * (s + 1) * (-s * s + s - 5 * t * t + 5)) / 8;
	Bs[0][7] = (3 * t * (s - 1) * (s + 1) * (s + 1)) / 8;
	Bs[0][8] = -((s + 1) * (3 * s * s * t - s * s - 3 * s * t + s + 15 * t * t * t - 3 * t * t - 15 * t + 3)) / 8;
	Bs[0][10] = -((s + 1) * (t - 1) * (5 * t * t + 2 * t - 1)) / 8;
	Bs[0][11] = ((3 * t - 1) * (s - 1) * (s + 1) * (s + 1)) / 8;
	Bs[0][12] = -(3 * t * (s + 1) * (-s * s + s - 5 * t * t + 5)) / 8;
	Bs[0][13] = -(3 * t * (s - 1) * (s + 1) * (s + 1)) / 8;
	Bs[0][14] = ((s + 1) * (-3 * s * s * t - s * s + 3 * s * t + s - 15 * t * t * t - 3 * t * t + 15 * t + 3)) / 8;
	Bs[0][16] = ((s + 1) * (t + 1) * (5 * t * t - 2 * t - 1)) / 8;
	Bs[0][17] = ((3 * t + 1) * (s - 1) * (s + 1) * (s + 1)) / 8;
	Bs[0][18] = -(3 * t * (s - 1) * (s * s + s + 5 * t * t - 5)) / 8;
	Bs[0][19] = -(3 * t * (s - 1) * (s - 1) * (s + 1)) / 8;
	Bs[0][20] = ((s - 1) * (3 * s * s * t + s * s + 3 * s * t + s + 15 * t * t * t + 3 * t * t - 15 * t - 3)) / 8;
	Bs[0][22] = -((s - 1) * (t + 1) * (5 * t * t - 2 * t - 1)) / 8;
	Bs[0][23] = ((3 * t + 1) * (s - 1) * (s - 1) * (s + 1)) / 8;

	Bs[1][0] = (3 * s * (t - 1) * (5 * s * s + t * t + t - 5)) / 8;
	Bs[1][1] = -((t - 1) * (-15 * s * s * s + 3 * s * s - 3 * s * t * t - 3 * s * t + 15 * s + t * t + t - 3)) / 8;
	Bs[1][2] = (3 * s * (t - 1) * (t - 1) * (t + 1)) / 8;
	Bs[1][3] = ((s - 1) * (t - 1) * (5 * s * s + 2 * s - 1)) / 8;
	Bs[1][5] = ((3 * s - 1) * (t - 1) * (t - 1) * (t + 1)) / 8;
	Bs[1][6] = -(3 * s * (t - 1) * (5 * s * s + t * t + t - 5)) / 8;
	Bs[1][7] = ((t - 1) * (15 * s * s * s + 3 * s * s + 3 * s * t * t + 3 * s * t - 15 * s + t * t + t - 3)) / 8;
	Bs[1][8] = -(3 * s * (t - 1) * (t - 1) * (t + 1)) / 8;
	Bs[1][9] = ((s + 1) * (t - 1) * (-5 * s * s + 2 * s + 1)) / 8;
	Bs[1][11] = ((3 * s + 1) * (t - 1) * (t - 1) * (t + 1)) / 8;
	Bs[1][12] = -(3 * s * (t + 1) * (-5 * s * s - t * t + t + 5)) / 8;
	Bs[1][13] = ((t + 1) * (-15 * s * s * s - 3 * s * s - 3 * s * t * t + 3 * s * t + 15 * s - t * t + t + 3)) / 8;
	Bs[1][14] = -(3 * s * (t - 1) * (t + 1) * (t + 1)) / 8;
	Bs[1][15] = -((s + 1) * (t + 1) * (-5 * s * s + 2 * s + 1)) / 8;
	Bs[1][17] = ((3 * s + 1) * (t - 1) * (t + 1) * (t + 1)) / 8;
	Bs[1][18] = (3 * s * (t + 1) * (-5 * s * s - t * t + t + 5)) / 8;
	Bs[1][19] = ((t + 1) * (-15 * s * s * s + 3 * s * s - 3 * s * t * t + 3 * s * t + 15 * s + t * t - t - 3)) / 8;
	Bs[1][20] = (3 * s * (t - 1) * (t + 1) * (t + 1)) / 8;
	Bs[1][21] = -((s - 1) * (t + 1) * (5 * s * s + 2 * s - 1)) / 8;
	Bs[1][23] = ((3 * s - 1) * (t - 1) * (t + 1) * (t + 1)) / 8;

	Bs[2][0] = -(15 * s * s * s * s + 18 * s * s * t * t - 36 * s * s + 15 * t * t * t * t - 36 * t * t + 24) / 32;
	Bs[2][1] = -((3 * s + 1) * (s - 1) * (5 * s * s + 2 * s + 6 * t * t - 9)) / 32;
	Bs[2][2] = -((3 * t + 1) * (t - 1) * (6 * s * s + 5 * t * t + 2 * t - 9)) / 32;
	Bs[2][3] = -((5 * s + 1) * (s - 1) * (s - 1) * (s + 1)) / 32;
	Bs[2][4] = -((5 * t + 1) * (t - 1) * (t - 1) * (t + 1)) / 32;
	Bs[2][5] = -((3 * s + 1) * (3 * t + 1) * (s - 1) * (t - 1)) / 16;
	Bs[2][6] = (15 * s * s * s * s + 18 * s * s * t * t - 36 * s * s + 15 * t * t * t * t - 36 * t * t + 24) / 32;
	Bs[2][7] = ((3 * s - 1) * (s + 1) * (-5 * s * s + 2 * s - 6 * t * t + 9)) / 32;
	Bs[2][8] = ((3 * t + 1) * (t - 1) * (6 * s * s + 5 * t * t + 2 * t - 9)) / 32;
	Bs[2][9] = ((5 * s - 1) * (s - 1) * (s + 1) * (s + 1)) / 32;
	Bs[2][10] = ((5 * t + 1) * (t - 1) * (t - 1) * (t + 1)) / 32;
	Bs[2][11] = -((3 * s - 1) * (3 * t + 1) * (s + 1) * (t - 1)) / 16;
	Bs[2][12] = -(15 * s * s * s * s + 18 * s * s * t * t - 36 * s * s + 15 * t * t * t * t - 36 * t * t + 24) / 32;
	Bs[2][13] = -((3 * s - 1) * (s + 1) * (-5 * s * s + 2 * s - 6 * t * t + 9)) / 32;
	Bs[2][14] = -((3 * t - 1) * (t + 1) * (-6 * s * s - 5 * t * t + 2 * t + 9)) / 32;
	Bs[2][15] = -((5 * s - 1) * (s - 1) * (s + 1) * (s + 1)) / 32;
	Bs[2][16] = -((5 * t - 1) * (t - 1) * (t + 1) * (t + 1)) / 32;
	Bs[2][17] = -((3 * s - 1) * (3 * t - 1) * (s + 1) * (t + 1)) / 16;
	Bs[2][18] = (15 * s * s * s * s + 18 * s * s * t * t - 36 * s * s + 15 * t * t * t * t - 36 * t * t + 24) / 32;
	Bs[2][19] = ((3 * s + 1) * (s - 1) * (5 * s * s + 2 * s + 6 * t * t - 9)) / 32;
	Bs[2][20] = ((3 * t - 1) * (t + 1) * (-6 * s * s - 5 * t * t + 2 * t + 9)) / 32;
	Bs[2][21] = ((5 * s + 1) * (s - 1) * (s - 1) * (s + 1)) / 32;
	Bs[2][22] = ((5 * t - 1) * (t - 1) * (t + 1) * (t + 1)) / 32;
	Bs[2][23] = -((3 * s + 1) * (3 * t - 1) * (s - 1) * (t + 1)) / 16;

	vector<vector<double> > Bs1mat(3, vector<double>(24, 0));  // Bs1mat = Dmat*Bs
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 24; j++) {
			Bs1mat[i][j] = 0;
			for (int k = 0; k < 3; k++) {
				Bs1mat[i][j] += Dmat[i][k] * Bs[k][j];
			}
		}
	}


	vector<vector<double> > Bsmat(3, vector<double>(24, 0)); // Bsmat = Dmat*Bs*Tmat = Bs1mat*Tmat 
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 24; j++) {
			Bsmat[i][j] = 0;
			for (int k = 0; k < 24; k++) {
				Bsmat[i][j] += Bs1mat[i][k] * Tmat[k][j];
			}
		}
	}

	BB BBresult;
	BBresult.x = matX;
	BBresult.y = matY;
	BBresult.Jmat = Jmat;
	BBresult.detJ = detJ;
	BBresult.Bd = Bd;
	BBresult.Bsmat = Bsmat;
	return BBresult;
}

vector<BB> Initialize::get_BB_results_mat(int k, int order, double *xcoord, double *ycoord, vector<double> values) {
	vector<BB> BB_results_mat(order);
	
	if (k == 2)
	{
		for (int i = 0; i < order; i++)
		{
			BB_results_mat[i] = Bsigma_Bd(xcoord, ycoord, 1, values[i]);
		}
	}
	else if (k == 4)
	{
		for (int i = 0; i < order; i++)
		{
			BB_results_mat[i] = Bsigma_Bd(xcoord, ycoord, -1, values[i]);
		}
	}
	else if (k == 3)
	{
		for (int i = 0; i < order; i++)
		{
			BB_results_mat[i] = Bsigma_Bd(xcoord, ycoord, values[i], 1);
		}
	}
	else if (k == 1)
	{
		for (int i = 0; i < order; i++)
		{
			BB_results_mat[i] = Bsigma_Bd(xcoord, ycoord, values[i], -1);
		}
	}
	return BB_results_mat;
}

bool Initialize::cmp_for_desc(int x, int y){
    if (x > y)
        return true;
    else
        return false;
}


int Initialize::compute_rank(vector<vector<double>> A) {
    int n = A.size();
    int m = A[0].size();

    int rank = 0;
    vector<bool> row_selected(n, false);
    for (int i = 0; i < m; ++i) {
        int j;
        for (j = 0; j < n; ++j) {
            if (!row_selected[j] && abs(A[j][i]) > EPS)
                break;
        }

        if (j != n) {
            ++rank;
	    rset.push_back(j);
            row_selected[j] = true;
            for (int p = i + 1; p < m; ++p)
                A[j][p] /= A[j][i];
            for (int k = 0; k < n; ++k) {
                if (k != j && abs(A[k][i]) > EPS) {
                    for (int p = i + 1; p < m; ++p)
                        A[k][p] -= A[j][p] * A[k][i];
                }
            }
        }
    }
    return rank;
}

void Initialize::startInitializing()
{
  order = 6;
	GQVandW GQdata= getWeightAndValues(order);

    //int ele = boundry.ele;

    RetBC boundry_condition_fun(bc boundry, GQVandW GQdat, int order) {
	cout << "In boundary condition" << endl;
	RetBC result;
	double bc_x1, bc_y1, bc_x2, bc_y2;
	int c1, c2, nd1, nd2;
	vector<double> values;
	vector<double> weights;
	values = GQdat.value;
	weights = GQdat.weight;
	
	nd1 = boundry.node1;
	nd2 = boundry.node2;
	bc_x1 = nodes[nd1].x_cord;
	bc_y1 = nodes[nd1].y_cord;
	bc_x2 = nodes[nd2].x_cord;
	bc_y2 = nodes[nd2].y_cord;
	
	vector<vector<double> > kmat;
	vector<double> kmatrow(12);
	// inti with Zero
	for (int i = 0; i < 7; i++) {
		kmat.push_back(kmatrow);
		for (int j = 0; j < 12; j++)
			kmat[i][j] = 0;
	}

	vector<vector<double> > fmat;
	vector<double>fmatrow(4);
	//init with zero
	for (int i = 0; i < 7; i++) {
		fmat.push_back(fmatrow);
		for (int j = 0; j < 4; j++)
			fmat[i][j] = 0;
	}

	double len, nx, ny, f1, f2, m1, m2, m3, m4, var, value, value2, value3;
	len = sqrt(pow((bc_x2 - bc_x1), 2) + pow((bc_y2 - bc_y1), 2));
/*
	cout<<"nd1: "<<nd1<<'\n';
	cout<<"nd2: "<<nd2<<'\n';
	cout<<"bc_x1: "<<bc_x1<<'\n';
	cout<<"bc_x2: "<<bc_x2<<'\n';
	
	cout<<"bc_y1: "<<bc_y1<<'\n';
	cout<<"bc_y2: "<<bc_y2<<'\n';	

	cout<<"len : "<<len<<'\n';
*/
	nx = (bc_y2 - bc_y1) / len;
	ny = -(bc_x2 - bc_x1) / len;

	if (std::isnan(nx)){
		cout<<"nx is Nan\n";
	}

	if (std::isnan(ny)){
		cout<<"ny is Nan\n";
	}

	int condition = 0;
	int ele = boundry.ele;

	if (boundry.node1 == (elements[ele].node1-1) && boundry.node2 == (elements[ele].node2-1)) // t = -1
	{
		condition = 1;
		c1 = 0, c2 = 6;
	}
	else if (boundry.node1 == (elements[ele].node2-1) && boundry.node2 == (elements[ele].node3-1)) // s = 1
	{
		condition = 2;
		c1 = 6, c2 = 12;
	}
	else if (boundry.node1 == (elements[ele].node3-1) && boundry.node2 == (elements[ele].node4-1)) // t = 1
	{
		condition = 3;
		c1 = 12, c2 = 18;
	}
	else if (boundry.node1 == (elements[ele].node4-1) && boundry.node2 == (elements[ele].node1-1)) // s = -1
	{
		condition = 4;
		c1 = 18, c2 = 0;
	}
	cout << "condition " << condition << endl;

	vector<BB> BB_results_mat;
	
	double xcoord[4];
	xcoord[0] = nodes[elements[ele].node1-1].x_cord;
	xcoord[1] = nodes[elements[ele].node2-1].x_cord;
	xcoord[2] = nodes[elements[ele].node3-1].x_cord;
	xcoord[3] = nodes[elements[ele].node4-1].x_cord;

	double ycoord[4];
	ycoord[0] = nodes[elements[ele].node1-1].y_cord;
	ycoord[1] = nodes[elements[ele].node2-1].y_cord;
	ycoord[2] = nodes[elements[ele].node3-1].y_cord;
	ycoord[3] = nodes[elements[ele].node4-1].y_cord;
	
	BB_results_mat = get_BB_results_mat(condition, order, xcoord, ycoord, values);

	if (condition == 2 || condition == 4) {
	value = 0.0;
	value2 = 0.0;
	value3 = 0.0;
	for (int i = 0; i < order; i++) {
		if (condition==2)
			var = sqrt(pow(BB_results_mat[i].Jmat[0][1], 2) + pow(BB_results_mat[i].Jmat[1][1], 2));
		else
		 	var = -sqrt(pow(BB_results_mat[i].Jmat[0][1], 2) + pow(BB_results_mat[i].Jmat[1][1], 2));
		value += weights[i] * var;
		value2 += weights[i] * var * BB_results_mat[i].x;
		value3 += weights[i] * var * BB_results_mat[i].y;
	}
	f1 = value; // h1
	m1 = value2; // x*h1
	m3 = value3; // y*h1
	value = 0.0;
	value2 = 0.0;
	value3 = 0.0;
	for (int i = 0; i < order; i++) {
		if (condition==2)
			var = sqrt((BB_results_mat[i].x - bc_x1) * (BB_results_mat[i].x - bc_x1) + (BB_results_mat[i].y - bc_y1) * (BB_results_mat[i].y - bc_y1)) * sqrt(pow(BB_results_mat[i].Jmat[0][1], 2) + pow(BB_results_mat[i].Jmat[1][1], 2))/ len;
		else
			var = -sqrt((BB_results_mat[i].x - bc_x1) * (BB_results_mat[i].x - bc_x1) + (BB_results_mat[i].y - bc_y1) * (BB_results_mat[i].y - bc_y1)) * sqrt(pow(BB_results_mat[i].Jmat[0][1], 2) + pow(BB_results_mat[i].Jmat[1][1], 2))/ len;
		value += weights[i] * var;
		value2 += weights[i] * var * BB_results_mat[i].x;
		value3 += weights[i] * var * BB_results_mat[i].y;
	}
	f2 = value; // h2 
	m2 = value2;  // x*h2
	m4 = value3; // y*h2
	fmat[0][0] = 1;
	fmat[1][2] = 1;
	fmat[2][1] = 1;
	fmat[3][3] = 1;

	}
	
	else if (condition == 1 || condition == 3) {
	value = 0.0;
	value2 = 0.0;
	value3 = 0.0;
	for (int i = 0; i < order; i++) {
		if (condition==1)
			var = sqrt(pow(BB_results_mat[i].Jmat[1][0], 2) + pow(BB_results_mat[i].Jmat[0][0], 2));
		else
			var = -sqrt(pow(BB_results_mat[i].Jmat[1][0], 2) + pow(BB_results_mat[i].Jmat[0][0], 2));
		value += weights[i] * var;
		value2 += weights[i] * var * BB_results_mat[i].x;
		value3 += weights[i] * var * BB_results_mat[i].y;
	}
	f1 = value; // h1
	m1 = value2; // x*h1
	m3 = value3; // y*h1
	value = 0.0;
	value2 = 0.0;
	value3 = 0.0;
	for (int i = 0; i < order; i++) {
		if (condition==1)
			var = sqrt((BB_results_mat[i].x - bc_x1) * (BB_results_mat[i].x - bc_x1) + (BB_results_mat[i].y - bc_y1) * (BB_results_mat[i].y - bc_y1)) * sqrt(pow(BB_results_mat[i].Jmat[1][0], 2) + pow(BB_results_mat[i].Jmat[0][0], 2))/ len;
		else
			var = -sqrt((BB_results_mat[i].x - bc_x1) * (BB_results_mat[i].x - bc_x1) + (BB_results_mat[i].y - bc_y1) * (BB_results_mat[i].y - bc_y1)) * sqrt(pow(BB_results_mat[i].Jmat[1][0], 2) + pow(BB_results_mat[i].Jmat[0][0], 2))/ len;
		value += weights[i] * var;
		value2 += weights[i] * var * BB_results_mat[i].x;
		value3 += weights[i] * var * BB_results_mat[i].y;
	}
	f2 = value; // h2 
	m2 = value2;  // x*h2
	m4 = value3; // y*h2
	fmat[0][1] = 1;
	fmat[1][3] = 1;
	fmat[2][0] = 1;
	fmat[3][2] = 1;
	}

	fmat[4][0] = f1 - f2;
	fmat[4][2] = f2;
	fmat[5][1] = f1 - f2;
	fmat[5][3] = f2;
	fmat[6][0] = m4 - m3;
	fmat[6][1] = m1 - m2;
	fmat[6][2] = -m4;
	fmat[6][3] = m2;
	
	if (condition == 2 || condition == 4) {
	kmat[0][4] = nx;
	kmat[0][5] = -ny;
	kmat[2][3] = ny;
	kmat[2][5] = -nx;
	kmat[1][10] = nx;
	kmat[1][11] = -ny;
	kmat[3][9] = ny;
	kmat[3][11] = -nx;
	
	for (int i = 0; i < 6; i++) {
		value = 0;
		value2 = 0;
		value3 = 0;
		for (int j = 0; j < order; j++)
		{
			if (condition==2)
				var = sqrt(pow(BB_results_mat[j].Jmat[0][1], 2) + pow(BB_results_mat[j].Jmat[1][1], 2));
			else
				var = -sqrt(pow(BB_results_mat[j].Jmat[0][1], 2) + pow(BB_results_mat[j].Jmat[1][1], 2));
			value += weights[j] * (BB_results_mat[j].Bsmat[0][i + c1] * nx + BB_results_mat[j].Bsmat[2][i + c1] * ny) * var;
			value2 += weights[j] * (BB_results_mat[j].Bsmat[2][i + c1] * nx + BB_results_mat[j].Bsmat[1][i + c1] * ny) * var;
			value3 += weights[j] * (BB_results_mat[j].x * BB_results_mat[j].Bsmat[1][i + c1] * ny - BB_results_mat[j].y * BB_results_mat[j].Bsmat[0][i + c1] * nx + BB_results_mat[j].Bsmat[2][i + c1] * (BB_results_mat[j].x * nx - BB_results_mat[j].y * ny)) * var;
		}
		kmat[4][i] = value; // (Bsmat[0][i]*nx*h1) + (Bsmat[2][i]*ny*h1))
		kmat[5][i] = value2; // (Bsmat[2][i]*nx*h1) + (Bsmat[1][i]*ny*h1))
		kmat[6][i] = value3;	// (x*Bsmat[1][i]*ny*h1) - (y*Bsmat[0][i]*nx*h1) + Bsmat[2][i]*(x*nx - y*ny)*h1)
		value = 0;
		value2 = 0;
		value3 = 0;
		for (int j = 0; j < order; j++)
		{
			if (condition==2)
				var = sqrt(pow(BB_results_mat[j].Jmat[0][1], 2) + pow(BB_results_mat[j].Jmat[1][1], 2));
			else
				var = -sqrt(pow(BB_results_mat[j].Jmat[0][1], 2) + pow(BB_results_mat[j].Jmat[1][1], 2));
			value += weights[j] * (BB_results_mat[j].Bsmat[0][i + c2] * nx + BB_results_mat[j].Bsmat[2][i + c2] * ny) * var;
			value2 += weights[j] * (BB_results_mat[j].Bsmat[2][i + c2] * nx + BB_results_mat[j].Bsmat[1][i + c2] * ny) * var;
			value3 += weights[j] * (BB_results_mat[j].x * BB_results_mat[j].Bsmat[1][i + c2] * ny - BB_results_mat[j].y * BB_results_mat[j].Bsmat[0][i + c2] * nx + BB_results_mat[j].Bsmat[2][i + c2] * (BB_results_mat[j].x * nx - BB_results_mat[j].y * ny)) * var;
		}
		kmat[4][i + 6] = value; // (Bsmat[0][i]*nx*h1) + (Bsmat[2][i]*ny*h1))
		kmat[5][i + 6] = value2; // (Bsmat[2][i]*nx*h1) + (Bsmat[1][i]*ny*h1))
		kmat[6][i + 6] = value3;	//(x*Bsmat[1][i]*ny*h1) - (y*Bsmat[0][i]*nx*h1) + Bsmat[2][i]*(x*nx - y*ny)*h1)
	}
	}

	else if (condition == 1 || condition == 3) {
	kmat[0][5] = -nx;
	kmat[0][3] = ny;
	kmat[2][5] = -ny;
	kmat[2][4] = nx;
	kmat[1][11] = -nx;
	kmat[1][9] = ny;
	kmat[3][11] = -ny;
	kmat[3][10] = nx;

		
		for (int i = 0; i < 6; i++) {
		value = 0;
		value2 = 0;
		value3 = 0;
		for (int j = 0; j < order; j++)
		{
			if (condition==1)
				var = sqrt(pow(BB_results_mat[j].Jmat[1][0], 2) + pow(BB_results_mat[j].Jmat[0][0], 2));
			else
				var = -sqrt(pow(BB_results_mat[j].Jmat[1][0], 2) + pow(BB_results_mat[j].Jmat[0][0], 2));
			value += weights[j] * (BB_results_mat[j].Bsmat[0][i + c1] * nx + BB_results_mat[j].Bsmat[2][i + c1] * ny) * var;
			value2 += weights[j] * (BB_results_mat[j].Bsmat[2][i + c1] * nx + BB_results_mat[j].Bsmat[1][i + c1] * ny) * var;
			value3 += weights[j] * (BB_results_mat[j].x * BB_results_mat[j].Bsmat[1][i + c1] * ny - BB_results_mat[j].y * BB_results_mat[j].Bsmat[0][i + c1] * nx + BB_results_mat[j].Bsmat[2][i + c1] * (BB_results_mat[j].x * nx - BB_results_mat[j].y * ny)) * var;
		}
		kmat[4][i] = value; // (Bsmat[0][i]*nx*h1) + (Bsmat[2][i]*ny*h1))
		kmat[5][i] = value2; // (Bsmat[2][i]*nx*h1) + (Bsmat[1][i]*ny*h1))
		kmat[6][i] = value3;	// (x*Bsmat[1][i]*ny*h1) - (y*Bsmat[0][i]*nx*h1) + Bsmat[2][i]*(x*nx - y*ny)*h1)
		value = 0;
		value2 = 0;
		value3 = 0;
		for (int j = 0; j < order; j++)
		{
			if (condition==1)
				var = sqrt(pow(BB_results_mat[j].Jmat[1][0], 2) + pow(BB_results_mat[j].Jmat[0][0], 2));
			else
				var = -sqrt(pow(BB_results_mat[j].Jmat[1][0], 2) + pow(BB_results_mat[j].Jmat[0][0], 2));
			value += weights[j] * (BB_results_mat[j].Bsmat[0][i + c2] * nx + BB_results_mat[j].Bsmat[2][i + c2] * ny) * var;
			value2 += weights[j] * (BB_results_mat[j].Bsmat[2][i + c2] * nx + BB_results_mat[j].Bsmat[1][i + c2] * ny) * var;
			value3 += weights[j] * (BB_results_mat[j].x * BB_results_mat[j].Bsmat[1][i + c2] * ny - BB_results_mat[j].y * BB_results_mat[j].Bsmat[0][i + c2] * nx + BB_results_mat[j].Bsmat[2][i + c2] * (BB_results_mat[j].x * nx - BB_results_mat[j].y * ny)) * var;
		}
		kmat[4][i + 6] = value; // (Bsmat[0][i]*nx*h1) + (Bsmat[2][i]*ny*h1))
		kmat[5][i + 6] = value2; // (Bsmat[2][i]*nx*h1) + (Bsmat[1][i]*ny*h1))
		kmat[6][i + 6] = value3;	// (x*Bsmat[1][i]*ny*h1) - (y*Bsmat[0][i]*nx*h1) + Bsmat[2][i]*(x*nx - y*ny)*h1)
	}
	}
	for (int a=0; a<7; a++) {
		for (int b=0; b<12; b++) {
			if (kmat[a][b] <= TOL && kmat[a][b] >= -TOL)
				kmat[a][b] = 0;
		}
	}
	for (int a=0; a<7; a++) {
		for (int b=0; b<4; b++) {
			if (fmat[a][b] <= TOL && fmat[a][b] >= -TOL)
				fmat[a][b] = 0;
		}
	}
	cout<<"Finished Kmat and Fmat"<<endl;
	result.Fmat = fmat;
	result.Kmat = kmat;
	return result;
}

	
    vector<BB> BB_results_mat;
    vector<BB> BB_results_k2 = get_BB_results_mat(2, order, xcoord, ycoord, GQdata.value);
    vector<BB> BB_results_k4 = get_BB_results_mat(4, order, xcoord, ycoord, GQdata.value);
    vector<BB> BB_results_k3 = get_BB_results_mat(3, order, xcoord, ycoord, GQdata.value);
    vector<BB> BB_results_k1 = get_BB_results_mat(1, order, xcoord, ycoord, GQdata.value);
    vector<vector<double>> A;

    int rank = compute_rank(A);

    // Output results for verification
    cout << "Order: " << order << endl;
    cout << "GQ Weights: ";
    for (double w : GQdata.weight) {
        cout << w << " ";
    }
    cout << endl;

    cout << "GQ Values: ";
    for (double v : GQdata.value) {
        cout << v << " ";
    }
    cout << endl;

    cout << "Rank of matrix A: " << rank << endl;

    // Output BB results for verification
    cout << "BB Results for k=2:" << endl;
    for (const BB& bb : BB_results_k2) {
        cout << "x: " << bb.x << ", y: " << bb.y << endl;
    }

cout << "BB Results for k=4:" << endl;
    for (const BB& bb : BB_results_k4) {
        cout << "x: " << bb.x << ", y: " << bb.y << endl;
    }

    cout << "BB Results for k=3:" << endl;
    for (const BB& bb : BB_results_k3) {
        cout << "x: " << bb.x << ", y: " << bb.y << endl;
    }

    cout << "BB Results for k=1:" << endl;
    for (const BB& bb : BB_results_k1) {
        cout << "x: " << bb.x << ", y: " << bb.y << endl;
    }


}
