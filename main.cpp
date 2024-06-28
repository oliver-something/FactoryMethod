#include <iostream>
#include <memory>
#include <string_view>

enum class ProductId {
    FIRST_PRODUCT,
    SECOND_PRODUCT
};

class Product {
public:
    virtual void Print() = 0;
    virtual std::string_view ToString() = 0;
    virtual ~Product() = default;
};

class FirstConcreteProduct : public Product {
public:
    void Print() override {
        std::cout << "This is from " << this->ToString() << '\n';
    }

    std::string_view ToString() override {
        return "First Product";
    }
};

class SecondConcreteProduct : public Product {
public:
    void Print() override {
        std::cout << "This is from " << this->ToString() << '\n';
    }

    std::string_view ToString() override {
        return "Second Product";
    }
};

class Creator {
public:
    [[nodiscard]] virtual std::unique_ptr<Product> create(ProductId id) const {
        switch (id) {

            case ProductId::FIRST_PRODUCT:
                return std::make_unique<FirstConcreteProduct>();
            case ProductId::SECOND_PRODUCT:
                return std::make_unique<SecondConcreteProduct>();
            default:
                return nullptr;
        }
    }
    virtual ~Creator() = default;
};

int main() {
    std::unique_ptr<Creator> creator = std::make_unique<Creator>();
    std::unique_ptr<Product> product;

    product = creator->create(ProductId::FIRST_PRODUCT);
    if(product) product->Print();
    product = creator->create(ProductId::SECOND_PRODUCT);
    if (product) product->Print();
    return 0;
}
