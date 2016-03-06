class Logger {
  private:
    int size = 100;
    int* data;
  public:
    Logger(int log_size);
    void push(int value);
    void clear();
    void print();
    int get_average();
};
