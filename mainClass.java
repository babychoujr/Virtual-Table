import java.lang.Math;
class Shape{
	String name;
	Shape(String newName){
           name = newName;
	}

	double area(){
	   return 0.0;
	}
	void draw(){
	   System.out.println(name);
	}
}

class Triangle extends Shape{
	int myHeight, myBase;
	Triangle(String name, int h, int b){
		super(name);
		myHeight = h;
		myBase = b;
	}
	
	double area(){
		return 0.5 * myHeight * myBase;
	}

	void draw(){
		System.out.println("Shape: " + name);
		System.out.println("*");
		System.out.println("**");
		System.out.println("***");
		System.out.println("****");
	}
}

class Circle extends Shape{
	int myRadius;
	Circle(String name, int r){
		super(name);
		myRadius = r;
	}

	double area(){
		return myRadius * myRadius *  Math.PI; 
	}	
	
	void draw(){
		System.out.println("Shape: " + name);
		System.out.println(" **** ");
		System.out.println("*    *");
		System.out.println(" **** ");
	}
}

class Square extends Shape{
	int mySide;
	Square(String name, int side){
		super(name);
		mySide = side;
	}
	
	double area(){
		return mySide * mySide;
	}
	
	void draw(){
		System.out.println("Shape: " + name);
		System.out.println("****");
		System.out.println("*  *");
		System.out.println("*  *");
		System.out.println("****");
	}

	public double getSide(){
		return mySide;
	}
}

class Rectangle extends Square{
	int myHeight;

	Rectangle(String name, int side, int height){
		super(name, side);
		myHeight = height;
	}

	double area(){
		return myHeight * super.getSide();
	}
	
	void draw(){
		System.out.println("Shape: " + name);
		System.out.println("--------");
		System.out.println("|      |");
		System.out.println("--------");
	}
}

class ListNode{
	Shape info;
	ListNode next;
	
	ListNode(Shape newInfo, ListNode newNext){
		info = newInfo;
		next = newNext;
	}
}
class Picture{
	ListNode head;
	
	public Picture(){
		head = null;
	}	

	void add(Shape sh){
		head = new ListNode(sh, head);
	}
	
	void drawAll(){
		for(ListNode p = head; p != null; p = p.next){
			p.info.draw();
		}
	}
	
	double totalArea(){
		double area = 0.0;
		for(ListNode p = head; p != null; p = p.next){
			area += p.info.area();	
		}
		return area;
	}
}


public class mainClass{
	static void println(double d){
		System.out.println("Double d is "+ d);
	}
	
	public static void main(String[] args){
		Picture p = new Picture();
		p.add(new Triangle("FirstTriangle", 5, 5));
		p.add(new Triangle("SecondTriangle", 4, 3));
		p.add(new Circle("FirstCircle", 5));
	//	p.printShapes();
		System.out.println(p.totalArea());
		p.drawAll();

		Picture j = new Picture();
		j.add(new Square("FirstSquare", 5));
		j.add(new Square("SecondSquare", 4));
		j.add(new Square("ThirdSquare", 3));

		System.out.println(j.totalArea());
		j.drawAll();
		
		Picture r = new Picture();
		r.add(new Rectangle("First Rectangle", 3, 2));
		r.add(new Rectangle("Second Rectangle", 10, 5));
		r.add(new Rectangle("Third Rectangle", 5, 6));
		
		System.out.println(r.totalArea());
		r.drawAll();

		Picture c = new Picture();
		c.add(new Circle("First Circle", 6));
		c.add(new Circle("Second Circle", 5));
		c.add(new Circle("Third Circle", 4));

		System.out.println(c.totalArea());
		c.drawAll();	
	}	
}

