#include <iostream>
#include <vector>

// Інтерфейс ітератора
template <typename T>
class Iterator {
public:
    virtual T next() = 0;
    virtual bool hasNext() const = 0;
    virtual ~Iterator() = default;
};

// Конкретний ітератор для вектора
template <typename T>
class VectorIterator : public Iterator<T> {
public:
    VectorIterator(const std::vector<T>& vector) : vector_(vector), index_(0) {}

    T next() override {
        return vector_[index_++];
    }

    bool hasNext() const override {
        return index_ < vector_.size();
    }

private:
    const std::vector<T>& vector_;
    size_t index_;
};

// Колекція
template <typename T>
class Collection {
public:
    virtual std::shared_ptr<Iterator<T>> createIterator() const = 0;
    virtual ~Collection() = default;
};

// Конкретна колекція, яка використовує вектор
template <typename T>
class ConcreteCollection : public Collection<T> {
public:
    void addItem(const T& item) {
        items_.push_back(item);
    }

    std::shared_ptr<Iterator<T>> createIterator() const override {
        return std::make_shared<VectorIterator<T>>(items_);
    }

private:
    std::vector<T> items_;
};

int main() {
    // Використання паттерна "Ітератор"
    ConcreteCollection<int> collection;
    collection.addItem(1);
    collection.addItem(2);
    collection.addItem(3);

    std::shared_ptr<Iterator<int>> iterator = collection.createIterator();

    while (iterator->hasNext()) {
        std::cout << iterator->next() << " ";
    }

    return 0;
}
