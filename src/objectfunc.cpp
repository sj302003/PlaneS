#include "objectfunc.h"
#include "constraints.h"
#include "initialize.h"
#include <vector>
#include <cmath>
#include <omp.h>

Cnstrelret LinElast(double *stress, double *strain, vector<double> matpar) {
	
	for (int i = 0; i < 3; i++) {
		delvalue.push_back(0);
		Cmat.push_back(tempmat);
		Emat.push_back(tempmat);
		for (int j = 0; j < 3; j++){
			Cmat[i][j] = 0;
			Emat[i][j] = 0;
		}
	}
	
	Cmat[0][0] = Cmat[1][1] = -1/matpar[0];
	Cmat[0][1] = Cmat[1][0] = matpar[1]/matpar[0];
	Cmat[2][2] = -2*(1 + matpar[1])/matpar[0];
	Emat[0][0] = Emat[1][1] = Emat[2][2] = 1;
	
	for (int i = 0; i < 3; i++) {
		delvalue[i] = strain[i];
		for (int j = 0; j < 3; j++) {
			delvalue[i] = delvalue[i] + Cmat[i][j]*stress[j];
		}
	}
	Cnstrelret LEresult;
	LEresult.delval = delvalue;
	LEresult.dfdstrain = Emat;
	LEresult.dfdstress = Cmat;
	return LEresult;
}

Errret ErrGQ(double *uval, double *phival, double *xcord, double *ycord, int mattype, vector<double> mtpar, double dispscalefac, int order) {
	Initialize init;
	GQVandW GQresult;
	Cnstrelret Cnstreldat;
	vector<double> values;
	vector<double> weights;
	GQresult = init.getWeightAndValues(order);
	values = GQresult.value;
	weights = GQresult.weight;
	double sts[3];	
	double strn[3];
	vector<vector<double>> dfdstrn;
	vector<vector<double>> dfdsts;
	double errval = 0;
	double reqBd[8][3];
	double reqBs[24][3];	
	double ki[32];
	vector<double> Ivals;
	vector<double> delvalue;
	double objint = 0;
	double detJ=0;
	Errret ErrAGradval;
	for (int k=0;k<32;k++){
		Ivals.push_back(0);
	}
	for(int i=0; i<order; i++) {
		for (int j = 0; j<order; j++) {			
			BB BBresult = init.Bsigma_Bd(xcord,ycord,values[i],values[j]);
			detJ = BBresult.detJ;
			for (int k = 0; k < 3; k++) {
				sts[k] = 0;
				for (int l = 0; l < 24; l++) {
					sts[k] = sts[k] + BBresult.Bsmat[k][l]*phival[l];
				}
			}
			for (int k = 0; k < 3; k++) {
				strn[k] = 0;
				for (int l = 0; l < 8; l++) {
					strn[k] = strn[k] + BBresult.Bd[k][l]*uval[l];
				}
			}
			switch (mattype){
				case 1: Cnstreldat = LinElast(sts,strn,mtpar);
					break;
					
			}
			delvalue = Cnstreldat.delval;
			dfdstrn = Cnstreldat.dfdstrain;
			dfdsts = Cnstreldat.dfdstress;
			objint = 0;
			for(int k=0; k<3; k++){
				objint = objint + delvalue[k]*delvalue[k];
			}
			errval = errval + detJ*weights[i]*weights[j]*sqrt(objint);	
			for (int k = 0; k < 8; k++) {		
				//cout<<endl;		
				for (int l = 0; l <3; l++) {
					reqBd[k][l] = 0;
					for(int m=0; m<3; m++){
						reqBd[k][l] = reqBd[k][l] + BBresult.Bd[m][k]*dfdstrn[l][m];
					}
				}
			}
			
			for (int k = 0; k < 8; k++) {
				ki[k] = 0;
				for (int l = 0; l < 3; l++) {
					ki[k] = ki[k] + reqBd[k][l]*delvalue[l]/dispscalefac/sqrt(objint);
				}
				Ivals[k] = Ivals[k]+detJ*weights[i]*weights[j]*ki[k];
			}
			for (int k = 0; k < 24; k++) {	
				for (int l = 0; l <3; l++) {
					reqBs[k][l] = 0;
					for(int m=0; m<3; m++){
						reqBs[k][l] = reqBs[k][l] + BBresult.Bsmat[m][k]*dfdsts[l][m];
					}
				}
			}
			for (int k = 0; k < 24; k++) {
				ki[k+8] = 0;
				for (int l = 0; l < 3; l++) {
					ki[k+8] = ki[k+8] + reqBs[k][l]*delvalue[l]/sqrt(objint);
				}
				Ivals[k+8] = Ivals[k+8] + detJ*weights[i]*weights[j]*ki[k+8];
			}
		}
	}
	ErrAGradval.errv = errval;
	ErrAGradval.grdval = Ivals;
	return ErrAGradval;
}

void myconstraint(unsigned m, double *result, unsigned n, const double *x, double* grad, void *cdat)
{
	constdata *d = (constdata *) cdat;
	vector<vector<double>> Amatrix = d->Amat;
	vector<double> frcvec = d->Fvec;
	double ScaleFac = 1;
	if (grad == nullptr){
		free(grad1);
		grad1 = (double*) malloc(Amatrix.size() * Amatrix[0].size() * sizeof(double));
		for (int i = 0; i < Amatrix.size()*Amatrix[0].size(); i++) grad1[i] = 0;
		
		grad = grad1;	
	}

	for (int i = 0; i < Amatrix.size(); i++) {
		result[i] = -frcvec[i];
		for (int j = 0; j < n; j++) {
			result[i] = result[i] + Amatrix[i][j]*x[j];
			grad[i*n+j] = Amatrix[i][j];
		}
		result[i] = result[i]*ScaleFac;
	}
	return;
}

double myfunc(unsigned n, const double *x, double *grad, void *f_data)
{
	cout<<"Objective function value: ";
	double s1 = omp_get_wtime();

	objdata *d = (objdata *)f_data;
	vector<node> nodecords = d->nodecord;
	vector<element> ele = d->elemdat;
	int numnodes = d->numnode;
	int numelem = d->numele;
	int lenpos = d->lnpos;
	double dispscalefac = d->dispscalefac;

	if (grad == nullptr){
		free(grad2);
		grad2 = (double*) malloc((8*numnodes+lenpos) * sizeof(double));
		grad = grad2;	
	}

	for (int i=0; i<(8*numnodes+lenpos); i++){
		grad[i] = 0;
	}

	for (int e=0; e<numelem; e++){
		cout<<"Check Obj 1"<<endl;
		vector<double> matparv;
		elenodes[0] = ele[e].node1-1;
		elenodes[1] = ele[e].node2-1;
		elenodes[2] = ele[e].node3-1;
		elenodes[3] = ele[e].node4-1;		
		xcoord[0] = nodes[elenodes[0]].x_cord;
		xcoord[1] = nodes[elenodes[1]].x_cord;
		xcoord[2] = nodes[elenodes[2]].x_cord;
		xcoord[3] = nodes[elenodes[3]].x_cord;
		ycoord[0] = nodes[elenodes[0]].y_cord;
		ycoord[1] = nodes[elenodes[1]].y_cord;
		ycoord[2] = nodes[elenodes[2]].y_cord;
		ycoord[3] = nodes[elenodes[3]].y_cord;
		numpar = ele[e].nummatpar;
		cout<<"Check Obj 2"<<endl;

		for(int i=0;i<numpar;i++){
			matparv.push_back(ele[e].matpar[i]);
		}
        
		for(int i=0; i<4; i++){
			u_pos[2*i] = 2*elenodes[i];
			u_pos[2*i+1] = 2*elenodes[i]+1;
			u_val[2*i] = x[u_pos[2*i]]/dispscalefac;
			u_val[2*i+1] = x[u_pos[2*i+1]]/dispscalefac;

			for (int c=0; c<6;c++){
				phi_pos[6*i+c] = numnodes*2+6*elenodes[i]+c;
				phi_val[6*i+c] = x[phi_pos[6*i+c]];
			}
		}

		ErrAGrad = ErrGQ(u_val,phi_val,xcoord,ycoord,ele[e].mattype,matparv,dispscalefac,GQorder);
		gradval = ErrAGrad.grdval;
		cout<<"Check Obj 3"<<endl;
		
		for (int i = 0; i < 8; i++) {
			grad[u_pos[i]] = grad[u_pos[i]] + gradval[i]*ScaleFac;
		}

		for (int i=0; i<24; i++){
			grad[phi_pos[i]] = grad[phi_pos[i]] + gradval[i+8]*ScaleFac;
		}
		errval = errval + ErrAGrad.errv;			
	}
	errval = errval*ScaleFac;
	cout<<errval<<endl;

	double e1 = omp_get_wtime();
	obj_exec_time += e1 - s1;

	return errval;
}
