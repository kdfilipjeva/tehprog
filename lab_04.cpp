#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

class Product {
public:
    Product(const std::string& id, const std::string& name, double price, const std::string& category, const std::string& description)
            : id(id), name(name), price(price), category(category), description(description) {}

    std::string id;
    std::string name;
    double price;
    std::string category;
    std::string description;
};

class SimpleDB {
public:
    SimpleDB(const std::string& filename) : filename(filename) {
        loadFromFile();
    }

    void loadFromFile() {
        std::ifstream file(filename);
        if (file.is_open()) {
            std::string line;
            while (std::getline(file, line)) {
                std::istringstream iss(line);
                std::string id, name, category, description;
                double price;
                if (std::getline(iss, id, ',') &&
                    std::getline(iss, name, ',') &&
                    iss >> price &&
                    iss.ignore() &&
                    std::getline(iss, category, ',') &&
                    std::getline(iss, description)) {
                    data.emplace_back(id, name, price, category, description);
                }
            }
            file.close();
        }
    }

    void saveToFile() {
        std::ofstream file(filename);
        if (file.is_open()) {
            for (const auto& product : data) {
                file << product.id << ","
                     << product.name << ","
                     << product.price << ","
                     << product.category << ","
                     << product.description << "\n";
            }
            file.close();
        }
    }

    void addProduct(const Product& product) {
        data.push_back(product);
        saveToFile();
    }

    void editProduct(const std::string& id, const std::string& name, double price, const std::string& category, const std::string& description) {
        for (auto& product : data) {
            if (product.id == id) {
                product.name = name;
                product.price = price;
                product.category = category;
                product.description = description;
                break;
            }
        }
        saveToFile();
    }

    void deleteProduct(const std::string& id) {
        data.erase(std::remove_if(data.begin(), data.end(), [&](const Product& product) {
            return product.id == id;
        }), data.end());
        saveToFile();
    }

    Product* findProduct(const std::string& id) {
        for (auto& product : data) {
            if (product.id == id) {
                return &product;
            }
        }
        return nullptr;
    }

    void displayProduct(const Product& product) {
        std::cout << "ID: " << product.id << "\n";
        std::cout << "Name: " << product.name << "\n";
        std::cout << "Price: " << product.price << "\n";
        std::cout << "Category: " << product.category << "\n";
        std::cout << "Description: " << product.description << "\n";
    }

private:
    std::string filename;
    std::vector<Product> data;
};

int main() {
    SimpleDB db("products.txt");

    while (true) {
        std::cout << "\nMenu:\n";
        std::cout << "1. Add product\n";
        std::cout << "2. Edit product\n";
        std::cout << "3. Delete product\n";
        std::cout << "4. Find product\n";
        std::cout << "5. Exit\n";

        std::string choice;
        std::cout << "Enter your choice (1-5): ";
        std::getline(std::cin, choice);

        if (choice == "1") {
            std::string id, name, category, description;
            double price;
            std::cout << "Enter product ID: ";
            std::getline(std::cin, id);
            std::cout << "Enter product name: ";
            std::getline(std::cin, name);
            std::cout << "Enter product price: ";
            std::cin >> price;
            std::cin.ignore();
            std::cout << "Enter product category: ";
            std::getline(std::cin, category);
            std::cout << "Enter product description: ";
            std::getline(std::cin, description);
            Product product(id, name, price, category, description);
            db.addProduct(product);
            std::cout << "Product added successfully.\n";
        }
        else if (choice == "2") {
            std::string id;
            std::cout << "Enter product ID to edit: ";
            std::getline(std::cin, id);
            Product* product = db.findProduct(id);
            if (product) {
                std::string name, category, description;
                double price;
                std::cout << "Enter new name (" << product->name << "): ";
                std::getline(std::cin, name);
                if (!name.empty()) {
                    product->name = name;
                }
                std::cout << "Enter new price (" << product->price << "): ";
                std::cin >> price;
                std::cin.ignore();
                if (price > 0) {
                    product->price = price;
                }
                std::cout << "Enter new category (" << product->category << "): ";
                std::getline(std::cin, category);
                if (!category.empty()) {
                    product->category = category;
                }
                std::cout << "Enter new description (" << product->description << "): ";
                std::getline(std::cin, description);
                if (!description.empty()) {
                    product->description = description;
                }
                db.editProduct(id, product->name, product->price, product->category, product->description);
                std::cout << "Product edited successfully.\n";
            }
            else {
                std::cout << "Product not found.\n";
            }
        }
        else if (choice == "3") {
            std::string id;
            std::cout << "Enter product ID to delete: ";
            std::getline(std::cin, id);
            db.deleteProduct(id);
            std::cout << "Product deleted successfully.\n";
        }
        else if (choice == "4") {
            std::string id;
            std::cout << "Enter product ID to find: ";
            std::getline(std::cin, id);
            Product* product = db.findProduct(id);
            if (product) {
                db.displayProduct(*product);
            }
            else {
                std::cout << "Product not found.\n";
            }
        }
        else if (choice == "5") {
            break;
        }
        else {
            std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
