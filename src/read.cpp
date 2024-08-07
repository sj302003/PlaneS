#include "read.h"
#include "constraints.h"
#include <fstream>
#include <sstream>
#include <iostream>

Read::Read() {};

void Read::node_reader(vector<Oceane::Nodeptr>& x, string name)
{
  // reading codrinates of nodes
	ifstream infile_node_cord(name);

    if (!infile_node_cord) {
        std::cerr << "Error opening file: " << name << std::endl;
        return;
    }

	int i;
	double ix, iy;
	while (infile_node_cord >>i >>ix >>iy) {
		node n;
		n.id = i;
		std::cout<<n.id<<" "<<endl;
		n.x_cord = ix;
		n.y_cord = iy;
		nodes.push_back(n);
		numnode++;
	}
	infile_node_cord.close();
	//cout <<"Finished reading node coordinates"<<endl;
	//cout<<"Number of nodes = " << nodes.size() << endl;
}

void Read::element_reader(vector<vector<string>>& x, vector<Oceane::Elementptr>& y, vector<vector<double>>& z, vector<Oceane::Nodeptr> nodes, string name){
    //reading node connectivity or elements
	ifstream infile_ele(name);

     if (!infile_ele) {
        std::cerr << "Error opening file: " << name << std::endl;
        return;
    }

    int numele = 0;	
	while (!infile_ele.eof()) {
		element tempe;
		vector<double> matpar_ele;
		infile_ele >> tempe.ele >> tempe.node1 >> tempe.node2 >> tempe.node3 >> tempe.node4 >> tempe.mattype >> tempe.nummatpar;
		for (int i=0; i < tempe.nummatpar; i++)
		{
			infile_ele >> tempmatpar;
			matpar_ele.push_back(tempmatpar);
		}
		tempe.matpar = matpar_ele;
		elements.push_back(tempe);
		numele++;
	}
	infile_ele.close();
	//cout << "Finished reading element data "<<numele<<endl;
}

void Read::boundary_condition_reader(vector<Oceane::Nodeptr>& x, string name)
{
  // reading boundary condition of elements
  //cout<<"Starting boundary conditions"<<endl;
	ifstream infile_boundry_con(name);

    if (!infile_boundry_con) {
        std::cerr << "Error opening file: " << name << std::endl;
        return;
    }
    
    // int bndsdes = 0;
	while (!infile_boundry_con.eof()) {
		bc temp;
		double dispvecval[4];
		double tracvecval[4];
		infile_boundry_con >> temp.ele >> temp.node1 >> temp.node2; 
		temp.ele = temp.ele-1;
		temp.node1 = temp.node1-1;
		temp.node2 = temp.node2-1;
		infile_boundry_con >> temp.tractvec[0]>>temp.tractvec[1]>>temp.tractvec[2]>>temp.tractvec[3];
		infile_boundry_con >> temp.dc_x1 >> temp.dc_y1 >> temp.dc_x2 >> temp.dc_y2;
		infile_boundry_con >> temp.dispvec[0]>>temp.dispvec[1]>>temp.dispvec[2]>>temp.dispvec[3];
		bc_arr.push_back(temp);
		bndsdes++;
	}
	infile_boundry_con.close();
	//bndsdes = bndsdes-1;
	bc temp;
	for (int a=0;a<bndsdes;a++)
	{
		temp = bc_arr[a];
		if (temp.dc_x1 == 1){
			dof = 2*temp.node1;
			cout<<"dof at x1 "<<dof<<endl;
			thereflg = 0;
			for (int i=0; i<rest_dispdof.size(); i++)
			{
				if (rest_dispdof[i] == dof){
					thereflg = 1;
					if (knwndisp[i]!=temp.dispvec[0])
						cout<<"Inconsistent displacement specification 1"<<endl;
				}
			}
			if (thereflg==0){
				rest_dispdof.push_back(dof);
				knwndisp.push_back(temp.dispvec[0]);
				count_dc++;
			}
		}
		if (temp.dc_y1 == 1){
			dof = 2*temp.node1+1;
			cout<<"dof at y1 "<<dof<<endl;			
			thereflg = 0;
			for (int i=0; i<rest_dispdof.size(); i++)
			{
				if (rest_dispdof[i] == dof){
					thereflg = 1;
					if (knwndisp[i]!=temp.dispvec[1])
						cout<<"Inconsistent displacement specification 2"<<endl;
				}
			}
			if (thereflg==0){
				rest_dispdof.push_back(dof);
				knwndisp.push_back(temp.dispvec[1]);
				count_dc++;
			}
		}
		if (temp.dc_x2 == 1){
			dof = 2*temp.node2;
			cout<<"dof at x2 "<<dof<<endl;			
			thereflg = 0;
			for (int i=0; i<rest_dispdof.size(); i++)
			{
				if (rest_dispdof[i] == dof){
					thereflg = 1;
					if (knwndisp[i]!=temp.dispvec[2])
						cout<<"Inconsistent displacement specification 3"<<endl;
				}
			}
			if (thereflg==0){
				rest_dispdof.push_back(dof);
				knwndisp.push_back(temp.dispvec[2]);				
				count_dc++;
			}
		}
		if (temp.dc_y2 == 1){
			dof = 2*temp.node2+1;
			cout<<"dof at y2 "<<dof<<endl;			
			thereflg = 0;
			for (int i=0; i<rest_dispdof.size(); i++)
			{
				if (rest_dispdof[i] == dof){
					thereflg = 1;
					if (knwndisp[i]!=temp.dispvec[3])
						cout<<"Inconsistent displacement specification 4"<<endl;
				}
			}
			if (thereflg==0){
				rest_dispdof.push_back(dof);
				knwndisp.push_back(temp.dispvec[3]);
				count_dc++;
			}
		}
	}

	// Sorting
	for(int i=0;i<count_dc;i++)
	{	
		// int tempdof;
		// double	tempdisp;
		for(int j=i+1;j<count_dc;j++)
		{
			if(rest_dispdof[i]>rest_dispdof[j])
			{
				// tempdof=rest_dispdof[i];
				// tempdisp = knwndisp[i];
				// rest_dispdof[i]=rest_dispdof[j];
				// knwndisp[i] = knwndisp[j];
				// rest_dispdof[j]=tempdof;
				// knwndisp[j] = tempdisp;
        swap(rest_dispdof[i], rest_dispdof[j]);
        swap(knwndisp[i], knwndisp[j]);
			}
		}
	}
	cout << "Printing resting disp" << endl;
	for(int i = 0 ; i < count_dc ; i++){
		cout << rest_dispdof[i] << " , ";
	}
	cout << endl;
	cout <<"Finished reading boundary conditions"<<endl;  
  //cout<<"count_dc: "<<count_dc<<endl;  
}

void Read::startreading()
{
    Read reader1;
    reader1.node_reader(m_nodes,"../PlaneS/files/nodecoord.txt");
    reader1.element_reader(funcname, m_elements, parameters, m_nodes, "../PlaneS/files/nodecon.txt");
    reader1.boundary_condition_reader(m_boundaryElements,"../PlaneS/files/boundcond_UE.txt");
    
}