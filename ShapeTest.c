#include <malloc.h>
#include <stdio.h>

//Start of Shape Class

//setting up the vpointers
typedef double (*VirtualMethodPointer)(void *);

typedef VirtualMethodPointer * VTableType;

typedef struct{
	VTableType VPointer;
	const char* name;
}Shape;

double area(Shape * _this){
	return 0.0;
}
void draw(Shape * _this)
{
	printf("%s\n", _this->name);
}

VirtualMethodPointer Shape_VTable [] = {
	(VirtualMethodPointer)area, // VTable[0] - the first virtual method
	(VirtualMethodPointer)draw // VTable[1] - the second virtual method
};	

Shape * Shape_Shape(Shape * _this, const char * newName){
	_this->VPointer = Shape_VTable;
	_this->name = newName;
	//Constructors usually return void but it makes the example simpler
	return _this;
}



//End of Shape Class
//
//Start of Triangle Class

typedef struct{
	//extends Shape
	VTableType VPointer;
	const char* name;
	int myHeight;
	int myBase;
}Triangle;

double Triangle_area(Triangle * _this){
	return _this->myHeight * _this->myBase * 0.5;
}

void Triangle_draw(Triangle * _this){
	printf("%s\n",_this->name);
	printf("*\n");
	printf("**\n");
	printf("***\n");
	printf("****\n"); 
}

VirtualMethodPointer Triangle_VTable [] = {
	(VirtualMethodPointer)Triangle_area, //Override area
	(VirtualMethodPointer)Triangle_draw // override draw from Shape	
};

Triangle * Triangle_Triangle(Triangle * _this, const char* newName, int newHeight, int newBase){
	Shape_Shape((Shape *)_this, newName); // call parents constructor
	_this->VPointer = Triangle_VTable; // set the vpointer after parent
	_this->myHeight = newHeight;
	_this->myBase = newBase;	
	return _this;
}

//End of Triangle Class
//
//Start of Circle Class
#define PI 3.14159

typedef struct{
//extends Shape
	VTableType VPointer;
	const char* name;
	int  radius;
}Circle;

double Circle_area(Circle * _this){
	return PI * _this->radius * _this->radius;
}

void Circle_draw(Circle * _this){
	printf("%s\n", _this->name);
	printf(" ****\n");
	printf("*    *\n");
	printf(" **** \n");
}

VirtualMethodPointer Circle_VTable[] = {
	(VirtualMethodPointer)Circle_area, //Over-ride
	(VirtualMethodPointer)Circle_draw // override the Shape draw
};

Circle * Circle_Circle(Circle * _this, const char* newName, int newRadius){
	Shape_Shape((Shape *)_this, newName); 
	_this->VPointer = Circle_VTable; // set the vpointer after parent
	_this->radius = newRadius;
	return _this;
}

//End of Circle Class
//
//Start of Square calss

typedef struct{
	//extends Shape
	VTableType VPointer;
	const char* name;
	int side;
}Square;

double Square_area(Square * _this){
	return _this->side * _this->side;
}

void Square_draw(Square * _this){
	printf("%s\n", _this->name);
	printf("****\n");
	printf("*  *\n");
	printf("*  *\n");
	printf("****\n");
}

VirtualMethodPointer Square_VTable [] ={
	(VirtualMethodPointer)Square_area, // Over-ride
	(VirtualMethodPointer)Square_draw //Over-ride
};

Square * Square_Square(Square * _this, const char* newName, int newSide){
	Shape_Shape((Shape *) _this, newName);
	_this->VPointer = Square_VTable; // set the vnpointer AFter Parent
	_this->side = newSide;
	return _this;
}

//End of Square Class

//Start of rectangle Class

typedef struct{
	VTableType VPointer;
	const char* name;
	int side;
	int height;
}Rectangle;

double Rectangle_area(Rectangle * _this){
	return _this->side * _this->height;
}

void Rectangle_draw(Rectangle * _this){
	printf("%s\n", _this->name);
	printf("*********\n");
	printf("*       *\n");
	printf("*********\n");
}

VirtualMethodPointer Rectangle_VTable [] = {
	(VirtualMethodPointer)Rectangle_area, // OVerride
	(VirtualMethodPointer)Rectangle_draw // Override	
};

Rectangle * Rectangle_Rectangle(Rectangle * _this, const char* newName, int newSide, int newHeight){
	Square_Square((Square *)_this, newName, newSide);
	_this->VPointer = Rectangle_VTable;
	_this->height = newHeight;
	return _this;
}

//END of Rectangle Class
//
//Start of main Class
int main(){
	
	Shape * s[] = {
		//Shape Objects
		Shape_Shape((Shape *)malloc(sizeof(Shape)), "First Shape"),
		Shape_Shape((Shape *)malloc(sizeof(Shape)), "Second Shape"),
		Shape_Shape((Shape *)malloc(sizeof(Shape)), "Third Shape"),
		//Triangle Objects
		(Shape*)Triangle_Triangle((Triangle*)malloc(sizeof(Triangle)), "First Triangle", 5, 5),
		(Shape*)Triangle_Triangle((Triangle *)malloc(sizeof(Triangle)), "Second Triangle", 4, 3),
		(Shape*)Triangle_Triangle((Triangle *)malloc(sizeof(Triangle)), "Third Triangle", 2, 3),
		(Shape*)Triangle_Triangle((Triangle *)malloc(sizeof(Triangle)), "Fourth Triangle", 10, 2),
		(Shape*)Triangle_Triangle((Triangle *)malloc(sizeof(Triangle)), "Fifth Triangle", 2, 20),


		//Circle Objects
		(Shape*)Circle_Circle((Circle *)malloc(sizeof(Circle)), "First Circle", 6),
		(Shape*)Circle_Circle((Circle *)malloc(sizeof(Circle)), "Second Circle", 5),
		(Shape*)Circle_Circle((Circle *)malloc(sizeof(Circle)), "Third Circle", 4),
		(Shape*)Circle_Circle((Circle *)malloc(sizeof(Circle)), "Fourth Circle", 3),
		(Shape*)Circle_Circle((Circle *)malloc(sizeof(Circle)), "Fifth Circle", 2),


		//Square Objects
		(Shape*)Square_Square((Square *)malloc(sizeof(Square)), "First Square", 5),
		(Shape*)Square_Square((Square *)malloc(sizeof(Square)), "Second Square", 4),
		(Shape*)Square_Square((Square *)malloc(sizeof(Square)), "Third Square", 3),
		(Shape*)Square_Square((Square *)malloc(sizeof(Square)), "Fourth Square", 6),
		(Shape*)Square_Square((Square *)malloc(sizeof(Square)), "Fifth Square", 7),


		//Rectangle Objects
		(Shape*)Rectangle_Rectangle((Rectangle *)malloc(sizeof(Rectangle)), "First Rectangle", 3, 2),
		(Shape*)Rectangle_Rectangle((Rectangle *)malloc(sizeof(Rectangle)), "Second Rectangle", 10, 5),
		(Shape*)Rectangle_Rectangle((Rectangle *)malloc(sizeof(Rectangle)), "Third Rectangle", 5, 6),
		(Shape*)Rectangle_Rectangle((Rectangle *)malloc(sizeof(Rectangle)), "Fourth Rectangle", 3, 4),
		(Shape*)Rectangle_Rectangle((Rectangle *)malloc(sizeof(Rectangle)), "Fifth Rectangle", 10, 3)

	};	
	//Used to print out the Data
	int i = 0;
	for(i = 0; i < sizeof(s)/ sizeof(*s); i++){
		printf("Area: %f\n",(s[i]->VPointer[0])(s[i]));
		printf("Draw: ");
		(s[i]->VPointer[1])(s[i]);
		printf("\n"); 
	}
	//Used to free the Objects so there isn't any memory leaks
	int n = 0;
	for(n = 0; n < 23; n++){
		free(s[n]);
	}

	//Test Cases while building the program
	/*
	Triangle * t[] = {
		Triangle_Triangle((Triangle*)malloc(sizeof(Triangle)), "First Triangle", 4, 5),
		Triangle_Triangle((Triangle *)malloc(sizeof(Triangle)), "Second Triangle", 3, 4),
		Triangle_Triangle((Triangle *)malloc(sizeof(Triangle)), "Third Triangle", 2, 3) 
	};

	int j = 0;
	for(j = 0; j < sizeof(t)/sizeof(*t); j++){
		printf("Area: %f\n", (t[j]->VPointer[0])(t[j]));
		printf("Draw: \n");
		(t[j]->VPointer[1])(t[j]);
	}
	*/
	/*
	Circle * c[] = {
		Circle_Circle((Circle *)malloc(sizeof(Circle)), "First Circle", 3.0),
		Circle_Circle((Circle *)malloc(sizeof(Circle)), "Second Circle", 4.0),
		Circle_Circle((Circle *)malloc(sizeof(Circle)), "Third Circle", 5.0)
	};

	int k = 0;
	for( k = 0; k < sizeof(c)/sizeof(*c); k++){
		printf("Area: %f\n", (c[k]->VPointer[0])(c[k]));
		printf("Draw: \n");
		(c[k]->VPointer[1])(c[k]);
	}
	
	*/
	/*
	Square * sq[] = {
		Square_Square((Square *)malloc(sizeof(Square)), "FirstSquare", 4),
		Square_Square((Square *)malloc(sizeof(Square)), "SecondSquare", 5),
		Square_Square((Square *)malloc(sizeof(Square)), "ThirdSquare", 6)
	};
	
	int l = 0;
	for(l = 0; l < sizeof(sq)/sizeof(*sq); l++){
		printf("Area: %f\n", (sq[l]->VPointer[0])(sq[l]));
		printf("Draw: \n");
		(sq[l]->VPointer[1])(sq[l]);
	}
	*/
	/*
	Rectangle * r[] = {
		Rectangle_Rectangle((Rectangle *)malloc(sizeof(Rectangle)), "FirstRectangle", 3, 10),
		Rectangle_Rectangle((Rectangle *)malloc(sizeof(Rectangle)), "SecondRectangle", 4, 5),
		Rectangle_Rectangle((Rectangle *)malloc(sizeof(Rectangle)), "ThirdRectangle", 8, 10)
	};

	int m = 0;
	for(m = 0; m < sizeof(r)/sizeof(*r); m++){
		printf("Area: %f\n", (r[m]->VPointer[0])(r[m]));
		printf("Draw: \n");
		(r[m]->VPointer[1])(r[m]);
	}
	*/
	/*
	int n = 0;
	for(n = 0; n < 15; n++){
		free(s[n]);
	}
	*/
	//free(ptr);
}
//end of start class
