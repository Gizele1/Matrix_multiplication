#pragma once
struct mat{
int col;
int row;
float *matrix;
};
struct mat generate(int row,int col,float matrix[]);
struct mat generateR(int row,int col);
void deletemat(struct mat *mat);
struct mat copymat( struct mat mat1);
struct mat mulmat(struct mat mat1,struct mat mat2);
float getvalueofmat(int i,int j,struct mat mat);
void setvalueofmat(int i,int j,float value,struct mat* mat);
