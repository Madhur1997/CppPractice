#include<iostream>

using namespace std;

class Shape {
public:
    virtual void draw() const = 0;
};

class Circle : public Shape {
private:
    double radius;
public:
    Circle(double r) : radius(r) {}
    void draw() const override {
        cout<<"Drawing circle of radius " << radius << endl;
    }
};

class Square : public Shape {
private:
    double edge_;
public:
    Square(double edge) : edge_(edge) {}
    void draw() const override {
        cout<<"Drawing square of side " << edge_ << endl;
    }
};

void drawShape(Shape* shape) {
    cout<< "Static cast" << endl;
    Circle* circle = static_cast<Circle*>(shape); // Compile-time checked cast
    Square* square = static_cast<Square*>(shape); // Compile-time checked cast 
    circle->draw();
    square->draw();

    cout<< "-------------------\nDynamic cast" << endl;
    Square* dynamicPtrTest = dynamic_cast<Square*>(shape);
    string val = dynamicPtrTest == NULL? "true": "false"; // If dynamic_cast fails, it returns NULL
    cout<<val.c_str()<< endl;

    if(circle = dynamic_cast<Circle*>(shape)) {
        circle->draw();
    } else if(square = dynamic_cast<Square*>(shape)) {
        square->draw();
    } else {
        cout<<"Invalid shape" << endl;
    }   
}

int main() {
    Shape* circle1 = new Circle(3), *square2 = new Square(5);
    drawShape(circle1);
    cout<<"\n";
    drawShape(square2); 
    return 0;
}