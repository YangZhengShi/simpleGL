#include <iostream>
#include <cstdlib>
#include <unistd.h>
using namespace std;

#include "../headers/graphics.h"
//#include "../utils/simple_initializer.h" 
#include "../utils/simple_math.h"

namespace fl{

struct vec3{
	float x;
	float y;
	float z;
};

}

bool compare_z(const fl::vec3& p1, const fl::vec3& p2){
	return (p1.z < p2.z);
}

bool compare_y(const fl::vec3& p1, const fl::vec3& p2){
	return (p1.y < p2.y);
}

bool compare_x(const fl::vec3& p1, const fl::vec3& p2){
	return (p1.x < p2.x);
}

void sort_by_y(float* begin, float* end){
	sort((fl::vec3*)begin, (fl::vec3*)end, compare_y); 
}
	
void sort_by_z(float* begin, float* end){
	sort((fl::vec3*)begin, (fl::vec3*)end, compare_z); 
}

void sort_by_x(float* begin, float* end){
	sort((fl::vec3*)begin, (fl::vec3*)end, compare_x); 
}


int main(int argc, char **argv){

	float ptest[] = {1, 2, 3, 2, 3, 2, 3, 1, 1};
//	vector <float> ptvec(ptest, ptest+9);

	sort_by_y(ptest, ptest + 9);
	for (int i=0; i<9; ++i) cout << ptest[i] << " ";
	cout << "\n-----------------------------" << endl;

	int nverts;
	float *pos9;
	float *col9;
	
	ifstream fin("odm_georeferenced_model.ply");
	string s, u;
	int prop_count = 0;
	while (fin >> s && s != "end_header"){
		if (s == "element"){
			fin >> u;
			if (u == "vertex") fin >> nverts;
		}
		if (s == "property") ++prop_count;
	}

	nverts = 100000;
	cout << "PLY: vertices = " << nverts << ", properties = " << prop_count << endl; 	

	

	pos9 = new float[3*nverts];
	col9 = new float[4*nverts];
	
	float * vals = new float[prop_count];
	
	for (int i=0; i<nverts; ++i){
		for (int k=0; k<prop_count; ++k){
			fin >> vals[k];
		}
		pos9[3*i+0] = vals[1];
		pos9[3*i+1] = vals[2];
		pos9[3*i+2] = vals[0];
		
		col9[4*i+0] = vals[3]/255; 
		col9[4*i+1] = vals[4]/255; 
		col9[4*i+2] = vals[5]/255; 
		col9[4*i+3] = 1;
	} 
	

	for (int i=0; i<5; ++i){
		cout << 
		pos9[3*i+0] << " " << 
		pos9[3*i+1] << " " << 
		pos9[3*i+2] << " " << endl;
		//col9[i].x << " " << col9[i].y << " " << col9[i].z << " " << col9[i].w << endl;  
	} 

//	for (int i=0; i<6; ++i) cout << pos9[3*i] << " " << pos9[3*i+1] << " " << pos9[3*i+2] << endl;
	cout << "sort...\n";
	sort_by_y(pos9, pos9+3*nverts); 
	for (int i=0; i<10; ++i) cout << pos9[3*i] << " " << pos9[3*i+1] << " " << pos9[3*i+2] << endl;
 
	init_hyperGL(&argc, argv);

	Palette p(100);
	p.create_rainbow();
//	p.print();
	
	float pos11[] = {-1.1, 1, 1.1, -2.2, 2, 2.2, -3.3, 3, 3.3};
	vector <float> cols11z = p.map_values(&pos11[1], 3, 3); 

	vector <float> cols9z = p.map_values(&pos9[1], nverts, 3);

	Shape pt(nverts, 3, "points"); //, 4, -1, 1);
//	pt.createShaders();
	pt.pointSize = 1;
	pt.setVertices(pos9);	
//	pt.createColorBuffer();
//	pt.setColors(col9);
	pt.setColors(&cols9z[0]);
	pt.autoExtent(pos9);


//	float pos[] = { 50, 50, -10,//0.5,
//				  25, 50, -20,//-0.5,
//				  50,  25, -30,//  -1,
//				  25,   25, 0 //  1,
//				};

//	float4 col[] = {make_float4(1,1,1, 1),
//				    make_float4(1,0,0, 1),
//				    make_float4(0,1,0, 1),
//				    make_float4(0,0,1, 1)
//				   };

//	
////	int nx = 100, ny = 100;  
////	float L = 2;
////	ColorMap res_shape("res", 100, nx, 0, L);
////	float2 cmap_pos[res_shape.nVertices];
////	res_shape.createGridCentres(cmap_pos); 
////	res_shape.createShaders();
////	res_shape.createVBO(cmap_pos, res_shape.nVertices*sizeof(float2));	
////	res_shape.createColorBuffer();
////	vector <float> res(nx*ny); for (int i=0; i<nx*ny; ++i) res[i]=i; 
////	res_shape.updateColors(&res[0], nx*ny);


//	Shape pt(4, 3, "points"); //, 4, -1, 1);
////	pt.createShaders();
//	pt.pointSize = 4;
//	pt.setVertices(pos);	
////	pt.createColorBuffer();
//	pt.setColors(col);
//	pt.autoExtent(pos);
////	pt.setDefaultColor();
//	

//	float pos2[] = { -.25, -.25, //0,//0.5,
//				  -.25, .25, //0,//-0.5,
//				  .25,  -.25, //0,//  -1,
//				  .25,   .25 //0 //  1,
//					};

//	float4 col2[] = {make_float4(1,1,0, 0.5),
//				    make_float4(1,0,1, 0.5),
//				    make_float4(0,1,0, 0.5),
//				    make_float4(1,1,1, 0.5)
//				   };
//					
//	Shape2D pt2(4, "triangles");
//	pt2.setVertices(pos2);
//	pt2.setColors(col2);
//	pt2.setExtent(-.5, .5, -.5, .5);
	
	float pos3[] = {-100,0,0, 100,0,0, 0,-100,0, 0,100,0, 0,0,-100, 0,0,100};
	float col3[] = {1,0,0, 0.5	,
				     1,0,0, 0.5,
				     0,1,0, 0.5,
				     0,1,0, 0.5,
				     0.0,0.8,1, 0.5,
				     0.0,0.8,1, 0.5
				   };
	
	Shape axis(6, 3, "lines");
	axis.setVertices(pos3);
	axis.setColors((float*)col3);
//	axis.autoExtent(pos3);

//	Palette p(20);
//	p.create_grayscale();
//	p.print();
//	
//	float v[] = {0.1, 0.2, 0.3, 0.4, 0.1, 0.2, 0.3, 0.4};
//	vector <glm::vec4> c = p.map_values(v, 8);
//	for (int i=0; i<8; ++i) cout << c[i].r << " " << c[i].g << " " << c[i].b << " " << c[i].a << "\n";
//	cout << endl; 
	
	
	while(1){       // infinite loop needed to poll anim_on signal.
		glutMainLoopEvent();
		usleep(20000);
	}
	// launch sim end.
	
	return 0;
}



