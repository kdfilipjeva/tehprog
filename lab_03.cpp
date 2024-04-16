#include <SFML/Graphics.hpp>
#include <cmath>

class Point {
protected:
    float x, y;
    float angle;

public:
    Point(float x, float y) : x(x), y(y), angle(0) {}
    virtual ~Point() {}

    virtual void draw(sf::RenderWindow& window) const = 0;
    virtual void move(float dx, float dy) { x += dx; y += dy; }
    virtual void rotate(float degrees) { angle += degrees; }
    virtual sf::FloatRect getGlobalBounds() const = 0;
};

class Line : public Point {
protected:
    float x2, y2;

public:
    Line(float x1, float y1, float x2, float y2) : Point(x1, y1), x2(x2), y2(y2) {}

    void draw(sf::RenderWindow& window) const override {
        sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(x, y)),
                sf::Vertex(sf::Vector2f(x2, y2))
        };
        window.draw(line, 2, sf::Lines);
    }

    void move(float dx, float dy) override {
        Point::move(dx, dy);
        x2 += dx; y2 += dy;
    }

    sf::FloatRect getGlobalBounds() const override {
        float minX = std::min(x, x2);
        float minY = std::min(y, y2);
        float maxX = std::max(x, x2);
        float maxY = std::max(y, y2);
        return sf::FloatRect(minX, minY, maxX - minX, maxY - minY);
    }
};

class Rectangle : virtual public Point {
protected:
    float width, height;

public:
    Rectangle(float x, float y, float width, float height) : Point(x, y), width(width), height(height) {}

    void draw(sf::RenderWindow& window) const override {
        sf::RectangleShape rectangle(sf::Vector2f(width, height));
        rectangle.setPosition(x, y);
        rectangle.setFillColor(sf::Color::Blue);
        rectangle.setOrigin(width / 2, height / 2);
        rectangle.setRotation(angle);
        window.draw(rectangle);
    }

    sf::FloatRect getGlobalBounds() const override {
        sf::RectangleShape rectangle(sf::Vector2f(width, height));
        rectangle.setPosition(x, y);
        rectangle.setOrigin(width / 2, height / 2);
        rectangle.setRotation(angle);
        return rectangle.getGlobalBounds();
    }
};

class Square : virtual public Rectangle {
public:
    Square(float x, float y, float size) : Point(x, y), Rectangle(x, y, size, size) {}

    void draw(sf::RenderWindow& window) const override {
        sf::RectangleShape square(sf::Vector2f(width, height));
        square.setPosition(x, y);
        square.setFillColor(sf::Color::Red);
        square.setOrigin(width / 2, height / 2);
        square.setRotation(angle);
        window.draw(square);
    }

    sf::FloatRect getGlobalBounds() const override {
        return Rectangle::getGlobalBounds();
    }
};

class Rhombus : virtual public Point {
protected:
    float diagonal1, diagonal2;

public:
    Rhombus(float x, float y, float diagonal1, float diagonal2) : Point(x, y), diagonal1(diagonal1), diagonal2(diagonal2) {}

    void draw(sf::RenderWindow& window) const override {
        sf::ConvexShape rhombus(4);
        rhombus.setPoint(0, sf::Vector2f(0, -diagonal2 / 2));
        rhombus.setPoint(1, sf::Vector2f(diagonal1 / 2, 0));
        rhombus.setPoint(2, sf::Vector2f(0, diagonal2 / 2));
        rhombus.setPoint(3, sf::Vector2f(-diagonal1 / 2, 0));
        rhombus.setPosition(x, y);
        rhombus.setFillColor(sf::Color::Green);
        rhombus.setOrigin(0, 0);
        rhombus.setRotation(angle);
        window.draw(rhombus);
    }

    sf::FloatRect getGlobalBounds() const override {
        sf::ConvexShape rhombus(4);
        rhombus.setPoint(0, sf::Vector2f(0, -diagonal2 / 2));
        rhombus.setPoint(1, sf::Vector2f(diagonal1 / 2, 0));
        rhombus.setPoint(2, sf::Vector2f(0, diagonal2 / 2));
        rhombus.setPoint(3, sf::Vector2f(-diagonal1 / 2, 0));
        rhombus.setPosition(x, y);
        rhombus.setOrigin(0, 0);
        rhombus.setRotation(angle);
        return rhombus.getGlobalBounds();
    }
};

class Parallelogram : public Rectangle, public Rhombus {
public:
    Parallelogram(float x, float y, float width, float height, float angle) :
            Point(x, y),
            Rectangle(x, y, width, height),
            Rhombus(x, y, std::sqrt(width * width + height * height), std::sqrt(width * width + height * height)) {}

    void draw(sf::RenderWindow& window) const override {
        sf::ConvexShape parallelogram(4);
        parallelogram.setPoint(0, sf::Vector2f(0, 0));
        parallelogram.setPoint(1, sf::Vector2f(width, 0));
        parallelogram.setPoint(2, sf::Vector2f(width - height, height));
        parallelogram.setPoint(3, sf::Vector2f(-height, height));
        parallelogram.setPosition(x, y);
        parallelogram.setFillColor(sf::Color::Yellow);
        parallelogram.setOrigin(width / 2, height / 2);
        parallelogram.setRotation(angle);
        window.draw(parallelogram);
    }

    sf::FloatRect getGlobalBounds() const override {
        sf::ConvexShape parallelogram(4);
        parallelogram.setPoint(0, sf::Vector2f(0, 0));
        parallelogram.setPoint(1, sf::Vector2f(width, 0));
        parallelogram.setPoint(2, sf::Vector2f(width - height, height));
        parallelogram.setPoint(3, sf::Vector2f(-height, height));
        parallelogram.setPosition(x, y);
        parallelogram.setOrigin(width / 2, height / 2);
        parallelogram.setRotation(angle);
        return parallelogram.getGlobalBounds();
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Geometry");

    Line line(100, 100, 200, 200);
    Rectangle rectangle(300, 100, 150, 100);
    Square square(500, 100, 100);
    Rhombus rhombus(100, 300, 100, 150);
    Parallelogram parallelogram(300, 300, 200, 100, 30);

    Point* selectedShape = nullptr;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePosition(event.mouseButton.x, event.mouseButton.y);
                    if (rectangle.getGlobalBounds().contains(mousePosition))
                        selectedShape = &rectangle;
                    else if (square.getGlobalBounds().contains(mousePosition))
                        selectedShape = &square;
                    else if (rhombus.getGlobalBounds().contains(mousePosition))
                        selectedShape = &rhombus;
                    else if (parallelogram.getGlobalBounds().contains(mousePosition))
                        selectedShape = &parallelogram;
                }
            }
            else if (event.type == sf::Event::KeyPressed) {
                if (selectedShape != nullptr) {
                    if (event.key.code == sf::Keyboard::Left)
                        selectedShape->move(-10, 0);
                    else if (event.key.code == sf::Keyboard::Right)
                        selectedShape->move(10, 0);
                    else if (event.key.code == sf::Keyboard::Up)
                        selectedShape->move(0, -10);
                    else if (event.key.code == sf::Keyboard::Down)
                        selectedShape->move(0, 10);
                    else if (event.key.code == sf::Keyboard::R)
                        selectedShape->rotate(10);
                    else if (event.key.code == sf::Keyboard::E)
                        selectedShape->rotate(-10);
                }
            }
        }

        window.clear(sf::Color::White);

        line.draw(window);
        rectangle.draw(window);
        square.draw(window);
        rhombus.draw(window);
        parallelogram.draw(window);

        window.display();
    }

    return 0;
}