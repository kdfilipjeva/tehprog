#include <cmath>
#include <iostream>
#include <vector>

class GeometricObject {
public:
    virtual std::vector<std::pair<int, int>> getPoints() = 0;
    virtual void display() = 0;
    virtual void remove() = 0;
    virtual void move(int dx, int dy) = 0;
    virtual void rotate(double angle) = 0;
};

class Point : public GeometricObject {
public:
    int x, y;
    Point(int x, int y) : x(x), y(y) {}
    virtual std::vector<std::pair<int, int>> getPoints() override { return {{x, y}}; }
    virtual void display() override { std::cout << "Point (" << x << ", " << y << ")" << std::endl; }
    virtual void remove() override { std::cout << "Removing point (" << x << ", " << y << ")" << std::endl; }
    virtual void move(int dx, int dy) override { x += dx; y += dy; }
    virtual void rotate(double angle) override {
        double rad = angle * M_PI / 180.0;
        int newX = x * std::cos(rad) - y * std::sin(rad);
        int newY = x * std::sin(rad) + y * std::cos(rad);
        x = newX;
        y = newY;
    }
};

class Line : public GeometricObject {
protected:
    Point start, end;
public:
    Line(int x1, int y1, int x2, int y2) : start(x1, y1), end(x2, y2) {}
    virtual std::vector<std::pair<int, int>> getPoints() override { return {std::make_pair(start.x, start.y), std::make_pair(end.x, end.y)}; }
    virtual void display() override {
        std::cout << "Line from (" << start.x << ", " << start.y << ") to (" << end.x << ", " << end.y << ")" << std::endl;
        for (auto& point : getPoints()) {
            std::cout << "  Point (" << point.first << ", " << point.second << ")" << std::endl;
        }
    }
    virtual void remove() override {
        std::cout << "Removing line from (" << start.x << ", " << start.y << ") to (" << end.x << ", " << end.y << ")" << std::endl;
    }
    virtual void move(int dx, int dy) override {
        start.move(dx, dy);
        end.move(dx, dy);
    }
    virtual void rotate(double angle) override {
        start.rotate(angle);
        end.rotate(angle);
        std::cout << "Line after rotation:" << std::endl;
        for (auto& point : getPoints()) {
            std::cout << "  Point (" << point.first << ", " << point.second << ")" << std::endl;
        }
    }
};

class Rectangle : public GeometricObject {
protected:
    Point topLeft;
    int width, height;
public:
    Rectangle(int x, int y, int w, int h) : topLeft(x, y), width(w), height(h) {}
    virtual std::vector<std::pair<int, int>> getPoints() override {
        return {
                std::make_pair(topLeft.x, topLeft.y),
                std::make_pair(topLeft.x + width, topLeft.y),
                std::make_pair(topLeft.x + width, topLeft.y + height),
                std::make_pair(topLeft.x, topLeft.y + height)
        };
    }
    virtual void display() override {
        std::cout << "Rectangle with top-left (" << topLeft.x << ", " << topLeft.y << "), width " << width << ", and height " << height << std::endl;
        for (auto& point : getPoints()) {
            std::cout << "  Point (" << point.first << ", " << point.second << ")" << std::endl;
        }
    }
    virtual void remove() override {
        std::cout << "Removing rectangle with top-left (" << topLeft.x << ", " << topLeft.y << "), width " << width << ", and height " << height << std::endl;
    }
    virtual void move(int dx, int dy) override {
        topLeft.move(dx, dy);
    }
    virtual void rotate(double angle) override {
        for (auto& point : getPoints()) {
            Point p(point.first, point.second);
            p.rotate(angle);
            std::cout << "  Point (" << p.x << ", " << p.y << ")" << std::endl;
        }
    }
};

class Rhombus : public GeometricObject {
protected:
    Point center;
    int width, height;
public:
    Rhombus(int x, int y, int w, int h) : center(x, y), width(w), height(h) {}
    virtual std::vector<std::pair<int, int>> getPoints() override {
        return {
                std::make_pair(center.x - width / 2, center.y),
                std::make_pair(center.x, center.y + height / 2),
                std::make_pair(center.x + width / 2, center.y),
                std::make_pair(center.x, center.y - height / 2)
        };
    }
    virtual void display() override {
        std::cout << "Rhombus with center (" << center.x << ", " << center.y << "), width " << width << ", and height " << height << std::endl;
        for (auto& point : getPoints()) {
            std::cout << "  Point (" << point.first << ", " << point.second << ")" << std::endl;
        }
    }
    virtual void remove() override {
        std::cout << "Removing rhombus with center (" << center.x << ", " << center.y << "), width " << width << ", and height " << height << std::endl;
    }
    virtual void move(int dx, int dy) override {
        center.move(dx, dy);
    }
    virtual void rotate(double angle) override {
        for (auto& point : getPoints()) {
            Point p(point.first, point.second);
            p.rotate(angle);
            std::cout << "  Point (" << p.x << ", " << p.y << ")" << std::endl;
        }
    }
};

class Square : public virtual GeometricObject {
protected:
    Point topLeft;
    int size;
public:
    Square(int x, int y, int size) : topLeft(x, y), size(size) {}
    virtual std::vector<std::pair<int, int>> getPoints() override {
        return {
                std::make_pair(topLeft.x, topLeft.y),
                std::make_pair(topLeft.x + size, topLeft.y),
                std::make_pair(topLeft.x + size, topLeft.y + size),
                std::make_pair(topLeft.x, topLeft.y + size)
        };
    }
    virtual void display() override {
        std::cout << "Square with top-left (" << topLeft.x << ", " << topLeft.y << ") and size " << size << std::endl;
        for (auto& point : getPoints()) {
            std::cout << "  Point (" << point.first << ", " << point.second << ")" << std::endl;
        }
    }
    virtual void remove() override {
        std::cout << "Removing square with top-left (" << topLeft.x << ", " << topLeft.y << ") and size " << size << std::endl;
    }
    virtual void move(int dx, int dy) override {
        topLeft.move(dx, dy);
    }
    virtual void rotate(double angle) override {
        for (auto& point : getPoints()) {
            Point p(point.first, point.second);
            p.rotate(angle);
            std::cout << "  Point (" << p.x << ", " << p.y << ")" << std::endl;
        }
    }
};

class Parallelogram : public virtual GeometricObject {
protected:
    Point topLeft;
    int width, height;
public:
    Parallelogram(int x, int y, int w, int h) : topLeft(x, y), width(w), height(h) {}
    virtual std::vector<std::pair<int, int>> getPoints() override {
        return {
                std::make_pair(topLeft.x, topLeft.y),
                std::make_pair(topLeft.x + width, topLeft.y),
                std::make_pair(topLeft.x + width, topLeft.y + height),
                std::make_pair(topLeft.x, topLeft.y + height)
        };
    }
    virtual void display() override {
        std::cout << "Parallelogram with top-left (" << topLeft.x << ", " << topLeft.y << "), width " << width << ", and height " << height << std::endl;
        for (auto& point : getPoints()) {
            std::cout << "  Point (" << point.first << ", " << point.second << ")" << std::endl;
        }
    }
    virtual void remove() override {
        std::cout << "Removing parallelogram with top-left (" << topLeft.x << ", " << topLeft.y << "), width " << width << ", and height " << height << std::endl;
    }
    virtual void move(int dx, int dy) override {
        topLeft.move(dx, dy);
    }
    virtual void rotate(double angle) override {
        for (auto& point : getPoints()) {
            Point p(point.first, point.second);
            p.rotate(angle);
            std::cout << "  Point (" << p.x << ", " << p.y << ")" << std::endl;
        }
    }
};

int main() {
    int choice, action;
    GeometricObject* obj = nullptr;

    std::cout << "Choose a geometric object:\n";
    std::cout << "1. Point\n2. Line\n3. Rectangle\n4. Rhombus\n5. Square\n6. Parallelogram\n";
    std::cin >> choice;

    switch (choice) {
        case 1:
            obj = new Point(100, 100);
            break;
        case 2:
            obj = new Line(50, 50, 100, 100);
            break;
        case 3:
            obj = new Rectangle(75, 75, 40, 60);
            break;
        case 4:
            obj = new Rhombus(150, 150, 40, 60);
            break;
        case 5:
            obj = new Square(50, 50, 30);
            break;
        case 6:
            obj = new Parallelogram(75, 75, 40, 60);
            break;
        default:
            std::cout << "Invalid choice.\n";
            return 1;
    }

    obj->display();

    std::cout << "What do you want to do?\n";
    std::cout << "1. Move\n2. Rotate\n";
    std::cin >> action;

    if (action == 1) {
        int dx, dy;
        std::cout << "Enter dx and dy: ";
        std::cin >> dx >> dy;
        obj->move(dx, dy);
        obj->display();
    } else if (action == 2) {
        double angle;
        std::cout << "Enter angle (in degrees): ";
        std::cin >> angle;
        obj->rotate(angle);
    } else {
        std::cout << "Invalid choice.\n";
    }

    obj->remove();
    delete obj;
    return 0;
}
