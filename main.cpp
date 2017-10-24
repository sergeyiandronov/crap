#include <iostream>
#include <sstream>
using namespace std;
struct mtrx{
bool Succes=false;
int Row;
int Column;
float **Matrix;
};
mtrx InitZero(int columns,int rows){
mtrx result;
float **matrix;

     matrix = new float *[ rows];
for(  int i = 0; i < rows; ++i ) {
    matrix[ i ] = new float[ columns];
for( int j = 0; j < columns; ++j ) {
        matrix[ i ][ j ] = 0.0f;
    }
}
result.Succes=true;result.Matrix=matrix;result.Column=columns;result.Row=rows;
return result;
	
}
mtrx sum(mtrx Mat1,mtrx Mat2){
     mtrx result;
     result=InitZero(Mat1.Column,Mat1.Row);
     if((Mat1.Row==Mat2.Row)&&(Mat1.Column==Mat2.Column)){
     	for(int j=0;j<Mat1.Row;j++){
     		for(int i=0;i<Mat1.Column;i++){
     			result.Matrix[j][i]=Mat1.Matrix[j][i]+Mat2.Matrix[j][i];
     		}
     	} 
     }else{result.Succes=false;}
     return result;
}
mtrx sub(mtrx Mat1,mtrx Mat2){
     mtrx result;
     result=InitZero(Mat1.Column,Mat1.Row);
     if((Mat1.Row==Mat2.Row)&&(Mat1.Column==Mat2.Column)){
     	for(int j=0;j<Mat1.Row;j++){
     		for(int i=0;i<Mat1.Column;i++){
     			result.Matrix[j][i]=Mat1.Matrix[j][i]-Mat2.Matrix[j][i];
     		}
     	} 
     }else{result.Succes=false;}
     return result;
}
mtrx mul(mtrx Mat1,mtrx Mat2){
     mtrx result;
     result=InitZero(Mat2.Column,Mat1.Row);
     if(Mat1.Column==Mat2.Row){
     	for(int j=0;j<Mat1.Row;j++){
     		for(int i=0;i<Mat2.Column;i++){
     			float y=0;
     			for(int z=0;z<Mat1.Column;z++){
     			    y+=Mat1.Matrix[j][z]*Mat2.Matrix[z][i];	
     			}
     			result.Matrix[j][i]=y;
     		}
     	} 
     }else{result.Succes=false;}
     return result;
}
mtrx Tr(mtrx Mat){
     mtrx result;
     result=InitZero(Mat.Row,Mat.Column);
     
     	for(int j=0;j<Mat.Column;j++){
     		for(int i=0;i<Mat.Row;i++){
     			result.Matrix[j][i]=Mat.Matrix[i][j];
     		}
     	} 
     
     return result;
}
bool getMatrix(float **matrix,int ncolumns,int nrows){


	for(int j=0;j<nrows;j++){
                   		string newrow;	
	       getline(cin,newrow);
	       istringstream stream(newrow);
	       for(int i=0;i<ncolumns;i++){
	       	if(!(stream>>matrix[j][i])){
	       		return false;
	       	}
	       }
	}
	return true;
	
}

void coutMatrix(mtrx Matsign){
	for(int j=0;j<Matsign.Row;j++){
	       for(int i=0;i<Matsign.Column;i++){
	       	
	       	cout<<Matsign.Matrix[j][i]<<" ";
	       }cout<<"\n";
	}
}
mtrx getfullMatrix(){
mtrx result;
float **matrix;
string header;
int rows;
int columns;
        char razdel;
       getline(cin,header);
        istringstream str(header);
        if((str>>rows)&&(str>>razdel)&&(str>>columns)&&(razdel==',')){
     matrix = new float *[ rows];
for(  int i = 0; i < rows; ++i ) {
    matrix[ i ] = new float[ columns];
for( int j = 0; j < columns; ++j ) {
        matrix[ i ][ j ] = 0.0f;
    }
}result.Succes=getMatrix(matrix,columns,rows);result.Row=rows;result.Column=columns;result.Matrix=matrix;return result;}result.Succes=false;return result;}
int main(){
	mtrx Mat3sign;
	 
        mtrx Mat1sign;
mtrx Mat2sign;
string strop;
char op;
Mat1sign=getfullMatrix();
getline(cin, strop);
istringstream streamop(strop);
streamop>>op;

if(Mat1sign.Succes){switch(op){
case 'T':
    Mat3sign=Tr(Mat1sign);
    
    break;
case 'R':
    
    break;
default:if((op!='+')&&(op!='-')&&(op!='*')){exit(0);}
    break;
}}else{exit(0);}
if(Mat3sign.Succes){
	coutMatrix(Mat3sign);
	exit(0);
}
Mat2sign=getfullMatrix(); 

  if(Mat2sign.Succes){
          switch(op){
case '+':
Mat3sign=sum(Mat1sign,Mat2sign);
break;
case '*':Mat3sign=mul(Mat1sign,Mat2sign);
break;
case '-':Mat3sign=sub(Mat1sign,Mat2sign);
break;

}else{exit(0);}


}
        
if((Mat1sign.Succes)&&(Mat2sign.Succes)&&(Mat3sign.Succes)){
	coutMatrix(Mat3sign);
}else{exit(0)}



  }
