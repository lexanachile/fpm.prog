class AbstractContainer
{
public:
    virtual ~AbstractContainer() {};
    virtual bool IsEmpty() const = 0;    // контейнер пуст
    virtual void push(const int &n) = 0; // втолкнуть
    virtual void pop() = 0;		 		 // вытолкнуть
    virtual int Size() const = 0;		 // количество элементов
    virtual void Show() const = 0;
};
