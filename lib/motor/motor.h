class Motor {
  private:
    int* left_wheel;
    int* right_wheel;
    int speed;
  public:
    Motor(int* left, int* right, int speed);
    void setup();
    void set_direction(const int* motor, int dir);
    void set_speed(const int* motor, int m_speed);
    void stop();
    void go();
    void forward();
    void backward();
    void left();
    void right();
    void breaks(bool val);
    int get_left_current();
    int get_right_current();
};
